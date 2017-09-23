; �ű��� Inno Setup �ű��� ���ɣ�
; �йش��� Inno Setup �ű��ļ�����ϸ��������İ����ĵ���

#define MyAppName "��ͥͼ�����ϵͳ"
#define MyAppVersion "1.0"
#define MyAppExeName "Books.exe"

[Setup]
; ע: AppId��ֵΪ������ʶ��Ӧ�ó���
; ��ҪΪ������װ����ʹ����ͬ��AppIdֵ��
; (�����µ�GUID����� ����|��IDE������GUID��)
AppId={{1C291759-01A2-4223-B328-70D7008FFF1F}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
DefaultDirName={pf}\ͼ�����
DefaultGroupName={#MyAppName}
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "E:\���\Backup\Learn\Books\Books.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\Books.db"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\Books.MB"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\User.DB"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\BDE\blw32.dll"; DestDir: "{app}\BDE"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\BDE\fareast.btl"; DestDir: "{app}\BDE"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\BDE\idapi32.dll"; DestDir: "{app}\BDE"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\BDE\idpdx32.dll"; DestDir: "{app}\BDE"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\BDE\idr20009.dll"; DestDir: "{app}\BDE"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\BDE\usa.btl"; DestDir: "{app}\BDE"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\BDE\idsql32.dll"; DestDir: "{app}\BDE"; Flags: ignoreversion
Source: "E:\���\Backup\Learn\Books\BDE\charset.cvb"; DestDir: "{app}\BDE"; Flags: ignoreversionSource: "E:\���\Backup\Learn\Books\BDE\idbat32.dll"; DestDir: "{app}\BDE"; Flags: ignoreversionSource: "E:\���\Backup\Learn\Books\BDE\bantam.dll"; DestDir: "{app}\BDE"; Flags: ignoreversion
; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Registry]
Root:HKLM;Subkey:"Software\Borland\Database Engine";ValueType:string;ValueName:"DLLPATH";ValueData:"{app}\BDE"
Root:HKLM;Subkey:"Software\Borland\BLW32";ValueType:string;ValueName:"BLAPIPATH";ValueData:"{app}\BDE"Root:HKLM;Subkey:"Software\Borland\BLW32";ValueType:string;ValueName:"LOCALE_LIB0";ValueData:"fareasst.btl"
Root:HKLM;Subkey:"Software\Borland\BLW32";ValueType:string;ValueName:"LOCALE_LIB1";ValueData:"usa.btl"

