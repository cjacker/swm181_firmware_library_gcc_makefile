# swm181_firmware_library_gcc_makefile
Synwit Tech SWM181 firmware library with gcc / Makefile support.

This is for Luat SWM181 devboard.

**NOTE 1: NOW, it can not program by pyocd with Synwit official DFP !**

**NOTE 2: SRAM SIZE can be configured by SRAM_SWITCH in startup asm file, by default, SRAM_SWITCH set to 0. it means 16K RAM.**

Please use SWMProg to program:

```
git clone https://github.com/cjacker/SWMProg
git checkout linux
python ./SWMProg.py
```

