Program Cover;
Const Maxn=10000;  �������弯�����������10000���������
Type Blocks=Record
              x1,y1,z1,x2,y2,z2:Longint; �����������6�����
            End;
Var i,j,k,m,n,x,y,z,r,tot:longint;
    Cubic:array[1..Maxn] of Blocks;
    Now:Blocks;
Procedure Init;  ���������ݲ�Ԥ����Ĺ��̣�
Begin
  assign(input,'cover.in');
  reset(input);
  assign(output,'cover.out');
  rewrite(output);
  readln(n);
  Fillchar(Cubic,sizeof(Cubic),0);
  tot:=0;
End;
Function Max(a,b:Longint):Longint; ���Ƚ������������ؽϴ��ߵĺ�����
Begin
  if a>b then Max:=a
  else Max:=b;
End;
Function Min(a,b:Longint):Longint; ���Ƚ������������ؽ�С�ߵĺ�����
Begin
  if a<b then Min:=a
  else Min:=b;
End;
Procedure Add(x1,y1,z1,x2,y2,z2:Longint);������������Ĺ��̣�
Begin
  inc(tot);
  Cubic[tot].x1:=x1; Cubic[tot].y1:=y1; Cubic[tot].z1:=z1;
  Cubic[tot].x2:=x2; Cubic[tot].y2:=y2; Cubic[tot].z2:=z2;
End;
Procedure Cut(x1,y1,z1,x2,y2,z2,Direction:Longint);���и��
Var k1,k2:longint;
Begin
  Case Direction of
    1:Begin ������x�����У�
        k1:=Max(x1,Now.x1);  �������߶�[x1,x2],[Now.x1,Now.x2]��
        k2:=Min(x2,Now.x2);  ���Ľ���[k1,k2]��
        if x1<k1 then Add(x1,y1,z1,k1,y2,z2);
        if k2<x2 then Add(k2,y1,z1,x2,y2,z2);
        Cut(k1,y1,z1,k2,y2,z2,Direction+1); ������y������и��
      End;
    2:Begin��Ȼ����y�����У�
        k1:=Max(y1,Now.y1);
        k2:=Min(y2,Now.y2);
        if y1<k1 then Add(x1,y1,z1,x2,k1,z2);
        if k2<y2 then Add(x1,k2,z1,x2,y2,z2);
        Cut(x1,k1,z1,x2,k2,z2,Direction+1); ������z������и��
      End;
    3:Begin��������z�����У�
        k1:=Max(z1,Now.z1);
        k2:=Min(z2,Now.z2);
        if z1<k1 then Add(x1,y1,z1,x2,y2,k1);
        if k2<z2 then Add(x1,y1,k2,x2,y2,z2);
      End;
  End;
End;
Function Cross(x1,x2,x3,x4:longint):boolean; ���ж��߶�[x1,x2]��[x3,x4]�Ƿ��ཻ��
Begin
  if (x1>=x4)or(x3>=x2) then Cross:=false
  else Cross:=true;
End;
Procedure Caculate;  ���������������������ͣ�
Var i,Volume,k:longint;
Begin
  Volume:=0;
  for i:=1 to tot do
  begin
    k:=(Cubic[i].x2-Cubic[i].x1)*
	(Cubic[i].y2-Cubic[i].y1)*
	(Cubic[i].z2-Cubic[i].z1);
    Inc(Volume,k);
  end;
  Writeln(Volume);
End;

Procedure Main;  �������̣�
Var  i,j,tot1:Longint;
Begin
  for i:=1 to n do
  begin
    readln(x,y,z,r);
    Now.x1:=x-r;   Now.y1:=y-r;   Now.z1:=z-r;
    Now.x2:=x+r;   Now.y2:=y+r;   Now.z2:=z+r;
    j:=0;
    tot1:=tot; �����浱ǰ���е�βָ�룬��tot1֮��������嶼�����и�����ģ�
    While j<tot1 do
    Begin
      inc(j);
      if (Cross(Cubic[j].x1,Cubic[j].x2,Now.x1,Now.x2))
      and(Cross(Cubic[j].y1,Cubic[j].y2,Now.y1,Now.y2))
      and(Cross(Cubic[j].z1,Cubic[j].z2,Now.z1,Now.z2)) then  �����������巢���ص���������и��
      Begin
        Cut(Cubic[j].x1,Cubic[j].y1,Cubic[j].z1,
            Cubic[j].x2,Cubic[j].y2,Cubic[j].z2,1);
        Cubic[j]:=Cubic[tot1];
        Cubic[tot1]:=Cubic[tot];
        dec(tot);
        dec(tot1);
        dec(j);
      End;
    End;
    Add(Now.x1,Now.y1,Now.z1,Now.x2,Now.y2,Now.z2);���������Now��
  end;
  Caculate;
  Close(output);
End;

Begin
  Init;
  Main;
End.
