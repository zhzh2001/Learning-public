const maxn=20010; maxm=1000010;
type gtp=record y,d,c,op,next:longint; end;
//========================================================
var n,m,tot,st,ed,ans:longint;
    g:array[0..maxm] of gtp;
    first,now,dis:array[0..maxn] of longint;
    v:array[0..maxn] of boolean;
//========================================================
function min(a,b:longint):longint;
begin
 if a>b then exit(b) else exit(a);
end;
//========================================================
procedure add(x,y,d,c,t:longint); {��߱�}
begin
 inc(tot);
 g[tot].y:=y; g[tot].d:=d; g[tot].c:=c;
 g[tot].op:=tot+t; g[tot].next:=first[x]; first[x]:=tot;
end;
//========================================================
procedure init;
var i,x,y,d,c:longint;
begin
 fillchar(first,sizeof(first),0);
 readln(n,m); tot:=0; st:=1; ed:=n; ans:=0;
 for i:=1 to m do
 begin
  readln(x,y,d,c); {x��y�㣬����������}
  add(x,y,d,c,1); add(y,x,0,-c,-1); {�����򶼴�}
 end;
end;
//========================================================
function aug(x,flow:longint):longint; {Ѱ������·}
var y,t,tmp:longint;
begin
 if x=ed then {�ҵ�����·����������}
 begin
  inc(ans,flow*dis[st]);
  exit(flow);
 end;
 t:=now[x]; v[x]:=true;
 while t<>0 do
 begin
  y:=g[t].y;
  if (g[t].d>0)and(not v[y])and(dis[x]=dis[y]+g[t].c) then {����������δ�����ʣ�������һ���Ż����������Ź�ϵ}
  begin
   tmp:=aug(y,min(g[t].d,flow)); {��������}
   if tmp>0 then {������ɹ�}
   begin
    dec(g[t].d,tmp); inc(g[g[t].op].d,tmp); {��������ֵ}
    now[x]:=t; {���µ�ǰ��}
    exit(tmp);
   end;
  end;
  t:=g[t].next;
 end;
 now[x]:=0; {С�Ż�}
 exit(0);
end;
//========================================================
function modlabel:boolean; {�޸ľ�����}
var tmp,y,i,t:longint;
begin
 tmp:=maxlongint;
 for i:=1 to n do
 if v[i] then {��ĳ��Ϊtrue����������Ѿ����ϸ�}
 begin
  t:=first[i];
  while t<>0 do
  begin
   y:=g[t].y;
   if (g[t].d>0)and(not v[y])and(dis[y]+g[t].c-dis[i]<tmp) then tmp:=dis[y]+g[t].c-dis[i]; {ȡ��Сֵ}
   t:=g[t].next;
  end;
 end;
 if tmp=maxlongint then exit(true); {�޷��޸�������}
 for i:=1 to n do {�����޸������޸�������}
 if v[i] then
 begin
  inc(dis[i],tmp);
  v[i]:=false;
 end;
 exit(false);
end;
//========================================================
procedure main;
var i:longint;
begin
 fillchar(dis,sizeof(dis),0);
 repeat
  for i:=1 to n do now[i]:=first[i];
  while aug(st,maxlongint)>0 do fillchar(v,sizeof(v),false); {������������������}
 until modlabel; {ֱ���޷��޸�������}
 writeln(ans);
end;
//========================================================
begin
 assign(input,'costflow.in'); reset(input);
 assign(output,'costflow.out'); rewrite(output);
 init;
 main;
 close(input); close(output);
end.
