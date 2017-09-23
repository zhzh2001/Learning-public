object frmDelete: TfrmDelete
  Left = 1132
  Top = 553
  Width = 294
  Height = 117
  BorderIcons = [biSystemMenu]
  Caption = #21024#38500#29992#25143
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 286
    Height = 50
    Align = alTop
    Caption = #29992#25143#21015#34920
    TabOrder = 0
    object edtUser: TComboBox
      Left = 8
      Top = 20
      Width = 273
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = edtUserChange
    end
  end
  object btnOK: TBitBtn
    Left = 109
    Top = 58
    Width = 75
    Height = 25
    Caption = #21024#38500'&D'
    TabOrder = 1
    OnClick = btnOKClick
    Kind = bkOK
  end
  object btnCancel: TBitBtn
    Left = 205
    Top = 58
    Width = 75
    Height = 25
    Caption = #21462#28040'&C'
    TabOrder = 2
    OnClick = btnCancelClick
    Kind = bkCancel
  end
end
