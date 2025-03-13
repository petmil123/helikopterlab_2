clear;
close all;

s1 = load('data\serie1\data.mat', 'ans');
%s2 = load('data\serie2\data.mat', 'ans');
%s3 = load('data\serie3\data.mat', 'ans');
%s4 = load('data\serie4\data.mat', 'ans');
%s5 = load('data\serie5\data.mat', 'ans');
%s6 = load('data\serie6\data.mat', 'ans');
opt= load('data\serie1\optimization_data.mat', 'ideal_data');

s1 = s1.ans;
%s2 = s2.ans;
%s3 = s3.ans;
%s4 = s4.ans;
%s5 = s5.ans;
%s6 = s6.ans;
opt = opt.ideal_data;
xlabels = ["Travel" "Travel rate" "Pitch" "Pitch Rate" "Elevation" "Elevation rate"];
for i = 1:6
   subplot(6,1,i);
   hold on;
plot(s1(1,:),s1(i+1,:));
plot(opt(1,:), rad2deg(opt(i+3,:)));
title(xlabels(i));
legend(["experimental" "optimal"]);
hold off;
end

