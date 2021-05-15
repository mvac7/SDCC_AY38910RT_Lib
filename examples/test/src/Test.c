/* =============================================================================
   Test
   v1.3 (10 May 2021)
   
   Description:
      PSG AY-3-8910 MSX SDCC Library (from fR3eL Project)
      
   History of versions:
     v1.3 (10 May 2021) Test External AY (MEGAFLASHROM SCC+) + new GUI
     v1.2 (18/06/2018)
     v1.1 (12 March 2018)
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxSystemVariables.h"
#include "../include/msxBIOS.h"

#include "../include/memory.h"
#include "../include/keyboard.h"
#include "../include/VDP_TMS9918A_MSXROM.h"
#include "../include/VDP_PRINT.h"
#include "../include/AY38910.h"
#include "../include/unRLEWBtoVRAM.h"

#include "../include/Test_GFX.h"


#define  HALT __asm halt __endasm   //wait for the next interrupt

#define PAUSE_TIME 30



// Function Declarations -------------------------------------------------------
void test1(); // test SOUND
void test2(); // test SetTonePeriod
void test3(); // test SetNoisePeriod
void test4(); // test SetVolume
void test5(); // test SetEnvelopePeriod
void test6(); // test PlayEnvelope and SetChannel

void test_Noise();

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
const char text01[] = "Test SDCC AY-3-8910 Library";
const char text02[] = "v1.3 (10/May/2021)";


// global variable definition --------------------------------------------------



// Functions -------------------------------------------------------------------


//
void main(void)
{
  char result;
  
  POKE(LINL32,32); //Width(32)
  COLOR(BLACK,GRAY,DARK_BLUE);      
  SCREEN(1);
  
  unRLEWBtoVRAM((uint) Frame_MAP,BASE5);
  unRLEWBtoVRAM((uint) GUI_G1_TSET_COLOR,BASE6);
  unRLEWBtoVRAM((uint) GUI_G1_TSET,BASE7);
  
  VPRINT(1,1,text01);
  VPRINT(1,2,text02);
  
  VPRINT(1,8,"Do you want to use the");
  VPRINT(1,9,"external AY? ([Y] for Yes)");
  
  LOCATE(1,10);
  result = INKEY();
  
  if (result==89 || result==121) isAYextern=true;  //<<--- Extern AY ON
  else isAYextern=false;                           //<<--- Extern AY OFF
  
  unRLEWBtoVRAM((uint) GUI_MAP,BASE5+96); //show screen map
  
  PRINTON(0x1ACD,isAYextern);
    
  test1(); // test SOUND
  test2(); // test SetTonePeriod
  test3(); // test SetNoisePeriod
  test4(); // test SetVolume
  test5(); // test SetEnvelopePeriod
  test6(); // test PlayEnvelope and SetChannel
 
  unRLEWBtoVRAM((uint) Frame_MAP,BASE5);
  
  WAIT(50);
  
//EXIT MSXDOS
/*  screen(0);
    
__asm
 	ld b,4(ix)
	ld c,#0x62
	call 5 
__endasm;*/
//end EXIT

  return;
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
x;y;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   A,4(IX) ;x
  inc  A       ;incrementa las posiciones para que se situen correctamente en la pantalla
  ld   H,A
  ld   A,5(IX) ;y
  inc  A
  ld   L,A   
  call POSIT
  
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
  char pos=5-length;
  char text[]="     ";

  num2Dec16(value, text); 
  
  while (length-->0){ VPOKE(vaddr++,text[pos++]+offset);}
  
}




// test SOUND
void test1()
{  
 
  VPRINT(1,4,">Test SOUND function");  
  VPRINT(1,5," Press a key to stop sound");

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
  
  LOCATE(27,5);
  INKEY();
  
  Set_Amp(AY_Channel_A,0); //silence channel A  
  
  WAIT(PAUSE_TIME);
}



// test SetTonePeriod
void test2()
{
  uint period=0;
  
  VPRINT(1,4,">Test SetTonePeriod function  ");  
  VPRINT(1,5," Press [SPACE] to next        ");
  
  Set_mixer(0B00111110);
  Set_Amp(AY_Channel_A,15);
  while(1)
  {
    HALT;
    
    if (GetKeyMatrix(8)!=255) break;
    
    VPrintNumberO(0x1946,period,4,+144); //6,10
    
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
    
    VPrintNumberO(0x1950,period,4,+144); //16,10
    
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
    
    VPrintNumberO(0x195A,period,4,144); //27,10
    
    SetTonePeriod(AY_Channel_C, period++);
    if (period>4094) period=0;
  
  }
  Set_Amp(AY_Channel_C,0);
  
  WAIT(PAUSE_TIME);
  
}



// Test SetNoisePeriod
void test3()
{
  char noise=0;  
   
  VPRINT(1,4,">Test SetNoisePeriod function ");
  VPRINT(1,5,"                              ");
  
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



void test_Noise()
{
    char i;
    
    for (i=0;i<32;i++)
    {
        //if (GetKeyMatrix(8)!=255) break;
    
        VPrintNumberO(0x1A2F,i,2,144); // 15,17
    
        SetNoisePeriod(i);
        
        WAIT(10);    
    }
}



// Test SetVolume
void test4()
{
  char i;

  VPRINT(1,4,">Test SetVolume function     ");
  VPRINT(1,5,"                             ");
  
  Set_noise(10);
  
  Set_tone(AY_Channel_A,1000);
  Set_mixer(0B11110110);
  for(i=0;i<16;i++)
  {     
    VPrintNumberO(0x1985,i,2,144); // 5,12    
    SetVolume(AY_Channel_A,i);
    WAIT(10);
  }  
  SetVolume(AY_Channel_A,0);
  
  WAIT(PAUSE_TIME);
  

  Set_tone(AY_Channel_B,1000);
  Set_mixer(0B00101101);
  for(i=0;i<16;i++)
  { 
    VPrintNumberO(0x198F,i,2,144); // 15,12    
    SetVolume(AY_Channel_B,i);
    WAIT(10);
  }  
  SetVolume(AY_Channel_B,0);
  
  WAIT(PAUSE_TIME);
  
  Set_tone(AY_Channel_C,1000);
  Set_mixer(0B00011011);
  for(i=0;i<16;i++)
  {  
    VPrintNumberO(0x1999,i,2,144); //25,12
    SetVolume(AY_Channel_C,i);
    WAIT(10);
  }  
  SetVolume(AY_Channel_C,0);
  
  WAIT(PAUSE_TIME);
    
}


// Test SetEnvelopePeriod
void test5()
{
  uint period=0;
  char i;  
  boolean isEnd=false;
  
  VPRINT(1,4,">Test SetEnvelopePeriod      ");
  VPRINT(1,5," Press [SPACE] to end        ");
  
  //LOCATE(0,8);
  //PRINT(" Env Period:");
  
  Set_tone(AY_Channel_A,1000);
  Set_mixer(0B00111110); //Mixer
  Set_Amp(AY_Channel_A,16);
  Set_EnvShape(14);
  
  while(!isEnd)
  {
    VPrintNumberO(0x1A70,period,5,144); //16,19,period,4);

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
void test6()
{  
  char i;
  //env_Index = 0;
  //char keyvalue;
  
  boolean isEnd=false;
    
  VPRINT(1,4,">Test PlayEnvelope           ");
  VPRINT(1,5,"                             ");
  
  Set_tone(AY_Channel_A,1000);
  Set_mixer(0B00111110); //Mixer
  Set_Amp(AY_Channel_A,16); //Enable sound envelope
  Set_EnvPeriod(1024);
   
  LOCATE(26,5);
  
    
 //while(!isEnd)
  for(i=0;i<16;i++)
  {
    PLAY_EnvShape(i);    
    //env_Index++;
    //if(env_Index>7) env_Index=0;
    //keyvalue = INKEY();
    //if (INKEY()==27) isEnd=true;
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
  
  VPrintNumberO(0x1A90,shape,2,+144);    
  CopyToVRAM((uint) EnvelopeShapes + (index*3), 0x1A93, 3);
  
}





void Set_tone(char channel, uint period)
{
  uint vaddr=BASE5 + 6+(channel*10) + (10*32);
   
  VPrintNumberO(vaddr,period,4,144);  //6+(channel*10),10
  
  channel=channel*2;
  SOUND(channel++,period & 0xFF);
  SOUND(channel,(period & 0xFF00)/0xFF);
}



void Set_Amp(char channel, char value)
{
  boolean envState;
  uint vaddr=BASE5 + 5+(channel*10) + (12*32); 
  
  SOUND(8+channel,value);
  
  VPrintNumberO(vaddr,value,2,144); //5+(channel*10),12
  
  if (value&Bit4) envState=true;
  else envState=false;
  
  PRINTON(0x1987+(channel*10),envState); //Envelope     (value&Bit4)>>4

}



void Set_noise(char period)
{
    VPrintNumberO(0x1A2F,period,2,144); //15,17
    SOUND(AY_Noise,period);
}



void Set_EnvPeriod(uint period)
{
  SOUND(11,period & 0xFF);
  SOUND(12,(period & 0xFF00)/0xFF);
  
  VPrintNumberO(0x1A70,period,5,144); //16,19,period,4);
}



void Set_EnvShape(char shape)
{
  char index = EnvelopeIndex[shape];
    
  SOUND(AY_EnvShape,shape); //envelope wave type
  
  VPrintNumberO(0x1A90,shape,2,+144); //16,20
  CopyToVRAM((uint) EnvelopeShapes + (index*3), 0x1A93, 3);
}



void Set_mixer(char value)
{
    SOUND(AY_Mixer,value);
    
    PRINTON(0x19C7,!(value&Bit0)); //tone  A
    PRINTON(0x19D1,!(value&Bit1)); //tone  B
    PRINTON(0x19DB,!(value&Bit2)); //tone  C
    
    PRINTON(0x19E7,!(value&Bit3)); //noise A
    PRINTON(0x19F1,!(value&Bit4)); //noise B
    PRINTON(0x19FB,!(value&Bit5)); //noise C
    
}



void PRINTON(uint vaddr, boolean state)
{
    char value = 221;
    if(state==true) value=189;
    VPOKE(vaddr++,value++);
    VPOKE(vaddr++,value++);
    VPOKE(vaddr,value);
}



