# dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.
This is a heavily patched version with all the scripts i use for my configuration in daily use.

## Requirements

In order to build dwm you need the Xlib header files.
This patched version as is, requires the following packages:
- feh
- brightnessctl
- pamixer
- ttf-joypixels
- easyeffects
- picom

## Installation

This build can be installed normally as stock dwm, however there is an install script that helps with all the scripts installation and configuration of this build (use --help option).

## Patches

- swallow
- restartsig
- attachdirection
- xresources
- status2d
- systray
## Running dwm

By using the install script running dwm can be done automaticly through the login manager.
If not using one, it can be executed by adding `exec dwm` in the .xinitrc file.

For a statusbar any can be installed but you can use [my version](https://github.com/dimgerasimou/dwm-asyncblocks 'dwm-asyncblocks') of dwmblocks.

## Configuration

The configuration of dwm is done by creating a custom config.h and (re)compiling the source code.
