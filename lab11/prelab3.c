///set the value of a single specified LED
///@param pBase the location of the beginning of the LEDs in memory
///@param ledNR the number (0-7) of the LED to switch
///@param state whether the LED should be on (1) or off (0)
void userio_ledSet(unsigned char *pBase, unsigned int ledNr, unsigned int state) ///change the state of a single LED
{
	unsigned int ledoffset = 0x12C ///location of the first LED in memory
	unsigned int offset = ledoffset + ledNr*4; ///each LED address is 4 more than the previous according to the #defines
	
	REG_WRITE(pBase, offset, state); ///write the state to the specified LED address
}
	
	
	