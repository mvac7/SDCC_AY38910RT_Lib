# SDCC C PSG AY38910 Functions Library (object type)

Version: v1.3 (11 March 2018)

Author: mvac7/303bcn

Architecture: MSX

Format: C Object (SDCC .rel)

Programming language: C

WEB: 

mail: mvac7303b@gmail.com



Doc version: 1.0.1 (11 March 2018) 

## Document changes

- 1.0.1:
    + Reviewed text.
- 1.0: 
    + Initial version.


## 1. Introduction:

This project is an opensource library (object type), with basic functions for 
work with PSG AY-3-8910 or compatible. 

Designed for developing MSX applications using Small Device C Compiler (SDCC).
  
It does not use the BIOS so it can be used to program both ROMs or MSX-DOS
executables.
  
Reading or writing to the PSG is done through calls to the assigned ports. 
In most of the known MSX the following are used: 0xA0, 0xA1 and 0xA2. 
If you want to use this library for a different architecture, you will have to 
change these assignments found at the start of the AY38910.c sources.

In the header file there is a definition of boolean type, need for the functions.
This type uses the values "true" or "false" in lowercase, which equals 1 and 0 
respectively.  

                           


## 2. Acknowledgments
  
Thanks for Info & help, to:

* Avelino Herrera > http://msx.atlantes.org/index_es.html
* Nerlaska > http://albertodehoyonebot.blogspot.com.es
* Fubu > http://www.gamerachan.org/fubu/
* Marq/Lieves!Tuore > http://www.kameli.net/lt/
* Sapphire/Z80ST > http://z80st.auic.es/
* Pentacour > http://pentacour.com/
* JamQue/TPM > http://www.thepetsmode.com/
* Andrear > http://andrear.altervista.org/home/msxsoftware.php
* Konamiman > https://www.konamiman.com
* MSX Assembly Page > http://map.grauw.nl/resources/msxbios.php
* Portar MSX Tech Doc > http://nocash.emubase.de/portar.htm
* MSX Resource Center > http://www.msx.org/
* Karoshi MSX Community > http://karoshi.auic.es/
* BlueMSX >> http://www.bluemsx.com/
* OpenMSX >> http://openmsx.sourceforge.net/
* Meisei  >> ?



## 3. Requirements:

Small Device C Compiler (SDCC) v3.6  

http://sdcc.sourceforge.net/
     


## 4 Constants


### 4.1 Envelope shapes

The header file defines envelope shapes in case you prefer to use it instead 
of the numerical form:
  
* ENV_LowerBeat      0 
* ENV_Upper          4 
* ENV_LeftSaw        8
* ENV_LowerTriangle 10 
* ENV_LowerHold     11 
* ENV_RightSaw      12
* ENV_UpperHold     13
* ENV_UpperTriangle 14


  
## 5 Functions


* Sound(register, value) - Write into a register of PSG
* GetSound(register) - Read PSG register value
* SetTonePeriod(channel, period) - Set Tone Period for any channel
* SetNoisePeriod(period) - Set Noise Period
* SetEnvelopePeriod(period) - Set Envelope Period
* SetVolume(channel, volume) - Set volume channel
* SetChannel(channel, isTone, isNoise) - Mixer. Enable/disable Tone and Noise channels.
* PlayEnvelope(shape) - Set envelope type. Plays the sound on channels that have a volume of 16.


 
