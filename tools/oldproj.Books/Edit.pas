unit Edit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, Grids, DBGrids, DB, StdCtrls, Buttons, DBCtrls;

type
  TfrmEdit = class(TForm)
    DataSource1: TDataSource;
    DBGrid1: TDBGrid;
    DBNavigator1: TDBNavigator;
    Panel1: TPanel;
    GroupBox1: TGroupBox;
    DBMemo1: TDBMemo;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure DBGrid1KeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmEdit: TfrmEdit;

implementation

uses Main;

{$R *.dfm}

procedure TfrmEdit.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action:=caFree;
end;

procedure TfrmEdit.DBGrid1KeyPress(Sender: TObject; var Key: Char);
begin
  if Key=#13 then
    PostMessage(DBGrid1.Handle,WM_KEYDOWN,VK_TAB,0);
end;

end.
