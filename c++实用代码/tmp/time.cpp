#include <time.h>
#include <stdio.h>
#include<cstdlib>
clock_t start,finish;
int a,b;
int main()
{
   start=clock();
   a=10;b=2000000000;
    __asm
    (
        "mov _b,%ecx;"   //ʵ�����
"testBegin:;"
        "mov _a,%eax;"
        "mov _a,%ebx;"
        "cdq;"
//�������ʵ�����
        "dec %ecx;"
        "jz testEnd;"
        "jmp testBegin;"
"testEnd:;"
    );
    finish=clock();
    printf("%.3lf\n",double(finish-start)/CLOCKS_PER_SEC); 
    system("pause");
    return 0;
}
