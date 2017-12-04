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
//邻接矩阵
typedef struct
{
    int n,e; //顶点数，边数
    char vertex[maxsize];//顶点表
    int edge[maxsize][maxsize];//边表
}mtgraph;
//创建图的邻接矩阵
void createmt(mtgraph &G)
{
        int a,b;
        int i=0;
        int weight;//权值
        char str[maxsize];
        char*p;
        FILE* file;
        cout<<"请输入文件名："<<endl;
        cin>>filename;
        file=fopen(filename,"r");

        if(file==NULL)
        {
            cout<<"文件打开失败！"<<endl;
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

        for(int j=0;j<G.n;j++)  //边表初始化
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
//dijkstra算法--单源最短路径
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
    for(int i=0;i<G.n;i++) //dis path 和 mark初始化
    {
        dis[i]=G.edge[0][i];
        mark[i]=false;
        path[i]=0;  //以0为源点
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
//floyd-warshall算法--任意两个顶点间的最短路径
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
                cout<<"从顶点"<<i<<"到顶点"<<j<<"不存在路径"<<endl;
            else
            {
                cout<<"从顶点"<<i<<"到顶点"<<j<<"最短距离为: "<<dis1[i][j]<<"  其路径为：";
                vector<int>temp;
                temp.insert(temp.begin(),j);//把终点插入
                int ok1=i,ok2=j;
                while(true)
                {
                   ok1=path1[ok1][ok2];
                   if(ok1==-1)
                       break;
                   temp.insert(temp.begin(),ok1);

                }

                temp.insert(temp.begin(),i);//把起点插入

                for(int z=0;z<temp.size();z++)
                    cout<<temp[z]<<" ";
                cout<<endl;
            }
        }
    }
    cout<<"----------------------------------------------"<<endl;
}
//dijkstra算法--单目标最短路径
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
    for(int i=0;i<G.n;i++) //dis path 和 mark初始化
    {
        dis[i]=G.edge[i][v];
        mark[i]=false;
        if(i!=v&&dis[i]<inf)
            path[i]=v;  //以v为源点
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
//dijkstra算法--单顶点对最短路径
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
    for(int i=0;i<G.n;i++) //dis path 和 mark初始化
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
//floyd-warshall算法--计算可达矩阵
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
    cout<<"1.单源最短路径问题."<<endl;
    cout<<"2.任意两个顶点间的最短路径问题."<<endl;
    cout<<"3.单目标最短路径问题."<<endl;
    cout<<"4.单顶点对最短路径问题."<<endl;
    cout<<"5.计算可达矩阵问题."<<endl;
    cout<<"0.退出程序."<<endl;

    cout<<"请输入你的选择："<<endl;
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
        cout<<"源点0及其到其他顶点的最短路径长度为："<<endl;
        for(int i=1;i<G.n;i++)
        {
            cout<<dis[i]<<"\t";
        }
        cout<<endl;
        cout<<"源点0及其到其他顶点的最短路径为："<<endl;
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
        cout<<" 任意两个顶点间的最短距离矩阵为："<<endl;
        for(int i=0;i<G.n;i++)
        {
            for(int j=0;j<G.n;j++)
            {
                cout<<dis1[i][j]<<"\t";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<" 任意两个顶点间的最短路径矩阵为："<<endl;
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
        cout<<"请输入目标点："<<endl;
        cin>>m;
        dijkstra_sd(G,dis,path,mark,m);
        cout<<"其他顶点到目标点的最短路径长度为："<<endl;
        for(int i=0;i<G.n;i++)
        {
            if(i!=m)
            cout<<i<<"号:"<<dis[i]<<"\t";
        }
        cout<<endl;
        cout<<"其他顶点到目标点的最短路径的上该顶点的后继顶点为：（-1表示没有有向路）"<<endl;
        for(int i=0;i<G.n;i++)
        {
            if(i!=m)
            cout<<i<<"号:"<<path[i]<<"\t";
        }
        cout<<endl;
        break;
    case 4:
        int v,u;
        cout<<"请输入一对顶点v和u："<<endl;
        cin>>v>>u;
        dijkstra_sp(G,dis,path,mark,v);
        for(int i=0;i<G.n;i++)
        {
            if(i==u)
            if(dis[i]<inf)
            {
               cout<<"以v为源点其到顶点u的最短路径长度为："<<endl;
               cout<<dis[i]<<"\t";
            }
            else
                cout<<"以v为源点其到顶点u不存在路："<<endl;
        }
        cout<<endl;
        for(int i=0;i<G.n;i++)
        {
            if(i==u&&dis[i]<inf)
            {
                cout<<"以v为源点其到顶点u的最短路径为："<<endl;
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
               cout<<"以u为源点其到顶点v的最短路径长度为："<<endl;
               cout<<dis[i]<<"\t";
           }
            else
                cout<<"以u为源点其到顶点v不存在路"<<endl;
        }
        cout<<endl;
        for(int i=0;i<G.n;i++)
        {
            if(i==v&&dis[i]<inf)
            {
                cout<<"以u为源点其到顶点v的最短路径为："<<endl;
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
        cout<<"程序结束."<<endl;
        exit(0);
    }
}
    return 0;
}
