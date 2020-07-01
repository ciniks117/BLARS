#include "__cf_AbstractFuelControl_expanded_breach.h"
#include <math.h>
#include "AbstractFuelControl_expanded_breach_acc.h"
#include "AbstractFuelControl_expanded_breach_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T
AbstractFuelControl_expanded_breach_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T
* bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
{ int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T
* tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail <
( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] )
&& ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T *
tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024
; if ( newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU
= ( real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if (
tempU == ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if (
istransportdelay ) * xBufPtr = tempX ; } else { * tailPtr = testIdx ; }
return ( true ) ; } real_T
AbstractFuelControl_expanded_breach_acc_rt_VTDelayfindtDInterpolate ( real_T
x , real_T * tBuf , real_T * uBuf , real_T * xBuf , int_T bufSz , int_T head
, int_T tail , int_T * pLast , real_T t , real_T tStart , boolean_T discrete
, boolean_T minorStepAndTAtLastMajorOutput , real_T initOutput , real_T *
appliedDelay ) { int_T n , k ; real_T f ; int_T kp1 ; real_T tminustD , tL ,
tR , uD , uL , uR , fU ; if ( minorStepAndTAtLastMajorOutput ) { if ( * pLast
== head ) { * pLast = ( * pLast == 0 ) ? bufSz - 1 : * pLast - 1 ; } head = (
head == 0 ) ? bufSz - 1 : head - 1 ; } if ( x <= 1 ) { return initOutput ; }
k = * pLast ; n = 0 ; for ( ; ; ) { n ++ ; if ( n > bufSz ) break ; if ( x -
xBuf [ k ] > 1.0 ) { if ( k == head ) { int_T km1 ; f = ( x - 1.0 - xBuf [ k
] ) / ( x - xBuf [ k ] ) ; tminustD = ( 1.0 - f ) * tBuf [ k ] + f * t ; km1
= k - 1 ; if ( km1 < 0 ) km1 = bufSz - 1 ; tL = tBuf [ km1 ] ; tR = tBuf [ k
] ; uL = uBuf [ km1 ] ; uR = uBuf [ k ] ; break ; } kp1 = k + 1 ; if ( kp1 ==
bufSz ) kp1 = 0 ; if ( x - xBuf [ kp1 ] <= 1.0 ) { f = ( x - 1.0 - xBuf [ k ]
) / ( xBuf [ kp1 ] - xBuf [ k ] ) ; tL = tBuf [ k ] ; tR = tBuf [ kp1 ] ; uL
= uBuf [ k ] ; uR = uBuf [ kp1 ] ; tminustD = ( 1.0 - f ) * tL + f * tR ;
break ; } k = kp1 ; } else { if ( k == tail ) { f = ( x - 1.0 ) / xBuf [ k ]
; if ( discrete ) { return ( uBuf [ tail ] ) ; } kp1 = k + 1 ; if ( kp1 ==
bufSz ) kp1 = 0 ; tminustD = ( 1 - f ) * tStart + f * tBuf [ k ] ; tL = tBuf
[ k ] ; tR = tBuf [ kp1 ] ; uL = uBuf [ k ] ; uR = uBuf [ kp1 ] ; break ; } k
= k - 1 ; if ( k < 0 ) k = bufSz - 1 ; } } * pLast = k ; if ( tR == tL ) { fU
= 1.0 ; } else { fU = ( tminustD - tL ) / ( tR - tL ) ; } if ( discrete ) {
uD = ( fU > ( 1.0 - fU ) ) ? uR : uL ; } else { uD = ( 1.0 - fU ) * uL + fU *
uR ; } * appliedDelay = t - tminustD ; return uD ; } real_T look2_binlxpw (
real_T u0 , real_T u1 , const real_T bp0 [ ] , const real_T bp1 [ ] , const
real_T table [ ] , const uint32_T maxIndex [ ] , uint32_T stride ) { real_T
frac ; uint32_T bpIndices [ 2 ] ; real_T fractions [ 2 ] ; real_T yL_1d ;
uint32_T iRght ; uint32_T bpIdx ; uint32_T iLeft ; if ( u0 <= bp0 [ 0U ] ) {
iLeft = 0U ; frac = ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ] - bp0 [ 0U ] ) ; }
else if ( u0 < bp0 [ maxIndex [ 0U ] ] ) { bpIdx = maxIndex [ 0U ] >> 1U ;
iLeft = 0U ; iRght = maxIndex [ 0U ] ; while ( iRght - iLeft > 1U ) { if ( u0
< bp0 [ bpIdx ] ) { iRght = bpIdx ; } else { iLeft = bpIdx ; } bpIdx = (
iRght + iLeft ) >> 1U ; } frac = ( u0 - bp0 [ iLeft ] ) / ( bp0 [ iLeft + 1U
] - bp0 [ iLeft ] ) ; } else { iLeft = maxIndex [ 0U ] - 1U ; frac = ( u0 -
bp0 [ maxIndex [ 0U ] - 1U ] ) / ( bp0 [ maxIndex [ 0U ] ] - bp0 [ maxIndex [
0U ] - 1U ] ) ; } fractions [ 0U ] = frac ; bpIndices [ 0U ] = iLeft ; if (
u1 <= bp1 [ 0U ] ) { iLeft = 0U ; frac = ( u1 - bp1 [ 0U ] ) / ( bp1 [ 1U ] -
bp1 [ 0U ] ) ; } else if ( u1 < bp1 [ maxIndex [ 1U ] ] ) { bpIdx = maxIndex
[ 1U ] >> 1U ; iLeft = 0U ; iRght = maxIndex [ 1U ] ; while ( iRght - iLeft >
1U ) { if ( u1 < bp1 [ bpIdx ] ) { iRght = bpIdx ; } else { iLeft = bpIdx ; }
bpIdx = ( iRght + iLeft ) >> 1U ; } frac = ( u1 - bp1 [ iLeft ] ) / ( bp1 [
iLeft + 1U ] - bp1 [ iLeft ] ) ; } else { iLeft = maxIndex [ 1U ] - 1U ; frac
= ( u1 - bp1 [ maxIndex [ 1U ] - 1U ] ) / ( bp1 [ maxIndex [ 1U ] ] - bp1 [
maxIndex [ 1U ] - 1U ] ) ; } bpIdx = iLeft * stride + bpIndices [ 0U ] ;
yL_1d = ( table [ bpIdx + 1U ] - table [ bpIdx ] ) * fractions [ 0U ] + table
[ bpIdx ] ; bpIdx += stride ; return ( ( ( table [ bpIdx + 1U ] - table [
bpIdx ] ) * fractions [ 0U ] + table [ bpIdx ] ) - yL_1d ) * frac + yL_1d ; }
static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T B_14_11_0 ;
real_T B_14_28_0 ; real_T B_14_38_0 ; real_T B_14_42_0 ; real_T B_14_54_0 ;
real_T B_14_58_0 ; real32_T B_14_10_0 ; real32_T B_14_24_0 ; real32_T
B_13_5_0 ; boolean_T B_13_4_0 ; real32_T rtb_B_1_9_0 ; real32_T rtb_B_4_0_0 ;
boolean_T rtb_B_10_3_0 ; ZCEventType zcEvent ; real_T rtb_B_13_0_0 ; real32_T
rtb_B_13_3_0 ; real_T taskTimeV ; uint32_T numCycles ; real_T ratio ;
B_AbstractFuelControl_expanded_breach_T * _rtB ;
P_AbstractFuelControl_expanded_breach_T * _rtP ;
X_AbstractFuelControl_expanded_breach_T * _rtX ;
PrevZCX_AbstractFuelControl_expanded_breach_T * _rtZCE ;
DW_AbstractFuelControl_expanded_breach_T * _rtDW ; _rtDW = ( (
DW_AbstractFuelControl_expanded_breach_T * ) ssGetRootDWork ( S ) ) ; _rtZCE
= ( ( PrevZCX_AbstractFuelControl_expanded_breach_T * ) _ssGetPrevZCSigState
( S ) ) ; _rtX = ( ( X_AbstractFuelControl_expanded_breach_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_AbstractFuelControl_expanded_breach_T
* ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_AbstractFuelControl_expanded_breach_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB
-> B_14_0_0 = _rtX -> Integrator2_CSTATE ; _rtB -> B_14_1_0 = _rtP -> P_8 *
_rtB -> B_14_0_0 ; ssCallAccelRunBlock ( S , 14 , 2 , SS_CALL_MDL_OUTPUTS ) ;
if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> EngineSpeed9001100_MODE = ( (
ExternalUPtrs_AbstractFuelControl_expanded_breach_T * ) ssGetU ( S ) ) ->
speed >= _rtP -> P_9 ? 1 : ( (
ExternalUPtrs_AbstractFuelControl_expanded_breach_T * ) ssGetU ( S ) ) ->
speed > _rtP -> P_10 ? 0 : - 1 ; } _rtB -> B_14_3_0 = _rtDW ->
EngineSpeed9001100_MODE == 1 ? _rtP -> P_9 : _rtDW -> EngineSpeed9001100_MODE
== - 1 ? _rtP -> P_10 : ( (
ExternalUPtrs_AbstractFuelControl_expanded_breach_T * ) ssGetU ( S ) ) ->
speed ; _rtB -> B_14_4_0 = _rtP -> P_11 * _rtB -> B_14_3_0 ; _rtDW ->
engine_speed = ( real32_T ) _rtB -> B_14_4_0 ; _rtB -> B_14_6_0 = 0.0 ; _rtB
-> B_14_6_0 += _rtP -> P_13 * _rtX -> Throttledelay_CSTATE ; _rtB -> B_14_8_0
= _rtB -> B_14_6_0 + _rtB -> B_14_7_0 ; if ( ssIsMajorTimeStep ( S ) ) {
_rtDW -> theta090_MODE = _rtB -> B_14_8_0 >= _rtP -> P_15 ? 1 : _rtB ->
B_14_8_0 > _rtP -> P_16 ? 0 : - 1 ; } _rtB -> B_14_9_0 = _rtDW ->
theta090_MODE == 1 ? _rtP -> P_15 : _rtDW -> theta090_MODE == - 1 ? _rtP ->
P_16 : _rtB -> B_14_8_0 ; B_14_10_0 = ( real32_T ) _rtB -> B_14_9_0 ;
B_14_11_0 = ( ( 2.821 - 0.05231 * _rtB -> B_14_9_0 ) + 0.10299 * _rtB ->
B_14_9_0 * _rtB -> B_14_9_0 ) - 0.00063 * _rtB -> B_14_9_0 * _rtB -> B_14_9_0
* _rtB -> B_14_9_0 ; _rtB -> B_14_12_0 = _rtX -> p00543bar_CSTATE ; _rtB ->
B_14_14_0 = _rtB -> B_14_12_0 / _rtB -> B_14_13_0 ; _rtB -> B_14_15_0 = 1.0 /
_rtB -> B_14_12_0 * _rtB -> B_14_13_0 ; if ( ssIsMajorTimeStep ( S ) ) {
taskTimeV = _rtB -> B_14_14_0 ; _rtDW -> MinMax_MODE = 0 ; if ( _rtB ->
B_14_15_0 < _rtB -> B_14_14_0 ) { taskTimeV = _rtB -> B_14_15_0 ; _rtDW ->
MinMax_MODE = 1 ; } _rtB -> B_14_16_0 = taskTimeV ; } else { taskTimeV = _rtB
-> B_14_14_0 ; if ( _rtDW -> MinMax_MODE == 1 ) { taskTimeV = _rtB ->
B_14_15_0 ; } _rtB -> B_14_16_0 = taskTimeV ; } taskTimeV = _rtB -> B_14_16_0
- _rtB -> B_14_16_0 * _rtB -> B_14_16_0 ; if ( taskTimeV < 0.0 ) { taskTimeV
= - muDoubleScalarSqrt ( - taskTimeV ) ; } else { taskTimeV =
muDoubleScalarSqrt ( taskTimeV ) ; } _rtB -> B_14_17_0 = 2.0 * taskTimeV ; if
( ssIsMajorTimeStep ( S ) ) { _rtDW -> Switch1_Mode = ( _rtB -> B_14_16_0 >=
_rtP -> P_20 ) ; } if ( _rtDW -> Switch1_Mode ) { _rtB -> B_14_19_0 = _rtB ->
B_14_17_0 ; } else { _rtB -> B_14_19_0 = _rtB -> B_14_18_0 ; } _rtB ->
B_14_20_0 = _rtB -> B_14_13_0 - _rtB -> B_14_12_0 ; if ( ssIsSampleHit ( S ,
1 , 0 ) ) { if ( _rtB -> B_14_20_0 > 0.0 ) { _rtDW -> flowdirection_MODE = 1
; } else if ( _rtB -> B_14_20_0 < 0.0 ) { _rtDW -> flowdirection_MODE = - 1 ;
} else { _rtDW -> flowdirection_MODE = 0 ; } _rtB -> B_14_21_0 = _rtDW ->
flowdirection_MODE ; _rtDW -> AFSensorFaultInjection_MODE = ( ssGetTaskTime (
S , 1 ) >= _rtP -> P_23 ) ; if ( _rtDW -> AFSensorFaultInjection_MODE == 1 )
{ _rtB -> B_14_26_0 = _rtP -> P_25 ; } else { _rtB -> B_14_26_0 = _rtP ->
P_24 ; } } _rtB -> B_14_22_0 = B_14_11_0 * _rtB -> B_14_19_0 * _rtB ->
B_14_21_0 ; B_14_24_0 = ( real32_T ) ( _rtP -> P_21 * _rtB -> B_14_22_0 ) ;
if ( _rtB -> B_14_26_0 >= _rtP -> P_26 ) { taskTimeV = _rtB -> B_14_25_0 ; }
else { taskTimeV = _rtB -> B_14_1_0 ; } B_14_28_0 = _rtP -> P_27 * taskTimeV
; _rtDW -> airbyfuel_meas = ( real32_T ) B_14_28_0 ; if ( ssIsSampleHit ( S ,
1 , 0 ) ) { _rtDW -> Pwon_MODE = ( ssGetTaskTime ( S , 1 ) >= _rtP -> P_0 ) ;
if ( _rtDW -> Pwon_MODE == 1 ) { rtb_B_13_0_0 = _rtP -> P_2 ; } else {
rtb_B_13_0_0 = _rtP -> P_1 ; } } if ( ssIsSampleHit ( S , 3 , 0 ) ) {
taskTimeV = ssGetTaskTime ( S , 3 ) ; if ( ssGetTNextWasAdjusted ( S , 3 ) )
{ _rtDW -> nextTime = _ssGetVarNextHitTime ( S , 0 ) ; } if ( _rtDW ->
justEnabled != 0 ) { _rtDW -> justEnabled = 0 ; if ( taskTimeV >= _rtP -> P_6
) { ratio = ( taskTimeV - _rtP -> P_6 ) / _rtP -> P_4 ; numCycles = (
uint32_T ) muDoubleScalarFloor ( ratio ) ; if ( muDoubleScalarAbs ( ( real_T
) ( numCycles + 1U ) - ratio ) < DBL_EPSILON * ratio ) { numCycles ++ ; }
_rtDW -> numCompleteCycles = numCycles ; ratio = ( ( real_T ) numCycles *
_rtP -> P_4 + _rtP -> P_6 ) + _rtP -> P_5 * _rtP -> P_4 / 100.0 ; if (
taskTimeV < ratio ) { _rtDW -> currentValue = 1 ; _rtDW -> nextTime = ratio ;
} else { _rtDW -> currentValue = 0 ; _rtDW -> nextTime = ( real_T ) (
numCycles + 1U ) * _rtP -> P_4 + _rtP -> P_6 ; } } else { _rtDW ->
numCompleteCycles = _rtP -> P_6 != 0.0 ? - 1 : 0 ; _rtDW -> currentValue = 0
; _rtDW -> nextTime = _rtP -> P_6 ; } } else { if ( _rtDW -> nextTime <=
taskTimeV ) { if ( _rtDW -> currentValue == 1 ) { _rtDW -> currentValue = 0 ;
_rtDW -> nextTime = ( real_T ) ( _rtDW -> numCompleteCycles + 1L ) * _rtP ->
P_4 + _rtP -> P_6 ; } else { _rtDW -> numCompleteCycles ++ ; _rtDW ->
currentValue = 1 ; _rtDW -> nextTime = ( _rtP -> P_5 * _rtP -> P_4 * 0.01 + (
real_T ) _rtDW -> numCompleteCycles * _rtP -> P_4 ) + _rtP -> P_6 ; } } }
_ssSetVarNextHitTime ( S , 0 , _rtDW -> nextTime ) ; if ( _rtDW ->
currentValue == 1 ) { _rtB -> B_13_1_0 = _rtP -> P_3 ; } else { _rtB ->
B_13_1_0 = 0.0 ; } } ssWriteToDataStoreWithPath ( S , ( int ) _rtDW ->
dsmIdx_f ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/DataStoreWrite"
, NULL ) ; ; _rtDW -> throttle_angle = B_14_10_0 ; ssWriteToDataStoreWithPath
( S , ( int ) _rtDW -> dsmIdx_m ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/DataStoreWrite3"
, NULL ) ; ; _rtDW -> throttle_flow = B_14_24_0 ; ssWriteToDataStoreWithPath
( S , ( int ) _rtDW -> dsmIdx_h ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/DataStoreWrite1"
, NULL ) ; ; ssWriteToDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx_ha ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/DataStoreWrite2"
, NULL ) ; ; if ( ssIsSampleHit ( S , 1 , 0 ) && ssIsMajorTimeStep ( S ) ) {
zcEvent = rt_ZCFcn ( RISING_ZERO_CROSSING , & _rtZCE ->
fuel_controller_pwon_Trig_ZCE , ( rtb_B_13_0_0 ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { _rtDW -> controller_mode = ( _rtP -> P_77 != 0.0F ) ;
ssWriteToDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx_l ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_pwon/DataStoreWrite1"
, NULL ) ; ; _rtDW -> commanded_fuel = _rtP -> P_78 ;
ssWriteToDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_pwon/DataStoreWrite"
, NULL ) ; ; _rtDW -> airbyfuel_ref = _rtP -> P_79 ;
ssWriteToDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx_e ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_pwon/DataStoreWrite2"
, NULL ) ; ; _rtDW -> fuel_controller_pwon_SubsysRanBC = 4 ; } zcEvent =
rt_ZCFcn ( RISING_ZERO_CROSSING , & _rtZCE ->
fuel_controller_mode_10ms_Trig_ZCE , ( _rtB -> B_13_1_0 ) ) ; if ( zcEvent !=
NO_ZCEVENT ) { ssReadFromDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx_ha ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_mode_10ms/DataStoreRead2"
, NULL ) ; ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_9_3_0 = ( ( _rtDW
-> airbyfuel_meas <= _rtB -> B_9_0_0 ) || _rtDW -> UnitDelay_DSTATE ) ; }
_rtB -> B_7_2_0 = _rtDW -> UnitDelay2_DSTATE + _rtP -> P_72 ; _rtB -> B_7_6_0
= ( ( _rtB -> B_7_2_0 >= _rtP -> P_73 ) || _rtDW -> UnitDelay1_DSTATE_e ) ;
rtb_B_10_3_0 = ! _rtB -> B_7_6_0 ; ssReadFromDataStoreWithPath ( S , ( int )
_rtDW -> dsmIdx_m ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_mode_10ms/DataStoreRead4"
, NULL ) ; ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if ( _rtDW ->
UnitDelay1_DSTATE_a ) { rtb_B_4_0_0 = _rtB -> B_8_0_0 ; } else { rtb_B_4_0_0
= _rtB -> B_8_3_0 ; } _rtB -> B_8_5_0 = ( _rtDW -> throttle_angle >=
rtb_B_4_0_0 ) ; } _rtDW -> controller_mode = ( _rtB -> B_9_3_0 ||
rtb_B_10_3_0 || _rtB -> B_8_5_0 ) ; ssWriteToDataStoreWithPath ( S , ( int )
_rtDW -> dsmIdx_l ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_mode_10ms/DataStoreWrite"
, NULL ) ; ; if ( _rtB -> B_7_6_0 && _rtB -> B_8_5_0 ) { _rtDW ->
airbyfuel_ref = _rtP -> P_70 ; } else { _rtDW -> airbyfuel_ref = _rtP -> P_69
; } ssWriteToDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx_e ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_mode_10ms/DataStoreWrite1"
, NULL ) ; ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW -> UnitDelay_DSTATE =
_rtB -> B_9_3_0 ; _rtDW -> UnitDelay1_DSTATE_a = _rtB -> B_8_5_0 ; } _rtDW ->
UnitDelay2_DSTATE = _rtB -> B_7_2_0 ; _rtDW -> UnitDelay1_DSTATE_e = _rtB ->
B_7_6_0 ; _rtDW -> fuel_controller_mode_10ms_SubsysRanBC = 4 ; } zcEvent =
rt_ZCFcn ( RISING_ZERO_CROSSING , & _rtZCE -> fuel_controller_10ms_Trig_ZCE ,
( _rtB -> B_13_1_0 ) ) ; if ( zcEvent != NO_ZCEVENT ) {
ssReadFromDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx_h ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreRead"
, NULL ) ; ; rtb_B_4_0_0 = _rtDW -> throttle_flow ;
ssReadFromDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx_f ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreRead1"
, NULL ) ; ; rtb_B_1_9_0 = ( ( _rtDW -> UnitDelay1_DSTATE_d * _rtDW ->
engine_speed * _rtP -> P_56 + _rtP -> P_55 ) + _rtDW -> UnitDelay1_DSTATE_d *
_rtDW -> UnitDelay1_DSTATE_d * _rtDW -> engine_speed * _rtP -> P_57 ) + _rtDW
-> engine_speed * _rtDW -> engine_speed * _rtDW -> UnitDelay1_DSTATE_d * _rtP
-> P_58 ; _rtB -> B_1_13_0 = ( rtb_B_4_0_0 - rtb_B_1_9_0 ) * _rtP -> P_60 *
_rtP -> P_54 + _rtDW -> UnitDelay1_DSTATE_d ; ssReadFromDataStoreWithPath ( S
, ( int ) _rtDW -> dsmIdx_e ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreRead4"
, NULL ) ; ; rtb_B_4_0_0 = _rtDW -> airbyfuel_ref ; rtb_B_1_9_0 /= _rtDW ->
airbyfuel_ref ; ssReadFromDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx_l ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreRead3"
, NULL ) ; ; rtb_B_10_3_0 = _rtDW -> controller_mode ;
ssReadFromDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx_ha ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreRead2"
, NULL ) ; ; _rtB -> B_4_10_0 = ! rtb_B_10_3_0 ; if ( _rtB -> B_4_10_0 ) {
rtb_B_4_0_0 = _rtDW -> airbyfuel_meas - rtb_B_4_0_0 ; _rtB -> B_2_6_0 = _rtP
-> P_63 * rtb_B_4_0_0 * _rtP -> P_61 + _rtDW -> UnitDelay1_DSTATE ; _rtB ->
B_2_7_0 = _rtP -> P_62 * rtb_B_4_0_0 + _rtB -> B_2_6_0 ; _rtDW ->
feedback_PI_controller_SubsysRanBC = 4 ; } if ( rtb_B_10_3_0 ) { rtb_B_4_0_0
= _rtB -> B_4_5_0 ; } else { rtb_B_4_0_0 = _rtB -> B_4_7_0 + _rtB -> B_2_7_0
; if ( rtb_B_4_0_0 > _rtP -> P_52 ) { rtb_B_4_0_0 = _rtP -> P_52 ; } else {
if ( rtb_B_4_0_0 < _rtP -> P_53 ) { rtb_B_4_0_0 = _rtP -> P_53 ; } } }
rtb_B_4_0_0 *= rtb_B_1_9_0 ; if ( rtb_B_4_0_0 > _rtP -> P_67 ) { _rtDW ->
commanded_fuel = _rtP -> P_67 ; } else if ( rtb_B_4_0_0 < _rtP -> P_68 ) {
_rtDW -> commanded_fuel = _rtP -> P_68 ; } else { _rtDW -> commanded_fuel =
rtb_B_4_0_0 ; } ssWriteToDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx ,
 "AbstractFuelControl_expanded_breach/AF_Controller/fuel_controller/fuel_controller_10ms/DataStoreWrite"
, NULL ) ; ; _rtDW -> UnitDelay1_DSTATE_d = _rtB -> B_1_13_0 ; if ( _rtB ->
B_4_10_0 ) { _rtDW -> UnitDelay1_DSTATE = _rtB -> B_2_6_0 ; } _rtDW ->
fuel_controller_10ms_SubsysRanBC = 4 ; } } if ( ssIsSampleHit ( S , 2 , 0 ) )
{ ssReadFromDataStoreWithPath ( S , ( int ) _rtDW -> dsmIdx ,
"AbstractFuelControl_expanded_breach/AF_Controller/DataStoreRead" , NULL ) ;
; rtb_B_13_3_0 = _rtDW -> commanded_fuel ; ssReadFromDataStoreWithPath ( S ,
( int ) _rtDW -> dsmIdx_l ,
"AbstractFuelControl_expanded_breach/AF_Controller/DataStoreRead1" , NULL ) ;
; B_13_4_0 = _rtDW -> controller_mode ; ssReadFromDataStoreWithPath ( S , (
int ) _rtDW -> dsmIdx_e ,
"AbstractFuelControl_expanded_breach/AF_Controller/DataStoreRead2" , NULL ) ;
; B_13_5_0 = _rtDW -> airbyfuel_ref ; _rtB -> B_14_31_0 = B_13_5_0 ;
ssCallAccelRunBlock ( S , 14 , 32 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_14_33_0
= B_13_4_0 ; ssCallAccelRunBlock ( S , 14 , 34 , SS_CALL_MDL_OUTPUTS ) ; } {
if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_rpmtorads_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_rpmtorads_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_4_0 ) ; } }
_rtB -> B_14_36_0 = _rtP -> P_28 * _rtB -> B_14_4_0 ; _rtB -> B_14_37_0 [ 0 ]
= _rtB -> B_14_12_0 ; _rtB -> B_14_37_0 [ 1 ] = _rtB -> B_14_4_0 ; B_14_38_0
= ( ( 0.08979 * _rtB -> B_14_37_0 [ 0 ] * _rtB -> B_14_37_0 [ 1 ] + - 0.366 )
- 0.0337 * _rtB -> B_14_37_0 [ 1 ] * _rtB -> B_14_37_0 [ 0 ] * _rtB ->
B_14_37_0 [ 0 ] ) + 0.0001 * _rtB -> B_14_37_0 [ 0 ] * _rtB -> B_14_37_0 [ 1
] * _rtB -> B_14_37_0 [ 1 ] ; _rtB -> B_14_39_0 = _rtP -> P_86 * B_14_38_0 ;
_rtB -> B_14_40_0 = _rtB -> B_14_39_0 / _rtB -> B_14_4_0 ; _rtB -> B_14_41_0
= _rtP -> P_29 * _rtB -> B_14_40_0 ; B_14_42_0 = look2_binlxpw ( _rtB ->
B_14_36_0 , _rtB -> B_14_41_0 , _rtP -> P_31 , _rtP -> P_32 , _rtP -> P_30 ,
_rtP -> P_87 , 5U ) ; { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal (
_rtDW -> HiddenToAsyncQueue_InsertedFor_1Kappa_at_outport_0_PWORK . AQHandles
, _rtDW -> HiddenToAsyncQueue_InsertedFor_1Kappa_at_outport_0_PWORK . SlioLTF
, 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & B_14_42_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_AFsensortolerance_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_AFsensortolerance_at_outport_0_PWORK . SlioLTF
, 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & B_14_28_0 ) ; } } if (
ssIsSampleHit ( S , 1 , 0 ) ) { { if ( ssGetLogOutput ( S ) ) {
sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_AFSensorFaultInjection_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_AFSensorFaultInjection_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_14_26_0 ) ; }
} } if ( ssIsSampleHit ( S , 2 , 0 ) ) { { if ( ssGetLogOutput ( S ) ) {
sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_AF_Controller_at_outport_1_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_AF_Controller_at_outport_1_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 2 ) , ( void * ) & B_13_4_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_AF_Controller_at_outport_2_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_AF_Controller_at_outport_2_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 2 ) , ( void * ) & B_13_5_0 ) ; } } } { if
( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_AF_sensor1_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_AF_sensor1_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_1_0 ) ; } }
_rtB -> B_14_49_0 = _rtP -> P_33 * B_14_42_0 ; _rtB -> B_14_50_0 = _rtP ->
P_34 * _rtB -> B_14_49_0 ; _rtB -> B_14_52_0 = _rtB -> B_14_50_0 + _rtB ->
B_14_51_0 ; { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Add2_at_outport_0_PWORK . AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_Add2_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_52_0 ) ; } } if (
ssIsSampleHit ( S , 2 , 0 ) ) { B_14_54_0 = rtb_B_13_3_0 ; _rtB -> B_14_55_0
= _rtP -> P_36 * B_14_54_0 ; } _rtB -> B_14_56_0 = _rtB -> B_14_49_0 * _rtB
-> B_14_55_0 ; _rtB -> B_14_57_0 = _rtX -> Integrator_CSTATE ; B_14_58_0 =
look2_binlxpw ( _rtB -> B_14_36_0 , _rtB -> B_14_41_0 , _rtP -> P_39 , _rtP
-> P_40 , _rtP -> P_38 , _rtP -> P_88 , 5U ) ; _rtB -> B_14_59_0 = _rtP ->
P_41 * B_14_58_0 ; _rtB -> B_14_60_0 = _rtB -> B_14_57_0 / _rtB -> B_14_59_0
; _rtB -> B_14_61_0 = _rtB -> B_14_56_0 + _rtB -> B_14_60_0 ; { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Add_at_outport_0_PWORK . AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_Add_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_61_0 ) ; } } if (
ssIsSampleHit ( S , 1 , 0 ) ) { { if ( ssGetLogOutput ( S ) ) {
sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_AtmosphericPressurebar_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_AtmosphericPressurebar_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_14_13_0 ) ; }
} { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Baseopeningangle_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_Baseopeningangle_at_outport_0_PWORK . SlioLTF
, 0 , ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_14_7_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Constant_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Constant_at_outport_0_PWORK . SlioLTF
, 0 , ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_14_51_0 ) ; } } } { if
( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_DataTypeConversion2_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_DataTypeConversion2_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & B_14_24_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_DataTypeConversion4_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_DataTypeConversion4_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & B_14_10_0 ) ; } } if (
ssIsSampleHit ( S , 2 , 0 ) ) { { if ( ssGetLogOutput ( S ) ) {
sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_DataTypeConversion5_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_DataTypeConversion5_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 2 ) , ( void * ) & _rtB -> B_14_31_0 ) ; }
} { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_DataTypeConversion6_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_DataTypeConversion6_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 2 ) , ( void * ) & _rtB -> B_14_33_0 ) ; }
} { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_DataTypeConversion_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_DataTypeConversion_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 2 ) , ( void * ) & B_14_54_0 ) ; } } } _rtB
-> B_14_71_0 = _rtB -> B_14_55_0 * _rtB -> B_14_52_0 ; { if ( ssGetLogOutput
( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Divide1_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_Divide1_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_71_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Divide2_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_Divide2_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_60_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Divide3_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_Divide3_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_56_0 ) ; } } _rtB ->
B_14_75_0 = _rtB -> B_14_39_0 / _rtB -> B_14_61_0 ; { if ( ssGetLogOutput ( S
) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Divide_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_Divide_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_75_0 ) ; } } if (
ssIsSampleHit ( S , 1 , 0 ) ) { { if ( ssGetLogOutput ( S ) ) {
sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_FaultySensorOutput_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_FaultySensorOutput_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_14_25_0 ) ; }
} } { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Gain1_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_Gain1_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_50_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Gain2_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_Gain2_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_39_0 ) ; } } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> fuelsystemtransportdelay_PWORK .
TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
fuelsystemtransportdelay_PWORK . TUbufferPtrs [ 1 ] ; real_T * * xBuffer = (
real_T * * ) & _rtDW -> fuelsystemtransportdelay_PWORK . TUbufferPtrs [ 2 ] ;
real_T simTime = ssGetT ( S ) ; real_T appliedDelay ; _rtB -> B_14_80_0 =
AbstractFuelControl_expanded_breach_acc_rt_VTDelayfindtDInterpolate ( ( (
X_AbstractFuelControl_expanded_breach_T * ) ssGetContStates ( S ) ) ->
fuelsystemtransportdelay_CSTATE , * tBuffer , * uBuffer , * xBuffer , _rtDW
-> fuelsystemtransportdelay_IWORK . CircularBufSize , _rtDW ->
fuelsystemtransportdelay_IWORK . Head , _rtDW ->
fuelsystemtransportdelay_IWORK . Tail , & _rtDW ->
fuelsystemtransportdelay_IWORK . Last , simTime , 0.0 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
, _rtP -> P_43 , & appliedDelay ) ; } _rtB -> B_14_81_0 = _rtX ->
Integrator1_CSTATE ; _rtB -> B_14_82_0 = _rtB -> B_14_80_0 - _rtB ->
B_14_81_0 ; _rtB -> B_14_83_0 = _rtP -> P_45 * _rtB -> B_14_82_0 ; { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Gain3_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_Gain3_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_83_0 ) ; } } _rtB ->
B_14_85_0 = _rtB -> B_14_81_0 - _rtB -> B_14_0_0 ; _rtB -> B_14_86_0 = _rtP
-> P_46 * _rtB -> B_14_85_0 ; { if ( ssGetLogOutput ( S ) ) {
sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Gain4_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_Gain4_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_86_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Gain_at_outport_0_PWORK . AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_Gain_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_41_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Integrator1_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Integrator1_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_81_0 ) ; }
} { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Integrator2_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Integrator2_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_0_0 ) ; } }
{ if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Integrator_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Integrator_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_57_0 ) ; }
} { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Kappatolerance_at_outport_0_PWORK . AQHandles
, _rtDW -> HiddenToAsyncQueue_InsertedFor_Kappatolerance_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_49_0 ) ; }
} { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_MinMax_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_MinMax_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_16_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Mux_at_outport_0_PWORK . AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_Mux_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_37_0 [ 0 ] ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Product1_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Product1_at_outport_0_PWORK . SlioLTF
, 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_40_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Product2_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Product2_at_outport_0_PWORK . SlioLTF
, 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_15_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Product3_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_Product3_at_outport_0_PWORK . SlioLTF
, 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_14_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Pumping_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_Pumping_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & B_14_38_0 ) ; } } _rtB -> B_14_99_0 =
_rtB -> B_14_22_0 - _rtB -> B_14_39_0 ; _rtB -> B_14_100_0 = _rtP -> P_47 *
_rtB -> B_14_99_0 ; { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal (
_rtDW -> HiddenToAsyncQueue_InsertedFor_RTVm_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_RTVm_at_outport_0_PWORK . SlioLTF , 0
, ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_100_0 ) ; } } if (
ssIsSampleHit ( S , 1 , 0 ) ) { { if ( ssGetLogOutput ( S ) ) {
sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_SonicFlow_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_SonicFlow_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_14_18_0 ) ; }
} } { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Sum1_at_outport_0_PWORK . AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_Sum1_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_99_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Sum2_at_outport_0_PWORK . AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_Sum2_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_20_0 ) ; } } _rtB ->
B_14_105_0 = _rtB -> B_14_71_0 - _rtB -> B_14_60_0 ; { if ( ssGetLogOutput (
S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Sum3_at_outport_0_PWORK . AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_Sum3_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_105_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Sum4_at_outport_0_PWORK . AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_Sum4_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_82_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Sum5_at_outport_0_PWORK . AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_Sum5_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_85_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_Switch1_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_Switch1_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_19_0 ) ; } } _rtB ->
B_14_110_0 = _rtP -> P_48 * _rtB -> B_14_4_0 ; _rtB -> B_14_111_0 =
look2_binlxpw ( _rtB -> B_14_110_0 , _rtB -> B_14_41_0 , _rtP -> P_50 , _rtP
-> P_51 , _rtP -> P_49 , _rtP -> P_89 , 5U ) ; { if ( ssGetLogOutput ( S ) )
{ sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_delays_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_delays_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_111_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_ftheta_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_ftheta_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & B_14_11_0 ) ; } } if ( ssIsSampleHit (
S , 1 , 0 ) ) { { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW
-> HiddenToAsyncQueue_InsertedFor_flowdirection_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_flowdirection_at_outport_0_PWORK . SlioLTF , 0
, ssGetTaskTime ( S , 1 ) , ( void * ) & _rtB -> B_14_21_0 ) ; } } } if (
ssIsSampleHit ( S , 2 , 0 ) ) { { if ( ssGetLogOutput ( S ) ) {
sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_fuelinjectortolerance_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_fuelinjectortolerance_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 2 ) , ( void * ) & _rtB -> B_14_55_0 ) ; }
} } { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_fuelsystemtransportdelay_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_fuelsystemtransportdelay_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_80_0 ) ; }
} { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_gpratio_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_gpratio_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_17_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_p00543bar_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_p00543bar_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_12_0 ) ; }
} { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_radstorpm_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_radstorpm_at_outport_0_PWORK .
SlioLTF , 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_110_0 ) ; }
} { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_speed_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_speed_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & ( (
ExternalUPtrs_AbstractFuelControl_expanded_breach_T * ) ssGetU ( S ) ) ->
speed ) ; } } { if ( ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW
-> HiddenToAsyncQueue_InsertedFor_tau_wwtolerance_at_outport_0_PWORK .
AQHandles , _rtDW ->
HiddenToAsyncQueue_InsertedFor_tau_wwtolerance_at_outport_0_PWORK . SlioLTF ,
0 , ssGetTaskTime ( S , 0 ) , ( void * ) & _rtB -> B_14_59_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_tau_ww_at_outport_0_PWORK . AQHandles , _rtDW
-> HiddenToAsyncQueue_InsertedFor_tau_ww_at_outport_0_PWORK . SlioLTF , 0 ,
ssGetTaskTime ( S , 0 ) , ( void * ) & B_14_58_0 ) ; } } { if (
ssGetLogOutput ( S ) ) { sdiSlioSdiWriteSignal ( _rtDW ->
HiddenToAsyncQueue_InsertedFor_throttle_at_outport_0_PWORK . AQHandles ,
_rtDW -> HiddenToAsyncQueue_InsertedFor_throttle_at_outport_0_PWORK . SlioLTF
, 0 , ssGetTaskTime ( S , 0 ) , ( void * ) & ( (
ExternalUPtrs_AbstractFuelControl_expanded_breach_T * ) ssGetU ( S ) ) ->
throttle ) ; } } UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID4 (
SimStruct * S , int_T tid ) { B_AbstractFuelControl_expanded_breach_T * _rtB
; P_AbstractFuelControl_expanded_breach_T * _rtP ; _rtP = ( (
P_AbstractFuelControl_expanded_breach_T * ) ssGetModelRtp ( S ) ) ; _rtB = (
( B_AbstractFuelControl_expanded_breach_T * ) _ssGetModelBlockIO ( S ) ) ;
_rtB -> B_14_7_0 = _rtP -> P_14 ; _rtB -> B_14_13_0 = _rtP -> P_18 ; _rtB ->
B_14_18_0 = _rtP -> P_19 ; _rtB -> B_14_25_0 = _rtP -> P_22 ; _rtB -> B_9_0_0
= _rtP -> P_76 ; _rtB -> B_8_0_0 = _rtP -> P_74 ; _rtB -> B_8_3_0 = _rtB ->
B_8_0_0 + _rtP -> P_75 ; _rtB -> B_4_5_0 = _rtP -> P_65 ; _rtB -> B_4_7_0 =
_rtP -> P_66 ; _rtB -> B_14_51_0 = _rtP -> P_35 ; UNUSED_PARAMETER ( tid ) ;
}
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) {
B_AbstractFuelControl_expanded_breach_T * _rtB ;
P_AbstractFuelControl_expanded_breach_T * _rtP ;
DW_AbstractFuelControl_expanded_breach_T * _rtDW ; _rtDW = ( (
DW_AbstractFuelControl_expanded_breach_T * ) ssGetRootDWork ( S ) ) ; _rtP =
( ( P_AbstractFuelControl_expanded_breach_T * ) ssGetModelRtp ( S ) ) ; _rtB
= ( ( B_AbstractFuelControl_expanded_breach_T * ) _ssGetModelBlockIO ( S ) )
; { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
fuelsystemtransportdelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & _rtDW -> fuelsystemtransportdelay_PWORK . TUbufferPtrs [ 1 ] ;
real_T * * xBuffer = ( real_T * * ) & _rtDW -> fuelsystemtransportdelay_PWORK
. TUbufferPtrs [ 2 ] ; real_T simTime = ssGetT ( S ) ; real_T appliedDelay ;
appliedDelay = _rtB -> B_14_111_0 ; if ( appliedDelay > _rtP -> P_42 ) {
appliedDelay = _rtP -> P_42 ; } _rtDW -> fuelsystemtransportdelay_IWORK .
Head = ( ( _rtDW -> fuelsystemtransportdelay_IWORK . Head < ( _rtDW ->
fuelsystemtransportdelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
fuelsystemtransportdelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW ->
fuelsystemtransportdelay_IWORK . Head == _rtDW ->
fuelsystemtransportdelay_IWORK . Tail ) { if ( !
AbstractFuelControl_expanded_breach_acc_rt_TDelayUpdateTailOrGrowBuf ( &
_rtDW -> fuelsystemtransportdelay_IWORK . CircularBufSize , & _rtDW ->
fuelsystemtransportdelay_IWORK . Tail , & _rtDW ->
fuelsystemtransportdelay_IWORK . Head , & _rtDW ->
fuelsystemtransportdelay_IWORK . Last , simTime - _rtP -> P_42 , tBuffer ,
uBuffer , xBuffer , ( boolean_T ) 0 , ( boolean_T ) 1 , & _rtDW ->
fuelsystemtransportdelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"vtdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
fuelsystemtransportdelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
fuelsystemtransportdelay_IWORK . Head ] = _rtB -> B_14_75_0 ; ( * xBuffer ) [
_rtDW -> fuelsystemtransportdelay_IWORK . Head ] = ( (
X_AbstractFuelControl_expanded_breach_T * ) ssGetContStates ( S ) ) ->
fuelsystemtransportdelay_CSTATE ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID4 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) {
B_AbstractFuelControl_expanded_breach_T * _rtB ;
P_AbstractFuelControl_expanded_breach_T * _rtP ;
X_AbstractFuelControl_expanded_breach_T * _rtX ;
XDot_AbstractFuelControl_expanded_breach_T * _rtXdot ;
DW_AbstractFuelControl_expanded_breach_T * _rtDW ; _rtDW = ( (
DW_AbstractFuelControl_expanded_breach_T * ) ssGetRootDWork ( S ) ) ; _rtXdot
= ( ( XDot_AbstractFuelControl_expanded_breach_T * ) ssGetdX ( S ) ) ; _rtX =
( ( X_AbstractFuelControl_expanded_breach_T * ) ssGetContStates ( S ) ) ;
_rtP = ( ( P_AbstractFuelControl_expanded_breach_T * ) ssGetModelRtp ( S ) )
; _rtB = ( ( B_AbstractFuelControl_expanded_breach_T * ) _ssGetModelBlockIO (
S ) ) ; _rtXdot -> Integrator2_CSTATE = _rtB -> B_14_86_0 ; _rtXdot ->
Throttledelay_CSTATE = 0.0 ; _rtXdot -> Throttledelay_CSTATE += _rtP -> P_12
* _rtX -> Throttledelay_CSTATE ; _rtXdot -> Throttledelay_CSTATE += ( (
ExternalUPtrs_AbstractFuelControl_expanded_breach_T * ) ssGetU ( S ) ) ->
throttle ; _rtXdot -> p00543bar_CSTATE = _rtB -> B_14_100_0 ; _rtXdot ->
Integrator_CSTATE = _rtB -> B_14_105_0 ; { real_T instantDelay ; instantDelay
= _rtB -> B_14_111_0 ; if ( instantDelay > _rtP -> P_42 ) { instantDelay =
_rtP -> P_42 ; } if ( instantDelay < 0.0 ) { ( (
XDot_AbstractFuelControl_expanded_breach_T * ) ssGetdX ( S ) ) ->
fuelsystemtransportdelay_CSTATE = 0 ; } else { ( (
XDot_AbstractFuelControl_expanded_breach_T * ) ssGetdX ( S ) ) ->
fuelsystemtransportdelay_CSTATE = 1.0 / instantDelay ; } } _rtXdot ->
Integrator1_CSTATE = _rtB -> B_14_83_0 ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) {
B_AbstractFuelControl_expanded_breach_T * _rtB ;
P_AbstractFuelControl_expanded_breach_T * _rtP ;
ZCV_AbstractFuelControl_expanded_breach_T * _rtZCSV ;
DW_AbstractFuelControl_expanded_breach_T * _rtDW ; _rtDW = ( (
DW_AbstractFuelControl_expanded_breach_T * ) ssGetRootDWork ( S ) ) ; _rtZCSV
= ( ( ZCV_AbstractFuelControl_expanded_breach_T * ) ssGetSolverZcSignalVector
( S ) ) ; _rtP = ( ( P_AbstractFuelControl_expanded_breach_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_AbstractFuelControl_expanded_breach_T *
) _ssGetModelBlockIO ( S ) ) ; _rtZCSV -> EngineSpeed9001100_UprLim_ZC = ( (
ExternalUPtrs_AbstractFuelControl_expanded_breach_T * ) ssGetU ( S ) ) ->
speed - _rtP -> P_9 ; _rtZCSV -> EngineSpeed9001100_LwrLim_ZC = ( (
ExternalUPtrs_AbstractFuelControl_expanded_breach_T * ) ssGetU ( S ) ) ->
speed - _rtP -> P_10 ; _rtZCSV -> theta090_UprLim_ZC = _rtB -> B_14_8_0 -
_rtP -> P_15 ; _rtZCSV -> theta090_LwrLim_ZC = _rtB -> B_14_8_0 - _rtP ->
P_16 ; if ( _rtB -> B_14_14_0 < _rtB -> B_14_15_0 ) { if ( _rtDW ->
MinMax_MODE == 0 ) { _rtZCSV -> MinMax_MinmaxInput_ZC = _rtB -> B_14_14_0 -
_rtB -> B_14_14_0 ; } else { _rtZCSV -> MinMax_MinmaxInput_ZC = _rtB ->
B_14_14_0 - _rtB -> B_14_15_0 ; } } else if ( _rtDW -> MinMax_MODE == 0 ) {
_rtZCSV -> MinMax_MinmaxInput_ZC = _rtB -> B_14_15_0 - _rtB -> B_14_14_0 ; }
else { _rtZCSV -> MinMax_MinmaxInput_ZC = _rtB -> B_14_15_0 - _rtB ->
B_14_15_0 ; } _rtZCSV -> Switch1_SwitchCond_ZC = _rtB -> B_14_16_0 - _rtP ->
P_20 ; _rtZCSV -> flowdirection_Input_ZC = _rtB -> B_14_20_0 ; _rtZCSV ->
AFSensorFaultInjection_StepTime_ZC = ssGetT ( S ) - _rtP -> P_23 ; _rtZCSV ->
Pwon_StepTime_ZC = ssGetT ( S ) - _rtP -> P_0 ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 142486136U
) ; ssSetChecksumVal ( S , 1 , 3453720492U ) ; ssSetChecksumVal ( S , 2 ,
2911587697U ) ; ssSetChecksumVal ( S , 3 , 3178585908U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "8.9" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_AbstractFuelControl_expanded_breach_T ) ) {
ssSetErrorStatus ( S , "Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_AbstractFuelControl_expanded_breach_T ) ) { ssSetErrorStatus
( S , "Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofU ( S ) != sizeof
( ExternalUPtrs_AbstractFuelControl_expanded_breach_T ) ) { static char msg [
256 ] ; sprintf ( msg , "Unexpected error: Internal ExternalInputs sizes do "
"not match for accelerator mex file." ) ; ssSetErrorStatus ( S , msg ) ; } if
( ssGetSizeofY ( S ) != sizeof ( ExtY_AbstractFuelControl_expanded_breach_T )
) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal ExternalOutputs sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_AbstractFuelControl_expanded_breach_T ) ) { static char msg [ 256 ] ;
sprintf ( msg , "Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & AbstractFuelControl_expanded_breach_rtDefaultP ) ; rt_InitInfAndNaN (
sizeof ( real_T ) ) ; ( ( P_AbstractFuelControl_expanded_breach_T * )
ssGetModelRtp ( S ) ) -> P_52 = rtInfF ; } static void
mdlInitializeSampleTimes ( SimStruct * S ) { slAccRegPrmChangeFcn ( S ,
mdlOutputsTID4 ) ; } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
