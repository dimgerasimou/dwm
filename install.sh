#!/bin/bash
#  ____   ____
# |  _ \ / ___|    Dimitris Gerasimou (dimgerasimou)
# | | | | |  _     <https://github.com/dimgerasimou>
# | |_| | |_| |
# |____/ \____|
#
# Script that aids with the installation of dwm. Can build dwm, and copy
# the scripts needed for it to run at their designated directories.

# Global variables ---------------------------------------------------

configScripts="swaplanguage"
compiledScripts="audiocontrol"
SCRIPTDIR="$HOME/.local/bin/dwm"
SRC="src"
SCRIPTSRC="sripts"

# Functions-----------------------------------------------------------

function printhelp {
	echo "This is a simple script to aid with the help of dwm installation."
	echo "Builds dwm and copies the correct scripts in their directories."
	echo ""
	echo "WARNING: do not run as root."
	echo ""
	echo "You will be promted for your password as the script is running."
	echo "On Arch Linux if sudo prompts right password as wrong, check if systemd-homed service is running."
	echo ""
	echo "	help              Prints this menu then exits."
	echo "	clean             Cleans the directory from extra files then exits."
	echo "	install           Installs dwm then cleans the directory."
	echo "	uninstall         Uninstalls dwm binary and all scripts."
}

function clean {
	echo "Cleaning build directory."
	make --directory=$SRC clean 1> /dev/null 2> log.txt
}

function removeScripts {
	echo "Removing scripts."
	if [ -s /usr/local/bin/dwm-start ]; then
		sudo rm -f /usr/local/bin/dwm-start 1> /dev/null 2> log.txt
	fi
	
	for script in $configScripts; do
		if [[ -s $configDirectory/$script ]]; then
			rm -rf $configDirectory/$script 1> /dev/null 2> log.txt
		fi
	done

	for script in $compiledScripts; do
		if [[ -s $configDirectory/$script ]]; then
			rm -rf $configDirectory/$script 1> /dev/null 2> log.txt
		fi
	done


	if [ -s /usr/share/xsessions/dwm.desktop ]; then
		sudo rm -f /usr/share/xsessions/dwm.desktop 1> /dev/null 2> log.txt
	fi
	
	if ! [ "$(ls -A $SCRIPTDIR)" ]; then
		rmdir $SCRIPTDIR 1> /dev/null 2> log.txt
	fi
}

function copyScripts {
	echo "Copying scripts."
	sudo cp $SCRIPTSRC/dwm-start /usr/local/bin 1> /dev/null 2> log.txt

	mkdir -p $SCRIPTDIR 1> /dev/null 2> log.txt


	for script in $configScripts; do
		cp $SCRIPTSRC/$script $SCRIPTDIR/$script 1> /dev/null 2> log.txt
	done

	for script in $compiledScripts; do
		gcc -o $SCRIPTSRC/$script $SCRIPTSRC/$script.c -Wall -Os
		mv $SCRIPTSRC/$script $SCRIPTDIR/$script 1> /dev/null 2> log.txt
	done
	
	sudo cp $SCRIPTSRC/dwm.desktop /usr/share/xsessions/dwm.desktop 1> /dev/null 2> log.txt
}

function compile {
	echo "Compiling dwm."
	echo ""
	make --directory=$SRC
	if (( $? != 0 )); then
		echo "Failed in compiling dwm."
		exit 1;
	fi
	echo ""
}

function install {
	echo "Installing dwm."
	echo ""
	sudo make --directory=$SRC install
	echo ""
}

function uninstall {
	echo "Uninstalling dwm."
	echo ""
	sudo make --directory=$SRC uninstall
	echo ""
	removeScripts
}

# Script--------------------------------------------------------------

UNINSTALL=0
CLEAN=0
INSTALL=0

# Checking arguments:
for var in "$@"
do
	case $var in
		"help" | "-h")    printhelp
		                  exit;;
		"clean")          CLEAN=1;;
		"uninstall")      UNINSTALL=1;;
		"install")        INSTALL=1;;
		*)                echo "Invalid arguments. [help] for help."
		                  exit 1;;
	esac
done

# Check for root privilages.
if (( $EUID == 0 )); then
	echo "Please do not run as root."
		exit 1
fi

# Check if script is in correct directory.
if ! [[ -s $SRC/config.mk ]]; then
	echo "Script not in correct directory."
	exit 1
fi

# Delete existing log.
if [[ -s log.txt ]]; then
	rm log.txt
fi

if (( $CLEAN == 1 )); then
	clean
fi

if (( $UNINSTALL == 1 )); then
	uninstall
fi

if (( $CLEAN == 0 && $UNINSTALL == 0 )); then
	compile
fi

if (( $UNINSTALL == 0 && $INSTALL == 1 )); then
	install
fi

if [[ -s log.txt ]]; then
		echo "Finished with errors."
		exit 1
	else
		if [ -e log.txt ]; then
			rm log.txt
		fi
		echo "Done!"
fi
