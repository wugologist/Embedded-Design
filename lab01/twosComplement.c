///@file twosComplememt.cab
///@author Michael Wong and Zamir Johl

#include <stdio.h> ///include standard io library for console inputs and outputs

///main function
///takes a user inputed int and prints the one's and two's complement of its binary representation
///@return int indicated a terminated program 
int main(void) ///required main function
{
	int num; ///number to be converted
	printf("Enter an integer: "); ///prompt the user for an int input
	scanf("%d", &num); ///take the user input from console and store its value at num

	int ones = ~num; ///assign the bitwise negation of num to ones for the one's complement
	int twos = -1 * num; ///negative numbers are already stored in two's complement form so no special method is required

	printf("One's complement of %d is %X.\n", num, ones); ///print the value of the one's complement in hex and the original decimal number
	printf("Two's complement of %d is %X.\n", num, twos); ///print the value of the two's complement in hex and the original decimal number
	
	return 0; ///end the program
}
