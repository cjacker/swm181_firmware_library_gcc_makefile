# swm181_firmware_library_gcc_makefile

Synwit Tech SWM181 firmware library with gcc / Makefile support.

This is for Luat SWM181 devboard.

**NOTE 1: NOW, Synwit official DFP did not support pyOCD and seems no plan to support it!**

**NOTE 2: SRAM SIZE can be configured by SRAM_SWITCH in startup asm file, by default, SRAM_SWITCH set to 0. it means 16K RAM.**

Please use SWMProg to program:

```
git clone https://github.com/Synwit-Co-Ltd/SWMProg
python ./SWMProg.py
```

