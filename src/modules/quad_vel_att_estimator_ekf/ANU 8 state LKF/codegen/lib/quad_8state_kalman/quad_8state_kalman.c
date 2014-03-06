/*
 * quad_8state_kalman.c
 *
 * Code generation for function 'quad_8state_kalman'
 *
 * C source code generated on: Thu Mar  6 20:31:10 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "quad_8state_kalman.h"

/* Variable Definitions */
static float p_est[64];
static float x_est[8];

/* Function Definitions */
void quad_8state_kalman(const float a[2], const float g[3], float delta_t, float
  gyro_rp, float gyro_y, float v_xy, float gb_rp, float gb_y, float acc_xy,
  float k_1, float y[8])
{
  float A[64];
  signed char I[64];
  int i;
  signed char G[24];
  float H[16];
  float v[8];
  float d[64];
  float b_v[2];
  float R[4];
  float b_A[24];
  int r1;
  int r2;
  float c_A[24];
  float b_g[3];
  float d_A[8];
  float e_A[64];
  float x_prd[8];
  float p_prd[64];
  float a21;
  float klm_gain[16];
  float S[4];
  float inv[16];
  float a22;
  float Y[16];
  float b_a[2];
  float c_a[2];

  /* states {phi, theta, psi, vx vy, beta_gx, beta_gy, beta_gz} */
  /* continuous state transition matrix */
  for (i = 0; i < 64; i++) {
    A[i] = 0.0F;

    /* discretize state transition matrix */
    I[i] = 0;
  }

  A[40] = -1.0F;
  A[49] = -1.0F;
  A[58] = -1.0F;
  A[11] = -9.81F;
  A[27] = k_1;
  A[4] = 9.8F;
  A[36] = k_1;
  for (i = 0; i < 8; i++) {
    I[i + (i << 3)] = 1;
  }

  for (i = 0; i < 64; i++) {
    A[i] = (float)I[i] + A[i] * delta_t;
  }

  /* continuous control matrix */
  for (i = 0; i < 24; i++) {
    G[i] = 0;
  }

  G[0] = 1;
  G[9] = 1;
  G[18] = 1;

  /* measurement matrix */
  memset(&H[0], 0, sizeof(float) << 4);
  H[6] = k_1;
  H[9] = k_1;

  /* process noise matrix */
  v[0] = gyro_rp;
  v[1] = gyro_rp;
  v[2] = gyro_y;
  v[3] = v_xy;
  v[4] = v_xy;
  v[5] = gb_rp;
  v[6] = gb_rp;
  v[7] = gb_y;
  memset(&d[0], 0, sizeof(float) << 6);
  for (i = 0; i < 8; i++) {
    d[i + (i << 3)] = v[i];
  }

  /* measurement noise matrix */
  b_v[0] = acc_xy;
  b_v[1] = acc_xy;
  for (i = 0; i < 4; i++) {
    R[i] = 0.0F;
  }

  for (i = 0; i < 2; i++) {
    R[i + (i << 1)] = b_v[i];
  }

  /* initialization */
  /*  Predicted state and covariance */
  for (i = 0; i < 8; i++) {
    for (r1 = 0; r1 < 3; r1++) {
      b_A[i + (r1 << 3)] = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        b_A[i + (r1 << 3)] += A[i + (r2 << 3)] * (float)G[r2 + (r1 << 3)];
      }
    }
  }

  for (i = 0; i < 3; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      c_A[r1 + (i << 3)] = b_A[r1 + (i << 3)] * delta_t;
    }
  }

  b_g[0] = g[0];
  b_g[1] = g[1];
  b_g[2] = g[2];
  for (i = 0; i < 8; i++) {
    v[i] = 0.0F;
    for (r1 = 0; r1 < 8; r1++) {
      v[i] += A[i + (r1 << 3)] * x_est[r1];
    }

    d_A[i] = 0.0F;
    for (r1 = 0; r1 < 3; r1++) {
      d_A[i] += c_A[i + (r1 << 3)] * b_g[r1];
    }

    x_prd[i] = v[i] + d_A[i];
    for (r1 = 0; r1 < 8; r1++) {
      e_A[i + (r1 << 3)] = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        e_A[i + (r1 << 3)] += A[i + (r2 << 3)] * p_est[r2 + (r1 << 3)];
      }
    }
  }

  for (i = 0; i < 8; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      a21 = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        a21 += e_A[i + (r2 << 3)] * A[r1 + (r2 << 3)];
      }

      p_prd[i + (r1 << 3)] = a21 + d[i + (r1 << 3)] * delta_t;
    }
  }

  /*  Estimation */
  for (i = 0; i < 2; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      klm_gain[i + (r1 << 1)] = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        klm_gain[i + (r1 << 1)] += H[i + (r2 << 1)] * p_prd[r1 + (r2 << 3)];
      }
    }
  }

  for (i = 0; i < 2; i++) {
    for (r1 = 0; r1 < 2; r1++) {
      a21 = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        a21 += klm_gain[i + (r2 << 1)] * H[r1 + (r2 << 1)];
      }

      S[i + (r1 << 1)] = a21 + R[i + (r1 << 1)];
    }
  }

  for (i = 0; i < 2; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      inv[i + (r1 << 1)] = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        inv[i + (r1 << 1)] += H[i + (r2 << 1)] * p_prd[r1 + (r2 << 3)];
      }
    }
  }

  if ((real32_T)fabs(S[1]) > (real32_T)fabs(S[0])) {
    r1 = 1;
    r2 = 0;
  } else {
    r1 = 0;
    r2 = 1;
  }

  a21 = S[r2] / S[r1];
  a22 = S[2 + r2] - a21 * S[2 + r1];
  for (i = 0; i < 8; i++) {
    Y[1 + (i << 1)] = (inv[r2 + (i << 1)] - inv[r1 + (i << 1)] * a21) / a22;
    Y[i << 1] = (inv[r1 + (i << 1)] - Y[1 + (i << 1)] * S[2 + r1]) / S[r1];
  }

  /*  Estimated state and covariance */
  b_a[0] = a[0];
  b_a[1] = a[1];
  for (i = 0; i < 2; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      klm_gain[r1 + (i << 3)] = Y[i + (r1 << 1)];
    }

    b_v[i] = 0.0F;
    for (r1 = 0; r1 < 8; r1++) {
      b_v[i] += H[i + (r1 << 1)] * x_prd[r1];
    }

    c_a[i] = b_a[i] - b_v[i];
  }

  for (i = 0; i < 8; i++) {
    a21 = 0.0F;
    for (r1 = 0; r1 < 2; r1++) {
      a21 += klm_gain[i + (r1 << 3)] * c_a[r1];
    }

    x_est[i] = x_prd[i] + a21;
  }

  for (i = 0; i < 8; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      A[i + (r1 << 3)] = 0.0F;
      for (r2 = 0; r2 < 2; r2++) {
        A[i + (r1 << 3)] += klm_gain[i + (r2 << 3)] * H[r2 + (r1 << 1)];
      }
    }
  }

  for (i = 0; i < 8; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      a21 = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        a21 += A[i + (r2 << 3)] * p_prd[r2 + (r1 << 3)];
      }

      p_est[i + (r1 << 3)] = p_prd[i + (r1 << 3)] - a21;
    }
  }

  for (i = 0; i < 8; i++) {
    y[i] = x_est[i];
  }
}

void quad_8state_kalman_init(void)
{
  static const float fv0[64] = { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.1F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.1F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.1F };

  int i;
  memcpy(&p_est[0], &fv0[0], sizeof(float) << 6);
  for (i = 0; i < 8; i++) {
    x_est[i] = 0.0F;
  }
}

/* End of code generation (quad_8state_kalman.c) */
