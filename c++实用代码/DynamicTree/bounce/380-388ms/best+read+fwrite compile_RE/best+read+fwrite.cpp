//update2
/**************************************************************
    Problem: 2002
    User: dogcpp
    Language: C++
    Result: Accepted
    Time:380 ms
    Memory:5792 kb
****************************************************************/
 
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#define maxn 200010
int n,x,y,T;   
struct DynamicTree{   
    struct node{   
        int size;   
        node *l,*r,*p; 
    };   
    node *a,*null;   
    int isroot(node *p){return p->p->l!=p&&p->p->r!=p;}   
    void clear(){   
        null=new node;null->l=null->r=null;   
        null->size=0;   
    }   
    void ini_node(node *p){   
        p->l=p->r=null;p->size=1; 
    }
    void set(int n){
        n+=5;a=new node[n];clear();
        for (int i=0;i<n;++i)ini_node(a+i);
    }
    void zig(node *x){
        node *y=x->p,*z=y->p;
        if (z->l==y) z->l=x;else if (z->r==y)z->r=x;   
        x->p=z;y->p=x;   
        y->l=x->r;x->r=y;   
        y->l->p=y;   
        y->size=y->l->size+y->r->size+1;  
    }   
    void zag(node *x){   
        node *y=x->p,*z=y->p;   
        if (z->l==y) z->l=x;else if (z->r==y)z->r=x;   
        x->p=z;y->p=x;   
        y->r=x->l;x->l=y;   
        y->r->p=y;   
        y->size=y->l->size+y->r->size+1;  
    }   
    void splay(node *x)   
    {   
        node *y,*z;   
        if (x==null) return; 
        while (!isroot(x)){   
            y=x->p;z=y->p;   
            if (isroot(y)) {if (x==y->l)zig(x);else zag(x);}   
            else
                if (y==z->l)   
                    if (x==y->l){zig(y);zig(x);} 
                    else{zag(x);zig(x);}   
                else
                    if (x==y->r){zag(y);zag(x);}   
                    else{zig(x);zag(x);}   
        }
        x->size=x->l->size+x->r->size+1;  
    } 
    node *Expose(node *p){   
        node *q=null;   
        for (;p!=null;p=p->p){   
            splay(p);p->r=q;p->size=p->l->size+q->size+1;q=p;
        }
        return q;
    } 
    node *getnode(int x){return a+x;}   
    int getid(node *p){return p-a;}   
    int Depth(node *p){Expose(p);splay(p);return p->l->size;} 
    void Cut(node *p){   
        splay(p);p->l->p=p->p;p->l=null;
        p->size=p->r->size+1;
    }   
    void Changefa(node *x,node *y){Cut(x);x->p=y;}
    void Changefa(int x,int y){Changefa(getnode(x),getnode(y));}   
};   
DynamicTree a; 
char str[1500000],*p=str,buf[10],out[400000],*o=out;
inline int Read(){
    int re=0;
    while(*p<'0'||*p>'9')p++;
    while(*p>='0'&&*p<='9')re=re*10+*p++-48;
    return re;
}
inline void print(int x){
    char *b=buf;
    while(x){*b++=x%10+48;x/=10;} 
    while(b--!=buf)*o++=*b; 
    *o++='\n'; 
} 
void init(){ 
     int i,x,y,z; 
     n=Read();a.set(n);
     for (i=1;i<=n;i++){   
         x=Read(); 
         int tmp=i+x>n?n+1:i+x; 
         a.a[i].p=a.getnode(tmp); 
     } 
     a.a[n+1].p=a.null; 
}   
int main()
{
    //freopen("bounce.in","r",stdin);   
    //freopen("bounce+.out","w",stdout); 
    //fRead(p,1,1500000,stdin);
    //stdin
    int fd =3; //open("bounce1.in",O_RDONLY);
    //printf("nie%d\n",fd);
    read(fd,str,1500000);
    int m,ch,i,tmp;  
    init();
    m=Read();++m;
    for (i=1;i<m;++i){
        ch=Read();x=Read();++x;
        if (ch==1){ 
                   print(a.Depth(a.getnode(x))); 
                   }
        else       {
                   y=Read();
                   tmp=x+y;if (tmp>n)tmp=n+1;
                   a.Changefa(x,tmp);
                   }
        }
    //puts(out);
    fwrite(out,1,o-out,stdout);
    //for (;;);
    return 0;
}


