/* =============================================================================
# PSG_AY38910RT

- Version: 1.8 (14/08/2025)
- Author: mvac7/303bcn
- Architecture: MSX
- Format: SDCC Relocatable object file (.rel)
- Programming language: C
- Compiler: SDCC 4.4 
- Library: fR3eL Project

## Description:
PSG AY-3-8910 RealTime MSX SDCC Library (fR3eL Project)

Opensource library for access to internal or external MSX PSG AY-3-8910 
in Real Time.

It does not use the BIOS so it can be used to program ROMs or 
MSX-DOS executables.
 
## History of versions (dd/mm/yyyyy):
- v1.8 (14/08/2025) Added InitAY, SilenceAY and SilenceAYbyPort functions
- v1.7 (05/02/2025) update to SDCC (4.1.12) Z80 calling conventions
- v1.6 (07/06/2021) fixes problem with reading the registers in the 
				    external AY from MEGAFLASHROM SCC++
- v1.5 (09/05/2021) External AY
- v1.4 (17/06/2018) Corrected a BUG in the SOUND function.  Sound to SOUND.
- v1.3 (11/02/2018) Revised and first publication.
- v1.1 (14/02/2014) 
============================================================================= */
#include "../include/PSG_AY38910RT.h"


//intern MSX AY
//#define AY0index 0xA0
//#define AY0write 0xA1
//#define AY0read  0xA2

//AY from MEGAFLASHROM-SCC+
//#define AY1index 0x10
//#define AY1write 0x11
//#define AY1read  0x12



//char AY_TYPE;		// 1 = External AY  Else Internal AY
char AY_IOport = AY_INTERNAL;		//new (v1.0) set default AY (first port of 3)



/* =============================================================================
InitAY
Function:		InitAY()
Description:	Initialize the library. 
				Set default AY (internal).
Input:			-
Output:			-
============================================================================= */
void InitAY(void) __naked
{
	AY_IOport = AY_INTERNAL;
}




/* =============================================================================
SOUND
Function:		SOUND(reg, value)
Description:	Writes a value into a PSG register
Input:			[char] register number (0 to 13)
				[char] value
Output:			-
============================================================================= */
void SOUND(char reg, char value) __naked
{
reg;	//A
value;		//L
__asm
  
	ld   D,A		//reg

	ld   A,(_AY_IOport)
	ld   C,A
  
//CheckReg7:  
	ld   A,D			//check if it is register 7
	cp   #7
	jr   Z,AY_setREG7	//IF not = 7 goto writeAY
 
AY_writeReg:    
	out  (C),D			//register number
	inc  C				//go to write port
	out  (C),L
	ret

AY_setREG7:
// Yes. It is PSG's 7th register.
	ld   A,L
	AND  #0b00111111	//reset the two PSG I/O bits 
	ld   L,A
	  
//	call AY_ReadReg
	out  (C),D
	inc  C
	inc  C
	in   A,(C)			//read register 7 (mixer)
	
	and  #0b11000000	//Mask to catch the two PSG I/O bits  
	or   L				//and add the new value.
	ld   L,A

	dec  C
	dec  C				//Placing in the index port

	jp   AY_writeReg

__endasm;  
}

    


/* =============================================================================
GetSound
Function:		GetSound(reg)
Description:	Read PSG register value.
				ATTENTION! This function does not work with the MAGAFLASHROM SCC+
				because the PSG has not implemented the reading of the registers. 
Input:			[char] register number (0 to 13)
Output:			[char] value 
============================================================================= */
char GetSound(char reg) __naked
{
reg;	//A
__asm
	ld   D,A

	ld   A,(_AY_IOport)	//AY index port (Internal or External AY)
	ld   C,A
  
AY_ReadReg:  
	out  (C),D
	inc  C
	inc  C				//Placing in the read port
	in   A,(C) 

	ret  
__endasm;
}



/* =============================================================================
SilenceAY
Function:		SilenceAY()
Description:	Silences selected AY sound processor.
Input:			[char] AY index port
Output:			-
============================================================================= */
void SilenceAY(void)
{
	SilenceAYbyPort(AY_IOport);
}



/* =============================================================================
SilenceAYbyPort
Function:		SilenceAYbyPort(port)
Description:	Silences the indicated AY sound processor.
				Set to zero the amplitude value by writing directly to the AY 
				registers.
				This is indicated for the case of playing sound dynamically 
				between AYs (Internal/External), so that the last written 
				values ​​do not sound infinitely.
Input:			[char] AY index port
Output:			-
============================================================================= */
void SilenceAYbyPort(char port) __naked
{
port;		//A
__asm
	ld   E,A	//AY index port (Internal or External AY)
	ld   D,#AY_AmpA
	xor  A
	
	ld   B,#3
AY_ampLOOP:
	ld   C,E	//set AY index port
	out  (C),D	//AY register
	inc  C		//go to AY write port
	out  (C),A	//write to AY reg
	inc  D
	djNZ AY_ampLOOP
	ret
__endasm;	
}
