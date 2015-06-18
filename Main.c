#pragma config(Sensor, S1,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S2,     comp,           sensorI2CHiTechnicCompass)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * Code by Oscar and Jed
 * Robotics Team 2015
 */

#include "drivers/hitechnic-irseeker-v2.h"

//global variables
int fast = 50;
int slow = 10;
int lastdirection = 0;

//helper functions
int max(int x, int y)
{
	if (x > y) { return x; }
	else
	{ return y; }
}

int min(int x, int y)
{
	if (x < y) { return x; }
	else { return y; }
}


void turnLeft(int num_dist)
{
	motor[motorA] = fast;
	motor[motorC] =-slow;
	lastdirection = 1;
}

void turnRight(int num_dist)
{
	motor[motorA] =-slow;
	motor[motorC] = fast;
	lastdirection = 9;
}

void swivelLeft(int pwr)
{
	motor[motorA] = pwr;
	motor[motorC] = -pwr;
}

void swivelRight(int pwr)
{
	motor[motorA] = -pwr;
	motor[motorC] = pwr;
}

void forward(int pwr)
{
	motor[motorA] = pwr;
	motor[motorC] = pwr;
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
	int cur = (current - target) % 360;
	if(cur > 185)
	{
		cur = 360-cur;
		swivelRight(cur);
	}
	else if (cur > 5)
	{
		swivelLeft(cur);
	}
	else
	{
		forward(fast);
	}
}

//always put this task last
task main()
{
	bFloatDuringInactiveMotorPWM = true;
	kickoff();

	motor[motorA] = 0;
	motor[motorC] = 0;

	//set up sensor variables
	int _dirEnh, _strEnh;

	//we need our AC sensing to be at 1200Hz
  tHTIRS2DSPMode _mode = DSP_1200;

  //setup loop
  while (true)
	{
		// set the DSP to the new mode
		if (HTIRS2setDSPMode(HTIRS2, _mode))
		{
			break; // Sensor initialized
	}
		nxtDisplayCenteredTextLine(6, "Connect Sensor");
    nxtDisplayCenteredTextLine(7, "to Port S1!");
	} //setup

	//main loop
	while (true)
	{
		//int ir = SensorValue[S1];

		// Read the 'enhanced' direction and strength
		if (!HTIRS2readEnhanced(HTIRS2, _dirEnh, _strEnh))
		{
    	nxtDisplayCenteredTextLine(5, "I2C READ ERROR");
			wait1Msec(2500);
    	break; // I2C read error occurred
  	}

  	int comp = SensorValue[S2];
  	int dist = 310 - _strEnh;

    //print values to screen.
  	char str_dirEnh[15], str_strEnh[15], str_comp[15], str_dist[15];

    sprintf(str_dirEnh, "%d", _dirEnh);
		sprintf(str_strEnh, "%d", _strEnh);
		sprintf(str_comp, "%d", comp);
		sprintf(str_dist, "%d", dist);

    nxtDisplayCenteredTextLine(3, str_dirEnh);
    nxtDisplayCenteredTextLine(4, str_strEnh);
    nxtDisplayCenteredTextLine(5, str_comp);
    nxtDisplayCenteredTextLine(6, str_dist);

    int num_dist = abs(5 - _dirEnh);
    num_dist = (4 - num_dist) * 10;

		if(dist > 10)
			//right
			{
			if (_dirEnh > 5) {
				turnRight(num_dist);
			}
			//straight
			else if (_dirEnh == 5) {
				forward(fast);
			}
			//left
			else if (_dirEnh < 5) {
				turnLeft(num_dist);
			}
		}
		else
		{
    	turnToDirection(comp, 0);
  	}

		/*
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
		*/
	} //main while loop
}
