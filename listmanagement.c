/* Author: Fotis Papaodisseas
 * AM: 11152005262
 * Leitourgika 2011 - Project 1
 *   
 * */
 
 
 
  /* The list management functions
  * are taken from the program listmanagement.c
  * included in the notes of Takis Stamatopoulos
  * for the course Introduction to Programming */
  
  
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listmanagement.h"

#define MAX_LINE 512;


int empty(Listptr list)                   /* Check if list is empty */
{ if (list == NULL)                          /* Is it really empty? */
    return 1;                                         /* Yes, it is */
  else
    return 0;                                       /* No, it isn't */
}

int in(Listptr list, char *v)         /* Check if v is member of list */
{ 
	
	while (list != NULL) {         /* Visit list elements up to the end */
		printf("%s--> ", list->value);  
		if (strcmp(v,list->value)==0)  { /* Did we find what we are looking for? */    
			return 1;                   
		} else {
			list = list->next;      
		}
     }            /* No, go to next element */
  return 0;                            /* Finally, v is not in list */
}


void insert_at_end(Listptr *ptraddr, char *v)
                       /* Insert v as last element of list *ptraddr */
{ while (*ptraddr != NULL)                     /* Go to end of list */
    ptraddr = &((*ptraddr)->next);/* Prepare what we need to change */
  *ptraddr = malloc(sizeof(struct listnode)); /* Space for new node */
  (*ptraddr)->value = (char*) malloc(256);
  v[strlen(v)] = '\0';
  strncpy((*ptraddr)->value,v,strlen(v));       
   (*ptraddr)->value[strlen((*ptraddr)->value)] = '\0';                       /* Put value */ 
  (*ptraddr)->next = NULL;              /* There is no next element */
}

int delete(Listptr *ptraddr, char *v)
               /* Delete element v from list *ptraddr, if it exists */
{ Listptr templist;
  while ((*ptraddr) != NULL)   /* Visit list elements up to the end */
    if (strcmp(v,(*ptraddr)->value)==0) {    /* Did we find what to delete? */
      templist = *ptraddr;         /* Yes, save address of its node */
      *ptraddr = (*ptraddr)->next;        /* Bypass deleted element */
      free(templist);     /* Free memory for the corresponding node */
      return 1;                           /* We deleted the element */
    }
    else
      ptraddr = &((*ptraddr)->next);/* Prepare what we might change */
  return 0;        /* We did't find the element we were looking for */
}

int print(Listptr list, char *v)                  /* Print elements of list */
{
	char temp_value[256];
	
	while (list != NULL) {
		      /* Visit list elements up to the end */
	//sprintf(temp_value,"%s",list->value);
  //  printf("%s--> ", list->value);    
    sprintf(temp_value,"%s ", list->value); 
    //printf("Comparing\n%s%s",temp_value,v);
    if(strncmp(temp_value,v,strlen(v))==0) {
		printf("--------------FOUND-----");
		return 1;
	}
         /* Print current element */
    list = list->next;                        /* Go to next element */
  }
  printf("NULL\n"); 
  return 0;                           /* Print end of list */
}
