#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Motor,  mtr_Matrix_S1_1, motorD,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_2, motorE,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_3, motorF,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_4,  motorG,             tmotorMatrix, openLoop)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)

#include "drivers/hitechnic-irseeker-v2.h"

void drive(int powerL, int powerR);

task main()
{
	tHTIRS2DSPMode _mode = DSP_1200;
	if (HTIRS2setDSPMode(HTIRS2, _mode) == 0){
		eraseDisplay();
		nxtDisplayCenteredTextLine(0, "ERROR!");
		nxtDisplayCenteredTextLine(2, "Init failed!");
		nxtDisplayCenteredTextLine(3, "Connect sensor");
		nxtDisplayCenteredTextLine(4, "to Port 2.");
		// make a noise to get their attention.
		PlaySound(soundBeepBeep);
	}
	int power = 75;
	int ac[] = {0, 0, 0, 0, 0};
	drive(power, power);
	while(1){
		HTIRS2readAllACStrength(HTIRS2, ac[0], ac[1], ac[2], ac[3], ac[4]);
		for(int i = 1; i < 5; i++){ // try to catch the peak going through the sectors
			if(ac[i] - ac[i - 1] > 100){ // this is just a guess, we need to test this
				if(i > 3) power = -30;
				if(i == 3) power = 0;
				else power = 30;
			}
			drive(power, power);
		}
		drive(power, power);
	}
}

void drive(int powerL, int powerR){
	motor[motorD] = powerL;
	motor[motorE] = powerR;
}
