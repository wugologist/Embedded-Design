///@file pointers.c
///@author Michael Wong and Zamir Johl

#include <stdio.h> ///include io library

///perform various operations with pointers and references
///@return int when the program terminates

int main(void) ///main function
{
	char ch = 'T'; ///assign character T to ch
	char *chptr = &ch; ///create a pointer chptr to the address of the value of ch
	char name[6]; ///create an array called name of characters, aka a string

	int a = 1000; ///assign 1000 to integer a
	int *intptr = &a; ///create a pointer named intptr to the address of a

	float fnumber = 1.20000; ///create a float called fnumber and assign 1.2 to it
	float *fptr = &fnumber; ///create a pointer called fptr to the address of fnumber

	char *ptr = "My dog has fleas!"; ///create a pointer, ptr, to the string "My dog has fleas!"

	printf("\n [%c],[%d],[%f],[%c],[%s]\n", *chptr, *intptr, *fptr, *ptr, ptr); ///print the values of the above variables by referencing their addresses
	///a pointer to an array or string only points to the first element in it, so *ptr prints 'M' but ptr refers to the entire string

	chptr = ptr; /// assign a copy of the value of ptr to chptr

	printf("\n [%c], [%s] \n" , *chptr, chptr); ///print the value *chptr points to (the first element of the string) and then the entire string

	name[0] = 75; ///assign the character with the number 75 to the first index of name
	name[1] = 97; ///assign char 97 to the second index of name
	name[2] = 0x65; ///assign char 0x65 to the third inded of name
	name[3] = 0154; ///assign char 154 to the fourth index of name
	name[4] = 105; ///assign char 105 to the fifth index of name
	name[5] = 0; ///null terminator, ends the string

	printf("\n [%s]\n", name); ///print the string
	///this prints a string because the array is of type char, so the numbers are interpreted as ASCII values

	return 0; ///end the program
}
