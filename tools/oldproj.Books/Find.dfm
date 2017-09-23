object frmFind: TfrmFind
  Left = 446
  Top = 248
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #22270#20070#26597#35810
  ClientHeight = 369
  ClientWidth = 420
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object cbName: TCheckBox
    Left = 8
    Top = 8
    Width = 57
    Height = 17
    Caption = #20070#21517#65306
    Checked = True
    State = cbChecked
    TabOrder = 0
    OnClick = cbNameClick
  end
  object cbNot1: TCheckBox
    Left = 64
    Top = 8
    Width = 49
    Height = 17
    Caption = #19981#26159
    TabOrder = 1
  end
  object cbStrOpration1: TComboBox
    Left = 112
    Top = 4
    Width = 49
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 2
    Text = #31867#20284
    Items.Strings = (
      #31867#20284
      #31561#20110)
  end
  object edtName: TEdit
    Left = 168
    Top = 4
    Width = 193
    Height = 21
    TabOrder = 3
  end
  object cbNumber: TCheckBox
    Left = 8
    Top = 32
    Width = 97
    Height = 17
    Caption = #32534#21495#65306
    TabOrder = 4
    OnClick = cbNumberClick
  end
  object cbNot2: TCheckBox
    Left = 64
    Top = 32
    Width = 49
    Height = 17
    Caption = #19981#26159
    TabOrder = 5
  end
  object cbIntOpration1: TComboBox
    Left = 112
    Top = 28
    Width = 49
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 6
    Text = #23567#20110
    Items.Strings = (
      #23567#20110
      #22823#20110
      #31561#20110
      #21306#38388)
  end
  object edtNumber: TEdit
    Left = 168
    Top = 28
    Width = 193
    Height = 21
    TabOrder = 7
  end
  object cbType: TCheckBox
    Left = 8
    Top = 56
    Width = 97
    Height = 17
    Caption = #31867#21035#65306
    TabOrder = 8
    OnClick = cbTypeClick
  end
  object cbNot3: TCheckBox
    Left = 64
    Top = 56
    Width = 49
    Height = 17
    Caption = #19981#26159
    TabOrder = 9
  end
  object cbStrOpration2: TComboBox
    Left = 112
    Top = 52
    Width = 49
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 10
    Text = #31867#20284
    Items.Strings = (
      #31867#20284
      #31561#20110)
  end
  object edtType: TEdit
    Left = 168
    Top = 52
    Width = 193
    Height = 21
    TabOrder = 11
  end
  object cbHand: TCheckBox
    Left = 8
    Top = 80
    Width = 97
    Height = 17
    Caption = #20316#32773#65306
    TabOrder = 12
    OnClick = cbHandClick
  end
  object cbNot4: TCheckBox
    Left = 64
    Top = 80
    Width = 49
    Height = 17
    Caption = #19981#26159
    TabOrder = 13
  end
  object cbStrOpration3: TComboBox
    Left = 112
    Top = 76
    Width = 49
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 14
    Text = #31867#20284
    Items.Strings = (
      #31867#20284
      #31561#20110)
  end
  object edtHand: TEdit
    Left = 168
    Top = 76
    Width = 193
    Height = 21
    TabOrder = 15
  end
  object cbHouse: TCheckBox
    Left = 8
    Top = 104
    Width = 97
    Height = 17
    Caption = #20986#29256#31038#65306
    TabOrder = 16
    OnClick = cbHouseClick
  end
  object cbNot5: TCheckBox
    Left = 80
    Top = 104
    Width = 49
    Height = 17
    Caption = #19981#26159
    TabOrder = 17
  end
  object cbStrOpration4: TComboBox
    Left = 128
    Top = 100
    Width = 49
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 18
    Text = #31867#20284
    Items.Strings = (
      #31867#20284
      #31561#20110)
  end
  object edtHouse: TEdit
    Left = 184
    Top = 100
    Width = 177
    Height = 21
    TabOrder = 19
  end
  object cbPrice: TCheckBox
    Left = 8
    Top = 128
    Width = 97
    Height = 17
    Caption = #20215#26684#65306
    TabOrder = 20
  end
  object cbNot6: TCheckBox
    Left = 64
    Top = 128
    Width = 49
    Height = 17
    Caption = #19981#26159
    TabOrder = 21
  end
  object cbIntOpration2: TComboBox
    Left = 112
    Top = 124
    Width = 49
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 22
    Text = #23567#20110
    Items.Strings = (
      #23567#20110
      #22823#20110
      #31561#20110
      #21306#38388)
  end
  object edtPrice: TEdit
    Left = 168
    Top = 124
    Width = 193
    Height = 21
    TabOrder = 23
  end
  object cbOpration1: TComboBox
    Left = 368
    Top = 4
    Width = 49
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 24
    Text = #24182#19988
    Items.Strings = (
      #24182#19988
      #25110#32773)
  end
  object cbOpration2: TComboBox
    Left = 368
    Top = 28
    Width = 49
    Height = 21
    Style = csDropDownList
    Enabled = False
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 25
    Text = #24182#19988
    Items.Strings = (
      #24182#19988
      #25110#32773)
  end
  object cbOpration3: TComboBox
    Left = 368
    Top = 52
    Width = 49
    Height = 21
    Style = csDropDownList
    Enabled = False
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 26
    Text = #24182#19988
    Items.Strings = (
      #24182#19988
      #25110#32773)
  end
  object cbOpration4: TComboBox
    Left = 368
    Top = 76
    Width = 49
    Height = 21
    Style = csDropDownList
    Enabled = False
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 27
    Text = #24182#19988
    Items.Strings = (
      #24182#19988
      #25110#32773)
  end
  object cbOpration5: TComboBox
    Left = 368
    Top = 100
    Width = 49
    Height = 21
    Style = csDropDownList
    Enabled = False
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 28
    Text = #24182#19988
    Items.Strings = (
      #24182#19988
      #25110#32773)
  end
  object cbFilter: TComboBox
    Left = 8
    Top = 152
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 29
    Text = #25152#26377#22270#20070
    Items.Strings = (
      #25152#26377#22270#20070
      #22312#26550#22270#20070
      #20511#20986#22270#20070
      #20002#22833#22270#20070)
  end
  object btnFind: TBitBtn
    Left = 160
    Top = 152
    Width = 75
    Height = 25
    Caption = #26597#35810'&F'
    TabOrder = 30
    OnClick = btnFindClick
    Glyph.Data = {
      76010000424D7601000000000000760000002800000020000000100000000100
      04000000000000010000130B0000130B00001000000000000000000000000000
      800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      333333333333333333FF33333333333330003FF3FFFFF3333777003000003333
      300077F777773F333777E00BFBFB033333337773333F7F33333FE0BFBF000333
      330077F3337773F33377E0FBFBFBF033330077F3333FF7FFF377E0BFBF000000
      333377F3337777773F3FE0FBFBFBFBFB039977F33FFFFFFF7377E0BF00000000
      339977FF777777773377000BFB03333333337773FF733333333F333000333333
      3300333777333333337733333333333333003333333333333377333333333333
      333333333333333333FF33333333333330003333333333333777333333333333
      3000333333333333377733333333333333333333333333333333}
    NumGlyphs = 2
  end
  object btnClose: TBitBtn
    Left = 336
    Top = 152
    Width = 75
    Height = 25
    Caption = #20851#38381'&C'
    TabOrder = 31
    Kind = bkClose
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 183
    Width = 420
    Height = 186
    Align = alBottom
    Caption = #32467#26524
    TabOrder = 32
    object DBGrid1: TDBGrid
      Left = 2
      Top = 15
      Width = 416
      Height = 169
      Align = alClient
      DataSource = DataSource1
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
    end
  end
  object qrBooks: TQuery
    Left = 200
    Top = 184
  end
  object DataSource1: TDataSource
    DataSet = qrBooks
    Left = 208
    Top = 192
  end
end
