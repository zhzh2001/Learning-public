//O(n)��������Ӵ�
//ֻ��ʶ�𳤶�Ϊż���Ĵ�
//��Ҫʶ�𳤶�Ϊ�����Ĵ������� abcba �Ĵ���Ϊ aabbccbbaa
//�����maxR/=2 
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
const int N=100;
char str[N];
int rad[N];
int len,ans;

inline void Manacher(){
       int i=1,j=0,k;
       for (;i<=len;){
           while (i-j>0 && i+j+1<=len && str[i-j]==str[i+j+1]) j++;
           rad[i]=j;k=1;
           while (k<=rad[i] && rad[i-k]!=rad[i]-k){
                 rad[i+k]=(rad[i-k]<rad[i]-k)? rad[i-k]:rad[i]-k;
                 k++;
           }
           i=i+k;j=(j-k>0)? j-k:0;
       }
}

int main(){
    scanf("%s",str+1);
    len=strlen(str+1);
    Manacher();
    ans=0;
    for (int i=1;i<=len;i++) if (rad[i]>ans) ans=rad[i];
    printf("%d\n",ans);
    system("pause");
}
