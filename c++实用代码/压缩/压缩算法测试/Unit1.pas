//
//�������������
//���ߣ�ҶҶ��2010��8��30��
//
//���ļ���Ȩ��ҶҶӵ�У���������Ȩ����
//���ļ��еĴ�������ѳ��������κ���Ȩ����ɼ������ڸ��˺���ҵĿ�ġ�ʹ����һ�к���Ը���
//
//�����ת���˱��ļ��еĴ��룬��ע����������ʹ������ߣ�
//������޸��˱��ļ��еĴ��룬��ע���޸�λ�ú��޸����ߣ�
//
//���ļ������ġ���������㷨�ķ�����ʵ�֡������׳���
//���ļ�������http://programbbs.com/bbs/�Ϸ�����
//

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls,

  MemoryBuffer, CanonicalHuffman, RangeCoding, ArithmeticCoding;

type
  TForm1 = class(TForm)
    Panel1: TPanel;
    Memo1: TMemo;
    Edit1: TEdit;
    Edit2: TEdit;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    Button1: TButton;
    ComboBox1: TComboBox;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    procedure Edit1DblClick(Sender: TObject);
    procedure Edit2DblClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
  private
    FHaveError : Boolean; //�Ƚ��ļ�ʱ���Ƿ��д���
    FInSize : Integer; //�������ݴ�С
    FOutSize : Integer; //������ݴ�С
    FTime : Cardinal; //��ʱ
  public
    procedure OutRadio;

    procedure PackCanHuf8;
    procedure UnpackCanHuf8;

    procedure PackRange;
    procedure UnpackRange;

    procedure PackArithmetic;
    procedure UnpackArithmetic;

  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

//��������ļ���
procedure TForm1.Edit1DblClick(Sender: TObject);
begin
    if self.OpenDialog1.Execute then
    begin
        self.Edit1.Text:=self.OpenDialog1.FileName;
    end;
end;

//�������ļ���
procedure TForm1.Edit2DblClick(Sender: TObject);
begin
    if self.SaveDialog1.Execute then
    begin
        self.Edit2.Text:=self.SaveDialog1.FileName;
    end;
end;

//ѹ����
//���ݵ�ǰ���㷨���ã�������صĺ�������ѹ��������
//��Edit1��Ӧ���ļ�ѹ�����浽Edit2��Ӧ���ļ��С�
procedure TForm1.Button1Click(Sender: TObject);
begin
    case self.ComboBox1.ItemIndex of
        0 : self.PackCanHuf8;
        1 : self.PackRange;
        2 : self.PackArithmetic;
    end;
end;

//��ѹ����
//���ݵ�ǰ���㷨���ã�������صĺ������н�ѹ��������
//��Edit1��Ӧ���ļ���ѹ�����浽Edit2��Ӧ���ļ��С�
procedure TForm1.Button2Click(Sender: TObject);
begin
    case self.ComboBox1.ItemIndex of
        0 : self.UnpackCanHuf8;
        1 : self.UnpackRange;
        2 : self.UnpackArithmetic;
    end;
end;

//�ļ��Ƚϣ�
//��Edit1��Ӧ���ļ���Edit2��Ӧ���ļ����бȽϣ���������Memo1�У�
//�ȽϽ���������FHaveError��
procedure TForm1.Button3Click(Sender: TObject);
var
    s1,s2 : TFileStream;
    l1,l2,i : Integer;
    m1,m2 : Pointer;
    d1,d2 : PByte;
    b : Boolean;
begin
    self.FHaveError:=False;

    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('�Ƚ��ļ���');
    self.Memo1.Lines.Add(self.Edit1.Text);
    self.Memo1.Lines.Add(self.Edit2.Text);
    s1:=TFileStream.Create(self.Edit1.Text,fmOpenRead);
    s2:=TFileStream.Create(self.Edit2.Text,fmOpenRead);
    l1:=s1.Size;
    l2:=s2.Size;

    if l1<>l2 then
    begin
        self.Memo1.Lines.Add(Format('����%d��%d��һ�£�',[l1,l2]));
        self.FHaveError:=True;
        if l1>l2 then l1:=l2;
    end;

    GetMem(m1,l1); s1.Read(m1^,l1); s1.Free; d1:=m1;
    GetMem(m2,l1); s2.Read(m2^,l1); s2.Free; d2:=m2;

    b:=True;
    for i:=0 to l1-1 do
    begin
        if d1^<>d2^ then
        begin
            b:=False;
            self.FHaveError:=True;
            self.Memo1.Lines.Add(Format(
                '��%dλ�ò�һ�£�$%.2x<>$%.2x��',
                [i,d1^,d2^]));
            break;
        end;
        Inc(d1); Inc(d2);
    end;
    if b then self.Memo1.Lines.Add(Format('����%d�ֽڣ��Ƚ�һ�¡�',[l1]));
    
    FreeMem(m1);
    FreeMem(m2);
end;

//�������ԣ�
//��Edit1��Ӧ���ļ����µ������ļ������ݵ�ǰ���㷨���ã����в��ԣ�
//���ļ�ѹ����һ��ʱ�ļ��У��ٽ�ѹ������һ��ʱ�ļ������ȽϽ����
//�����ļ��������֮��ͳ�Ʋ���Memo1����������
procedure TForm1.Button4Click(Sender: TObject);
var
    Find : THandle;
    FindData : TWIN32FindData;

    DirName,OutDir,FileName,PackFile,DataFile,OutText,s : String;
    FileList : TStringList;
    b : Boolean;

    Infos : array of array [0..6] of String;
    InfoLen : array [0..6] of Integer;
    InCount,OutCount : Int64;

    i,n,l : Integer;
begin
    self.Button1.Enabled:=False;
    self.Button2.Enabled:=False;
    self.Button3.Enabled:=False;
    self.Button4.Enabled:=False;

    //ȷ���ļ���
    DirName:=self.Edit1.Text;
    if DirName[Length(DirName)]<>'\' then DirName:=DirName+'\';
    if not DirectoryExists(DirName) then
    begin
        self.Memo1.Lines.Add('');
        self.Memo1.Lines.Add('�����ļ���û���ҵ���');
        self.Memo1.Lines.Add(DirName);
        self.Button1.Enabled:=True;
        self.Button2.Enabled:=True;
        self.Button3.Enabled:=True;
        self.Button4.Enabled:=True;
        exit;
    end;

    OutDir:=self.Edit2.Text;
    if OutDir[Length(OutDir)]<>'\' then OutDir:=OutDir+'\';
    if not DirectoryExists(OutDir) then
    begin
        self.Memo1.Lines.Add('');
        self.Memo1.Lines.Add('�����ļ���û���ҵ���');
        self.Memo1.Lines.Add(OutDir);
        self.Button1.Enabled:=True;
        self.Button2.Enabled:=True;
        self.Button3.Enabled:=True;
        self.Button4.Enabled:=True;
        exit;
    end;

    //�����ļ�
    FileName:=DirName+'*';

    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('�������������ļ����е������ļ���');
    self.Memo1.Lines.Add(DirName);

    FileList:=TStringList.Create;

    Find:=FindFirstFile(PChar(FileName),FindData);
    b:=Find<>INVALID_HANDLE_VALUE;

    while b do
    begin
        if ((FindData.dwFileAttributes and FILE_ATTRIBUTE_DIRECTORY)=0) and
           (FindData.nFileSizeLow<>0) then
        begin
            //��¼�ǿ��ļ�
            FileList.Add(FindData.cFileName);
        end;
        b:=FindNextFile(Find,FindData);
    end;

    Windows.FindClose(Find);

    if FileList.Count=0 then
    begin
        self.Memo1.Lines.Add('�ļ�����û���ҵ��ļ������Խ�����');
        FileList.Free;
        self.Button1.Enabled:=True;
        self.Button2.Enabled:=True;
        self.Button3.Enabled:=True;
        self.Button4.Enabled:=True;
        exit;
    end
    else
    begin
        self.Memo1.Lines.Add('');
        self.Memo1.Lines.Add(Format('����%d���ļ������Կ�ʼ...',[FileList.Count]));
    end;

    //��ʼ����
    PackFile:=OutDir+'_Temp.pack'; //ѹ������ļ�
    DataFile:=OutDir+'_Temp.data'; //��ѹ������ļ�

    SetLength(Infos,FileList.Count);

    InCount:=0;
    OutCount:=0;

    for i:=0 to FileList.Count-1 do
    begin
        //�ļ���
        FileName:=FileList[i];
        Infos[i][0]:=FileName;

        //ѹ��
        self.Caption:='ѹ�����ԣ�'+FileName;
        Application.Title:=self.Caption;

        self.Edit1.Text:=DirName+FileName;
        self.Edit2.Text:=PackFile;
        self.Button1Click(self);

        //�����С
        Infos[i][1]:=Format('%dB',[self.FInSize]);
        Inc(InCount,self.FInSize);

        //�����С
        Infos[i][2]:=Format('%dB',[self.FOutSize]);
        Inc(OutCount,self.FOutSize);

        //ѹ����
        Infos[i][3]:=Format('%d��',[
            ((self.FInSize-self.FOutSize)*100) div self.FInSize]);

        //bpc
        Infos[i][4]:=Format('%1.3fbpc',[
            (self.FOutSize*8)/self.FInSize]);

        //����ʱ��
        Infos[i][5]:=Format('%dms',[self.FTime]);

        //��ѹ��
        self.Caption:='��ѹ���ԣ�'+FileName;
        Application.Title:=self.Caption;

        self.Edit1.Text:=PackFile;
        self.Edit2.Text:=DataFile;
        self.Button2Click(self);

        //�ļ��Ƚ�
        self.Caption:='�ļ��Ƚϣ�'+FileName;
        Application.Title:=self.Caption;

        self.FHaveError:=False;

        self.Edit1.Text:=DirName+FileName;
        self.Edit2.Text:=DataFile;
        self.Button3Click(self);

        //����ʱ��
        if self.FHaveError then
        begin
            Infos[i][6]:='�������';
        end
        else
        begin
            Infos[i][6]:=Format('%dms',[self.FTime]);
        end;
    end;

    //��������
    for n:=0 to 6 do InfoLen[n]:=0;

    for i:=0 to FileList.Count-1 do
    begin
        for n:=0 to 6 do
        begin
            l:=Length(Infos[i][n]);
            if l>InfoLen[n] then InfoLen[n]:=l;
        end;
    end;

    for n:=1 to 6 do Inc(InfoLen[n]);

    //���������Ϣ
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add(self.ComboBox1.Text+'���������Խ�����£�');
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('�ļ��� �����С �����С ѹ���� bpc �����ʱ �����ʱ');
    self.Memo1.Lines.Add('');

    for i:=0 to FileList.Count-1 do
    begin
        OutText:=Infos[i][0];
        l:=Length(OutText);
        while l<InfoLen[0] do
        begin
            OutText:=OutText+' '; Inc(l);
        end;
        for n:=1 to 6 do
        begin
            s:=Infos[i][n];
            l:=Length(s);
            while l<InfoLen[n] do
            begin
                s:=' '+s; Inc(l);
            end;
            OutText:=OutText+s;
        end;

        self.Memo1.Lines.Add(OutText);
    end;

    //���������С�ܼ�
    Infos[0][0]:='�ܼ� ';
    Infos[1][0]:='     ';
    Infos[2][0]:='     ';

    Infos[0][1]:='�����С��';
    Infos[1][1]:='�����С��';
    Infos[2][1]:='ѹ���ʣ�';

    Infos[0][2]:=Format('%dB',[InCount]);
    Infos[1][2]:=Format('%dB',[OutCount]);
    Infos[2][2]:=Format('%d�� %1.3fbpc',[
        ((InCount-OutCount)*100) div InCount,
        (OutCount*8)/InCount]);

    InfoLen[2]:=0;
    for i:=0 to 2 do
    begin
        l:=Length(Infos[i][2]);
        if l>InfoLen[2] then InfoLen[2]:=l;
    end;
    Inc(InfoLen[2]);

    self.Memo1.Lines.Add('');
    for i:=0 to 2 do
    begin
        s:=Infos[i][0];
        l:=Length(s);
        while l<InfoLen[0] do
        begin
            s:=s+' '; Inc(l);
        end;
        OutText:=s;

        s:=Infos[i][1];
        l:=Length(s);
        while l<InfoLen[1] do
        begin
            s:=s+' '; Inc(l);
        end;
        OutText:=OutText+s;

        s:=Infos[i][2];
        l:=Length(s);
        while l<InfoLen[2] do
        begin
            s:=' '+s; Inc(l);
        end;
        OutText:=OutText+s;

        self.Memo1.Lines.Add(OutText);
    end;

    self.Caption:='�����������';
    Application.Title:=self.Caption;
    self.Edit1.Text:=DirName;
    self.Edit2.Text:=OutDir;

    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('����������ɡ�');

    FileList.Free;
    self.Button1.Enabled:=True;
    self.Button2.Enabled:=True;
    self.Button3.Enabled:=True;
    self.Button4.Enabled:=True;

    //���
end;

//�����Ϣ��
procedure TForm1.Button5Click(Sender: TObject);
begin
    self.Memo1.Lines.Clear;
end;

//�����ǰ��ѹ���ʡ�
procedure TForm1.OutRadio;
begin
    self.Memo1.Lines.Add(Format('������ɣ���ʱ��%d',[self.FTime]));
    self.Memo1.Lines.Add(Format('ѹ��ǰ��%d �ֽ�',[self.FInSize]));
    self.Memo1.Lines.Add(Format('ѹ����%d �ֽ�',[self.FOutSize]));
    self.Memo1.Lines.Add(Format('ѹ���ʣ�%d�� %1.3fbpc',[
        ((self.FInSize-self.FOutSize)*100) div self.FInSize,
        (self.FOutSize*8)/self.FInSize]));
end;

//��ʽ�������㷨��8λ���ţ���
//��Edit1��Ӧ���ļ�ѹ�����浽Edit2��Ӧ���ļ��У�
//ͬʱ��¼�����С�������С���㷨��ʱ��
procedure TForm1.PackCanHuf8;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TCHCoding;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('ʹ�÷�ʽ�������㷨ѹ����8λ���ţ�...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('�ӣ�'+InFile);
    self.Memo1.Lines.Add('����'+OutFile);

    //����������
    MBInit(InBuf);
    MBInit(OutBuf);

    self.FInSize:=MBLoadFromFile(InBuf,InFile);

    //����������
    Coding:=TCHCoding.Create;

    //��ʱ
    self.FTime:=GetTickCount;

    self.FOutSize:=Coding.Encode(InBuf,OutBuf,self.FInSize);

    //ѹ�����
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //��������
    MBSaveToFile(OutBuf,self.FOutSize,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //�������
    self.OutRadio;

    //���
end;

//��ʽ�������㷨��8λ���ţ���
//��Edit1��Ӧ���ļ���ѹ�����浽Edit2��Ӧ���ļ��У�
//ͬʱ��¼�㷨��ʱ��
procedure TForm1.UnpackCanHuf8;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TCHCoding;

    Size : Integer;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('ʹ�÷�ʽ�������㷨��ѹ����8λ���ţ�...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('�ӣ�'+InFile);
    self.Memo1.Lines.Add('����'+OutFile);

    //����������
    MBInit(InBuf);
    MBInit(OutBuf);

    MBLoadFromFile(InBuf,InFile);

    //����������
    Coding:=TCHCoding.Create;

    //��ʱ
    self.FTime:=GetTickCount;

    Size:=Coding.Decode(InBuf,OutBuf);

    //��ѹ�����
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //��������
    MBSaveToFile(OutBuf,Size,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //��ʾ
    self.Memo1.Lines.Add(Format('������ɣ���ʱ��%d',[self.FTime]));

    //���
end;

//��������㷨��
//��Edit1��Ӧ���ļ�ѹ�����浽Edit2��Ӧ���ļ��У�
//ͬʱ��¼�����С�������С���㷨��ʱ��
procedure TForm1.PackRange;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TRCCoding;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('ʹ����������㷨ѹ��...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('�ӣ�'+InFile);
    self.Memo1.Lines.Add('����'+OutFile);

    //����������
    MBInit(InBuf);
    MBInit(OutBuf);

    self.FInSize:=MBLoadFromFile(InBuf,InFile);

    //����������
    Coding:=TRCCoding.Create;

    //��ʱ
    self.FTime:=GetTickCount;

    self.FOutSize:=Coding.Encode(InBuf,OutBuf,self.FInSize);

    //ѹ�����
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //��������
    MBSaveToFile(OutBuf,self.FOutSize,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //�������
    self.OutRadio;

    //���
end;

//��������㷨��
//��Edit1��Ӧ���ļ���ѹ�����浽Edit2��Ӧ���ļ��У�
//ͬʱ��¼�㷨��ʱ��
procedure TForm1.UnpackRange;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TRCCoding;

    Size : Integer;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('ʹ����������㷨��ѹ��...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('�ӣ�'+InFile);
    self.Memo1.Lines.Add('����'+OutFile);

    //����������
    MBInit(InBuf);
    MBInit(OutBuf);

    MBLoadFromFile(InBuf,InFile);

    //����������
    Coding:=TRCCoding.Create;

    //��ʱ
    self.FTime:=GetTickCount;

    Size:=Coding.Decode(InBuf,OutBuf);

    //��ѹ�����
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //��������
    MBSaveToFile(OutBuf,Size,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //��ʾ
    self.Memo1.Lines.Add(Format('������ɣ���ʱ��%d',[self.FTime]));

    //���
end;

//���������㷨��
//��Edit1��Ӧ���ļ�ѹ�����浽Edit2��Ӧ���ļ��У�
//ͬʱ��¼�����С�������С���㷨��ʱ��
procedure TForm1.PackArithmetic;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TACCoding;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('ʹ�����������㷨ѹ��...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('�ӣ�'+InFile);
    self.Memo1.Lines.Add('����'+OutFile);

    //����������
    MBInit(InBuf);
    MBInit(OutBuf);

    self.FInSize:=MBLoadFromFile(InBuf,InFile);

    //����������
    Coding:=TACCoding.Create;

    //��ʱ
    self.FTime:=GetTickCount;

    self.FOutSize:=Coding.Encode(InBuf,OutBuf,self.FInSize);

    //ѹ�����
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //��������
    MBSaveToFile(OutBuf,self.FOutSize,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //�������
    self.OutRadio;

    //���
end;

//���������㷨��
//��Edit1��Ӧ���ļ���ѹ�����浽Edit2��Ӧ���ļ��У�
//ͬʱ��¼�㷨��ʱ��
procedure TForm1.UnpackArithmetic;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TACCoding;

    Size : Integer;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('ʹ�����������㷨��ѹ��...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('�ӣ�'+InFile);
    self.Memo1.Lines.Add('����'+OutFile);

    //����������
    MBInit(InBuf);
    MBInit(OutBuf);

    MBLoadFromFile(InBuf,InFile);

    //����������
    Coding:=TACCoding.Create;

    //��ʱ
    self.FTime:=GetTickCount;

    Size:=Coding.Decode(InBuf,OutBuf);

    //��ѹ�����
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //��������
    MBSaveToFile(OutBuf,Size,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //��ʾ
    self.Memo1.Lines.Add(Format('������ɣ���ʱ��%d',[self.FTime]));

    //���
end;

//��Ԫ����
end.

