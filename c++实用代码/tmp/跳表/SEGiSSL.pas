PROGRAM DPiSSL(input,output);
{
һ��SSLά������SEGi������
���߶�ȾɫΪ��
}
CONST
	maxlev=16;
    inf=9999999;
    maxn=5000000;
    none=-1;
    maxp=1000;
VAR
    val,down,next,pre:array[0..maxn]of longint;
    segi:array[0..maxn]of longint;        //segi��Ϣ ��Ⱦ����ɫΪ�� ��ʼʱ����ƽ��Ϊ��(0)
    Last:array[0..maxlev]of longint;        //last�洢������������ÿһ�������������ʵĽڵ�
    Path:array[1..maxp]of longint;          //path�洢����·��
    bt:array[1..maxn]of boolean;            //�ýڵ��Ƿ�Ϊĳ��Ķ����ڵ� �����жϺ����ʵ��
    SLSize,PathSize:longint;
    op,l,r,c,right:longint;
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
        fillchar(bt,sizeof(bt),false);
        fillchar(segi,sizeof(segi),0);
    	val[maxn]:=inf;
        for i:=0 to maxlev do
        begin
        	val[i]:=-inf;
            down[i]:=i-1;
            next[i]:=maxn;
            pre[i]:=none;
        end;
        down[0]:=none;
        SLSize:=maxlev;
    End;
    Function search(v:longint):longint;     //����v
    Var
    	p,lv,color:longint;
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
    Function ask(v:longint):longint;
    Var
    	p:longint;
    Begin
    	p:=maxlev;
        while p<>none do
        begin
            if segi[p]<>0 then exit(segi[p]);
            if val[next[p]]<=v then
            	p:=next[p]
            else
            	p:=down[p];
        end;
        exit(0);
    End;
    Procedure update;
    Var
        i,p:longint;
    Begin
    	for i:=1 to PathSize-1 do
        begin
            p:=Path[i];
            if segi[p]<>0 then
            begin
                segi[down[p]]:=segi[p];
                if bt[next[p]] then
                    segi[next[p]]:=segi[p];
                segi[p]:=0;
            end;
        end;
    End;
    Procedure insert(v:longint);            //����
    Var
    	h,i,p,tmp:longint;
    Begin
        h:=RandomLev;
        tmp:=none;
        if val[search(v)]=v then
        begin
            update;         //��path(v)�·�������Ϣ
    	end else begin
            update;         //��path(v)�·�������Ϣ
            segi[SLSize+1]:=segi[Path[PathSize]];
            for i:= 0 to h do
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
            bt[SLSize]:=true;
        end;
        bt[SLSize]:=true;
    End;
    Procedure paint(p,l,r,c:longint);       //��p��Ӧ��������[l,r)����Ľ�Ⱦ��c��ɫ
    Begin
        if (p=none)or(val[p]>=r)or (right<=l) then exit;
        if (val[p]>=l)and(right<=r) then
        begin
            segi[p]:=c;
            exit;
        end;
        if bt[next[p]] then paint(next[p],l,r,c);
        right:=val[next[p]];
        paint(down[p],l,r,c);
    End;
    Procedure delete(v:longint);            //ɾ��
    Var
    	i,p,c1,c2:longint;
    Begin
    //��������д��ɾ����������ȫ������������д�Ľ��� ����ʹ������һ��д�� ���������ʾ������������
    	if val[search(v)]<>v then
        begin
            writeln('ERROR!');
        	exit;
        end;
        p:=Path[PathSize];
        c1:=ask(val[pre[p]]);
        c2:=ask(val[p]);
        if c1<>c2 then  //v��ĳ��Ⱦɫ����Ķ˵�
        begin
            writeln('ERROR!');
            exit;
        end;
        paint(maxlev,val[pre[p]],val[next[p]],c1);
        for i:=0 to maxlev do
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
        read(op);
        if op=1 then        //��һ�ֲ��� Ⱦɫ
        begin
            read(l,r,c);    //��[l,r)Ⱦ��c��ɫ
            insert(l);
            insert(r);
            right:=inf;
            paint(maxlev,l,r,c);   //��[l,r)Ⱦ��c��ɫ
            writeln('Done');
        end;
        if op=2 then        //�ڶ��ֲ��� ѯ��
        begin
            read(l);
            writeln('Color(',l,')=',ask(l));
                            //ѯ��x=l������ɫ
        end;
        if op=3 then        //�����ֲ��� ɾ��
        begin
            read(l);
            delete(l);      //�����ֲ��� ɾ��
        end;
    end;
    writeln(SLSize);
END.


