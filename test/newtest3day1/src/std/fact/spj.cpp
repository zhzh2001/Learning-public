#include<bits/stdc++.h>
using namespace std;
int main(int argc,char* argv[])
{
	if(argc<4)
		return 1;
	ifstream fans(argv[2]),fout(argv[3]);
	FILE *fres=argc>4?fopen(argv[4],"w"):stdout;
	string ans,out;
	fans>>ans;
	fout>>out;
	double score=.0;
	size_t pans=ans.find('e'),pout=out.find('e');
	if(ans.substr(0,pans)==out.substr(0,pout))
		score+=.6;
	if(ans.substr(pans+1)==out.substr(pout+1))
		score+=.4;
	fprintf(fres,"%.3lf\n",score);
	if(score==.0)
		fputs("答案错误",fres);
	if(score==.6)
		fputs("指数错误",fres);
	if(score==.4)
		fputs("尾数错误",fres);
	if(score==1.0)
		fputs("正确",fres);
	return 0;
}