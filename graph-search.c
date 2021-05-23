#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10


typedef struct node {
	int vertex; //정점을 나타내는 데이터 필드
	struct node *link; //다음 인접 정점을 연결하는 링크 필드.
} node;

typedef struct Graphlist{
	node *graph[MAX_VERTEX]; //그래프 정점에 대한 헤드 노드
	int n; // 그래프의 정점의 개수
}Graphlist;

void InitializeGraph(Graphlist *g);
void PrintGraph(Graphlist *g);
void InsertVertex(Graphlist *g);
void InsertEdge(Graphlist *g, int x, int y);
void DeleteGraph(Graphlist *g);
int main()
{
	char command;
	int x,ver;
	Graphlist *main=NULL;


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
			InitializeGraph(main);
			break;

		case 'q': case 'Q':
			DeleteGraph(main);
			break;

		case 'v': case 'V':
			InsertVertex(main);
			break;
		case 'd': case 'D':
			break;

		case 'b': case 'B':
			break;

		case 'e': case 'E':
			printf("Two Vertex: ");
			fflush(stdout);
			scanf("%d %d",&x,&ver);
			InsertEdge(main,x,ver);
			break;

		case 'p': case 'P':
			PrintGraph(main);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');

	return 1;
}

void PrintGraph(Graphlist *g){ //그래프 g의 각 정점에 대한 인접리스트를 출력하는 연산
	int i;
	node *now=NULL;
	for(i=0;i<g->n;i++){
		printf("\t%c :  ",i+65);
		for(now=g->graph[i]; now!=NULL; now=now->link)
			printf(" -> %c",now->vertex+65);
	}
}

void InitializeGraph(Graphlist *g){
	int v;
	g->n=0; //그래프의 정점의 개수를 0으로 초기화
	for(v=0;v<MAX_VERTEX;)
		g->graph[v]=NULL; //그래프 정점에 대한 헤드노드 배열을 NULL로 초기화
}

void InsertVertex(Graphlist *g){
	if((g->n)+1>MAX_VERTEX){ //정점이 최대값보다 클 경우 오류출력후 종료
		printf("graph is full\n");
		return;
	}
	g->n++; //vertex을 하나 올려준다.
}

void InsertEdge(Graphlist *g, int x, int ver){ //그래프 g에 간선(u,v)를 삽입하는 연산.
	node *nd;
	if(x>=g->n || ver>=g->n){ //x나 ver이 정점보다 크거나 같을 경우.
		printf("graph number ERROR\n");
		return;
	}
	nd =(node *)malloc(sizeof(node));
	nd->vertex=ver; //입력받은 ver값을 정점의 데이터 필드에 넣어준다.
	nd->link=g->graph[x]; // nd의 link이 g의 graph[x]를 가리키게한다.
	g->graph[x]=nd; //g의 graph[x]값을 nd에 넣는다.
}

void DeleteGraph(Graphlist *g){
	int i;
	node *now,*next; //현재값과 그다음값을 받을 포인터.
	for(i=0;i<g->n;i++){ //정점의 끝까지 반복.
		now=g->graph[i]; //now는 graph[i]를 가리킨다.
		while(now !=NULL){ //graph의 끝까지 반복.
			next=now->link; //next에 now의 다음값을 받는다.
			free(now);//now의 메모리를 해제한다.
			now=next; //now에 next값을 넣는다.
		}
	}
}
