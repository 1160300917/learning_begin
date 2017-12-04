#include <iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<string.h>
#include<vector>


using namespace std;

#define namesize 50
#define maxsize 100
#define maxsize1 20
#define inf 1000000

char filename[namesize];
//�ڽӾ���
typedef struct
{
    int n,e; //������������
    char vertex[maxsize];//�����
    int edge[maxsize][maxsize];//�߱�
}mtgraph;
//����ͼ���ڽӾ���
void createmt(mtgraph &G)
{
        int a,b;
        int i=0;
        int weight;//Ȩֵ
        char str[maxsize];
        char*p;
        FILE* file;
        cout<<"�������ļ�����"<<endl;
        cin>>filename;
        file=fopen(filename,"r");

        if(file==NULL)
        {
            cout<<"�ļ���ʧ�ܣ�"<<endl;
            exit(0);
        }
        fscanf(file,"%d,%d",&G.n,&G.e);
        fscanf(file,"%s",&str);
        p=strtok(str,",");
        while(p)
        {
            G.vertex[i]=*p;
            char t=G.vertex[i];
            p=strtok(NULL,",");
            i++;
        }

        for(int j=0;j<G.n;j++)  //�߱��ʼ��
            for(int k=0;k<G.n;k++)
        {
            G.edge[j][k]=inf;
        }

        for(int i=0;i<G.e;i++)
        {
            fscanf(file,"%d,%d,%d",&a,&b,&weight);
            if(weight<G.edge[a][b])
            {
                G.edge[a][b]=weight;
            }
        }
        fclose(file);
}
//dijkstra�㷨--��Դ���·��
int mincost(int dis[],bool mark[],int n)
{
    int temp=inf;
    int w=1;
    for(int i=1;i<n;i++)
    {
        if(!mark[i]&&dis[i]<temp)
        {
            temp=dis[i];
            w=i;
        }
    }
    return w;
}

void dijkstra_ss(mtgraph &G,int dis[],int path[],bool mark[])
{
    for(int i=0;i<G.n;i++) //dis path �� mark��ʼ��
    {
        dis[i]=G.edge[0][i];
        mark[i]=false;
        path[i]=0;  //��0ΪԴ��
    }
    mark[0]=true;
    for(int i=0;i<G.n-1;i++)
    {
        int w;
        w=mincost(dis,mark,G.n);
        mark[w]=true;
        for(int j=1;j<G.n;j++)
        {
            if(!mark[j])
            {
                int sum=dis[w]+G.edge[w][j];
                if(sum<dis[j])
                {
                    dis[j]=sum;
                    path[j]=w;
                }
            }
        }
    }
}
//floyd-warshall�㷨--�����������������·��
void floyd_warshall(mtgraph &G,int dis1[][maxsize1],int path1[][maxsize1])
{
    for(int i=0;i<G.n;i++)
        for(int j=0;j<G.n;j++)
    {
        dis1[i][j]=G.edge[i][j];
        path1[i][j]=-1;
    }
    for(int k=0;k<G.n;k++)
        for(int i=0;i<G.n;i++)
            if(i!=k)
            for(int j=0;j<G.n;j++)
            if(j!=k)
            {
                if(i!=j)
                {
                    if(dis1[i][j]>dis1[i][k]+dis1[k][j])
                        {
                            dis1[i][j]=dis1[i][k]+dis1[k][j];
                            path1[i][j]=k;
                        }
                }
            }
        for(int i=0;i<G.n;i++)
    {
        for(int j=0;j<G.n;j++)
        {
            if(dis1[i][j]==inf)
                cout<<"�Ӷ���"<<i<<"������"<<j<<"������·��"<<endl;
            else
            {
                cout<<"�Ӷ���"<<i<<"������"<<j<<"��̾���Ϊ: "<<dis1[i][j]<<"  ��·��Ϊ��";
                vector<int>temp;
                temp.insert(temp.begin(),j);//���յ����
                int ok1=i,ok2=j;
                while(true)
                {
                   ok1=path1[ok1][ok2];
                   if(ok1==-1)
                       break;
                   temp.insert(temp.begin(),ok1);

                }

                temp.insert(temp.begin(),i);//��������

                for(int z=0;z<temp.size();z++)
                    cout<<temp[z]<<" ";
                cout<<endl;
            }
        }
    }
    cout<<"----------------------------------------------"<<endl;
}
//dijkstra�㷨--��Ŀ�����·��
int mincost_sdsp(int dis[],bool mark[],int n,int v)
{
    int temp=inf;
    int w=v;
    for(int i=0;i<n;i++)
    {
        if(!mark[i]&&dis[i]<temp)
        {
            temp=dis[i];
            w=i;
        }
    }
    return w;
}
void dijkstra_sd(mtgraph &G,int dis[],int path[],bool mark[],int v)
{
    for(int i=0;i<G.n;i++) //dis path �� mark��ʼ��
    {
        dis[i]=G.edge[i][v];
        mark[i]=false;
        if(i!=v&&dis[i]<inf)
            path[i]=v;  //��vΪԴ��
        else
            path[i]=-1;
    }
    mark[v]=true;
    for(int i=0;i<G.n-1;i++)
    {
        int w;
        w=mincost_sdsp(dis,mark,G.n,v);
        mark[w]=true;
        for(int j=0;j<G.n;j++)
        {
            if(!mark[j])
            {
                int sum=dis[w]+G.edge[j][w];
                if(sum<dis[j])
                {
                    dis[j]=sum;
                    path[j]=w;
                }
            }
        }
    }
}
//dijkstra�㷨--����������·��
int mincost_sp(int dis[],bool mark[],int n,int v)
{
    int temp=inf;
    int w=v;
    for(int i=0;i<n;i++)
    {
        if(!mark[i]&&dis[i]<temp)
        {
            temp=dis[i];
            w=i;
        }
    }
    return w;
}

void dijkstra_sp(mtgraph &G,int dis[],int path[],bool mark[],int v)
{
    for(int i=0;i<G.n;i++) //dis path �� mark��ʼ��
    {
        dis[i]=G.edge[v][i];
        mark[i]=false;
        if(i!=v&&dis[i]<inf)
            path[i]=v;
        else
            path[i]=-1;
    }
    mark[v]=true;
    for(int i=0;i<G.n;i++)
    {
        int w;
        w=mincost_sp(dis,mark,G.n,v);
        mark[w]=true;
        for(int j=0;j<G.n;j++)
        {
            if(!mark[j])
            {
                int sum=dis[w]+G.edge[w][j];
                if(sum<dis[j])
                {
                    dis[j]=sum;
                    path[j]=w;
                }
            }
        }
    }

}
//floyd-warshall�㷨--����ɴ����
void floyd_rm(mtgraph &G,int rm[][maxsize1])
{
    for(int i=0;i<G.n;i++)
        for(int j=0;j<G.n;j++)
    {
        if(i==j||G.edge[i][j]<inf)
            rm[i][j]=1;
        else
            rm[i][j]=0;
    }
    for(int k=0;k<G.n;k++)
        for(int i=0;i<G.n;i++)
            for(int j=0;j<G.n;j++)
            {
                rm[i][j]=rm[i][j]||(rm[i][k]&&rm[k][j]);
            }
}

int menu()
{
    int ch;
    cout<<"1.��Դ���·������."<<endl;
    cout<<"2.�����������������·������."<<endl;
    cout<<"3.��Ŀ�����·������."<<endl;
    cout<<"4.����������·������."<<endl;
    cout<<"5.����ɴ��������."<<endl;
    cout<<"0.�˳�����."<<endl;

    cout<<"���������ѡ��"<<endl;
    cin>>ch;
    return ch;
}

int main()
{
    int ch;
    mtgraph G;
    createmt(G);

    int dis[G.n];
    int path[G.n];
    bool mark[G.n];


    while(1)
{
    ch=menu();
         switch(ch)
    {
    case 1:
        dijkstra_ss(G,dis,path,mark);
        cout<<"Դ��0���䵽������������·������Ϊ��"<<endl;
        for(int i=1;i<G.n;i++)
        {
            cout<<dis[i]<<"\t";
        }
        cout<<endl;
        cout<<"Դ��0���䵽������������·��Ϊ��"<<endl;
        for(int i=1;i<G.n;i++)
        {
            cout<<path[i]<<"\t";
        }
        cout<<endl;
        break;
    case 2:
        int dis1[maxsize1][maxsize1];
        int path1[maxsize1][maxsize1];
        floyd_warshall(G,dis1,path1);
        cout<<" ����������������̾������Ϊ��"<<endl;
        for(int i=0;i<G.n;i++)
        {
            for(int j=0;j<G.n;j++)
            {
                cout<<dis1[i][j]<<"\t";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<" �����������������·������Ϊ��"<<endl;
        for(int i=0;i<G.n;i++)
        {
            for(int j=0;j<G.n;j++)
            {
                cout<<path1[i][j]<<"\t";
            }
            cout<<endl;
        }
        cout<<endl;
        break;
    case 3:
        int m;
        cout<<"������Ŀ��㣺"<<endl;
        cin>>m;
        dijkstra_sd(G,dis,path,mark,m);
        cout<<"�������㵽Ŀ�������·������Ϊ��"<<endl;
        for(int i=0;i<G.n;i++)
        {
            if(i!=m)
            cout<<i<<"��:"<<dis[i]<<"\t";
        }
        cout<<endl;
        cout<<"�������㵽Ŀ�������·�����ϸö���ĺ�̶���Ϊ����-1��ʾû������·��"<<endl;
        for(int i=0;i<G.n;i++)
        {
            if(i!=m)
            cout<<i<<"��:"<<path[i]<<"\t";
        }
        cout<<endl;
        break;
    case 4:
        int v,u;
        cout<<"������һ�Զ���v��u��"<<endl;
        cin>>v>>u;
        dijkstra_sp(G,dis,path,mark,v);
        for(int i=0;i<G.n;i++)
        {
            if(i==u)
            if(dis[i]<inf)
            {
               cout<<"��vΪԴ���䵽����u�����·������Ϊ��"<<endl;
               cout<<dis[i]<<"\t";
            }
            else
                cout<<"��vΪԴ���䵽����u������·��"<<endl;
        }
        cout<<endl;
        for(int i=0;i<G.n;i++)
        {
            if(i==u&&dis[i]<inf)
            {
                cout<<"��vΪԴ���䵽����u�����·��Ϊ��"<<endl;
                cout<<path[i]<<"\t";
            }
        }
        printf("\n----------------------------------------------\n");
        dijkstra_sp(G,dis,path,mark,u);
        for(int i=0;i<G.n;i++)
        {
            if(i==v)
            if(dis[i]<inf)
           {
               cout<<"��uΪԴ���䵽����v�����·������Ϊ��"<<endl;
               cout<<dis[i]<<"\t";
           }
            else
                cout<<"��uΪԴ���䵽����v������·"<<endl;
        }
        cout<<endl;
        for(int i=0;i<G.n;i++)
        {
            if(i==v&&dis[i]<inf)
            {
                cout<<"��uΪԴ���䵽����v�����·��Ϊ��"<<endl;
                cout<<path[i]<<"\t";
            }
        }
        cout<<endl;
        break;
    case 5:
        int rm[maxsize1][maxsize1];
        floyd_rm(G,rm);
        for(int i=0;i<G.n;i++)
        {
            for(int j=0;j<G.n;j++)
            cout<<rm[i][j]<<"\t";
            cout<<endl;
        }
        cout<<endl;
        break;
    case 0:
        cout<<"�������."<<endl;
        exit(0);
    }
}
    return 0;
}
