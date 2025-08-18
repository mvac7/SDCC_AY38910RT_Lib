/* =============================================================================
# Example01

- Architecture: MSX
- Format: 8K ROM
- Compiler: SDCC 4.4

## Description:
	Simple example of the PSG_AY38910RT Library (fR3eL Project)
============================================================================= */
#include "PSG_AY38910RT.h"

#define  HALT	 __asm halt __endasm

void main(void)
{
	unsigned int time = 10*50;					//10 seconds in PAL
	unsigned int tone = 1000;
	unsigned int envPeriod = 700;
	
	InitAY();    								//Init library. Set default AY (internal) 
	
	SOUND(AY_ToneA_fine,tone&0xFF);				//Set channel A fine tune period (8b)
	SOUND(AY_ToneA_coarse,tone>>8);				//Set channel A coarse tune period (4b)
	SOUND(AY_Noise,20);							//Set noise period
	SOUND(AY_AmpA,16);							//Enable envelope
	SOUND(AY_Mixer,0B00110110);					//Enable Tone and Noise in channel A
	SOUND(AY_EnvPeriod_fine,envPeriod&0xFF);	//Set fine tune envelope period (8b)
	SOUND(AY_EnvPeriod_coarse,envPeriod>>8);	//Set coarse tune envelope period (8b)
	SOUND(AY_EnvShape,AY_ENV_UpperTriangle);	//Set envelope shape
		
	while(time-->0) HALT;						//wait 10secs.
}
