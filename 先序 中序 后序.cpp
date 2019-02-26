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
	int flag;//�ж��Ƿ�������ڵ�,1��ʾ����,0��ʾ��
	arcnode *firstarc;
}vextexnode,adjust[N];
typedef struct
{
	adjust vertices;
	int vexnum, arcnum;//������ ����
}algraph;

void creatalgraph(algraph &G)//��ͼ
{
	int i,vi,vj,wey;

	scanf("%d%d", &G.vexnum, &G.arcnum);//���붥����������

	for (i = 0; i < G.vexnum; i++)//������������
	{
		G.vertices[i].data = i + 1;//���������±�������ֵ����Ȼ��Ӧ��ϵ
		G.vertices[i].firstarc = NULL;
		G.vertices[i].flag=0;

	}
	for (i = 0; i < G.arcnum; i++)//��ͼ
	{
		scanf("%d%d%d", &vi, &vj, &wey);//������������ֵ��Ȩֵ
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
int dijway(algraph G, int a, int b)//dij�㷨ʵ����С·��
{
	int S[N] = { 0 };//��ʼ��S����
	int D[N];
	int i, j, k,mina;
	arcnode *q;
	for (i = 0; i < G.vexnum; i++)//��ʼ��D����
		D[i] = MAX;
	for (q = G.vertices[a - 1].firstarc; q != NULL; q = q->nextarc)//����ʼ��
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
