    
    %movefile('BrFalse.csv','logs');
    %movefile('BrFalse_Robust_neg.csv','logs');
    %movefile('join.csv','logs');
    movefile(strcat(file,'.xml'),'models')
    movefile(strcat(newfile,'.xml'),'repair');
    movefile(strcat(newfile,'.slx'),'repair');
    movefile(strcat(newfile,'_params.mat'),'repair');
    movefile('mylog.out','logs');