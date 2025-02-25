% Calculates LQR gain matrices. Assumes A and B are stored in workspace

Q = diag([1,1,1,1]);
R = diag([1]);

[K,S,P] = dlqr(A1,B1,Q,R);