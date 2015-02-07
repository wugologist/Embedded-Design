#include <stdio.h> ///Imports standard io library

/**
*logicalOp.c
*
*Zamir Johl & Michael Wong
*
*This program prompts the user for two integers and then performs
*a series of bitwise operations and displays the result
*/

int main(void) ///Main function
{
	int num1, num2;  ///Variables to store user inputs

	printf("Enter the first integer to convert: \n"); ///Prompts the user for an integer
	scanf("%d", &num1);		///Stores integer as a decimal in num1
	printf("Enter the second integer to convert: \n"); ///Prompts the user for an integer
	scanf("%d", &num2);		///Stores integer as a decimal in num2

	int and = num1 & num2; ///Applies the bitwise AND operation to the numbers and stores in a new variable
	int or = num1 | num2;  ///Applies the bitwise OR operation to the numbers and stores in a new variable
	int xor = num1 ^ num2; ///Applies the bitwise XOR operation to the numbers and stores in a new variable

	printf("The value of %d AND %d is %X\n", num1, num2, and); ///Displays the value of num1 AND num2
	printf("The value of %d OR %d is %X\n", num1, num2, or);  ///Displays the value of num1 OR num2
	printf("The value of %d XOR %d is %X\n", num1, num2, xor);  ///Displays the value of num1 XOR num2
	
	return 0; ///Returns 0 and ends the program
}
	
