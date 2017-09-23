
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define M 20000050

char str1[M],str[2*M];//start from index 1
int rad[M],nn,n;

void Manacher(int *rad,char *str,int n)/*str������һ���ַ������±��1��ʼ����
��������ԭ�ַ���Ϊ"abcd"����strΪ"$#a#b#c#d#"�������һ����ֹ����
nΪstr�ĳ��ȣ���ԭ�ַ�������Ϊnn����n=2*nn+2��
rad[i]��ʾ���ĵİ뾶��������j����str[i-j+1...i] = str[i+1...i+j]��
��rad[i]-1��Ϊ��str[i]Ϊ���ĵĻ����Ӵ���ԭ���еĳ���*/
{
    int i;
    int mx = 0;
    int id;
    for(i=1; i<n; i++)
    {
        if( mx > i )
			rad[i] = rad[2*id-i]<mx-i?rad[2*id-i]:mx-i;        
        else
            rad[i] = 1;
        for(; str[i+rad[i]] == str[i-rad[i]]; rad[i]++)
            ;
        if( rad[i] + i > mx )
        {
            mx = rad[i] + i;
            id = i;
        }
    }
}

n#a#a#e
int main()
{
	int i,ans,Case=1;
	while(scanf("%s",str1)!=EOF)
	{
		nn=strlen(str1);
		n=2*nn+2;
		str[0]='$';
		printf("nie%d\n",nn);
		for(i=0;i<=nn;i++)
		{
			str[2*i+1]='#';
			str[2*i+2]=str1[i];
		}
		Manacher(rad,str,n);
		ans=1;
		for(i=0;i<n;i++)
			ans=rad[i]>ans?rad[i]:ans;
		printf("%d\n",ans-1);
	}
return 0;
}
