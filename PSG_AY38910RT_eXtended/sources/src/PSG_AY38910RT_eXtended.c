/* =============================================================================
# PSG_AY38910RT_eXtended

- Version: 1.0 (04/08/2025)
- Author: mvac7/303bcn
- Architecture: MSX
- Format: SDCC Relocatable object file (.rel)
- Programming language: C
- Compiler: SDCC 4.4 
- Library: fR3eL Project

##Description:  
PSG AY-3-8910 RT eXtended functions MSX SDCC Library (fR3eL Project)
Extension of the PSG_AY38910RT library.
 
Adds specific functions to make it easier to write AY parameters.
 
## History of versions (dd/mm/yyyy):
- v1.0 (04/08/2025) First version
============================================================================= */
#include "../include/PSG_AY38910RT.h"
#include "../include/PSG_AY38910RT_eXtended.h"


char AYamp_buffer[3];



/* =============================================================================
SetTonePeriod
Function:		SetTonePeriod(channel, period) 
Description:	Set Tone Period for any channel
Input:			[char] channel (0, 1 or 2)
				[unsigned int] period (0 - 4095)
Output:			-
============================================================================= */
void SetTonePeriod(char channel, unsigned int period)
{
	if (channel>2) return;
	channel=channel*2;
	SOUND(channel++,period & 0xFF);
	SOUND(channel,(period & 0xFF00)/0xFF);
}



/* =============================================================================
SetNoisePeriod
Function:		SetNoisePeriod(period) 
Description:	Set Noise Period
Input:			[char] period (0 - 31) 
Output:			-
============================================================================= */
void SetNoisePeriod(char period){
	SOUND(AY_Noise,period);
}



/* =============================================================================
SetEnvelopePeriod
Function:		SetEnvelopePeriod(period) 
Description:	Set Envelope Period
Input:			[unsigned int] period (0 - 65535) 
Output:			-
============================================================================= */
void SetEnvelopePeriod(unsigned int period){
	SOUND(AY_EnvPeriod,period & 0xFF);
	SOUND(AY_EnvPeriod+1,period>>8);	//(period & 0xFF00)/0xFF
}



/* =============================================================================
SetVolume
Function:		SetVolume(channel, volume) 
Description:	Set volume channel
Input:			[char] channel (0, 1 or 2)
				[char] volume, 0 to 15 or 16 for activate envelope
Output:			-
============================================================================= */
void SetVolume(char channel, char volume)
{
	if (channel>2) return;
	AYamp_buffer[channel]=volume;
	SOUND(AY_AmpA+channel,volume);
}



/* =============================================================================
EnableEnvelope
Function:		EnableEnvelope(channel, isEnvelope) 
Description:	Enables or disables sound envelope on a channel.
Input:			[char] channel (0, 1 or 2)
				[switcher] Envelope state (ON=enable;OFF=disable)
Output:			-
============================================================================= */
void EnableEnvelope(char channel, switcher state)
{
	char value;
	if (channel>2) return;
	if(state) value=0b00010000;
	else value=AYamp_buffer[channel];
	SOUND(AY_AmpA+channel,value);
}




/* =============================================================================
SetChannel
Function:		SetChannel(channel, isTone, isNoise)
Description:	Mixer. 
				Enables or disables Tone and Noise on channels.
Input:			[char] channel (0, 1 or 2)
				[switcher] tone state (ON=enable;OFF=disable)
				[switcher] noise state (ON=enable;OFF=disable)
Output:			-
============================================================================= */
void SetChannel(char channel, switcher isTone, switcher isNoise)
{
	char newValue;
	
	if (channel>2) return;
	
	newValue = GetSound(7);

//	if(AY_TYPE==AY_EXTERNAL) newValue = AY_reg7;
//	else newValue = GetSound(7);

	//control of the two I/O bits of register 7 is done in the SOUND function
	if(channel==0) 
	{
		if(isTone==ON){newValue&=254;}else{newValue|=1;}
		if(isNoise==ON){newValue&=247;}else{newValue|=8;}
	}
	if(channel==1)    
	{
		if(isTone==ON){newValue&=253;}else{newValue|=2;}
		if(isNoise==ON){newValue&=239;}else{newValue|=16;}
	}
	if(channel==2)
	{ 
		if(isTone==ON){newValue&=251;}else{newValue|=4;}
		if(isNoise==ON){newValue&=223;}else{newValue|=32;}
	}
	SOUND(AY_Mixer,newValue);
}



/* =============================================================================
SetEnvelope
Function:		SetEnvelope(shape) 
Description:	Set envelope shape.
				It will affect all channels that have the sound envelope active.
				Use SetVolume function to activate the sound envelope.
Input:			[char] Envelope shape (0-15) (use envelope shapes definitions)
Output:			-
============================================================================= */
void SetEnvelope(char shape)
{
	SOUND(AY_EnvShape,shape);
}

