#include <cmath > 
#include <cstdio>
#include <algorithm>

using namespace std;

/* ���õĳ������� */ 
const double    INF     = 1E200    ;
const double    EP      = 1E-10 ;
const int       MAXV    = 300 ;
const double    PI      = 3.14159265 ;

/* �������νṹ */ 
struct POINT 
{ 
    double x; 
    double y; 
	int seq;
    POINT(double a=0, double b=0) { x=a; y=b;} //constructor 
}; 
struct LINESEG 
{ 
    POINT s; 
    POINT e; 
    LINESEG(POINT a, POINT b) { s=a; e=b;} 
    LINESEG() { } 
}; 
struct LINE           // ֱ�ߵĽ������� a*x+b*y+c=0  Ϊͳһ��ʾ��Լ�� a >= 0 
{ 
   double a; 
   double b; 
   double c; 
   LINE(double d1=1, double d2=-1, double d3=0) {a=d1; b=d2; c=d3;} 
}; 

/**********************
 *                    * 
 *   ��Ļ�������     * 
 *                    * 
 **********************/ 
//1. ƽ��������֮����� 1 
double dist(POINT p1,POINT p2)                // ��������֮��ŷ�Ͼ��� 
{ 
    return( sqrt( (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y) ) ); 
} 
//2. �ж������Ƿ��غ� 1 
bool equal_point(POINT p1,POINT p2)           // �ж��������Ƿ��غ�  
{ 
    return ( (abs(p1.x-p2.x)<EP)&&(abs(p1.y-p2.y)<EP) ); 
} 
//3. ʸ����� 1 
/****************************************************************************** 
r=multiply(sp,ep,op),�õ�(sp-op)��(ep-op)�Ĳ�� 
r>0��ep��ʸ��opsp����ʱ�뷽�� 
r=0��opspep���㹲�ߣ� 
r<0��ep��ʸ��opsp��˳ʱ�뷽�� 
*******************************************************************************/ 
double multiply(POINT sp,POINT ep,POINT op) 
{ 
    return((sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y)); 
} 
//4. ʸ����� 2 
/* 
r=dotmultiply(p1,p2,op),�õ�ʸ��(p1-op)��(p2-op)�ĵ�����������ʸ��������ʸ�� 
r<0����ʸ���н�Ϊ��ǣ�
r=0����ʸ���н�Ϊֱ�ǣ�
r>0����ʸ���н�Ϊ�۽� 
*******************************************************************************/ 
double dotmultiply(POINT p1,POINT p2,POINT p0) 
{ 
    return ((p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y)); 
} 

//5. �жϵ��Ƿ����߶��� 2 
/****************************************************************************** 
�жϵ�p�Ƿ����߶�l��
������(p���߶�l���ڵ�ֱ����) && (��p�����߶�lΪ�Խ��ߵľ�����)
*******************************************************************************/ 
bool online(LINESEG l,POINT p) 
{ 
    return( (multiply(l.e,p,l.s)==0) &&( ( (p.x-l.s.x)*(p.x-l.e.x)<=0 )&&( (p.y-l.s.y)*(p.y-l.e.y)<=0 ) ) ); 
} 
//6. ��һ����ĳ����ת������� 2 
// ���ص�p�Ե�oΪԲ����ʱ����תalpha(��λ������)�����ڵ�λ�� 
POINT rotate(POINT o,double alpha,POINT p) 
{ 
    POINT tp; 
    p.x-=o.x; 
    p.y-=o.y; 
    tp.x=p.x*cos(alpha)-p.y*sin(alpha)+o.x; 
    tp.y=p.y*cos(alpha)+p.x*sin(alpha)+o.y; 
    return tp; 
} 
//7. ��ʸ���н� 2 
/* ���ض�����o�㣬��ʼ��Ϊos����ֹ��Ϊoe�ļн�(��λ������) 
    �Ƕ�С��pi��������ֵ 
    �Ƕȴ���pi�����ظ�ֵ 
    �����������߶�֮��ļн� 
ԭ��
    r = dotmultiply(s,e,o) / (dist(o,s)*dist(o,e))
    r'= multiply(s,e,o)

    r >= 1  angle = 0;
    r <= -1 angle = -PI
    -1<r<1 && r'>0  angle = arccos(r)
    -1<r<1 && r'<=0 angle = -arccos(r)
*/ 
double angle(POINT o,POINT s,POINT e) 
{ 
    double cosfi,fi,norm; 
    double dsx = s.x - o.x; 
    double dsy = s.y - o.y; 
    double dex = e.x - o.x; 
    double dey = e.y - o.y; 

    cosfi=dsx*dex+dsy*dey; 
    norm=(dsx*dsx+dsy*dsy)*(dex*dex+dey*dey); 
    cosfi /= sqrt( norm ); 

    if (cosfi >=  1.0 ) return 0; 
    if (cosfi <= -1.0 ) return -3.1415926; 

    fi=acos(cosfi); 
    if (dsx*dey-dsy*dex>0) return fi;      // ˵��ʸ��os ��ʸ�� oe��˳ʱ�뷽�� 
    return -fi; 
} 
  /*****************************\ 
  *                             * 
  *      �߶μ�ֱ�ߵĻ�������   * 
  *                             * 
  \*****************************/ 
//1. �����߶εĹ�ϵ 3 
/* �жϵ����߶εĹ�ϵ,��;�ܹ㷺 
�������Ǹ�������Ĺ�ʽд�ģ�P�ǵ�C���߶�AB����ֱ�ߵĴ��� 

                AC dot AB 
        r =     --------- 
                 ||AB||^2 
             (Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay) 
          = ------------------------------- 
                          L^2 

    r has the following meaning: 

        r=0      P = A 
        r=1      P = B 
        r<0      P is on the backward extension of AB 
        r>1      P is on the forward extension of AB 
        0<r<1    P is interior to AB 
*/ 
double relation(POINT p,LINESEG l) 
{ 
    LINESEG tl; 
    tl.s=l.s; 
    tl.e=p; 
    return dotmultiply(tl.e,l.e,l.s)/(dist(l.s,l.e)*dist(l.s,l.e)); 
} 
//2. ��㵽�߶�����ֱ�ߴ��ߵĴ��� 4 
// ���C���߶�AB����ֱ�ߵĴ��� P 
POINT perpendicular(POINT p,LINESEG l) 
{ 
    double r=relation(p,l); 
    POINT tp; 
    tp.x=l.s.x+r*(l.e.x-l.s.x); 
    tp.y=l.s.y+r*(l.e.y-l.s.y); 
    return tp; 
} 
//3. �㵽�߶ε������ 4 
/* ���p���߶�l����̾���,�������߶��Ͼ�õ�����ĵ�np 
ע�⣺np���߶�l�ϵ���p����ĵ㣬��һ���Ǵ��� */ 
double ptolinesegdist(POINT p,LINESEG l,POINT &np) 
{ 
    double r=relation(p,l); 
    if(r<0) 
    { 
        np=l.s; 
        return dist(p,l.s); 
    } 
    if(r>1) 
    { 
        np=l.e; 
        return dist(p,l.e); 
    } 
    np=perpendicular(p,l); 
    return dist(p,np); 
} 
//4. �㵽�߶�����ֱ�ߵľ��� 4 
// ���p���߶�l����ֱ�ߵľ���,��ע�Ȿ�������ϸ�����������  
double ptoldist(POINT p,LINESEG l) 
{ 
    return abs(multiply(p,l.e,l.s))/dist(l.s,l.e); 
} 
//5. �㵽���߼���������� 4 
/* ����㵽���߼����������,�����������. 
ע�⣺���õ���ptolineseg()���� */ 
double ptopointset(int vcount,POINT pointset[],POINT p,POINT &q) 
{ 
    int i; 
    double cd=double(INF),td; 
    LINESEG l; 
    POINT tq,cq; 

    for(i=0;i<vcount-1;i++) 
    { 
        l.s=pointset[i]; 

        l.e=pointset[i+1]; 
        td=ptolinesegdist(p,l,tq); 
        if(td<cd) 
        { 
            cd=td; 
            cq=tq; 
        } 
    } 
    q=cq; 
    return cd; 
} 
//6. �ж�Բ�Ƿ��ڶ������ 5 
/* �ж�Բ�Ƿ��ڶ������.ptolineseg()������Ӧ��2 */ 
bool CircleInsidePolygon(int vcount,POINT center,double radius,POINT polygon[]) 
{ 
    POINT q; 
    double d; 
    q.x=0; 
    q.y=0; 
    d=ptopointset(vcount,polygon,center,q); 
    if(d<radius||fabs(d-radius)<EP) 
        return true; 
    else 
        return false; 
} 
//8. ���߶�֮��ļн� 5 
// �����߶�l1��l2֮��ļн� ��λ������ ��Χ(-pi��pi) 
double lsangle(LINESEG l1,LINESEG l2) 
{ 
    POINT o,s,e; 
    o.x=o.y=0; 
    s.x=l1.e.x-l1.s.x; 
    s.y=l1.e.y-l1.s.y; 
    e.x=l2.e.x-l2.s.x; 
    e.y=l2.e.y-l2.s.y; 
    return angle(o,s,e); 
} 
//9. �ж��߶��Ƿ��ཻ 6 
// ����߶�u��v�ཻ(�����ཻ�ڶ˵㴦)ʱ������true 
//
//�ж�P1P2����Q1Q2�������ǣ�( P1 - Q1 ) �� ( Q2 - Q1 ) * ( Q2 - Q1 ) �� ( P2 - Q1 ) >= 0��
//�ж�Q1Q2����P1P2�������ǣ�( Q1 - P1 ) �� ( P2 - P1 ) * ( P2 - P1 ) �� ( Q2 - P1 ) >= 0��
bool intersect(LINESEG u,LINESEG v) 
{ 
    return( (max(u.s.x,u.e.x)>=min(v.s.x,v.e.x))&&                     //�ų�ʵ�� 
            (max(v.s.x,v.e.x)>=min(u.s.x,u.e.x))&& 
            (max(u.s.y,u.e.y)>=min(v.s.y,v.e.y))&& 
            (max(v.s.y,v.e.y)>=min(u.s.y,u.e.y))&& 
            (multiply(v.s,u.e,u.s)*multiply(u.e,v.e,u.s)>=0)&&         //����ʵ�� 
            (multiply(u.s,v.e,v.s)*multiply(v.e,u.e,v.s)>=0)); 
} 
//10.�ж��߶��Ƿ��ཻ�������ڶ˵㴦 6 
//  (�߶�u��v�ཻ)&&(���㲻��˫���Ķ˵�) ʱ����true    
bool intersect_A(LINESEG u,LINESEG v) 
{ 
    return  ((intersect(u,v))&& 
            (!online(u,v.s))&& 
            (!online(u,v.e))&& 
            (!online(v,u.e))&& 
            (!online(v,u.s))); 
} 
//11.���߶�����ֱ�ߵķ��� 6 
// �߶�v����ֱ�����߶�u�ཻʱ����true���������ж��߶�u�Ƿ�����߶�v  
bool intersect_l(LINESEG u,LINESEG v) 
{ 
    return multiply(u.s,v.e,v.s)*multiply(v.e,u.e,v.s)>=0; 
} 
//11.���߶�����ֱ�ߵķ��� 6 
// ������֪�������꣬����������ֱ�߽������̣� a*x+b*y+c = 0  (a >= 0)  
LINE makeline(POINT p1,POINT p2) 
{ 
    LINE tl; 
    int sign = 1; 
    tl.a=p2.y-p1.y; 
    if(tl.a<0) 
    { 
        sign = -1; 
        tl.a=sign*tl.a; 
    } 
    tl.b=sign*(p1.x-p2.x); 
    tl.c=sign*(p1.y*p2.x-p1.x*p2.y); 
    return tl; 
} 
//12.��ֱ�ߵ�б�� 7 
// ����ֱ�߽������̷���ֱ�ߵ�б��k,ˮƽ�߷��� 0,��ֱ�߷��� 1e200 
double slope(LINE l) 
{ 
    if(abs(l.a) < 1e-20)
        return 0; 
    if(abs(l.b) < 1e-20)
        return INF; 
    return -(l.a/l.b); 
} 
//13.��ֱ�ߵ���б�� 7 
// ����ֱ�ߵ���б��alpha ( 0 - pi) 
double alpha(LINE l) 
{ 
    if(abs(l.a)< EP)
        return 0; 
    if(abs(l.b)< EP)
        return PI/2; 
    double k=slope(l); 
    if(k>0) 
        return atan(k); 
    else 
        return PI+atan(k); 
} 
//14.������ĳֱ�ߵĶԳƵ� 7 
// ���p����ֱ��l�ĶԳƵ�  
POINT symmetry(LINE l,POINT p) 
{ 
   POINT tp; 
   tp.x=((l.b*l.b-l.a*l.a)*p.x-2*l.a*l.b*p.y-2*l.a*l.c)/(l.a*l.a+l.b*l.b); 
   tp.y=((l.a*l.a-l.b*l.b)*p.y-2*l.a*l.b*p.x-2*l.b*l.c)/(l.a*l.a+l.b*l.b); 
   return tp; 
} 
//15.�ж�����ֱ���Ƿ��ཻ����ֱ�߽��� 7 
// �������ֱ�� l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)�ཻ������true���ҷ��ؽ���p  
bool lineintersect(LINE l1,LINE l2,POINT &p) // �� L1��L2 
{ 
    double d=l1.a*l2.b-l2.a*l1.b; 
    if(abs(d)<EP) // ���ཻ 
        return false; 
    p.x = (l2.c*l1.b-l1.c*l2.b)/d; 
    p.y = (l2.a*l1.c-l1.a*l2.c)/d; 
    return true; 
} 
//16.�ж��߶��Ƿ��ཻ������ཻ���ؽ��� 7 
// ����߶�l1��l2�ཻ������true�ҽ�����(inter)���أ����򷵻�false 
bool intersection(LINESEG l1,LINESEG l2,POINT &inter) 
{ 
    LINE ll1,ll2; 
    ll1=makeline(l1.s,l1.e); 
    ll2=makeline(l2.s,l2.e); 
    if(lineintersect(ll1,ll2,inter)) 
        return online(l1,inter); 
    else 
        return false; 
} 

/******************************\ 
*                             * 
* ����γ����㷨ģ��         * 
*                             * 
\******************************/ 

// ������ر�˵�����������ζ���Ҫ����ʱ������ 

/* 
����ֵ������Ķ�����Ǽ򵥶���Σ�����true 
Ҫ �����붥�����а���ʱ������ 
˵ �����򵥶���ζ��壺 
1��ѭ�������������߶ζԵĽ�������֮�乲�еĵ����� 
2�������ڵ��߶β��ཻ 
������Ĭ�ϵ�һ�������Ѿ����� 
*/ 
//1. �ж϶�����Ƿ�򵥶���� 8 
bool issimple(int vcount,POINT polygon[]) 
{ 
    int i,cn; 
    LINESEG l1,l2; 
    for(i=0;i<vcount;i++) 
    { 
        l1.s=polygon[i]; 
        l1.e=polygon[(i+1)%vcount]; 
        cn=vcount-3; 
        while(cn) 
        { 
            l2.s=polygon[(i+2)%vcount]; 
            l2.e=polygon[(i+3)%vcount]; 
            if(intersect(l1,l2)) 
                break; 
            cn--; 
        } 
        if(cn) 
            return false; 
    } 
    return true; 
} 
//2. ������ζ����͹���� 9 
// ����ֵ��������˳�򷵻ض���ζ����͹�����жϣ�bc[i]=1,iff:��i��������͹���� 
void checkconvex(int vcount,POINT polygon[],bool bc[]) 
{ 
    int i,index=0; 
    POINT tp=polygon[0]; 
    for(i=1;i<vcount;i++) // Ѱ�ҵ�һ��͹���� 
    { 
        if(polygon[i].y<tp.y||(polygon[i].y == tp.y&&polygon[i].x<tp.x)) 
        { 
            tp=polygon[i]; 
            index=i; 
        } 
    } 
    int count=vcount-1; 
    bc[index]=1; 
    while(count) // �ж�͹���� 
    { 
        if(multiply(polygon[(index+1)%vcount],polygon[(index+2)%vcount],polygon[index])>=0 ) 
            bc[(index+1)%vcount]=1; 
        else 
            bc[(index+1)%vcount]=0; 
        index++; 
        count--; 
    } 
}
//3. �ж϶�����Ƿ�͹����� 9 
// ����ֵ�������polygon��͹�����ʱ������true  
bool isconvex(int vcount,POINT polygon[]) 
{ 
    bool bc[MAXV]; 
    checkconvex(vcount,polygon,bc); 
    for(int i=0;i<vcount;i++) // ��һ��鶥�㣬�Ƿ�ȫ����͹���� 
        if(!bc[i]) 
            return false; 
    return true; 
} 
//4. ��������� 9 
// ���ض�������(signed)�����붥�㰴��ʱ������ʱ��������ֵ�����򷵻ظ�ֵ 
double area_of_polygon(int vcount,POINT polygon[]) 
{ 
    int i; 
    double s; 
    if (vcount<3) 
        return 0; 
    s=polygon[0].y*(polygon[vcount-1].x-polygon[1].x); 
    for (i=1;i<vcount;i++) 
        s+=polygon[i].y*(polygon[(i-1)].x-polygon[(i+1)%vcount].x); 
    return s/2; 
} 
//5. �ж϶���ζ�������з��򣬷���һ 10 
// ������붥�㰴��ʱ�����У�����true 
bool isconterclock(int vcount,POINT polygon[]) 
{ 
    return area_of_polygon(vcount,polygon)>0; 
} 
//6. �ж϶���ζ�������з��򣬷����� 10 
// ��һ���ж϶���ζ������з���ķ���  
bool isccwize(int vcount,POINT polygon[]) 
{ 
    int i,index; 
    POINT a,b,v; 
    v=polygon[0]; 
    index=0; 
    for(i=1;i<vcount;i++) // �ҵ���������󶥵㣬�϶���͹���� 
    { 
        if(polygon[i].y<v.y||polygon[i].y == v.y && polygon[i].x<v.x) 
        { 
            index=i; 
        } 
    } 
    a=polygon[(index-1+vcount)%vcount]; // ����v��ǰһ���� 
    b=polygon[(index+1)%vcount]; // ����v�ĺ�һ���� 
    return multiply(v,b,a)>0; 
} 
/********************************************************************************************   
���߷��жϵ�q������polygon��λ�ù�ϵ��Ҫ��polygonΪ�򵥶���Σ�������ʱ������ 
   ������ڶ�����ڣ�   ����0 
   ������ڶ���α��ϣ� ����1 
   ������ڶ�����⣺  ����2 
*********************************************************************************************/ 
//7. ���߷��жϵ��Ƿ��ڶ������ 10 
int insidepolygon(int vcount,POINT Polygon[],POINT q) 
{ 
    int c=0,i,n; 
    LINESEG l1,l2; 
    bool bintersect_a,bonline1,bonline2,bonline3; 
    double r1,r2; 

    l1.s=q; 
    l1.e=q; 
    l1.e.x=double(INF); 
    n=vcount; 
    for (i=0;i<vcount;i++) 
    { 
        l2.s=Polygon[i]; 
        l2.e=Polygon[(i+1)%n]; 
        if(online(l2,q))
            return 1; // ������ڱ��ϣ�����1 
        if ( (bintersect_a=intersect_A(l1,l2))|| // �ཻ�Ҳ��ڶ˵� 
        ( (bonline1=online(l1,Polygon[(i+1)%n]))&& // �ڶ����˵��������� 
        ( (!(bonline2=online(l1,Polygon[(i+2)%n])))&& /* ǰһ���˵�ͺ�һ���˵����������� */ 
        ((r1=multiply(Polygon[i],Polygon[(i+1)%n],l1.s)*multiply(Polygon[(i+1)%n],Polygon[(i+2)%n],l1.s))>0) ||    
        (bonline3=online(l1,Polygon[(i+2)%n]))&&     /* ��һ������ˮƽ�ߣ�ǰһ���˵�ͺ�һ���˵�����������  */ 
            ((r2=multiply(Polygon[i],Polygon[(i+2)%n],l1.s)*multiply(Polygon[(i+2)%n], 
        Polygon[(i+3)%n],l1.s))>0) 
                ) 
            ) 
        ) c++; 
    } 
    if(c%2 == 1) 
        return 0; 
    else 
        return 2; 
} 
//8. �жϵ��Ƿ���͹������� 11 
//��q��͹�����polygon��ʱ������true��ע�⣺�����polygonһ��Ҫ��͹�����  
bool InsideConvexPolygon(int vcount,POINT polygon[],POINT q) // �����������Σ� 
{ 
    POINT p; 
    LINESEG l; 
    int i; 
    p.x=0;p.y=0; 
    for(i=0;i<vcount;i++) // Ѱ��һ���϶��ڶ����polygon�ڵĵ�p������ζ���ƽ��ֵ 
    { 
        p.x+=polygon[i].x; 
        p.y+=polygon[i].y; 
    } 
    p.x /= vcount; 
    p.y /= vcount; 

    for(i=0;i<vcount;i++) 
    { 
        l.s=polygon[i];l.e=polygon[(i+1)%vcount]; 
        if(multiply(p,l.e,l.s)*multiply(q,l.e,l.s)<0) /* ��p�͵�q�ڱ�l�����࣬˵����q�϶��ڶ������ */ 
        break; 
    } 
    return (i==vcount); 
} 
//9. Ѱ�ҵ㼯��graham�㷨 12 
/********************************************** 
Ѱ��͹����graham ɨ�跨 
PointSetΪ����ĵ㼯�� 
chΪ�����͹���ϵĵ㼯��������ʱ�뷽������; 
nΪPointSet�еĵ����Ŀ 
lenΪ�����͹���ϵĵ�ĸ��� 
**********************************************/ 
void Graham_scan(POINT PointSet[],POINT ch[],int n,int &len) 
{ 
    int i,j,k=0,top=2; 
    POINT tmp; 
    // ѡȡPointSet��y������С�ĵ�PointSet[k]����������ĵ��ж������ȡ����ߵ�һ�� 
    for(i=1;i<n;i++) 
        if ( PointSet[i].y<PointSet[k].y || (PointSet[i].y==PointSet[k].y) && (PointSet[i].x<PointSet[k].x) ) 
            k=i; 
    tmp=PointSet[0]; 
    PointSet[0]=PointSet[k]; 
    PointSet[k]=tmp; // ����PointSet��y������С�ĵ���PointSet[0] 
    for (i=1;i<n-1;i++) /* �Զ��㰴�����PointSet[0]�ļ��Ǵ�С����������򣬼�����ͬ�İ��վ���PointSet[0]�ӽ���Զ�������� */ 
    { 
        k=i; 
        for (j=i+1;j<n;j++) 
            if ( multiply(PointSet[j],PointSet[k],PointSet[0])>0 ||  // ���Ǹ�С    
                (multiply(PointSet[j],PointSet[k],PointSet[0])==0) && /* ������ȣ�������� */        
                dist(PointSet[0],PointSet[j])<dist(PointSet[0],PointSet[k])
               ) 
                k=j; 
        tmp=PointSet[i]; 
        PointSet[i]=PointSet[k]; 
        PointSet[k]=tmp; 
    } 
    ch[0]=PointSet[0]; 
    ch[1]=PointSet[1]; 
    ch[2]=PointSet[2]; 
    for (i=3;i<n;i++) 
    { 
        while (multiply(PointSet[i],ch[top],ch[top-1])>=0) 
            top--; 
        ch[++top]=PointSet[i]; 
    } 
    len=top+1; 
} 

/*********************************************************************************************  
    �ж��߶��Ƿ��ڼ򵥶������(ע�⣺����������͹����Σ�������㷨���Ի���) 
    ��Ҫ����һ���߶ε������˵㶼�ڶ�����ڣ� 
    ��Ҫ���������߶κͶ���ε����б߶����ڽ��� 
    ��;��   1. �ж������Ƿ��ڼ򵥶������ 
            2. �жϼ򵥶�����Ƿ�����һ���򵥶������ 
**********************************************************************************************/ 
//11.�ж��߶��Ƿ��ڶ������ 14 
bool LinesegInsidePolygon(int vcount,POINT polygon[],LINESEG l) 
{ 
    // �ж��߶�l�Ķ˵��Ƿ񲻶��ڶ������ 
    if(!insidepolygon(vcount,polygon,l.s)||!insidepolygon(vcount,polygon,l.e)) 
        return false; 
    int top=0,i,j; 
    POINT PointSet[MAXV],tmp; 
    LINESEG s; 

    for(i=0;i<vcount;i++) 
    { 
        s.s=polygon[i]; 
        s.e=polygon[(i+1)%vcount]; 
        if(online(s,l.s)) //�߶�l����ʼ�˵����߶�s�� 
            PointSet[top++]=l.s; 
        else if(online(s,l.e)) //�߶�l����ֹ�˵����߶�s�� 
            PointSet[top++]=l.e; 
        else 
        { 
            if(online(l,s.s)) //�߶�s����ʼ�˵����߶�l�� 
                PointSet[top++]=s.s; 
            else if(online(l,s.e)) // �߶�s����ֹ�˵����߶�l�� 
                PointSet[top++]=s.e; 
            else 
            { 
                if(intersect(l,s)) // ���ʱ������ཻ���϶����ڽ�������false 
                return false; 
            } 
        } 
    } 

    for(i=0;i<top-1;i++) /* ð������x����С������ǰ�棻x������ͬ�ߣ�y����С������ǰ�� */ 
    { 
        for(j=i+1;j<top;j++) 
        { 
            if( PointSet[i].x>PointSet[j].x || fabs(PointSet[i].x-PointSet[j].x)<EP && PointSet[i].y>PointSet[j].y ) 
            { 
                tmp=PointSet[i]; 
                PointSet[i]=PointSet[j]; 
                PointSet[j]=tmp; 
            } 
        } 
    } 

    for(i=0;i<top-1;i++) 
    { 
        tmp.x=(PointSet[i].x+PointSet[i+1].x)/2; //�õ��������ڽ�����е� 
        tmp.y=(PointSet[i].y+PointSet[i+1].y)/2; 
        if(!insidepolygon(vcount,polygon,tmp)) 
            return false; 
    } 
    return true; 
} 
//12.��򵥶���ε����� 15 
/*********************************************************************************************  
������򵥶����polygon������ 
��Ҫ�������漸�������� 
    void AddPosPart(); �����ұ��������� 
    void AddNegPart(); ��������������� 
    void AddRegion(); ����������� 
��ʹ�øó���ʱ�������xtr,ytr,wtr,xtl,ytl,wtl���ȫ�ֱ����Ϳ���ʹ��Щ��������ʽ�õ�����,
��Ҫע�⺯���������͵���Ҫ����Ӧ�仯 
**********************************************************************************************/ 
void AddPosPart(double x, double y, double w, double &xtr, double &ytr, double &wtr) 
{ 
    if (abs(wtr + w)<1e-10 ) return; // detect zero regions 
    xtr = ( wtr*xtr + w*x ) / ( wtr + w ); 
    ytr = ( wtr*ytr + w*y ) / ( wtr + w ); 
    wtr = w + wtr; 
    return; 
} 
//13.��͹����ε����� 17 
// ��͹����ε�����,Ҫ���������ΰ���ʱ������ 
POINT gravitycenter(int vcount,POINT polygon[]) 
{ 
    POINT tp; 
    double x,y,s,x0,y0,cs,k; 
    x=0;y=0;s=0; 
    for(int i=1;i<vcount-1;i++) 
    { 
        x0=(polygon[0].x+polygon[i].x+polygon[i+1].x)/3; 
        y0=(polygon[0].y+polygon[i].y+polygon[i+1].y)/3; //��ǰ�����ε����� 
        cs=multiply(polygon[i],polygon[i+1],polygon[0])/2; 
        //�������������ֱ�����øù�ʽ��� 
        if(abs(s)<1e-20) 
        { 
            x=x0;y=y0;s+=cs;continue; 
        } 
        k=cs/s; //��������� 
        x=(x+k*x0)/(1+k); 
        y=(y+k*y0)/(1+k); 
        s += cs; 
    } 
    tp.x=x; 
    tp.y=y; 
    return tp; 
} 

/************************************************
����һ�򵥶���Σ��ҳ�һ���϶��ڸö�����ڵĵ� 
����1 ��ÿ�������������һ��͹���� 
����2 ��������>=4�ļ򵥶����������һ���Խ��� 
����  �� x���������С�ĵ�϶���͹���� 
    y���������С�ĵ�϶���͹����            
************************************************/ 
//14.��϶��ڸ���������ڵ�һ���� 17 
POINT a_point_insidepoly(int vcount,POINT polygon[]) 
{ 
    POINT v,a,b,r; 
    int i,index; 
    v=polygon[0]; 
    index=0; 
    for(i=1;i<vcount;i++) //Ѱ��һ��͹���� 
    { 
        if(polygon[i].y<v.y) 
        { 
            v=polygon[i]; 
            index=i; 
        } 
    } 
    a=polygon[(index-1+vcount)%vcount]; //�õ�v��ǰһ������ 
    b=polygon[(index+1)%vcount]; //�õ�v�ĺ�һ������ 
    POINT tri[3],q; 
    tri[0]=a;tri[1]=v;tri[2]=b; 
    double md=INF; 
    int in1=index; 
    bool bin=false; 
    for(i=0;i<vcount;i++) //Ѱ����������avb�����붥��v����Ķ���q 
    { 
        if(i == index)continue; 
        if(i == (index-1+vcount)%vcount)continue; 
        if(i == (index+1)%vcount)continue; 
        if(!InsideConvexPolygon(3,tri,polygon[i]))continue; 
        bin=true; 
        if(dist(v,polygon[i])<md) 
        { 
            q=polygon[i]; 
            md=dist(v,q); 
        } 
    } 
    if(!bin) //û�ж�����������avb�ڣ������߶�ab�е� 
    { 
        r.x=(a.x+b.x)/2; 
        r.y=(a.y+b.y)/2; 
        return r; 
    } 
    r.x=(v.x+q.x)/2; //�����߶�vq���е� 
    r.y=(v.y+q.y)/2; 
    return r; 
} 
/***********************************************************************************************
��Ӷ������һ��p������һ���򵥶���ε�����,������ڷ����е�,����rp�������е�,lp�����е� 
ע�⣺p��һ��Ҫ�ڶ������ ,���붥����������ʱ������ 
ԭ ��  ������ڶ�����ڿ϶�������;͹�������Ψһ�������е�,������ξͿ����ж����������е�; 
        ���polygon��͹����Σ��е�ֻ������ֻҪ�ҵ��Ϳ���,���Ի�����㷨 
        ����ǰ�����λ���һ���㷨�������:���󰼶���ε�͹��,Ȼ����͹�������� 
/***********************************************************************************************/ 
//15.��Ӷ������һ��������ö���ε����� 18 
void pointtangentpoly(int vcount,POINT polygon[],POINT p,POINT &rp,POINT &lp) 
{ 
    LINESEG ep,en; 
    bool blp,bln; 
    rp=polygon[0]; 
    lp=polygon[0]; 
    for(int i=1;i<vcount;i++) 
    { 
        ep.s=polygon[(i+vcount-1)%vcount]; 
        ep.e=polygon[i]; 
        en.s=polygon[i]; 
        en.e=polygon[(i+1)%vcount]; 
        blp=multiply(ep.e,p,ep.s)>=0;                // p is to the left of pre edge 
        bln=multiply(en.e,p,en.s)>=0;                // p is to the left of next edge 
        if(!blp&&bln) 
        { 
            if(multiply(polygon[i],rp,p)>0)           // polygon[i] is above rp 
            rp=polygon[i]; 
        } 
        if(blp&&!bln) 
        { 
            if(multiply(lp,polygon[i],p)>0)           // polygon[i] is below lp 
            lp=polygon[i]; 
        } 
    } 
    return ; 
} 
//16.�ж϶���εĺ��Ƿ���� 19 
// ��������polygon�ĺ˴��ڣ�����true�����غ��ϵ�һ��p.���㰴��ʱ�뷽������  
bool core_exist(int vcount,POINT polygon[],POINT &p) 
{ 
    int i,j,k; 
    LINESEG l; 
    LINE lineset[MAXV]; 
    for(i=0;i<vcount;i++) 
    { 
        lineset[i]=makeline(polygon[i],polygon[(i+1)%vcount]); 
    } 
    for(i=0;i<vcount;i++) 
    { 
        for(j=0;j<vcount;j++) 
        { 
            if(i == j)continue; 
            if(lineintersect(lineset[i],lineset[j],p)) 
            { 
                for(k=0;k<vcount;k++) 
                { 
                    l.s=polygon[k]; 
                    l.e=polygon[(k+1)%vcount]; 
                    if(multiply(p,l.e,l.s)>0)      
                    //����ζ��㰴��ʱ�뷽�����У��˿϶���ÿ���ߵ�������� 
                    break; 
                } 
                if(k == vcount)             //�ҵ���һ�����ϵĵ� 
                break; 
            } 
        } 
        if(j<vcount) break; 
    } 
    if(i<vcount) 
        return true; 
    else 
        return false; 
} 
/*************************\ 
*                        * 
* Բ�Ļ�������           * 
*                        * 
\*************************/ 
/******************************************************************************
����ֵ   �� ��p��Բ��(�����߽�)ʱ������true 
��;  �� ��ΪԲΪ͹���������жϵ㼯�����ߣ�������Ƿ���Բ��ʱ��
    ֻ��Ҫ��һ�жϵ��Ƿ���Բ�ڼ��ɡ� 
*******************************************************************************/ 
//1 .���Ƿ���Բ�� 20 
bool point_in_circle(POINT o,double r,POINT p) 
{ 
    double d2=(p.x-o.x)*(p.x-o.x)+(p.y-o.y)*(p.y-o.y); 
    double r2=r*r; 
    return d2<r2||abs(d2-r2)<EP; 
} 
/******************************************************************************
�� ; ���󲻹��ߵ�����ȷ��һ��Բ 
�� �� ��������p1,p2,p3 
����ֵ   ��������㹲�ߣ�����false����֮������true��Բ����q���أ��뾶��r���� 
*******************************************************************************/ 
//2 .�󲻹��ߵ�������ȷ����Բ 21 
bool cocircle(POINT p1,POINT p2,POINT p3,POINT &q,double &r) 
{ 
    double x12=p2.x-p1.x; 
    double y12=p2.y-p1.y; 
    double x13=p3.x-p1.x; 
    double y13=p3.y-p1.y; 
    double z2=x12*(p1.x+p2.x)+y12*(p1.y+p2.y); 
    double z3=x13*(p1.x+p3.x)+y13*(p1.y+p3.y); 
    double d=2.0*(x12*(p3.y-p2.y)-y12*(p3.x-p2.x)); 
    if(abs(d)<EP) //���ߣ�Բ������ 
        return false; 
    q.x=(y13*z2-y12*z3)/d; 
    q.y=(x12*z3-x13*z2)/d; 
    r=dist(p1,q); 
    return true; 
} 
int line_circle(LINE l,POINT o,double r,POINT &p1,POINT &p2) 
{ 
    return true; 
} 

/**************************\ 
*                         * 
* ���εĻ�������          * 
*                         * 
\**************************/ 
/* 
˵������Ϊ���ε������ԣ������㷨���Ի��� 
1.�жϾ����Ƿ������ 
ֻҪ�жϸõ�ĺ�������������Ƿ���ھ��ε����ұߺ����±�֮�䡣 
2.�ж��߶Ρ����ߡ�������Ƿ��ھ����� 
��Ϊ�����Ǹ�͹��������ֻҪ�ж����ж˵��Ƿ��ھ����оͿ����ˡ� 
3.�ж�Բ�Ƿ��ھ����� 
Բ�ھ����еĳ�Ҫ�����ǣ�Բ���ھ�������Բ�İ뾶С�ڵ���Բ�ĵ������ıߵľ������Сֵ�� 
*/ 
// ��֪���ε���������(a,b,c)��������ĸ�����d������. ע�⣺��֪�������������������� 
//1.��֪�����������꣬���4������ 22 
POINT rect4th(POINT a,POINT b,POINT c) 
{ 
    POINT d; 
    if(abs(dotmultiply(a,b,c))<EP) // ˵��c����ֱ�ǹսǴ� 
    { 
        d.x=a.x+b.x-c.x; 
        d.y=a.y+b.y-c.y; 
    } 
    if(abs(dotmultiply(a,c,b))<EP) // ˵��b����ֱ�ǹսǴ� 
    { 
        d.x=a.x+c.x-b.x; 
        d.y=a.y+c.y-b.x; 
    } 
    if(abs(dotmultiply(c,b,a))<EP) // ˵��a����ֱ�ǹսǴ� 
    { 
        d.x=c.x+b.x-a.x; 
        d.y=c.y+b.y-a.y; 
    } 
    return d; 
} 

const double eps = 1e-5;

POINT p[8];

//�ж��Ƿ���
bool CheckLine(POINT a, POINT b, POINT c, POINT d)
{
	if(abs(multiply(a, b, c)) < eps)
		return false;
	if(abs(multiply(a, b, d)) < eps)
		return false;
	if(abs(multiply(a, c, d)) < eps)
		return false;
	if(abs(multiply(b, c, d)) < eps)
		return false;
	return true;
}

void Check()
{
	POINT a, b, c, d, dd;
	a = p[0], b = p[1], c=p[2], d=p[3], dd=p[3];
	d.x = -1000000;
	d.y = -1000000;
	if(!CheckLine(a, b, c, dd))
		return;
	
	if(abs(dotmultiply(a,b,c))<EP) // ˵��c����ֱ�ǹսǴ� 
    { 
		if(abs(dist(a, c)-dist(b, c)) > eps)
			return;
        d.x=a.x+b.x-c.x; 
        d.y=a.y+b.y-c.y; 
    } 
    if(abs(dotmultiply(a,c,b))<EP) // ˵��b����ֱ�ǹսǴ� 
    { 
		if(abs(dist(a, b)-dist(c, b)) > eps)
			return;
        d.x=a.x+c.x-b.x; 
        d.y=a.y+c.y-b.y; 
    } 
    if(abs(dotmultiply(c,b,a))<EP) // ˵��a����ֱ�ǹսǴ� 
    { 
		if(abs(dist(a, b)-dist(a, c)) > eps)
			return;
        d.x=c.x+b.x-a.x; 
        d.y=c.y+b.y-a.y; 
    } 
	
	if(!equal_point(d, dd))
		return;
	
	a = p[4], b = p[5], c=p[6], d=p[7], dd=p[7];
	d.x = -1000000;
	d.y = -1000000;
	if(!CheckLine(a, b, c, dd))
		return;
	if(abs(dotmultiply(a,b,c))<EP) // ˵��c����ֱ�ǹսǴ� 
    { 
        d.x=a.x+b.x-c.x; 
        d.y=a.y+b.y-c.y; 
    } 
    if(abs(dotmultiply(a,c,b))<EP) // ˵��b����ֱ�ǹսǴ� 
    { 
        d.x=a.x+c.x-b.x; 
        d.y=a.y+c.y-b.y; 
    } 
    if(abs(dotmultiply(c,b,a))<EP) // ˵��a����ֱ�ǹսǴ� 
    { 
        d.x=c.x+b.x-a.x; 
        d.y=c.y+b.y-a.y; 
    } 
	if(!equal_point(d, dd))
		return;
	printf("YES\n");
	for(int i = 0; i<8; ++i){
		printf("%d", p[i].seq);
		if(i % 4 == 3)
			printf("\n");
		else
			printf(" ");
	}
	exit(0);
	
}

int main()
{
	POINT a[8];
	for(int i = 0; i<8; ++i){
		scanf("%lf%lf", &a[i].x, &a[i].y);
		a[i].seq = i+1;
	}
	for(int i = 0; i<8; ++i){
		for(int j = i+1; j<8; ++j){
			for(int k = j+1; k<8; ++k){
				for(int t = k+1; t<8; ++t){
					int kk = 0;
					for(int now = 4; now<8; ++now){
						while(true){
							if(kk != i && kk != j && kk != k && kk != t){
								p[now] = a[kk];
								kk++;
								break;
							}else{
								kk++;
							}
						}
					}
					p[0] = a[i];
					p[1] = a[j];
					p[2] = a[k];
					p[3] = a[t];
					Check();
				}
			}
		}
	}
	printf("NO");
	return 0;
}


