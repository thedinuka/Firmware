/****************************************************************************
 *
 *   Copyright (C) 2012 PX4 Development Team. All rights reserved.
 *   Author: Dinuka Abeywardena <thedinuka@gmail.com>
 *     
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/*
 * @file quad_vel_att_estimator_ekf_main.c
 *
 * Extended Kalman Filter for Velocity and Attitude Estimation.
 */

#include <nuttx/config.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <poll.h>
#include <fcntl.h>
#include <float.h>
#include <nuttx/sched.h>
#include <sys/prctl.h>
#include <termios.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <uORB/uORB.h>
#include <uORB/topics/debug_key_value.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/vehicle_control_mode.h>
#include <uORB/topics/parameter_update.h>
#include <drivers/drv_hrt.h>

#include <systemlib/systemlib.h>
#include <systemlib/perf_counter.h>
#include <systemlib/err.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "codegen/quad_8state_kalman_initialize.h" 
#include "codegen/quad_8state_kalman.h"
#include "quad_vel_att_estimator_ekf_params.h"	
#ifdef __cplusplus
}
#endif

extern "C" __EXPORT int quad_vel_att_estimator_ekf_main(int argc, char *argv[]);

static bool thread_should_exit = false;		/**< Deamon exit flag */
static bool thread_running = false;		/**< Deamon status flag */
static int vel_att_estimator_ekf_task;				/**< Handle of deamon task / thread */

/**
 * Mainloop of quad_vel_att_estimator_ekf.
 */
int quad_vel_att_estimator_ekf_thread_main(int argc, char *argv[]);

/**
 * Print the correct usage.
 */
static void usage(const char *reason);

static void
usage(const char *reason)
{
	if (reason)
		fprintf(stderr, "%s\n", reason);

	fprintf(stderr, "quad_vel_att_estimator_ekf {start|stop|status} [-p <additional params>]\n\n");
	exit(1);
}

/**
 * The attitude_estimator_ekf app only briefly exists to start
 * the background job. The stack size assigned in the
 * Makefile does only apply to this management task.
 *
 * The actual stack size should be set in the call
 * to task_create().
 */
int quad_vel_att_estimator_ekf_main(int argc, char *argv[])
{
	if (argc < 1)
		usage("missing command");

	if (!strcmp(argv[1], "start")) {

		if (thread_running) {
			printf("quad_vel_att_estimator_ekf already running\n");
			/* this is not an error */
			exit(0);
		}

		thread_should_exit = false;
		vel_att_estimator_ekf_task = task_spawn_cmd("quad_vel_att_estimator_ekf",
					      SCHED_DEFAULT,
					      SCHED_PRIORITY_MAX - 5,
					      14000,
					      quad_vel_att_estimator_ekf_thread_main,
					      (argv) ? (const char **)&argv[2] : (const char **)NULL);
		exit(0);
	}

	if (!strcmp(argv[1], "stop")) {
		thread_should_exit = true;
		exit(0);
	}

	if (!strcmp(argv[1], "status")) {
		if (thread_running) {
			warnx("running");
			exit(0);

		} else {
			warnx("not started");
			exit(1);
		}

		exit(0);
	}

	usage("unrecognized command");
	exit(1);
}

/*
 * EKF Attitude and Velocity Estimator main function.
 *
 * Estimates the attitude and velocity recursively once started.
 *
 * @param argc number of commandline arguments (plus command name)
 * @param argv strings containing the arguments
 */
int quad_vel_att_estimator_ekf_thread_main(int argc, char *argv[])
{

	const unsigned int loop_interval_alarm = 6500;	// loop interval in microseconds

	float dt;
	/* state vector x has the following entries [phi, theta, psi, vx, vy, bgx, bgy, bgz]' */
	//float x_aposteriori_k[8] = {0, 0, 0, 0, 0, 0, 0, 0};		/** initialization done in the kalman filter c file for now */

	//measurements are x and y accelerometers [ax , ay]'
	float a_k[2]; /**< accelerometer measurement , only ax and ay are used*/
	float g_k[3]; //gyro measurement

	/* initialization is done in the kalman filter c file for now	
	float P_aposteriori_k[64] = {0.1f, 0,   0,   0,   0,   0,   0,   0,
				     0, 0.1f,   0,   0,   0,   0,   0,   0,
				     0,   0, 0.1f,   0,   0,   0,   0,   0,
				     0,   0,   0, 0.1f,   0,   0,   0,   0,
				     0,   0,   0,   0,  0.1f,  0,   0,   0,
				     0,   0,   0,   0,   0, 0.1f,   0,   0,
				     0,   0,   0,   0,   0,   0, 0.1f,   0,
				     0,   0,   0,   0,   0,   0,   0, 0.1f,
				    }; /**< init: diagonal matrix with big values */

	float x_aposteriori[8];
	float P_aposteriori[64];

	// print text
	printf("Extended Kalman Filter Attitude and Velocity Estimator initialized..\n\n");
	fflush(stdout);

	//int overloadcounter = 19;

	/* Initialize filter */
	quad_8state_kalman_initialize();

	struct sensor_combined_s raw;
	memset(&raw, 0, sizeof(raw));
	struct vehicle_attitude_s att;
	memset(&att, 0, sizeof(att));
	struct vehicle_control_mode_s control_mode;
	memset(&control_mode, 0, sizeof(control_mode));

	uint64_t last_data = 0;
	uint64_t last_measurement = 0;

	/* subscribe to raw data */
	int sub_raw = orb_subscribe(ORB_ID(sensor_combined));
	/* rate-limit raw data updates to 333 Hz (sensors app publishes at 200, so this is just paranoid) */
	orb_set_interval(sub_raw, 3);

	/* subscribe to param changes */
	int sub_params = orb_subscribe(ORB_ID(parameter_update));

	/* subscribe to control mode*/
	int sub_control_mode = orb_subscribe(ORB_ID(vehicle_control_mode));

	/* advertise attitude */
	orb_advert_t pub_att = orb_advertise(ORB_ID(vehicle_attitude), &att);

	int loopcounter = 0;
	int printcounter = 0;

	thread_running = true;

	float sensor_update_hz[3] = {0.0f, 0.0f, 0.0f};

	/* keep track of sensor updates */
	uint32_t sensor_last_count[3] = {0, 0, 0};
	uint64_t sensor_last_timestamp[3] = {0, 0, 0};


	struct quad_vel_att_estimator_ekf_params 		 ekf_params;
	struct quad_vel_att_estimator_ekf_param_handles 	 ekf_param_handles;
	/* initialize parameter handles */
	parameters_init(&ekf_param_handles);


	uint64_t start_time = hrt_absolute_time();
	bool initialized = false;
	bool dt_initialized = false;		//used to properly initialize dt

	float acc_offsets[3] = { 0.0f, 0.0f, 0.0f };	//to calculate the accelerometer bias before start
	unsigned offset_count = 0;

	/*struct pollfd fds[] = {{ .fd = sub_raw, .events = POLLIN },
				{ .fd = sub_params, .events = POLLIN }};*/
	struct pollfd fds[2];
	fds[0].fd = sub_raw;
	fds[0].events = POLLIN;
	fds[1].fd = sub_params;
	fds[1].events = POLLIN;

	/* Main loop*/
	while (!thread_should_exit) {

		int ret = poll(fds, 2, 1000);

		if (ret < 0) {
			/* XXX this is seriously bad - should be an emergency */
		} else if (ret == 0) {
			/* check if we're in HIL - not getting sensor data is fine then */
			orb_copy(ORB_ID(vehicle_control_mode), sub_control_mode, &control_mode);

			if (!control_mode.flag_system_hil_enabled) {
				fprintf(stderr,
					"[att ekf] WARNING: Not getting sensors - sensor app running?\n");
			}

		} else {

			/* only update parameters if they changed */
			if (fds[1].revents & POLLIN) {
				/* read from param to clear updated flag */
				struct parameter_update_s update;
				orb_copy(ORB_ID(parameter_update), sub_params, &update);

				/* update parameters */ 
				//TODO change to correct param update function names
				parameters_update(&ekf_param_handles, &ekf_params);
			}

			/* only run filter if sensor values changed */
			if (fds[0].revents & POLLIN) {

				/* get latest measurements */
				orb_copy(ORB_ID(sensor_combined), sub_raw, &raw);

				if (!initialized) {
					// TODO calculate accelerometer bias
					initialized = true;

				} else {
					/* Calculate data time difference in seconds */
					dt = (raw.timestamp - last_measurement) / 1000000.0f;
					last_measurement = raw.timestamp;
					uint8_t update_vect[3] = {0, 0, 0};

					/* Fill in gyro measurements */
					if (sensor_last_count[0] != raw.gyro_counter) {
						update_vect[0] = 1;
						sensor_last_count[0] = raw.gyro_counter;
						sensor_update_hz[0] = 1e6f / (raw.timestamp - sensor_last_timestamp[0]);
						sensor_last_timestamp[0] = raw.timestamp;
					}

					g_k[0] =  raw.gyro_rad_s[0];
					g_k[1] =  raw.gyro_rad_s[1];
					g_k[2] =  raw.gyro_rad_s[2];

					/* update accelerometer measurements */
					if (sensor_last_count[1] != raw.accelerometer_counter) {
						update_vect[1] = 1;
						sensor_last_count[1] = raw.accelerometer_counter;
						sensor_update_hz[1] = 1e6f / (raw.timestamp - sensor_last_timestamp[1]);
						sensor_last_timestamp[1] = raw.timestamp;
					}

					a_k[0] = raw.accelerometer_m_s2[0];
					a_k[1] = raw.accelerometer_m_s2[1];
					//a_k[2] = raw.accelerometer_m_s2[2];


					/* skip the first run because dt might not be accurate */
					if (!dt_initialized)  {
						dt_initialized = true;
						continue;
					}

					//call the kalman filter with measurements, inputs, delta_t and parameter k_1
					//TODO pass the process noise and measurement noise parameters to the filter

					quad_8state_kalman(a_k, g_k, dt, ekf_params.gyro_rp, ekf_params.gyro_y, ekf_params.v_xy, ekf_params.gb_rp, ekf_params.gb_y, ekf_params.acc_xy, ekf_params.k_1, x_aposteriori);

					/* only publish if Euler angles and velocities are finite */
					if (isfinite(x_aposteriori[0]) && isfinite(x_aposteriori[1]) && isfinite(x_aposteriori[2]) && isfinite(x_aposteriori[3]) && isfinite(x_aposteriori[4])) 
					{
					last_data = raw.timestamp;

					/* send out */
					att.timestamp = raw.timestamp;

					att.roll = x_aposteriori[0];
					att.pitch = x_aposteriori[1];
					att.yaw = x_aposteriori[2];
					
					//rotational rates are gyro measurements minus the bias
					att.rollspeed =  g_k[0] - x_aposteriori[5];
					att.pitchspeed = g_k[1] - x_aposteriori[6];
					att.yawspeed =   g_k[2] - x_aposteriori[7];
				
					//not calculating the body angular acc for now
					att.rollacc =  0;
					att.pitchacc = 0;
					att.yawacc =   0;

					/* copy gyro biases */
					memcpy(&att.rate_offsets, &(x_aposteriori[5]), sizeof(att.rate_offsets));

					//not calculating the R for  now
					att.R_valid = false;
					att.q_valid = false;
					orb_publish(ORB_ID(vehicle_attitude), pub_att, &att);


					} else {
						/* due to inputs or numerical failure the output is invalid, skip it */
						warnx("NaN in roll/pitch/yaw estimate!");
						continue;
					}

					if (last_data > 0 && raw.timestamp - last_data > 12000)
						printf("[velocity and attitude estimator ekf] sensor data missed! (%llu)\n", raw.timestamp - last_data);

				}
			}
		}

		loopcounter++;
	}

	thread_running = false;

	return 0;
}
