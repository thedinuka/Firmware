/*
 * quad_8state_kalman.c
 *
 * Code generation for function 'quad_8state_kalman'
 *
 * C source code generated on: Thu Feb 27 21:45:01 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "quad_8state_kalman.h"

/* Variable Definitions */
static float p_est[64];
static float x_est[8];

/* Function Definitions */

/*
 * function y = quad_8state_kalman(a,g, delta_t, gyro_rp, gyro_y, v_xy, gb_rp, gb_y, acc_xy, k_1)
 */
void quad_8state_kalman(const float a[2], const float g[3], float delta_t, float
  gyro_rp, float gyro_y, float v_xy, float gb_rp, float gb_y, float acc_xy,
  float k_1, float y[8])
{
  double A[64];
  signed char I[64];
  int i;
  float b_A[64];
  signed char G[24];
  double H[16];
  float v[8];
  float d[64];
  float b_v[2];
  float R[4];
  float c_A[24];
  int r1;
  int r2;
  float d_A[24];
  float b_g[3];
  float e_A[8];
  float f_A[64];
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
  /* 'quad_8state_kalman:5' u = [g(1); g(2); g(3)]; */
  /* 'quad_8state_kalman:6' z = [a(1); a(2)]; */
  /* continuous state transition matrix */
  /* 'quad_8state_kalman:10' A = zeros(8,8); */
  /* 'quad_8state_kalman:11' A(1,6) = -1; */
  for (i = 0; i < 64; i++) {
    A[i] = 0.0;

    /* discretize state transition matrix */
    /* 'quad_8state_kalman:20' A = eye(8)+ A.*delta_t; */
    I[i] = 0;
  }

  A[40] = -1.0;

  /* 'quad_8state_kalman:12' A(2,7) = -1; */
  A[49] = -1.0;

  /* 'quad_8state_kalman:13' A(3,8) = -1; */
  A[58] = -1.0;

  /* 'quad_8state_kalman:14' A(4,2) = -9.81; */
  A[11] = -9.81;

  /* 'quad_8state_kalman:15' A(4,4) = k_1; */
  A[27] = k_1;

  /* 'quad_8state_kalman:16' A(5,1) = 9.8; */
  A[4] = 9.8;

  /* 'quad_8state_kalman:17' A(5,5) = k_1; */
  A[36] = k_1;
  for (i = 0; i < 8; i++) {
    I[i + (i << 3)] = 1;
  }

  for (i = 0; i < 64; i++) {
    b_A[i] = (float)I[i] + (float)A[i] * delta_t;
  }

  /* continuous control matrix */
  /* 'quad_8state_kalman:23' G = zeros(8,3); */
  for (i = 0; i < 24; i++) {
    G[i] = 0;
  }

  /* 'quad_8state_kalman:24' G(1,1) = 1; */
  G[0] = 1;

  /* 'quad_8state_kalman:25' G(2,2) = 1; */
  G[9] = 1;

  /* 'quad_8state_kalman:26' G(3,3) = 1; */
  G[18] = 1;

  /* 'quad_8state_kalman:28' B = A*G*delta_t; */
  /* measurement matrix */
  /* 'quad_8state_kalman:31' H = zeros(2,8); */
  memset(&H[0], 0, sizeof(double) << 4);

  /* 'quad_8state_kalman:32' H(1,4) = k_1; */
  H[6] = k_1;

  /* 'quad_8state_kalman:33' H(2,5) = k_1; */
  H[9] = k_1;

  /* process noise matrix */
  /* 'quad_8state_kalman:36' Q = diag([gyro_rp, gyro_rp, gyro_y, v_xy, v_xy, gb_rp, gb_rp, gb_y])*delta_t; */
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
  /* 'quad_8state_kalman:39' R = diag([acc_xy, acc_xy]); */
  b_v[0] = acc_xy;
  b_v[1] = acc_xy;
  for (i = 0; i < 4; i++) {
    R[i] = 0.0F;
  }

  for (i = 0; i < 2; i++) {
    R[i + (i << 1)] = b_v[i];
  }

  /* initialization */
  /* 'quad_8state_kalman:44' if isempty(x_est) */
  /*  Predicted state and covariance */
  /* 'quad_8state_kalman:50' x_prd = A * x_est + B * u; */
  for (i = 0; i < 8; i++) {
    for (r1 = 0; r1 < 3; r1++) {
      c_A[i + (r1 << 3)] = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        c_A[i + (r1 << 3)] += b_A[i + (r2 << 3)] * (float)G[r2 + (r1 << 3)];
      }
    }
  }

  for (i = 0; i < 3; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      d_A[r1 + (i << 3)] = c_A[r1 + (i << 3)] * delta_t;
    }
  }

  b_g[0] = g[0];
  b_g[1] = g[1];
  b_g[2] = g[2];

  /* 'quad_8state_kalman:51' p_prd = A * p_est * A' + Q; */
  for (i = 0; i < 8; i++) {
    v[i] = 0.0F;
    for (r1 = 0; r1 < 8; r1++) {
      v[i] += b_A[i + (r1 << 3)] * x_est[r1];
    }

    e_A[i] = 0.0F;
    for (r1 = 0; r1 < 3; r1++) {
      e_A[i] += d_A[i + (r1 << 3)] * b_g[r1];
    }

    x_prd[i] = v[i] + e_A[i];
    for (r1 = 0; r1 < 8; r1++) {
      f_A[i + (r1 << 3)] = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        f_A[i + (r1 << 3)] += b_A[i + (r2 << 3)] * p_est[r2 + (r1 << 3)];
      }
    }
  }

  for (i = 0; i < 8; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      a21 = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        a21 += f_A[i + (r2 << 3)] * b_A[r1 + (r2 << 3)];
      }

      p_prd[i + (r1 << 3)] = a21 + d[i + (r1 << 3)] * delta_t;
    }
  }

  /*  Estimation */
  /* 'quad_8state_kalman:54' S = H * p_prd' * H' + R; */
  for (i = 0; i < 2; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      klm_gain[i + (r1 << 1)] = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        klm_gain[i + (r1 << 1)] += (float)H[i + (r2 << 1)] * p_prd[r1 + (r2 << 3)];
      }
    }
  }

  for (i = 0; i < 2; i++) {
    for (r1 = 0; r1 < 2; r1++) {
      a21 = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        a21 += klm_gain[i + (r2 << 1)] * (float)H[r1 + (r2 << 1)];
      }

      S[i + (r1 << 1)] = a21 + R[i + (r1 << 1)];
    }
  }

  /* 'quad_8state_kalman:55' inv = H * p_prd'; */
  for (i = 0; i < 2; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      inv[i + (r1 << 1)] = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        inv[i + (r1 << 1)] += (float)H[i + (r2 << 1)] * p_prd[r1 + (r2 << 3)];
      }
    }
  }

  /* 'quad_8state_kalman:56' klm_gain = (S \ inv)'; */
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
  /* 'quad_8state_kalman:59' x_est = x_prd + klm_gain * (z - H * x_prd); */
  b_a[0] = a[0];
  b_a[1] = a[1];
  for (i = 0; i < 2; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      klm_gain[r1 + (i << 3)] = Y[i + (r1 << 1)];
    }

    b_v[i] = 0.0F;
    for (r1 = 0; r1 < 8; r1++) {
      b_v[i] += (float)H[i + (r1 << 1)] * x_prd[r1];
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

  /* 'quad_8state_kalman:60' p_est = p_prd - klm_gain * H * p_prd; */
  for (i = 0; i < 8; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      b_A[i + (r1 << 3)] = 0.0F;
      for (r2 = 0; r2 < 2; r2++) {
        b_A[i + (r1 << 3)] += klm_gain[i + (r2 << 3)] * (float)H[r2 + (r1 << 1)];
      }
    }
  }

  for (i = 0; i < 8; i++) {
    for (r1 = 0; r1 < 8; r1++) {
      a21 = 0.0F;
      for (r2 = 0; r2 < 8; r2++) {
        a21 += b_A[i + (r2 << 3)] * p_prd[r2 + (r1 << 3)];
      }

      p_est[i + (r1 << 3)] = p_prd[i + (r1 << 3)] - a21;
    }
  }

  /* 'quad_8state_kalman:62' y = x_est; */
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
