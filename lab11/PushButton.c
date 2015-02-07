/*
*@file PushButton.c
*@authors Zamir Johl and Michael Wong
*@short Allows the user to control the value of the LEDs using push-buttons
*@description This program adds the userio_PushButton function which is used to control the value of the LEDs. This value was set but the disposition of teh switches when the program starts or when the centre button is pressed. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

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

#define PBTN_UP             1
#define PBTN_RT             2
#define PBTN_DWN            4
#define PBTN_LFT            8
#define PBTN_CNT           16

#define REG_WRITE(addr, off, val) (*(volatile int*)(addr+off)=(val))
#define REG_READ(addr,off) (*(volatile int*)(addr+off))

/**
 * Initialize userio module.
 *  - opens access to physical memory /dev/mem
 *  - mapps memory at offset 'PhysicalAddress' into virtual address space
 *
 *@param  fd	pointer to file descriptor (needed for later)
 *@return  address to virtual memory which is mapped to physical,
 *          or MAP_FAILED on error.
 */
unsigned char *userio_init(int *fd)
{
	unsigned long int PhysicalAddress = GPIO_ADDRESS;
	int map_len = GPIO_MAP_LEN;
	unsigned char *pBase;

	*fd = open( "/dev/mem", O_RDWR);

	pBase = (unsigned char*)mmap(NULL, map_len, PROT_READ |
				PROT_WRITE, MAP_SHARED, *fd, (off_t)PhysicalAddress);

	return pBase;
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
void userio_deinit(unsigned char *pBase, int fd)
{
	int map_len = GPIO_MAP_LEN;
	munmap((void *)pBase, map_len);
	close(fd);
}

///set the value of a single specified LED
///@param pBase the location of the beginning of the LEDs in memory
///@param ledNR the number (0-7) of the LED to switch
///@param state whether the LED should be on (1) or off (0)
void userio_ledSet(unsigned char *pBase, unsigned int ledNr, unsigned int state) ///change the state of a single LED
{
	unsigned int ledoffset = 0x12C; ///location of the first LED in memory
	unsigned int offset = ledoffset + ledNr*4; ///each LED address is 4 more than the previous according to the #defines
	
	REG_WRITE(pBase, offset, state); ///write the state to the specified LED address
}

unsigned int userio_switchGet(unsigned char *pBase)
{
	int i;
	unsigned int swoffset = 0x14C;
	unsigned int offset;
	unsigned int state = 0;
	for(i=7; i>=0; i--)
	{
		offset = swoffset + 4*i;
		state = state << 1;
		state += REG_READ(pBase, offset);
	}
	return state;
}

unsigned int userio_pushButtonGet(unsigned char *pBase)
{
	if(REG_READ(pBase, PBTNU_OFFSET))
	{
		return PBTN_UP;
	}
	else if(REG_READ(pBase, PBTNR_OFFSET))
	{
		return PBTN_RT;
	}
	else if(REG_READ(pBase, PBTND_OFFSET))
	{
		return PBTN_DWN;
	}
	else if(REG_READ(pBase, PBTNL_OFFSET))
	{
		return PBTN_LFT;
	}
	else if(REG_READ(pBase, PBTNC_OFFSET))
	{
		return PBTN_CNT;
	}
	else
	{
		return 0;
	}
}

int main()
{
	int fd;
	
	// open userio module
	unsigned char *pMemBase = userio_init(&fd);
	
	if(pMemBase == MAP_FAILED)
	{
		perror("Mapping memory for absolute memory access failed -- Test Try\n");
		return -1;
	}	



	unsigned int initstate = userio_switchGet(pMemBase); ///Determines the state of the switches and stores the value in the initstate variable

	userio_ledSetAll(pMemBase, initstate); ///Sets the LEDs to the same state as the switches based upon the value stored in initstate
	
	unsigned int counter = initstate; ///current state = initial state
	unsigned int prev = 0; ///previous states of the buttons
	
	/**
	*Loop continues until program ends
	*When the previous state is zero, the action associated with the button pressed (first in sequential order)
	*is implemented on the counter variable and then this variable is sent to userio_ledSetAll.
	*/
	
	while(1)
	{
		unsigned int state = userio_pushButtonGet(pMemBase); ///The button being pressed is determined
		unsigned int initstate = userio_switchGet(pMemBase); ///Determines the state of the switches and stores the value in the initstate variable
		
		if(state == 1 && !prev) ///If the up button is pressed and the previous state was zero
		{
			counter++;  ///The counter is increased by one
			prev = 1;   ///The previous state is set to zero
		}
		
		else if(state == 4 && !prev) ///If the down button is pressed and the previous state was zero
		{
			counter--; ///The counter is decreased by 1
			prev = 1;  ///The previous state is set to zero
		}
		
		else if(state == 16 && !prev) ///If the centre button is pressed and the previous state was zero
		{
			counter = initstate; ///The counter is reset to the state of the switches
			prev = 1; ///The previous state is set to zero
		}

		else if(state == 0) ///If no button is pressed
		{
			prev = 0;  ///The previous state is set to zero
		}
		
		userio_ledSetAll(pMemBase, counter); ///The LEDs are set to reflect the value of the counter
	}


	/// close userio module
	userio_deinit(pMemBase, fd);

	return 0;
}
