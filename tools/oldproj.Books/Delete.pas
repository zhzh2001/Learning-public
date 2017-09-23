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
      Application.MessageBox('请保存数据后再删除！','提示',MB_OK+MB_ICONASTERISK);
      Exit;
    end;
    tbUser.First;
    edtUser.Items.Clear;
    while not(tbUser.Eof)do
    begin
      s:=tbUser.FieldByName('用户名').AsString;
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
    User:=Copy(User,Length('用户:')+1,Len-Length('用户:'));
    if edtUser.Text=User then
    begin
      Application.MessageBox('不能删除现在登录的用户！','提示',MB_OK+MB_ICONASTERISK);
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
      Application.MessageBox('请保存数据后再删除！','提示',MB_OK+MB_ICONASTERISK);
      Exit;
    end;
    tbUser.Locate('用户名',edtUser.Text,[loCaseInsensitive]);
    if Application.MessageBox(PChar('确实要删除用户['+edtUser.Text+']吗？'),'询问',MB_YESNO+MB_ICONQUESTION)=idNo then
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
