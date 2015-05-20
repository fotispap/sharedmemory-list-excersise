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

#define SHMSZ 27

int main(int argc, char* argv[]) {
	printf("Deleter no: %d reporting\n",getpid());
	
	Listptr shm;
	int shmid;
	key_t key = atoi(argv[1]);
	printf("My args were: %s %s\n",argv[0],argv[1]);
	if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        printf("Error locating shared memory segment\n");
        exit(EXIT_FAILURE);
    }
    printf("I got shmid:%d\n",shmid);
	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        printf("Error attaching shared memory segment\n");
        exit(EXIT_FAILURE);
    }
    sleep(60);

	return 0;
}	
