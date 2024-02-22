# CH32X035 USB Serial / CDC

## What is this??

Implements a basic Arduino class for `SerialUSB` that is able to `println()`

**Also** implements the feature that if the serial connection is opened at 1200bps, the chip will reboot into its USB bootloader, after which it can be flashed again.

Easy upload cycles!

USB bootloader can be used by latest version `wchisp` or WCHISPStudio. 

The CH32X035 USB bootloader can also be initially entered by connecting PC17 via a 1 kOhm (also 10kOhm works) resistor to VCC upon boot.