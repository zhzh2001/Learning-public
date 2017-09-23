unit Find;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, DB, DBTables, Grids, DBGrids;

type
  TfrmFind = class(TForm)
    cbName: TCheckBox;
    cbNot1: TCheckBox;
    cbStrOpration1: TComboBox;
    edtName: TEdit;
    cbNumber: TCheckBox;
    cbNot2: TCheckBox;
    cbIntOpration1: TComboBox;
    edtNumber: TEdit;
    cbType: TCheckBox;
    cbNot3: TCheckBox;
    cbStrOpration2: TComboBox;
    edtType: TEdit;
    cbHand: TCheckBox;
    cbNot4: TCheckBox;
    cbStrOpration3: TComboBox;
    edtHand: TEdit;
    cbHouse: TCheckBox;
    cbNot5: TCheckBox;
    cbStrOpration4: TComboBox;
    edtHouse: TEdit;
    cbPrice: TCheckBox;
    cbNot6: TCheckBox;
    cbIntOpration2: TComboBox;
    edtPrice: TEdit;
    cbOpration1: TComboBox;
    cbOpration2: TComboBox;
    cbOpration3: TComboBox;
    cbOpration4: TComboBox;
    cbOpration5: TComboBox;
    cbFilter: TComboBox;
    btnFind: TBitBtn;
    btnClose: TBitBtn;
    GroupBox1: TGroupBox;
    qrBooks: TQuery;
    DataSource1: TDataSource;
    DBGrid1: TDBGrid;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure cbNameClick(Sender: TObject);
    procedure cbNumberClick(Sender: TObject);
    procedure cbTypeClick(Sender: TObject);
    procedure cbHandClick(Sender: TObject);
    procedure cbHouseClick(Sender: TObject);
    procedure btnFindClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmFind: TfrmFind;

implementation

uses Main;

{$R *.dfm}

procedure TfrmFind.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action:=caFree;
end;

procedure TfrmFind.cbNameClick(Sender: TObject);
begin
  cbOpration1.Enabled:=cbName.Checked;
end;

procedure TfrmFind.cbNumberClick(Sender: TObject);
begin
  cbOpration2.Enabled:=cbNumber.Checked;
end;

procedure TfrmFind.cbTypeClick(Sender: TObject);
begin
  cbOpration3.Enabled:=cbType.Checked;
end;

procedure TfrmFind.cbHandClick(Sender: TObject);
begin
  cbOpration4.Enabled:=cbHand.Checked;
end;

procedure TfrmFind.cbHouseClick(Sender: TObject);
begin
  cbOpration5.Enabled:=cbHouse.Checked;
end;

procedure TfrmFind.btnFindClick(Sender: TObject);
var
  s:string;
  i,len:Integer;
begin
  if qrBooks.Active then
    qrBooks.Close;
  qrBooks.SQL.Clear;
  qrBooks.SQL.Add('SELECT *');
  qrBooks.SQL.Add('FROM '+#39+frmMain.tbBooks.TableName+#39);
  s:='WHERE ';

  if cbName.Checked then
  begin
    if cbNot1.Checked then
      s:=s+'NOT ';
    s:=s+'书名';
    case cbStrOpration1.ItemIndex of
    0:s:=s+' LIKE '+#39+'%'+edtName.Text+'%'+#39;
    1:s:=s+'='+#39+edtName.Text+#39;
    end;
    case cbOpration1.ItemIndex of
    0:s:=s+' AND ';
    1:s:=s+' OR ';
    end;
  end;

  if cbNumber.Checked then
  begin
    if cbNot2.Checked then
      s:=s+'NOT ';
    s:=s+'编号';
    case cbIntOpration1.ItemIndex of
    0:s:=s+'<'+edtNumber.Text;
    1:s:=s+'>'+edtNumber.Text;
    2:s:=s+'='+edtNumber.Text;
    3:begin
        len:=Length(edtNumber.Text);
        for i:=1 to len do
          if(edtNumber.Text[i]>'9')or(edtNumber.Text[i]<'0')then
            Break;
        s:=s+' BETWEEN '+Copy(edtNumber.Text,1,i-1)+' AND '+Copy(edtNumber.Text,i+1,len-i);
      end;
    end;
    case cbOpration2.ItemIndex of
    0:s:=s+' AND ';
    1:s:=s+' OR ';
    end;
  end;

  if cbType.Checked then
  begin
    if cbNot3.Checked then
      s:=s+'NOT ';
    s:=s+'类别';
    case cbStrOpration2.ItemIndex of
    0:s:=s+' LIKE'+#39+'%'+edtType.Text+'%'+#39;
    1:s:=s+'='+#39+edtType.Text+#39;
    end;
    case cbOpration3.ItemIndex of
    0:s:=s+' AND ';
    1:s:=s+' OR ';
    end;
  end;

  if cbHand.Checked then
  begin
    if cbNot4.Checked then
      s:=s+'NOT ';
    s:=s+'作者';
    case cbStrOpration3.ItemIndex of
    0:s:=s+' LIKE'+#39+'%'+edtHand.Text+'%'+#39;
    1:s:=s+'='+#39+edtHand.Text+#39;
    end;
    case cbOpration4.ItemIndex of
    0:s:=s+' AND ';
    1:s:=s+' OR ';
    end;
  end;

  if cbHouse.Checked then
  begin
    if cbNot5.Checked then
      s:=s+'NOT ';
    s:=s+'出版社';
    case cbStrOpration4.ItemIndex of
    0:s:=s+' LIKE'+#39+'%'+edtHouse.Text+'%'+#39;
    1:s:=s+'='+#39+edtHouse.Text+#39;
    end;
    case cbOpration5.ItemIndex of
    0:s:=s+' AND ';
    1:s:=s+' OR ';
    end;
  end;

  if cbPrice.Checked then
  begin
    if cbNot6.Checked then
      s:=s+'NOT ';
    s:=s+'价格';
    case cbIntOpration2.ItemIndex of
    0:s:=s+'<'+edtPrice.Text;
    1:s:=s+'>'+edtPrice.Text;
    2:s:=s+'='+edtPrice.Text;
    3:begin
        len:=Length(edtPrice.Text);
        for i:=1 to len do
          if(edtPrice.Text[i]>'9')or(edtPrice.Text[i]<'0')then
            Break;
        s:=s+' BETWEEN '+Copy(edtPrice.Text,1,i-1)+' AND '+Copy(edtPrice.Text,i+1,len-i);
      end;
    end;
  end;

  len:=Length(s);
  if Copy(s,len-3,4)='AND 'then
    Delete(s,len-3,4) else
      if Copy(s,len-2,3)='OR 'then
        Delete(s,len-2,3);
  case cbFilter.ItemIndex of
  1:s:=s+'AND 在架情况='+#39+'在架'+#39;
  2:s:=s+'AND 在架情况='+#39+'借出'+#39;
  3:s:=s+'AND 在架情况='+#39+'丢失'+#39;
  end;
  if Copy(s,7,4)='AND 'then
    Delete(s,7,4);

  if s<>'WHERE ' then
    qrBooks.SQL.Add(s);
  qrBooks.Open;
end;

end.
