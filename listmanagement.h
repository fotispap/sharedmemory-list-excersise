
typedef struct listnode *Listptr;

struct listnode {
  char *value;
  Listptr next;
};


int empty(Listptr list);
int in(Listptr list, char *v);

int print(Listptr list,char *v);
void insert_at_end(Listptr *ptraddr, char *v);
int delete(Listptr *ptraddr, char *v);

