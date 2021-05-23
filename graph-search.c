#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 30


typedef struct node {
	int vertex;
	struct node *link;
} Node;

typedef struct Graphlist{
	Node *graph[MAX_VERTEX];
	int vertex;
}Graphlist;

void InitializeGraph(Graphlist *g);
void PrintGraph(Graphlist *g);
void InsertVertex(Graphlist *g);
void InsertEdge(Graphlist *g);
int main()
{
	char command;
	printf("[----- [이연규] [2018038038] -----]");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Graph Searches                          \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                       \n");
		printf(" Insert Vertex          = v      Insert Edge                  = e \n");
		printf(" Depth First Search     = d      Breath First Search          = b \n");
		printf(" Print Graph            = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			break;
		case 'q': case 'Q':
			break;
		case 'v': case 'V':
			break;
		case 'd': case 'D':
			break;
		case 'b': case 'B':
			break;
		case 'e': case 'E':
			break;
		case 'p': case 'P':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}
void PrintGraph(Graphlist *g){
	int i;
	Node *now=NULL;
	for(i=0;i<g->vertex;i++){
		printf("%c :  ",'A'+i);
		for(now=g->graph[i]; now!=NULL; now=now->link)
			printf("%c -> ",'A'+now->vertex);
	}
}
void InitializeGraph(Graphlist *g){
	int v;
	g->vertex=0;
	for(v=0;v<MAX_VERTEX;)
		g->graph[v]=NULL;
}
void InsertVertex(Graphlist *g){
	
}
void InsertEdge(Graphlist *g){
	
}
