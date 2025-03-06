% Calculates LQR gain matrices. Assumes A1 and B1 are stored in workspace
template_problem_2;
Q = diag([10 10 10 10]);
R = diag([.1]);

[K,S,P] = dlqr(A1,B1,Q,R);