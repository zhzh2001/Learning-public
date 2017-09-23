unit Delete;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, DB;

type
  TfrmDelete = class(TForm)
    GroupBox1: TGroupBox;
    btnOK: TBitBtn;
    btnCancel: TBitBtn;
    edtUser: TComboBox;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormCreate(Sender: TObject);
    procedure edtUserChange(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmDelete: TfrmDelete;

implementation

uses Main;

{$R *.dfm}

procedure TfrmDelete.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action:=caFree;
end;

procedure TfrmDelete.FormCreate(Sender: TObject);
var
  s:string;
begin
  with frmMain do
  begin
    if tbUser.State<>dsBrowse then
    begin
      Application.MessageBox('�뱣�����ݺ���ɾ����','��ʾ',MB_OK+MB_ICONASTERISK);
      Exit;
    end;
    tbUser.First;
    edtUser.Items.Clear;
    while not(tbUser.Eof)do
    begin
      s:=tbUser.FieldByName('�û���').AsString;
      edtUser.Items.Add(s);
      tbUser.Next;
    end;
  end;
end;

procedure TfrmDelete.edtUserChange(Sender: TObject);
var
  User:String;
  Len:Integer;
begin
  with frmMain do
  begin
    User:=StatusBar1.Panels[1].Text;
    Len:=Length(User);
    User:=Copy(User,Length('�û�:')+1,Len-Length('�û�:'));
    if edtUser.Text=User then
    begin
      Application.MessageBox('����ɾ�����ڵ�¼���û���','��ʾ',MB_OK+MB_ICONASTERISK);
      edtUser.ItemIndex:=-1;
    end;
  end;
end;

procedure TfrmDelete.btnOKClick(Sender: TObject);
begin
  with frmMain do
  begin
    if edtUser.Text=''then exit;
    if tbUser.State<>dsBrowse then
    begin
      Application.MessageBox('�뱣�����ݺ���ɾ����','��ʾ',MB_OK+MB_ICONASTERISK);
      Exit;
    end;
    tbUser.Locate('�û���',edtUser.Text,[loCaseInsensitive]);
    if Application.MessageBox(PChar('ȷʵҪɾ���û�['+edtUser.Text+']��'),'ѯ��',MB_YESNO+MB_ICONQUESTION)=idNo then
      Exit;
    tbUser.Delete;
  end;
  FormCreate(Self);
end;

procedure TfrmDelete.btnCancelClick(Sender: TObject);
begin
  Close;
end;

end.
