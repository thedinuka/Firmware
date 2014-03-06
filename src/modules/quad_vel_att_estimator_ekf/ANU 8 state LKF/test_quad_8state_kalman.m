%%%test the quad_8state_kalman with some random data

data_size = 1000;

a = single(rand(data_size,2));
g = single(rand(data_size,3));
dt = single(0.004);
gyro_rp = single(0.05); gyro_y = single(0.001); v_xy = single(0.1); gb_rp = single(0.0001); 
gb_y = single(0.0001); acc_xy = single(0.3); k_1 = single(-0.3);

results_vec = single(zeros(8,data_size));
for i=1:1000
    results_vec(:,i) = quad_8state_kalman(a(i,:),g(i,:),dt,gyro_rp, gyro_y, v_xy, gb_rp, gb_y,acc_xy, k_1);
    
end