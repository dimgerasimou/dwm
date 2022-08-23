/* Executable that determines if an HDMI output is connected and sets the appropriate settings. */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
	char* args[]= { "xrandr", "--output", "HDMI-0", "--auto", "--primary", "--right-of", "eDP-1-1", (char*)NULL };
	FILE* fp = popen("/bin/xrandr", "r");

	if (fp == NULL) {
		perror("dwm-xrandr: Failed to execute xrandr");
		return 1;
	}

	char input[128];
	char firstin[128];
	int first = 1;

	while (fgets(input, sizeof(input), fp) != NULL) {
		if (first) {
			strcpy(firstin, input);
			first = 0;
		}
		if (strstr(input, "HDMI-0") != NULL) {
			if (execv("/bin/xrandr", args) == -1) {
				perror("dwm-xrandr: Failed to execute command.");
				pclose(fp);
				return 1;
			}
			break;
			
		}
	}
	if (pclose(fp)) {
		fprintf(stderr, "dwm-xrandr: ERROR: xrandr: %s\n", firstin);
		return 1;
	}
	return 0;
}
