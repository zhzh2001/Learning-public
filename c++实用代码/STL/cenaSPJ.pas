{�����CEOI 2011 Day1 T1 balloons��SJ�Ĵ���}
{����n���ж�ѡ�������n���������Ƿ����������Χ��}
uses
	libcheck;
var
	n,i: longint;
	x,y: extended;
	bin,bout: text;
	procedure ends(x:double);  {���ص÷�Ϊx����������}
	begin
		score(x);
		writeln(rep,n,' lines checked');
		writeln(rep,'SJ by wyl8899');
		Finish;
		halt;
	end;
begin
	assign(bin,'balloons.in'); reset(bin); 
	readln(bin,n); close(bin);
	assign(bout,'balloons.out'); reset(bout);
	for i:=1 to n do
	begin
		readln(std,y); 
		if seekeof(bout) then
		begin
			writeln(rep,'Output Too Short');
			ends(0);
		end;
		readln(bout,x);
		if (x-y>0.001001)or(y-x>0.001001) then
		begin
			writeln(rep,'Line ',i);
			writeln(rep,'Std:',y:0:3);
			writeln(rep,'W A:',x:0:3);
			ends(0);
		end;
	end;
	if not seekeof(bout) then
	begin
		writeln(rep,'Output Too Long');
		ends(0);
	end;
	ends(fsco);							 
end.


