unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Buttons, Registry, Zlib, ShlObj, ComObj, ActiveX,
  FileCtrl;

type
  TfrmMain = class(TForm)
    Label1: TLabel;
    imgLogo: TImage;
    edtName: TEdit;
    Label2: TLabel;
    edtPath: TEdit;
    btnBrowse: TButton;
    Label3: TLabel;
    Bevel1: TBevel;
    btnInstall: TBitBtn;
    btnCancel: TBitBtn;
    edtStep: TEdit;
    procedure FormCreate(Sender: TObject);
    procedure btnInstallClick(Sender: TObject);
    procedure btnBrowseClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure ExtractRes(ResName,ResType,Path:String);
    procedure ExtractZip(ResName,ResType,Path:String);
    procedure CreateShortCut(ExeName,ShortcutName:String);
    procedure ShowStep(Hint:String);
  end;

var
  frmMain: TfrmMain;

implementation

uses Thread;

{$R *.dfm}
{$R Books.res}

var
  InstallThread:TInstallThread;

procedure TfrmMain.FormCreate(Sender: TObject);
var
  reg:TRegistry;
begin
  reg:=TRegistry.Create;
  reg.RootKey:=HKEY_LOCAL_MACHINE;
  reg.OpenKey('\Software\Microsoft\Windows\CurrentVersion',False);
  edtPath.Text:=reg.ReadString('ProgramFilesDir')+'\图书管理';
  reg.CloseKey;
  reg.Free;
end;

procedure TfrmMain.btnInstallClick(Sender: TObject);
begin
  if btnInstall.Caption='安装&I'then
  begin
    InstallThread:=TInstallThread.Create(False);
    btnInstall.Enabled:=False;
    btnCancel.Enabled:=True;
  end else
  begin
    Application.Terminate;
    WinExec(PChar(edtPath.Text+'\Books.exe'),SW_NORMAL);
  end;
end;

procedure TfrmMain.ExtractRes(ResName,ResType,Path:String);
var
  res:TResourceStream;
begin
  res:=TResourceStream.Create(hInstance,ResName,PChar(ResType));
  res.SaveToFile(Path);
  res.Free;
end;

procedure TfrmMain.ExtractZip(ResName,ResType,Path:String);
var
  res:TResourceStream;
  Decompress:TDeCompressionStream;
  Dest:TFileStream;
  Size:Int64;
begin
  res:=TResourceStream.Create(hInstance,ResName,PChar(ResType));
  Decompress:=TDeCompressionStream.Create(res);
  Decompress.ReadBuffer(Size,8);
  Dest:=TFileStream.Create(Path,fmCreate);
  Dest.CopyFrom(Decompress,Size);
  try
    res.Free;
    Decompress.Free;
    Dest.Free;
  except
  end;
end;

procedure TfrmMain.CreateShortCut(ExeName,ShortcutName:String);
var
  Buf:array[0..MAX_PATH]of Char;
  p:PItemIDList;
  teObject:IUnknown;
  teSLink:IShellLink;
  tePFile:IPersistFile;
  LinkName:WideString;
begin
  SHGetSpecialFolderLocation(0,CSIDL_PROGRAMS,p);
  FillChar(Buf,Sizeof(Buf),#0);
  SHGetPathFromIDList(p,Buf);
  CoInitialize(nil);
  teObject:=CreateComObject(CLSID_SHELLLINK);
  teSLink:=teObject as IShellLink;
  tePFile:=teObject as IPersistFile;
  teSlink.SetPath(PChar(ExeName));
  teSLink.SetWorkingDirectory(PChar(ExtractFilePath(ExeName)));
  LinkName:=StrPas(Buf)+'\'+ShortcutName+'.lnk';
  tePFile.Save(PWideChar(LinkName),False);
end;

procedure TfrmMain.ShowStep(Hint:String);
begin
  edtStep.Text:=Hint;
end;

procedure TfrmMain.btnBrowseClick(Sender: TObject);
var
  Dir:String;
begin
  if SelectDirectory('选择安装目录','',Dir)then
    edtPath.Text:=Dir;
end;

procedure TfrmMain.btnCancelClick(Sender: TObject);
begin
  InstallThread.Terminate;
  Application.Terminate;
end;

end.
