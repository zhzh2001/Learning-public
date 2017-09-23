/*
ID: dd.ener1
PROG: ditch
LANG: C++
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=20010,OO=1000000000;
struct edge{
	int x,y;//�������� 
	int w;//���� 
	int f;
	edge *next,*back;
	edge(){}
	edge(int x,int y,int w,edge* next):x(x),y(y),w(w),f(0),next(next),back(0){}
	void* operator new(size_t, void *p){
		return p;
	}
}*E[maxn];
int D[maxn];//�����ţ����㵽�������ٵĻ���
int N,S,T;

void init_distance_label(){//���Ǵӻ�㿪ʼ��ֻ������Ϊ0�ıߵ�һ�ι��� 
	int queue[maxn],head=0,tail=0;
	queue[tail++]=S;
	memset(D,-1,sizeof(D));
	D[T]=0;
	for(;;){
		int v=queue[head++];
		for(edge* e=E[v];e;e=e->next){
			if(e->w!=0)continue;
			int y=e->y;
			if(D[y]==-1){
				D[y]=D[v]+1;
				queue[tail++]=y;
			}
		}
		if(head==tail)
			break;
	}
}
int maxflow(){
	int res=0;
	init_distance_label();
	edge* path[maxn];
	edge* current[maxn];
	memcpy(current,E,sizeof(E));
	int path_n=0;
	int i=S;
	for(;;){
		if(i==T){
			int min=OO,mink;
			for(int k=0;k<path_n;++k){
				if(path[k]->w < min){
					min=path[k]->w;
					mink=k;
				}
			}
			res+=min;
			for(int k=0;k<path_n;++k){
				path[k]->w -= min;
				path[k]->back->w += min;
				path[k]->f += min;
				path[k]->back->f = -(path[k]->f);
			}
			path_n=mink;
			i=path[path_n]->x;
		}
		edge* e;
		for(e=current[i];e;e=e->next){
			if(e->w==0)continue;
			int j=e->y;
			if(D[i]==D[j]+1)
				break;
		}
		if(e){//e���Ǵ�i����������
			current[i]=e;//ǰ��Ķ����������������´δ����￪ʼ�ҾͿ��� 
			path[path_n++]=e;
			i=e->y;
		}
		else{//��i����û����������Ҫ�޸ı�� 
			int minlabel=N;
			for(edge* e=E[i];e;e=e->next){
				if(e->w==0)continue;
				int j=e->y;
				if(D[j]<minlabel){
					minlabel=D[j];
					current[i]=e;//��С��ŵı߾����µ����� 
				}
			}
			D[i]=minlabel+1;
			if(i!=S){//����i�ı�ű��ı䣬·���е�i���������϶��Ѿ���������������Ҫ����һ��
				--path_n;
				i=path[path_n]->x;
			}
			else if(D[i]>N)//��ʱ�Ѿ�û�д�Դ�㵽����·�� 
				break;
		}
	}
	return res;
}
void input(){
	int m;
	scanf("%d%d",&m,&N);
	memset(E,0,sizeof(E));
	edge* data=new edge[2*m];
	while(m--){
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		E[x]=new((void*)data++) edge(x,y,w,E[x]);
		E[y]=new((void*)data++) edge(y,x,0,E[y]);
		E[x]->back = E[y];
		E[y]->back = E[x];
	}
	S=1;
	T=N;
}
int main(){
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	input();
	int res=maxflow();
	printf("%d\n",res);
}
