/* =============================================================================
   Test
   v1.1 (12 March 2018)
   Description:
      Test SDCC AY38910
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxsystemvars.h"
#include "../include/msxBIOS.h"

#include "../include/memory.h"
#include "../include/textmode.h"
#include "../include/keyboard.h"
#include "../include/AY38910.h"


#define  HALT __asm halt __endasm   //wait for the next interrupt

#define PAUSE_TIME 30



// Function Declarations -------------------------------------------------------
void test1(); // test SOUND
void test2(); // test SetTonePeriod
void test3(); // test SetNoisePeriod
void test4(); // test SetVolume
void test5(); // test SetEnvelopePeriod
void test6(); // test PlayEnvelope and SetChannel

void setEnv(char envType);

void  printChannel(char chan, boolean stateTone, boolean stateNoise);

void WAIT(uint cicles);

boolean NOT(boolean value);



// constants  ------------------------------------------------------------------
const char text01[] = "Test SDCC AY38910 Lib";
const char text02[] = "v1.2 (18/06/2018)";


// global variable definition --------------------------------------------------
char _lastEnv;


// Functions -------------------------------------------------------------------


//
void main(void)
{
  COLOR(BLACK,GRAY,DARK_BLUE);      
  SCREEN1();
  WIDTH(32);
    
  test1(); // test SOUND
  test2(); // test SetTonePeriod
  test3(); // test SetNoisePeriod
  test4(); // test SetVolume
  test5(); // test SetEnvelopePeriod
  test6(); // test PlayEnvelope and SetChannel
 

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





// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
  return;
}



boolean NOT(boolean value)
{
  if (value) return false;
  return true;
}



// test SOUND
void test1()
{  
  CLS(); 

  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);
  
  LOCATE(0,4);
  PRINT(">Test SOUND function");
  LOCATE(0,6);
  PRINT(" Press a key to stop sound");

  SOUND(AY_ToneA,100);//tone period channel A (2 Bytes)
  SOUND(AY_ToneA+1,10); 
  SOUND(AY_Noise,100); //noise
  SOUND(AY_Mixer,0B00110110); //Mixer (Don't worry! The bits of the joysticks are added in the function)
  SOUND(AY_AmplA,16); //channel A envelope on
  SOUND(AY_Env,100);//envelope period (2B)
  SOUND(AY_Env+1,10); // 
  SOUND(AY_EnvTp,14); //envelope wave type
  
  INKEY();
  
  SOUND(AY_AmplA,0); //silence channel A
  SOUND(AY_EnvTp,0);
  
  WAIT(PAUSE_TIME);
}



// test SetTonePeriod
void test2()
{
  uint period=0;
  
  CLS();
  
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);
  
  LOCATE(0,4);
  PRINT(">Test SetTonePeriod function");
  LOCATE(0,6);
  PRINT(" Press space to end");
  
  LOCATE(0,8);
  PRINT(" Tone Period A:");
  
  SOUND(7,0B00111110); //Mixer
  SOUND(8,12);
  while(1)
  {
    HALT;
    
    if (GetKeyMatrix(8)!=255) break;
    
    LOCATE(16,8);
    PrintNumber(period);
    
    SetTonePeriod(0, period++);
    if (period>4094) period=0;
  
  }  
  SOUND(8,10);
  WAIT(PAUSE_TIME);
  
  LOCATE(0,9);
  PRINT(" Tone Period B:");
  period = 0;
  SOUND(7,0B00111100); //Mixer
  SOUND(9,12);
  while(1)
  {
    HALT;
    
    if (GetKeyMatrix(8)!=255) break;
    
    LOCATE(16,9);
    PrintNumber(period);
    
    SetTonePeriod(1, period++);
    if (period>4094) period=0;
  
  }  
  SOUND(9,10);
  WAIT(PAUSE_TIME);
  
  LOCATE(0,10);
  PRINT(" Tone Period C:");
  period = 0;
  SOUND(7,0B00111000); //Mixer
  SOUND(10,12);
  while(1)
  {
    HALT;
    
    if (GetKeyMatrix(8)!=255) break;
    
    LOCATE(16,10);
    PrintNumber(period);
    
    SetTonePeriod(2, period++);
    if (period>4094) period=0;
  
  }
  
  WAIT(PAUSE_TIME);
    
  SOUND(8,0);
  SOUND(9,0);
  SOUND(10,0);    

}



// Test SetNoisePeriod
void test3()
{
  byte noise=0;  
  
  CLS();
  
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);
  
  LOCATE(0,4);
  PRINT(">Test SetNoisePeriod function");
  LOCATE(0,6);
  PRINT(" Press space to end");
  LOCATE(0,8);
  PRINT(" Noise Period:");
  SOUND(7,0B00110111); //Mixer
  SOUND(8,11);
  while(1)
  {
    if (GetKeyMatrix(8)!=255) break;
    
    LOCATE(14,8);
    PrintNumber(noise);
    
    SetNoisePeriod(noise++);
    if (noise>31) noise=0;
    
    WAIT(4);  
  }
  
  WAIT(PAUSE_TIME);
  
  SOUND(8,0);
  SOUND(9,0);
  SOUND(10,0);  
  
}



// Test SetVolume
void test4()
{
  byte amp=0;
  
  CLS();
  
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);
     
  LOCATE(0,4);
  PRINT(">Test SetVolume function");
  LOCATE(0,6);
  PRINT(" Press space to end");
  
  LOCATE(0,8);
  PRINT(" Volume A:");
  SOUND(0,100);
  SOUND(1,10); //tone period
  SOUND(7,0B11110110); //Mixer > Test write to 7 AY register
  while(1)
  {    
    if (GetKeyMatrix(8)!=255) break;

    LOCATE(10,8);
    PrintNumber(amp);
    
    SetVolume(0,amp++);
    if (amp>15) amp=0;
  
    WAIT(5);
  }
  
  WAIT(PAUSE_TIME);
  
  LOCATE(0,9);
  PRINT(" Volume B:");
  amp=0;
  SOUND(2,300);
  SOUND(3,10); //tone period
  SOUND(7,0B00101101); //Mixer > Test write to 7 AY register
  while(1)
  {    
    if (GetKeyMatrix(8)!=255) break;

    LOCATE(10,9);
    PrintNumber(amp);
    
    SetVolume(1,amp++);
    if (amp>15) amp=0;
  
    WAIT(5);
  }
  
  WAIT(PAUSE_TIME);
  
  LOCATE(0,10);
  PRINT(" Volume C:");
  amp=0;
  SOUND(4,600);
  SOUND(5,10); //tone period
  SOUND(7,0B00011011); //Mixer > Test write to 7 AY register
  while(1)
  {    
    if (GetKeyMatrix(8)!=255) break;

    LOCATE(10,10);
    PrintNumber(amp);
    
    SetVolume(2,amp++);
    if (amp>15) amp=0;
  
    WAIT(5);
  }
  
  WAIT(PAUSE_TIME);
  
  SOUND(8,0);//enjoy the silence
  SOUND(9,0);
  SOUND(10,0);  
  
}


// Test SetEnvelopePeriod
void test5()
{
  uint period=0;
  byte i;  
  boolean isEnd=false;
  
  CLS();
  
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);
    
  LOCATE(0,4);
  PRINT(">Test SetEnvelopePeriod function");
  LOCATE(0,6);
  PRINT(" Press space to end");
  LOCATE(0,8);
  PRINT(" Env Period:");
  
  SOUND(0,100);
  SOUND(1,10); //tone period
  SOUND(7,0B00111110); //Mixer
  SOUND(8,16);
  SOUND(13,14);
  
  while(!isEnd)
  {
    LOCATE(12,8);
    PrintNumber(period);

    SetEnvelopePeriod(period++);
    if (period>65533) period=0;
    
    for(i=0;i<20;i++)
    {
      HALT;     
      if (GetKeyMatrix(8)!=255){isEnd=true;break;}
    }    
    //if (joytrig(0)) break;
  }
  
  SOUND(8,0);
  
  WAIT(PAUSE_TIME);
  
}



// Test PlayEnvelope and SetChannel
void test6()
{
  byte pressKey;
  boolean chanA = true;
  boolean chanB = true;
  boolean chanC = true;
  boolean noiseA = false;
  boolean noiseB = false;
  boolean noiseC = false;
  boolean keyB0semaphore = false;
  boolean keyB1semaphore = false;
  boolean keyB3semaphore = false;
  boolean keyB6semaphore = false;
  
  _lastEnv=0;
  
  CLS();
  
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);

  LOCATE(0,4);
  PRINT(">Test PlayEnvelope function");
  LOCATE(0,6);
  PRINT("Press 0-7 to fire Envelope");
  
  LOCATE(0,8);
  PRINT("           A        B        C  ");
  PRINT("      -------- -------- --------");
  LOCATE(0,10);
  PRINT("Tone :");
  LOCATE(0,11);
  PRINT("Noise:");
  
  LOCATE(0,14);
  PRINT(" 1 - \\_____\n");
  PRINT(" 2 - /|____\n");
  PRINT(" 3 - |\\|\\|\\ \n");
  PRINT(" 4 - \\/\\/\\/\n");
  PRINT(" 5 - \\|----\n");
  PRINT(" 6 - /|/|/|\n");
  PRINT(" 7 - /-----\n");
  PRINT(" 8 - /\\/\\/\\ \n");
  
  
  SetTonePeriod(0, 1000);
  SetTonePeriod(1, 1100);
  SetTonePeriod(2, 1200);
  SetVolume(0,16);
  SetVolume(1,16);
  SetVolume(2,16);
  SetEnvelopePeriod(7000);
  setEnv(7);
 
  printChannel(0, chanA,noiseA);
  printChannel(1, chanB,noiseB);
  printChannel(2, chanC,noiseC);
  
  
  while(1)  //bucle infinito
  {
    HALT;

    pressKey = GetKeyMatrix(0);      
    if (pressKey!=255)
    {
      if (!keyB0semaphore)
      {
        keyB0semaphore = true;
        //if (pressKey==0b11111110)      //0
        if (pressKey==0b11111101) setEnv(0);     //1
        if (pressKey==0b11111011) setEnv(1);     //2
        if (pressKey==0b11110111) setEnv(2);     //3
        if (pressKey==0b11101111) setEnv(3);     //4
        if (pressKey==0b11011111) setEnv(4);     //5
        if (pressKey==0b10111111) setEnv(5);     //6
        if (pressKey==0b01111111) setEnv(6);     //7
      }
    }else keyB0semaphore=false;
    
    
    pressKey = GetKeyMatrix(1);      
    if (pressKey!=255)
    {
      if (!keyB1semaphore)
      {
        keyB1semaphore = true;
        if (pressKey==0b11111110) setEnv(7);     //8
      }
    }else keyB1semaphore=false;
    
    
    pressKey = GetKeyMatrix(3);      
    if (pressKey!=255)
    {
      if (!keyB3semaphore)
      {
        keyB3semaphore = true;
        if (pressKey==0b11111101){ noiseA=NOT(noiseA);printChannel(0, chanA,noiseA);} // D
        if (pressKey==0b11110111){ noiseB=NOT(noiseB);printChannel(1, chanB,noiseB);} //F
        if (pressKey==0b11101111){ noiseC=NOT(noiseC);printChannel(2, chanC,noiseC);} //G
      }      
    }else keyB3semaphore=false;
    
    
    pressKey = GetKeyMatrix(6);      
    if (pressKey!=255)
    {
      if (!keyB6semaphore)
      {
        keyB6semaphore = true;
        if (pressKey==0b11011111){ chanA=NOT(chanA);printChannel(0, chanA,noiseA);} //F1
        if (pressKey==0b10111111){ chanB=NOT(chanB);printChannel(1, chanB,noiseB);} //F2
        if (pressKey==0b01111111){ chanC=NOT(chanC);printChannel(2, chanC,noiseC);} //F3
      }      
    }else keyB6semaphore=false;

  } //END while


}



void setEnv(char envType)
{
  LOCATE(0,14+_lastEnv);
  PRINT(" ");
  _lastEnv = envType;
  
  LOCATE(0,14+envType);
  PRINT(">");
  
  switch (envType)
  {
    case 0:      
      PlayEnvelope(ENV_LowerBeat);
      break;
    case 1:      
      PlayEnvelope(ENV_Upper);
      break;
    case 2:      
      PlayEnvelope(ENV_LeftSaw);
      break;
    case 3:      
      PlayEnvelope(ENV_LowerTriangle);
      break;
    case 4:      
      PlayEnvelope(ENV_LowerHold);
      break;
    case 5:      
      PlayEnvelope(ENV_RightSaw);
      break;
    case 6:      
      PlayEnvelope(ENV_UpperHold);
      break;
    case 7:      
      PlayEnvelope(ENV_UpperTriangle);
      break;
    
  
  }
}



void printChannel(char chan, boolean stateTone, boolean stateNoise)
{
  byte posx = (chan*9)+6;
  
  SetChannel(chan, stateTone, stateNoise);
    
  LOCATE(posx,10); 
  switch (chan)
  {
    case 1:      
      PRINT("[F2] ");
      break;
    case 2:      
      PRINT("[F3] ");
      break;
    default:
      PRINT("[F1] ");
      break;  
  }
  if (stateTone) PRINT("On ");
  else PRINT("Off");
  
  LOCATE(posx,11); 
  switch (chan)
  {
    case 1:      
      PRINT("[F]  ");
      break;
    case 2:      
      PRINT("[G]  ");
      break;
    default:
      PRINT("[D]  ");
      break;  
  }
  if (stateNoise) PRINT("On ");
  else PRINT("Off");

  return;
}


