%% Get the wanted files
dir = "data/serie4/"; % Change this to the series you want. 
simdata = load(dir + "simdata.mat").ans;
optdata = load(dir + "optimization_data.mat").ideal_data;

% Manipulate data to be in desired format (radians, lambda_0 = pi)
simdata(2:end , : ) = deg2rad(simdata(2:end , : ));
simdata(2, :) = simdata(2, :) + pi;

%% Get the relevant data from the different matrices
t = simdata(1,:);
t_opt = optdata(1,:);
u = optdata(2,:);
x1 = simdata(2,:);
x2 = simdata(3,:);
x3 = simdata(4,:);
x4 = simdata(5,:);

x1_opt = optdata(3,:);
x2_opt = optdata(4,:);
x3_opt = optdata(5,:);
x4_opt = optdata(6,:);

%% plot the experimental data
figure(2)
subplot(511)
stairs(t_opt,u),grid
xlim([0 min(t(size(t,2)), t_opt(size(t_opt, 2)))])
ylabel('u')
subplot(512)
plot(t,x1,'m'),grid
xlim([0 min(t(size(t,2)), t_opt(size(t_opt, 2)))])
ylabel('lambda')
subplot(513)
plot(t,x2,'m'),grid
xlim([0 min(t(size(t,2)), t_opt(size(t_opt, 2)))])
ylabel('r')
subplot(514)
plot(t,x3,'m'),grid
xlim([0 min(t(size(t,2)), t_opt(size(t_opt, 2)))])
ylabel('p')
subplot(515)
plot(t,x4,'m'),grid
xlabel('tid (s)'),ylabel('pdot')
xlim([0 min(t(size(t,2)), t_opt(size(t_opt, 2)))])
exportgraphics(gcf, dir + "experimental.pdf", 'ContentType', 'vector');

%% Plot the optimization data with cutoff time

figure(3)
subplot(511)
stairs(t_opt,u),grid
xlim([0 min(t(size(t,2)), t_opt(size(t_opt, 2)))])
ylabel('u')
subplot(512)
plot(t_opt,x1_opt,'m',t_opt,x1_opt,'mo'),grid
xlim([0 min(t(size(t,2)), t_opt(size(t_opt, 2)))])
ylabel('lambda')
subplot(513)
plot(t_opt,x2_opt,'m',t_opt,x2_opt','mo'),grid
xlim([0 min(t(size(t,2)), t_opt(size(t_opt, 2)))])
ylabel('r')
subplot(514)
plot(t_opt,x3_opt,'m',t_opt,x3_opt,'mo'),grid
xlim([0 min(t(size(t,2)), t_opt(size(t_opt, 2)))])
ylabel('p')
subplot(515)
plot(t_opt,x4_opt,'m',t_opt,x4_opt','mo'),grid
xlim([0 min(t(size(t,2)), t_opt(size(t_opt, 2)))])
xlabel('tid (s)'),ylabel('pdot')
exportgraphics(gcf, dir + "optimization.pdf", 'ContentType', 'vector');

