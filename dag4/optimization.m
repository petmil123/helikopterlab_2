%% Initialization
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
N  = 100;                               % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization

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

cnl = -alpha*exp(-beta*(z(1:mx:N*mx)-lambda_t*ones(N))^2)-z(5:mx:N*mx);

Q2 = diag([1 0 0 0 0 0]);
P2 = diag([q_1 q_2]);

Q_e =gen_q(Q2, P2, N,M);

Aeq = gen_aeq(A2, B2, N, mx, mu);
beq = zeros(mx*N,1);
beq(1:6, 1) = A2*x0;

f = @(x)(x')*Q2*x;

[z, lambda] = fmincon(f, x0, [],[], Aeq, beq, vlb, vub, cnl);
