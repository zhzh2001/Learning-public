procedure add(i,j:longint);
begin
     inc(top);
     v[top]:=j;
     next[top]:=u[i];
     u[i]:=top;
     inc(degree[i]);
end;
procedure ins(i:longint);
var o:longint;
begin
     visit[i]:=true;
     inc(tot);
     o:=u[i];
     while o<>0 do begin
          dec(degree[v[o]]);
          o:=next[o];
     end;
end;
begin
     readln(n,m,k);
     for a:=1 to k do begin
        readln(b,c);
        c:=n+c;
        add(b,c);
        add(c,b);
     end;

     n:=n+m;
     while tot<n do begin
          b:=maxlongint;//�ҽ��u
          for a:=1 to n do if(not visit[a])and(degree[a]<b)then begin
             b:=degree[a];
             c:=a;
          end;
          a:=u[c];
          b:=maxlongint;//�ҽ��v
          while a<>0 do begin
               if(not visit[v[a]])and(degree[v[a]]<b)then begin
                 b:=degree[v[a]];
                 d:=v[a];
               end;
               a:=next[a];
          end;
          inc(ans);//���ߣ��𰸼�һ
          ins(c);//��u����ɾ������
          if b<>maxlongint then ins(d);//�������v����v����ɾ������
     end;
     writeln(ans);
end.

