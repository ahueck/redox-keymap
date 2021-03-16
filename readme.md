# The ahueck keymap for Redox/rev1 &middot; ![](https://github.com/ahueck/redox-keymap/workflows/Keymap-CI/badge.svg?branch=master)

Further information for the keyboard specifics: [Redox repository](https://github.com/mattdibi/redox-keyboard) and [Redox qmk firmware](https://github.com/qmk/qmk_firmware/tree/master/keyboards/redox)

## Flashing the device
Note: new qmk CLI; not fully tested w.r.t. flashing; see also (Github CI)[.github/workflows/basic-ci.yml]

Always do the flashing procedure for both sides.
Reset button (pinhole) is on the underside of each half, respectively.

### 1. Setup CLI
    - python3 -m pip install --user qmk

### 2. Setup firmware
    - qmk --setup -H ${QMK_HOME}

### 3. Setup keymap
    1. cd ${QMK_HOME}/keyboards/redox/keymaps/
    2. git clone https://github.com/ahueck/redox-keymap.git ahueck
    3. qmk compile -kb redox/rev1 -km ahueck

#### Useful links
[Online config](https://config.qmk.fm/#/redox/rev1/LAYOUT)
 
##### Key related
[Keycodes basic](https://beta.docs.qmk.fm/using-qmk/simple-keycodes)

[Keycodes advanced](https://beta.docs.qmk.fm/using-qmk/advanced-keycodes)

[Software features](https://beta.docs.qmk.fm/using-qmk/software-features)

### 4. Flash
    1. Modem manager may need special handling, see [QMK FAQ](https://beta.docs.qmk.fm/faqs/faq_build), e.g., `sudo systemctl stop ModemManager.service`
    2. qmk flash -kb redox/rev1 -km ahueck



## Flashing the device (manually, possibly outdated)
Always do the flashing procedure for both sides.
Reset button (pinhole) is on the underside of each half, respectively.

### Pre-requisites 
    - git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
    - cd qmk_firmware
    - util/qmk_install.sh
    - (ubuntu: sudo apt-get install gcc unzip wget zip gcc-avr binutils-avr avr-libc dfu-programmer dfu-util gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi)
    - sudo apt-get install avrdude

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

