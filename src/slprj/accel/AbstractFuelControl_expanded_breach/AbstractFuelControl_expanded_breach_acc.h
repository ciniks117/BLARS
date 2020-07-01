#include "__cf_AbstractFuelControl_expanded_breach.h"
#ifndef RTW_HEADER_AbstractFuelControl_expanded_breach_acc_h_
#define RTW_HEADER_AbstractFuelControl_expanded_breach_acc_h_
#include <stddef.h>
#include <float.h>
#ifndef AbstractFuelControl_expanded_breach_acc_COMMON_INCLUDES_
#define AbstractFuelControl_expanded_breach_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "AbstractFuelControl_expanded_breach_acc_types.h"
#include "multiword_types.h"
#include "rt_zcfcn.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_14_0_0 ; real_T B_14_1_0 ; real_T B_14_3_0 ; real_T
B_14_4_0 ; real_T B_14_6_0 ; real_T B_14_7_0 ; real_T B_14_8_0 ; real_T
B_14_9_0 ; real_T B_14_12_0 ; real_T B_14_13_0 ; real_T B_14_14_0 ; real_T
B_14_15_0 ; real_T B_14_16_0 ; real_T B_14_17_0 ; real_T B_14_18_0 ; real_T
B_14_19_0 ; real_T B_14_20_0 ; real_T B_14_21_0 ; real_T B_14_22_0 ; real_T
B_14_25_0 ; real_T B_14_26_0 ; real_T B_14_31_0 ; real_T B_14_33_0 ; real_T
B_14_36_0 ; real_T B_14_37_0 [ 2 ] ; real_T B_14_39_0 ; real_T B_14_40_0 ;
real_T B_14_41_0 ; real_T B_14_49_0 ; real_T B_14_50_0 ; real_T B_14_51_0 ;
real_T B_14_52_0 ; real_T B_14_55_0 ; real_T B_14_56_0 ; real_T B_14_57_0 ;
real_T B_14_59_0 ; real_T B_14_60_0 ; real_T B_14_61_0 ; real_T B_14_71_0 ;
real_T B_14_75_0 ; real_T B_14_80_0 ; real_T B_14_81_0 ; real_T B_14_82_0 ;
real_T B_14_83_0 ; real_T B_14_85_0 ; real_T B_14_86_0 ; real_T B_14_99_0 ;
real_T B_14_100_0 ; real_T B_14_105_0 ; real_T B_14_110_0 ; real_T B_14_111_0
; real_T B_13_1_0 ; real32_T B_9_0_0 ; real32_T B_8_0_0 ; real32_T B_8_3_0 ;
real32_T B_7_2_0 ; real32_T B_4_5_0 ; real32_T B_4_7_0 ; real32_T B_2_6_0 ;
real32_T B_2_7_0 ; real32_T B_1_13_0 ; boolean_T B_9_3_0 ; boolean_T B_8_5_0
; boolean_T B_7_6_0 ; boolean_T B_4_10_0 ; }
B_AbstractFuelControl_expanded_breach_T ; typedef struct { real_T nextTime ;
int64_T numCompleteCycles ; struct { real_T modelTStart ; }
fuelsystemtransportdelay_RWORK ; struct { void * AQHandles ; void * SlioLTF ;
} HiddenToAsyncQueue_InsertedFor_rpmtorads_at_outport_0_PWORK ; struct { void
* AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_1Kappa_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_AFsensortolerance_at_outport_0_PWORK ; struct
{ void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_AFSensorFaultInjection_at_outport_0_PWORK ;
struct { void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_AF_Controller_at_outport_1_PWORK ; struct {
void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_AF_Controller_at_outport_2_PWORK ; struct {
void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_AF_sensor1_at_outport_0_PWORK ; struct { void
* AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Add2_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Add_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_AtmosphericPressurebar_at_outport_0_PWORK ;
struct { void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Baseopeningangle_at_outport_0_PWORK ; struct {
void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Constant_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_DataTypeConversion2_at_outport_0_PWORK ;
struct { void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_DataTypeConversion4_at_outport_0_PWORK ;
struct { void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_DataTypeConversion5_at_outport_0_PWORK ;
struct { void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_DataTypeConversion6_at_outport_0_PWORK ;
struct { void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_DataTypeConversion_at_outport_0_PWORK ; struct
{ void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Divide1_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Divide2_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Divide3_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Divide_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_FaultySensorOutput_at_outport_0_PWORK ; struct
{ void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Gain1_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Gain2_at_outport_0_PWORK ; struct { void *
TUbufferPtrs [ 3 ] ; } fuelsystemtransportdelay_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Gain3_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Gain4_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Gain_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Integrator1_at_outport_0_PWORK ; struct { void
* AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Integrator2_at_outport_0_PWORK ; struct { void
* AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Integrator_at_outport_0_PWORK ; struct { void
* AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Kappatolerance_at_outport_0_PWORK ; struct {
void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_MinMax_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Mux_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Product1_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Product2_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Product3_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Pumping_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_RTVm_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_SonicFlow_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Sum1_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Sum2_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Sum3_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Sum4_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Sum5_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_Switch1_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_delays_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_ftheta_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_flowdirection_at_outport_0_PWORK ; struct {
void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_fuelinjectortolerance_at_outport_0_PWORK ;
struct { void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_fuelsystemtransportdelay_at_outport_0_PWORK ;
struct { void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_gpratio_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_p00543bar_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_radstorpm_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_speed_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_tau_wwtolerance_at_outport_0_PWORK ; struct {
void * AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_tau_ww_at_outport_0_PWORK ; struct { void *
AQHandles ; void * SlioLTF ; }
HiddenToAsyncQueue_InsertedFor_throttle_at_outport_0_PWORK ; void *
commanded_fuel_PWORK ; void * mode_fb_PWORK ; void * mode_fb1_PWORK ; void *
DataStoreMemory_PWORK ; void * DataStoreMemory1_PWORK ; void *
DataStoreMemory2_PWORK ; void * DataStoreMemory3_PWORK ; real32_T
UnitDelay2_DSTATE ; real32_T UnitDelay1_DSTATE ; real32_T UnitDelay1_DSTATE_d
; real32_T commanded_fuel ; real32_T airbyfuel_ref ; real32_T engine_speed ;
real32_T throttle_flow ; real32_T airbyfuel_meas ; real32_T throttle_angle ;
int32_T justEnabled ; int32_T currentValue ; int32_T dsmIdx ; int32_T
dsmIdx_l ; int32_T dsmIdx_e ; int32_T dsmIdx_f ; int32_T dsmIdx_h ; int32_T
dsmIdx_ha ; int32_T dsmIdx_m ; struct { int_T Tail ; int_T Head ; int_T Last
; int_T CircularBufSize ; int_T MaxNewBufSize ; }
fuelsystemtransportdelay_IWORK ; int_T EngineSpeed9001100_MODE ; int_T
theta090_MODE ; int_T MinMax_MODE ; int_T flowdirection_MODE ; int_T
AFSensorFaultInjection_MODE ; int_T Pwon_MODE ; boolean_T UnitDelay_DSTATE ;
boolean_T UnitDelay1_DSTATE_a ; boolean_T UnitDelay1_DSTATE_e ; int8_T
fuel_controller_pwon_SubsysRanBC ; int8_T
fuel_controller_mode_10ms_SubsysRanBC ; int8_T
fuel_controller_10ms_SubsysRanBC ; int8_T feedback_PI_controller_SubsysRanBC
; boolean_T Switch1_Mode ; boolean_T controller_mode ; char_T
pad_controller_mode [ 3 ] ; } DW_AbstractFuelControl_expanded_breach_T ;
typedef struct { real_T Integrator2_CSTATE ; real_T Throttledelay_CSTATE ;
real_T p00543bar_CSTATE ; real_T Integrator_CSTATE ; real_T
fuelsystemtransportdelay_CSTATE ; real_T Integrator1_CSTATE ; }
X_AbstractFuelControl_expanded_breach_T ; typedef struct { real_T
Integrator2_CSTATE ; real_T Throttledelay_CSTATE ; real_T p00543bar_CSTATE ;
real_T Integrator_CSTATE ; real_T fuelsystemtransportdelay_CSTATE ; real_T
Integrator1_CSTATE ; } XDot_AbstractFuelControl_expanded_breach_T ; typedef
struct { boolean_T Integrator2_CSTATE ; boolean_T Throttledelay_CSTATE ;
boolean_T p00543bar_CSTATE ; boolean_T Integrator_CSTATE ; boolean_T
fuelsystemtransportdelay_CSTATE ; boolean_T Integrator1_CSTATE ; }
XDis_AbstractFuelControl_expanded_breach_T ; typedef struct { real_T
Integrator2_CSTATE ; real_T Throttledelay_CSTATE ; real_T p00543bar_CSTATE ;
real_T Integrator_CSTATE ; real_T fuelsystemtransportdelay_CSTATE ; real_T
Integrator1_CSTATE ; } CStateAbsTol_AbstractFuelControl_expanded_breach_T ;
typedef struct { real_T EngineSpeed9001100_UprLim_ZC ; real_T
EngineSpeed9001100_LwrLim_ZC ; real_T theta090_UprLim_ZC ; real_T
theta090_LwrLim_ZC ; real_T MinMax_MinmaxInput_ZC ; real_T
Switch1_SwitchCond_ZC ; real_T flowdirection_Input_ZC ; real_T
AFSensorFaultInjection_StepTime_ZC ; real_T Pwon_StepTime_ZC ; real_T
fuel_controller_pwon_Trig_ZC ; real_T fuel_controller_mode_10ms_Trig_ZC ;
real_T fuel_controller_10ms_Trig_ZC ; }
ZCV_AbstractFuelControl_expanded_breach_T ; typedef struct { ZCSigState
EngineSpeed9001100_UprLim_ZCE ; ZCSigState EngineSpeed9001100_LwrLim_ZCE ;
ZCSigState theta090_UprLim_ZCE ; ZCSigState theta090_LwrLim_ZCE ; ZCSigState
MinMax_MinmaxInput_ZCE ; ZCSigState Switch1_SwitchCond_ZCE ; ZCSigState
flowdirection_Input_ZCE ; ZCSigState AFSensorFaultInjection_StepTime_ZCE ;
ZCSigState Pwon_StepTime_ZCE ; ZCSigState fuel_controller_pwon_Trig_ZCE ;
ZCSigState fuel_controller_mode_10ms_Trig_ZCE ; ZCSigState
fuel_controller_10ms_Trig_ZCE ; }
PrevZCX_AbstractFuelControl_expanded_breach_T ; typedef struct { real_T
throttle ; real_T speed ; }
ExternalUPtrs_AbstractFuelControl_expanded_breach_T ; typedef struct { real_T
* B_14_0 ; real_T * B_14_2 ; real_T * B_14_3 ; }
ExtY_AbstractFuelControl_expanded_breach_T ; struct
P_AbstractFuelControl_expanded_breach_T_ { real_T P_0 ; real_T P_1 ; real_T
P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T
P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ;
real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T
P_19 ; real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ;
real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T
P_30 [ 20 ] ; real_T P_31 [ 5 ] ; real_T P_32 [ 4 ] ; real_T P_33 ; real_T
P_34 ; real_T P_35 ; real_T P_36 ; real_T P_37 ; real_T P_38 [ 20 ] ; real_T
P_39 [ 5 ] ; real_T P_40 [ 4 ] ; real_T P_41 ; real_T P_42 ; real_T P_43 ;
real_T P_44 ; real_T P_45 ; real_T P_46 ; real_T P_47 ; real_T P_48 ; real_T
P_49 [ 20 ] ; real_T P_50 [ 5 ] ; real_T P_51 [ 4 ] ; real32_T P_52 ;
real32_T P_53 ; real32_T P_54 ; real32_T P_55 ; real32_T P_56 ; real32_T P_57
; real32_T P_58 ; real32_T P_59 ; real32_T P_60 ; real32_T P_61 ; real32_T
P_62 ; real32_T P_63 ; real32_T P_64 ; real32_T P_65 ; real32_T P_66 ;
real32_T P_67 ; real32_T P_68 ; real32_T P_69 ; real32_T P_70 ; real32_T P_71
; real32_T P_72 ; real32_T P_73 ; real32_T P_74 ; real32_T P_75 ; real32_T
P_76 ; real32_T P_77 ; real32_T P_78 ; real32_T P_79 ; real32_T P_80 ;
real32_T P_81 ; real32_T P_82 ; real32_T P_83 ; real32_T P_84 ; real32_T P_85
; real32_T P_86 ; uint32_T P_87 [ 2 ] ; uint32_T P_88 [ 2 ] ; uint32_T P_89 [
2 ] ; boolean_T P_90 ; boolean_T P_91 ; boolean_T P_92 ; boolean_T P_93 ; } ;
extern P_AbstractFuelControl_expanded_breach_T
AbstractFuelControl_expanded_breach_rtDefaultP ;
#endif
