{$inline on}
program CQF_SBT;
const maxn=2000000;
var key,s,left,right,a,b:array[0..maxn] of longint;
tt,q:longint;

procedure init;
begin
readln(q);
for q:=1 to q do
readln(a[q],b[q]);
end;

procedure work;
var t,k:longint;

procedure right_rotate(var t:longint);inline;{��������}
begin
k:=left[t];
left[t]:=right[k];
right[k]:=t;
s[k]:=s[t];
s[t]:=s[left[t]]+s[right[t]]+1;
t:=k;
end;
procedure left_rotate(var t:longint);inline;{��������}
begin
k:=right[t];
right[t]:=left[k];
left[k]:=t;
s[k]:=s[t];
s[t]:=s[left[t]]+s[right[t]]+1;
t:=k;
end;

procedure maintain(var t:longint;flag:boolean);inline;{����Ҫ��ά������}
begin
if flag=false then{�����������뵼�µĲ�ƽ��}
if s[left[left[t]]]>s[right[t]] then{������������������������}
right_rotate(t)
else
if s[right[left[t]]]>s[right[t]] then begin{������������������������}
left_rotate(left[t]);
right_rotate(t);
end
else
exit{��ǰ��ƽ��ģ��˳�}
else
if s[right[right[t]]]>s[left[t]] then{������������������������}
left_rotate(t)
else
if s[left[right[t]]]>s[left[t]] then begin{������������������������}
right_rotate(right[t]);
left_rotate(t);
end
else
exit;
maintain(left[t],false);{����������ҿ����Լ�����һ�£���ʵ��ͼһ�²��򵥷����Ϳ��Եó�������}
maintain(right[t],true);
maintain(t,true);{ά������ƽ��}
maintain(t,false);
end;

procedure insert(var t,v:longint);inline;{�������}
begin
if t=0 then begin{�����ǰ��Ϊ����ô����}
inc(tt);
t:=tt;
key[t]:=v;
s[t]:=1;
left[t]:=0;
right[t]:=0;
end
else begin{��ǰ�㲻Ϊ��}
inc(s[t]);{�������}
if v<key[t] then
insert(left[t],v)
else
insert(right[t],v);
maintain(t,v>=key[t]);{ά��ע�⣬flag=TRUE��ά��������������ά������������������}
end;
end;
function delete(var t:longint;v:longint):longint;inline;{ɾ������}
begin
dec(s[t]);{����ǰ���size��С��Ҫɾ��Ԫ��}
if (v=key[t])or(v<key[t])and(left[t]=0)or(v>key[t])and(right[t]=0) then begin{�����ǰ����Ҫɾ����}
delete:=key[t];{��¼ɾ���ĵ���ʲô}
if (left[t]=0)or(right[t]=0) then{�������������һ���ǿյ�}
t:=left[t]+right[t]{�����е��ǿ÷ǿ�����ʾΪt}
else
key[t]:=delete(left[t],key[t]+1){ɾ�������������ģ�Ȼ����������};
end
else
if v<key[t] then{�ֱ����������ɾ����������ɾ}
delete:=delete(left[t],v)
else
delete:=delete(right[t],v);
end;

function find(var t,v:longint):boolean;inline;{���Ҳ���}
begin
if t=0 then
exit(false);
if v<key[t] then
find:=find(left[t],v)
else
find:=(key[t]=v)or find(right[t],v);
end;
function rank(var t,v:longint):longint;inline;{��Ԫ�ص���}
begin
if t=0 then
exit(1);
if v<=key[t] then
rank:=rank(left[t],v)
else
rank:=s[left[t]]+1+rank(right[t],v);
end;
function select(var t:longint;k:longint):longint;inline;{�����k��}
begin
if k=s[left[t]]+1 then
exit(key[t]);
if k<=s[left[t]] then
select:=select(left[t],k)
else
select:=select(right[t],k-1-s[left[t]]);
end;
function pred(var t,v:longint):longint;inline;{��ǰ��}
begin
if t=0 then
exit(v);
if v<=key[t] then
pred:=pred(left[t],v)
else begin
pred:=pred(right[t],v);
if pred=v then
pred:=key[t];
end;
end;
function succ(var t,v:longint):longint;inline;{�Һ��}
begin
if t=0 then
exit(v);
if key[t]<=v then
succ:=succ(right[t],v)
else begin
succ:=succ(left[t],v);
if succ=v then
succ:=key[t];
end;
end;

begin{work}
tt:=0;
t:=0;
s[0]:=0;
for q:=1 to q do
case a[q] of
1:insert(t,b[q]);
2:delete(t,b[q]);
3:writeln(find(t,b[q]));
4:writeln(rank(t,b[q]));
5:writeln(select(t,b[q]));
6:writeln(pred(t,b[q]));
7:writeln(succ(t,b[q]));
end;
end;

begin
assign(input,'bst.in');
assign(output,'bst.out');
reset(input);
rewrite(output);
init;
work;
close(input);
close(output);
end.


