# PSG AY-3-8910 RT MSX SDCC Library (fR3eL Project)

```
Author: mvac7
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and Z80 assembler
```


---
## Description

Library for access to internal or external MSX PSG AY-3-8910 in Real Time. 

It does not use the BIOS so it can be used to program both ROMs or MSX-DOS executables.
  
Reading or writing to the PSG is done through calls to the assigned ports.

It incorporates the SOUND function with the same behavior as the command included in MSX BASIC, as well as specific functions to modify the different sound parameters of the AY. 

Controls the I/O bits of register 7 (Mixer), of the internal AY.

It allows to use the internal PSG of the MSX or an external one (like the one incorporated in the MEGAFLASHROM SCC+, Flashjacks or other).

In the header file there is a definition of SWITCHER type, needed for the functions.
This type uses the values "ON" or "OFF", which equals 1 and 0 respectively.

Include definitions to improve the readability of your programs.

Use them for developing MSX applications using Small Device C Compiler (SDCC).

This project is an Open Source library. 
You can add part or all of this code in your application development or include it in other libraries/engines.

You can access the documentation here with [`How to use the library`](docs/HOWTO.md).

In the source code [`examples/`](examples/), you can find applications for testing and learning purposes.

![TEST AY Lib](https://raw.githubusercontent.com/mvac7/SDCC_AY38910RT_Lib/master/examples/test01_ROM/GFX/TESTAY_screenshot.png) 

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!                           


---
## History of versions

- v1.6 (07/06/2021) Fixes problem with reading the registers in the MEGAFLASHROM SCC++
- v1.5 (09/05/2021) External AY
- v1.4 (17/06/2018) Corrected a BUG in the SOUND function.  Change name function Sound to SOUND.
- v1.3 (11/02/2018) Revised and first publication.
- v1.2 (?) ?
- v1.1 (14/02/2014) Initial version.
- v1.0 (?) ?


---
## Requirements

- [Small Device C Compiler (SDCC) v4.1](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)



---
## Acknowledgments
  
I want to give a special thanks to all those who freely share their knowledge with the MSX developer community.

- Avelino Herrera > [`WEB`](http://msx.avelinoherrera.com/index_es.html)
- Nerlaska > [`Blog`](http://albertodehoyonebot.blogspot.com.es)
- Marq > [`Marq`](http://www.kameli.net/marq/)
- MSXKun/Paxanga soft > [`WEB`](http://paxangasoft.retroinvaders.com/)
- Fubukimaru [`gitHub`](https://github.com/Fubukimaru)
- Andrear > [`Blog`](http://andrear.altervista.org/home/msxsoftware.php)
- Sapphire/Z80ST > [`WEB`](http://z80st.auic.es/)
- Fernando García > [`Video Tutorial`](http://www.z80st.es/cursos/bitvision-assembler)
- Ramones > [`MSXblog`](https://www.msxblog.es/tutoriales-de-programacion-en-ensamblador-ramones/) - [`MSXbanzai`](http://msxbanzai.tni.nl/dev/faq.html)
- Eric Boez > [`gitHub`](https://github.com/ericb59)
- MSX Assembly Page > [`WEB`](http://map.grauw.nl/resources/msxbios.php)
- Portar MSX Tech Doc > [`WEB`](https://problemkaputt.de/portar.htm)
- MSX Resource Center > [`WEB`](http://www.msx.org/)
- Karoshi MSX Community > [`WEB`](http://karoshi.auic.es/)
- BlueMSX emulator >> [`WEB`](http://www.bluemsx.com/)
- OpenMSX emulator >> [`WEB`](http://openmsx.sourceforge.net/)
- [`WebMSX`](https://webmsx.org/) emulator by Paulo A. Peccin >> [`gitHub`](https://github.com/ppeccin/webmsx)
- fMSX emulator by Marat Fayzullin [`WEB`](https://fms.komkon.org/fMSX/)
- Meisei emulator by Hap >> `?`

