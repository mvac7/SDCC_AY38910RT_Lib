/* =============================================================================
# Example02

- Architecture: MSX
- Format: 8K ROM
- Compiler: SDCC 4.4

## Description:
	Simple example of the PSG_AY38910RT + PSG_AY38910RT_eXtended Libraries 
	(fR3eL Project)
============================================================================= */
#include "PSG_AY38910RT.h"
#include "PSG_AY38910RT_eXtended.h"

#define  HALT	 __asm halt __endasm



// WF: Cosine Unsigned Length=32 Min=4 Max=12 Phase=0 Freq=1
const char InstrEnvelop[]={
0x0C,0x0C,0x0C,0x0B,0x0B,0x0A,0x09,0x09,0x08,0x07,0x06,0x06,0x05,0x05,0x04,0x04};

//0=Silent;1=C;2=C#;3=D;4=D#;5=E;6=F;7=F#;8=G;9=G#;10=A;11=A#;12=B
const char pattern00[]={
	1,1,0,1,1,0,3,4,
	1,1,0,1,1,0,5,4};

//tone period by note (0-11) octave 1
const unsigned int toneFreqz[]={
0,
0x06AE,0x064E,0x05F4,0x059E,0x054D,0x0501,0x04B9,0x0475,0x0435,0x03F9,0x03C0,0x038A};	//octave 1
//0x0357,0x0327,0x02FA,0x02CF,0x02AF,0x0281,0x025D,0x023B,0x021B,0x01FC,0x01E0,0x01C5};	//Octave 2



void SetKick(void);
void SetHihat(void);



void main(void)
{
	char frame=0;
	char step=0;
	char track=0;
	char note=0;

		
	InitAY();    						//Init library. Set default AY (internal) 
	//AY_IOport=AY_EXTERNAL;			//uncomment for test extern AY
	
	SetNoisePeriod(4);					//Set noise period

	SetChannel(AY_Channel_A,ON,OFF);	//Enable Tone and Noise in channel A

	EnableEnvelope(AY_Channel_C,ON);
	SetTonePeriod(AY_Channel_C, 0x0D5D);	//Set channel A tone period	(C note · Octave 0)

	//8 tracks; 16 steps
	while(track<8)
	{
		HALT;
		
		if(frame==0)
		{
			//Play Drums in chanel C
			if((step&0b00000011)==0) SetKick();		//0,4,8,12
			if((step&0b00000011)==2) SetHihat();	//2,6,10,14

			//Play tone in channel A
			note=pattern00[step];
			if(note==0) SetVolume(AY_Channel_A,0);
			else SetTonePeriod(AY_Channel_A, toneFreqz[note]);	//Set channel A tone period
				
			step++;
			if(step>15){step=0;track++;}
		}
		
		if(note>0) SetVolume(AY_Channel_A,InstrEnvelop[frame]);
		
		frame++;
		if(frame>15) frame=0;		
	}
	//SilenceAY();						//Stop any sound!
}



void SetKick(void)
{
	SetEnvelopePeriod(1024);
	SetChannel(AY_Channel_C,ON,OFF);			//Enable Tone and Noise in channel C
	SetEnvelope(AY_ENV_LowerBeat);
}



void SetHihat(void)
{
	SetEnvelopePeriod(808);
	SetChannel(AY_Channel_C,OFF,ON);			//Enable Tone and Noise in channel C
	SetEnvelope(AY_ENV_LowerBeat);
}