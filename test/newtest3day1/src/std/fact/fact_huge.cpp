#include<bits/stdc++.h>
using namespace std;
struct huge{
	#define N_huge 10000
	#define base 100000000
	typedef long long value;
	value a[N_huge];int len;
	void clear(){len=1;a[len]=0;}
	huge(){clear();}
	huge(value x){*this=x;}
	huge operator =(const huge &b){
		len=b.len;for (int i=1;i<=len;++i)a[i]=b.a[i]; return *this;
	}
	huge operator +(const huge &b){
		int L=len>b.len?len:b.len;huge tmp;
		for (int i=1;i<=L+1;++i)tmp.a[i]=0;
		for (int i=1;i<=L;++i){
			if (i>len)tmp.a[i]+=b.a[i];
			else if (i>b.len)tmp.a[i]+=a[i];
			else {
				tmp.a[i]+=a[i]+b.a[i];
				if (tmp.a[i]>=base){
					tmp.a[i]-=base;++tmp.a[i+1];
				}
			}
		}
		if (tmp.a[L+1])tmp.len=L+1;
			else tmp.len=L;
		return tmp;
	}
	huge operator -(huge b){
		int L=len>b.len?len:b.len;huge tmp;
		for (int i=1;i<=L+1;++i)tmp.a[i]=0;
		for (int i=1;i<=L;++i){
			if (i>b.len)b.a[i]=0;
			tmp.a[i]+=a[i]-b.a[i];
			if (tmp.a[i]<0){
				tmp.a[i]+=base;--tmp.a[i+1];
			}
		}
		while (L>1&&!tmp.a[L])--L;
		tmp.len=L;
		return tmp;
	}
	huge operator *(const huge &b)const{
		int L=len+b.len;huge tmp;
		for (int i=1;i<=L;++i)tmp.a[i]=0;
		for (int i=1;i<=len;++i)
			for (int j=1;j<=b.len;++j){
				tmp.a[i+j-1]+=a[i]*b.a[j];
				if (tmp.a[i+j-1]>=base){
					tmp.a[i+j]+=tmp.a[i+j-1]/base;
					tmp.a[i+j-1]%=base;
				}
			}
		tmp.len=len+b.len;
		while (tmp.len>1&&!tmp.a[tmp.len])--tmp.len;
		return tmp;
	}
	pair<huge,huge> divide(const huge &a,const huge &b){
		int L=a.len;huge c,d;
		for (int i=L;i;--i){
			c.a[i]=0;d=d*base;d.a[1]=a.a[i];
			//while (d>=b){d-=b;++c.a[i];}
			int l=0,r=base-1,mid;
			while (l<r){
				mid=(l+r+1)>>1;
				if (b*mid<=d)l=mid;
					else r=mid-1;
			}
			c.a[i]=l;d-=b*l;
		}
		while (L>1&&!c.a[L])--L;c.len=L;
		return make_pair(c,d);
	}
	huge operator /(value x){
		value d=0;huge tmp;
		for (int i=len;i;--i){
			d=d*base+a[i];
			tmp.a[i]=d/x;d%=x;
		}
		tmp.len=len;
		while (tmp.len>1&&!tmp.a[tmp.len])--tmp.len;
		return tmp;
	}
	value operator %(value x){
		value d=0;
		for (int i=len;i;--i)d=(d*base+a[i])%x;
		return d;
	}
	huge operator /(const huge &b){return divide(*this,b).first;}
	huge operator %(const huge &b){return divide(*this,b).second;}
	huge &operator +=(const huge &b){*this=*this+b;return *this;}
	huge &operator -=(const huge &b){*this=*this-b;return *this;}
	huge &operator *=(const huge &b){*this=*this*b;return *this;}
	huge operator /=(const huge &b){*this=*this/b;return *this;}
	huge operator %=(const huge &b){*this=*this%b;return *this;}
	huge &operator ++(){huge T;T=1;*this=*this+T;return *this;}
	huge &operator --(){huge T;T=1;*this=*this-T;return *this;}
	huge operator ++(int){huge T,tmp=*this;T=1;*this=*this+T;return tmp;}
	huge operator --(int){huge T,tmp=*this;T=1;*this=*this-T;return tmp;}
	huge operator +(value x){huge T;T=x;return *this+T;}
	huge operator -(value x){huge T;T=x;return *this-T;}
	huge operator *(value x){huge T;T=x;return *this*T;}
	//huge operator /(value x){huge T;T=x;return *this/T;}
	//huge operator %(value x){huge T;T=x;return *this%T;}
	huge operator *=(value x){*this=*this*x;return *this;}
	huge operator +=(value x){*this=*this+x;return *this;}
	huge operator -=(value x){*this=*this-x;return *this;}
	huge operator /=(value x){*this=*this/x;return *this;}
	huge operator %=(value x){*this=*this%x;return *this;}
	bool operator ==(value x){huge T;T=x;return *this==T;}
	bool operator !=(value x){huge T;T=x;return *this!=T;}
	bool operator <=(value x){huge T;T=x;return *this<=T;}
	bool operator >=(value x){huge T;T=x;return *this>=T;}
	bool operator <(value x){huge T;T=x;return *this<T;}
	bool operator >(value x){huge T;T=x;return *this>T;}
	huge operator =(value x){
		len=0;
		while (x)a[++len]=x%base,x/=base;
		if (!len)a[++len]=0;
		return *this;
	}
	bool operator <(const huge &b){
		if (len<b.len)return 1;
		if (len>b.len)return 0;
		for (int i=len;i;--i){
			if (a[i]<b.a[i])return 1;
			if (a[i]>b.a[i])return 0;
		}
		return 0;
	}
	bool operator ==(const huge &b){
		if (len!=b.len)return 0;
		for (int i=len;i;--i)
			if (a[i]!=b.a[i])return 0;
		return 1;
	}
	bool operator !=(const huge &b){return !(*this==b);}
	bool operator >(const huge &b){return !(*this<b||*this==b);}
	bool operator <=(const huge &b){return (*this<b)||(*this==b);}
	bool operator >=(const huge &b){return (*this>b)||(*this==b);}
}ans;
ostream& operator<<(ostream& os,const huge& x)
{
	os<<x.a[x.len];
	char c=os.fill();
	os.fill('0');
	for(int i=x.len-1;i;i--)
	{
		os.width(8);
		os<<x.a[i];
	}
	os.fill(c);
	return os;
}
ifstream fin("fact.in");
ofstream fout("fact.out");
int main()
{
	int n,k;
	fin>>n>>k;
	ans=1;
	for(int i=1;i<=n;i++)
		ans*=i;
	stringstream ss;
	ss<<ans;
	int len=ss.str().length();
	string s;
	if(len<=k)
		s=ss.str();
	else
	{
		s=ss.str().substr(0,k);
		if(ss.str()[k]>='5')
		{
			stringstream ss1(s);
			long long t;
			ss1>>t;
			t++;
			stringstream ss2;
			ss2<<t;
			s=ss2.str();
		}
	}
	while(s[s.length()-1]=='0')
		s.erase(s.length()-1);
	if(k>1)
		fout<<s[0]<<'.'<<s.substr(1)<<"e+"<<len-1<<endl;
	else
		fout<<s[0]<<"e+"<<len-1<<endl;
	return 0;
}