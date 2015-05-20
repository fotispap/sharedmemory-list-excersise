/* Author: Fotis Papaodisseas
 * AM: 11152005262
 * Leitourgika 2011 - Project 1
 *   
 * 
 */ 


#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "listmanagement.h"

#define SHMSZ 26

int main(int argc, char* argv[]) {
	if(argc!=5) { printf("\nUsage: ./sharedlist <#S> <#D> <#I> <records_file>\nExample: ./sharedlist 2 1 3 records.txt \n"); exit(-1); }
	
	int S = atoi(argv[1]);
	int D = atoi(argv[2]);
	int I = atoi(argv[3]);
	pid_t pid;
	key_t key = 666999;
	int shmid;
	char **shm;
	
	shm = NULL;
	int i,status=0;
	printf("Going to create %d Search, %d Delete and %d Insert proccesses\n",S,D,I);
	
	/* Creating shared memory segment */
	if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("Error creating shared memory segment\n");
        exit(EXIT_FAILURE);
    }
    printf("I got shmid:%d\n",shmid);
    if ((shm = shmat(shmid, NULL, 0)) == (char**) -1) {
        perror("Error attaching shared memory segment\n");
        exit(EXIT_FAILURE);
    }
    shm = malloc(sizeof(char*)*256);
    for(i=0;i<256;i++) shm[i] = malloc(256);
    shm[0] = NULL;
	char shmid_arg[8];
	snprintf(shmid_arg,8,"%d",shmid);
	char key_arg[8];
	snprintf(key_arg,8,"%d",key);
	
	/* Forking child proccesses */
	for(i=0;i<S;i++) {
		if( (pid=fork()) == 0) {
			execlp("./searcher",argv[4],key_arg,NULL);
		} else {
			continue;
		}
	}
	for(i=0;i<D;i++) {
		if( (pid=fork()) == 0) {
			execlp("./deleter",argv[4],key_arg,NULL);
		} else {
			continue;
		}
	}
	for(i=0;i<I;i++) {
		if( (pid=fork()) == 0) {
			execlp("./inserter",argv[4],key_arg,NULL);
		} else {
			continue;
		}
	}
	/* Waiting for childs to finish */
	for(i=0;i<I+S+D;i++) {
		waitpid(-1,&status,NULL);
		printf("child returned with status: %d\n",status);
	}
	
			
	
} 
