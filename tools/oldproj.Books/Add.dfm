object frmAdd: TfrmAdd
  Left = 1096
  Top = 553
  Width = 344
  Height = 197
  BorderIcons = [biSystemMenu]
  Caption = #28155#21152#29992#25143
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
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 336
    Height = 129
    Align = alTop
    Caption = #29992#25143#20449#24687
    TabOrder = 0
    object lbUser: TLabel
      Left = 16
      Top = 32
      Width = 49
      Height = 13
      AutoSize = False
      Caption = #29992#25143'(&U):'
    end
    object lbPassword: TLabel
      Left = 16
      Top = 64
      Width = 49
      Height = 13
      AutoSize = False
      Caption = #23494#30721'(&P):'
      FocusControl = edtPassword
    end
    object Label1: TLabel
      Left = 16
      Top = 96
      Width = 49
      Height = 13
      AutoSize = False
      Caption = #26435#38480'(&T):'
      FocusControl = edtPassword
    end
    object edtPassword: TEdit
      Left = 72
      Top = 60
      Width = 249
      Height = 21
      PasswordChar = '*'
      TabOrder = 1
    end
    object edtToken: TComboBox
      Left = 72
      Top = 92
      Width = 249
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 2
      Text = #26222#36890#29992#25143
      Items.Strings = (
        #26222#36890#29992#25143
        #36229#32423#29992#25143
        #31649#29702#21592)
    end
    object edtUser: TEdit
      Left = 72
      Top = 28
      Width = 249
      Height = 21
      TabOrder = 0
    end
  end
  object btnOK: TBitBtn
    Left = 160
    Top = 136
    Width = 75
    Height = 25
    Caption = #30830#23450'&O'
    TabOrder = 1
    OnClick = btnOKClick
    Kind = bkOK
  end
  object btnCancel: TBitBtn
    Left = 256
    Top = 136
    Width = 75
    Height = 25
    Caption = #21462#28040'&C'
    TabOrder = 2
    OnClick = btnCancelClick
    Kind = bkCancel
  end
end
