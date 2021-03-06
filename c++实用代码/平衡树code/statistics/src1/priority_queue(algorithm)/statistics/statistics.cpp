#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
#include<stack>
#include<functional>
using namespace std;
priority_queue<int,vector<int>,greater<int> > a1;
class Priority_queue
{
    private:
        vector<int> data;
         
    public:
        void push( int t ){ 
            data.push_back(t); 
            push_heap( data.begin(), data.end()); 
        }
         
        void pop(){
            pop_heap( data.begin(), data.end() );
            data.pop_back();
        }
         
        int top() { return data.front(); }
        int size() { return data.size(); }
        bool empty() { return data.empty(); }
};
Priority_queue a;
int main()
{
	long long n,A,b,c,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.push(1);
	for (int i=2;i<=n;++i){
		key=(A*a.top()+b*i+c)%1000000007;
		if (i&1)a.push(key);
			else a1.push(key);
		while (a.top()>a1.top()){
			int tmp1=a.top(),tmp2=a1.top();
			a.pop();a1.pop();
			a.push(tmp2);a1.push(tmp1);
		}
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


