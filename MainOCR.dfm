object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'OCR'
  ClientHeight = 507
  ClientWidth = 1031
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 72
    Top = 24
    Width = 160
    Height = 160
    OnMouseMove = Image1MouseMove
  end
  object Image2: TImage
    Left = 576
    Top = 24
    Width = 160
    Height = 160
  end
  object Label1: TLabel
    Left = 440
    Top = 32
    Width = 31
    Height = 13
    Caption = 'Label1'
  end
  object ClearButton: TButton
    Left = 280
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 0
    OnClick = ClearButtonClick
  end
  object TransformButton: TButton
    Left = 280
    Top = 80
    Width = 75
    Height = 25
    Caption = 'Transform'
    TabOrder = 1
    OnClick = TransformButtonClick
  end
  object StringGrid1: TStringGrid
    Left = 232
    Top = 120
    Width = 345
    Height = 345
    ColCount = 16
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 16
    FixedRows = 0
    TabOrder = 2
  end
  object SaveXMLButton: TButton
    Left = 480
    Top = 80
    Width = 75
    Height = 25
    Caption = 'SaveXML'
    TabOrder = 3
    OnClick = SaveXMLButtonClick
  end
  object Edit1: TEdit
    Left = 433
    Top = 82
    Width = 41
    Height = 21
    MaxLength = 1
    TabOrder = 4
    TextHint = 'Letter'
  end
  object CheckButton: TButton
    Left = 480
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Check'
    TabOrder = 5
    OnClick = CheckButtonClick
  end
  object XMLDocument1: TXMLDocument
    FileName = 
      'C:\Users\xFiLiNx\Documents\Embarcadero\Studio\Projects\OCR\Untit' +
      'led1.xml'
    NodeIndentStr = '    '
    Left = 824
    Top = 96
    DOMVendorDesc = 'MSXML'
  end
end