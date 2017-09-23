#include <direct.h>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
char str[1000005];
int allline,effectline,big,small,allchar,visiblechar;
int filenum;
string bigfile,smallfile;
void count(const string &filename)
{
	freopen(filename.data(),"r",stdin);
	filenum++;
	int line=0;
	while(gets(str))
	{
		allline++;
		line++;
		bool flag=false;
		for(int i=0; str[i]; i++)
		{
			if(!(str[i]==' ' || str[i]=='{' || str[i]=='}' || str[i]=='\t'))
			{
				flag=true;
				visiblechar++;
			}
			if(str[i]=='{' || str[i]=='}')visiblechar++;
			allchar++;
		}
		if(flag)effectline++;
	}
	if(big<line)
	{
		bigfile=filename;
		big=line;
	}
	if(small>line)
	{
		smallfile=filename;
		small=line;
	}
	fclose(stdin);
	freopen("CON","r",stdin);
}
void getFiles(const string &path)
{
	//�ļ����
	long hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string *pp=new string;
	string &p=*pp;
	if((hFile=_findfirst(p.assign(path).append("\\*").c_str(),&fileinfo))   !=   -1)
	{
		do
		{
			//�����Ŀ¼,����֮
			//�������,�����б�
			if((fileinfo.attrib&_A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".")!=0&&strcmp(fileinfo.name,"..")!=0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name));
			}
			else
			{
				string filename=p.assign(path).append("\\").append(fileinfo.name);
				int t=filename.find(".cpp");
				if(filename.length()-t==4)
					count(filename);
				t=filename.find(".java");
				if(filename.length()-t==5)
					count(filename);
			}
		}
		while(_findnext(hFile,&fileinfo)==0);
		_findclose(hFile);
	}
}
int main()
{
	allline=effectline=big=allchar=visiblechar=filenum=0;
	small=0x7fffffff;
	printf("������·��\n��ʽ��\nE:\\yy\n");
	string path;
	cin>>path;
	getFiles(path.data());
	printf("<< %s >>�¹���<< %d >>��Դ�ļ�\n",path.data(),filenum);
	printf("�������д�������Ϊ<< %d >>��\n",allline);
	printf("��Ч��������Ϊ<< %d >>��\n",effectline);
	printf("ÿ���ļ�ƽ������Ϊ<< %d >>��\n",allline/filenum);
	printf("��������ļ��� << %s >> ���д���<< %d >>��\n",bigfile.data(),big);
	printf("������̵��ļ��� << %s >> ���д���<< %d >>��\n",smallfile.data(),small);
	printf("���е��ַ���<< %d >>��\n",allchar);
	printf("���пɼ��ַ���<< %d >>��\n",visiblechar);
	printf("ƽ��ÿ���ļ��ɼ��ַ���<< %d >>��\n",visiblechar/filenum);
	system("pause");
	return 0;
}


