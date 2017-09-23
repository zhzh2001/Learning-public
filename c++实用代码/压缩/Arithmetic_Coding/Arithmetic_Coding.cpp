// Arithmetic_Coding.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream >
using  namespace  std; 

#define     M  100
#define     N  4
#define     DELTA (0.000000000001)

#define		NUM 2
#define		ZERO 0.000001

//����interger��decimal�����ǽ�ʮ����ת��Ϊ������
void integer(int n)
{
	if(n>0)
	{
		integer(n/NUM);
		//cout<<n%NUM;
		printf("%d",n%NUM);
	}
}

void decimal(double m)
{
	if(m>ZERO)
	{
		m=m*NUM;
		printf("%d",(long)m);
		decimal(m-(long)m);
	}
}

class CAC
{
    int m_iCount,m_iLength, m_iL;//��Դ�����������źų���
    char m_cSymbol[N];
    long double m_fProb[N];
    char m_cCode[M];
    long double m_fHigh,m_fLow;//����ʱ������ʵ��������м����

public:
    CAC();//�����ṹ��
    void encode();
    void decode();
    ~CAC(){}//�����ṹ��
};

CAC::CAC()
{
    m_fHigh = 0;
    m_fLow = 0;
    
	//�趨�ĸ���Դ����a,b,c,d
    m_iCount = 4;
    m_cSymbol[0] = 'a';
    m_cSymbol[1] = 'b';
    m_cSymbol[2] = 'c';
    m_cSymbol[3] = 'd';
   
	//�趨��Դ���Ÿ���
    m_fProb[0] = 0.1;
    m_fProb[1] = 0.2;
    m_fProb[2] = 0.4;
    m_fProb[3] = 0.3;
    
	//�趨�������ԪΪacbdbcab,��8���ַ����ڴ˶�����б�������
    m_iLength = 8;
    m_cCode[0] = 'a';
    m_cCode[1] = 'c';
    m_cCode[2] = 'b';
    m_cCode[3] = 'd';
    m_cCode[4] = 'b';
    m_cCode[5] = 'c';
    m_cCode[6] = 'a';
    m_cCode[7] = 'b';
}

void CAC::encode()
{
    int  i,j=0;
    long double p = 1.0, d;

    cout << "begin to encode..." <<endl;

    //�ҵ���һ����Ԫ���ĸ��ַ�
    for(i = 0; i < m_iCount; i++)
    {
        if(m_cCode[0] == m_cSymbol[i])
            break;
    }

    //�ҵ���һ���ַ��ĸ�����������
    while(j < i)
    {
        m_fLow += m_fProb[j++];
    }

    d = m_fProb[j];//�������䳤�ȸ�ֵ��d

    m_fHigh = m_fLow + d;//�趨��һ���ַ�������������
    
    //����������㷨���£�
    for(i = 1; i < m_iLength; i++)
    {
        for(j = 0; j < m_iCount; j++)
        {
            if(m_cCode[i] == m_cSymbol[j])
            {
                if(j == 0)//���ź�Ϊ�涨��Ԫ�ĵ�һ������Ӧ�ĸ��������޼�������������
                {
                    m_fHigh = m_fLow + m_fProb[j]*d;
                    d *= m_fProb[j];
                }
                else //���źŲ��ǹ涨��Ԫ�ĵ�һ��������Ӧ�ĸ����������㷨����
                {
                    double  chance_l=0.0;
                    for(int k = 0; k <= j-1; k++)
                        chance_l += m_fProb[k];
                    m_fLow = m_fLow + d*chance_l;
                    m_fHigh = m_fLow + d*(chance_l + m_fProb[j]);
                    d *= m_fProb[j];
                }
            }
            else
                continue;
        }
    }
    
#if 1
	//�����������źŵĸ���ֵ�������
    for (i = 0; i < m_iLength; i++)
    {
        for(j = 0; j < m_iCount; j++)
        {
            if (m_cCode[i] == m_cSymbol[j])
            {
                p *= m_fProb[j];
            }
        }
    }
#endif
   
	//��ʮ����С��ת��Ϊ������С�����,�����ñ���
	long n;
	n=(long)m_fLow;
	integer(n);
	decimal(m_fLow-n);
	cout<<"\n";

    //����źŸ�������������������ֵ
    cout<<"Arithmetic coding: "<<m_fLow<<endl;
	cout<<"\n";

}

//ȡ�������ø�������ֵ������

void CAC::decode()
{
    int i;
    long double dd, dc;

    cout << "begin to decode..." <<endl;

    dd = m_fLow;

    while(1)
    {
        long double xlow = 0;

        if (dd < DELTA)
            break;

		//�ҵ�����ֵ������Ӧ��Ԫ�ĸ�������
        dc = 0;
        for (i = 0; i < N; i++)
        {
            dc += m_fProb[i];
            if (dd < dc)
                break;
            xlow += m_fProb[i];
        }
		//����Ѱ����һ���ַ����ڸ�������
        cout << m_cSymbol[i];
        dd -= xlow;
        dd /= m_fProb[i];
    }
}

int  main()
{  
    CAC  a;
    a.encode();
    a.decode();

    return  0;
}