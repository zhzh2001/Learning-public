program Install;

uses
  Forms,
  Main in 'Main.pas' {frmMain},
  Thread in 'Thread.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.Title := '��װ��ͥͼ�����ϵͳ';
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
