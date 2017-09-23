//
//��ʽ�����������㷨��ʵ��
//���ߣ�ҶҶ��2010��7��5��
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

unit CanonicalHuffman;

interface

uses
    MemoryBuffer;

const
    //���Ʊ���λ������������Cardinal���ͱ�����룬��������32λ
    CH_MAXLENGTH = 32;

type
    //�������ͣ�������Ҫ�����޸�ΪWord��Byte
    TCHSymbol = Integer;

    //��ʽ������������
    TCHEncode = class
    private
        FContent : Integer; //������Ϣ��
        FBuf : array of Cardinal; //������������ΪFContent*2

        FHeapCount : Integer; //����Ԫ�ظ���
        FMaxBitLen : Integer; //ʵ��������λ��

        FOutBuf : PMBBuffer; //���������

        FEncode : TCHEncode; //������������������ѹ��

        procedure HeapInsert(Id : Cardinal);
        procedure HeapDelete;
        procedure LengthLimited;
    public
        Freq : PMBCardinalAry; //Ƶ�ȱ�

        constructor Create;
        destructor Destroy; override;

        //�������
        procedure InitEncode(OutBuf : PMBBuffer; Content : Integer);
        procedure AllocCode;
        procedure SaveBitLenG;
        procedure SaveBitLenH;
        procedure Encode(Symbol : TCHSymbol);
        procedure FinishEncode;
    end;

    //��ʽ������������
    TCHDecode = class
    private
        FContent : Integer; //������Ϣ��
        FSymList : array of TCHSymbol; //��������ķ����б�����ΪFContent

        FMaxBitLen : Integer; //ʵ��������λ��

        FFirstCode : array [1..CH_MAXLENGTH] of Cardinal; //ÿ��λ�����ױ���
        FSymCount : array [1..CH_MAXLENGTH] of Integer; //ÿ��λ���ķ�����
        FSymIndex : array [1..CH_MAXLENGTH] of Integer; //ÿ��λ����Ӧ�ķ�����FSymList�п�ʼ��λ��

        FFastLen : Integer; //���λ��
        FFastSymList : array of TCHSymbol; //�������б�����Ϊ1 shl FFastLen
        FFastBitLen : array of Byte; //���λ���б�����Ϊ1 shl FFastLen

        FInBuf : PMBBuffer; //���뻺����

        FDecode : TCHDecode; //�����������������ν�ѹ��

        procedure Construct;
    public
        constructor Create;
        destructor Destroy; override;

        //�������
        procedure InitDecode(InBuf : PMBBuffer; Content : Integer; FastLen : Integer);
        procedure LoadBitLenG;
        procedure LoadBitLenH;
        function Decode: TCHSymbol;
        procedure FinishDecode;
    end;

    //��ʽ�����������������TCHEncode��TCHDecode�ļ򵥷�װ
    TCHCoding = class
    private
        FEncode : TCHEncode; //������
        FDecode : TCHDecode; //������
    public
        constructor Create;
        destructor Destroy; override;

        function Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
        function Decode(var InBuf,OutBuf : TMBBuffer): Integer;

        function Encode16(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
        function Decode16(var InBuf,OutBuf : TMBBuffer): Integer;
    end;


implementation

{TCHEncode} //��ʽ������������

//�½���ʽ��������������
constructor TCHEncode.Create;
begin
    self.FContent:=0;
    SetLength(self.FBuf,0);

    self.FEncode:=nil;

    self.Freq:=nil;
end;

//���ٷ�ʽ��������������
destructor TCHEncode.Destroy;
begin
    SetLength(self.FBuf,0);
    if self.FEncode<>nil then self.FEncode.Free;
end;

//��ָ��Ƶ�Ȳ���ѣ���Ƶ��Ϊ�ؼ��ֵ���С�ѣ��Ѻ�Ƶ�ȶ�������FBuf�У�
//Id��Ƶ����FBuf�е�������Ƶ��λ��FBuf���ұߣ�
//��������������浽���У�����λ��FBuf����ߣ�
//Id��Ƶ�ȵ�������
procedure TCHEncode.HeapInsert(Id : Cardinal);
var
    Parent,Child : Integer;
begin
    //�ն�
    if self.FHeapCount=0 then
    begin
        self.FBuf[0]:=Id;
        Inc(self.FHeapCount);
        exit;
    end;

    //����Ƶ��
    Child:=self.FHeapCount;
    Parent:=((Child+1) shr 1)-1;
    while self.FBuf[self.FBuf[Parent]]>self.FBuf[Id] do
    begin
        self.FBuf[Child]:=self.FBuf[Parent];
        Child:=Parent;
        if Parent=0 then break;
        Parent:=((Parent+1) shr 1)-1;
    end;
    self.FBuf[Child]:=Id;
    Inc(self.FHeapCount);
end;

//�Ӷ���ɾ��һ��Ƶ�ȣ�ɾ��Ƶ�ȵ���������ƶ�����ǰ�ѵ�ĩβ��
procedure TCHEncode.HeapDelete;
var
    Id : Cardinal;
    Parent,Child : Integer;
begin
    Id:=self.FBuf[0];
    Dec(self.FHeapCount);

    //ɾ��Ƶ��
    Parent:=0;
    Child:=1;
    while Child<=self.FHeapCount do
    begin
        if (Child<self.FHeapCount) and
           (self.FBuf[self.FBuf[Child]]>
            self.FBuf[self.FBuf[Child+1]]) then Inc(Child);

        if self.FBuf[self.FBuf[Child]]>=
           self.FBuf[self.FBuf[self.FHeapCount]] then break;

        self.FBuf[Parent]:=self.FBuf[Child];
        Parent:=Child;
        Child:=((Child+1) shl 1)-1;
    end;
    self.FBuf[Parent]:=self.FBuf[self.FHeapCount];
    self.FBuf[self.FHeapCount]:=Id;
end;

//���Ʊ���λ����������ı���λ����������λ��ʱ��
//�ú��������λ��������������ʹ���������λ���Ĵ�С��
//���øú���ǰ���轫����λ��������FBuf[FContent..FContent*2-1]�У�
//��������ʱ����FBuf��ǰ�벿�ݱ��������������ݡ�
procedure TCHEncode.LengthLimited;
var
    Num : array of Integer;
    i,SymCount,Id,Sum,t : Integer;
    Val1,Val2 : Cardinal;
begin
    //����������λ����Ϊ��һ�ؼ��֣�����ֵ��Ϊ�ڶ��ؼ��֣�
    //��С���������������������浽FBuf[0..FContent-1]��
    SetLength(Num,self.FMaxBitLen+1);

    SymCount:=0; //ʵ�ʳ��ֵķ�����
    for i:=self.FContent to (self.FContent*2)-1 do
    begin
        if self.FBuf[i]<>0 then
        begin
            Inc(Num[self.FBuf[i]]); Inc(SymCount);
        end;
    end;

    Sum:=0;
    for i:=1 to self.FMaxBitLen do
    begin
        t:=Num[i]; Num[i]:=Sum; Inc(Sum,t);
    end;

    for i:=self.FContent to (self.FContent*2)-1 do
    begin
        if self.FBuf[i]<>0 then
        begin
            self.FBuf[Num[self.FBuf[i]]]:=i;
            Inc(Num[self.FBuf[i]]);
        end;
    end;

    SetLength(Num,0); //�������

    //���µ�������λ��
    Id:=SymCount-1;
    repeat
        {//����������޷������������Լ��ͣ�
        if self.FBuf[self.FBuf[0]]>=CH_MAXLENGTH then
        begin
            raise Exception.Create('λ��������޷�������룡');
        end;//}

        //��ǰ����С������λ����λ��
        for i:=Id downto 0 do
        begin
            if self.FBuf[self.FBuf[i]]<CH_MAXLENGTH then
            begin
                Id:=i; break;
            end;
        end;

        //����
        Inc(self.FBuf[self.FBuf[Id]]);
        Val1:=self.FBuf[self.FBuf[SymCount-1]]-1;

        for i:=SymCount-3 downto Id do
        begin
            Val2:=self.FBuf[self.FBuf[i]];
            if Val1>=Val2 then
            begin
                self.FBuf[self.FBuf[i+2]]:=Val1;
                break;
            end;
            self.FBuf[self.FBuf[i+2]]:=Val2;
        end;
        for i:=i downto Id do
        begin
            self.FBuf[self.FBuf[i+1]]:=self.FBuf[self.FBuf[i]];
        end;

        Inc(Id); //�ӵ�������λ�ÿ�ʼ

        self.FMaxBitLen:=self.FBuf[self.FBuf[SymCount-1]];

    until self.FMaxBitLen<=CH_MAXLENGTH;

    //���
end;

//��ʼ����������������������ָ������������󶨣�
//OutBuf�������������
//Content��������Ϣ����
procedure TCHEncode.InitEncode(OutBuf : PMBBuffer; Content : Integer);
var
    i : Integer;
begin
    self.FOutBuf:=OutBuf;

    //���仺����
    if Content>self.FContent then SetLength(self.FBuf,Content*2);
    self.FContent:=Content;

    //Ƶ������
    self.Freq:=@(self.FBuf[self.FContent]);
    for i:=0 to self.FContent-1 do self.Freq[i]:=0;
end;

//������ŵı���λ����������룬ͬʱ����������λ��FMaxBitLen��
//���øú���ǰ���轫����Ƶ�ȱ�����Freq�У�
//��ע��Freqָ�򻺳���FBuf[FContent..FContent*2-1]����
//��������ʱ����FBuf��ǰ�벿�ݱ�����ʱ���ݣ�
//�������������ı��뱣�浽FBuf[0..FContent-1]�У�
//����λ�����浽FBuf[FContent..FContent*2-1]�У�
//ԭ�е�Ƶ�����ݽ��ᱻ�滻����
procedure TCHEncode.AllocCode;
var
    i : Integer;
    Id0,Id1,Id2 : Cardinal;
    Code,t : Cardinal;
    Num : array [1..CH_MAXLENGTH] of Cardinal;
begin
    self.Freq:=nil; //��������

    //Ƶ�Ȳ�����У������ݱ��浽FBuf[0..FContent-1]��
    self.FHeapCount:=0;
    for i:=self.FContent to (self.FContent*2)-1 do
    begin
        if self.FBuf[i]<>0 then self.HeapInsert(i);
    end;

    //ֻ����һ�ַ���
    if self.FHeapCount=1 then
    begin
        self.FBuf[self.FBuf[0]]:=1;
        self.FBuf[self.FBuf[0]-Cardinal(self.FContent)]:=0;
        self.FMaxBitLen:=1;
        exit;
    end;

    //���ಿ������
    for i:=self.FHeapCount to self.FContent-1 do self.FBuf[i]:=0;

    //��������
    repeat
        //�Ӷ���ȡ������Ƶ��
        Id0:=self.FHeapCount-1;
        self.HeapDelete;
        self.HeapDelete;

        //�ϲ�Ƶ��
        Id1:=self.FBuf[Id0];
        Id2:=self.FBuf[Id0-1];
        self.FBuf[Id0]:=self.FBuf[Id1]+self.FBuf[Id2];

        //������ϵ
        self.FBuf[Id1]:=Id0;
        self.FBuf[Id2]:=Id0;

        //���²����
        self.HeapInsert(Id0);

    until self.FHeapCount=1;

    //����λ�������ݱ��浽FBuf[FContent..FConten*2-1]��
    self.FMaxBitLen:=0;
    self.FBuf[1]:=0;
    for i:=2 to (self.FContent*2)-1 do
    begin
        if self.FBuf[i]<>0 then
        begin
            self.FBuf[i]:=self.FBuf[self.FBuf[i]]+1;
            if self.FBuf[i]>Cardinal(self.FMaxBitLen) then
            begin
                self.FMaxBitLen:=self.FBuf[i];
            end;
        end;
    end;

    //λ�����
    if self.FMaxBitLen>CH_MAXLENGTH then self.LengthLimited;

    //����ͬ����ţ����ݱ��浽FBuf[0..FContent-1]��
    for i:=1 to self.FMaxBitLen do Num[i]:=0;

    for i:=self.FContent to (self.FContent*2)-1 do
    begin
        if self.FBuf[i]<>0 then
        begin
            self.FBuf[i-self.FContent]:=Num[self.FBuf[i]];
            Inc(Num[self.FBuf[i]]);
        end;
    end;

    //�����ױ���
    Code:=0;
    for i:=1 to self.FMaxBitLen do
    begin
        t:=Num[i]; Num[i]:=Code; Code:=(Code+t) shl 1;
    end;

    //������룬���ݱ��浽FBuf[0..FContent-1]��
    for i:=0 to self.FContent-1 do
    begin
        Inc(self.FBuf[i],Num[self.FBuf[i+self.FContent]]);
    end;

    //���
end;

//����ָ�����ײ��㷨��������ѹ����д�뵽������FOutBuf�У�
//����������ʱ��չ��������
//����FOutBuf.Offsetȷ��д��λ�ã�д����޸�FOutBuf.Offset��
//���øú���ǰҪ��ȷ���Ѿ����ù�AllocCode������롣
procedure TCHEncode.SaveBitLenG;
var
    Id,n : Integer;
begin
    //д�����λ��
    MBEncodeEG(self.FOutBuf^,self.FMaxBitLen);

    //д��λ������
    Id:=self.FContent;
    while Id<(self.FContent*2) do
    begin
        if self.FBuf[Id]=0 then
        begin
            //����Ϊ0��λ�����ݸ���
            n:=Id; Inc(Id);
            while (Id<(self.FContent*2)) and (self.FBuf[Id]=0) do Inc(Id);
            n:=Id-n;

            //д������
            MBEncodeEG(self.FOutBuf^,0);
            MBEncodeEG(self.FOutBuf^,n);
        end
        else
        begin
            //д�벻Ϊ0��λ������
            MBEncodeEG(self.FOutBuf^,Cardinal(self.FMaxBitLen)-self.FBuf[Id]+1);
            Inc(Id);
        end;
    end;

    //���
end;

//���ù������㷨��������ѹ����д�뵽������FOutBuf�У�
//����������ʱ��չ��������
//����FOutBuf.Offsetȷ��д��λ�ã�д����޸�FOutBuf.Offset��
//���øú���ǰҪ��ȷ���Ѿ����ù�AllocCode������롣
procedure TCHEncode.SaveBitLenH;
var
    Id,n : Integer;
begin
    //д�����λ��
    MBEncodeEG(self.FOutBuf^,self.FMaxBitLen);

    //����������
    if self.FEncode=nil then self.FEncode:=TCHEncode.Create;
    self.FEncode.InitEncode(self.FOutBuf,self.FMaxBitLen+1);

    //ͳ��Ƶ��
    Id:=self.FContent;
    while Id<(self.FContent*2) do
    begin
        if self.FBuf[Id]=0 then
        begin
            Inc(self.FEncode.Freq[0]); //�ظ���0ֻͳ��1��
            Inc(Id);

            //�����ظ�Ϊ0��λ������
            while (Id<(self.FContent*2)) and (self.FBuf[Id]=0) do Inc(Id);
        end
        else
        begin
            //��Ϊ0��λ������
            Inc(self.FEncode.Freq[self.FBuf[Id]]);
            Inc(Id);
        end;
    end;

    //������벢�������
    self.FEncode.AllocCode;
    self.FEncode.SaveBitLenG;

    //����
    Id:=self.FContent;
    while Id<(self.FContent*2) do
    begin
        if self.FBuf[Id]=0 then
        begin
            //д������
            self.FEncode.Encode(0);

            //����Ϊ0��λ�����ݸ�����д��
            n:=Id; Inc(Id);
            while (Id<(self.FContent*2)) and (self.FBuf[Id]=0) do Inc(Id);
            n:=Id-n;

            MBEncodeEG(self.FOutBuf^,n);
        end
        else
        begin
            //д�벻Ϊ0��λ������
            self.FEncode.Encode(self.FBuf[Id]);
            Inc(Id);
        end;
    end;
    self.FEncode.FinishEncode;

    //���
end;

//����һ�����Ų�д�뵽������FOutBuf�У�
//����FOutBuf.Offsetȷ��д��λ�ã�д����޸�FOutBuf.Offset��
//Symbol�����š�
procedure TCHEncode.Encode(Symbol : TCHSymbol);
begin
    MBWriteBit(
        self.FOutBuf^,
        self.FBuf[Symbol],
        self.FBuf[Symbol+self.FContent]);
end;

//�������룬������β������
procedure TCHEncode.FinishEncode;
begin
    self.FOutBuf:=nil;
end;

{TCHDecode} //��ʽ������������

//�½���ʽ��������������
constructor TCHDecode.Create;
begin
    self.FContent:=0;
    SetLength(self.FSymList,0);

    self.FFastLen:=0;
    SetLength(self.FFastSymList,0);
    SetLength(self.FFastBitLen,0);

    self.FDecode:=nil;
end;

//���ٷ�ʽ��������������
destructor TCHDecode.Destroy;
begin
    SetLength(self.FSymList,0);
    SetLength(self.FFastSymList,0);
    SetLength(self.FFastBitLen,0);

    if self.FDecode<>nil then self.FDecode.Free;
end;

//��ʼ����������������������ָ�����뻺�����󶨣�
//InBuf�����뻺������
//Content��������Ϣ��
//FastLen�����λ����
procedure TCHDecode.InitDecode(InBuf : PMBBuffer; Content : Integer; FastLen : Integer);
begin
    self.FInBuf:=InBuf;

    //���仺����
    if Content>self.FContent then SetLength(self.FSymList,Content);
    self.FContent:=Content;

    self.FFastLen:=FastLen;
end;

//������������ĸ������ݱ�
//���øú���ǰ���轫����λ��������FSymList�С�
procedure TCHDecode.Construct;
var
    i,t,l,m,Sum : Integer;
    Id1,Id2,Sym1,Sym2 : Integer;
    Flag : array of Cardinal;
    Code : Cardinal;
begin
    //����������λ����Ϊ��һ�ؼ��֣�����ֵ��Ϊ�ڶ��ؼ��֣�
    //�����������浽FSymList�У�ԭλ�����ݽ��ᱻ�滻��
    //ͬʱͳ��ÿ��λ���ķ����������浽FSymCount��
    for i:=1 to self.FMaxBitLen do self.FSymCount[i]:=0;

    for i:=0 to self.FContent-1 do
    begin
        if self.FSymList[i]<>0 then Inc(self.FSymCount[self.FSymList[i]]);
    end;

    Sum:=0;
    for i:=1 to self.FMaxBitLen do
    begin
        self.FSymIndex[i]:=Sum;
        Inc(Sum,self.FSymCount[i]);
    end;

    for i:=0 to self.FContent-1 do
    begin
        t:=self.FSymList[i];
        if t<>0 then
        begin
            self.FSymList[i]:=self.FSymIndex[t]+1; //+1�����ֳ�0
            Inc(self.FSymIndex[t]);
        end;
    end;

    //����������������ţ�
    //��������ķ��ű��浽FSymList�У�ԭ�����������ᱻ�滻
    t:=(self.FContent+31) shr 5;
    SetLength(Flag,t);

    for i:=0 to self.FContent-1 do
    begin
        if (self.FSymList[i]=0) or
           ((Flag[i shr 5] and (1 shl (i and 31)))<>0) then continue;

        //����λ��
        Sym2:=i;
        Id2:=self.FSymList[i];
        self.FSymList[i]:=0;
        repeat
            Sym1:=Sym2;
            Id1:=Id2-1;

            Sym2:=Id1;
            Id2:=self.FSymList[Id1];

            self.FSymList[Id1]:=Sym1;
            Flag[Id1 shr 5]:=Flag[Id1 shr 5] or (1 shl (Id1 and 31));

        until Id2=0;
    end;

    SetLength(Flag,0);

    //�����ױ���FFirstCode�ͷ�������FSymIndex
    Code:=0;
    Sum:=0;
    for i:=1 to self.FMaxBitLen do
    begin
        self.FFirstCode[i]:=Code;
        Code:=(Code+Cardinal(self.FSymCount[i])) shl 1;

        self.FSymIndex[i]:=Sum;
        Inc(Sum,self.FSymCount[i]);
    end;

    //������
    if self.FFastLen=0 then exit;
    if self.FFastLen>self.FMaxBitLen then self.FFastLen:=self.FMaxBitLen;
    if (1 shl self.FFastLen)>Length(self.FFastSymList) then
    begin
        SetLength(self.FFastSymList,1 shl self.fFastLen);
        SetLength(self.FFastBitLen,1 shl self.fFastLen);
    end;

    //����λ��С�ڿ��λ�������
    Id1:=0;
    for i:=1 to self.FFastLen-1 do
    begin
        t:=(1 shl (self.FFastLen-i))-1;

        for l:=0 to self.FSymCount[i]-1 do
        begin
            Sym1:=self.FSymList[self.FSymIndex[i]+l];

            for m:=0 to t do
            begin
                self.FFastSymList[Id1]:=Sym1;
                self.FFastBitLen[Id1]:=i;
                Inc(Id1);
            end;
        end;
    end;

    //����λ�����ڿ��λ�������
    for l:=0 to self.FSymCount[self.FFastLen]-1 do
    begin
        self.FFastSymList[Id1]:=self.FSymList[self.FSymIndex[self.FFastLen]+l];
        self.FFastBitLen[Id1]:=self.FFastLen;
        Inc(Id1);
    end;

    //����λ�����ڿ��λ�������
    for i:=self.FFastLen+1 to self.FMaxBitLen do
    begin
        t:=i-self.FFastLen;

        for l:=0 to self.FSymCount[i]-1 do
        begin
            if Id1=Integer((self.FFirstCode[i]+Cardinal(l)) shr t) then
            begin
                self.FFastSymList[Id1]:=0; //���Ų�ȷ��
                self.FFastBitLen[Id1]:=i;
                Inc(Id1);
            end;
        end;
    end;

    //���
end;

//����ָ�����ײ��㷨��FInBuf�ж�ȡ����ѹ�������
//�������е�ѹ����������ʹ��TCHEncode.SaveBitLenG����ģ�
//����FInBuf.Offsetȷ����ȡλ�ã���ȡ���޸�FInBuf.Offset��
//��������ú��������Construct���������
procedure TCHDecode.LoadBitLenG;
var
    Id,n,i : Integer;
begin
    //��ȡ���λ��
    self.FMaxBitLen:=MBDecodeEG(self.FInBuf^);

    //��ȡλ������
    Id:=0;
    while Id<self.FContent do
    begin
        n:=MBDecodeEG(self.FInBuf^);
        if n=0 then
        begin
            //Ϊ0��λ������
            n:=MBDecodeEG(self.FInBuf^);
            for i:=1 to n do
            begin
                self.FSymList[Id]:=0; Inc(Id);
            end;
        end
        else
        begin
            //��Ϊ0��λ������
            self.FSymList[Id]:=self.FMaxBitLen-n+1;
            Inc(Id);
        end;
    end;

    //���������
    self.Construct;

    //���
end;

//���ù������㷨��FInBuf�ж�ȡ����ѹ�������
//�������е�ѹ����������ʹ��TCHEncode.SaveBitLenH����ģ�
//����FInBuf.Offsetȷ����ȡλ�ã���ȡ���޸�FInBuf.Offset��
//��������ú��������Construct���������
procedure TCHDecode.LoadBitLenH;
var
    Id,i,n : Integer;
begin
    //��ȡ���λ��
    self.FMaxBitLen:=MBDecodeEG(self.FInBuf^);

    //����������
    if self.FDecode=nil then self.FDecode:=TCHDecode.Create;
    self.FDecode.InitDecode(self.FInBuf,self.FMaxBitLen+1,8);
    self.FDecode.LoadBitLenG;

    //��ȡλ������
    Id:=0;
    while Id<self.FContent do
    begin
        n:=self.FDecode.Decode;
        if n=0 then
        begin
            //Ϊ0��λ������
            n:=MBDecodeEG(self.FInBuf^);
            for i:=1 to n do
            begin
                self.FSymList[Id]:=0; Inc(Id);
            end;
        end
        else
        begin
            //��Ϊ0��λ������
            self.FSymList[Id]:=n;
            Inc(Id);
        end;
    end;
    self.FDecode.FinishDecode;

    //���������
    self.Construct;

    //���
end;

//�ӻ�����FInBuf�н����һ�����ţ������أ�
//����FInBuf.Offsetȷ����ȡλ�ã���ȡ���޸�FInBuf.Offset��
function TCHDecode.Decode: TCHSymbol;
var
    Code : Cardinal;
    LastOff,Id,Num : Integer;
begin
    Result:=0;

    with self.FInBuf^ do
    begin
        if DataType<>dtBit then MBSetType(self.FInBuf^,dtBit);
        LastOff:=Offset;
    end;

    //һ���Զ�ȡ32λ����
    Code:=MBReadBit(self.FInBuf^,32);

    //���ҿ��
    if self.FFastLen=0 then Id:=1
    else
    begin
        Id:=Code shr (32-self.FFastLen);

        if self.FFastBitLen[Id]<=self.FFastLen then
        begin
            //ֱ������
            Result:=self.FFastSymList[Id];
            self.FInBuf.Offset:=LastOff+self.FFastBitLen[Id];
            exit;
        end
        else
        begin
            //û������
            Id:=self.FFastBitLen[Id];
        end;
    end;

    //����
    for Id:=Id to self.FMaxBitLen do
    begin
        if self.FSymCount[Id]<>0 then
        begin
            Num:=(Code shr (32-Id))-self.FFirstCode[Id];

            if Num<self.FSymCount[Id] then
            begin
                Result:=self.FSymList[self.FSymIndex[Id]+Num];
                break;
            end;
        end;
    end;

    //����λ��
    self.FInBuf.Offset:=LastOff+Id;

    //���
end;

//�������룬������β������
procedure TCHDecode.FinishDecode;
begin
    self.FInBuf:=nil;
end;

{TCHCoding} //��ʽ�����������������TCHEncode��TCHDecode�ļ򵥷�װ

//�½���ʽ���������������
constructor TCHCoding.Create;
begin
    self.FEncode:=nil;
    self.FDecode:=nil;
end;

//���ٷ�ʽ���������������
destructor TCHCoding.Destroy;
begin
    if self.FEncode<>nil then self.FEncode.Free;
    if self.FDecode<>nil then self.FDecode.Free;
end;

//�ӻ�����InBuf�ж�ȡSize���ȵ����ݽ���ѹ�������浽������OutBuf�У�
//����д�뵽������OutBuf�����ݵĴ�С���ֽڣ���
//������OutBuf����ʱ��չ��������
//����InBuf.Offsetȷ����ȡλ�ã���ȡ���޸�InBuf.Offset��
//����OutBuf.Offsetȷ��д��λ�ã�д����޸�OutBuf.Offset��
//InBuf�����뻺������
//OutBuf�������������
//Size�����ݴ�С���ֽڣ���
function TCHCoding.Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
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

    //������������8λ���ţ�
    if self.FEncode=nil then self.FEncode:=TCHEncode.Create;
    self.FEncode.InitEncode(@OutBuf,$100);

    //�������ݳ���
    MBWrite(OutBuf,ReadSize,SizeOf(Integer));

    //ͳ�Ƹ���
    for i:=0 to ReadSize-1 do Inc(self.FEncode.Freq[Dest[i]]);

    //������벢�������
    self.FEncode.AllocCode;
    self.FEncode.SaveBitLenH;

    //����
    for i:=0 to ReadSize-1 do self.FEncode.Encode(Dest[i]);
    self.FEncode.FinishEncode;

    //����д�볤��
    MBSetType(OutBuf,dtByte);
    Result:=OutBuf.Offset-LastOff;

    //���
end;

//�ӻ�����InBuf�ж�ȡ���ݽ��н�ѹ�������浽������OutBuf�У�
//����д�뵽������OutBuf�����ݵĴ�С���ֽڣ���
//������OutBuf����ʱ��չ��������
//������InBuf�е�ѹ�����ݱ�����ʹ��TCHCoding.Encode����ģ�
//����InBuf.Offsetȷ����ȡλ�ã���ȡ���޸�InBuf.Offset��
//����OutBuf.Offsetȷ��д��λ�ã�д����޸�OutBuf.Offset��
//InBuf�����뻺������
//OutBuf�������������
function TCHCoding.Decode(var InBuf,OutBuf : TMBBuffer): Integer;
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

    //������������8λ���ţ�
    if self.FDecode=nil then self.FDecode:=TCHDecode.Create;
    self.FDecode.InitDecode(@InBuf,$100,8); //ʹ��8λ���

    //�������
    self.FDecode.LoadBitLenH; //H����

    //����
    for i:=0 to Result-1 do Sour[i]:=self.FDecode.Decode;
    self.FDecode.FinishDecode;

    //���
end;

//�ӻ�����InBuf�ж�ȡSize���ȵ����ݽ���ѹ�������浽������OutBuf�У�
//����д�뵽������OutBuf�����ݵĴ�С���ֽڣ���
//������OutBuf����ʱ��չ��������
//����InBuf.Offsetȷ����ȡλ�ã���ȡ���޸�InBuf.Offset��
//����OutBuf.Offsetȷ��д��λ�ã�д����޸�OutBuf.Offset��
//��TCHCoding.Encode��ͬ���Ǳ�����ÿ��ѹ�������ֽڣ�16λ���ķ��ţ�
//InBuf�����뻺������
//OutBuf�������������
//Size�����ݴ�С���ֽڣ���
function TCHCoding.Encode16(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
var
    i,ReadSize,NeedSize,LastOff : Integer;
    Dest : PMBWordAry;
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

    //������������16λ���ţ�
    if self.FEncode=nil then self.FEncode:=TCHEncode.Create;
    self.FEncode.InitEncode(@OutBuf,$10000);

    //�������ݳ���
    MBWrite(OutBuf,ReadSize,SizeOf(Integer));
    ReadSize:=(ReadSize+1) shr 1;

    //ͳ�Ƹ���
    for i:=0 to ReadSize-1 do Inc(self.FEncode.Freq[Dest[i]]);

    //������벢�������
    self.FEncode.AllocCode;
    self.FEncode.SaveBitLenH;

    //����
    for i:=0 to ReadSize-1 do self.FEncode.Encode(Dest[i]);
    self.FEncode.FinishEncode;

    //����д�볤��
    MBSetType(OutBuf,dtByte);
    Result:=OutBuf.Offset-LastOff;

    //���
end;

//�ӻ�����InBuf�ж�ȡ���ݽ��н�ѹ�������浽������OutBuf�У�
//����д�뵽������OutBuf�����ݵĴ�С���ֽڣ���
//������OutBuf����ʱ��չ��������
//������InBuf�е�ѹ�����ݱ�����ʹ��TCHCoding.Encode16����ģ�
//����InBuf.Offsetȷ����ȡλ�ã���ȡ���޸�InBuf.Offset��
//����OutBuf.Offsetȷ��д��λ�ã�д����޸�OutBuf.Offset��
//��TCHCoding.Decode��ͬ���Ǳ�����ÿ�ν�ѹ�������ֽڣ�16λ���ķ��ţ�
//InBuf�����뻺������
//OutBuf�������������
function TCHCoding.Decode16(var InBuf,OutBuf : TMBBuffer): Integer;
var
    i,NeedSize : Integer;
    Sour : PMBWordAry;
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

    //������������16λ���ţ�
    if self.FDecode=nil then self.FDecode:=TCHDecode.Create;
    self.FDecode.InitDecode(@InBuf,$10000,8); //ʹ��8λ���

    //�������
    self.FDecode.LoadBitLenH; //H����

    //����
    for i:=0 to ((Result+1) shr 1)-1 do Sour[i]:=self.FDecode.Decode;
    self.FDecode.FinishDecode;

    //���
end;

//��Ԫ����
end.

