data = load('ex2data1.txt');
X = data(:, [1, 2]); y = data(:, 3);


plotData(X, y);


[m, n] = size(X);

% Add intercept term to x and X_test
X = [ones(m, 1) X];

% Initialize fitting parameters
initial_theta = zeros(n + 1, 1);

options = optimset('GradObj', 'on', 'MaxIter', 4000);


[theta,cost,exitFlag] = ...
	fminunc(@(t)(costFunction(t, X, y)), initial_theta, options);

 % Print theta to screen
fprintf(' %f \n', theta);
fprintf('Expected theta (approx):\n -25.161\n 0.206\n 0.201\n');


