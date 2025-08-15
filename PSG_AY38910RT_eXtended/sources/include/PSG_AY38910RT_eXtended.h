/* =============================================================================
PSG_AY38910BF_eXtended
PSG AY-3-8910 Buffer eXtended functions MSX SDCC Library (fR3eL Project)
============================================================================= */
#ifndef  __AY38910RT_Xfunc_H__
#define  __AY38910RT_Xfunc_H__





#ifndef _SWITCHER
#define _SWITCHER
	typedef enum {OFF = 0, ON = 1} switcher;
#endif




/* =============================================================================
SetTonePeriod
Function:		SetTonePeriod(channel, period) 
Description:	Set Tone Period for any channel
Input:			[char] channel (0, 1 or 2)
				[unsigned int] period (0 - 4095)
Output:			-
============================================================================= */
void SetTonePeriod(char channel, unsigned int period);



/* =============================================================================
SetNoisePeriod
Function:		SetNoisePeriod(period) 
Description:	Set Noise Period
Input:			[char] period (0 - 31) 
Output:			-
============================================================================= */
void SetNoisePeriod(char period);



/* =============================================================================
SetEnvelopePeriod
Function:		SetEnvelopePeriod(period) 
Description:	Set Envelope Period
Input:			[unsigned int] period (0 - 65535) 
Output:			-
============================================================================= */
void SetEnvelopePeriod(unsigned int period);



/* =============================================================================
SetVolume
Function:		SetVolume(channel, volume) 
Description:	Set volume channel
Input:			[char] channel (0, 1 or 2)
				[char] volume, 0 to 15 or 16 for activate envelope
Output:			-
============================================================================= */
void SetVolume(char channel, char volume);



/* =============================================================================
EnableEnvelope
Function:		EnableEnvelope(channel, isEnvelope) 
Description:	Enables or disables sound envelope on a channel.
Input:			[char] channel (0, 1 or 2)
				[switcher] Envelope state (ON=enable;OFF=disable)
Output:			-
============================================================================= */
void EnableEnvelope(char channel, switcher state);



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
void SetChannel(char channel, switcher isTone, switcher isNoise);



/* =============================================================================
SetEnvelope
Function:		SetEnvelope(shape) 
Description:	Set envelope shape.
				It will affect all channels that have the sound envelope active.
				Use SetVolume function to activate the sound envelope.
Input:			[char] Envelope shape (0-15) (use envelope shapes definitions)
Output:			-
============================================================================= */
void SetEnvelope(char shape);




#endif