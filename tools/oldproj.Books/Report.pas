unit Report;

interface

uses
  SysUtils, Windows, Messages, Classes, Graphics, Controls,
  StdCtrls, ExtCtrls, Forms, QuickRpt, QRCtrls, DB, DBTables;

type
  TfrmReport = class(TForm)
    QuickRep1: TQuickRep;
    PageFooterBand1: TQRBand;
    QRExpr1: TQRExpr;
    ColumnHeaderBand1: TQRBand;
    DetailBand1: TQRBand;
    QRLabel1: TQRLabel;
    QRExpr2: TQRExpr;
    QRLabel2: TQRLabel;
    QRExpr3: TQRExpr;
    QRLabel3: TQRLabel;
    QRExpr4: TQRExpr;
    QRLabel4: TQRLabel;
    QRExpr5: TQRExpr;
    QRLabel5: TQRLabel;
    QRExpr6: TQRExpr;
    QRLabel6: TQRLabel;
    QRExpr7: TQRExpr;
    QRLabel7: TQRLabel;
    QRExpr8: TQRExpr;
    PageHeaderBand1: TQRBand;
    QRSysData1: TQRSysData;
  private
  end;

var
  frmReport: TfrmReport;

implementation

uses Main;

{$R *.DFM}

end.
