//
//�ڴ滺��������
//���ߣ�ҶҶ��2010��6��22��
//
//���ļ���Ȩ��ҶҶӵ�У���������Ȩ����
//���ļ��еĴ�������ѳ��������κ���Ȩ����ɼ������ڸ��˺���ҵĿ�ġ�ʹ����һ�к���Ը���
//
//�����ת���˱��ļ��еĴ��룬��ע����������ʹ������ߣ�
//������޸��˱��ļ��еĴ��룬��ע���޸�λ�ú��޸����ߣ�
//
//���ļ������ġ���ʽ�������㷨�ķ�����ʵ�֡������׳���
//���ļ�������http://programbbs.com/bbs/�Ϸ�����
//

unit MemoryBuffer;

interface

uses
    Classes, SysUtils;

type
    //Byte���飨8λ��
    PMBByteAry = ^TMBByteAry;
    TMBByteAry = array [0..0] of Byte;

    //Word���飨16λ��
    PMBWordAry = ^TMBWordAry;
    TMBWordAry = array [0..0] of Word;

    //Cardinal���飨32λ��
    PMBCardinalAry = ^TMBCardinalAry;
    TMBCardinalAry = array [0..0] of Cardinal;

    //���ݵĵ�λ����
    TMBDataType = (
        dtByte, //���ֽ�Ϊ��λ
        dtBit   //��λΪ��λ
    );

    //������
    PMBBuffer = ^TMBBuffer;
    TMBBuffer = record
        BufSize : Integer; //��������С���ֽڣ�
        IncSize : Integer; //������ÿ����չ��С���ֽڣ��������Ǵ��ڵ���4��2�Ĵη���
        DataType : TMBDataType; //���ݵĵ�λ����
        Offset : Integer; //��ǰ����λ�ã�λ���ֽڣ�����λ����DataType�����ö���ͬ
        case Byte of
            1 : (Mem   : Pointer); //�ڴ�ָ��
            2 : (Mem8  : PMBByteAry); //Byte����ָ��
            3 : (Mem32 : PMBCardinalAry); //Cardinal����ָ��
    end;

    //����������
    procedure MBInit   (var Buf : TMBBuffer; ABufSize : Integer = 0; AIncSize : Integer = 1024; ADataType : TMBDataType = dtByte);
    procedure MBReAlloc(var Buf : TMBBuffer; NewSize : Integer);
    procedure MBFree   (var Buf : TMBBuffer);
    procedure MBSetType(var Buf : TMBBuffer; NewType : TMBDataType);

    //���뵼��
    function MBLoadFromFile  (var Buf : TMBBuffer; const FileName : string): Integer;
    function MBSaveToFile    (const Buf : TMBBuffer; Size : Integer; const FileName : string): Integer;
    function MBLoadFromStream(var Buf : TMBBuffer; Stream : TStream): Integer;
    function MBSaveToStream  (const Buf : TMBBuffer; Size : Integer; Stream : TStream): Integer;

    //���ݶ�д
    procedure MBWrite   (var Buf : TMBBuffer; const Data; Size : Integer);
    procedure MBRead    (var Buf : TMBBuffer; var Data; Size : Integer);
    procedure MBWriteBit(var Buf : TMBBuffer; Data : Cardinal; Size : Integer);
    function  MBReadBit (var Buf : TMBBuffer; Size : Integer): Cardinal;
    procedure MBSetBit  (var Buf : TMBBuffer; Bit : Cardinal);
    function  MBGetBit  (var Buf : TMBBuffer): Cardinal;

    //0��ָ�����ײ�����
    procedure MBEncodeEG(var Buf : TMBBuffer;  Num : Cardinal);
    function  MBDecodeEG(var Buf : TMBBuffer): Cardinal;

implementation

{����������}

//��ʼ��������Buf����������Ҫ�����ڴ棬���ó�ʼֵ��
//Buf����������
//ABufSize����������ʼʱ�Ĵ�С���ֽڣ���
//AIncSize��������ÿ����չ��С���ֽڣ���
//ADataType�����ݵĵ�λ���͡�
procedure MBInit(var Buf : TMBBuffer; ABufSize,AIncSize : Integer; ADataType : TMBDataType);
begin
    with Buf do
    begin
        //ȷ��ÿ����չ��С
        IncSize:=4;
        while IncSize<AIncSize do IncSize:=IncSize shl 1;

        //�����ڴ�
        BufSize:=(ABufSize+(IncSize-1)) and (not (IncSize-1));
        if BufSize=0 then Mem:=nil
        else              GetMem(Mem,BufSize);

        //����
        DataType:=ADataType;
        Offset:=0;

        //���
    end;
end;

//���·��仺����Buf���ڴ棬
//Buf����������
//NewSize���µĻ�������С���ֽڣ���
procedure MBReAlloc(var Buf : TMBBuffer; NewSize : Integer);
begin
    with Buf do
    begin
        NewSize:=(NewSize+(IncSize-1)) and (not (IncSize-1));
        if NewSize=BufSize then exit;
        ReallocMem(Mem,NewSize);
        BufSize:=NewSize;
    end;
end;

//�ͷŻ�����Buf��ռ�õ��ڴ棬
//Buf����������
procedure MBFree(var Buf : TMBBuffer);
begin
    with Buf do
    begin
        if Mem<>nil then FreeMem(Mem);
        Mem:=nil;
        BufSize:=0;
    end;
end;

//���û�����Buf�ķ��ʵ�λ����Buf.Offset�������»��㣬
//Buf����������
//NewType���µĵ�λ���͡�
procedure MBSetType(var Buf : TMBBuffer; NewType : TMBDataType);
begin
    with Buf do
    begin
        if NewType=DataType then exit;

        //����
        case NewType of
            dtByte : Offset:=((Offset+31) and (not 31)) shr 3;
            dtBit  : Offset:=((Offset+ 3) and (not  3)) shl 3;
        end;

        //����
        DataType:=NewType;
    end;
end;

{���뵼��}

//��ָ���ļ��е������ݵ�������Buf�У�����������ʱ��չ��������
//���ص��뵽�����������ݵĴ�С���ֽڣ���
//Buf����������
//FileName���ļ�����
function MBLoadFromFile(var Buf : TMBBuffer; const FileName : string): Integer;
var
    Stream : TStream;
begin
    Stream:=TFileStream.Create(FileName,fmOpenRead);
    try
        Result:=MBLoadFromStream(Buf,Stream);
    finally
        Stream.Free;
    end;
end;

//��������Buf�е�ָ�����ȵ����ݱ��浽ָ���ļ��У�
//����д�뵽�ļ������ݵĴ�С���ֽڣ���
//����Sizeȷ�������������ݵĴ�С��
//Buf����������
//Size�����ݴ�С���ֽڣ���
//FileName���ļ�����
function MBSaveToFile(const Buf : TMBBuffer; Size : Integer; const FileName : string): Integer;
var
    Stream : TStream;
begin
    Stream:=TFileStream.Create(FileName,fmCreate);
    try
        Result:=MBSaveToStream(Buf,Size,Stream);
    finally
        Stream.Free;
    end;
end;

//��ָ���������е������ݵ�������Buf�У�����������ʱ��չ��������
//���ص��뵽�����������ݵĴ�С���ֽڣ���
//Buf����������
//Stream����������
function MBLoadFromStream(var Buf : TMBBuffer; Stream : TStream): Integer;
begin
    with Buf do
    begin
        Result:=Stream.Size-Stream.Position;
        if Result>BufSize then MBReAlloc(Buf,Result);
        Result:=Stream.Read(Mem^,Result);
    end;
end;

//��������Buf�е�ָ�����ȵ����ݱ��浽ָ���������У�
//����д�뵽�����������ݵĴ�С���ֽڣ���
//����Sizeȷ�������������ݵĴ�С��
//Buf����������
//Size�����ݴ�С���ֽڣ���
//Stream����������
function MBSaveToStream(const Buf : TMBBuffer; Size : Integer; Stream : TStream): Integer;
begin
    with Buf do
    begin
        if Size>BufSize then Size:=BufSize;
        Result:=Stream.Write(Mem^,Size);
    end;
end;

{���ݶ�д}

//��Data�е�����д�뵽������Buf�У�����������ʱ��չ��������
//����Buf.Offsetȷ��д��λ�ã�д����޸�Buf.Offset��
//Buf����������
//Data������
//Size�����ݳ��ȣ��ֽڣ���
procedure MBWrite(var Buf : TMBBuffer; const Data; Size : Integer);
var
    NeedSize : Integer;
begin
    if Size<=0 then exit;

    with Buf do
    begin
        if DataType<>dtByte then MBSetType(Buf,dtByte);

        //��չ������
        NeedSize:=Offset+Size;
        if NeedSize>BufSize then MBReAlloc(Buf,NeedSize);

        //��������
        Move(Data,Mem8[Offset],Size);

        //����λ��
        Offset:=NeedSize;

        //���
    end;
end;

//�ӻ�����Buf�ж�ȡָ�����ȵ����ݵ�Data�У�
//����Buf.Offsetȷ����ȡλ�ã���ȡ���޸�Buf.Offset��
//Buf����������
//Data������
//Size�����ݳ��ȣ��ֽڣ���
procedure MBRead(var Buf : TMBBuffer; var Data; Size : Integer);
var
    ReadSize : Integer;
begin
    if Size<=0 then exit;

    with Buf do
    begin
        if DataType<>dtByte then MBSetType(Buf,dtByte);

        //�жϿɶ�����
        ReadSize:=BufSize-Offset;
        if ReadSize<=0 then exit;
        if ReadSize>Size then ReadSize:=Size;

        //��������
        Move(Mem8[Offset],Data,ReadSize);

        //����λ��
        Inc(Offset,ReadSize);

        //���
    end;
end;

//��Data��Size��λд�뻺����Buf�У�����������ʱ��չ��������
//����Buf.Offsetȷ��д��λ�ã�д����޸�Buf.Offset��
//Buf����������
//Data������
//Size�����ݳ��ȣ�λ����1��32��Χ�ڣ���
procedure MBWriteBit(var Buf : TMBBuffer; Data : Cardinal; Size : Integer);
var
    Dest : PCardinal;
    NeedSize,Hi,Lo : Integer;
begin
    if Size<=0 then exit;
    if Size>32 then Size:=32;

    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //��չ������
        NeedSize:=((Offset+Size+31) and (not 31)) shr 3;
        if NeedSize>BufSize then MBReAlloc(Buf,NeedSize);

        //���㲢����λ��
        Dest:=@(Mem32[Offset shr 5]);
        Hi:=Offset and 31;
        Lo:=32-Hi;
        Inc(Offset,Size);
    end;

    //����λ���ݣ���CardinalΪ��λ���Ӹ�λ���λд�롣��
    Data:=Data shl (32-Size);
    Dest^:=(Dest^ and (not ($FFFFFFFF shr Hi))) or (Data shr Hi);
    if Size>Lo then
    begin
        Inc(Dest); Dest^:=Data shl Lo;
    end;

    //���
end;

//�ӻ�����Buf�ж�ȡSize��λ�����أ�
//���軺���������е����ݶ�Ϊ������1��
//�����㹻ʱ��ȡ4λʱ�����ص�λΪ0..01111��
//���ݲ���ʱ��ȡ4λʱ�����ص�λΪ0..01100��
//����Buf.Offsetȷ����ȡλ�ã���ȡ���޸�Buf.Offset��
//Buf����������
//Size�����ݳ��ȣ�λ����1��32��Χ�ڣ���
function MBReadBit(var Buf : TMBBuffer; Size : Integer): Cardinal;
var
    Sour : PCardinal;
    ReadSize,Hi,Lo : Integer;
begin
    Result:=0;
    if Size<=0 then exit;
    if Size>32 then Size:=32;

    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //�жϿɶ�λ��
        ReadSize:=(BufSize shl 3)-Offset;
        if ReadSize<=0 then exit;
        if ReadSize>Size then ReadSize:=Size;

        //���㲢����λ��
        Sour:=@(Mem32[Offset shr 5]);
        Hi:=Offset and 31;
        Lo:=32-Hi;
        Inc(Offset,ReadSize);
    end;

    //����λ���ݣ���CardinalΪ��λ���Ӹ�λ���λ��ȡ����
    Result:=Sour^ shl Hi;
    if ReadSize>Lo then
    begin
        Inc(Sour); Result:=Result or (Sour^ shr Lo);
    end;
    Result:=Result shr (32-ReadSize);

    //���ݲ��㣬���Ʋ���
    if ReadSize<Size then Result:=Result shl (Size-ReadSize);

    //���
end;

//�򻺳���Buf��д��һ��λ��BitΪ0ʱд��0��Bit��Ϊ0ʱд��1��
//����������ʱ��չ��������
//����Buf.Offsetȷ��д��λ�ã�д����޸�Buf.Offset��
//Buf����������
//Bit��λ���ݡ�
procedure MBSetBit(var Buf : TMBBuffer; Bit : Cardinal);
var
    Dest : PCardinal;
    NeedSize : Integer;
    Mask : Cardinal;
begin
    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //��չ������
        NeedSize:=((Offset+1+31) and (not 31)) shr 3;
        if NeedSize>BufSize then MBReAlloc(Buf,NeedSize);

        //���㲢����λ��
        Dest:=@(Mem32[Offset shr 5]);
        Mask:=$80000000 shr (Offset and 31);
        Inc(Offset);
    end;

    //����λ����CardinalΪ��λ���Ӹ�λ���λд�롣��
    if Bit=0 then Dest^:=Dest^ and (not Mask)
    else          Dest^:=Dest^ or  Mask;

    //���
end;

//�ӻ�����Buf�ж�ȡһ��λ����λΪ0����0����λΪ1����1��
//����Buf.Offsetȷ����ȡλ�ã���ȡ���޸�Buf.Offset��
//Buf����������
function MBGetBit(var Buf : TMBBuffer): Cardinal;
var
    ReadSize : Integer;
begin
    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //�жϿɶ�λ��
        ReadSize:=(BufSize shl 3)-Offset;
        if ReadSize<1 then
        begin
            Result:=0; exit;
        end;

        //��ȡλ����CardinalΪ��λ���Ӹ�λ���λ��ȡ����
        Result:=(Mem32[Offset shr 5] shr (32-(Offset and 31)-1)) and 1;

        //����λ��
        Inc(Offset);

        //���
    end;
end;

{0��ָ�����ײ�����}

//ʹ��ָ�����ײ��㷨��һ����ֵ���ݽ���ѹ����д�뵽������Buf�У�
//����������ʱ��չ��������
//����Buf.Offsetȷ��д��λ�ã�д����޸�Buf.Offset��
//Buf����������
//Num����ֵ���ݡ�
procedure MBEncodeEG(var Buf : TMBBuffer;  Num : Cardinal);
var
    Dest : PCardinal;
    N : Cardinal;
    BitLen,NeedSize,Len,Hi,Lo : Integer;
begin
    if Num=0 then
    begin
        MBSetBit(Buf,1); exit;
    end;

    Inc(Num);

    //����ǰ׺λ��
    BitLen:=1;
    N:=$FFFFFFFC;
    while (N and Num)<>0 do
    begin
        Inc(BitLen); N:=N shl 1;
    end;

    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //��չ������
        Len:=(BitLen shl 1)+1; //��λ��
        NeedSize:=((Offset+Len+31) and (not 31)) shr 3;
        if NeedSize>BufSize then MBReAlloc(Buf,NeedSize);

        //���㲢����λ��
        Dest:=@(Mem32[Offset shr 5]);
        Hi:=Offset and 31;
        Lo:=32-Hi;
        Inc(Offset,Len);
    end;

    //д��ǰ׺BitLen��0����CardinalΪ��λ���Ӹ�λ���λд�롣��
    Dest^:=Dest^ and (not ($FFFFFFFF shr Hi));
    if BitLen>Lo then
    begin
        Inc(Dest); Dest^:=0;
    end;

    //д���׺���ݣ���CardinalΪ��λ���Ӹ�λ���λд�롣��
    Hi:=(Hi+BitLen) and 31;
    Lo:=32-Hi;
    if Hi=0 then Inc(Dest);

    Inc(BitLen);
    Num:=Num shl (32-BitLen);
    Dest^:=(Dest^ and (not ($FFFFFFFF shr Hi))) or (Num shr Hi);
    if BitLen>Lo then
    begin
        Inc(Dest); Dest^:=Num shl Lo;
    end;

    //���
end;

//ʹ��ָ�����ײ��㷨�ӻ������н�ѹ����һ����ֵ���ݣ������أ�
//����������е����ݲ��������һ�ν��룬�򷵻�$FFFFFFFF��
//����Buf.Offsetȷ����ȡλ�ã���ȡ���޸�Buf.Offset��
//Buf����������
function MBDecodeEG(var Buf : TMBBuffer): Cardinal;
var
    Sour : PCardinal;
    N : Cardinal;
    ReadSize,Len,BitLen,Hi,Lo : Integer;
begin
    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //����ɶ�λ����λ��
        ReadSize:=(BufSize shl 3)-Offset;
        if ReadSize<=0 then
        begin
            Result:=$FFFFFFFF; exit;
        end;
        Sour:=@(Mem32[Offset shr 5]);
        Hi:=Offset and 31;
    end;

    //����ǰ׺λ������CardinalΪ��λ���Ӹ�λ���λ��ȡ����
    BitLen:=0;
    N:=$80000000 shr Hi;
    while (BitLen<ReadSize) and ((Sour^ and N)=0) do
    begin
        Inc(BitLen);
        N:=N shr 1;
        if N=0 then
        begin
            Inc(Sour); N:=$80000000;
        end;
    end;

    //���㲢����λ��
    Len:=(BitLen shl 1)+1;
    if ReadSize<Len then
    begin
        Result:=$FFFFFFFF; exit;
    end;

    Inc(Buf.Offset,Len);

    if BitLen=0 then
    begin
        Result:=0; exit;
    end;

    //��ȡ��׺���ݣ���CardinalΪ��λ���Ӹ�λ���λ��ȡ����
    Hi:=(Hi+BitLen) and 31;
    Lo:=32-Hi;

    Inc(BitLen);
    Result:=Sour^ shl Hi;
    if BitLen>Lo then
    begin
        Inc(Sour); Result:=Result or (Sour^ shr Lo);
    end;
    Result:=(Result shr (32-BitLen))-1;

    //���
end;

//��Ԫ������
end.

