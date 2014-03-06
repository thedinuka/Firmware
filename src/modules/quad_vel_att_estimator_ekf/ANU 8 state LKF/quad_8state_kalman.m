function y = quad_8state_kalman(a,g, delta_t, gyro_rp, gyro_y, v_xy, gb_rp, gb_y, acc_xy, k_1) %#codegen

%states {phi, theta, psi, vx vy, beta_gx, beta_gy, beta_gz}

u = [g(1); g(2); g(3)];
z = [a(1); a(2)];


%continuous state transition matrix
A = single(zeros(8,8));
A(1,6) = -1;
A(2,7) = -1;   
A(3,8) = -1;
A(4,2) = -9.81;
A(4,4) = k_1;
A(5,1) = 9.8;
A(5,5) = k_1;

%discretize state transition matrix
A = eye(8)+ A.*delta_t;

%continuous control matrix
G = single(zeros(8,3));             
G(1,1) = 1;
G(2,2) = 1;
G(3,3) = 1;

B = A*G*delta_t;

%measurement matrix
H = single(zeros(2,8));
H(1,4) = k_1;
H(2,5) = k_1;

%process noise matrix
Q = diag([gyro_rp, gyro_rp, gyro_y, v_xy, v_xy, gb_rp, gb_rp, gb_y])*delta_t;

%measurement noise matrix
R = diag([acc_xy, acc_xy]);


persistent p_est x_est
%initialization
if isempty(x_est)
    p_est = single(diag([0,0,0,     0,0,     0.1, 0.1, 0.1]));
    x_est = single([0,0,0,     0,0,    0,0,0]');
end

% Predicted state and covariance
x_prd = A * x_est + B * u;
p_prd = A * p_est * A' + Q;

% Estimation
S = H * p_prd' * H' + R;
inv = H * p_prd';
klm_gain = (S \ inv)';

% Estimated state and covariance
x_est = x_prd + klm_gain * (z - H * x_prd);
p_est = p_prd - klm_gain * H * p_prd;

y = x_est;

end