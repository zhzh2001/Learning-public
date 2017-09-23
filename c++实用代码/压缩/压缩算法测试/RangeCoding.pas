//
//��������㷨��ʵ��
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

unit RangeCoding;

interface

uses
    MemoryBuffer;

const
    //����������������2�Ĵη���
    RC_SYMBOL_NO = 256;

    //������
    RC_EOM = RC_SYMBOL_NO;

    //����λ��
    RC_CODE_BITS = 31;

    //��λ��ȥλ��
    RC_SHIFT_BITS = RC_CODE_BITS-8; //һ�����8��λ

    //���䷶Χ�����ֵ��Rmax��
    RC_MAX_RANGE = Cardinal(1 shl RC_CODE_BITS);

    //���䷶Χ����Сֵ��Rmin��
    RC_MIN_RANGE = 1 shl RC_SHIFT_BITS;

    //���Ƶ�ȣ����ܳ���$FFFF����ΪƵ�ȱ���Word��������
    RC_MAX_FREQ = $FFFF;

type
    //�������ͣ�������RC_SYMBOL_NO���Ӧ
    TRCSymbol = Integer;

    //���������ı����������������ģ����
    PRCCoder = ^TRCCoder;
    TRCCoder = class
    private
        //���䣺c,(d,n),[L",H"]
        FLow : Cardinal; //��ǰ��������أ�L"��
        FRange : Cardinal; //��ǰ���䷶Χ��R��
        FDigits : Cardinal; //����ʱ���������ӳ����֣�d��������ʱ��������������루V��
        FFollow : Integer; //�ӳ����ֳ��ȣ�n��

        FBuf : PMBBuffer; //��������������

        procedure OutputCode(Code : Cardinal);
        function InputCode: Cardinal;
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
    TRCModel = class
    private
        FTotal : Cardinal; //Ƶ���ܼ�
        FTree : array [0..RC_SYMBOL_NO] of Word; //BIT�ṹ�������ۻ�Ƶ��

        FCoder : PRCCoder; //�������

        procedure GetFreq(Symbol : TRCSymbol; var CumFreq,Freq : Cardinal);
        procedure IncFreq(Symbol : TRCSymbol);
        function FindEstFreq(EstFreq : Cardinal): TRCSymbol;
    public
        constructor Create;
        destructor Destroy; override;

        //ģ�Ͳ���
        procedure InitModel(Coder : PRCCoder);
        procedure Encode(Symbol : TRCSymbol);
        function Decode: TRCSymbol;
        procedure FinishModel;
    end;

    //�����������������TRCCoder��TRCModel�ļ򵥷�װ
    TRCCoding = class
    private
        FCoder : TRCCoder; //�������
        FModel : TRCModel; //ģ��
    public
        constructor Create;
        destructor Destroy; override;

        //��������
        function Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
        function Decode(var InBuf,OutBuf : TMBBuffer): Integer;
    end;

implementation

{TRCCoder} //���������ı����������������ģ����

//�½����������ı��������
constructor TRCCoder.Create;
begin
end;

//�������������ı��������
destructor TRCCoder.Destroy;
begin
end;

//��FBuf���һ���ֽڵı��루8λ����
//����FBuf.Offsetȷ������λ�ã�������޸�FBuf.Offset��FBuf.DataSize��
//Code���������ݣ���8λ��Ч��
procedure TRCCoder.OutputCode(Code : Cardinal);
begin
    with self.FBuf^ do
    begin
        if DataType<>dtByte then MBSetType(self.FBuf^,dtByte);
        if (Offset+1)>BufSize then MBReAlloc(self.FBuf^,Offset+1);

        Mem8[Offset]:=Code;
        Inc(Offset);
    end;
end;

//��FBuf����һ���ֽڵı��루8λ���������أ�
//����FBuf.Offsetȷ����ȡλ�ã���ȡ���޸�FBuf.Offset��
function TRCCoder.InputCode: Cardinal;
begin
    with self.FBuf^ do
    begin
        if DataType<>dtByte then MBSetType(self.FBuf^,dtByte);

        if Offset>=BufSize then Result:=0
        else                    Result:=Mem8[Offset];
        
        Inc(Offset);
    end;
end;

//��ʼ����������������������ָ��������������󶨣�
//OutBuf����������
procedure TRCCoder.InitEncode(OutBuf : PMBBuffer);
begin
    self.FBuf:=OutBuf;
    self.FLow:=RC_MAX_RANGE;
    self.FRange:=RC_MAX_RANGE;
    self.FDigits:=0;
    self.FFollow:=0;
end;

//������������㷨����һ�����ŵ�Ƶ����Ϣ���б��벢д�뵽FBuf�У�
//����FBuf.Offsetȷ������λ�ã�������޸�FBuf.Offset��FBuf.DataSize��
//CumFreq���ۻ�Ƶ�ȣ�
//Freq��Ƶ�ȣ�
//Total��Ƶ���ܼơ�
procedure TRCCoder.Encode(CumFreq,Freq,Total : Cardinal);
var
    High : Cardinal;
    i : Integer;
begin
    //�������
    self.FRange:=self.FRange div Total;
    Inc(self.FLow,CumFreq*self.FRange);
    self.FRange:=Freq*self.FRange;

    //��������
    while self.FRange<=RC_MIN_RANGE do
    begin
        High:=self.FLow+self.FRange-1;

        //�ж��Ƿ����ӳ�����
        if self.FFollow<>0 then
        begin
            if High<=RC_MAX_RANGE then
            begin
                //��������
                self.OutputCode(self.FDigits);
                for i:=1 to self.FFollow-1 do self.OutputCode($FF);
                self.FFollow:=0;

                Inc(self.FLow,RC_MAX_RANGE);
            end
            else if self.FLow>=RC_MAX_RANGE then
            begin
                //��������
                self.OutputCode(self.FDigits+1);
                for i:=1 to self.FFollow-1 do self.OutputCode($00);
                self.FFollow:=0;
            end
            else
            begin
                //����δ��
                Inc(self.FFollow);

                //��չ����
                self.FLow:=(self.FLow shl 8) and (RC_MAX_RANGE-1);
                self.FRange:=self.FRange shl 8;

                continue;
            end;
        end;

        //�ж����λ����
        if ((self.FLow xor High) and ($FF shl RC_SHIFT_BITS))=0 then
        begin
            //���ֲ�������
            self.OutputCode(self.FLow shr RC_SHIFT_BITS);
        end
        else
        begin
            //�����ӳ�����
            Dec(self.FLow,RC_MAX_RANGE);
            self.FDigits:=self.FLow shr RC_SHIFT_BITS;
            self.FFollow:=1;
        end;

        //��չ����
        self.FLow:=((self.FLow shl 8) and (RC_MAX_RANGE-1)) or
                   (self.FLow and RC_MAX_RANGE);
        self.FRange:=self.FRange shl 8;
    end;

    //���
end;

//�������룬������β������
//����������������ĩβ���RC_EOM��������
procedure TRCCoder.FinishEncode;
var
    n : Integer;
begin
    //���ʣ���ӳ�����
    if self.FFollow<>0 then
    begin
        if self.FLow<RC_MAX_RANGE then
        begin
            //��������
            self.OutputCode(self.FDigits);
            for n:=1 to self.FFollow-1 do self.OutputCode($FF);
        end
        else
        begin
            //��������
            self.OutputCode(self.FDigits+1);
            for n:=1 to self.FFollow-1 do self.OutputCode($00);
        end;
    end;

    //���ʣ�����
    self.FLow:=self.FLow shl 1;
    n:=RC_CODE_BITS+1;
    repeat
        Dec(n,8);
        self.OutputCode(self.FLow shr n);
    until n<=0;

    self.FBuf:=nil;

    //���
end;

//��ʼ����������������������ָ�������뻺�����󶨣�
//InBuf����������
procedure TRCCoder.InitDecode(InBuf : PMBBuffer);
var
    n : Integer;
begin
    //��ʼ��
    self.FBuf:=InBuf;
    self.FLow:=0;
    self.FRange:=RC_MAX_RANGE;

    //�������
    self.FDigits:=0;

    n:=RC_CODE_BITS+1;
    repeat
        Dec(n,8);
        self.FDigits:=(self.FDigits shl 8) or self.InputCode;
    until n<=0;

    //���
end;

//���ݵ�ǰ�����䣬����ָ����Total����������ۻ�Ƶ�ȣ������أ�
//Total���ܼ�Ƶ�ȡ�
function TRCCoder.DecodeTarget(Total : Cardinal): Cardinal;
var
    Code : Cardinal;
begin
    Code:=self.FDigits shr 1;

    //��������ۻ�Ƶ��
    self.FRange:=self.FRange div Total;
    if Code<self.FLow then
    begin
        Result:=(Code+RC_MAX_RANGE-self.FLow) div self.FRange;
    end
    else
    begin
        Result:=(Code-self.FLow) div self.FRange;
    end;

    //���
end;

//����ָ����Ƶ�����ݵ�����ǰ���䣬������Ҫ�ӻ�����FBuf�ж������ݣ�
//�ڵ��ñ�����֮ǰ�����ȵ���DecodeTarget������
//����FBuf.Offsetȷ����ȡλ�ã���ȡ���޸�FBuf.Offset��
//CumFreq���ۻ�Ƶ�ȣ�
//Freq��Ƶ�ȡ�
procedure TRCCoder.Decode(CumFreq,Freq : Cardinal);
begin
    //�������
    Inc(self.FLow,CumFreq*self.FRange);
    self.FRange:=Freq*self.FRange;

    //��������
    while self.FRange<=RC_MIN_RANGE do
    begin
        self.FLow:=(self.FLow shl 8) and (RC_MAX_RANGE-1);
        self.FRange:=self.FRange shl 8;
        self.FDigits:=(self.FDigits shl 8) or self.InputCode;
    end;

    //���
end;

//�������룬������β������
procedure TRCCoder.FinishDecode;
begin
    self.FBuf:=nil;
end;

{TRCModel} //ͳ��ģ�ͣ�0�ף�

//�½�ͳ��ģ�͡�
constructor TRCModel.Create;
begin
    self.FCoder:=nil;
end;

//����ͳ��ģ�͡�
destructor TRCModel.Destroy;
begin
end;

//��ȡָ�����ŵ��ۻ�Ƶ�Ⱥ�Ƶ�ȣ�
//Symbol������ֵ��
//CumFreq�����ŵ��ۻ�Ƶ�ȣ�
//Freq�����ŵ�Ƶ�ȡ�
procedure TRCModel.GetFreq(Symbol : TRCSymbol; var CumFreq,Freq : Cardinal);
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
procedure TRCModel.IncFreq(Symbol : TRCSymbol);
var
    i,Id,Parent : Integer;
    Freq,NewFreq : Cardinal;
begin
    if self.FTotal=RC_MAX_FREQ then
    begin
        //����Ƶ��
        self.FTree[0]:=(self.FTree[0]+1) shr 1;
        self.FTotal:=self.FTree[0];
        for i:=1 to RC_SYMBOL_NO do
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
            until Id>RC_SYMBOL_NO;
        end;
    end;

    //����Ƶ��
    if Symbol=0 then Inc(self.FTree[0])
    else
    begin
        repeat
            Inc(self.FTree[Symbol]);
            Inc(Symbol,Symbol and -Symbol);
        until Symbol>RC_SYMBOL_NO;
    end;
    Inc(self.FTotal);

    //���
end;

//����ָ���Ĺ���Ƶ�ȣ����ض�Ӧ�ķ��ţ�
//EstFreq������Ƶ��ֵ��
function TRCModel.FindEstFreq(EstFreq : Cardinal): TRCSymbol;
var
    Mask,Id : Integer;
begin
    //�ų�����0�ͽ�����
    if EstFreq<self.FTree[0] then
    begin
        Result:=0; exit;
    end;
    Dec(EstFreq,self.FTree[0]);
    if EstFreq>=self.FTree[RC_SYMBOL_NO] then
    begin
        Result:=RC_EOM; exit;
    end;

    //����
    Result:=0;
    Mask:=RC_SYMBOL_NO shr 1;
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
procedure TRCModel.InitModel(Coder : PRCCoder);
var
    i,Id : Integer;
begin
    self.FCoder:=Coder;

    //��ʼ��Ƶ�ȣ���ʼʱÿ�����ŵ�Ƶ�ȶ�Ϊ1
    self.FTree[0]:=1;

    for i:=1 to RC_SYMBOL_NO do self.FTree[i]:=0;
    for i:=1 to RC_SYMBOL_NO do
    begin
        Id:=i;
        repeat
            Inc(self.FTree[Id]);
            Inc(Id,Id and -Id);
        until Id>RC_SYMBOL_NO;
    end;
    self.FTotal:=RC_SYMBOL_NO+1;

    //���
end;

//������������㷨��һ�����Ž��б��벢д�뵽FBuf�У�
//����FBuf.Offsetȷ������λ�ã�������޸�FBuf.Offset��FBuf.DataSize��
//Symbol������ֵ��
procedure TRCModel.Encode(Symbol : TRCSymbol);
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

//������������㷨�Դ�FBuf�н����һ�����ţ������أ�
//����FBuf.Offsetȷ����ȡλ�ã���ȡ���޸�FBuf.Offset��
function TRCModel.Decode: TRCSymbol;
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
procedure TRCModel.FinishModel;
begin
    self.FCoder:=nil;
end;

{TRCCoding} //�����������������TRCCoder��TRCModel�ļ򵥷�װ

//�½����������������
constructor TRCCoding.Create;
begin
    self.FCoder:=TRCCoder.Create;
    self.FModel:=TRCModel.Create;
end;

//�������������������
destructor TRCCoding.Destroy;
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
function TRCCoding.Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
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
//������InBuf�е�ѹ�����ݱ�����ʹ��TRCCoding.Encode����ģ�
//����InBuf.Offsetȷ����ȡλ�ã���ȡ���޸�InBuf.Offset��
//����OutBuf.Offsetȷ��д��λ�ã�д����޸�OutBuf.Offset��
//InBuf�����뻺������
//OutBuf�������������
function TRCCoding.Decode(var InBuf,OutBuf : TMBBuffer): Integer;
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
