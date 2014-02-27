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
 * @file quad_vel_att_estimator_ekf_params.c
 *
 * Parameters for Velocity and Attitude EKF filter
 */

#include "quad_vel_att_estimator_ekf_params.h"


/* gyro process noise for roll and pitch */
PARAM_DEFINE_FLOAT(EKF_VEL_V1_GYRO_RP, 0.05f);
/* gyro process noise for yaw */
PARAM_DEFINE_FLOAT(EKF_VEL_V1_GYRO_Y, 0.001f);

/* velocity process noise for x and y */
PARAM_DEFINE_FLOAT(EKF_VEL_V1_V_XY, 0.1f);

/* gyro bias process noise for roll and pitch */
PARAM_DEFINE_FLOAT(EKF_VEL_V1_GB_RP, 0.0001f);
/* gyro bias process noise for yaw */
PARAM_DEFINE_FLOAT(EKF_VEL_V1_GB_Y, 0.0001f);

/* accelerometer measurement noise for x and y */
PARAM_DEFINE_FLOAT(EKF_VEL_V1_ACC_XY, 0.3f);

/* lumped drag coefficient */
PARAM_DEFINE_FLOAT(EKF_VEL_V1_K_1, -0.3f);


int parameters_init(struct quad_vel_att_estimator_ekf_param_handles *h)
{
	/* PID parameters */
	h->gyro_rp 	=	param_find("EKF_VEL_V1_GYRO_RP");
	h->gyro_y 	=	param_find("EKF_VEL_V1_GYRO_Y");

	h->v_xy 	=	param_find("EKF_VEL_V1_V_XY");

	h->gb_rp 	=	param_find("EKF_VEL_V1_GB_RP");
	h->gb_y 	=	param_find("EKF_VEL_V1_GB_Y");

	h->acc_xy 	=	param_find("EKF_VEL_V1_ACC_XY");

	h->k_1 		=	param_find("EKF_VEL_V1_K_1");

	return OK;
}

int parameters_update(const struct quad_vel_att_estimator_ekf_param_handles *h, struct quad_vel_att_estimator_ekf_params *p)
{
	param_get(h->gyro_rp, &(p->gyro_rp));
	param_get(h->gyro_y, &(p->gyro_y));

	param_get(h->v_xy, &(p->v_xy));

	param_get(h->gb_rp, &(p->gb_rp));
	param_get(h->gb_y, &(p->gb_y));

	param_get(h->acc_xy, &(p->acc_xy));
	param_get(h->k_1, &(p->k_1));


	return OK;
}
