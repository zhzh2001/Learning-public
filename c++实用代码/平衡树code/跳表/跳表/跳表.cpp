#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include<ctime>
using namespace std;
#define DefaultSize 12

//SkipNode�ṹ  ����Ľ�������Ͷ���,EΪ�������������,KΪ�ؼ��������
template<class T>
struct SkipNode
{
	T data;						   //������
	SkipNode<T>** link;			   //ָ��������
	SkipNode(T x,int size=DefaultSize)//���캯��
	{
		data=x;
		link=new SkipNode<T>*[size];
		//����ڴ����ʧ��
		if(link==NULL)
		{
			cout<<"�ڴ����ʧ��!"<<endl;
			exit(1);
		};
		//��ָ�������ʼ��ΪNULL
		for(int i=0;i<size;i++)
			link[i]=NULL;
	};
	~SkipNode()					  //��������
	{delete [] link;};
};
//SkipList��ģ��  �������ģ�弴ͨ���༶�������֯��ʽ���������Ч��,0�����������˳���Ǵ���������
template<class T>
class SkipList
{
private:
	int maxLevel;		//�����������߼���
	int level;		   //��ǰ�ǿ�������߼���
	T TailKey;		   //���һ�������ŵ�������
	SkipNode<T>* head;   //����ͷ���ָ��
	SkipNode<T>* tail;   //����β���ָ��
	SkipNode<T>** last;  //ÿ�����ϵ����һ��Ԫ�ص�ָ��
	//Ϊ��L��H֮���Ԫ�ط���lev����
	void setGrade(int* grade,int L,int H,int lev);
	//��[0,level]֮���������һ������
   int randLevel();
public:
	//���캯��
	SkipList(T large,int maxLev);
	//ͨ����������������һ������
	void CreateSkipList(T* A,int n);
	//��������
	~SkipList();
	//��ʾ�������������
	void Display();
	//����ָ������x�Ľ��
	SkipNode<T>* Search(T x);
	//�ж�Ԫ�����������Ƿ����
	bool Exist(T x);
	//��ָ����Ԫ��x���뵽��ǰ��������ȥ
	bool Insert(T x);
	//ɾ��������ָ��ֵ�Ľ��
	bool Remove(T x);
};
//���캯��  ����һ��������
template<class T>
SkipList<T>::SkipList(T large,int maxLev)
{
	maxLevel=maxLev;	 //��ʼ����߼���
	level=0;			 //��ǰ��ʼ����Ϊ0��
	TailKey=large;	   //Ϊ����е����ؼ���

	//��������ͷ���
	head=new SkipNode<T>(-1000,maxLevel+1);
	//����һ������β���
	tail=new SkipNode<T>(TailKey,maxLevel+1);
	//Ϊlast���鿪���ڴ�,�����г�ʼ��
	last=new SkipNode<T>*[maxLevel];
	for(int i=0;i<=maxLevel;i++)
		last[i]=head;
	//��head����ͷ������ָ��ȫ��ָ��tail,��ʾ�����
	for(int i=0;i<=maxLevel;i++)
		head->link[i]=tail;
};
//��������,�ͷ�������ڴ�ռ�
template<class T>
SkipList<T>::~SkipList()
{
	//�α�ָ��
	SkipNode<T>* ptr=head;
	SkipNode<T>* pre=head;
	//����ɾ��ÿ�����
	while(pre!=NULL)
	{
		//��ptr���Ƶ����������ͷ
		ptr=ptr->link[0];
		//�ͷ�pre���Ŀռ�
		delete pre;
		pre=ptr;
	};
};
//Display()���г�Ա����,��ʾ�������������
template<class T>
void SkipList<T>::Display()
{
	//�α�ָ��
	SkipNode<T>* ptr=head;
	//������������
	for(int i=0;i<=level;i++)
	{
		cout<<i<<"����:";
		ptr=head->link[i];
		while(ptr!=tail)
		{
			cout<<ptr->data<<" ";
			ptr=ptr->link[i];
		}
		cout<<endl;
	};
};
//CreateSkipList()���г�Ա����,ͨ���������鴮��������
template<class T>
void SkipList<T>::CreateSkipList(T* A,int n)
{
	int* grade=new int[n];   //��ż���������
	for(int i=0;i<n;i++)	 //�Ѽ��������ʼ��Ϊ0
		grade[i]=0;
	level=int(log(n)/log(2));//����n����󼶱�

	//Ϊÿ�������伶�𣬲��Ѽ������grade����
	setGrade(grade,0,n-1,level);

	//�Ȱ�A�е�ȡ����������������
	for(int i=0;i<n;i++)
	{
		//�½�һ�����
		SkipNode<T>* newNode=new SkipNode<T>(A[i]);
		//������i�����ĸ�������
		for(int j=0;j<=grade[i];j++)
		{
			//�����j������
			last[j]->link[j]=newNode;
			//��j���α�ָ������ƽ�
			last[j]=newNode;
		};
	};
	//���ϸ���β���
	for(int i=0;i<=level;i++)
		last[i]->link[i]=tail;

	//�ͷ�grade����Ŀռ�
	delete [] grade;
};
//Search()���г�Ա����,������������ָ��ֵx��Ԫ�صĽ��ָ��
template<class T>
SkipNode<T>* SkipList<T>::Search(T x)
{
	//�α�ָ�����߼����ĵ�һ��Ԫ�ؿ�ʼ
	SkipNode<T>* ptr=head->link[level];
	//��ǰ��������Ļ���ָ��
	SkipNode<T>* base=head;
	int grade=level;
	//����߼�����ʼ������������
	//�ڵ�grade�����н�������
	while(base!=tail && grade!=-1)
	{
		//����ҵ��ͷ��ص�ǰ���ָ��
		if(x==ptr->data)
			return ptr;
		//���x�ȵ�ǰ����,�ͼ������
		else if(x>ptr->data)
		{
			base=ptr;
			ptr=ptr->link[grade];
		}
		//���x�ȵ�ǰ���С,�ͽ���
		else if(x<ptr->data)
		{
			//�Ӵμ���base���¿�ʼ����
			grade--;
			ptr=base->link[grade];
		};
	};
	//���û���ҵ��ͷ���βָ���ֵ
	return tail;
};
//Exist()���г�Ա����,�ж�Ԫ��x�ڵ�ǰ�������Ƿ����
template<class T>
bool SkipList<T>::Exist(T x)
{
	//�α�ָ�����߼����ĵ�һ��Ԫ�ؿ�ʼ
	SkipNode<T>* ptr=head->link[level];
	//��ǰ��������Ļ���ָ��
	SkipNode<T>* base=head;
	int grade=level;
	//����߼�����ʼ������������
	//�ڵ�grade�����н�������
	while(base!=tail && grade!=-1)
	{
		//����ҵ��ͷ�����
		if(x==ptr->data)
			return true;
		//���x�ȵ�ǰ����,�ͼ������
		else if(x>ptr->data)
		{
			base=ptr;
			ptr=ptr->link[grade];
		}
		//���x�ȵ�ǰ���С,�ͽ���
		else if(x<ptr->data)
		{
			//�Ӵμ���base���¿�ʼ����
			grade--;
			ptr=base->link[grade];
		};
	};
	//���û���ҵ��ͷ��ؼ�
	return false;
};
//Insert()���г�Ա����,��Ԫ��x���뵽��ǰ��������ȥ,�ɹ��ͷ���true
template<class T>
bool SkipList<T>::Insert(T x)
{
	//���Ԫ���Ѿ����ھͷ���false
	if(Exist(x)||x>TailKey)
		return false;
	//Ϊ��Ԫ�ش����µĽ��
	SkipNode<T>* newNode=new SkipNode<T>(x);
	//���ڴ��Ҫ����Ľ��ǰ�ڸ��������е�ָ��
	SkipNode<T>** preLoc=new SkipNode<T>*[level+1];
	//�α�ָ��
	SkipNode<T>* ptr=head;
	//����߼���ʼ��������
	int grade=level;
	//Ѱ���½���ڸ��������в���λ��
	while(grade!=-1)
	{
		//���xС��ptr�¸�����ֵ
		if(x<ptr->link[grade]->data)
		{
			//�ѵ�ǰ��ptr��¼��preLoc������
			preLoc[grade]=ptr;
			//�����¼���������������
			grade--;
		}
		//���x����ptr�¸�����ֵ
		else if(x>ptr->link[grade]->data)
			ptr=ptr->link[grade];
	};
	//Ϊ������Ľ��������伶��
	int g=randLevel();
	//���½��newNode���뵽����������
	for(int i=g;i>=0;i--)
	{
		//���½������i��������
		newNode->link[i]=preLoc[i]->link[i];
		preLoc[i]->link[i]=newNode;
	};
	return true;
};
//Remove()//���г�Ա����,ɾ��������ָ��ֵ��Ԫ�ؽ��
template<class T>
bool SkipList<T>::Remove(T x)
{
	//���ָ����Ԫ�ز�����
	if(!Exist(x))
		return false;
	//���ڴ��Ҫɾ���Ľ��ǰ�ڸ��������е�ָ��
	SkipNode<T>** preLoc=new SkipNode<T>*[level+1];
	//�Ѹ������ʼ��ΪNULL
	for(int i=0;i<=level+1;i++)
		preLoc[i]=NULL;
	//�α�ָ��
	SkipNode<T>* ptr=head;
	//����߼���ʼ��������
	int grade=level;
	//Ѱ���½���ڸ��������в���λ��
	while(grade!=-1)
	{
		//���xС��ptr�¸�����ֵ
		if(ptr->link[grade]->data>x)
			//x�ڵ�ǰ���������в�����,
			//�����¼���������������
			grade--;
		//���x����ptr�¸�����ֵ
		else if(ptr->link[grade]->data<x)
			ptr=ptr->link[grade];
		//�������ptr�¸�����ֵ
		else if(ptr->link[grade]->data==x)
		{
			//��¼�µ�ǰҪɾ������ǰ��ָ��
			preLoc[grade]=ptr;
			//��������
			grade--;
		};
	};
	//�Ѹ�Ԫ���ڸ������н���ɾ��
	for(int i=0;preLoc[i]!=NULL;i++)
		preLoc[i]->link[i]=preLoc[i]->link[i]->link[i];

	return true;
};
//setGrade()˽�г�Ա����,���±��L��H�Ľ�����lev�ļ���
template<class T>
void SkipList<T>::setGrade(int* grade,int L,int H,int lev)
{
	//����½�С���Ͻ�
	if(L<H && lev>0)
	{
		//ȡ�м�Ԫ��
		int q=int((L+H)/2);
		//���ø�Ԫ�صļ���
		grade[q]=lev;
		//�ݹ�����q���ҵĽ��
		setGrade(grade,L,q-1,lev-1);
		setGrade(grade,q+1,H,lev-1);
	};
};
//randLevel()˽�г�Ա��������[0,level]֮���������һ������
template<class T>
int SkipList<T>::randLevel()
{
	srand(time(0));
	return rand()%(level+1);
};
int e=1000,d=4;
SkipList<int> s(e,d);
int main()
{
	int sp[12]={1,3,5,12,15,18,21,32,35,45,55,66};
	s.CreateSkipList(sp,12); //��������
	s.Display();//���ԭʼ����
	printf("nie\n");
	int k=1;
	while(k!=4)  //�����˵������
	{
		cout<<"1.����Ԫ��\n";
		cout<<"2.ɾ��Ԫ��\n";
		cout<<"3.���Ԫ��\n";
		cout<<"4.��������\n";
		cin>>k;
		switch(k)
		{
		case 1:	cout<<"����������Ԫ��"<<endl;
				int a;
				cin>>a;
				if(s.Search(a)->data==1000)
				{	cout<<"��ֵ�����ڣ�\n"<<'\n';}
				else
				{
					cout<<"Ԫ��:"<<s.Search(a)->data<<"����\n"<<'\n';
				}
				break;
		case 2:	cout<<"����ɾ����Ԫ��"<<endl;
				int b;
				cin>>b;
				if(s.Search(b)->data==1000)
				{	cout<<"��ֵ�����ڣ�\n"<<'\n';}
				else
				{
				s.Remove(b);
				cout<<"ɾ����������ʾ��"<<endl;
				s.Display();
				}
				break;
		case 3:	cout<<"������ӵ�Ԫ��"<<endl;
				int c;
				cin>>c;
				if(s.Search(b)->data!=1000)
				{
					cout<<"��ӵ�ֵ�Ѿ�����\n";
				}
				else
				{
				s.Insert(c);
				cout<<"��Ӻ�������ʾ��"<<endl;
				s.Display();
				}
				break;
		case 4:	;
		}
	}
}


