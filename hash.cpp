#include <iostream>
#include <stdio.h>
#include <math.h>
#define N 10000

unsigned long long int tablehash[4096];
int counter;//探查次数 全局变量
void inithash(void)//hash函数初始化
{
             int i;
             for(i=0;i<4096;i++)
                          tablehash[i]=0;
}
long long int inserthash(unsigned long long int a)//插入a的值
{
             unsigned long long int b;
             unsigned long long int c;
             counter=1;
             b=a*a;
             c = (b >> 26) % 4096;
             //c=(b>>38-b>>26)/67108864;
             //if(c<0)
               //           c=(c+4096)%4096-1;
             while(tablehash[c]!=0&&tablehash[c]!=-1)
             {
                          if(a%2==0)
                                       c=((c+(a+1)%4096) % 4096);
                          if(a%2!=0)
                                       c=((c+(a%4096)) % 4096);
                          counter++;
             }
             tablehash[c]=a;
             return c;//返回插入位置
}
long long int searchhash(unsigned long long int a)//查询hash表中是否存在a
{
             unsigned long long int b;
             unsigned long long int c;
             b=a*a;
             //c=b/67108864-((b/274877906944)*67108864);
             //c=(b%274877906944-b%67108864)/67108864;//取中间12位
             c = (b >> 26) % 4096;
             //if(c<0)
                          //c=(c+4096)%4096-1;
             counter=1;
             while(tablehash[c]!=0&&tablehash[c]!=a)
             {
                          if(a%2==0)
                                       c=((c+((a+1)%4096)) % 4096);
                          if(a%2!=0)
                                       c=((c+(a%4096)) % 4096);
                          counter++;
             }
             if(tablehash[c]==0)
                           return -1;
             if(tablehash[c]==a)
             {
                          tablehash[c]=-1;
                          return c;//返回查找到的地址
             }
}
int main()
{
             int i;
             int b;//存储0 1 值
             int flag1,flag2;//flag1表示插入元素的个数,flag2表示查询元素的个数
             unsigned long long int a;//存储a
             long long int asl1=0;
             long long int asl2=0;
             long long int m,n;//m表示插入位置,n表示元素所在的槽
             inithash();//初始化hash表
             flag1=0;
             flag2=0;
             for(i=0;i<N;i++)
             {
                          scanf("%llu%d",&a,&b);
                          //printf("3");
                          if(b==1)
                          {
                                       m=inserthash(a);
                                       printf("%d %lld\n",counter,m);
                          }
                          if(b==0)
                          {
                                       n=searchhash(a);
                                       printf("%d %lld\n",counter,n);
                                       if(n==-1)
                                       {
                                                    flag2++;
                                                    asl2+=counter;
                                       }
                                       else
                                       {
                                                    flag1++;
                                                    asl1+=counter;
                                       }

                          }
             }
             printf("%lld",asl1);
             printf("/");
             printf("%d\n",flag1);
             printf("%lld",asl2);
             printf("/");
             printf("%d",flag2);
             return 0;
}
