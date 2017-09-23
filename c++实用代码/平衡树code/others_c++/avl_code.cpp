#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct AvlNode;
typedef AvlNode *Position;
typedef AvlNode *AvlTree;
#define ElementType int

int Max(int,int);
int Height(Position T);
AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType x,AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType x,AvlTree T);
AvlTree Delete(ElementType x,AvlTree T);
AvlTree LLRotate(Position k2);
AvlTree RRRotate(Position k2);
AvlTree LRRotate(Position k2);
AvlTree RLRotate(Position k2);
void PrintTree(AvlTree T,int depth);
void PrintName(AvlTree T,int depth);
char Welcome(void);

struct AvlNode
{
	ElementType data;
	AvlTree left;
	AvlTree right;
	int height;
};

int main(void)
{
	char a;
	int value;
	AvlTree T = NULL;
	while(1)
	{
		switch(a = Welcome())
		{
			fflush(stdin);
		case '1':
			printf("������Ҫ��ӵ�ֵ��");
			scanf("%d",&value);
			fflush(stdin);
			T = Insert(value,T);
			break;
		case '2':
			printf("������Ҫɾ����ֵ��");
			scanf("%d",&value);
			fflush(stdin);
			T = Delete(value,T);
			break;
		case '3':
			PrintTree(T,0);
			fflush(stdin);
			getch();
			break;
		case '4':
			MakeEmpty(T);
			system("pause");
			return 0;
		default:
			printf("�������\n");
		}
	}

	return 0;
}

int Max(int a,int b)
{
	return ((a>b)?a:b);
}
int Height(Position T)
{
	if(T == NULL)
		return -1;
	else
		return T->height;
}
AvlTree MakeEmpty(AvlTree T)
{
	if(T != NULL)
	{
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}
	return NULL;
}

Position Find(ElementType x,AvlTree T)
{
	if(T == NULL)
		return NULL;
	else if(x < T->data)
		return Find(x,T->left);
	else if(x > T->data)
		return Find(x,T->right);
	else
		return T;
}

Position FindMin(AvlTree T)
{
	if(T == NULL)
		return NULL;
	while(T->left != NULL)
		T = T->left;
	return T;
}

Position FindMax(AvlTree T)
{
	if(T == NULL)
		return NULL;
	else if(T->right == NULL)
		return T;
	else
		return FindMax(T->right);
}

AvlTree Insert(ElementType x,AvlTree T)
{
	if(T == NULL)
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		T->data = x;
		T->height = 0;
		T->left = T->right  = NULL;
	}
	else if(x < T->data)//�����ǰ�ڵ��ֵ����Ҫ�����ֵ�����������������
	{
		T->left = Insert(x,T->left);
		if(Height(T->left) - Height(T->right) == 2)//������ɺ���֤���Ƿ�ƽ�⡣�����ƽ��
		{								//����LL����LR�ͣ���Ϊ�Ѿ�����������������ֻ�������ֿ��ܡ�
			if(x < T->left->data)		//�����ͬ��
			{
				T = LLRotate(T);
			}
			else
			{
				T = LRRotate(T);
			}
		}
	}
	else if(x > T->data)//�����ǰ�ڵ��ֵС��Ҫ�����ֵ�����������������
	{
		T->right = Insert(x,T->right);
		if(Height(T->right) - Height(T->left) == 2)
		{
			if(x > T->right->data)
			{
				T = RRRotate(T);
			}
			else
			{
				T = RLRotate(T);
			}
		}
	}
//���������Ҫ�������ڲ�����֮�󣬸ı���ڵ�ĸ߶ȡ�����û�в��룬�������䲻������κ�ֵ�øı䡣
	T->height = Max(Height(T->left),Height(T->right)) + 1;//��Ϊ�ǵݹ顣�����ڵ��⡣����˼������
	return T;
}

AvlTree Delete(ElementType x,AvlTree T)//���ɾ�������Ǳ����Լ���д�����ûץ�񡣇�Orz..
{
	Position tmp;
	if(T == NULL)
	{
		printf("Can't found!\n");
		return NULL;
	}
	else if(x < T->data)
	{
		T->left = Delete(x,T->left);//���ɾ�������������Ľڵ㣬���������ƽ�⣬�϶���������������
		if(Height(T->right) - Height(T->left) == 2)
		{//�ⲽ���ж���RR����RL�͡������ͬ����
			if( Height(T->right->right) >= Height(T->right->left) )
				T = RRRotate(T);
			else
				T = RLRotate(T);
		}
	}
	else if(x > T->data)
	{
		T->right = Delete(x,T->right);
		if(Height(T->left) - Height(T->right) == 2)
		{
			if( Height(T->left->left) >= Height(T->left->right) )
				T = LLRotate(T);
			else
				T = LRRotate(T);
		}
	}
	else
	{
		if(T->left && T->right) //�����������ӵĽڵ�ɾ�����������类ɾ�ڵ����������ӽڵ㣬����������������Сֵ�Ľڵ�
		{						//�����滻��Ȼ��ɾ��������������Сֵ�Ľڵ㡣(������С�����������һ���Һ��ӡ������ͷ��㡣
			tmp = FindMin(T->left);
			T->data = tmp->data;
			Delete(tmp->data,T->left);
		}
		else//����һ����0�����ӵĽڵ��ɾ��������
		{
			tmp = T;
			if(T->left == NULL)
				T = T->right;
			else if(T->right == NULL)
				T = T->left;
			free(tmp);
		}
	}//���if��Ϊ�˱���ɾ���ڵ�֮���NULLָ�븳ֵ��
	if(T != NULL)
		T->height = Max(Height(T->left),Height(T->right)) +1;//�������ڵ�ĸ߶ȡ�
	return T;
}

AvlTree LLRotate(Position k2)//��LL�� ֱ���ڲ�ƽ��ڵ㴦��������ת��
{
	Position k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = Max(Height(k2->left),Height(k2->right))+1;
	k1->height = Max(Height(k1->left),Height(k1->right))+1;
	return k1;
}

AvlTree RRRotate(Position k1)//��RR�� ֱ���ڲ�ƽ��ڵ㴦��������ת��
{
	Position k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k2->height = Max(Height(k2->left),Height(k2->right))+1;
	k1->height = Max(Height(k1->left),Height(k1->right))+1;

	return k2;
}

AvlTree LRRotate(Position k3)//����LR��
{
	k3->left = RRRotate(k3->left);//��һ�����ڲ�ƽ��ڵ�k3�������k1����������ת��
	return LLRotate(k3);//���ǵڶ������ڲ�ƽ��ڵ�k3����������ת���������µĸ���
}

AvlTree RLRotate(Position k3)//����RL��
{
	k3->right = LLRotate(k3->right);//��һ�����ڲ�ƽ��ڵ�k3���Ҷ���k1����������ת��
	return RRRotate(k3);//���ǵڶ������ڲ�ƽ��ڵ�k3����������ת���������µĸ���
}

void PrintTree(AvlTree T,int depth)//��ӡ������Ϊ��ֱ�ۣ������������Ҳ��������Ҳ���Ǻ��򣬇塣
{
	if(T != NULL)
	{
		PrintName(T,depth);
		PrintTree(T->right,depth+1);
		PrintTree(T->left,depth+1);
	}
}

void PrintName(AvlTree T,int depth)
{
	for(int i=0; i<depth; i++)
		printf("   ");
	printf("%d(%d)\n",T->data,T->height);
}

char Welcome(void)//���Ժ���
{
	char a;
	printf("1.����ڵ�\n");
	printf("2.ɾ���ڵ�\n");
	printf("3.��ӡ��\n");
	printf("4.�˳�����\n");
	a = getchar();
	return a;
}


