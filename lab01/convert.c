#include <stdio.h>  ///Imports standard io library

/**
*convert.c
*
*Zamir Johl and Michael Wong
*
*This program asks the user to input two integers which 
*are then printed in decimal, octal and hexadecimal form
*/

int main(void)  ///Main method
{
	int num1, num2; ///Variables to store user inputs

	printf("Enter the first integer to convert: \n"); ///Prompts the user for an integer
	scanf("%d", &num1);		///Stores integer as a decimal in num1
	printf("Enter the second integer to convert: \n"); ///Prompts the user for an integer
	scanf("%d", &num2);		///Stores integer as a decimal in num2

	printf("%d is %X in hex. %d is %o in octal.\n", num1, num1, num1, num1); ///Prints num1 in decimal, hex and octal format
	printf("%d is %X in hex. %d is %o in octal.\n", num2, num2, num2, num2); ///Prints num2 in decimal, hex and octal format
	
	return 0;///Returns 0, ends program
}
	
