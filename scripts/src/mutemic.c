#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>

void freestruct(struct dirent** input, int n) {
	while (n--)
		free(input[n]);
	free(input);
}

int isnumber(char* string) {
	for (int i = 0; i < strlen(string); i++)
		if (string[i] > '9' || string[i] < '0')
			return 0;
	return 1;
}

int main(void) {
	FILE* fp;
	fp = popen("pamixer --source 3 --toggle-mute", "r");
	if (fp == NULL) {
		perror("dwm-mutemic: Failed to execute pamixer command");
		exit(EXIT_FAILURE);
	}
	pclose(fp);
	struct dirent** pidlist;

	int funcret = scandir("/proc", &pidlist, NULL, alphasort); 
	if (funcret == -1) {
		perror("dwm-mutemic: Failed to scand /proc directory");
		freestruct(pidlist, funcret);
		exit(EXIT_FAILURE);
	}
	
	char buffer[128];
	char filename[128];
	int pid = -1;

	for (int i = 0; i < funcret; i++) {
		if (isnumber(pidlist[i]->d_name)) {
			strcpy(filename, "/proc/");
			strcat(filename, pidlist[i]->d_name);
			strcat(filename, "/cmdline");
			fp = fopen(filename, "r");
			if (fp == NULL) {
				fclose(fp);
				continue;
			}
			fgets(buffer, sizeof(buffer), fp);
			fclose(fp);
			if (strstr(buffer, "dwmblocks") != NULL) { 
				pid = strtol(pidlist[i]->d_name, NULL, 10);
				break;
			}
		}
	}

	if (pid == -1) {
		perror("dwm-mutemic: dwmblocks not running");
		freestruct(pidlist, funcret);
		exit(EXIT_FAILURE);
	}

	kill(pid, SIGRTMIN + 10);
	freestruct(pidlist, funcret);
	return 0;
}
