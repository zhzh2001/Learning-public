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
      MessageDlg('�뱣�����ݺ��ٵ�½��',mtInformation,[mbOK],0);
      Exit;
    end;
    tbUser.First;
    edtUser.Items.Clear;
    while not(tbUser.Eof)do
    begin
      s:=tbUser.FieldByName('�û���').AsString;
      case tbUser.FieldByName('Ȩ��').AsInteger of
      0:s:=s+'(��ͨ�û�)';
      1:s:=s+'(�����û�)';
      2:s:=s+'(����Ա)';
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
      Application.MessageBox('������30���������µ�½���������¼�ʱ��','����',MB_OK+MB_ICONEXCLAMATION);
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
      Application.MessageBox('�뱣�����ݺ��ٵ�¼��','��ʾ',MB_OK+MB_ICONASTERISK);
      Exit;
    end;
    tbUser.First;
    tbUser.MoveBy(edtUser.ItemIndex);
    if(tbUser.FieldByName('����').AsString=edtPassword.Text)and(edtUser.Text<>'')then
    begin
      StatusBar1.Panels[1].Text:='�û�:'+tbUser.FieldByName('�û���').AsString;
      Application.MessageBox('��½�ɹ���','��ʾ',MB_OK+MB_ICONASTERISK);
      atFind.Enabled:=True;
      atStat.Enabled:=True;
      atExport.Enabled:=True;
      atPack.Enabled:=True;
      atReport.Enabled:=True;
      atAdduser.Enabled:=False;
      atDeleteUser.Enabled:=False;
      atEdit.Enabled:=False;
      if tbUser.FieldByName('Ȩ��').AsInteger>0 then
        atEdit.Enabled:=True;
      if tbUser.FieldByName('Ȩ��').AsInteger>1 then
      begin
        atAdduser.Enabled:=True;
        atDeleteuser.Enabled:=True;
      end;
      frmLogin.Close;
    end else
    begin
      Application.MessageBox('�������','��ʾ',MB_OK+MB_ICONASTERISK);
      inc(count);
      if count>=3 then
      begin
        reg:=TRegistry.Create;
        reg.RootKey:=HKEY_LOCAL_MACHINE;
        reg.OpenKey('\Software\Books',True);
        reg.WriteInteger('Wrongtime',GetTickCount);
        reg.CloseKey;
        reg.Free;
        Application.MessageBox('�������3�����ϣ�30�����ڲ������µ�½��','����',MB_OK+MB_ICONEXCLAMATION);
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
