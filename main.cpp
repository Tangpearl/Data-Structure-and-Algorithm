#include<stdio.h>
#include<malloc.h>
#define N 1000
typedef struct biscuit
{
             int vi;
             int vj;
             int weight;
}biscuit;
typedef struct gralph
{
             biscuit bis[N];
             int vexnum;
             int arcnum;
}graplgh;
void build(graplgh &B)
{
             int a,b,c;
             scanf("%d%d",&B.vexnum,&B.arcnum);
             scanf("%d%d%d",&a,&b,&c);

}
int main()
{
             graplgh B;
             build(B);
             return 0;
}
