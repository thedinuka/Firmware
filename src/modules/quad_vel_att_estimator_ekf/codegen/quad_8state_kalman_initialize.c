/*
 * quad_8state_kalman_initialize.c
 *
 * Code generation for function 'quad_8state_kalman_initialize'
 *
 * C source code generated on: Thu Feb 27 21:45:01 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "quad_8state_kalman.h"
#include "quad_8state_kalman_initialize.h"

/* Function Definitions */
void quad_8state_kalman_initialize(void)
{
  rt_InitInfAndNaN(8U);
  quad_8state_kalman_init();
}

/* End of code generation (quad_8state_kalman_initialize.c) */
