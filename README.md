# swm181_firmware_library_gcc_makefile
Synwit Tech SWM181 firmware library with gcc / Makefile support.

**NOTE 1: NOW, it can not program by pyocd with Synwit official DFP !**

**NOTE 2: I use Luat SWM181 devboard, the MCU model is 'swm181cbt6', according to datasheet, it's 16K ram, but
only 8K can be specified in swm181.ld, otherwise, it will not work!**


Please use SWMProg to program:

```
git clone https://github.com/cjacker/SWMProg
git checkout linux
python ./SWMProg.py
```

