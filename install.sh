#!/bin/bash
#Script that compiles dwm, and then copies all files nessesary to run my dwm build from sddm.
#Script that must be run from dwm repo main folder.

#Functions-----------------------------------------------------------

#Yes no function.
function yesNo {
	DEFAULT="y"

	read -p "Do you want to install it? [Y/n] " -r INPUT
	INPUT=${INPUT:-${DEFAULT}}

	if [[ "$INPUT" =~ ^[yY]$ ]]; then
		pacman -S $package
	else
		WITHFEH=false
	fi
}

#Check package installation function
function havei {
	package="$1"
	if $(pacman -Qi $package &>/dev/null); then
		echo -e "[\e[92m 🗸 \e[39m] $package is installed"
	else
	    echo -e "[\e[91m ❌\e[39m] $package is not installed"
		yesNo
	fi
}

function printhelp {
	echo "This is a simple script to aid with the help of dwm installation."
	echo "Checks if the needed packages are installed and install the correct script in its place."
	echo ""
	echo "It needs to be ran as root!"
	echo ""
	echo "    --no-feh    does not install feh and sources the correct scripts."
	echo "    --help      prints this menu then exits."
}

function correctDirectory {
	if [[ -f "config.mk" ]]; then
		echo "In correct directory."
	else
		echo "Script not in correct directory."
		exit
	fi
}

#Script--------------------------------------------------------------

#Check for help input.
if [[ "$1" == "--help" || "$1" == "-h" ]]; then
	printhelp
	exit
fi


#Check for root privilages.
if (( $EUID != 0 )); then
	echo "Please run as root"
		exit
fi

#Check if script is in correct directory
correctDirectory

#Variable to set if feh will be installed
WITHFEH=true

#Check for feh and whatever to install it or not.
if [ "$1" == "--no-feh" ]; then
	WITHFEH=false
else
	havei feh
fi

#Install dwm to usr/local/bin.
make clean install

#Copy scripts for sddm integration with or without feh
cp /scripts/dwm.desktop /usr/share/xsessions/dwm.desktop
cp /scripts/dwm-start /usr/local/bin/dwm-start

if [ "$WITHFEH" = true ]; then
	cp /scripts/dwm-start.sh ~/.dwm-start.sh
else
	cp /scrpits/dwm-start-nofeh.sh ~/.dwm-start.sh
fi

echo "Done!"
