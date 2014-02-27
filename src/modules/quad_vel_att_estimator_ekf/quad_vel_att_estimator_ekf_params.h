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
 * @file quad_vel_att_estimator_ekf_params.h
 *
 * Parameters for Velocity and Attitude EKF filter
 */

#include <systemlib/param/param.h>

struct quad_vel_att_estimator_ekf_params {
	float gyro_rp;
	float gyro_y;

	float v_xy;

	float gb_rp;
	float gb_y;

	float acc_xy;

	float k_1;
};

struct quad_vel_att_estimator_ekf_param_handles {
	param_t gyro_rp, gyro_y;
	param_t v_xy;
	param_t gb_rp, gb_y;
	param_t acc_xy;
	param_t k_1;
};

/**
 * Initialize all parameter handles and values
 *
 */
int parameters_init(struct quad_vel_att_estimator_ekf_param_handles *h);

/**
 * Update all parameters
 *
 */
int parameters_update(const struct quad_vel_att_estimator_ekf_param_handles *h, struct quad_vel_att_estimator_ekf_params *p);
