function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
X = [ones(m,1) X];
% You need to return the following variables correctly 
J = 0;

Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%


h2 = sigmoid(X*Theta1');  % 5000 x 401 * 401 x 25
h2 = [ones(m,1) h2];      % 5000 x 26
h3 = sigmoid(h2*Theta2'); %5000 x 26 * 26 x 10


y1 = zeros(m,num_labels);      %5000 x 10
for i=1:m
  y1(i,y(i)) = 1;
endfor


%      5000 x 10 .* 5000 x 10      5000 x 10 .* 5000 x 10  
J = (-1/m)*sum(sum(  log(h3).*y1 + log(1 - h3).*(1 - y1)   ));

J = J + lambda*(sum(sum(Theta1(:,2:end).^2)) + sum(sum(Theta2(:,2:end).^2)))/(2*m);




for i = 1:m
  %        25 x 10          *  10 x 1        .* (25 x 1   .* 25 x 1)
  delta2 = Theta2(:,2:end)' * (h3 - y1)(i,:)' .* ((h2(i,:) .*(1 - h2(i,:)))(:,2:end))';
  
  %                            10 x 1       * 1 x 26
  Theta2_grad = Theta2_grad + (h3 - y1)(i,:)'*h2(i,:);
  
  %                           25 x 1 * 1 x 401
  Theta1_grad = Theta1_grad + delta2 * X(i,:);
endfor

Theta1_grad=Theta1_grad ./ m;
Theta2_grad=Theta2_grad ./ m;

Theta1(:,1) = 0;
Theta2(:,1) = 0;
Theta1_grad = Theta1_grad + lambda / m * Theta1;
Theta2_grad = Theta2_grad + lambda / m * Theta2;


% -------------------------------------------------------------
##X=[ones(m,1),X];
##a1=Theta1*X';     %25x401 * 401x5000
##z1=[ones(m,1),sigmoid(a1)'];
##a2=Theta2*z1';
##h=sigmoid(a2);
##
##yk=zeros(m,num_labels);
##for i=1:m
##	yk(i,y(i))=1;
##end
##
##J = (1/m)* sum(sum(((-yk) .* log(h') - (1 - yk) .* log(1 - h'))));
##
##r=(lambda/2/m)*(sum(sum(Theta1(:,2:end) .^ 2))+sum(sum(Theta2(:,2:end) .^ 2)));
##J=J+r;
##
##
##for i=1:m
##	a1=X(i,:);
##	a1=a1';
##	z2=Theta1*a1; % 25 x 401 * 401 x 1
##	a2=[1;sigmoid(z2)];
##	z3=Theta2*a2;
##	a3=sigmoid(z3);
##	y=yk(i,:);
##	delta3=a3-y'; % 10 x 1
##  %        25 x 10           10 x 1 .* 25 x 1
##	delta2 = Theta2(:,2:end)' * delta3 .* sigmoidGradient(z2);  % delta2 is a 25x1 column vector
##    
##	Theta2_grad = Theta2_grad + delta3 * a2';
##	Theta1_grad = Theta1_grad + delta2 * a1';
##
##end
##
##Theta1_grad=Theta1_grad ./ m;
##Theta2_grad=Theta2_grad ./ m;
##
##Theta1(:,1) = 0;
##Theta2(:,1) = 0;
##Theta1_grad = Theta1_grad + lambda / m * Theta1;
##Theta2_grad = Theta2_grad + lambda / m * Theta2;
##
##




% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
