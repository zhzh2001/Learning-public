program Install;

uses
  Forms,
  Main in 'Main.pas' {frmMain},
  Thread in 'Thread.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.Title := '安装家庭图书管理系统';
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
