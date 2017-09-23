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
  frmMain.ShowStep('正在创建目录'+frmMain.edtPath.Text);
  if not(DirectoryExists(frmMain.edtPath.Text))then
    ForceDirectories(frmMain.edtPath.Text);
  if Self.Terminated then
    Exit;

  frmMain.ShowStep('正在解压文件Books.exe');
  frmMain.ExtractZip('BooksZIP','zip',frmMain.edtPath.Text+'\Books.exe');
  if Self.Terminated then
    Exit;

  frmMain.ShowStep('正在提取文件Books.MB');
  frmMain.ExtractRes('BooksMB','MB',frmMain.edtPath.Text+'\Books.MB');
  if Self.Terminated then
    Exit;

  frmMain.ShowStep('正在提取文件Books.DB');
  frmMain.ExtractRes('BooksDB','DB',frmMain.edtPath.Text+'\Books.DB');
  if Self.Terminated then
    Exit;

  frmMain.ShowStep('正在提取文件User.DB');
  frmMain.ExtractRes('UserDB','DB',frmMain.edtPath.Text+'\User.DB');
  if Self.Terminated then
    Exit;

  frmMain.ShowStep('正在创建程序项');
  frmMain.CreateShortCut(frmMain.edtPath.Text+'\Books.exe','家庭图书管理系统');
  if Self.Terminated then
    Exit;
  frmMain.ShowStep('安装完成');

  frmMain.btnInstall.Enabled:=True;
  frmMain.btnCancel.Enabled:=False;
  frmMain.btnInstall.Caption:='完成&D';
end;

end.
