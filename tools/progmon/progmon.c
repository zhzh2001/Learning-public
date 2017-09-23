#include<stdio.h>
#include<windows.h>
#include<psapi.h>
int main(int argc,char* argv[])
{
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
    PROCESS_MEMORY_COUNTERS pmc;
	DWORD exitCode;
	FILETIME ct,et,kt,ut;
    SYSTEMTIME _kt,_ut;
	double fkt,fut;
	
	char cmd[MAX_PATH];
	int i;
	
	if(argc<2)
	{
		fprintf(stderr,"progmon:Too few arguments\nusage:progmon <exe_file>\n");
		return 1;
	}
	
	strcpy(cmd,argv[1]);
	for(i=2;i<argc;i++)
	{
		strcat(cmd," ");
		strcat(cmd,argv[i]);
	}
	
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.dwFlags=STARTF_USESTDHANDLES;
	if(!CreateProcess(0,cmd,0,0,FALSE,0,0,0,&si,&pi))
	{
		fprintf(stderr,"progmon:Can not execute %s\n",cmd);
		return 2;
	}
	
	while(1)
	{
		if(WaitForSingleObject(pi.hProcess,0)==WAIT_OBJECT_0)
			break;
		Sleep(10);
	}
	
	GetExitCodeProcess(pi.hProcess,&exitCode);
    if(exitCode&&exitCode!=STILL_ACTIVE)
    {
        fprintf(stderr,"progmon:Runtime error %u\n",exitCode);
		return 3;
    }
	
	GetProcessMemoryInfo(pi.hProcess,&pmc,sizeof(pmc));
	printf("Memory:%lf MiB\n",pmc.PeakPagefileUsage/1024.0/1024.0);
	
	GetProcessTimes(pi.hProcess,&ct,&et,&kt,&ut);
    FileTimeToSystemTime(&ut,&_ut);
	fut=_ut.wHour*3600+_ut.wMinute*60+_ut.wSecond+_ut.wMilliseconds/1000.0;
	FileTimeToSystemTime(&kt,&_kt);
	fkt=_kt.wHour*3600+_kt.wMinute*60+_kt.wSecond+_kt.wMilliseconds/1000.0;
	
	printf("Time:%lf s\n%lf + %lf (userTime + kernelTime)\n",fut+fkt,fut,fkt);
	
	return 0;
}