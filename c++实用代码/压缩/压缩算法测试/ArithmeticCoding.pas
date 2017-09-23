//
//���������㷨��ʵ��
//���ߣ�ҶҶ��2010��8��30��
//
//���ļ������㷨�о�ʹ�á����ļ���ʵ�ֵ��㷨����а�Ȩ�ģ��ɰ�Ȩ������ӵ�С�
//
//���ļ������ġ���������㷨�ķ�����ʵ�֡������׳���
//���ļ�������http://programbbs.com/bbs/�Ϸ�����
//

unit ArithmeticCoding;

interface

uses
    MemoryBuffer;

const
    //����������������2�Ĵη���
    AC_SYMBOL_NO = 256;

    //������
    AC_EOM = AC_SYMBOL_NO;

    //����λ��
    AC_CODE_BITS = 31;

    //��������Χ
    AC_TOP = Cardinal(1 shl AC_CODE_BITS);

    //���Χ�Ķ���֮һ
    AC_HALF = AC_TOP shr 1;

    //���Χ���ķ�֮һ
    AC_QUAR = AC_HALF shr 1;

    //���Ƶ�ȣ����ܳ���$FFFF����ΪƵ�ȱ���Word��������
    AC_MAX_FREQ = $FFFF;

type
    //�������ͣ�������AC_SYMBOL_NO���Ӧ
    TACSymbol = Integer;

    //����������ı����������������ģ����
    PACCoder = ^TACCoder;
    TACCoder = class
    private
        FLow : Cardinal; //��ǰ���������
        FRange : Cardinal; //��ǰ���䷶Χ
        FFollow : Integer; //�ӳ�λ����

        FValue : Cardinal; //����ʱ����ı���ֵ

        FBuf : PMBBuffer; //��������������
    public
        constructor Create;
        destructor Destroy; override;

        //�������
        procedure InitEncode(OutBuf : PMBBuffer);
        procedure Encode(CumFreq,Freq,Total : Cardinal);
        procedure FinishEncode;

        //�������
        procedure InitDecode(InBuf : PMBBuffer);
        function DecodeTarget(Total : Cardinal): Cardinal;
        procedure Decode(CumFreq,Freq : Cardinal);
        procedure FinishDecode;
    end;

    //ͳ��ģ�ͣ�0�ף�
    TACModel = class
    private
        FTotal : Cardinal; //Ƶ���ܼ�
        FTree : array [0..AC_SYMBOL_NO] of Word; //BIT���������ۻ�Ƶ��

        FCoder : PACCoder; //�������

        procedure GetFreq(Symbol : TACSymbol; var CumFreq,Freq : Cardinal);
        procedure IncFreq(Symbol : TACSymbol);
        function FindEstFreq(EstFreq : Cardinal): TACSymbol;
    public
        constructor Create;
        destructor Destroy; override;

        //ģ�Ͳ���
        procedure InitModel(Coder : PACCoder);
        procedure Encode(Symbol : TACSymbol);
        function Decode: TACSymbol;
        procedure FinishModel;
    end;

    //������������������TACCoder��TACModel�ļ򵥷�װ
    TACCoding = class
    private
        FCoder : TACCoder; //�������
        FModel : TACModel; //ģ��
    public
        constructor Create;
        destructor Destroy; override;

        function Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
        function Decode(var InBuf,OutBuf : TMBBuffer): Integer;
    end;

implementation

{TACCoder} //����������ı����������������ģ����

//�½�����������ı��������
constructor TACCoder.Create;
begin
end;

//��������������ı��������
destructor TACCoder.Destroy;
begin
end;

//��ʼ����������������������ָ��������������󶨣�
//OutBuf����������
procedure TACCoder.InitEncode(OutBuf : PMBBuffer);
begin
    self.FBuf:=OutBuf;
    self.FLow:=0;
    self.FRange:=AC_TOP;
    self.FFollow:=0;
end;

//������������㷨��һ�����Ž��б��벢д�뵽Buf�У�
//����Buf.Offsetȷ������λ�ã�������޸�Buf.Offset��Buf.DataSize��
//CumFreq���ۻ�Ƶ�ȣ�
//Freq��Ƶ�ȣ�
//Total��Ƶ���ܼơ�
procedure TACCoder.Encode(CumFreq,Freq,Total : Cardinal);
var
    High,Check,Bit : Cardinal;
    i : Integer;
begin
    //�������
    self.FRange:=self.FRange div Total;
    Inc(self.FLow,CumFreq*self.FRange);
    High:=self.FLow+(Freq*self.FRange)-1;

    //��������
    while True do
    begin
        Check:=High xor self.FLow;

        if (Check and AC_HALF)=0 then
        begin
            //����λ���ϰ������°���
            Bit:=(High shr (AC_CODE_BITS-1)) and 1;
            MBSetBit(self.FBuf^,Bit);

            if self.FFollow<>0 then
            begin
                if Bit=0 then Bit:=1
                else          Bit:=0;

                for i:=1 to self.FFollow do MBSetBit(self.FBuf^,Bit);
                self.FFollow:=0;
            end;
        end
        else if ((Check and AC_QUAR)<>0) and
                ((High and AC_QUAR)=0) then
        begin
            //����λ���м���
            Inc(self.FFollow);
            Dec(High,AC_QUAR);
            Dec(self.FLow,AC_QUAR);
        end
        else break;

        //��չ����
        High:=((High shl 1)+1) and (AC_TOP-1);
        self.FLow:=(self.FLow shl 1) and (AC_TOP-1);
    end;

    self.FRange:=High-self.FLow+1;

    //���
end;

//�������룬������β������
//����������������ĩβ���AC_EOM��������
procedure TACCoder.FinishEncode;
var
    i : Integer;
begin
    //���ʣ�����
    Inc(self.FFollow);

    if self.FLow<AC_QUAR then
    begin
        MBSetBit(self.FBuf^,0);
        for i:=1 to self.FFollow do MBSetBit(self.FBuf^,1);
    end
    else
    begin
        MBSetBit(self.FBuf^,1);
        for i:=1 to self.FFollow do MBSetBit(self.FBuf^,0);
    end;

    self.FFollow:=0;

    self.FBuf:=nil;

    //���
end;

//��ʼ����������������������ָ�������뻺�����󶨣�
//InBuf����������
procedure TACCoder.InitDecode(InBuf : PMBBuffer);
begin
    //��ʼ��
    self.FBuf:=InBuf;
    self.FLow:=0;
    self.FRange:=AC_TOP;

    //�������
    self.FValue:=MBReadBit(self.FBuf^,AC_CODE_BITS);

    //���
end;

//���ݵ�ǰ�����䣬����ָ����Total����������ۻ�Ƶ�ȣ������أ�
//Total���ܼ�Ƶ�ȡ�
function TACCoder.DecodeTarget(Total : Cardinal): Cardinal;
begin
    self.FRange:=self.FRange div Total;
    Result:=(self.FValue-self.FLow) div self.FRange;
end;

//����ָ����Ƶ�����ݵ�����ǰ���䣬������Ҫ�ӻ������ж������ݣ�
//�ڵ��ñ�����֮ǰ�����ȵ���DecodeTarget������
//����FBuf.Offsetȷ����ȡλ�ã���ȡ���޸�FBuf.Offset��
//CumFreq���ۻ�Ƶ�ȣ�
//Freq��Ƶ�ȡ�
procedure TACCoder.Decode(CumFreq,Freq : Cardinal);
var
    High,Check : Cardinal;
begin
    //�������
    Inc(self.FLow,CumFreq*self.FRange);
    High:=self.FLow+(Freq*self.FRange)-1;

    //��������
    while True do
    begin
        Check:=High xor self.FLow;

        if (Check and AC_HALF)=0 then
        begin
            //����λ���ϰ������°���
        end
        else if ((Check and AC_QUAR)<>0) and
                ((High and AC_QUAR)=0) then
        begin
            //����λ���м���
            Dec(High,AC_QUAR);
            Dec(self.FLow,AC_QUAR);
            Dec(self.FValue,AC_QUAR);
        end
        else break;

        //��չ����
        High:=((High shl 1)+1) and (AC_TOP-1);
        self.FLow:=(self.FLow shl 1) and (AC_TOP-1);
        self.FValue:=((self.FValue shl 1) or MBGetBit(self.FBuf^)) and (AC_TOP-1);
    end;

    self.FRange:=High-self.FLow+1;

    //���
end;

//�������룬������β������
procedure TACCoder.FinishDecode;
begin
    self.FBuf:=nil;
end;

{TACModel} //ͳ��ģ�ͣ�0�ף�

//�½�ͳ��ģ�͡�
constructor TACModel.Create;
begin
    self.FCoder:=nil;
end;

//����ͳ��ģ�͡�
destructor TACModel.Destroy;
begin
end;

//��ȡָ�����ŵ��ۻ�Ƶ�Ⱥ�Ƶ�ȣ�
//Symbol������ֵ��
//CumFreq�����ŵ��ۻ�Ƶ�ȣ�
//Freq�����ŵ�Ƶ�ȡ�
procedure TACModel.GetFreq(Symbol : TACSymbol; var CumFreq,Freq : Cardinal);
var
    Id,Parent : Integer;
    Sum : Cardinal;
begin
    //�ų�����0
    if Symbol=0 then
    begin
        CumFreq:=0;
        Freq:=self.FTree[0];
        exit;
    end;

    //ͳ���ۻ�Ƶ�Ⱥ�Ƶ��
    Id:=Symbol;
    Parent:=Id-(Id and -Id);
    Dec(Id);
    Sum:=0;

    while Id<>Parent do
    begin
        Inc(Sum,self.FTree[Id]);
        Dec(Id,Id and -Id);
    end;
    Freq:=self.FTree[Symbol]-Sum;

    while Id>0 do
    begin
        Inc(Sum,self.FTree[Id]);
        Dec(Id,Id and -Id);
    end;
    CumFreq:=self.FTree[0]+Sum;

    //���
end;

//����ָ�����ŵ�Ƶ�ȣ�����Ƶ�ȴ�������ֵʱ������Ƶ�ȣ�
//Symbol������ֵ��
procedure TACModel.IncFreq(Symbol : TACSymbol);
var
    i,Id,Parent : Integer;
    Freq,NewFreq : Cardinal;
begin
    if self.FTotal=AC_MAX_FREQ then
    begin
        //����Ƶ��
        self.FTree[0]:=(self.FTree[0]+1) shr 1;
        self.FTotal:=self.FTree[0];
        for i:=1 to AC_SYMBOL_NO do
        begin
            //ͳ��Ƶ��
            Id:=i;
            Freq:=self.FTree[Id];
            Parent:=Id-(Id and -Id);
            Dec(Id);
            while Id<>Parent do
            begin
                Dec(Freq,self.FTree[Id]);
                Dec(Id,Id and -Id);
            end;

            //�����ֵ
            NewFreq:=(Freq+1) shr 1;
            Inc(self.FTotal,NewFreq);
            Dec(Freq,NewFreq);
            if Freq=0 then continue;

            //����Ƶ��
            Id:=i;
            repeat
                Dec(self.FTree[Id],Freq);
                Inc(Id,Id and -Id);
            until Id>AC_SYMBOL_NO;
        end;
    end;

    //����Ƶ��
    if Symbol=0 then Inc(self.FTree[0])
    else
    begin
        repeat
            Inc(self.FTree[Symbol]);
            Inc(Symbol,Symbol and -Symbol);
        until Symbol>AC_SYMBOL_NO;
    end;
    Inc(self.FTotal);

    //���
end;

//����ָ���Ĺ���Ƶ�ȣ����ض�Ӧ�ķ��ţ�
//EstFreq������Ƶ��ֵ��
function TACModel.FindEstFreq(EstFreq : Cardinal): TACSymbol;
var
    Mask,Id : Integer;
begin
    //�ų�����0�ͽ�����
    if EstFreq<self.FTree[0] then
    begin
        Result:=0; exit;
    end;
    Dec(EstFreq,self.FTree[0]);
    if EstFreq>=self.FTree[AC_SYMBOL_NO] then
    begin
        Result:=AC_EOM; exit;
    end;

    //����
    Result:=0;
    Mask:=AC_SYMBOL_NO shr 1;
    while Mask<>0 do
    begin
        Id:=Result+Mask;
        if EstFreq>=self.FTree[Id] then
        begin
            Result:=Id;
            Dec(EstFreq,self.FTree[Id]);
        end;
        Mask:=Mask shr 1;
    end;
    Inc(Result);

    //���
end;

//��ʼ��ģ�ͣ�����ģ����ָ���ĺ��ı�������󶨣�
//Coder�����ı��������
procedure TACModel.InitModel(Coder : PACCoder);
var
    i,Id : Integer;
begin
    self.FCoder:=Coder;

    //��ʼ��Ƶ�ȣ���ʼʱÿ�����ŵ�Ƶ�ȶ�Ϊ1
    self.FTree[0]:=1;

    for i:=1 to AC_SYMBOL_NO do self.FTree[i]:=0;
    for i:=1 to AC_SYMBOL_NO do
    begin
        Id:=i;
        repeat
            Inc(self.FTree[Id]);
            Inc(Id,Id and -Id);
        until Id>AC_SYMBOL_NO;
    end;
    self.FTotal:=AC_SYMBOL_NO+1;

    //���
end;

//������������㷨��һ�����Ž��б��벢д�뵽Buf�У�
//����Buf.Offsetȷ������λ�ã�������޸�Buf.Offset��Buf.DataSize��
//Symbol������ֵ��
procedure TACModel.Encode(Symbol : TACSymbol);
var
    CumFreq,Freq : Cardinal;
begin
    //ͳ��Ƶ��
    self.GetFreq(Symbol,CumFreq,Freq);

    //����
    self.FCoder.Encode(CumFreq,Freq,self.FTotal);

    //����Ƶ��
    self.IncFreq(Symbol);

    //���
end;

//������������㷨�Դ�Buf�н����һ�����ţ������أ�
//����Buf.Offsetȷ����ȡλ�ã���ȡ���޸�Buf.Offset��
function TACModel.Decode: TACSymbol;
var
    CumFreq,Freq : Cardinal;
begin
    //���ҹ���Ƶ��
    Result:=self.FindEstFreq(
        self.FCoder.DecodeTarget(self.FTotal));

    //ͳ��Ƶ��
    self.GetFreq(Result,CumFreq,Freq);

    //��������
    self.FCoder.Decode(CumFreq,Freq);

    //����Ƶ��
    self.IncFreq(Result);

    //���
end;

//����������������β������
procedure TACModel.FinishModel;
begin
    self.FCoder:=nil;
end;

{TACCoding} //������������������TACCoder��TACModel�ļ򵥷�װ

//�½�����������������
constructor TACCoding.Create;
begin
    self.FCoder:=TACCoder.Create;
    self.FModel:=TACModel.Create;
end;

//��������������������
destructor TACCoding.Destroy;
begin
    self.FCoder.Free;
    self.FModel.Free;
end;

//�ӻ�����InBuf�ж�ȡSize���ȵ����ݽ���ѹ�������浽������OutBuf�У�
//����д�뵽������OutBuf�����ݵĴ�С���ֽڣ���
//������OutBuf����ʱ��չ��������
//����InBuf.Offsetȷ����ȡλ�ã���ȡ���޸�InBuf.Offset��
//����OutBuf.Offsetȷ��д��λ�ã�д����޸�OutBuf.Offset��
//InBuf�����뻺������
//OutBuf�������������
//Size�����ݴ�С���ֽڣ���
function TACCoding.Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
var
    i,ReadSize,NeedSize,LastOff : Integer;
    Dest : PMBByteAry;
begin
    with InBuf do
    begin
        if DataType<>dtByte then MBSetType(InBuf,dtByte);

        //�жϿɶ�����
        ReadSize:=BufSize-Offset;
        if ReadSize<=0 then
        begin
            Result:=0; exit;
        end;
        if ReadSize>Size then ReadSize:=Size;

        //���㲢����λ��
        Dest:=@(Mem8[Offset]);
        Inc(Offset,ReadSize);
    end;

    with OutBuf do
    begin
        if DataType<>dtByte then MBSetType(OutBuf,dtByte);

        //��չ������
        NeedSize:=Offset+ReadSize;
        if NeedSize>BufSize then MBReAlloc(OutBuf,NeedSize);

        LastOff:=Offset;
    end;

    //��ʼ��
    self.FCoder.InitEncode(@OutBuf);
    self.FModel.InitModel(@(self.FCoder));

    //�������ݳ���
    MBWrite(OutBuf,ReadSize,SizeOf(Integer));

    //����
    for i:=0 to ReadSize-1 do self.FModel.Encode(Dest[i]);

    //��������
    self.FModel.FinishModel;
    self.FCoder.FinishEncode;

    //����д�볤��
    MBSetType(OutBuf,dtByte);
    Result:=OutBuf.Offset-LastOff;

    //���
end;

//�ӻ�����InBuf�ж�ȡ���ݽ��н�ѹ�������浽������OutBuf�У�
//����д�뵽������OutBuf�����ݵĴ�С���ֽڣ���
//������OutBuf����ʱ��չ��������
//������InBuf�е�ѹ�����ݱ�����ʹ��TACCoding.Encode����ģ�
//����InBuf.Offsetȷ����ȡλ�ã���ȡ���޸�InBuf.Offset��
//����OutBuf.Offsetȷ��д��λ�ã�д����޸�OutBuf.Offset��
//InBuf�����뻺������
//OutBuf�������������
function TACCoding.Decode(var InBuf,OutBuf : TMBBuffer): Integer;
var
    i,NeedSize : Integer;
    Sour : PMBByteAry;
begin
    //��ȡԭ���ݳ���
    MBRead(InBuf,Result,SizeOf(Integer));
    if Result<=0 then
    begin
        Result:=0; exit;
    end;

    with OutBuf do
    begin
        if DataType<>dtByte then MBSetType(OutBuf,dtByte);

        //��չ������
        NeedSize:=Offset+Result;
        if NeedSize>BufSize then MBReAlloc(OutBuf,NeedSize);

        //���㲢����λ��
        Sour:=@(Mem8[Offset]);
        Offset:=NeedSize;
    end;

    //��ʼ��
    self.FCoder.InitDecode(@InBuf);
    self.FModel.InitModel(@(self.FCoder));

    //����
    for i:=0 to Result-1 do Sour[i]:=self.FModel.Decode;

    //��������
    self.FModel.FinishModel;
    self.FCoder.FinishDecode;

    //���
end;

//��Ԫ����
end.

