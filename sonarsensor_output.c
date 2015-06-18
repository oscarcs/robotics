#pragma config(Sensor, S2, sonarSensor, sensorSONAR)

task main()
{
	wait1Msec(50);
	while (true)	{
		nxtDisplayBigStringAt(2, 40, "%d", SensorValue[sonarSensor])
		wait1Msec(50);
	}
}
