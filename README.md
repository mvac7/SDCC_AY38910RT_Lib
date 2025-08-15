# PSG AY-3-8910 RT MSX SDCC Library (fR3eL Project)

<table>
<tr><td rowspan=2>Name</td><td>PSG_AY38910RT</td></tr>
<tr><td>PSG_AY38910RT_eXtended</td></tr>
<tr><td>Architecture</td><td>MSX</td></tr>
<tr><td>Environment</td><td>ROM, MSX-DOS, MSX BASIC</td></tr>
<tr><td>Programming language</td><td>C</td></tr>
<tr><td>Format</td><td>SDCC Relocatable object file (.rel)</td></tr>
<tr><td>Compiler</td><td>SDCC v4.4</td></tr>
</table>

---

## Description

C function library with functions for access to internal or external MSX PSG AY-3-8910 in Real Time. 

This project consists of two libraries that complement each other:
- **PSG_AY38910BF** Includes only the functions necessary to play sounds.
- **PSG_AY38910BF_eXtended** (optional) Adds specific functions to make it easier to write AY parameters. Requires the PSG_AY38910RT library.
  
Reading or writing to the PSG is done through calls to the assigned ports.

It incorporates the SOUND function with the same behavior as the command included in MSX BASIC, as well as specific functions to modify the different sound parameters of the AY. 

Controls the I/O bits of register 7 (Mixer), of the internal AY.

It allows to use the internal PSG of the MSX or an external one (like the one incorporated in the MEGAFLASHROM SCC+, Flashjacks or other).

In the header file there is a definition of SWITCHER type, needed for the functions.
This type uses the values "ON" or "OFF", which equals 1 and 0 respectively.

Include definitions to improve the readability of your programs.

You can access the documentation here with [`How to use the library`](docs/HOWTO.md).

In the source code [`examples/`](examples/), you can find applications for testing and learning purposes.

![TEST AY Lib](https://raw.githubusercontent.com/mvac7/SDCC_AY38910RT_Lib/master/examples/test01_ROM/GFX/TESTAY_screenshot.png) 

These libraries are part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Use them for developing MSX applications using Small Device C Compiler [`SDCC`](http://sdcc.sourceforge.net/).

This project is open source under the [MIT license](LICENSE).<br/>
You can add part or all of this code in your application development or include it in other libraries/engines.

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

- [Small Device C Compiler (SDCC) v4.4](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)

