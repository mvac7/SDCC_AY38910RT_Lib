# PSG AY-3-8910 MSX SDCC Library (fR3eL Project)

```
Author: mvac7 [mvac7303b@gmail.com]
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and Z80 assembler
```


---
## Description

This project is an opensource library with basic functions for work with PSG AY-3-8910 or compatible. 

Designed for developing MSX applications using Small Device C Compiler (SDCC).
  
It does not use the BIOS so it can be used to program both ROMs or MSX-DOS executables.
  
Reading or writing to the PSG is done through calls to the assigned ports.

It incorporates the SOUND function with the same behavior as the command included in MSX BASIC, as well as specific functions to modify the different sound parameters of the AY. 

It allows to use the internal PSG of the MSX or an external one (like the one incorporated in the MEGAFLASHROM SCC +).

In the header file there is a definition of boolean type, needed for the functions.
This type uses the values "true" or "false" in lowercase, which equals 1 and 0 respectively.

Include definitions to improve the readability of your programs.

In the source code (\examples), you can find applications for testing and learning purposes.

![TEST AY Lib](https://raw.githubusercontent.com/mvac7/SDCC_AY38910_Lib/master/examples/test/GFX/TESTAY_screenshot.png) 

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!                           


---
## History of versions

* v1.6 (07/06/2021) Fixes problem with reading the registers in the MEGAFLASHROM SCC++
* v1.5 (09/05/2021) External AY
* v1.4 (17/06/2018) Corrected a BUG in the SOUND function.  Change name function Sound to SOUND.
* v1.3 (11/02/2018) Revised and first publication.
* v1.2 (?) ?
* v1.1 (14/02/2014) Initial version.
* v1.0 (?) ?


---
## Requirements

* Small Device C Compiler (SDCC) v3.9 http://sdcc.sourceforge.net/
* Hex2bin v2.5 http://hex2bin.sourceforge.net/



---
## Definitions

### AY Registers

Label | Value | Description
-- | -- | -- 
AY_ToneA     |  0 | Channel A Tone Period (12 bits)
AY_ToneB     |  2 | Channel B Tone Period (12 bits)
AY_ToneC     |  4 | Channel C Tone Period (12 bits)
AY_Noise     |  6 | Noise Period (5 bits)
AY_Mixer     |  7 | Mixer
AY_AmpA      |  8 | Channel Volume A (4 bits + B5 active Envelope)
AY_AmpB      |  9 | Channel Volume B (4 bits + B5 active Envelope)
AY_AmpC      | 10 | Channel Volume C (4 bits + B5 active Envelope)
AY_EnvPeriod | 11 | Envelope Period (12 bits)
AY_EnvShape  | 13 | Envelope Shape


### Envelope shapes

The header file defines envelope shapes in case you prefer to use it instead 
of the numerical form:

Label | Value
-- | --  
AY_ENV_LowerBeat     | 1 
AY_ENV_Upper         | 4 
AY_ENV_LeftSaw       | 8
AY_ENV_LowerTriangle | 10 
AY_ENV_LowerHold     | 11 
AY_ENV_RightSaw      | 12
AY_ENV_UpperHold     | 13
AY_ENV_UpperTriangle | 14

**Attention!** The LowerBeat shape may be produced with the values: 0, 1, 2, 3 and 9. 
The value 1 has been assigned to *LowerBeat* as 0 can be useful in case you need to control when the envelope is triggered. In this case 0 can act as a "don't
write the envelop" event. Remember that, every time the register 13 is written, the sound with the assigned shape is started.

The Upper shape may be produced with the values: 4, 5, 6, 7 and 15.



### AY channels

You can use it in the functions: SetTonePeriod, SetVolume and SetChannel

Label | Value
-- | -- 
AY_Channel_A | 0
AY_Channel_B | 1
AY_Channel_C | 2


---  
## Functions

* **SOUND**(register, value) - Write into a register of PSG
* **GetSound**(register) - Read PSG register value
* **SetTonePeriod**(channel, period) - Set Tone Period for any channel
* **SetNoisePeriod**(period) - Set Noise Period
* **SetEnvelopePeriod**(period) - Set Envelope Period
* **SetVolume**(channel, volume) - Set volume channel
* **SetChannel**(channel, isTone, isNoise) - Mixer. Enable/disable Tone and Noise channels.
* **PlayEnvelope**(shape) - Set envelope type. Plays the sound on channels that have a volume of 16.


---
## Set Internal or External AY

To indicate in which PSG the sounds are to be played, you have the **isAYextern** variable. 
To select an external AY, like the one included in the MegaFlashROM SCC+ (ports 10h to 12h), you have to set the variable to true (or 1).

```
  isAYextern = true;
```

The library does not contain an initialization function so it is recommended to provide a value to this variable at the beginning of your program.


---
## AY-3-8910 Register Table

<table>
<tr>
<th colspan=2>Register\bit</th><th width=50>B7</th><th width=50>B6</th><th width=50>B5</th><th width=50>B4</th><th width=50>B3</th><th width=50>B2</th><th width=50>B1</th><th width=50>B0</th>
</tr>
<tr>
<td>R0</td><td rowspan=2>Channel A Tone Period</td><td colspan=8 align=center>8-Bit Fine Tune A</td>
</tr>
<tr>
<td>R1</td><td colspan=4></td><td colspan=4 align=center>4-Bit Coarse Tune A</td>
</tr>
<tr>
<td>R2</td><td rowspan=2>Channel B Tone Period</td><td colspan=8 align=center>8-Bit Fine Tune B</td>
</tr>
<tr>
<td>R3</td><td colspan=4></td><td colspan=4 align=center>4-Bit Coarse Tune B</td>
</tr>
<tr>
<td>R4</td><td rowspan=2>Channel C Tone Period</td><td colspan=8 align=center>8-Bit Fine Tune C</td>
</tr>
<tr>
<td>R5</td><td colspan=4></td><td colspan=4 align=center>4-Bit Coarse Tune C</td>
</tr>
<tr>
<td>R6</td><td>Noise period</td><td colspan=3></td><td colspan=5 align=center>5-Bit Period control</td>
</tr>
<tr>
<td rowspan=2>R7</td><td rowspan=2>Enable (bit 0=on, 1=off)</td><td colspan=2 align=center>IN/OUT</td><td colspan=3 align=center>Noise</td><td colspan=3 align=center>Tone</td></tr>
<tr>
<td align=center> IOB</td><td align=center>IOA</td><td align=center>C</td>
<td align=center>B</td><td align=center>A</td><td align=center>C</td>
<td align=center>B</td><td align=center>A</td>
</tr>
<tr>
<td>R8</td><td>Channel A Amplitude</td><td colspan=2></td><td align=center>Env</td><td colspan=5 align=center>Amplitude</td>
</tr>
<tr>
<td>R9</td><td>Channel B Amplitude</td><td colspan=2></td><td align=center>Env</td><td colspan=5 align=center>Amplitude</td>
</tr>
<tr>
<td>R10</td><td>Channel C Amplitude</td><td colspan=2></td><td align=center>Env</td><td colspan=5 align=center>Amplitude</td>
</tr>
<tr>
<td>R11</td><td rowspan=2>Envelope Period</td><td colspan=8 align=center>8-Bit Fine Tune Envelope</td>
</tr>
<tr>
<td>R12</td><td colspan=8 align=center>8-Bit Coarse Tune Envelope</td>
</tr>
<tr>
<td>R13</td><td>Envelope Shape/Cycle</td><td colspan=4></td><td>CONT</td><td>ATT</td><td>ALT</td><td>HOLD</td>
</tr>
<tr>
<td>R14</td><td>I/O Port A Data Store</td><td colspan=8 align=center>8-Bit Parallel I/O on Port A</td>
</tr>
<tr>
<td>R15</td><td>I/O Port B Data Store</td><td colspan=8 align=center>8-Bit Parallel I/O on Port B</td>
</tr>
</table>


---
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


---
## References

* [General Instrument AY-3-8910 (wikipedia)](https://en.wikipedia.org/wiki/General_Instrument_AY-3-8910)
* [GI AY-3-8910 Datasheet (PDF)](http://map.grauw.nl/resources/sound/generalinstrument_ay-3-8910.pdf)
