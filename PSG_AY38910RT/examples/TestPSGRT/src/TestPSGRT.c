/* =============================================================================
Test
Test AY38910RT MSX Library (fR3eL Project)

Version: 1.5 (08/02/2025)
Author: mvac7/303bcn
Architecture: MSX
Format: MSX 16K ROM
Programming language: C and Z80 assembler
Compiler: SDCC 4.4 or newer

Description:

  
History of versions: (dd/mm/yyyy)
- v1.5 (08/02/2025) update to SDCC (4.1.12) Z80 calling conventions
- v1.4 (07/07/2021) screen changes
- v1.3 (10/05/2021) Test External AY (MEGAFLASHROM SCC+, Flashjacks or other) + new GUI
- v1.2 (18/06/2018)
- v1.1 (12/03/2018)
- v1.0 (?)
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxSystemVariables.h"
#include "../include/msxBIOS.h"

#include "../include/memory_Z80.h"
#include "../include/keyboard_MSX.h"
#include "../include/VDP_TMS9918A_MSXROM.h"
#include "../include/VDP_PRINT.h"
#include "../include/unWRLE2toVRAM.h"

#include "../include/AY38910RT.h"

#include "../include/Test_GFX.h"


#define  HALT __asm halt __endasm   //wait for the next interrupt

#define PAUSE_TIME 30



// Function Declarations -------------------------------------------------------
void test1(void); // test SOUND
void test2(void); // test SetTonePeriod
void test3(void); // test SetNoisePeriod
void test4(void); // test SetVolume
void test5(void); // test SetEnvelopePeriod
void test6(void); // test PlayEnvelope and SetChannel

void test_Noise(void);

void PLAY_EnvShape(char envType);

void WAIT(uint cicles);

void LOCATE(char x, char y) ;

void VPrintNumberO(unsigned int vaddr, unsigned int value, char length, signed char offset);

void Set_tone(char channel, uint period);
void Set_Amp(char channel, char value);
void Set_noise(char period);
void Set_mixer(char value);
void Set_EnvPeriod(uint period);
void Set_EnvShape(char shape);
void PRINTON(uint vaddr, boolean state);

//const char EnvelopeValue[8]={1,4,8,10,11,12,13,14};
const char EnvelopeIndex[16]={0,0,0,0,1,1,1,1,2,0,3,4,5,6,7,1};

// constants  ------------------------------------------------------------------
const char text01[] = "Test AY38910RT Library";
const char text02[] = "v1.5 (8 February 2025)";

const char text03[] = "                             ";

// global variable definition --------------------------------------------------



// Functions -------------------------------------------------------------------


//
void main(void)
{
	char result;
	char AYtype = 0;

	POKE(LINL32,32); //Width(32)
	COLOR(BLACK,GRAY,DARK_BLUE);      
	SCREEN(1);

	unWRLE2toVRAM16((uint) Frame_MAP,BASE5);
	unWRLE2toVRAM16((uint) GUI_G1_TSET_COL,BASE6);
	unWRLE2toVRAM16((uint) GUI_G1_TSET_PAT,BASE7);

	VLOCATE(1,1);
	VPRINT(text01);
	VLOCATE(1,2);
	VPRINT(text02);

	VLOCATE(1,8);
	VPRINT("Do you want to use the");
	VLOCATE(1,9);
	VPRINT("external AY? ([Y] for Yes)");

	LOCATE(1,10);
	result = INKEY();
  
    unWRLE2toVRAM16((uint) GUI_MAP,BASE5+96); //show screen map
  
	if (result==89 || result==121){
		AY_IOport=AY_EXTERNAL;
		AYtype++;
	}else	AY_IOport=AY_INTERNAL;

	PRINTON(0x1A6D,AYtype);
    
	test1(); // test SOUND
	test2(); // test SetTonePeriod
	test3(); // test SetNoisePeriod
	test4(); // test SetVolume
	test5(); // test SetEnvelopePeriod
	test6(); // test PlayEnvelope and SetChannel

	VPRINT(1,21,">End Test                     ");
	WAIT(250);

	unRLEWBtoVRAM((uint) Frame_MAP,BASE5);

	WAIT(100);
  
}




/* =============================================================================
 Generates a pause in the execution of n interruptions.
 PAL: 50=1second. ; NTSC: 60=1second.
============================================================================= */ 
void WAIT(uint cicles)
{
	uint i;
	for(i=0;i<cicles;i++) HALT;
	return;
}



/* =============================================================================
  LOCATE
 
  Description: 
            Moves the cursor to the specified location.
  Input:    (char) Position X of the cursor. (0 to 31 or 79)
            (char) Position Y of the cursor. (0 to 23)         
  Output:   -
============================================================================= */
void LOCATE(char x, char y) __naked
{
x;	//A
y;	//L
__asm
	push IX

	inc  A       ;incrementa las posiciones para que se situen correctamente en la pantalla
	ld   H,A
	inc  L
	call BIOS_POSIT

	pop  IX
	ret
__endasm;
}



/* =============================================================================
VPrintNumberO
Prints a number at the specified position on the screen.

Apply an offset to the tile number to be able to use a font hosted in 
another area of the tileset.

Inputs:
			[unsigned int] VRAM address in Pattern Name Table.
			[unsigned int] number
			[char] length
============================================================================= */
void VPrintNumberO(unsigned int vaddr, unsigned int value, char length, signed char offset)
{
  char pos=0; //5-length;
  //char text[]="     ";

  num2Dec16(value, 0x2000+length); 
  
  while (length-->0){ VPOKE(vaddr++,VPRINT_ntext[pos++]+offset);}
  
}




// test SOUND
void test1(void)
{
	VLOCATE(1,21);
	VPRINT(">Test SOUND function");  
	VLOCATE(1,22);
	VPRINT(" Press a key to stop sound");

	Set_tone(AY_Channel_A,1000);
	Set_tone(AY_Channel_B,0);
	Set_tone(AY_Channel_C,0);

	Set_noise(20);

	Set_Amp(AY_Channel_A,16); //channel A envelope on
	Set_Amp(AY_Channel_B,0);
	Set_Amp(AY_Channel_C,0);

	Set_mixer(0B00110110);

	Set_EnvPeriod(1000);

	Set_EnvShape(14);

	LOCATE(27,22);
	INKEY();

	Set_Amp(AY_Channel_A,0); //silence channel A  

	WAIT(PAUSE_TIME);
}



// test SetTonePeriod
void test2(void)
{
	uint period=0;

	VLOCATE(1,21);  
	VPRINT(">Test SetTonePeriod function  ");  
	VLOCATE(1,22);
	VPRINT(" Press [SPACE] to next        ");

	Set_mixer(0B00111110);
	Set_Amp(AY_Channel_A,15);
	while(1)
	{
		HALT;

		if (GetKeyMatrix(8)!=255) break;

		VPrintNumberO(0x18E6,period,4,+144); //6,7

		SetTonePeriod(AY_Channel_A, period++);
		if (period>4094) period=0;
	}  
	Set_Amp(AY_Channel_A,0);

	WAIT(PAUSE_TIME);

	period = 0;
	Set_mixer(0B00111101);
	Set_Amp(AY_Channel_B,15);
	while(1)
	{
		HALT;

		if (GetKeyMatrix(8)!=255) break;

		VPrintNumberO(0x18F0,period,4,+144); //16,7

		SetTonePeriod(AY_Channel_B, period++);
		if (period>4094) period=0;
	}  
	Set_Amp(AY_Channel_B,0);

	WAIT(PAUSE_TIME);

	period = 0;
	Set_mixer(0B00111011);
	Set_Amp(AY_Channel_C,15);
	while(1)
	{
		HALT;

		if (GetKeyMatrix(8)!=255) break;

		VPrintNumberO(0x18FB,period,4,144); //27,7

		SetTonePeriod(AY_Channel_C, period++);
		if (period>4094) period=0;
	}
	Set_Amp(AY_Channel_C,0);

	WAIT(PAUSE_TIME);  
}



// Test SetNoisePeriod
void test3(void)
{
  char noise=0;  
   
  VLOCATE(1,21);
  VPRINT(">Test SetNoisePeriod function ");
  VLOCATE(1,22);
  VPRINT(text03);
  
  Set_mixer(0B00110111); //Mixer
  Set_Amp(AY_Channel_A,15);
  test_Noise();
  
  Set_mixer(0B00100111); //Mixer
  Set_Amp(AY_Channel_B,15);
  test_Noise();
  
  Set_mixer(0B00000111); //Mixer
  Set_Amp(AY_Channel_C,15);
  test_Noise();
  
  WAIT(PAUSE_TIME);
  
  Set_Amp(AY_Channel_A,0);
  Set_Amp(AY_Channel_B,0);
  Set_Amp(AY_Channel_C,0);
}



void test_Noise(void)
{
    char i;
    
    for (i=0;i<32;i++)
    {
        //if (GetKeyMatrix(8)!=255) break;
    
        VPrintNumberO(0x19CF,i,2,144); // 15,14
    
        SetNoisePeriod(i);
        
        WAIT(10);    
    }
}



// Test SetVolume
void test4(void)
{
	char i;

	VLOCATE(1,21);
	VPRINT(">Test SetVolume function     ");
	VLOCATE(1,22);
	VPRINT(text03);

	Set_noise(10);

	Set_tone(AY_Channel_A,1000);
	Set_mixer(0B11110110);
	for(i=0;i<16;i++)
	{     
		VPrintNumberO(0x1925,i,2,144); // 5,9    
		SetVolume(AY_Channel_A,i);
		WAIT(10);
	}  
	SetVolume(AY_Channel_A,0);

	WAIT(PAUSE_TIME);


	Set_tone(AY_Channel_B,1000);
	Set_mixer(0B00101101);
	for(i=0;i<16;i++)
	{ 
		VPrintNumberO(0x192F,i,2,144); // 15,9    
		SetVolume(AY_Channel_B,i);
		WAIT(10);
	}  
	SetVolume(AY_Channel_B,0);

	WAIT(PAUSE_TIME);

	Set_tone(AY_Channel_C,1000);
	Set_mixer(0B00011011);
	for(i=0;i<16;i++)
	{  
		VPrintNumberO(0x1939,i,2,144); //25,9
		SetVolume(AY_Channel_C,i);
		WAIT(10);
	}  
	SetVolume(AY_Channel_C,0);

	WAIT(PAUSE_TIME);    
}


// Test SetEnvelopePeriod
void test5(void)
{
	uint period=0;
	char i;  
	boolean isEnd=false;

	VLOCATE(1,21);
	VPRINT(">Test SetEnvelopePeriod      ");
	VLOCATE(1,22);
	VPRINT(" Press [SPACE] to end        ");

	//LOCATE(0,8);
	//PRINT(" Env Period:");

	Set_tone(AY_Channel_A,1000);
	Set_mixer(0B00111110); //Mixer
	Set_Amp(AY_Channel_A,16);
	Set_EnvShape(14);

	while(!isEnd)
	{
		VPrintNumberO(0x1A10,period,5,144); //16,16

		SetEnvelopePeriod(period++);

		for(i=0;i<10;i++)
		{
			HALT;     
			if (!(GetKeyMatrix(8)&Bit0)){isEnd=true;break;}
		}    
		//if (joytrig(0)) break;
	}

	Set_Amp(AY_Channel_A,0);

	WAIT(PAUSE_TIME);  
}



// Test PlayEnvelope and SetChannel
void test6(void)
{  
	char i;

	boolean isEnd=false;

	VLOCATE(1,21);
	VPRINT(">Test SetEnvelope           ");
	VLOCATE(1,22);
	VPRINT(text03);

	Set_tone(AY_Channel_A,1000);
	Set_mixer(0B00111110); //Mixer
	Set_Amp(AY_Channel_A,16); //Enable sound envelope
	Set_EnvPeriod(1024);

	LOCATE(26,5);


	//while(!isEnd)
	for(i=0;i<16;i++)
	{
		PLAY_EnvShape(i);    
		WAIT(100);
	}

	Set_Amp(AY_Channel_A,0);

	WAIT(PAUSE_TIME);
}



void PLAY_EnvShape(char shape)
{
  char index;
  
  //shape = EnvelopeValue[index];
  index = EnvelopeIndex[shape]; 
  
  PlayEnvelope(shape);
  
  VPrintNumberO(0x1A30,shape,2,+144); //16,17  
  CopyToVRAM((uint) EnvelopeShapes + (index*3), 0x1A33, 3);  // 19,17
  
}



void Set_tone(char channel, uint period)
{
  uint vaddr=BASE5 + 6+(channel*10) + (7*32); //calculates the position of the numeric field
  if (channel==2) vaddr++;  // correct the position of the third column
  
  VPrintNumberO(vaddr,period,4,144);  //6+(channel*10),10
  
  channel=channel*2;
  SOUND(channel++,period & 0xFF);
  SOUND(channel,(period & 0xFF00)/0xFF);
}



void Set_Amp(char channel, char value)
{
  boolean envState;
  uint vaddr=BASE5 + 5+(channel*10) + (9*32); //calculates the position of the numeric field
  
  SOUND(8+channel,value);
  
  VPrintNumberO(vaddr,value,2,144); //5+(channel*10),12
  
  if (value&Bit4) envState=true;
  else envState=false;
  
  PRINTON(0x1927+(channel*10),envState); //Envelope     (value&Bit4)>>4

}



void Set_noise(char period)
{
    VPrintNumberO(0x19CF,period,2,144); //15,14
    SOUND(AY_Noise,period);
}



void Set_EnvPeriod(uint period)
{
  SOUND(11,period & 0xFF);
  SOUND(12,(period & 0xFF00)/0xFF);
  
  VPrintNumberO(0x1A10,period,5,144); //16,16
}



void Set_EnvShape(char shape)
{
  char index = EnvelopeIndex[shape];
    
  SOUND(AY_EnvShape,shape); //envelope wave type
  
  VPrintNumberO(0x1A30,shape,2,+144); //16,17
  CopyToVRAM((uint) EnvelopeShapes + (index*3), 0x1A33, 3); //19,17
}



void Set_mixer(char value)
{
    SOUND(AY_Mixer,value);
    
    PRINTON(0x1967,!(value&Bit0)); //tone  A
    PRINTON(0x1971,!(value&Bit1)); //tone  B
    PRINTON(0x197B,!(value&Bit2)); //tone  C
    
    PRINTON(0x1987,!(value&Bit3)); //noise A
    PRINTON(0x1991,!(value&Bit4)); //noise B
    PRINTON(0x199B,!(value&Bit5)); //noise C
    
}



void PRINTON(uint vaddr, boolean state)
{
    char value = 221;
    if(state==true) value=189;
    VPOKE(vaddr++,value++);
    VPOKE(vaddr++,value++);
    VPOKE(vaddr,value);
}



