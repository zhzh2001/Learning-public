{
ID:yudingl2
PROG:ditch
LANG:PASCAL
}
type
	btp=record
		x,y,f,op,tot,next:longint;
	 end;

var
	n,m,tot:longint;
	edge:array[0..1000010] of btp; {����}
	son,now,sumd,dis,back,pre:array[0..20010] of longint; {���δ�����ʼ������ǰ���������������ţ�����ֵ��ǰ����}

procedure addit(x,y,d:longint); {��Dinicһ��������˫���}
begin
	inc(tot);
	edge[tot].x:=x; edge[tot].y:=y; edge[tot].f:=d; edge[tot].op:=tot+1;
	edge[tot].next:=son[x]; son[x]:=tot;
	inc(tot);
	edge[tot].x:=y; edge[tot].y:=x; edge[tot].f:=0; edge[tot].op:=tot-1;
	edge[tot].next:=son[y]; son[y]:=tot;
end;

procedure init; {��Dinicһ���Ķ���}
var i,x,y,d:longint;
begin
	tot:=0;
	fillchar(dis,sizeof(dis),0);
	fillchar(sumd,sizeof(sumd),0);
	fillchar(son,sizeof(son),0);
	fillchar(edge,sizeof(edge),0);

	readln(m,n);
	for i:=1 to m do
	  begin
		readln(x,y,d);
		addit(x,y,d);
	  end;
	now:=son; {��ǰ����ʼ���ɳ�ʼ��}
end;

procedure main;
var
	i,flow,ans,t,j,tmp,min:longint;
	flag:boolean;
begin
	sumd[0]:=n;ans:=0;
	i:=1;flow:=maxlongint; {��ʼ��}
	while dis[1]<n do {��ѭ������ݹ�}
	  begin
		back[i]:=flow; {I�ķ���ֵΪ��ǰ��С����}
		flag:=false; t:=now[i]; {���ÿ��û�Ϊfalse��tΪ��ǰ��һ����}
		while t<>0 do
		  begin
			j:=edge[t].y;
			if (edge[t].f>0)and(dis[j]+1=dis[i]) then {�����������Ź�ϵ}
		  	  begin
				flag:=true; {���û�}
				now[i]:=t; {���µ�ǰ��}
				if edge[t].f<flow then flow:=edge[t].f; {������С����}
				pre[j]:=t; {����j���ǰ����}
				i:=j; {ģ��ݹ飬i����j}
				if i=n then {������}
				  begin
					inc(ans,flow); {�ۼ������}
					while i<>1 do
					  begin
						dec(edge[pre[i]].f,flow); {������������}
						inc(edge[edge[pre[i]].op].f,flow); {���ӷ�������}
						i:=edge[pre[i]].x; {iΪǰ���ߵ�x}
					  end;
					flow:=maxlongint; {��ʼ��}
				  end;
				break; {�ҵ����û���ֱ������}
			  end;
			t:=edge[t].next;
		  end;
		if flag then continue; {����ҵ����û�����continue}
		min:=n-1; {��ʼ����С���}
		t:=son[i];
		while t<>0 do
		  begin
			if (edge[t].f>0)and(dis[edge[t].y]<min) then
			  begin
				tmp:=t;
				min:=dis[edge[t].y];
			  end; {���µ�ǰ����������С���}
			t:=edge[t].next;
		  end;
		now[i]:=tmp; {���õ�ǰ��Ϊ�ղŸ��µ�tmp}
		dec(sumd[dis[i]]); {��i���ڱ�ŵ�Ⱥ������ȥ1}
		if sumd[dis[i]]=0 then break; {���Ϊ0������ֶϲ㣬�˳�}
		dis[i]:=min+1; {���±��}
		inc(sumd[dis[i]]); {��i�����±�ŵ�Ⱥ��������1}
		if i<>1 then {����ǰһ����}
		  begin 
			i:=edge[pre[i]].x; 
			flow:=back[i]; 
		  end;
	  end;
	writeln(ans);
end;

begin
	assign(input,'ditch.in'); reset(input);
	assign(output,'ditch.out'); rewrite(output);
	init;
	main;
	close(input); close(output);
end.