object frmEdit: TfrmEdit
  Left = 446
  Top = 246
  Width = 979
  Height = 563
  Caption = #22270#20070#32534#36753
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object DBGrid1: TDBGrid
    Left = 0
    Top = 0
    Width = 704
    Height = 536
    Align = alClient
    DataSource = DataSource1
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgCancelOnExit]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnKeyPress = DBGrid1KeyPress
    Columns = <
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = #32534#21495
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = #31867#21035
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = #20070#21517
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = #20316#32773
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = #20986#29256#31038
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = #29256#27425
        Visible = True
      end
      item
        ButtonStyle = cbsNone
        Expanded = False
        FieldName = #20215#26684
        Visible = True
      end
      item
        Expanded = False
        FieldName = #22312#26550#24773#20917
        PickList.Strings = (
          #22312#26550
          #20511#20986
          #20002#22833)
        Visible = True
      end>
  end
  object Panel1: TPanel
    Left = 704
    Top = 0
    Width = 267
    Height = 536
    Align = alRight
    TabOrder = 1
    object DBNavigator1: TDBNavigator
      Left = 1
      Top = 510
      Width = 265
      Height = 25
      DataSource = DataSource1
      Align = alBottom
      Flat = True
      Hints.Strings = (
        #39318#26465
        #19978#19968#26465
        #19979#19968#26465
        #26411#26465
        #25554#20837
        #21024#38500
        #32534#36753
        #20445#23384
        #21462#28040
        #21047#26032)
      ConfirmDelete = False
      TabOrder = 0
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 265
      Height = 509
      Align = alClient
      Caption = #22791#27880
      TabOrder = 1
      object DBMemo1: TDBMemo
        Left = 2
        Top = 15
        Width = 261
        Height = 492
        Align = alClient
        DataField = #22791#27880
        DataSource = DataSource1
        TabOrder = 0
      end
    end
  end
  object DataSource1: TDataSource
    DataSet = frmMain.tbBooks
    Left = 472
    Top = 264
  end
end
