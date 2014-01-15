#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     sensorDist,     sensorSONAR)
#pragma config(Motor,  mtr_Matrix_S1_1, motorE,        tmotorMatrix, openLoop, reversed)
#pragma config(Motor,  mtr_Matrix_S1_2, motorF,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_3, motorG,        tmotorMatrix, openLoop, reversed)
#pragma config(Motor,  mtr_Matrix_S1_4, motorH,        tmotorMatrix, openLoop)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoStandard)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)

void drive(int powerL, int powerR);
task main()
{
	waitForStart();
	drive(100, 100); //drive forward 3 seconds
	wait10Msec(300);

	drive(100, -100); //90 degree turn, tweak delay as necessary
	wait10Msec(100);

	drive(100, 100);
	wait10Msec(100);

	drive(100, -100); //90 degree turn, tweak delay as necessary
	wait10Msec(100);

	drive(100, 100);
	wait10Msec(100);
}

void drive(int powerL, int powerR){
	motor[motorE] = -powerL;
	motor[motorG] = powerR;
}
