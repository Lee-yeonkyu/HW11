#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10
#define FALSE 0
#define TRUE 1

typedef struct node {
	int vertex; //정점을 나타내는 데이터 필드
	struct node *link; //다음 인접 정점을 연결하는 링크 필드.
} node;

typedef struct graphlist{
	node *graph[MAX_VERTEX]; //그래프 정점에 대한 헤드 노드
	int visted[MAX_VERTEX]; //정점에 대한 방문 표시를 위한 배열
	int n; // 그래프의 정점의 개수
}Graphlist;

typedef struct StackNode{
	int data;
	struct StackNode *link;
}StackNode;
StackNode *top;

typedef struct QNode{
	int data;
	struct QNode *link;
}QNode;

typedef struct{
	QNode *front, *rear;
}LQueueType;

void push(int item);
int pop();
LQueueType *createLinkedQueue();
int isEmpty(LQueueType *LQ);
void enQueue(LQueueType *LQ, int item);
int deQueue(LQueueType *LQ);
void InitializeGraph(Graphlist *g);
void PrintGraph(Graphlist *g);
void InsertVertex(Graphlist *g);
void InsertEdge(Graphlist *g, int x, int y);
void DeleteGraph(Graphlist *g);
void DFS(Graphlist *g,int v);
void BFS(Graphlist *g,int v);
int main()
{
	char command;
	int x,ver;
	Graphlist *G= NULL;
	G=(Graphlist *)malloc(sizeof(Graphlist));

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
			InitializeGraph(G);
			break;

		case 'q': case 'Q':
			DeleteGraph(G);
			break;

		case 'v': case 'V':
			InsertVertex(G);
			break;
		case 'd': case 'D':
			printf("Insert VERTEX : ");
			fflush(stdout);
			scanf("%d",&ver);
			DFS(G,ver);
			break;

		case 'b': case 'B':
			printf("Insert VERTEX : ");
			fflush(stdout);
			scanf("%d",&ver);
			BFS(G,ver);
			break;

		case 'e': case 'E':
			printf("Two Vertex: ");
			fflush(stdout);
			scanf("%d %d",&x,&ver);
			InsertEdge(G,x,ver);
			break;

		case 'p': case 'P':
			PrintGraph(G);
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
		printf("\t%c  =  ",i+65);
		for(now=g->graph[i]; now!=NULL; now=now->link)
			printf("-> %c\t",now->vertex+65);
		printf("\n");
	}
}

void InitializeGraph(Graphlist *g){
	int v;
	g->n=0; //그래프의 정점의 개수를 0으로 초기화
	for(v=0;v<MAX_VERTEX;v++){
		g->graph[v]=NULL; //그래프 정점에 대한 헤드노드 배열을 NULL로 초기화
		g->visted[v]=FALSE; // 그래프의 정점에 대한 배열 visted를 false로 초기화
	}

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
void push(int item)
{
	StackNode *temp=(StackNode *)malloc(sizeof(StackNode));
	temp->data=item;
	temp->link=top;
	top=temp;
}
int pop(){
	int item;
	StackNode *temp=top;

	if(top==NULL){
		printf("\n\n Stack is empty!\n");
		return 0;
	}
	else{
		item=temp->data;
		top=temp->link;
		free(temp);
		return item;
	}
}
void DFS(Graphlist *g,int v){
	node *w;
	top=NULL;
	push(v);
	g->visted[v]=TRUE;
	printf("%c",v+65);

	while(top!=NULL){//스택이 공백이 아닌 동안 우선 탐색 반복
		w=g->graph[v];
		while(w){
			if(!g->visted[w->vertex]){
				push(w->vertex);
				g->visted[w->vertex]=TRUE;
				printf("%c",w->vertex+65); //정점을 A~G로 바꾸어서 출력
				v=w->vertex;
				w=g->graph[v];
			}
			else
				w=w->link; //현재 정점w가 이미 방문 했을 경우.
		}
		v=pop();//현재 정점에서 더 이상 순회를 진행할게 없는 경우 pop
	}
	for(v=0;v<MAX_VERTEX;v++)
		g->visted[v]=FALSE;
}



LQueueType *createLinkedQueue(){
	LQueueType *LQ;
	LQ=(LQueueType *)malloc(sizeof(LQueueType));
	LQ->front=NULL;
	LQ->rear=NULL;

	return LQ;
}
int isEmpty(LQueueType *LQ){ //

	if(LQ->front==NULL){
		printf("\n Linked Queue is empty! \n");
		return 1;
	}
	else
		return 0;
}

void enQueue(LQueueType *LQ, int item){ //큐의 출력을 위한 함수.
	QNode* newNode=(QNode*)malloc(sizeof(QNode));

	newNode->data=item;
	newNode->link=NULL;

	if(LQ->front==NULL){ //큐에 아무것도 없을때.
		LQ->front=newNode; //newnode를 front와 rear로 설정한다.
		LQ->rear=newNode;
	}
	else{
		LQ->rear->link=newNode; //rear의 다음값을
		LQ->rear=newNode;
	}
}
int deQueue(LQueueType *LQ){ //큐의 입력을 위한 함수.
	QNode* old= LQ->front;
	int item;

	if(isEmpty(LQ))
		return 0;
	else{
		item=old->data;
		LQ->front=LQ->front->link;

		if(LQ->front==NULL)
			LQ->rear=NULL;

		free(old);
		return item;
	}
}
void BFS(Graphlist *g,int v){ //그래프 g에서 정점 v에 대한 너비우선 탐색 연산.
	node *w;
	LQueueType* Q; //큐 생성
	Q=createLinkedQueue();
	g->visted[v]=TRUE;
	printf("%c",v+65);
	enQueue(Q,v);

	while(!isEmpty(Q)){ //큐의 끝까지 반복
		v=deQueue(Q);

		for(w=g->graph[v];w;w=w->link){ //인접 정점이 있는 동안 수행
			if(!g->visted[w->vertex]){ // 정점 W가 방문하지 않은 정점인 경우.
				g->visted[w->vertex]=TRUE;
				printf("%c",w->vertex+65);//출력
				enQueue(Q,w->vertex);
			}
		}
	}
	for(v=0;v<MAX_VERTEX;v++)
			g->visted[v]=FALSE;
}
