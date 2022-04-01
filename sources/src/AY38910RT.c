/* =============================================================================
   PSG AY-3-8910 RT MSX SDCC Library (fR3eL Project)
   Version: 1.6 (07/06/2021)
   Author: mvac7
   Architecture: MSX
   Format: C Object (SDCC .rel)
   Programming language: C and Z80 assembler

   Description:                                                              
     Opensource library for access to internal or external MSX PSG AY-3-8910 
     in Real Time.
     
     It does not use the BIOS so it can be used to program ROMs or 
     MSX-DOS executables.
     
   History of versions:
    v1.6 (07/06/2021) fixes problem with reading the registers in the 
                      external AY from MEGAFLASHROM SCC++
    v1.5 (09/05/2021) External AY
    v1.4 (17/06/2018) Corrected a BUG in the SOUND function.  Sound to SOUND.
    v1.3 (11/02/2018) Revised and first publication.
    v1.1 (14/02/2014) 
============================================================================= */
#include "../include/AY38910RT.h"


//intern MSX AY
#define AY0index 0xA0
//#define AY0write 0xA1
//#define AY0read  0xA2

//AY from MEGAFLASHROM-SCC+
#define AY1index 0x10
//#define AY1write 0x11
//#define AY1read  0x12



char AY_TYPE;      // 1 = External AY  Else Internal AY

char AY_reg7;
//char AYREGS[14];



/* =============================================================================
 SOUND(register, value)

 Function : Write into a register of PSG
 Input    : [char] register number (0 to 13)
            [char] value
 Output   : -
============================================================================= */
void SOUND(char reg, char value) __naked
{
reg;value;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   E,4(IX) ;reg
  ld   D,5(IX) ;value
  
  ld   C,#AY0index       ;default AY (intern)
  
  ld   A,(#_AY_TYPE)
  cp   #1
  jr   NZ,CheckReg7
  
  ld   C,#AY1index     ;set extern AY
  ld   A,E             ;check if it is register 7
  cp   #7              ;
  jr   NZ,writeAY      ;IF not = 7 goto writeAY
  ld   A,D
  ld   (#_AY_reg7),A  ; save value in variable for extern AY
  jr   writeAY

CheckReg7:  
  ld   A,E             ;check if it is register 7
  cp   #7              ;
  jr   NZ,writeAY      ;IF not = 7 goto writeAY
  
; Yes
  ld   A,D
  AND  #0b00111111     ;reset the two PSG I/O bits 
  ld   D,A
      
  ld   A,#7
  out  (C),A
  inc  C
  inc  C            ; the reading port is positioned 
  in   A,(C)  
  and  #0b11000000	; Mask to catch the two PSG I/O bits  
  or   D		    ; and add the new value.
  ld   D,A
  
  dec  C            ; go back to index port
  dec  C
  
writeAY:    
  out  (C),E        ; register number
  inc  C            ; go to write port
  out  (C),D

  pop  IX
  ret
__endasm;  
}

    


/* =============================================================================
 GetSound(register)
 
 NOTICE! This function does not work with the MAGAFLASHROM SCC+
         because the PSG has not implemented the reading of the registers. 

 Function : Read PSG register value
 Input    : [char] register number (0 to 13)
 Output   : [char] value 
============================================================================= */
char GetSound(char reg) __naked
{
reg;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   C,#AY0index       ;default AY (intern)
  
  ld   A,(#_AY_TYPE)
  cp   #1
  jr   NZ,ReadAYreg
  ld   C,#AY1index       ;set extern AY

ReadAYreg:  
  ld   A,4(IX)
  out  (C),A
  inc  C
  inc  C            ; the reading port is positioned
  in   L,(C)
  
  pop  IX
  ret  
__endasm;
}



/* =============================================================================
 SetTonePeriod(channel, period) 

 Function : Set Tone Period for any channel
 Input    : [char] channel (0, 1 or 2)
            [unsigned int] period (0 - 4095)
 Output   : -
============================================================================= */
void SetTonePeriod(char channel, unsigned int period){
  channel=channel*2;
  SOUND(channel++,period & 0xFF);
  SOUND(channel,(period & 0xFF00)/0xFF);
}



/* =============================================================================
 SetNoisePeriod(period) 

 Function : Set Noise Period
 Input    : [char] Noise period (0 - 31) 
 Output   : - 
============================================================================= */
void SetNoisePeriod(char period){
  SOUND(6,period);
}



/* =============================================================================
 SetEnvelopePeriod(period) 

 Function : Set Envelope Period
 Input    : [unsigned int] Envelope period (0 - 65535) 
 Output   : - 
============================================================================= */
void SetEnvelopePeriod(unsigned int period){
  SOUND(11,period & 0xFF);
  SOUND(12,(period & 0xFF00)/0xFF);
}



/* =============================================================================
 SetVolume(channel, volume) 

 Function : Set volume channel
 Input    : [char] channel (0, 1 or 2)
            [char] volume, 0 to 15 or 16 for activate envelope
 Output   : -
============================================================================= */
void SetVolume(char channel, char volume){
  SOUND(8+channel,volume);
}



/* =============================================================================
 SetChannel(channel, isTone, isNoise)

 Function : Mixer. Enable/disable Tone and Noise channels.
 Input    : [char] channel (0, 1 or 2)
            [SWITCHER] tone state (ON=1;OFF=0)
            [SWITCHER] noise state (ON=1;OFF=0)
 Output   : -
============================================================================= */
void SetChannel(char channel, SWITCHER isTone, SWITCHER isNoise)
{
  char newValue;
  
  if(AY_TYPE==AY_EXTERNAL) newValue = AY_reg7;
  else newValue = GetSound(7);
   
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
  SOUND(7,newValue);
}



/* =============================================================================
 PlayEnvelope(shape) 

 Function : Set envelope type.
            Plays the sound on channels that have a volume of 16.
 Input    : [char] Envelope shape (0-15) (see envelope shapes definitions)
 Output   : -
============================================================================= */
void PlayEnvelope(char shape){
  SOUND(13,shape);
}







