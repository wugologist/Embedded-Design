#include <stdio.h> //library for console i/o
#include <stdlib.h> //several functions, including memory allocation
#include <fcntl.h> //allows for manipulating files
#include <unistd.h> //allows access to POSIX OS API
#include <sys/mman.h> //for memory mapping

// physical base address of GPIO
#define GPIO_ADDRESS	0x400D0000
// length of MEM Mapped IO window
#define GPIO_MAP_LEN 0xFF

#define LED1_OFFSET	0x12C  /* Offset for LED1 */
#define LED2_OFFSET	0x130  /* Offset for LED2 */
#define LED3_OFFSET	0x134  /* Offset for LED3 */
#define LED4_OFFSET	0x138  /* Offset for LED4 */
#define LED5_OFFSET	0x13C  /* Offset for LED5 */
#define LED6_OFFSET	0x140  /* Offset for LED6 */
#define LED7_OFFSET	0x144  /* Offset for LED7 */
#define LED8_OFFSET	0x148  /* Offset for LED8 */

#define SW1_OFFSET	0x14C  /* Offset for Switch 1 */
#define SW2_OFFSET	0x150  /* Offset for Switch 2 */
#define SW3_OFFSET	0x154  /* Offset for Switch 3 */
#define SW4_OFFSET	0x158  /* Offset for Switch 4 */
#define SW5_OFFSET	0x15C  /* Offset for Switch 5 */
#define SW6_OFFSET	0x160  /* Offset for Switch 6 */
#define SW7_OFFSET	0x164  /* Offset for Switch 7 */
#define SW8_OFFSET	0x168  /* Offset for Switch 8 */

#define PBTNL_OFFSET	0x16C  /* Offset for left push button */
#define PBTNR_OFFSET	0x170  /* Offset for right push button */
#define PBTNU_OFFSET	0x174  /* Offset for up push button */
#define PBTND_OFFSET	0x178  /* Offset for down push button */
#define PBTNC_OFFSET	0x17C  /* Offset for center push button */

#define REG_WRITE(addr, off, val) (*(volatile int*)(addr+off)=(val)) //macro to write val to the specified memory location (addr+off)
#define REG_READ(addr,off) (*(volatile int*)(addr+off)) //macro to read the value at memory location (addr+off)

/**
 * Initialize userio module.
 *  - opens access to physical memory /dev/mem
 *  - mapps memory at offset 'PhysicalAddress' into virtual address space
 *
 *@param  fd	pointer to file descriptor (needed for later)
 *@return  address to virtual memory which is mapped to physical,
 *          or MAP_FAILED on error.
 */
unsigned char *userio_init(int *fd) //initialize userio module
{
	unsigned long int PhysicalAddress = GPIO_ADDRESS; //assign the physical memory address of the GPIO locations
	int map_len = GPIO_MAP_LEN; //the amount of memory to be assigned to GPIO
	unsigned char *pBase; //pointer to the beginning of the memory-mapped physical elements

	*fd = open( "/dev/mem", O_RDWR); //open a file with read and write permissions

	pBase = (unsigned char*)mmap(NULL, map_len, PROT_READ |
				PROT_WRITE, MAP_SHARED, *fd, (off_t)PhysicalAddress); //map the physical locations to memory

	return pBase; //return the first address
}

/**
 * Show lower 8 bits of integer value on LEDs
 *@param pBase	base address of userio
 *@param value	value to show on LEDs
 */
void userio_ledSetAll(unsigned char *pBase, int value)
{
	REG_WRITE(pBase, LED1_OFFSET, value%2);
	REG_WRITE(pBase, LED2_OFFSET, (value/2)%2);
	REG_WRITE(pBase, LED3_OFFSET, (value/4)%2);
	REG_WRITE(pBase, LED4_OFFSET, (value/8)%2);
	REG_WRITE(pBase, LED5_OFFSET, (value/16)%2);
	REG_WRITE(pBase, LED6_OFFSET, (value/32)%2);
	REG_WRITE(pBase, LED7_OFFSET, (value/64)%2);
	REG_WRITE(pBase, LED8_OFFSET, (value/128)%2);
}

/**
 * close userio module and free resources
 * -  Unmap the address mapping at 'pBase' and close the file descriptor fd
 *@param pBase	base address
 *@param fd     file descriptor to close
 */
void userio_deinit(unsigned char *pBase, int fd) //free memory used by userio_init
{
	int map_len = GPIO_MAP_LEN; //length of the memory chunk taken by GPIO
	munmap((void *)pBase, map_len); //unmap the memory
	close(fd); //close the file
}

//main function
//@return exit value
int main() //main
{
	int fd; //file descriptor
	
	// open userio module
	unsigned char *pMemBase = userio_init(&fd); //address to virtual memory which is mapped to physical (or error)
	
	if(pMemBase == MAP_FAILED) //check if user_io broke
	{
		perror("Mapping memory for absolute memory access failed -- Test Try\n"); //raise error
		return -1; //return non-zero value
	}	
	
	int value = 0; //int to represent with LEDs
	printf("Enter a value less than 256: "); //prompt
	scanf("%d", &value); //read an int to value
	printf("value = %d\n", value); //confirm input

	// Show the value on the Zedboard LEDs
	userio_ledSetAll(pMemBase, value);

	// close userio module
	userio_deinit(pMemBase, fd);

	return 0; //exit
}
