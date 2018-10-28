close all
clear all
clc


%% Input parameters
R1 = 56e3;
R2 = 16e3;
C1 = 100e-9;
C2 = .670e-9;

%% Filter parameters and Transfer Function Generation
omega_p = 1/sqrt(R1*R2*C2*C1);
Q = 1/omega_p/(R2*C1+R1*C1+C2*R2);
K = C1*R2;
num = [K*omega_p^2 0];
den = [1 omega_p/Q omega_p^2];
sys = tf(num,den);  % Generating the system function
bode(sys)
title('Frequency Response for the Bandpass Filter')

%% Determining the Poles (Pass-band of the filter)
syms s
F = double(solve(  s^2 + ((R2*C1+R1*C1+R2*C2)/(R1*R2*C1*C2)) *s + 1/(R1*R2*C1*C2),s));
f_H = -F(1)/2/pi
f_L = -F(2)/2/pi