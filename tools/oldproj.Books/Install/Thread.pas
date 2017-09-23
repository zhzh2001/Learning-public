unit Thread;

interface

uses
  Classes, SysUtils;

type
  TInstallThread = class(TThread)
  private
    { Private declarations }
  protected
    procedure Execute; override;
  end;

implementation

uses Main;

procedure TInstallThread.Execute;
begin
  frmMain.ShowStep('���ڴ���Ŀ¼'+frmMain.edtPath.Text);
  if not(DirectoryExists(frmMain.edtPath.Text))then
    ForceDirectories(frmMain.edtPath.Text);
  if Self.Terminated then
    Exit;

  frmMain.ShowStep('���ڽ�ѹ�ļ�Books.exe');
  frmMain.ExtractZip('BooksZIP','zip',frmMain.edtPath.Text+'\Books.exe');
  if Self.Terminated then
    Exit;

  frmMain.ShowStep('������ȡ�ļ�Books.MB');
  frmMain.ExtractRes('BooksMB','MB',frmMain.edtPath.Text+'\Books.MB');
  if Self.Terminated then
    Exit;

  frmMain.ShowStep('������ȡ�ļ�Books.DB');
  frmMain.ExtractRes('BooksDB','DB',frmMain.edtPath.Text+'\Books.DB');
  if Self.Terminated then
    Exit;

  frmMain.ShowStep('������ȡ�ļ�User.DB');
  frmMain.ExtractRes('UserDB','DB',frmMain.edtPath.Text+'\User.DB');
  if Self.Terminated then
    Exit;

  frmMain.ShowStep('���ڴ���������');
  frmMain.CreateShortCut(frmMain.edtPath.Text+'\Books.exe','��ͥͼ�����ϵͳ');
  if Self.Terminated then
    Exit;
  frmMain.ShowStep('��װ���');

  frmMain.btnInstall.Enabled:=True;
  frmMain.btnCancel.Enabled:=False;
  frmMain.btnInstall.Caption:='���&D';
end;

end.
