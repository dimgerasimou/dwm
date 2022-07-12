#!/bin/bash
#  ____   ____
# |  _ \ / ___|    Dimitrs Gerasimou (dimgerasimou)
# | | | | |  _     <dimgerasimou@gmail.com>
# | |_| | |_| |    https://github.com/dimgerasimou
# |____/ \____|
#
# Script that aids with the installation of dwm. Can build dwm, and copy
# the scripts needed for it to run at their designated directories.

# Functions-----------------------------------------------------------

function printhelp {
	echo "This is a simple script to aid with the help of dwm installation."
	echo "Builds dwm and copies the correct scripts in their directories."
	echo ""
	echo "WARNING: do not run as root."
	echo "You will be promted for your password as the script is running."
	echo ""
	echo "    --help          prints this menu then exits."
	echo "    --no-build      does not build dwm."
	echo "    --no-config     delete config.h before building."
}

# Script--------------------------------------------------------------

BUILD=1
CONFIG=1

# Checking arguments:

for var in "$@"
do

# Check for help input.
if [[ "$var" == "--help" || "$var" == "-h" ]]; then
	printhelp
	exit
fi

# Check for build.
if [[ "$var" == "--no-build" ]]; then
	BUILD=0
fi

# Check for config.h deletion.
if [[ "$var" == "--no-config" ]]; then
	CONFIG=1
fi

done

# Check for root privilages.
if (( $EUID == 0 )); then
	echo "Please do not run as root"
		exit
fi

# Check if script is in correct directory.
if [[ -s build/config.mk ]]; then
	echo "In correct directory."
else
	echo "Script not in correct directory."
	exit
fi

# Install dwm to usr/local/bin.
if [ $BUILD == 1 ]; then
	if [[ -s dwminstalllog.txt ]]; then
		rm dwminstalllog.txt
	fi

	if [ $CONFIG == 0 ] && [ -s build/config.h ]; then
		echo "Deleting config.h"
		rm -f build/config.h
	fi

	echo "Building dwm."
	sudo make --directory=build clean install 1> /dev/null 2>dwminstalllog.txt
	
	if [[ -s dwminstalllog.txt ]]; then
		echo "Error with building. Check Logs at .dwminstalllog in this directory."
	else
	    echo "dwm built succesfully!"
		rm dwminstalllog.txt
	fi
fi

# Remove log text file.
if [[ -s dwmcopyscriptslog.txt ]]; then
	rm dwmcopyscriptslog.txt
fi

# Copy dwm-start script to /usr/local/bin
echo "Copying dwm-start to /usr/local/bin"
sudo cp scripts/dwm-start /usr/local/bin 1> /dev/null 2>dwmcopyscriptslog.txt

# Copy volume control script to ~/.local/bin/dwmblocks
echo "Copying volumecontrol to ~/.local/bin/dwmblocks"
cp scripts/volumecontrol "$HOME"/.local/bin/dwm/dwm/volumecontrol 1> /dev/null 2>dwmcopyscriptslog.txt

# Copy dwm.desktop to /usr/share/xsessions
echo "Copying dwm.desktop to /usr/share/xsessions/dwm.desktop"
sudo cp scripts/dwm.desktop /usr/share/xsessions/dwm.desktop 1> /dev/null 2>dwmcopyscriptslog.txt

if [[ -s dwmcopyscriptslog.txt ]]; then
	echo "Error with copying the scripts. Check logs at dwmcopyscriptslog.txt in this directory."
else
	echo "Copied all scripts succesfully!"
	rm dwmcopyscriptslog.txt
fi

echo "Installation completed!"
