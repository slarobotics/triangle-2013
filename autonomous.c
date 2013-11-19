#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Motor,  mtr_Matrix_S1_1, motorA,        tmotorMatrix, openLoop, reversed)
#pragma config(Motor,  mtr_Matrix_S1_2, motorB,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_3, motorC,        tmotorMatrix, openLoop, reversed)
#pragma config(Motor,  mtr_Matrix_S1_4, motorD,        tmotorMatrix, openLoop)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoStandard)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)

#include "drivers/hitechnic-irseeker-v2.h"

void drive(int powerL, int powerR);
void dump();

task main()
{
	bool atIR = false;
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
			writeDebugStream("\ni is %d", i);
			writeDebugStream("\nac[i] - ac[i - 1] is %d", ac[i] - ac[i - 1]);
			if(ac[i] - ac[i - 1] > 110){ // this is just a guess, we need to test this
				if(i > 3) power = -30;
				if(i == 3){
					power = 0;
					atIR = true;
				}
				else power = 30;
			}
			drive(power, power);
		}
		drive(power, power);
		if(atIR) break;
	}
	dump();
}

void drive(int powerL, int powerR){
	motor[motorA] = -powerL;
	motor[motorC] = powerR;
}
void dump(){
	servo[servo2] = 100;
	wait1Msec(1000);
	servo[servo2] = 0;
}
