PROGRAM SkipList(input,output);
CONST
	maxlev=16;
    inf=9999999;
    maxn=5000000;
    none=-1;
    maxp=1000;
VAR
    val,down,next,pre:array[1..maxn]of longint;
    Last:array[1..maxlev]of longint;        //last�洢������������ÿһ�������������ʵĽڵ�
    Path:array[1..maxp]of longint;          //path�洢����·��
    SLSize,PathSize:longint;
    op,v:longint;
    Function RandomLev:longint;             //����ó��߶�
    Var
        h:longint;
    Begin
        h:=1;
        while((random(4)=0)and(h<maxlev))do inc(h);
        RandomLev:=h;
    End;
    Procedure init;                         //��ʼ������
    Var
    	i:longint;
    Begin
    	val[maxn]:=inf;
        for i:=1 to maxlev do
        begin
        	val[i]:=-inf;
            down[i]:=i-1;
            next[i]:=maxn;
            pre[i]:=none;
        end;
        down[1]:=none;
        SLSize:=maxlev;
    End;
    Function search(v:longint):longint;     //����v
    Var
    	p,lv:longint;
    Begin
        p:=maxlev;
        lv:=maxlev;
        PathSize:=0;
        while(p<>none)do
        begin
        	inc(PathSize);
            Path[PathSize]:=p;
            if(val[next[p]]<=v)then
            begin
                p:=next[p];
            end else begin
            	last[lv]:=p;
                lv:=lv-1;
                p:=down[p];
            end;
        end;
        search:=Path[PathSize];
    End;
    Procedure insert(v:longint);            //����
    Var
    	h,i,p,tmp:longint;
    Begin
        h:=RandomLev;
        tmp:=none;
        if val[search(v)]=v then
        begin
            writeln('ERROR!');
        	exit;
        end;
        for i:=1 to h do
        begin
        	p:=last[i];
            inc(SLSize);
            val[SLSize]:=v;
            down[SLSize]:=tmp; tmp:=SLSize;
            next[SLSize]:=next[p];
            pre[SLSize]:=p;
            next[p]:=SLSize;
            pre[next[SLSize]]:=SLSize;
        end;
        writeln('Done');
    End;
    Procedure delete(v:longint);            //ɾ��
    Var
    	i,p:longint;
    Begin
    	if val[search(v)]<>v then
        begin
            writeln('ERROR!');
        	exit;
        end;
        for i:=1 to maxlev do
        begin
        	if val[last[i]]<>v then break;
            p:=pre[last[i]];
            next[p]:=next[next[p]];
            pre[next[p]]:=p;
        end;
        writeln('Done');
    End;
BEGIN
	randomize;
    init;
    while not eof do
    begin
        readln(op,v);   //������������ ��һ�����ֱ�ʾ���� �ڶ������ֱ�ʾ��Ҫ������ֵ
        if op=1 then writeln('Found ',val[search(v)]);
        if op=2 then insert(v);
        if op=3 then delete(v);
    end;
    writeln(SLSize);
END.



