#include "graphics.h"
int main() 
{ int gdrive=DETECT,gmode;/*������������:ͼ��������ͼ��ģʽ*/
  initgraph(&gdrive,&gmode,"");/*��ʼ��ͼ��ģʽ,���������������·��*/
  registerbgidriver(EGAVGA_driver);/*���������ע��ͼ��ģʽ����������ͼ�����г���*/
  bar(x1,y1,x2,y2);/*������*/
  circle(x1,y1,r);/*��Բ*/
  getch();
  closegraph();/*�ر�ͼ��ģʽ*/
}
