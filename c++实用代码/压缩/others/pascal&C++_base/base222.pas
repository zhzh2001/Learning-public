const
  s:string=' !"#$%&()*+,-.0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~��������������������������������������������������������������������������������������������������������������������������������';
  begin
  assign(output,'a.out');rewrite(output);
  write(s);
  close(output);
  end.
