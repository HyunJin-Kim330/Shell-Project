#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void handler_Ctrl_C(int), handler_Ctrl_Z(int);

main(){
	char buf[256];
	char *argv[50];
	int narg;
	pid_t pid;

	while(1){
		printf("HJYJ_shell> ");
		gets(buf);
		narg = getargs(buf, argv);
		pid = fork();

		if(pid == 0)
			execvp(argv[0], argv);
		else if(pid > 0)
			wait((int *)0);
		else
			perror("fork failed");	

	}
}

int getargs(char *cmd, char **argv){
	int narg = 0;
	
	while(*cmd){
		if(*cmd == ' ' || *cmd == '\t')
			*cmd++ = '\0';
		else{
			argv[narg++] = cmd++;
			while(*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
				cmd++;
		}
	}
	argv[narg] = NULL;
	return narg;
}
