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
      Application.MessageBox('�뱣�����ݺ�����ӣ�','��ʾ',MB_OK+MB_ICONASTERISK);
      Exit;
    end;
    if Length(edtUser.Text)<4 then
    begin
      Application.MessageBox('�û�����������4λ��','����',MB_OK+MB_ICONEXCLAMATION);
      Exit;
    end;
    if tbUser.Locate('�û���',edtUser.Text,[loCaseInsensitive])then
    begin
      Application.MessageBox('�û��Ѵ��ڣ�������û�����','��ʾ',MB_OK+MB_ICONASTERISK);
      Exit;
    end;
    if edtPassword.Text=''then
    begin
      if Application.MessageBox('���ÿ�����ܲ���ȫ���Ƿ������','ѯ��',MB_YESNO+MB_ICONQUESTION)=idNo then
        Exit;
    end else
    begin
      if Length(edtPassword.Text)<4 then
      begin
        Application.MessageBox('���벻������4λ��','����',MB_OK+MB_ICONEXCLAMATION);
        Exit;
      end;
      Password:=InputBox('��֤','���ٴ��������룺','');
      if Password<>edtPassword.Text then
      begin
        Application.MessageBox('�������','��ʾ',MB_OK+MB_ICONASTERISK);
        Exit;
      end;
    end;
    tbUser.Last;
    tbUser.Append;
    tbUser.FieldByName('�û���').AsString:=edtUser.Text;
    tbUser.FieldByName('����').AsString:=edtPassword.Text;
    tbUser.FieldByName('Ȩ��').AsInteger:=edtToken.ItemIndex;
    tbUser.Post;
  end;
  Close;
end;

procedure TfrmAdd.btnCancelClick(Sender: TObject);
begin
  Close;
end;

end.
