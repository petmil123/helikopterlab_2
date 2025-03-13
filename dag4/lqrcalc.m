% Calculates LQR gain matrices. Assumes A1 and B1 are stored in workspace
optimization;
Q = diag([100 10 10 10 10 10]);
R = diag([.1 .1]);

[K,S,P] = dlqr(A2,B2,Q,R);