program ditch; //��USACO��ditchΪ��
var
c:array[0..3011,0..3011] of cardinal; //�ڽӾ���
h,vh:array[0..3011] of cardinal;
n,augc,rd1,rd2,m,i:cardinal; //augcΪ����·����
flow:cardinal=0;
found:boolean; //��¼�Ƿ��Ѵ���
procedure aug(const m:cardinal);
var
i,augco,minh:cardinal;
begin
minh:=n-1;
augco:=augc;
if m=n then begin
found:=true;
inc(flow,augc);
exit;
end;
for i:=1 to n do
if c[m,i]>0 then begin
if h[i]+1=h[m] then begin
if c[m,i]<augc then augc:=c[m,i];
aug(i);
if h[1]>=n then exit; //GAP
if found then break;
augc:=augco;
end;
if h[i]<minh then minh:=h[i];
end;
if not found then begin //�ر��
dec(vh[h[m]]); //GAP
if vh[h[m]]=0 then h[1]:=n; //GAP
h[m]:=minh+1;
inc(vh[h[m]]); //GAP
end else begin //�޸Ĳ���
dec(c[m,i],augc);
inc(c[i,m],augc);
end;
end;
begin
assign(input,'ditch.in');
assign(output,'ditch.out');
reset(input);
rewrite(output);
readln(m,n);
fillchar(c,sizeof(c),0);
for i:=1 to m do begin
readln(rd1,rd2,augc);
inc(c[rd1,rd2],augc);
end;
fillchar(h,sizeof(h),0);
fillchar(vh,sizeof(vh),0);
vh[0]:=n;
while h[1]<n do begin
augc:=$FFFFFFFF;
found:=false;
aug(1);
end;
writeln(flow);
close(input);
close(output);
end.