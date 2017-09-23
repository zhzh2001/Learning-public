program Books;

{$MODE Delphi}

uses
  Forms,
  LCLIntf, LCLType, LMessages, Interfaces,
  Main in 'Main.pas' {frmMain},
  Login in 'Login.pas' {frmLogin},
  Add in 'Add.pas' {frmAdd},
  Delete in 'Delete.pas' {frmDelete},
  Find in 'Find.pas' {frmFind},
  Edit in 'Edit.pas' {frmEdit},
  Stat in 'Stat.pas' {frmStat},
  Report in 'Report.pas' {frmReport},
  Splash in 'Splash.pas' {frmSplash},
  About in 'About.pas' {AboutBox},
  uExportXls in 'uExportXls.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.Title := '家庭图书管理系统';
  CreateMutex(nil,False,'家庭图书管理系统');
  if GetLastError=ERROR_ALREADY_EXISTS then
    Halt;
  frmSplash:=TfrmSplash.Create(nil);
  frmSplash.Show;
  Application.CreateForm(TfrmMain, frmMain);
  Application.CreateForm(TfrmReport, frmReport);
  frmSplash.Close;
  frmSplash.Free;
  Application.Run;
end.
