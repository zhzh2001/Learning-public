object frmMain: TfrmMain
  Left = 192
  Top = 107
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #23433#35013#23478#24237#22270#20070#31649#29702#31995#32479
  ClientHeight = 125
  ClientWidth = 492
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 40
    Top = 16
    Width = 81
    Height = 13
    AutoSize = False
    Caption = #31243#24207#39033#21517#31216':'
  end
  object imgLogo: TImage
    Left = 8
    Top = 16
    Width = 32
    Height = 32
    AutoSize = True
    Picture.Data = {
      055449636F6E0000010001002020040000000000E80200001600000028000000
      2000000040000000010004000000000000020000000000000000000000000000
      0000000000000000000080000080000000808000800000008000800080800000
      80808000C0C0C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000
      FFFFFF000000000330310110000000000000000000000000BB31311110000000
      00000000000000000B33131000000000000000000000000000B3131000000000
      000000000000000000B3131000000000000000000000000000B3131000000000
      000000000000000000BB3130000000000000000000000000000B313000000000
      0000000000000000000B3130000000000000000000000000000B313000000000
      0000000000000000000B31300000000000000000000000000003313000000000
      0000000000000000000133110000000000000000000000000013333100000000
      0000000000000000013B313111100000000000000000000013B0310313310000
      00000000000022013B03331031B330000200000000200202B003B310B30B3100
      2000000000022022203B0B300B00B0020220222002202222222222B200022B22
      222222200222222002222222220222222222A2000222222222AA22A222222222
      22222200022222222022AA2222222222222A2200022222222222222222222222
      222220000A222AA222222222222A222222222A0000A22222A2222222AA222222
      2222A000000A2222AAAA22222222222222A000000000A2222222222222222222
      220000000000A0222222222222AAA222AA0000000000000AA22AAA222A000AAA
      00000000000000000AA00002A000000000000000000000000000000000000000
      00000000FC003FFFFE003FFFFF007FFFFF80FFFFFF80FFFFFF80FFFFFF80FFFF
      FFC0FFFFFFC0FFFFFFC0FFFFFFC0FFFFFFC0FFFFFFC07FFFF8801FFFF000033F
      C000001F80000001000000000000000000000000000000010000000100000001
      000000030000000180000003C0000007E000001FE000001FF400001FFE0038FF
      FF9C7FFF}
  end
  object Label2: TLabel
    Left = 40
    Top = 40
    Width = 65
    Height = 13
    AutoSize = False
    Caption = #23433#35013#30446#24405':'
  end
  object Label3: TLabel
    Left = 8
    Top = 64
    Width = 65
    Height = 13
    AutoSize = False
    Caption = #24403#21069#27493#39588':'
  end
  object Bevel1: TBevel
    Left = 8
    Top = 80
    Width = 473
    Height = 10
    Shape = bsBottomLine
  end
  object edtName: TEdit
    Left = 120
    Top = 12
    Width = 337
    Height = 21
    TabOrder = 0
    Text = #23478#24237#22270#20070#31649#29702#31995#32479
  end
  object edtPath: TEdit
    Left = 104
    Top = 36
    Width = 353
    Height = 21
    TabOrder = 1
  end
  object btnBrowse: TButton
    Left = 456
    Top = 32
    Width = 25
    Height = 25
    Caption = '...'
    TabOrder = 2
    OnClick = btnBrowseClick
  end
  object btnInstall: TBitBtn
    Left = 312
    Top = 96
    Width = 75
    Height = 25
    Caption = #23433#35013'&I'
    TabOrder = 3
    OnClick = btnInstallClick
    Kind = bkOK
  end
  object btnCancel: TBitBtn
    Left = 400
    Top = 96
    Width = 75
    Height = 25
    Caption = #21462#28040'&C'
    Enabled = False
    TabOrder = 4
    OnClick = btnCancelClick
    Kind = bkCancel
  end
  object edtStep: TEdit
    Left = 72
    Top = 64
    Width = 417
    Height = 21
    BorderStyle = bsNone
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 5
  end
end
