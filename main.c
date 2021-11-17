#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct nodo2
{
	char nome[40];
	char rel[40];
	struct nodo2 *parent;
	struct nodo2 *right;
	struct nodo2 *left;
};
typedef struct nodo2 *tree2;

struct nodo1
{
	char nome[40];
	struct nodo2 *p;
	struct nodo1 *parent;
	struct nodo1 *right;
	struct nodo1 *left;
};
typedef struct nodo1 *tree1;

struct nodo3
{
	char nome[40];
	int num;
	struct nodo3 *next;
};

typedef struct nodo3 *lista1;

struct nodo4
{
	char rel[40];
	struct nodo4 *next;
	struct nodo3 *punt;
};

typedef struct nodo4 *lista2;


// COMMAND FUNCTIONS
tree1 addent(char id_ent[], tree1 t);
tree1 delent(char id_ent[], tree1 t,lista2 *l);
tree1 addrel(char id_orig[], char id_dest[], char id_rel[], tree1 t,lista2 *l);
tree1 delrel(char id_orig[], char id_dest[], char id_rel[], tree1 t);
void report(lista2 l);
// UTILITY FUNCTIONS
// void print_tree(tree1 t);
// void print_tree2(tree2 t);
 void print_list(lista2 l);
// void print_list1(lista1 l);
void delete_id(char id_ent[],char id_dest[],tree2 * t,lista2 *l);
void delete_rel_id(char id_ent[], tree1 * t,lista2 *l);
lista2 rel_null(lista2 l);
void insert_list(lista2 *l, char id_rel[], char id_dest[]);
void insert_rel(lista1 * l, char id_dest[]);
lista2 delete_rel(lista2 l, char id_rel[], char id_dest[]);
int max_list(lista1 l);
lista2 delent_list(lista2 l,char id_ent[]);

tree1 tree_search(char id_ent[], tree1 t);
tree1 tree_successor(tree1 p);
tree1 tree_minimum(tree1 x);

tree2 tree_search_id_rel(char id_orig[], char id_rel[], tree2 x);
tree2 tree_successor2(tree2 p);
tree2 tree_minimum2(tree2 x);
tree2 tree_search2(char id_ent[], tree2 t);
tree2 tree_rel_search2(char id_orig[], char id_rel[], tree2 t);
int main()
{
	freopen("batch5.2.in","r", stdin);
	tree1 t = NULL, q = NULL;
	int end = 0,cont=0;
	char func[10];
	char id_ent[40];
	char id_orig[40];
	char id_dest[40];
	char id_rel[30];
	char buffer[100];
	lista2 l = NULL;
	do
	{
		
		scanf("%s", func);

		if (strcmp(func, "addent") == 0)
		{
			scanf("%s", id_ent);
			fgets(buffer, 100, stdin);
			t = addent(id_ent, t);
		}

		else if (strcmp(func, "delent") == 0)
		{
			scanf("%s", id_ent);
			fgets(buffer, 100, stdin);
			if(tree_search(id_ent,t)!=NULL)
			{
			t = delent(id_ent, t,&l);
			l=delent_list(l,id_ent);
		        }
		}

		else if (strcmp(func, "addrel") == 0)
		{
			scanf("%s", id_orig);
			scanf("%s", id_dest);
			scanf("%s", id_rel);
			fgets(buffer, 100, stdin);
			t = addrel(id_orig, id_dest, id_rel, t,&l);
				
		

		}

		else if (strcmp(func, "delrel") == 0)
		{
			scanf("%s", id_orig);
			scanf("%s", id_dest);
			scanf("%s", id_rel);
			fgets(buffer, 100, stdin);
			if ((tree_search(id_orig, t)) != NULL && (q = tree_search(id_dest, t)) != NULL)
			{
				tree2 s;
				if ((s = tree_rel_search2(id_orig, id_rel, q->p)) != NULL)
				{
					l = delete_rel(l, id_rel, id_dest);
					t = delrel(id_orig, id_dest, id_rel, t);
				}
			}
		}

		else if (strcmp(func, "report") == 0)
		{
			fgets(buffer, 100, stdin);
			cont++;
			report(l);
		}
		else if (strcmp(func, "end") == 0)
		{
			fgets(buffer, 100, stdin);
			end = 1;
		}
		else
		{
			printf("Comando scorretto riprovare\n");
			fgets(buffer, 100, stdin);
			continue;
		}
		
	}
	while (end == 0);

	return 0;

}


// FUNCTIONS IMPLEMENTATION

  void print_list(lista2 l) 
   { 
    while(l!=NULL)
    { 
    printf("%s-- ",l->rel);
    lista1 x;
    x=l->punt;
    while(x!=NULL){
     printf("%s %d",x->nome,x->num);
     x=x->next;}
     printf("|| ");
     l=l->next; 
    } 
    printf("\n\n");
   }  
lista2 rel_null(lista2 l)
{
 lista2 x,y;
 if(l!=NULL)
 {
  if(l->punt==NULL){
   l=l->next;
   //free(y);
  }
   
  rel_null(l);
  
 }
}
  
  
int max_list(lista1 l)
{
	int max = 0;
	while (l != NULL)
	{
		if (l->num > max)
			max = l->num;
		l = l->next;
	}
	return max;
}

tree1 tree_search(char id_ent[], tree1 t)
{
	if (t == NULL || (strcmp(id_ent, t->nome)) == 0)
		return t;
	else if ((strcmp(id_ent, t->nome)) < 0)
		return tree_search(id_ent, t->left);
	else
		return tree_search(id_ent, t->right);
}

tree2 tree_search2(char id_ent[], tree2 t)
{
	if (t == NULL || (strcmp(id_ent, t->nome)) == 0)
		return t;
	if ((strcmp(id_ent, t->nome)) < 0)
		return tree_search2(id_ent, t->left);
	else
		return tree_search2(id_ent, t->right);
}

tree2 tree_rel_search2(char id_orig[], char id_rel[], tree2 t)
{
	if (t == NULL || (strcmp(id_orig, t->nome) == 0 && strcmp(id_rel, t->rel) == 0))
		return t;
	if (strcmp(id_orig, t->nome) < 0)
		return tree_rel_search2(id_orig,id_rel, t->left);
	else
		return tree_rel_search2(id_orig,id_rel, t->right);
}

tree2 tree_search_id_rel(char id_orig[], char id_rel[], tree2 x)
{
	if (x == NULL || (strcmp(id_orig, x->nome) == 0 && strcmp(id_rel, x->rel)== 0))
		return x;
	if (strcmp(id_orig, x->nome) < 0)
		return tree_search_id_rel(id_orig,id_rel,x->left);
	else
		return tree_search_id_rel(id_orig,id_rel,x->right);
}

tree1 tree_minimum(tree1 x)
{
	while (x->left != NULL)
		x = x->left;
	return x;
}

tree2 tree_minimum2(tree2 x)
{
	while (x->left != NULL)
		x = x->left;
	return x;
}

tree1 tree_successor(tree1 p)
{
	tree1 y = NULL;
	if (p->right != NULL)
		return tree_minimum(p->right);
	y = p->parent;
	while (y != NULL && p == y->right)
	{
		p = y;
		y = y->parent;
	}
	return y;
}

tree2 tree_successor2(tree2 p)
{
	tree2 y = NULL;
	if (p->right != NULL)
		return tree_minimum2(p->right);
	y = p->parent;
	while (y != NULL && p == y->right)
	{
		p = y;
		y = y->parent;
	}
	return y;
}

void delete_id(char id_ent[],char id_dest[],tree2 *t,lista2 *l)
{
	tree2 q;
        while((q=tree_search2(id_ent,*t))!=NULL)
         {
          *l=delete_rel(*l,q->rel,id_dest);         
	               tree2 p = NULL, y = NULL, x = NULL;
			int i;
			p = q;
			if (p->left == NULL || p->right == NULL)
				y = p;
			else
				y = tree_successor2(p);
			if (y->left != NULL)
				x = y->left;
			else
				x = y->right;
			if (x != NULL)
				x->parent = y->parent;
			if (y->parent == NULL)
				(*t) = x;	
			else if (y == (y->parent->left))
				y->parent->left = x;
			else
				y->parent->right = x;
			if (y != p)
			{
				for (i = 0; y->nome[i] != '\0'; i++)
					p->nome[i] = y->nome[i];
                                p->nome[i]='\0';            
				for (i = 0; y->rel[i] != '\0'; i++)
					p->rel[i] = y->rel[i];
                                p->rel[i]='\0';     
			}
			free(y);
			
		}			
}

void delete_rel_id(char id_ent[], tree1 * t,lista2 *l)
{
	if ((*t) != NULL)
	{
		delete_rel_id(id_ent, &((*t)->left),&(*l));
		if ((*t)->p != NULL)
		{
			delete_id(id_ent,(*t)->nome,&((*t)->p),&(*l));

		}
		delete_rel_id(id_ent, &((*t)->right),&(*l));
	}
}

void insert_list(lista2 *l, char id_rel[], char id_dest[])
{
	int i;
	lista2 q;
	q = malloc(sizeof(struct nodo4));
	if (*l == NULL)
	{
		for (i = 0; id_rel[i] != '\0'; i++)
			q->rel[i] = id_rel[i];
                q->rel[i]='\0';    
		q->next = *l;
		*l = q;
		q->punt = NULL;
		insert_rel(&(q->punt), id_dest);
	}
	else
	{
		lista2 x,y = NULL;
		x = *l;
		while (x != NULL && strcmp(x->rel, id_rel) < 0)
		{
			y = x;
			x = x->next;
		}

		if (x == NULL && strcmp(y->rel, id_rel) < 0)
		{
			q->next = x;
			y->next = q;
			for (i = 0; id_rel[i] != '\0'; i++)
                         q->rel[i] = id_rel[i];
                        q->rel[i]='\0';       
			q->punt = NULL;
			insert_rel(&(q->punt), id_dest);
		}
		else if (x != NULL && strcmp(x->rel, id_rel) > 0)
		{
			q->next = x;
			if (y == NULL)
		         *l = q;
			else
			 y->next = q;
			for (i = 0; id_rel[i] != '\0'; i++)
			 q->rel[i] = id_rel[i];
                        q->rel[i]='\0';         
			q->punt = NULL;
			insert_rel(&(q->punt), id_dest);
		}
		else if (x != NULL && strcmp(x->rel, id_rel) == 0)
		{
			free(q);
			insert_rel(&(x->punt), id_dest);
		}

	}
	
}

void insert_rel(lista1 * l, char id_dest[])
{
	int i;
	lista1 q;
	q = malloc(sizeof(struct nodo3));
	if (*l == NULL)
	{
		for (i = 0; id_dest[i] != '\0'; i++)
	         q->nome[i] = id_dest[i];
                q->nome[i]='\0';    
		q->num = 1;
		q->next = *l;
		*l = q;
	}
	else
	{
		lista1 x, y = NULL;
		x = *l;
		while (x != NULL && strcmp(x->nome, id_dest) < 0)
		{
			y = x;
			x = x->next;
		}

		if (x == NULL && strcmp(y->nome, id_dest) < 0)
		{
			q->next = x;
			y->next = q;
			for (i = 0; id_dest[i] != '\0'; i++)
			 q->nome[i] = id_dest[i];
                        q->nome[i]='\0';         
			q->num = 1;
		}
		else if (x != NULL && strcmp(x->nome, id_dest) > 0)
		{
			q->next = x;
			if (y == NULL)
			 *l = q;
			else
			 y->next = q;
			for (i = 0; id_dest[i] != '\0'; i++)
			 q->nome[i] = id_dest[i];
                        q->nome[i]='\0';        
			q->num = 1;
		}
		else if (x != NULL && strcmp(x->nome, id_dest) == 0)
		{
			free(q);
			x->num = x->num + 1;
		}
	}
}

lista2 delete_rel(lista2 l, char id_rel[], char id_dest[])
{
	lista2 x;
	x = l;

	while (x != NULL && strcmp(id_rel, x->rel) != 0)
	 x = x->next;
		

	if (x != NULL)
	{
		lista1 q = x->punt, s = NULL;
		while (q != NULL && strcmp(q->nome, id_dest) != 0)
		{
			s = q;
			q = q->next;
		}
		if (q != NULL)
		{       
			q->num = q->num - 1;
			if (q->num == 0)
			{
				if (s == NULL && q->next == NULL)
					x->punt = s;
				else if (s == NULL && q->next != NULL)
				{
					x->punt = q->next;
				}
				else
					s->next = q->next;
				free(q);

			}
		}


	}

 return l;
}

lista2 delent_list(lista2 l,char id_ent[])
{
 lista2 x;
 lista1 q;
 x=l;
 while(x!=NULL)
 {
  lista1 prec=NULL;
  q=x->punt;
  while(q!=NULL && strcmp(q->nome,id_ent)!=0)
  {
   prec=q;
   q=q->next;
  }
  if(q!=NULL && strcmp(q->nome,id_ent)==0)
    {
     if(prec==NULL){
      x->punt=q->next;
      }
     else
      prec->next=q->next;
     free(q);
    }
  x=x->next;
 }
 return l;
}
  
tree1 addent(char id_ent[], tree1 t)
{
	tree1 q = NULL, y = NULL, x = NULL;
	int i;
	q = malloc(sizeof(struct nodo1));
	x = t;
	while (x != NULL)
	{
		y = x;					// father
		if (strcmp(id_ent, x->nome) < 0)
			x = x->left;
		else if (strcmp(id_ent, x->nome) > 0)
			x = x->right;
		else
			return t;
	}
	if (y == NULL)
		t = q;
	else if (strcmp(id_ent, y->nome) < 0)
		y->left = q;
	else if (strcmp(id_ent, y->nome) > 0)
		y->right = q;
	else
	{
		free(q);
		return t;
	}
	q->parent = y;
	for (i = 0; id_ent[i] != '\0'; i++)
		q->nome[i] = id_ent[i];
        q->nome[i]='\0'; 
	q->p = NULL;
	q->right = NULL;
	q->left = NULL;
	return t;
}

tree1 delent(char id_ent[], tree1 t,lista2 *l)
{
	tree1 r = NULL, y = NULL, x = NULL;
	int i;
		delete_rel_id(id_ent, &t,&(*l));
		r = tree_search(id_ent, t);
		if (r->left == NULL || r->right == NULL)
			y = r;
		else
			y = tree_successor(r);
		if (y->left != NULL)
			x = y->left;
		else
			x = y->right;
		if (x != NULL)
			x->parent = y->parent;
		if (y->parent == NULL)
		{
			t = x;
			return t;
		}
		else if (y == (y->parent->left))
			y->parent->left = x;
		else
			y->parent->right = x;
		if (y != r)
		{
	         for (i = 0; y->nome[i] != '\0'; i++)
		  r->nome[i] = y->nome[i];
                 r->nome[i]='\0';         
		 r->p=y->p;
		}
		free(y);
		return t;
  
}

tree1 addrel(char id_orig[], char id_dest[], char id_rel[], tree1 t,lista2 *l)
{
	int i;
	tree1 p = NULL, r = NULL;
	tree2 q = NULL, x = NULL, y = NULL;
	if ((r = tree_search(id_orig, t)) != NULL && (p = tree_search(id_dest, t)) != NULL)
	{
	 if (tree_rel_search2(id_orig, id_rel, p->p) == NULL)
	  {
		x = p->p;
		q = malloc(sizeof(struct nodo2));
		while (x != NULL)
		{
			y = x;				// father
			if (strcmp(id_orig, x->nome) < 0)
				x = x->left;
			else
				x = x->right;
		}
		if (y == NULL)
			p->p = q;
		else if (strcmp(id_orig, y->nome) < 0)
			y->left = q;
		else
			y->right = q;
		q->parent = y;

		for (i = 0; id_orig[i] != '\0'; i++)
			q->nome[i] = id_orig[i];
                q->nome[i]='\0';      
		for (i = 0; id_rel[i] != '\0'; i++)
			q->rel[i] = id_rel[i];
                q->rel[i]='\0';    
		q->right = NULL;
		q->left = NULL;
		insert_list(&(*l), id_rel, id_dest);
	 }
		
	}
        
	return t;
}

tree1 delrel(char id_orig[], char id_dest[], char id_rel[], tree1 t)
{
	tree1 w = NULL;
	tree2 q = NULL, z = NULL, x = NULL, y = NULL;
	int i;
	w = tree_search(id_dest, t);
	if (w != NULL)
	{
		z = w->p;
		q = tree_search_id_rel(id_orig, id_rel, z);
		if (q != NULL)
		{
			if (q->left == NULL || q->right == NULL)
				y = q;
			else
				y = tree_successor2(q);
			if (y->left != NULL)
				x = y->left;
			else
				x = y->right;
			if (x != NULL)
				x->parent = y->parent;
			if (y->parent == NULL)
				w->p = x;
			else if (y == (y->parent->left))
				y->parent->left = x;
			else
				y->parent->right = x;
			if (y != q)
			{
				for (i = 0; y->nome[i] != '\0'; i++)
					q->nome[i] = y->nome[i];
                                q->nome[i]='\0';          
 				for (i = 0; y->rel[i] != '\0'; i++)
					q->rel[i] = y->rel[i];
                                q->rel[i]='\0';          

			}
		}
	free(y);
	
}
return t;
}
void report(lista2 l)
{
	lista2 x;
	x = l;
	int max,control=0,prov=0;
	if (x == NULL)
	{
	        prov=1;
		fputs("none",stdout);
        }
	while (x != NULL)
	{
	        int cont=0;
		max = max_list(x->punt);
		lista1 p;
		p = x->punt;
		if(x->punt!=NULL)
		{
		 fputs(x->rel,stdout);
		 fputs(" ",stdout);
		 control=1;
		}
		while (p != NULL)
		{
			if (p->num == max){
				fputs(p->nome,stdout);
				fputs(" ",stdout);
		        }
			cont++;	
			p = p->next;
		
		}
		if(cont!=0)
		 printf("%d; ", max);
		x = x->next;
	}
        if(prov==0 && control==0)
         fputs("none",stdout);
	printf("\n");
}
