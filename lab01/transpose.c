#include <stdio.h>
#define SIZE 12

void transpose(int array[SIZE][SIZE])
{
	int temp, i, j;
	
	for(i=0; i<SIZE; i++)
	{
		for(j=i; j<SIZE; j++)
		{
			temp = array[i][j];
			array[i][j] = array[j][i];
			array[j][i] = temp;
		}
	}
}

void ptr_transpose(int array[SIZE][SIZE]){
	
	int counter, i, j,first,second;
	int* temp;

	for(i=0;i<SIZE;i++){
		counter = 0;
		for(j=i;j<SIZE;j++){
			if(i != j){
				first = (counter + (5*i)-1);
				second = first + ((SIZE-1)*counter);
				
				temp = *(array + first);
				/// *(array + first) = *(array + second);
				*(array + second) = temp;				
			}
			counter++;
		}
	}
}

void printarray(int array[SIZE][SIZE])
{
	int i, j;
	for (i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++)
		{
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void fillarray(int array[SIZE][SIZE])
{
        int counter = 0;
	int i, j;

        for(i=0; i<SIZE; i++)
        {
                for(j=0; j<SIZE; j++)
                {
                        array[i][j] = ++counter;
                }
        }
}



int main(void)
{
	int matrix[SIZE][SIZE];
	fillarray(matrix);
	printarray(matrix);
	transpose(matrix);
	printarray(matrix);
	
	return 0;
}
