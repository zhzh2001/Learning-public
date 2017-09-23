unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ImgList, Menus, ActnList, ComCtrls, ToolWin, DB, DBTables,
  StdActns;

type
  TfrmMain = class(TForm)
    ImageList1: TImageList;
    ActionList1: TActionList;
    atLogin: TAction;
    MainMenu1: TMainMenu;
    Safe1: TMenuItem;
    Login1: TMenuItem;
    StatusBar1: TStatusBar;
    atAdduser: TAction;
    Add1: TMenuItem;
    atDeleteuser: TAction;
    Delete1: TMenuItem;
    Manager1: TMenuItem;
    atFind: TAction;
    Find1: TMenuItem;
    atEdit: TAction;
    Edit1: TMenuItem;
    atStat: TAction;
    Stat1: TMenuItem;
    About1: TMenuItem;
    View1: TMenuItem;
    atStutusbar: TAction;
    Status1: TMenuItem;
    atToolbar: TAction;
    Tool1: TMenuItem;
    ToolBar1: TToolBar;
    ToolButton1: TToolButton;
    ToolButton2: TToolButton;
    ToolButton3: TToolButton;
    ToolButton4: TToolButton;
    ToolButton5: TToolButton;
    ToolButton6: TToolButton;
    ToolButton7: TToolButton;
    Window1: TMenuItem;
    tbUser: TTable;
    tbBooks: TTable;
    N1: TMenuItem;
    Export1: TMenuItem;
    P1: TMenuItem;
    atExport: TAction;
    ToolButton8: TToolButton;
    ToolButton9: TToolButton;
    atPack: TAction;
    ToolButton10: TToolButton;
    WindowClose1: TWindowClose;
    WindowCascade1: TWindowCascade;
    WindowTileHorizontal1: TWindowTileHorizontal;
    WindowTileVertical1: TWindowTileVertical;
    WindowMinimizeAll1: TWindowMinimizeAll;
    Cascade1: TMenuItem;
    Close1: TMenuItem;
    MinimizeAll1: TMenuItem;
    ileHorizontally1: TMenuItem;
    ileVertically1: TMenuItem;
    atReport: TAction;
    ToolButton11: TToolButton;
    R1: TMenuItem;
    SaveDialog1: TSaveDialog;
    ProgressBar1: TProgressBar;
    PopupMenu1: TPopupMenu;
    S1: TMenuItem;
    T1: TMenuItem;
    procedure FormCreate(Sender: TObject);
    procedure atLoginExecute(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure atAdduserExecute(Sender: TObject);
    procedure atDeleteuserExecute(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure atFindExecute(Sender: TObject);
    procedure atEditExecute(Sender: TObject);
    procedure tbBooksBeforePost(DataSet: TDataSet);
    procedure atStatExecute(Sender: TObject);
    procedure atStutusbarExecute(Sender: TObject);
    procedure atToolbarExecute(Sender: TObject);
    procedure atExportExecute(Sender: TObject);
    procedure atPackExecute(Sender: TObject);
    procedure atReportExecute(Sender: TObject);
    procedure About1Click(Sender: TObject);
    procedure FormActivate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    ExePath:String;
  end;

var
  frmMain: TfrmMain;

implementation

uses Login, Add, Delete, Find, Edit, Stat, Report, About, uExportXls;

{$R *.dfm}

procedure TfrmMain.FormCreate(Sender: TObject);
begin
  ExePath:=ExtractFilePath(Application.ExeName);
  tbUser.TableName:=ExePath+'User.db';
  tbBooks.TableName:=ExePath+'Books.db';
  try
    tbUser.Open;
    tbBooks.Open;
  except
    Application.MessageBox('数据表出错！请重新安装本程序！','警告',MB_OK+MB_ICONEXCLAMATION);
    Halt;
  end;
end;

procedure TfrmMain.atLoginExecute(Sender: TObject);
begin
  frmLogin:=TfrmLogin.Create(nil);
end;

procedure TfrmMain.FormDestroy(Sender: TObject);
begin
  tbUser.Close;
  tbBooks.Close;
end;

procedure TfrmMain.atAdduserExecute(Sender: TObject);
begin
  frmAdd:=TfrmAdd.Create(nil);
end;

procedure TfrmMain.atDeleteuserExecute(Sender: TObject);
begin
  frmDelete:=TfrmDelete.Create(nil);
end;

procedure TfrmMain.FormResize(Sender: TObject);
begin
  StatusBar1.Panels[0].Width:=StatusBar1.Width-150;
end;

procedure TfrmMain.atFindExecute(Sender: TObject);
begin
  frmFind:=TfrmFind.Create(nil);
end;

procedure TfrmMain.atEditExecute(Sender: TObject);
begin
  frmEdit:=TfrmEdit.Create(nil);
end;

procedure TfrmMain.tbBooksBeforePost(DataSet: TDataSet);
var
  s:string;
begin
  s:=tbBooks.FieldByName('在架情况').AsString;
  if(s<>'在架')and(s<>'借出')and(s<>'丢失')and(s<>'')then
  begin
    Application.MessageBox('在架情况中含有非法字符！','警告',MB_OK+MB_ICONEXCLAMATION);
    Abort;
  end;
end;

procedure TfrmMain.atStatExecute(Sender: TObject);
begin
  frmStat:=TfrmStat.Create(nil); 
end;

procedure TfrmMain.atStutusbarExecute(Sender: TObject);
begin
  atStutusbar.Checked:=not(atStutusbar.Checked);
  StatusBar1.Visible:=atStutusbar.Checked;
end;

procedure TfrmMain.atToolbarExecute(Sender: TObject);
begin
  atToolbar.Checked:=not(atToolbar.Checked);
  Toolbar1.Visible:=atToolbar.Checked;
end;

procedure TfrmMain.atExportExecute(Sender: TObject);
begin
  if not(SaveDialog1.Execute)then
    exit;
  ExportToExcel(SaveDialog1.FileName,tbBooks);
  Application.MessageBox('导出成功！','提示',MB_OK+MB_ICONASTERISK);
end;

procedure TfrmMain.atPackExecute(Sender: TObject);
var
  Temp:TQuery;
  i:Integer;
  Name:String;
begin
  ProgressBar1.Parent:=StatusBar1;
  ProgressBar1.Width:=StatusBar1.Panels[0].Width;
  ProgressBar1.Max:=tbBooks.RecordCount;
  ProgressBar1.Position:=0;
  ProgressBar1.Visible:=True;
  Temp:=TQuery.Create(nil);
  Temp.RequestLive:=False;
  Temp.Close;
  Temp.SQL.Add('SELECT *');
  Temp.SQL.Add('FROM '+#39+tbBooks.TableName+#39);
  Temp.Open;
  tbBooks.Close;
  tbBooks.EmptyTable;
  tbBooks.Open;

  while not(Temp.Eof)do
  begin
    tbBooks.Append;
    for i:=0 to Temp.FieldCount-1 do
    begin
      Name:=tbBooks.Fields.Fields[i].FieldName;
      case tbBooks.Fields.Fields[i].DataType of
      ftString,ftMemo:tbBooks.FieldByName(Name).AsString:=Temp.FieldByName(Name).AsString;
      ftSmallInt:tbBooks.FieldByName(Name).AsInteger:=Temp.FieldByName(Name).AsInteger;
      ftCurrency:tbBooks.FieldByName(Name).AsCurrency:=Temp.FieldByName(Name).AsCurrency;
      end;
    end;
    tbBooks.Post;
    Temp.Next;
    ProgressBar1.Position:=ProgressBar1.Position+1;
    Application.ProcessMessages;
  end;

  Temp.Free;
  ProgressBar1.Visible:=False;
  Application.MessageBox('压缩成功！','提示',MB_OK+MB_ICONASTERISK);
end;

procedure TfrmMain.atReportExecute(Sender: TObject);
begin
  frmReport.QuickRep1.Preview;
end;

procedure TfrmMain.About1Click(Sender: TObject);
begin
  AboutBox:=TAboutBox.Create(nil);
end;

procedure TfrmMain.FormActivate(Sender: TObject);
begin
  if tbUser.RecordCount=0 then
  begin
    Application.MessageBox('第一次使用本程序请添加用户！','第一次使用',MB_OK+MB_ICONASTERISK);
    atAdduserExecute(atAdduser);
  end;
end;

end.
