# dwm - dynamic window manager

## Introductiom

dwm is an extremely fast, small, and dynamic window manager for X.
This is my build of dwm.
dwm `--version 6.3`

## Requirements

The only requirments to build dwm are the Xlib Header files.

## Installation

Edit config.mk to match your local setup (dwm is installed into the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if necessary as root):

`make clean install`

The config.h is not deleted each build and must be deleted manualy for the changes on config.def.h to take effect.

## Patches

I have still not have not introduced any patches.

## Recommended binaries

### dmenu
dmenu is a dynamic menu for X, originally designed for dwm. It manages large numbers of user-defined menu items efficiently.

Source code: https://git.suckless.org/dmenu
