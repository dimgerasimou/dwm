#!/bin/bash
#  ____   ____
# |  _ \ / ___|    Dimitris Gerasimou (dimgerasimou)
# | | | | |  _     <https://github.com/dimgerasimou>
# | |_| | |_| |
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
	echo "On Arch Linux if sudo prompts right password as wrong, check if"
	echo "systemd-homed service is running."
	echo ""
	echo "    --help          prints this menu then exits."
	echo "    --no-build      does not build dwm."
	echo "    --delete-config deletes config.h before building."
	echo "    --clean         cleans the directory from extra files then exits."
	echo "    --uninstall     uninstalls dwm binary and all scripts."
}

# Script--------------------------------------------------------------

BUILD=1
CONFIG=1
UNINSTALL=0
CLEAN=0

configscripts="swaplanguage volumecontrol"

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
	if [[ "$var" == "--delete-config" ]]; then
		CONFIG=0
	fi

	# Check for clean build.
	if [[ "$var" == "--clean" ]]; then
		CLEAN=1
	fi

	# Check for uninstall.
	if [[ "$var" == "--uninstall" ]]; then
		UNINSTALL=1
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

# Clean build.
if [ $CLEAN == 1 ]; then
	# Check that logfile does not exist.
	if [ -s cleanlog.txt ]; then
		rm -f cleanlog.txt
	fi
	
	echo "Cleaning build directory."
	make --directory=build clean 1> /dev/null 2> cleanlog.txt
	if [ -s build/config.h ]; then
		echo "Deleting config.h."
		rm -f build/config.h 1> /dev/null 2> cleanlog.txt
	fi

	if [ -s cleanlog.txt ]; then
		echo "Error with clean. View cleanlog.txt for details."
	else	
		echo "Done!"
		rm -f cleanlog.txt
	fi
	exit
fi

# Uninstallation script.
if [ $UNINSTALL == 1 ]; then
	# Check that logfile doesn't exist.
	if [ -s uninstalllog.txt ]; then
		rm -f uninstalllog.txt
	fi

	#Make uninstall script and clean.
	echo "Uninstalling dwm binary and man."
	sudo make --directory=build uninstall 1> /dev/null 2> uninstalllog.txt
	"${0}" --clean
	
	# Removing scripts from their designated places
	if [ -s /usr/local/bin/dwm-start ]; then
		echo "Deleting dwm-start script."
		sudo rm -f /usr/local/bin/dwm-start 1> /dev/null 2> uninstalllog.txt
	fi
	
	if [ -s $HOME/.config/dwm/scripts/volumecontrol ]; then
		echo "Deleting scripts in config folder."
		for script in $configscripts; do
			rm -rf $HOME/.config/dwm/scripts/$script 1> /dev/null 2> uninstalllog.txt
		done
	fi

	if [ -s /usr/share/xsessions/dwm.desktop ]; then
		echo "Deleting dwm-start script."
		sudo rm -f /usr/share/xsessions/dwm.desktop 1> /dev/null 2> uninstalllog.txt
	fi

	if [ -s uninstalllog.txt ]; then
		echo "Uninstalling finished with errors. Check uninstalllog.txt."
	else
		echo "Done!"
		rm -f uninstalllog.txt
	fi
	exit
fi


# Install dwm to usr/local/bin.
if [ $BUILD == 1 ]; then
	PKG1=0
	PKG2=0
	PKG3=0
	PKG4=0
	pckglist="feh pamixer brightnessctl picom"
	if [[ -s /usr/bin/pacman ]]; then
		gr='\e[32m'
		nr='\e[39m'
		if $(pacman -Qi feh &>/dev/null); then
			PKG1=1
			echo "    [ ✓ ] feh is installed."
		else
			echo "    [ ❌] feh is not installed."
		fi
		if $(pacman -Qi pamixer &> /dev/null); then
			PKG2=1
			echo "    [ ✓ ] pamixer is installed."
		else
			echo "    [ ❌] pamixer is not installed."
		fi
		if $(pacman -Qi brightnessctl &> /dev/null); then
			PKG3=1
			echo "    [ ✓ ] brightnessctl is installed."
		else
			echo "    [ ❌] brightnessctl is not installed."
		fi
		if $(pacman -Qi picom &> /dev/null); then
			PKG4=1
			echo "    [ ✓ ] picom is installed."
		else
			echo "    [ ❌] picom is not installed."
		fi
		if [ $PKG1 == 0 ] || [ $PKG2 == 0 ] || [ $PKG3 == 0 ] || [ $PKG4 == 0 ]; then
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


	if [[ -s dwminstalllog.txt ]]; then
		rm dwminstalllog.txt
	fi

	if [ $CONFIG == 0 ] && [ -s build/config.h ]; then
		"${0}" --clean
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

# Copy scripts to .config/dwm
echo "Copying config scripts"
for script in $configscripts; do
	cp scripts/$script "$HOME"/.config/dwm/scripts/$script 1> /dev/null 2>dwmcopyscriptslog.txt
done

# Copy dwm.desktop to /usr/share/xsessions
echo "Copying dwm.desktop to /usr/share/xsessions/dwm.desktop"
sudo cp scripts/dwm.desktop /usr/share/xsessions/dwm.desktop 1> /dev/null 2>dwmcopyscriptslog.txt

if [[ -s dwmcopyscriptslog.txt ]]; then
	echo "Error with copying the scripts. Check logs at dwmcopyscriptslog.txt in this directory."
else
	echo "Copied all scripts succesfully!"
	rm dwmcopyscriptslog.txt
fi

if [[ -s dwmcopyscriptslog.txt ]] || [[ -s dwminstalllog.txt ]]; then
		echo "Installation finished with errors."
		exit 1
	else
		echo "Installation completed!"
fi
