data = load('ex1data2.txt');
X = data(:, 1:2);
y = data(:, 3) / 100000;
m = length(y);


alpha = 0.01;
num_iters = 400;

% Init Theta and Run Gradient Descent 
theta = zeros(3, 1);


X = [ones(m, 1) X];

X = X*[ 1 0 0 ;0 0.001 0; 0 0 1];



%surf(X(:,2),X(:,3),y);


[theta, J_history] = gradientDescentMulti(X, y, theta, alpha, num_iters);


figure;
plot(J_history);
xlabel('Number of iterations');
ylabel('Cost J');


theta' *[1;1650;5]

