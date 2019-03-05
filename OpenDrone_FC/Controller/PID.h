/*
 * Copyright (c) OpenDrone, 2018.  All rights reserved.
 * The entire project (including this file) is licensed under the GNU GPL v3.0
 * Purpose: TODO
 *
 * 	@author Thomas Brych
 * 	@version 0.0.1 14.02.2019
 */
#include "Orientation.h"
#include "../Motor/PWMMotorTest.h"
#include "wiringPi.h"
#include "iostream"

#pragma once
class PID
{
public:
	~PID();
	static PID *getInstance(Orientation *o, PWMMotorTest *p);
	static PID *instance;

	void setP(float curP);
	void setI(float curI);
	void setD(float curD);
	void setThrottle(float curThrottle);
	void setPitchSetpoint(int curPitchSetpoint);
	void setRollSetpoint(int curRollSetpoint);
	void setYawSetpoint(int curYawSetpoint);
	void setRun(bool curRun);
	void armMotor();
	bool isInit();
	void interruptPid();

	Orientation *getOrientatin();

	void calcValues();

private:
	PID(Orientation *o, PWMMotorTest *p);
	PWMMotorTest *pwm = NULL;
	Orientation *orientation = NULL;

	float pid_p_gain_roll = 1.25;              //Gain setting for the roll P-controller 0.8
	float pid_i_gain_roll = 0.05;              //Gain setting for the roll I-controller 0.0175
	float pid_d_gain_roll = 10;                //Gain setting for the roll D-controller 10.0
	int pid_max_roll = 300;                    //Maximum output of the PID-controller (+/-)

	float pid_p_gain_pitch = pid_p_gain_roll;  //Gain setting for the pitch P-controller.
	float pid_i_gain_pitch = pid_i_gain_roll;  //Gain setting for the pitch I-controller.
	float pid_d_gain_pitch = pid_d_gain_roll;  //Gain setting for the pitch D-controller.
	int pid_max_pitch = pid_max_roll;          //Maximum output of the PID-controller (+/-)

	float pid_p_gain_yaw = 4.0;                //Gain setting for the pitch P-controller.
	float pid_i_gain_yaw = 0.02;               //Gain setting for the pitch I-controller.
	float pid_d_gain_yaw = 0.00;               //Gain setting for the pitch D-controller.
	int pid_max_yaw = 300;                     //Maximum output of the PID-controller (+/-)

	float pid_error_temp;
	float pid_i_mem_roll = 0, pid_roll_setpoint = 0, pid_output_roll, pid_last_roll_d_error = 0;
	float pid_i_mem_pitch = 0, pid_pitch_setpoint = 0, pid_output_pitch, pid_last_pitch_d_error = 0;
	float pid_i_mem_yaw = 0, pid_yaw_setpoint = 0, pid_output_yaw, pid_last_yaw_d_error = 0;

	int esc_1, esc_2, esc_3, esc_4;
	int throttle = 1050;
	bool run = false, stop = false;

	void calcPid();
};
