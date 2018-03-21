/* =============================================================================
   AY38910.c                                                             
   v1.3 (11 March 2018)
                                                                       
   Description                                                              
     Opensource library for acces to PSG AY-3-8910
     It does not use the BIOS so it can be used to program ROMs or 
     MSX-DOS executables.
============================================================================= */
#include "../include/AY38910.h"

//intern MSX AY
#define AY0index 0xA0
#define AY0write 0xA1
#define AY0read  0xA2

//AY from MEGAFLASHROM-SCC+
//#define AY1index 0x10
//#define AY1write 0x11
//#define AY1read  0x12



/* =============================================================================
 Sound(register, value)

 Function : Write into a register of PSG
 Input    : [char] register number (0 to 13)
            [char] value
 Output   : -
============================================================================= */
void Sound(char reg, char value){
reg;value;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   C,4(ix)
  ld   B,5(ix)
  
  ;control del registro 7
  ld   A,B
  cp   #7   ;IF reg=7
  jr   NZ,writeAY      ;NO  
  ;YES
  ld   A,#7
  out  (#AY0index),A
  in   A,(#AY0read)
  
  and	 #0b11000000	; Mascara para coger dos bits de joys 
	or	 B		        ; Añado Byte de B
  ld   B,A

writeAY:
  ld   A,C    
  out  (#AY0index),A
  ld   A,B
  out  (#AY0write),A

  pop  IX
__endasm;  
}


    


/* =============================================================================
 GetSound(register) 

 Function : Read PSG register value
 Input    : [char] register number (0 to 13)
 Output   : [char] value 
============================================================================= */
char GetSound(char reg){
reg;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   A,4(ix)
  out  (#AY0index),A
  in   A,(#AY0read)
  
  ld   L,A
  
  pop  IX  
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
  Sound(channel++,period & 0xFF);
  Sound(channel,(period & 0xFF00)/0xFF);
  return;
}



/* =============================================================================
 SetNoisePeriod(period) 

 Function : Set Noise Period
 Input    : [char] Noise period (0 - 31) 
 Output   : - 
============================================================================= */
void SetNoisePeriod(char period){
  Sound(6,period);
  return;
}



/* =============================================================================
 SetEnvelopePeriod(period) 

 Function : Set Envelope Period
 Input    : [unsigned int] Envelope period (0 - 65535) 
 Output   : - 
============================================================================= */
void SetEnvelopePeriod(unsigned int period){
  Sound(11,period & 0xFF);
  Sound(12,(period & 0xFF00)/0xFF);
  return;
}



/* =============================================================================
 SetVolume(channel, volume) 

 Function : Set volume channel
 Input    : [char] channel (0, 1 or 2)
            [char] volume, 0 to 15 or 16 for activate envelope
 Output   : -
============================================================================= */
void SetVolume(char channel, char volume){
  Sound(8+channel,volume);
  return;
}



/* =============================================================================
 SetChannel(channel, isTone, isNoise)

 Function : Mixer. Enable/disable Tone and Noise channels.
 Input    : [char] channel (0, 1 or 2)
            [boolean] tone state
            [boolean] noise state
 Output   : -
============================================================================= */
void SetChannel(char channel, boolean isTone, boolean isNoise)
{
  char newValue=0;
  newValue = GetSound(7); 
  //el control de los dos bits de I/O del registro 7 
  //se hace en la función Sound
  if(channel==0) 
  {
      if(isTone==true){newValue&=254;}else{newValue|=1;}
      if(isNoise==true){newValue&=247;}else{newValue|=8;}
  }
  if(channel==1)    
  {
      if(isTone==true){newValue&=253;}else{newValue|=2;}
      if(isNoise==true){newValue&=239;}else{newValue|=16;}
  }
  if(channel==2)
  { 
      if(isTone==true){newValue&=251;}else{newValue|=4;}
      if(isNoise==true){newValue&=223;}else{newValue|=32;}
  }
  Sound(7,newValue);
  return;
}



/* =============================================================================
 PlayEnvelope(shape) 

 Function : Set envelope type.
            Plays the sound on channels that have a volume of 16.
 Input    : [char] Envelope shape (0-15) (see envelope shapes definitions)
 Output   : -
============================================================================= */
void PlayEnvelope(char shape){
  Sound(13,shape);
  return;
}




/*  
// DUMP 

;buffer to intern AY fast copy  ####################
_RAM2PSG::
  ld HL,#AY0_RAM
  call RAM2AY0
  ret


;RAM2PSG fast copy  ####################
RAM2AY0:
  ;internal PSG
  xor A	
	ld BC,#0x0DA1  ;0D=13 > num de regs; A1 > port
ILOOP:
  out (#0xA0),A
  inc A
  outi  
  JR NZ,ILOOP
  
  ;Envelope wave (reg 13)    
  ld A,(HL)
  cp #0  
  ret Z
  
  dec A  ;el valor esta incrementado para usar 0 como nulo
  ld E,A
  ld D,#13
  jp SET_SND_PSG  ;si no es 0, dispara la envolvente

*/




/*

; recoge los datos del instrumento y lo copia al buffer de registros   
SET_REGS:

  call GET_DRUM ;A = drum number; output IX mem addr
  
  ld A,2(IX)
  ld 4(IY),A
  
  ld A,3(IX)
  ld 5(IY),A
  
  ld A,4(IX)
  ld 6(IY),A
  
  ld 10(IY),#16 ;envelope on
  
  ld A,5(IX)
  ld 11(IY),A
  
  ld A,6(IX)
  ld 12(IY),A
  
  ld 13(IY),#1 ;envelope on wave 0

  ;mixer reg7
  ld B,#0b00111111 ;todos los canales desactivados
      
  ld A,(IX)   ;is tone
  cp #0
  call NZ,TONE_C_ON 
  
  ld A,1(IX)
  cp #0
  call NZ,NOISE_C_ON  
                      
  ;leer registro 7 y sumar valor de A, 
  ; ultimos dos bits son de control de puertos del joystick 
  ld	A,#7
	call GET_SND_PSG	  ; Lectura del R7, resultado en A
	and	#0b11000000	; Mascara para coger dos bits de joys 
	or	B		        ; Añado Byte de B
	
  ld 7(IY),A  ;ld (IY+7),A   
  
  ret




NOISE_C_ON:
  res 5,B
  ret

*/


