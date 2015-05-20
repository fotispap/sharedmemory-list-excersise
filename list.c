void insert_at_end(Listptr *ptraddr, int v)
/* Insert v as last element of list *ptraddr
{ while (*ptraddr != NULL)
/* Go to end of list
ptraddr = &((*ptraddr)->next);/* Prepare what we need to change
*ptraddr = malloc(sizeof(struct listnode)); /* Space for new node
(*ptraddr)->value = v;
/* Put value
(*ptraddr)->next = NULL;
/* There is no next element
}
