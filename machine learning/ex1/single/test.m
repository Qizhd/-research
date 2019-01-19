data = load('ex1data1.txt');
X = data(:, 1); y = data(:, 2);
m = length(y); % number of training examples

% Plot Data
% Note: You have to complete the code in plotData.m
plotData(X, y);


%% =================== Part 3: Cost and Gradient descent ===================

X = [ones(m, 1), data(:,1)]; % Add a column of ones to x
theta = zeros(2, 1); % initialize fitting parameters

iterations = 1400;
alpha = 0.01;



[theta,J_history] = gradientDescent(X, y, theta, alpha, iterations);

plot(J_history);
xlabel('iterations');ylabel('h(\theta)')
J_history;
theta;
