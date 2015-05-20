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
#include <time.h>

#include "listmanagement.h"

#define SHMSZ 26

int main(int argc, char* argv[]) {
	
	printf("Inserter no: %d reporting\n",getpid());
	char **shm;
	Listptr shm1;
	sleep(1);
	shm1 = NULL;
	int counter=0;
	int rnd;
	key_t key = atoi(argv[1]);
	srand( time(NULL) );
	int shmid;
	int i;
	printf("My args were: %s %s\n",argv[0],argv[1]);
	if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        printf("Error locating shared memory segment\n");
        exit(EXIT_FAILURE);
    }
    printf("I got shmid:%d\n",shmid);
	if ((shm = shmat(shmid, NULL, 0)) == (char**) -1) {
        printf("Error attaching shared memory segment\n");
        exit(EXIT_FAILURE);
    }
    // Open file with list entries and load it on memory
	FILE *fd = fopen(argv[0], "r");
	char buf[256];
	while(fgets(buf,256,fd) != NULL) {
		counter++;
	}
	printf("file has %d lines\n",counter);
	rewind(fd);
	char **records;
	records = (char**) malloc(counter*sizeof(char*));
	for(i=0;i<counter;i++) 
		records[i] = malloc(256);
	i=0;
	while(fgets(records[i],256,fd) != NULL) {
		//printf("%s",records[i]);
		i++;
	}
	// Pick a random line from the file and insert it at the end of the list
	i=0;
	while(i<99) {
	
	rnd = rand() % counter;
	int j=0;
	printf("go\n");
	while(shm[j]!=NULL) {
		j++;
	}
	strncpy(shm[j],records[rnd],strlen(records[rnd]));
	printf("inserted %s at %d\n",shm[j],j);
	shm[j+1]=NULL;
	
	/*
	if(empty(shm)==1) { printf("list empty\n"); }
	else { printf("list not empty\n"); }
	printf("Goint to insert %s",records[rnd]);
	
	insert_at_end(&shm, records[rnd]);
	*/
	
	i++;
	}
	/*i=0;
	print(shm, records[rnd]);
	while(i<15) {
	rnd = rand() % counter;
	
	printf("Goint to search for %s",records[rnd]);
	
	if(print(shm, records[rnd])==0) { 
		printf("The line does not exist\n");
	} else { 
		printf("The line exists\n");
	}
	i++;
} */
	sleep(40);
	
	return 0;
}	
