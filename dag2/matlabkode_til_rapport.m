% Discrete time system model. x = [lambda r p p_dot]'
delta_t	= 0.25; % sampling time
A1 = [0 1 0 0;
      0 0 -K_2 0;
      0 0 0 1;
      0 0 -K_1*K_pp -K_1*K_pd] * delta_t + eye(4);
B1 = [0; 0; 0; K_1*K_pp] * delta_t;

% Initial values
x1_0 = pi;                             % Lambda
x2_0 = 0;                              % r
x3_0 = 0;                              % p
x4_0 = 0;                              % p_dot
x0 = [x1_0 x2_0 x3_0 x4_0]';           % Initial values

% Bounds
ul 	    = -pi/6;                   % Lower bound on control
uu 	    = pi/6;                    % Upper bound on control

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
Q1 = zeros(mx,mx);
Q1(1,1) = 2;                            % Weight on state x1
Q1(2,2) = 0;                            % Weight on state x2
Q1(3,3) = 0;                            % Weight on state x3
Q1(4,4) = 0;                            % Weight on state x4
P1 = 2*q;                               % Weight on input
Q = gen_q(Q1,P1,N,M);                   % Generate Q, hint: gen_q
c = zeros(mx*N+mu*N,1);                 % Generate c, this is the linear constant term in the QP

%% Generate system matrixes for linear model
Aeq = gen_aeq(A1,B1,N,mx,mu);             % Generate A, hint: gen_aeq
beq = zeros(mx*N,1);                      % Generate b
beq(1:4,1) = A1*x0;

%% Solve QP problem with linear model
tic
[z,lambda] = quadprog(Q,c,[],[],Aeq,beq,vlb,vub); % hint: quadprog. Type 'doc quadprog' for more info 
t1=toc;