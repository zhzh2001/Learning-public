unit Login;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, DB, Registry;

type
  TfrmLogin = class(TForm)
    GroupBox1: TGroupBox;
    btnOK: TBitBtn;
    btnCancel: TBitBtn;
    lbUser: TLabel;
    edtUser: TComboBox;
    lbPassword: TLabel;
    edtPassword: TEdit;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormCreate(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    count:integer;
  end;

var
  frmLogin:TfrmLogin;

implementation

uses Main;

{$R *.dfm}

procedure TfrmLogin.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action:=caFree;
end;

procedure TfrmLogin.FormCreate(Sender: TObject);
var
  s:string;
  reg:TRegistry;
begin
  with frmMain do
  begin
    if tbUser.State<>dsBrowse then
    begin
      MessageDlg('请保存数据后再登陆！',mtInformation,[mbOK],0);
      Exit;
    end;
    tbUser.First;
    edtUser.Items.Clear;
    while not(tbUser.Eof)do
    begin
      s:=tbUser.FieldByName('用户名').AsString;
      case tbUser.FieldByName('权限').AsInteger of
      0:s:=s+'(普通用户)';
      1:s:=s+'(超级用户)';
      2:s:=s+'(管理员)';
      end;
      edtUser.Items.Add(s);
      tbUser.Next;
    end;
  end;
  count:=0;
  edtUser.ItemIndex:=0;
  reg:=TRegistry.Create;
  reg.RootKey:=HKEY_LOCAL_MACHINE;
  reg.OpenKey('\Software\Books',True);
  if reg.ValueExists('Wrongtime')then
    if GetTickCount<=reg.ReadInteger('Wrongtime')+1800000 then
    begin
      reg.WriteInteger('Wrongtime',GetTickCount);
      Application.MessageBox('不能在30分钟内重新登陆！现在重新计时！','警告',MB_OK+MB_ICONEXCLAMATION);
      Application.Terminate;
    end;
  reg.CloseKey;
  reg.Free;
end;

procedure TfrmLogin.btnOKClick(Sender: TObject);
var
  reg:TRegistry;
begin
  with frmMain do
  begin
    if tbUser.State<>dsBrowse then
    begin
      Application.MessageBox('请保存数据后再登录！','提示',MB_OK+MB_ICONASTERISK);
      Exit;
    end;
    tbUser.First;
    tbUser.MoveBy(edtUser.ItemIndex);
    if(tbUser.FieldByName('密码').AsString=edtPassword.Text)and(edtUser.Text<>'')then
    begin
      StatusBar1.Panels[1].Text:='用户:'+tbUser.FieldByName('用户名').AsString;
      Application.MessageBox('登陆成功！','提示',MB_OK+MB_ICONASTERISK);
      atFind.Enabled:=True;
      atStat.Enabled:=True;
      atExport.Enabled:=True;
      atPack.Enabled:=True;
      atReport.Enabled:=True;
      atAdduser.Enabled:=False;
      atDeleteUser.Enabled:=False;
      atEdit.Enabled:=False;
      if tbUser.FieldByName('权限').AsInteger>0 then
        atEdit.Enabled:=True;
      if tbUser.FieldByName('权限').AsInteger>1 then
      begin
        atAdduser.Enabled:=True;
        atDeleteuser.Enabled:=True;
      end;
      frmLogin.Close;
    end else
    begin
      Application.MessageBox('密码错误！','提示',MB_OK+MB_ICONASTERISK);
      inc(count);
      if count>=3 then
      begin
        reg:=TRegistry.Create;
        reg.RootKey:=HKEY_LOCAL_MACHINE;
        reg.OpenKey('\Software\Books',True);
        reg.WriteInteger('Wrongtime',GetTickCount);
        reg.CloseKey;
        reg.Free;
        Application.MessageBox('密码错误3次以上，30分钟内不能重新登陆！','警告',MB_OK+MB_ICONEXCLAMATION);
        Application.Terminate;
      end;
      edtPassword.Clear;
      edtPassword.SetFocus;
    end;
  end;
end;

procedure TfrmLogin.btnCancelClick(Sender: TObject);
begin
  Close;
end;

end.
