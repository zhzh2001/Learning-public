unit Add;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, DB;

type
  TfrmAdd = class(TForm)
    GroupBox1: TGroupBox;
    lbUser: TLabel;
    lbPassword: TLabel;
    edtPassword: TEdit;
    Label1: TLabel;
    edtToken: TComboBox;
    btnOK: TBitBtn;
    btnCancel: TBitBtn;
    edtUser: TEdit;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btnOKClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmAdd: TfrmAdd;

implementation

uses Main;

{$R *.dfm}

procedure TfrmAdd.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action:=caFree;
end;

procedure TfrmAdd.btnOKClick(Sender: TObject);
var
  Password:String;
begin
  with frmMain do
  begin
    if tbUser.State<>dsBrowse then
    begin
      Application.MessageBox('请保存数据后再添加！','提示',MB_OK+MB_ICONASTERISK);
      Exit;
    end;
    if Length(edtUser.Text)<4 then
    begin
      Application.MessageBox('用户名不能少于4位！','警告',MB_OK+MB_ICONEXCLAMATION);
      Exit;
    end;
    if tbUser.Locate('用户名',edtUser.Text,[loCaseInsensitive])then
    begin
      Application.MessageBox('用户已存在，请更换用户名！','提示',MB_OK+MB_ICONASTERISK);
      Exit;
    end;
    if edtPassword.Text=''then
    begin
      if Application.MessageBox('设置空密码很不安全，是否继续？','询问',MB_YESNO+MB_ICONQUESTION)=idNo then
        Exit;
    end else
    begin
      if Length(edtPassword.Text)<4 then
      begin
        Application.MessageBox('密码不能少于4位！','警告',MB_OK+MB_ICONEXCLAMATION);
        Exit;
      end;
      Password:=InputBox('验证','请再次输入密码：','');
      if Password<>edtPassword.Text then
      begin
        Application.MessageBox('密码错误！','提示',MB_OK+MB_ICONASTERISK);
        Exit;
      end;
    end;
    tbUser.Last;
    tbUser.Append;
    tbUser.FieldByName('用户名').AsString:=edtUser.Text;
    tbUser.FieldByName('密码').AsString:=edtPassword.Text;
    tbUser.FieldByName('权限').AsInteger:=edtToken.ItemIndex;
    tbUser.Post;
  end;
  Close;
end;

procedure TfrmAdd.btnCancelClick(Sender: TObject);
begin
  Close;
end;

end.
