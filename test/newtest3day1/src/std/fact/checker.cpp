#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc,char* argv[])
{
	registerTestlibCmd(argc,argv);
	string Out=ouf.readToken(),Ans=ans.readToken();
	double score=.0;
	size_t pans=Ans.find('e'),pout=Out.find('e');
	if(Ans.substr(0,pans)==Out.substr(0,pout))
		score+=.6;
	if(Ans.substr(pans+1)==Out.substr(pout+1))
		score+=.4;
	if(score==.0)
		quitp(score,"Wrong Answer");
	if(score==.6)
		quitp(score,"Error in Exponent");
	if(score==.4)
		quitp(score,"Error in Fraction");
	if(score==1.0)
		quitp(score,"Accepted");
	return 0;
}