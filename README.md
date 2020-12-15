# PSG AY38910 MSX SDCC Library (fR3eL Project)

```
Author: mvac7 [mvac7303b@gmail.com]
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and Z80 assembler
```



## Description

This project is an opensource library with basic functions for work with PSG AY-3-8910 or compatible. 

Designed for developing MSX applications using Small Device C Compiler (SDCC).
  
It does not use the BIOS so it can be used to program both ROMs or MSX-DOS executables.
  
Reading or writing to the PSG is done through calls to the assigned ports. 
In most of the known MSX the following are used: 0xA0, 0xA1 and 0xA2. 
If you want to use this library for a different architecture, you will have to change these assignments found at the start of the AY38910.c sources.

In the header file there is a definition of boolean type, need for the functions.
This type uses the values "true" or "false" in lowercase, which equals 1 and 0 respectively.

The source code includes an application to test or learn how to use the library.  

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!                           



## History of versions

* v1.4 (17/06/2018) Corrected a BUG in the SOUND function.  Change name function Sound to SOUND.
* v1.3 (11/02/2018) Revised and first publication.
* v1.2 (?)
* v1.1 (14/02/2014) Initial version.
* v1.0 (?)



## Requirements

* Small Device C Compiler (SDCC) v3.9 http://sdcc.sourceforge.net/
* Hex2bin v2.5 http://hex2bin.sourceforge.net/




## Constants

### Envelope shapes

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


  
## Functions

* **SOUND**(register, value) - Write into a register of PSG
* **GetSound**(register) - Read PSG register value
* **SetTonePeriod**(channel, period) - Set Tone Period for any channel
* **SetNoisePeriod**(period) - Set Noise Period
* **SetEnvelopePeriod**(period) - Set Envelope Period
* **SetVolume**(channel, volume) - Set volume channel
* **SetChannel**(channel, isTone, isNoise) - Mixer. Enable/disable Tone and Noise channels.
* **PlayEnvelope**(shape) - Set envelope type. Plays the sound on channels that have a volume of 16.



## Acknowledgments
  
I want to give a special thanks to all those who freely share their knowledge with the MSX developer community.

* Avelino Herrera > [WEB](http://msx.atlantes.org/index_es.html)
* Nerlaska > [Blog](http://albertodehoyonebot.blogspot.com.es)
* Marq/Lieves!Tuore > [Marq](http://www.kameli.net/marq/) [Lieves!Tuore](http://www.kameli.net/lt/)
* [Fubukimaru](https://github.com/Fubukimaru) > [Blog](http://www.gamerachan.org/fubu/)
* Andrear > [Blog](http://andrear.altervista.org/home/msxsoftware.php)
* Ramones > [MSXblog](https://www.msxblog.es/tutoriales-de-programacion-en-ensamblador-ramones/) - [MSXbanzai](http://msxbanzai.tni.nl/dev/faq.html)
* Sapphire/Z80ST > [WEB](http://z80st.auic.es/)
* Fernando García > [youTube](https://www.youtube.com/user/bitvision)
* Eric Boez > [gitHub](https://github.com/ericb59)
* MSX Assembly Page > [WEB](http://map.grauw.nl/resources/msxbios.php)
* Portar MSX Tech Doc > [WEB](http://nocash.emubase.de/portar.htm)
* MSX Resource Center > [WEB](http://www.msx.org/)
* Karoshi MSX Community (RIP 2007-2020)
* BlueMSX emulator >> [WEB](http://www.bluemsx.com/)
* OpenMSX emulator >> [WEB](http://openmsx.sourceforge.net/)
* Meisei emulator >> ?
 
