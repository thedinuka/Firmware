/*
 * quad_8state_kalman.h
 *
 * Code generation for function 'quad_8state_kalman'
 *
 * C source code generated on: Thu Mar  6 20:31:10 2014
 *
 */

#ifndef __QUAD_8STATE_KALMAN_H__
#define __QUAD_8STATE_KALMAN_H__
/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "rtwtypes.h"
#include "quad_8state_kalman_types.h"

/* Function Declarations */
extern void quad_8state_kalman(const float a[2], const float g[3], float delta_t, float gyro_rp, float gyro_y, float v_xy, float gb_rp, float gb_y, float acc_xy, float k_1, float y[8]);
extern void quad_8state_kalman_init(void);
#endif
/* End of code generation (quad_8state_kalman.h) */
