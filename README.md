(日本語による解説は[ＴＮＫソフトウェア](https://www.tnksoft.com/soft/iot/hemix/)のサイトにて公開しています)

# Helix Remix
Customized QMK Firmware for Helix keyboard

## :question: What's this?

[QMK](https://github.com/qmk/qmk_firmware) is the hardware firmware for Pro Micro an Arduino compatible microcontroller. It specializes in the control of USB HID keyboard devices and has been adopted by many DIY keyboards.


[Helix](https://github.com/MakotoKurauchi/helix) is a famous DIY keyboard kit in Japan developed by MakotoKurauchi, and this project doesn't require any code changes for Helix.

[![Helix Remix demo](https://img.youtube.com/vi/S8fJb82glCo/0.jpg)](https://www.youtube.com/watch?v=S8fJb82glCo "Helix Remix demo")

This program is published for learning to develop your own firmware. However, I would be glad if you introduced here with "This site and articles were helpful for me".

## :memo: Technical note

A built firmware is including in "build" folder. Write this hex file by [QML Toolbox](https://qmk.fm/toolbox/) and you can use all the features without any programming.

I use <a href="https://msys.qmk.fm/">QMK MSYS</a>, an integrated tool, to compile the firmware. Once you launch QMK MSYS, set up the development tool with the "qmk setup" command to begin with, and after you are done, run the following command to compile.
```
qmk compile -kb helix_remix -km default
```

Helix Remix has following features:
- Full scratched code for the latest QMK APIs.
- Change the color of any key by LED layer API.
- Show any bitmap to OLED display.
- Data synchronization for a split keyboard.
- Example of using the right keyboard as a one-handed keyboard (Clip Studio mode).<br><br>

"tools" folder contains the tools for Helix Remix. Those tools requires Python3.
- **hex2hsv.py** : Changes the name and HTML color code to a C define statement, described in the CSV.
- **img2hex.py** : Optimized bitmap files to OLED binary image text.

For more information, please visit [my site](https://www.tnksoft.com/reading/hardware/keyboard/).

## :yen: Donate, please!
[![Donate For Free Project](https://www.tnksoft.com/donate/donate.svg "Donate For Free Project")](https://www.tnksoft.com/donate/)

## :copyright: License
[MIT](http://opensource.org/licenses/MIT)
