#include <stdio.h>  //Imports io library
#define SIZE 10

void read_array(int list[])
{
	/*
	This function takes in an array. It then fills the array by first storing the console input in a temporary variable
	and then putting the input into the array.
	*/

	int number = 0;  //Creates temporary variable
	int i;           //Initializes counter variable

	printf("Input ten integers below: \n");  //Prints directions to console
	for(i=0;i<SIZE;i++)    //for loop that goes from 0 to SIZE
	{
		scanf("%d",&number );  //Takes console input and stores it in number
		list[i] = number;      //Transfers integer from number into array

	}
}

void print_array(int list[])
{
	/*
	This function prints the array to the console.
	*/
	int  i;		//Initializes counter variable
	printf("\n\nThe array is \n");		//Prints label to console
	for(i=0;i<SIZE;i++)			//for loop
	{
		printf("%d ", list[i]);         //Prints array to console
	}
	printf("\n");		//formatting
}

void sort_array(int list[]){
	int i, j;    //counters
	int temp;

	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE-1;j++)
		{
			if(list[j]>list[j+1])
			{
			temp = list[j];
			list[j] = list[j+1];
			list[j+1] = temp;
			}
		}
	}
}

int main(void)
{
	int list[SIZE];
	read_array(list);
	sort_array(list);
	print_array(list);
	return(0);
}

