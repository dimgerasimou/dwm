# dwm - dynamic window manager

## Introductiom

dwm is an extremely fast, small, and dynamic window manager for X.
This is my build of dwm for version 6.3.


## Requirements

The only requirments to build dwm are the Xlib Header files.

Packages:

- brightnessctl
- pamixer
- feh
- picom
- libxft-bgra (for emoji support)
- ttf-joypixels
- qt5ct (for qt5 application theme support)
- dunst (for notification support)

## Installation

Edit config.mk to match your local setup (dwm is installed into the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if necessary as root):

`make clean install`

The config.h is not deleted each build and must be deleted manualy for the changes on config.def.h to take effect.

Moreover the `install.sh` can be used to aid with the whole installation. Builds dwm and copies all neccesary scripts in the proper places.

## Patches

Patches installed:
- alpha
- restartsig
- vanitygaps
- noborderfloatingfix
- rotatestack
- statuscmd

### dmenu

dmenu is a dynamic menu for X, originally designed for dwm. It manages large numbers of user-defined menu items efficiently.

Source code: https://git.suckless.org/dmenu
