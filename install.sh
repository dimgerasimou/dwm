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

configScripts="volumecontrol swaplanguage"
configDirectory="$HOME/.local/bin/dwm"
dependencyList="feh brightnessctl pamixer ttf-joypixels"

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
	echo "	--help              Prints this menu then exits."
	echo "	--no-build          Does not build dwm."
	echo "	--clean             Cleans the directory from extra files then exits."
	echo "	--install-clean     Installs dwm then cleans the directory."
	echo "	--uninstall         Uninstalls dwm binary and all scripts."
}

function cleanDir {
	echo "Cleaning build directory."
	make --directory=build clean 1> /dev/null 2> log.txt
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

	if [ -s /usr/share/xsessions/dwm.desktop ]; then
		sudo rm -f /usr/share/xsessions/dwm.desktop 1> /dev/null 2> log.txt
	fi
	
	if ! [ "$(ls -A $configDirectory)" ]; then
		rmdir $configDirectory 1> /dev/null 2> log.txt
	fi
}

function copyScripts {
	echo "Copying scripts."
	sudo cp scripts/dwm-start /usr/local/bin 1> /dev/null 2> log.txt

	if [[ ! -d $configDirectory ]]; then
		mkdir $configDirectory 1> /dev/null 2> log.txt
	fi

	for script in $configScripts; do
		cp scripts/$script $configDirectory/$script 1> /dev/null 2> log.txt
	done
	
	sudo cp scripts/dwm.desktop /usr/share/xsessions/dwm.desktop 1> /dev/null 2> log.txt
}

function dependencyCheck {
	echo "Checking dependencies."
	gr='\x1b[32m'
	red='\x1b[31m'
	nrm='\x1b[0m'
	validDependencies=1
	if [[ -s /usr/bin/pacman ]]; then
		for pkg in $dependencyList; do
			if $(pacman -Qi $pkg &> /dev/null); then
				echo -e "	[$gr ✓ $nrm] $pkg is installed."
			else
				echo -e "	[$red ❌$nrm] $pkg is not installed."
				validDependencies=0
			fi
		done

		if [ validDependencies == 0 ]; then
			echo "Not all dependencies are installed. Install them manually."
			exit 1
		fi
	else
		read "Not running Arch. Please check that all dependencies are installed. Continue? [y/N]" yn
		case $yn in
			[Yy] ) break;;
			* ) exit 1;;
		esac
	fi
}

function build {
	dependencyCheck

	if [ CONFIG == 0 ]; then
		cleanDir
	fi

	echo "Building dwm."
	sudo make --directory=build clean install 1> /dev/null 2> log.txt

	
}

function uninstall {
	echo "Uninstalling dwm."
	sudo make --directory=build uninstall 1> /dev/null 2> log.txt
	cleanDir

	removeScripts
}

# Script--------------------------------------------------------------

BUILD=1
CONFIG=0
UNINSTALL=0
CLEAN=0
INSTALL=0

# Checking arguments:
for var in "$@"
do
	case $var in
		"--help" | "-h")    printhelp
		                    exit;;
		"--no-build")       BUILD=0;;
		"--keep-config")    CONFIG=1;;
		"--clean")          CLEAN=1;;
		"--uninstall")      UNINSTALL=1;;
		"--install-clean")  CLEAN=1
		                    INSTALL=1;;
		*)					echo "Invalid arguments. --help for help"
		                    exit 1;;
	esac
done

if [ $UNINSTALL == 0 ] && [ $CLEAN == 0 ]; then
	INSTALL=1
fi

# Check for root privilages.
if (( $EUID == 0 )); then
	echo "Please do not run as root"
		exit 1
fi

# Check if script is in correct directory.
if ! [[ -s build/config.mk ]]; then
	echo "Script not in correct directory."
	exit 1
fi

# Delete existing log.
if [[ -s log.txt ]]; then
	rm log.txt
fi


if [ $UNINSTALL == 1 ]; then
	uninstall
fi

if [ $INSTALL == 1 ]; then
	if [ $BUILD == 1 ]; then
		build
	fi
	copyScripts
fi

if [ $CLEAN == 1 ]; then
	cleanDir
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
