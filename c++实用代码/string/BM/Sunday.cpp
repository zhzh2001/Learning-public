#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<list>
#include<functional>

using namespace std;
int main()
{
	int i;
	char *text = new char[100];
	text = "substring searching algorithm search";
	char *patt = new char[10];
	patt = "search";
	size_t temp[256];
	size_t *shift = temp;
	size_t patt_size = strlen(patt);
	cout << "size : " << patt_size << endl;
	for(size_t i = 0; i < 256; i++)
		*(shift + i) = patt_size + 1; //����ֵ����7�����������
	for(i = 0; i < patt_size; i++)
		*(shift + (unsigned char)(*(patt + i) ) ) = patt_size - i;
	//�ƶ�3��-->shift['r']=6-3=3;�ƶ�����
	//shift['s']=6��,shitf['e']=5�Դ�����
	size_t text_size = strlen(text);
	size_t limit = text_size - i + 1;
	for(i = 0; i < limit; i += shift[text[i+patt_size] ] )
		if(text[i] == *patt)
		{
			/*	^13--���r��λ����0��ʼ��
				substring searching algorithm
				search
				searching-->���sΪ��10λ����0��ʼ��
				�����һ���ֽ�ƥ�䣬��ô����ƥ��ʣ�µ�
				*/
			char *match_text = text + i + 1;
			size_t	 match_size = 1;
			do
			{
				if(match_size == patt_size)
					cout << "the no is " << i << endl;
			}
			while( (*match_text++) == patt[match_size++] );
		}
	cout << endl;
	system("pause");for (;;);
	return 0;
}


