#include<stdio.h>
#include<iostream>
#include"malloc.h"

#define N 10000
#define MAX 2100000000

typedef struct arcnode
{
	int adjvex;
	int weight;
	struct arcnode *nextarc;
}arcnode;
typedef struct vertexnode
{
	int data;
	int flag;//判断是否是陷阱节点,1表示不是,0表示是
	arcnode *firstarc;
}vextexnode,adjust[N];
typedef struct
{
	adjust vertices;
	int vexnum, arcnum;//顶点数 边数
}algraph;

void creatalgraph(algraph &G)//建图
{
	int i,vi,vj,wey;

	scanf("%d%d", &G.vexnum, &G.arcnum);//输入顶点数及边数

	for (i = 0; i < G.vexnum; i++)//建立顶点数组
	{
		G.vertices[i].data = i + 1;//顶点数组下标与数组值有天然对应关系
		G.vertices[i].firstarc = NULL;
		G.vertices[i].flag=0;

	}
	for (i = 0; i < G.arcnum; i++)//建图
	{
		scanf("%d%d%d", &vi, &vj, &wey);//输入两个顶点值及权值
		arcnode *q;

		q = (arcnode *)malloc(sizeof(arcnode));
		q->adjvex = vj - 1;
		q->weight = wey;

		q->nextarc = G.vertices[vi - 1].firstarc;
		G.vertices[vi - 1].firstarc = q;
		G.vertices[vi - 1].flag = 1;

	}
}

void foundtrap(algraph &G,int b)
{
             arcnode *q;
             int i;
             for(i=0;i<G.vexnum;i++)
             {
                          for(q=G.vertices[i].firstarc;q!=NULL;q=q->nextarc)
                          {
                                       if(G.vertices[q->adjvex].flag==0&&q->adjvex!=b-1)
                                                    {
                                                                 G.vertices[i].firstarc=NULL;
                                                                 break;
                                                    }
                          }
             }
}
int dijway(algraph G, int a, int b)//dij算法实现最小路径
{
	int S[N] = { 0 };//初始化S数组
	int D[N];
	int i, j, k,mina;
	arcnode *q;
	for (i = 0; i < G.vexnum; i++)//初始化D数组
		D[i] = MAX;
	for (q = G.vertices[a - 1].firstarc; q != NULL; q = q->nextarc)//起点初始化
		{
                                       if(D[q->adjvex]>q->weight)
                                                    D[q->adjvex]=q->weight;
		}
	S[a - 1] = 1;
	D[a - 1] = 0;
	for (i = 1; i < G.vexnum; i++)
	{
		mina = MAX;
		for(j=0;j<G.vexnum;j++)
			if (!S[j] && D[j] < mina)
			{
				mina = D[j];
				k = j;
			}
		S[k] = 1;
		for(q=G.vertices[k].firstarc;q!=NULL;q=q->nextarc)
		{
		             j=q->adjvex;
		             if(S[j]==1)
                                                    continue;
                                       if(D[j]>D[k]+q->weight)
                                                    D[j]=D[k]+q->weight;
		}
	}
	if (D[b - 1] == MAX)
		return -1;
	else
		return D[b - 1];
}

int main()
{
	int a, b,c;
	algraph G;
	creatalgraph(G);
	scanf("%d%d", &a, &b);
	foundtrap(G,b);
	c = dijway(G, a, b);
	printf("%d", c);
}
