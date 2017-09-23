#ifndef _123DSL_
#define _123DSL_
template< class T >
class DSL
{
private:
	T Infinite;
	struct Node
	{
		T Data;
		Node *Right;
		Node *Down;
	};
	Node *Head;
	Node *Bottom;
	Node *Tail;
public:
	DSL( const T &inf )   /* ���캯��,����������������Ԫ��ֵ */
	{
		Infinite = inf;
		Head = new Node;
		Bottom = new Node;
		Tail = new Node;
		Head->Data = Tail->Data = Infinite;
		Head->Right = Tail->Right = Tail;
		Head->Down = Bottom->Down = Bottom->Right = Bottom;
	}
	~DSL()   /* �������� */
	{
		while( Head != Bottom )
		{
			Node *HeadDown = Head->Down;
			while( Head != Tail )
			{
				Node *HeadRight = Head->Right;
				delete Head;
				Head = HeadRight;
			}
			Head = HeadDown;
		}
		delete Bottom;
		delete Tail;
	}
	bool Find( const T &item )   /* ���Һ��� */
	{
		Node *p = Head;
		while( p != Bottom )
		{
			while( p->Data < item )
				p = p->Right;
			if( p->Data == item )
				return true;
			else p = p->Down;
		}
		return false;
	}
	void Insert( const T &item )   /* ���뺯��,��item���뵽��ײ� */
	{
		Bottom->Data = item; /* �޷�������,������Ч�����Ч�� */
		Node *p = Head;
		while( p != Bottom )
		{
			while( p->Data < item )
				p = p->Right;
			if( p->Data > p->Down->Right->Right->Data )   /* ������ж��Ƿ��½�һ���gapΪ3;���ߵ�ǰ����ײ���itemԪ��û�г��ֹ� */
			{
				Node *newNode = new Node;
				newNode->Right = p->Right;
				newNode->Down = p->Down->Right->Right;
				newNode->Data = p->Data;
				p->Right = newNode;
				p->Data = p->Down->Right->Data;
			}
			else p = p->Down;
		}
		if( Head->Right != Tail )   /* ���б�Ҫ,����DSL�ĸ߶� */
		{
			Node *newHead = new Node;
			newHead->Data = Infinite;
			newHead->Right = Tail;
			newHead->Down = Head;
			Head = newHead;
		}
	}
	void Delete( const T &item )   /* ɾ������ */
	{
		Node *p = Head;
		Node *StackHead = Tail; /* ջStack���ڼ�¼֮ǰ�����йؼ������item�Ľڵ��ַ */
		while( p->Down != Bottom )
		{
			Node *father = p; /* ��p�½�֮ǰ,��¼��һ��Ľڵ�father */
			p = p->Down; /* p�½�һ�� */
			Node *q = p; /* ָ��q������¼p��ͬһ���е�ǰ���ڵ� */
			while( p->Data < item )   /* p��q�����Ʋ��� */
			{
				q = p;
				p = p->Right;
			}
			/* ά��ջ��Ϣ */
			if( father->Data == p->Data )   /* ����ڵ�father��������Ҫ���Žڵ�p�����ݱ仯��һ��仯,��fatherѹ��ջStack�� */
			{
				Node *newStackHead = new Node;
				newStackHead->Right = StackHead;
				newStackHead->Down = father;
				StackHead = newStackHead;
			}
			else	/* ������ӹ�ϵ����һ���Ѷ�,��ջStack��� */
			{
				while( StackHead != Tail )
				{
					Node *newStackHead = StackHead->Right;
					delete StackHead;
					StackHead = newStackHead;
				}
			}
			/* ά���ڵ���Ϣ */
			if( p->Down == Bottom )   /* ������ײ�,��Ҫֱ��ɾ�� */
			{
				if( q == p )   /* ɾp���ҽڵ㲢������Ϣ������p�� */
				{
					Node *pRight = p->Right;
					p->Right = pRight->Right;
					p->Data = pRight->Data;
					delete pRight;
				}
				else	/* ֱ��ɾ�ڵ�p */
				{
					q->Right = p->Right;
					delete p;
					p = q; /* ��������ָ��p���ʺ�p->Down���ж� */
				}
				while( StackHead != Tail )   /* ���ջStack�ǿ�,���������нڵ����¸�ֵΪq->Data */
				{
					Node *newStackHead = StackHead->Right;
					StackHead->Down->Data = q->Data;
					delete StackHead;
					StackHead = newStackHead;
				}
			}
			else if( p->Data != p->Down->Right->Data  )	/* ����һ��gap����1,��ʲôҲ���� */
			{
			}
			else if ( q == p )	/* �����ұ����ڵ�gap */
			{
				if( p->Right->Data != p->Right->Down->Right->Data )   /* ���ұ����ڵ�gap����1,�����ұߵ�gap��һ�� */
				{
					p->Data = p->Right->Down->Data;
					p->Right->Down = p->Down->Right->Right->Right;
					while( StackHead != Tail )   /* ����p->Data�����ı�,���Խ�ջStack�����нڵ����¸�ֵ */
					{
						Node *newStackHead = StackHead->Right;
						StackHead->Down->Data = p->Data;
						delete StackHead;
						StackHead = newStackHead;
					}
				}
				else	/* ���ұ����ڵ�gapҲ����1,��ɾȥp���ҽڵ� */
				{
					Node *pRight = p->Right;
					p->Right = pRight->Right;
					p->Data = pRight->Data;
					delete pRight;
					while( StackHead != Tail )   /* ����p->Data�����ı�,���Խ�ջStack�����нڵ����¸�ֵ */
					{
						Node *newStackHead = StackHead->Right;
						StackHead->Down->Data = p->Data;
						delete StackHead;
						StackHead = newStackHead;
					}
				}
			}
			else	/* ����������ڵ�gap,������ڵ�gap��qΪͷָ�� */
			{
				if( q->Data != q->Down->Right->Data )   /* ��������ڵ�gap����1,������߽�һ�� */
				{
					Node *tmp = q->Down->Right;
					while( tmp->Right->Data != q->Data )
						tmp = tmp->Right;
					q->Data = tmp->Data;
					p->Down = tmp;
				}
				else	/* ��������ڵ�gapҲ����1,��ɾȥ�ڵ�p */
				{
					q->Right = p->Right;
					q->Data = p->Data;
					delete p;
					p = q; /* ��������ָ��p���ʺ�p->Down���ж� */
				}
			}
		}
		if( Head->Down->Data == Infinite )   /* ���б�Ҫ,����DSL�ĸ߶� */
		{
			Node *newHead = Head->Down;
			delete Head;
			Head = newHead;
		}
	}
	void print(){
		Node *x=Head;
		while (x->Down!=Bottom)x=x->Down;
		while (x->Right!=Tail)printf("%d ",x->Data),x=x->Right;
		printf("\n");
	}
};
#endif


