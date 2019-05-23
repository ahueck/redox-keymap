# The ahueck keymap for Redox/rev1  [![Build Status](https://travis-ci.com/ahueck/redox-keymap.svg?branch=master)](https://travis-ci.com/ahueck/redox-keymap)

Further information for the keyboard specifics: [Redox repository](https://github.com/mattdibi/redox-keyboard) and [Redox qmk firmware](https://github.com/qmk/qmk_firmware/tree/master/keyboards/redox)

## Flashing the device
Always do the flashing procedure for both sides.
Reset button (pinhole) is on the underside of each half, respectively.

### Pre-requisites 
    - git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
    - cd qmk_firmware
    - util/qmk_install.sh
    - (ubuntu: sudo apt-get install gcc unzip wget zip gcc-avr binutils-avr avr-libc dfu-programmer dfu-util gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi)
    - sudo apt-get install avrdude

#### Useful links
[Online config](https://config.qmk.fm/#/redox/rev1/LAYOUT)
 
##### Key related
[Keycodes basic](https://beta.docs.qmk.fm/features/keycodes_basic)

[Keycodes advanced](https://beta.docs.qmk.fm/features/feature_advanced_keycodes)

[Tap dance](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_tap_dance.md)

### Flash command procedure
    0. Ubuntu 18.10 hard requirement: sudo systemctl stop ModemManager.service
    1. sudo make redox/rev1:*keymap repo name*:avrdude
    2. hit reset button, when USB device detection is active (*Detecting USB port, reset your controller now*)
    3. repeat for right half of keyboard 

#### Example output (one side)
    sudo make redox/rev1:ahueck:avrdude
    QMK Firmware 0.6.368
    Making redox/rev1 with keymap ahueck and target avrdude

    avr-gcc (GCC) 5.4.0
    Copyright (C) 2015 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    Size before:
       text	   data	    bss	    dec	    hex	filename
          0	  23686	      0	  23686	   5c86	.build/redox_rev1_ahueck.hex

    Compiling: tmk_core/common/command.c                                                                [OK]
    Linking: .build/redox_rev1_ahueck.elf                                                               [OK]
    Creating load file for flashing: .build/redox_rev1_ahueck.hex                                       [OK]
    Copying redox_rev1_ahueck.hex to qmk_firmware folder                                                [OK]
    Checking file size of redox_rev1_ahueck.hex                                                         [OK]
     * The firmware size is fine - 23686/28672 (4986 bytes free)
    Detecting USB port, reset your controller now..................
    Device /dev/ttyACM0 has appeared; assuming it is the controller.
    Waiting for /dev/ttyACM0 to become writable.

    Connecting to programmer: .
    Found programmer: Id = "CATERIN"; type = S
        Software Version = 1.0; No Hardware Version given.
    Programmer supports auto addr increment.
    Programmer supports buffered memory access with buffersize=128 bytes.

    Programmer supports the following devices:
        Device code: 0x44

    avrdude: AVR device initialized and ready to accept instructions

    Reading | ################################################## | 100% 0.00s

    avrdude: Device signature = 0x1e9587 (probably m32u4)
    avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
             To disable this feature, specify the -D option.
    avrdude: erasing chip
    avrdude: reading input file ".build/redox_rev1_ahueck.hex"
    avrdude: input file .build/redox_rev1_ahueck.hex auto detected as Intel Hex
    avrdude: writing flash (23686 bytes):

    Writing | ################################################## | 100% 2.23s

    avrdude: 23686 bytes of flash written
    avrdude: verifying flash memory against .build/redox_rev1_ahueck.hex:
    avrdude: load data flash data from input file .build/redox_rev1_ahueck.hex:
    avrdude: input file .build/redox_rev1_ahueck.hex auto detected as Intel Hex
    avrdude: input file .build/redox_rev1_ahueck.hex contains 23686 bytes
    avrdude: reading on-chip flash data:

    Reading | ################################################## | 100% 0.47s

    avrdude: verifying ...
    avrdude: 23686 bytes of flash verified

    avrdude: safemode: Fuses OK (E:FB, H:D8, L:FF)

    avrdude done.  Thank you.

