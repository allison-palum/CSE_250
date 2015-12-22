#ifndef A6_HPP
#define A6_HPP

#include <stack>
#include <iostream>
#include <stdexcept>
#include "token.hpp"

//implement your function RPN
template <typename Iter>
double RPN(Iter first, Iter last) {
	std::stack<token> stack;
	token myToken;
	for (Iter myIter = first; myIter != last; ++myIter) {
		myToken = *myIter;
		if (myToken.is_operand()) {
			stack.push(myToken);
			//std::cout << myToken.as_operand() << std::endl;
		}
		else if (myToken.is_operator()) {
			//std::cout << myToken.as_operator() << std::endl;
			if (stack.size() < 2) { throw std::runtime_error("error"); }
			else {
				double secondOperand = stack.top().as_operand();
				stack.pop();
				double firstOperand = stack.top().as_operand();
				stack.pop();
				if (myToken.as_operator() == '*') {
					double value = (firstOperand * secondOperand);
					stack.push(token(value));
				}
				else if (myToken.as_operator() == '/') {
					if (secondOperand == 0.0) {
						throw std::runtime_error("error");
						return 0;
					}
					else {
						double value = (firstOperand / secondOperand);
						stack.push(token(value));
					}
				}
				else if (myToken.as_operator() == '+') {
					double value = (firstOperand + secondOperand);
					stack.push(token(value));
				}
				else if (myToken.as_operator() == '-') {
					double value = (firstOperand - secondOperand);
					stack.push(token(value));
				}
			}
		}
	}
	if (stack.size() == 1) { return stack.top().as_operand(); }
	else {
		throw std::runtime_error("error");
		return 0;
	}
}
#endif // A6_HPP
