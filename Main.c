#pragma config(Sensor, S1, ir, sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S2, comp, sensorI2CHiTechnicCompass)

int fast = 50;
int slow = 10;
int lastdirection = 0;

int max(int x, int y)
{
	if (x > y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

void turnLeft()
{
	motor[motorA] = fast;
	motor[motorC] = -slow;
	lastdirection = 1;
}

void turnRight()
{
	motor[motorA] = -slow;
	motor[motorC] = fast;
	lastdirection = 9;
}

void forward()
{
	motor[motorA] = fast;
	motor[motorC] = fast;
}

void kickoff()
{
	motor[motorA] = fast;
	motor[motorC] = fast;
	wait1Msec(750);
	motor[motorA] = -fast;
	motor[motorC] = -fast;
	wait1Msec(500);
}

void turnToDirection(int current, int target)
{

}

//always put this task last
task main()
{
	kickoff();
	bFloatDuringInactiveMotorPWM = true;
	//for(int i = 0; i <= 5000; i++) {
	//main loop
	while (true) {
		int ir = SensorValue[S1];
		int comp = SensorValue[S2];

		char str_ir[15];
		char str_comp[15];

		//lmao c doesn't have type coercion, no wonder it's been improved upon
		//'print' the 'val' variable to the string (%d) 'str'.
		sprintf(str_ir, "%d", ir);
		sprintf(str_comp, "%d", comp);

		nxtDisplayCenteredTextLine(5, str_ir);
		nxtDisplayCenteredTextLine(6, str_comp);

		//when the sensor is confused
		if(ir == 0) {
			if (lastdirection == 9)
			{
				turnRight();
			}
			else if (lastdirection == 1)
			{
				turnLeft();
			}
			else
			{
				turnRight();
			}
		}
		//right
		else if (ir > 5) {
			turnRight();
		}
		//straight
		else if (ir == 5) {
			forward();
		}
		//left
		else if (ir < 5) {
			turnLeft();
		}
	}
}
