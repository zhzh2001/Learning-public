object frmStat: TfrmStat
  Left = 432
  Top = 201
  Width = 979
  Height = 563
  Caption = #32479#35745
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
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object DBChart1: TDBChart
    Left = 0
    Top = 0
    Width = 971
    Height = 495
    AllowPanning = pmNone
    AllowZoom = False
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    BackWall.Pen.Visible = False
    PrintProportional = False
    Title.Text.Strings = (
      'TDBChart')
    Title.Visible = False
    AxisVisible = False
    ClipPoints = False
    Frame.Visible = False
    Legend.Visible = False
    View3DOptions.Elevation = 315
    View3DOptions.Orthogonal = False
    View3DOptions.Perspective = 0
    View3DOptions.Rotation = 360
    View3DWalls = False
    Align = alClient
    TabOrder = 0
    object Series1: TPieSeries
      Marks.ArrowLength = 8
      Marks.Style = smsLabelPercent
      Marks.Visible = True
      SeriesColor = clRed
      Circled = True
      ExplodeBiggest = 25
      OtherSlice.Text = 'Other'
      OtherSlice.Value = 12.000000000000000000
      PieValues.DateTime = False
      PieValues.Name = 'Pie'
      PieValues.Multiplier = 1.000000000000000000
      PieValues.Order = loAscending
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 495
    Width = 971
    Height = 41
    Align = alBottom
    TabOrder = 1
    DesignSize = (
      971
      41)
    object btnPreview: TBitBtn
      Left = 8
      Top = 8
      Width = 89
      Height = 25
      Caption = #25171#21360#39044#35272'&P'
      TabOrder = 0
      OnClick = btnPreviewClick
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00300000000000
        00033FFFFFFFFFFFFFFF0888888888888880777777777777777F088888888888
        8880777777777777777F0000000000000000FFFFFFFFFFFFFFFF0F8F8F8F8F8F
        8F80777777777777777F08F8F8F8F8F8F9F0777777777777777F0F8F8F8F8F8F
        8F807777777777777F7F0000000000000000777777777777777F3330FFFFFFFF
        03333337F3FFFF3F7F333330F0000F0F03333337F77773737F333330FFFFFFFF
        03333337F3FF3FFF7F333330F00F000003333337F773777773333330FFFF0FF0
        33333337F3FF7F3733333330F08F0F0333333337F7737F7333333330FFFF0033
        33333337FFFF7733333333300000033333333337777773333333}
      NumGlyphs = 2
    end
    object btnClose: TBitBtn
      Left = 120
      Top = 8
      Width = 75
      Height = 25
      Caption = #20851#38381'&C'
      TabOrder = 1
      Kind = bkClose
    end
    object CheckBox1: TCheckBox
      Left = 312
      Top = 12
      Width = 97
      Height = 17
      Caption = '3&D'
      Checked = True
      State = cbChecked
      TabOrder = 2
      OnClick = CheckBox1Click
    end
    object CheckBox2: TCheckBox
      Left = 376
      Top = 12
      Width = 97
      Height = 17
      Caption = #38543#26426#39068#33394'&R'
      Checked = True
      State = cbChecked
      TabOrder = 3
      OnClick = CheckBox2Click
    end
    object BitBtn1: TBitBtn
      Left = 216
      Top = 8
      Width = 75
      Height = 25
      Caption = #23548#20986'&E'
      TabOrder = 4
      OnClick = BitBtn1Click
      Glyph.Data = {
        76010000424D7601000000000000760000002800000020000000100000000100
        04000000000000010000130B0000130B00001000000000000000000000000000
        800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333303
        333333333333337FF3333333333333903333333333333377FF33333333333399
        03333FFFFFFFFF777FF3000000999999903377777777777777FF0FFFF0999999
        99037F3337777777777F0FFFF099999999907F3FF777777777770F00F0999999
        99037F773777777777730FFFF099999990337F3FF777777777330F00FFFFF099
        03337F773333377773330FFFFFFFF09033337F3FF3FFF77733330F00F0000003
        33337F773777777333330FFFF0FF033333337F3FF7F3733333330F08F0F03333
        33337F7737F7333333330FFFF003333333337FFFF77333333333000000333333
        3333777777333333333333333333333333333333333333333333}
      NumGlyphs = 2
    end
    object CheckBox3: TCheckBox
      Left = 472
      Top = 12
      Width = 97
      Height = 17
      Caption = #26174#31034#20026#22278#24418'&C'
      Checked = True
      State = cbChecked
      TabOrder = 5
      OnClick = CheckBox3Click
    end
    object CheckBox4: TCheckBox
      Left = 576
      Top = 12
      Width = 97
      Height = 17
      Caption = #21160#24577#26059#36716
      TabOrder = 6
      OnClick = CheckBox4Click
    end
    object TrackBar1: TTrackBar
      Left = 664
      Top = 8
      Width = 297
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      Enabled = False
      Max = 50
      Min = 1
      Position = 1
      TabOrder = 7
      TickStyle = tsManual
      OnChange = TrackBar1Change
    end
  end
  object ColorDialog1: TColorDialog
    Left = 472
    Top = 264
  end
  object SavePictureDialog1: TSavePictureDialog
    Filter = 
      #25152#26377#26684#24335' (*.bmp;*.emf;*.wmf)|*.bmp;*.emf;*.wmf|'#20301#22270#25991#20214' (*.bmp)|*.bmp|'#22686#24378 +
      #22270#20803#25991#20214' (*.emf)|*.emf|'#22270#20803#25991#20214' (*.wmf)|*.wmf'
    Left = 480
    Top = 272
  end
  object Query1: TQuery
    Left = 488
    Top = 280
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 496
    Top = 288
  end
end
