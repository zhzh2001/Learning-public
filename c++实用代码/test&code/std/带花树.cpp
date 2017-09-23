#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=250;
int n;
int head;
int tail;
int Start;
int Finish;
int link[N];     //��ʾ�ĸ���ƥ�����ĸ���
int Father[N];   //�����������·��Father��������������̫������
int Base[N];     //�õ������Ķ仨
int Q[N];
bool mark[N];
bool map[N][N];
bool InBlossom[N];
bool in_Queue[N];

void CreateGraph(){
    int x,y;
    scanf("%d",&n);
    while (scanf("%d%d",&x,&y)!=EOF)
      map[x][y]=map[y][x]=1;
}

void BlossomContract(int x,int y){
    fill(mark,mark+n+1,false);
    fill(InBlossom,InBlossom+n+1,false);
    #define pre Father[link[i]]
    int lca,i;
    for (i=x;i;i=pre) {i=Base[i]; mark[i]=true; }
    for (i=y;i;i=pre) {i=Base[i]; if (mark[i]) {lca=i; break;} }  //Ѱ��lca֮�á���һ��Ҫע��i=Base[i]
    for (i=x;Base[i]!=lca;i=pre){
        if (Base[pre]!=lca) Father[pre]=link[i]; //����BFS���еĸ�����ƥ��ߵĵ㣬Father�����
        InBlossom[Base[i]]=true;
        InBlossom[Base[link[i]]]=true;
    }
    for (i=y;Base[i]!=lca;i=pre){
        if (Base[pre]!=lca) Father[pre]=link[i]; //ͬ��
        InBlossom[Base[i]]=true;
        InBlossom[Base[link[i]]]=true;
    }
    #undef pre
    if (Base[x]!=lca) Father[x]=y;     //ע�ⲻ�ܴ�lca����滷�Ĺؼ���������
    if (Base[y]!=lca) Father[y]=x;
    for (i=1;i<=n;i++)
      if (InBlossom[Base[i]]){
          Base[i]=lca;
          if (!in_Queue[i]){
              Q[++tail]=i;
              in_Queue[i]=true;     //Ҫע�������������BFS���и����ı��Ƿ�ƥ��ߵĵ㣬������û����ӵ�
          }
      }
}

void Change(){
    int x,y,z;
    z=Finish;
    while (z){
        y=Father[z];
        x=link[y];
        link[y]=z;
        link[z]=y;
        z=x;
    }
}

void FindAugmentPath(){
    fill(Father,Father+n+1,0);
    fill(in_Queue,in_Queue+n+1,false);
    for (int i=1;i<=n;i++) Base[i]=i;
    head=0; tail=1;
    Q[1]=Start;
    in_Queue[Start]=1;
    while (head!=tail){
        int x=Q[++head];
        for (int y=1;y<=n;y++)
          if (map[x][y] && Base[x]!=Base[y] && link[x]!=y)   //������ı�
            if ( Start==y || link[y] && Father[link[y]] )    //�������Father��ʾ�õ��Ƿ�
                BlossomContract(x,y);
            else if (!Father[y]){
                Father[y]=x;
                if (link[y]){
                    Q[++tail]=link[y];
                    in_Queue[link[y]]=true;
                }
                else{
                    Finish=y;
                    Change();
                    return;
                }
            }
    }
}

void Edmonds(){
    memset(link,0,sizeof(link));
    for (Start=1;Start<=n;Start++)
      if (link[Start]==0)
        FindAugmentPath();
}

void output(){
    fill(mark,mark+n+1,false);
    int cnt=0;
    for (int i=1;i<=n;i++)
      if (link[i]) cnt++;
    printf("%d\n",cnt);
    for (int i=1;i<=n;i++)
      if (!mark[i] && link[i]){
          mark[i]=true;
          mark[link[i]]=true;
          printf("%d %d\n",i,link[i]);
      }
}

int main(){
//  freopen("input.txt","r",stdin);
    CreateGraph();
    Edmonds();
    output();
    return 0;
}


