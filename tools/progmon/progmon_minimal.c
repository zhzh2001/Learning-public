#include<stdio.h>
#include<windows.h>
#include<psapi.h>
int main(int argc,char* argv[])
{
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
    PROCESS_MEMORY_COUNTERS pmc;
	
	if(argc<2)
		return 1;
	
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.dwFlags=STARTF_USESTDHANDLES;
	if(!CreateProcess(0,argv[1],0,0,FALSE,CREATE_NO_WINDOW,0,0,&si,&pi))
		return 2;
	
	while(1)
	{
		if(WaitForSingleObject(pi.hProcess,0)==WAIT_OBJECT_0)
			break;
		Sleep(10);
	}
	
	GetProcessMemoryInfo(pi.hProcess,&pmc,sizeof(pmc));
	printf("Memory:%lf MiB\n",pmc.PeakPagefileUsage/1024.0/1024.0);
	
	return 0;
}