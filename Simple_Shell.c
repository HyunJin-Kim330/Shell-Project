#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void handler_Ctrl_C(int), handler_Ctrl_Z(int);  // 핸들러 전방선언

main(){
	char buf[256];
	char *argv[50];
	int narg;
	pid_t pid;
	
	struct sigaction sigint;  // sigaction 구조체 선언
	struct sigaction sigquit;

	sigint.sa_handler = handler_Ctrl_C;
	sigquit.sa_handler = handler_Ctrl_Z;
	sigfillset(&(sigint.sa_mask));
	sigfillset(&(sigquit.sa_mask));
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGTSTP, &sigquit, NULL);

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

void handler_Ctrl_C(int signo){  // ctrl-C 핸들러
	int ppid = getppid();
	printf("Call SIGINT by Ctrl-C!!!\n");
	kill(ppid, SIGINT);
}

void handler_Ctrl_Z(int signo){  // ctrl-Z 핸들러
	int ppid = getppid();
	printf("Call SIGQUIT by Ctrl-Z!!!\n");
	kill(ppid, SIGQUIT);
}
