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
	printf("Searcher no: %d reporting\n",getpid());
	int flag=0;
	char **shm;
	int counter=0;
	int rnd;
	printf("My args were: %s %s\n",argv[0],argv[1]);
	key_t key = atoi(argv[1]);
	srand( time(NULL) );
	int shmid;
	int i;
	if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("Error locating shared memory segment\n");
        exit(EXIT_FAILURE);
    }
    printf("I got shmid:%d\n",shmid);
	if ((shm = shmat(shmid, NULL, 0)) == (char**) -1) {
        perror("Error attaching shared memory segment\n");
        exit(EXIT_FAILURE);
    }
    // Open file with list entries and load it on memory
	printf("my argument is %s\n",argv[0]);
	sleep(15);
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
	
	
	printf("I am awake!!\n");
	i=0;
	
	while(i<15) {
	rnd = rand() % counter;
	
	printf("Goint to search for %s",records[rnd]);

	
	rnd = rand() % counter;
	int j=0;
	while(shm[j]!=NULL) {
		if( strncmp(shm[j],records[rnd],strlen(records[rnd])) == 0) {
			flag == 1;
			break;
		}
		j++;
	}
	if(flag==1) { printf("Record found at index: %d!\n",j); }
	i++;
}
        
	return EXIT_SUCCESS;
}	
