%% Initialization
clear;
close all;

init01;

delta_t = 0.25;
alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;
q_1 = 1;
q_2 = 1;
%System model
A_c = [0 1 0 0 0 0;
       0 0 -K_2 0 0 0;
       0 0 0 1 0 0;
       0 0 -K_1*K_pp -K_1*K_pd 0 0;
       0 0 0 0 0 1;
       0 0 0 0 -K_3*K_ep -K_3*K_ed];

B_c = [0 0;
       0 0;
       0 0;
       K_1*K_pp 0
       0 0;
       0 K_3*K_ep];

A2 = eye(6) + delta_t*A_c;
B2 = delta_t*B_c;

mx = size(A2, 2);
mu = size(B2,2);

% Initial values
x1_0 = pi;                             % Lambda
x2_0 = 0;                              % r
x3_0 = 0;                              % p
x4_0 = 0;                              % p_dot
x5_0 = 0;                              % e
x6_0 = 0;                              % e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x5_0 x6_0]'; % Initial values

% Time horizon and initialization
N  = 40;                               % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
%z0 = z;                                 % Initial value for optimization

% Bounds
ul_p 	    = -pi/6;                   % Lower bound on control
uu_p 	    = pi/6;                    % Upper bound on control
ul_e = -inf;
uu_e = inf;

ul = [ul_p; ul_e];
uu = [uu_p; uu_e];

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul_p;                           % Lower bound on state x3
xu(3)   = uu_p;                           % Upper bound on state x3

[vlb, vub] = gen_constraints(N,M, xl, xu, ul, uu);

Q2 = diag([1 0 0 0 0 0]);
P2 = diag([q_1 q_2]);

Q_e =gen_q(Q2, P2, N,M);

Aeq = gen_aeq(A2, B2, N, mx, mu);
beq = zeros(mx*N,1);
beq(1:6, 1) = A2*x0;

f = @(x)(x')*Q_e*x;

z0 = [repmat(x0, N, 1); zeros(M*mu,1)]; % Repeat initial state for the horizon


nonlcon = @(z) cnl(z,alpha, beta, lambda_t,mx, N);
options = optimoptions('fmincon', 'Algorithm', 'sqp', ...
    'MaxFunctionEvaluations', 1e5, 'MaxIterations', 10000, 'TolCon', 1e-8);

[z, lambda] = fmincon(f, z0, [], [], Aeq, beq, vlb, vub, nonlcon, options);
[c_val, ceq_val] = cnl(z, alpha, beta, lambda_t, mx, N);

%% Extract control inputs and states
u1  = [z(N*mx+1:mu:N*mx+M*mu);z(N*mx+M*mu)]; % Control input from solution
u2  = [z(N*mx+2:mu:N*mx+M*mu);z(N*mx+M*mu)];
x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];              % State x4 from solution
x5 = [x0(5);z(5:mx:N*mx)];              % State x5 from solution
x6 = [x0(6);z(6:mx:N*mx)];              % State x6 from solution


num_variables = 5/delta_t;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u1   = [zero_padding; u1; zero_padding];
u2   = [zero_padding; u2; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];

x = [x1 x2 x3 x4 x5 x6];

%% Plotting
t = 0:delta_t:delta_t*(length(u1)-1);

figure(2)
subplot(811)
stairs(t,u1),grid
ylabel('u_p')
subplot(812)
stairs(t,u2),grid
ylabel('u_e')
subplot(813)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
subplot(814)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
subplot(815)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
subplot(816)
plot(t,x4,'m',t,x4','mo'),grid
ylabel('pdot')
subplot(817)
plot(t,x5,'m',t,x5','mo'),grid
ylabel('e')
subplot(818)
plot(t,x6,'m',t,x6','mo'),grid
ylabel('edot')
xlabel('tid (s)'),ylabel('pdot')

%% Preparation of data for workspace
slx_input = [t' u1 u2];
slx_x_input = [t' x];
ideal_data = [t; u1'; u2' ; x1'; x2'; x3'; x4'; x5'; x6'];

save('optimization_data.mat', 'ideal_data');

%% Function for nonlinear constraints
function [c,ceq] = cnl(z, alpha, beta,lambda_t, mx, N)
ceq = [];
c = alpha*exp(-beta*(z(1:mx:N*mx)-lambda_t*ones(N,1)).^2)-z(5:mx:N*mx);

end


