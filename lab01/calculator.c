#include <stdio.h> ///include io library

///add two integers
///@param a the first number to be added
///@param b the second number to be added
///@return int the sum

int add(int a, int b) ///add two integers
{
	return a+b; ///return the sum
}

///subtract two integers
///@param a the first number to be subtracted
///@param b the second number to be subtracted
///@return int the difference

int subtract(int a, int b) ///subtract two integers
{
	return a-b; ///return the difference
}

///multiply two integers
///@param a the first number to be multiplied
///@param b the second number to be multiplied
///@return int the product

int multiply(int a, int b) ///multiply two integers
{
	return a*b; ///return the product
}

///divide two integers
///@param a the first number to be divided
///@param b the second number to be divided
///@return int the dividend

int divide(int a, int b) ///integer division of two integers
{
	return a/b; ///return the divident
}

///main function
///@return int signals when program terminates

int main(void) ///main function
{
	int num1, num2; ///declare the operands
	char operation; ///declare the operation character
	int result; ///declare the result of the operation

	while(1==1)	///repeat the following loop indefinitly
	{
		printf("\nEnter the first integer: "); ///prompt for the first operand
		scanf("%d", &num1); ///store the user input to num1
		
		printf("\nEnter the second integer: "); ///prompt for the second operand
		scanf("%d", &num2); ///store the user input to num2

		printf("\nEnter the operator (+, -, *, /): "); ///prompt for the operation
		scanf("%c", &operation); ///store the user input to the char 'operation'

		if(operation == '+') ///check for addition
		{
			result = add(num1, num2); ///add the two numbers
		}

		else if(operation == '-') ///check for subtraction
		{
			result == subtract(num1, num2); ///subtract the two numbers
		}

		else if(operation == '*') ///check for multiplication
		{
			result == multiply(num1, num2); ///multiply the numbers
		}

		else if (operation == '/') ///check for multiplication
		{
			result == divide(num1, num2); ///divide the numbers
		}
		
		else if(operation == 'q') ///check for quit
		{
			return 0; ///exit the program
		}

		else ///if something else is input
		{
			printf("Something went wrong.\n"); ///tell user something is wrong
		}

		printf("The result is %d.", result); //print the result to console
	}
}

