unit Stat;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, TeeProcs, TeEngine, Chart, DbChart, StdCtrls, Buttons,
  Series, TeePrevi, ExtDlgs, DB, DBTables, ComCtrls;

type
  TfrmStat = class(TForm)
    DBChart1: TDBChart;
    Panel1: TPanel;
    btnPreview: TBitBtn;
    btnClose: TBitBtn;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    ColorDialog1: TColorDialog;
    BitBtn1: TBitBtn;
    SavePictureDialog1: TSavePictureDialog;
    Series1: TPieSeries;
    Query1: TQuery;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    Timer1: TTimer;
    TrackBar1: TTrackBar;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btnPreviewClick(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
    procedure CheckBox2Click(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure CheckBox3Click(Sender: TObject);
    procedure CheckBox4Click(Sender: TObject);
    procedure TrackBar1Change(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    Speed:Integer;
  end;

var
  frmStat: TfrmStat;

implementation

uses Main;

{$R *.dfm}

procedure TfrmStat.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action:=caFree;
end;

procedure TfrmStat.btnPreviewClick(Sender: TObject);
begin
  ChartPreview(nil,DBChart1);
end;

procedure TfrmStat.CheckBox1Click(Sender: TObject);
begin
  DBChart1.View3D:=CheckBox1.Checked;
end;

procedure TfrmStat.CheckBox2Click(Sender: TObject);
begin
  Series1.ColorEachPoint:=CheckBox2.Checked;
  if not(CheckBox2.Checked)then
    if ColorDialog1.Execute then
      Series1.SeriesColor:=ColorDialog1.Color;
end;

procedure TfrmStat.BitBtn1Click(Sender: TObject);
var
  Ext:String[4];
begin
  SavePictureDialog1.FilterIndex:=0;
  SavePictureDialog1.FileName:='DBChart';
  if SavePictureDialog1.Execute then
  begin
    case SavePictureDialog1.FilterIndex of
    2:SavePictureDialog1.FileName:=SavePictureDialog1.FileName+'.bmp';
    3:SavePictureDialog1.FileName:=SavePictureDialog1.FileName+'.emf';
    4:SavePictureDialog1.FileName:=SavePictureDialog1.FileName+'.wmf';
    end;
    Ext:=ExtractFileExt(SavePictureDialog1.FileName);
    Ext:=AnsiUpperCase(Ext);
    if Ext='.BMP' then
      DBChart1.SaveToBitmapFile(SavePictureDialog1.FileName)else
        if Ext='.EMF' then
          DBChart1.SaveToMetafileEnh(SavePictureDialog1.FileName)else
            if Ext='.WMF' then
              DBChart1.SaveToMetafile(SavePictureDialog1.FileName);
  end;
end;

procedure TfrmStat.FormCreate(Sender: TObject);
begin
  Query1.Close;
  Query1.SQL.Clear;
  Query1.SQL.Add('Select 类别,Count(类别)');
  Query1.SQL.Add('From '+#39+frmMain.tbBooks.TableName+#39);
  Query1.SQL.Add('Group By 类别');
  Query1.Open;
  Series1.DataSource:=Query1;
  Series1.PieValues.ValueSource:='COUNT OF 类别';
  Series1.XLabelsSource:='类别';
  Speed:=1;
end;

procedure TfrmStat.CheckBox3Click(Sender: TObject);
begin
  Series1.Circled:=CheckBox3.Checked;
end;

procedure TfrmStat.CheckBox4Click(Sender: TObject);
begin
  Timer1.Enabled:=CheckBox4.Checked;
  TrackBar1.Enabled:=CheckBox4.Checked;
end;

procedure TfrmStat.TrackBar1Change(Sender: TObject);
begin
  Speed:=TrackBar1.Position;
  Timer1.Interval:=101-TrackBar1.Position;
end;

procedure TfrmStat.Timer1Timer(Sender: TObject);
begin
  Series1.Rotate(Speed);
end;

end.
