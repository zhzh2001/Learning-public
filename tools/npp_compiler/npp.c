#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

char *exe;

void _pause();

void show_help();

void error(char* msg);

#define MAX_NAME 260

int main(int argc,char* argv[])
{
	char fullname[MAX_NAME+1],*std=NULL,*opt=NULL;
	FILE *f;
	int i,warn=1,debug=0,exec=1,cname=0,lgmp=0,lmpfr=0,progmon=0,lqmath=0;
	
	exe=argv[0];
	if(argc==1||!strcmp(argv[1],"-h")||!strcmp(argv[1],"--help")||!strcmp(argv[1],"/?"))
		show_help();
	if(argc<4)
		error("too few arguments");
	
	chdir(argv[1]);
	strcpy(fullname,argv[2]);
	strcat(fullname,argv[3]);
	f=fopen(fullname,"r");
	if(!f)
	{
		char msg[MAX_NAME+1];
#ifdef __WIN32
		sprintf(msg,"file %s\\%s does not exists",argv[1],fullname);
#endif
#ifdef __linux
		sprintf(msg,"file %s/%s does not exists",argv[1],fullname);
#endif
		error(msg);
	}
	fclose(f);
	
	for(i=4;i<argc;i++)
		if(!strcmp(argv[i],"-nowarn"))
			warn=0;
		else
			if(!strcmp(argv[i],"-debug"))
				debug=1;
			else
				if(!strcmp(argv[i],"-noexec"))
					exec=0;
				else
					if(!strcmp(argv[i],"-cname"))
						cname=1;
					else
						if(!strncmp(argv[i],"-std=",5))
							std=argv[i];
						else
							if(!strcmp(argv[i],"-lgmp"))
								lgmp=1;
							else
								if(!strcmp(argv[i],"-lmpfr"))
									lmpfr=1;
								else
									if(!strncmp(argv[i],"-O",2))
										opt=argv[i];
									else
										if(!strcmp(argv[i],"-pm"))
											progmon=1;
										else
											if(!strcmp(argv[i],"-lquadmath"))
												lqmath=1;
	
	if(!strcmp(argv[3],".cpp")||!strcmp(argv[3],".cxx")||!strcmp(argv[3],".cc"))
	{
		char cmd[MAX_NAME+1],target[MAX_NAME+1];
		sprintf(cmd,"g++ %s",fullname);
		if(warn)
			strcat(cmd," -Wall");
		if(debug)
			strcat(cmd," -g");
		if(cname)
		{
			strcat(cmd," -o ");
			strcat(cmd,argv[2]);
			strcpy(target,argv[2]);
#ifdef __WIN32
			strcat(target,".exe");
#endif
		}
		else
#ifdef __WIN32
			strcpy(target,"a.exe");
#endif
#ifdef __linux
			strcpy(target,"a.out");
#endif
		if(std)
		{
			strcat(cmd," ");
			strcat(cmd,std);
		}
		if(opt)
		{
			strcat(cmd," ");
			strcat(cmd,opt);
		}
		
		if(lgmp)
			strcat(cmd," -lgmpxx -lgmp");
		if(lmpfr)
		{
			strcat(cmd," -lmpfr");
#ifdef __WIN32
			strcat(cmd," -lgmp");
#endif
		}
		if(lqmath)
			strcat(cmd," -lquadmath");
		
		if(system(cmd))
			error("compile error");
		
		if(exec)
		{
			if(debug)
			{
				sprintf(cmd,"gdb %s",target);
				if(system(cmd))
				{
					char msg[MAX_NAME+1];
					sprintf(msg,"cannot execute %s",target);
					error(msg);
				}
			}
			else
				if(progmon)
				{
					sprintf(cmd,"progmon %s",target);
					system(cmd);
				}
				else
				{
					clock_t t;
					int code;
#ifdef __WIN32
					strcpy(cmd,target);
#endif
#ifdef __linux
					sprintf(cmd,"./%s",target);
#endif
					t=clock();
					code=system(cmd);
					printf("%s exited after %.3lf s with code=%d\n",target,(double)(clock()-t)/CLOCKS_PER_SEC,code);
				}
			
#ifdef __WIN32
			sprintf(cmd,"del %s",target);
#endif
#ifdef __linux
			sprintf(cmd,"rm %s",target);
#endif
			if(system(cmd))
			{
				char msg[MAX_NAME+1];
				sprintf(msg,"cannot remove %s",target);
				error(msg);
			}
		}
	}
	else
		if(!strcmp(argv[3],".pas")||!strcmp(argv[3],".pp"))
		{
			char cmd[MAX_NAME+1],target[MAX_NAME+1];
			sprintf(cmd,"fpc %s",fullname);
			if(debug)
				strcat(cmd," -g");
			if(opt)
			{
				strcat(cmd," ");
				strcat(cmd,opt);
			}
			if(system(cmd))
				error("compile error");
#ifdef __WIN32
			sprintf(cmd,"del %s.o",argv[2]);
#endif
#ifdef __linux
			sprintf(cmd,"rm %s.o",argv[2]);
#endif
			if(system(cmd))
			{
				char msg[MAX_NAME+1];
				sprintf(msg,"cannot remove %s.o",argv[2]);
				error(msg);
			}
#ifdef __WIN32
			sprintf(target,"%s.exe",argv[2]);
#endif
#ifdef __linux
			sprintf(target,"%s.out",argv[2]);
#endif
			
			if(exec)
			{
				if(debug)
				{
					sprintf(cmd,"gdb %s",target);
					if(system(cmd))
					{
						char msg[MAX_NAME+1];
						sprintf(msg,"cannot execute %s",target);
						error(msg);
					}
				}
				else
					if(progmon)
					{
						sprintf(cmd,"progmon %s",target);
						system(cmd);
					}
					else
					{
						clock_t t;
						int code;
#ifdef __WIN32
						strcpy(cmd,target);
#endif
#ifdef __linux
						sprintf(cmd,"./%s",target);
#endif
						t=clock();
						code=system(cmd);
						printf("%s exited after %.3lf s with code=%d\n",target,(double)(clock()-t)/CLOCKS_PER_SEC,code);
					}
				
#ifdef __WIN32
				sprintf(cmd,"del %s",target);
#endif
#ifdef __linux
				sprintf(cmd,"rm %s",target);
#endif
				if(system(cmd))
				{
					char msg[MAX_NAME+1];
					sprintf(msg,"cannot remove %s",target);
					error(msg);
				}
			}
		}
		else
			if(!strcmp(argv[3],".c"))
			{
				char cmd[MAX_NAME+1],target[MAX_NAME+1];
				sprintf(cmd,"gcc %s",fullname);
				if(warn)
					strcat(cmd," -Wall");
				if(debug)
					strcat(cmd," -g");
				if(cname)
				{
					strcat(cmd," -o ");
					strcat(cmd,argv[2]);
					strcpy(target,argv[2]);
#ifdef __WIN32
					strcat(target,".exe");
#endif
				}
				else
#ifdef __WIN32
					strcpy(target,"a.exe");
#endif
#ifdef __linux
					strcpy(target,"a.out");
#endif
				if(std)
				{
					strcat(cmd," ");
					strcat(cmd,std);
				}
				if(opt)
				{
					strcat(cmd," ");
					strcat(cmd,opt);
				}
				
				if(lgmp)
					strcat(cmd," -lgmp");
				if(lmpfr)
				{
					strcat(cmd," -lmpfr");
#ifdef __WIN32
					strcat(cmd," -lgmp");
#endif
				}
				if(lqmath)
					strcat(cmd," -lquadmath");
		
				if(system(cmd))
					error("compile error");
		
				if(exec)
				{
					if(debug)
					{
						sprintf(cmd,"gdb %s",target);
						if(system(cmd))
						{
							char msg[MAX_NAME+1];
							sprintf(msg,"cannot execute %s",target);
							error(msg);
						}
					}
					else
						if(progmon)
						{
							sprintf("progmon %s",target);
							system(cmd);
						}
						else
						{
							clock_t t;
							int code;
#ifdef __WIN32
							strcpy(cmd,target);
#endif
#ifdef __linux
							sprintf(cmd,"./%s",target);
#endif
							t=clock();
							code=system(cmd);
							printf("%s exited after %.3lf s with code=%d\n",target,(double)(clock()-t)/CLOCKS_PER_SEC,code);
						}
#ifdef __WIN32
					sprintf(cmd,"del %s",target);
#endif
#ifdef __linux
					sprintf(cmd,"rm %s",target);
#endif
					if(system(cmd))
					{
						char msg[MAX_NAME+1];
						sprintf(msg,"cannot remove %s",target);
						error(msg);
					}
				}
			}
	_pause();
	return 0;
}

void _pause()
{
	printf("Press enter to continue...");
	getchar();
}

void show_help()
{
	printf("usage:%s $DIR $NAME $EXT [options]\n",exe);
	puts("options:");
	puts("-nowarn:not showing warnings(C/C++ only)");
	puts("-debug:debug the program");
	puts("-noexec:compile only");
	puts("-cname:using name part for target(C/C++ only)");
	puts("-std=<std>:specify standard(C/C++ only)");
	puts("-lgmp:link GNU Multiple Precision Arithmetic Library(C/C++ only)");
	puts("-lmpfr:link GNU MPFR Library(C/C++ only)");
	puts("-O*:using optimize level *");
	puts("-pm:using progmon as timer");
	_pause();
	exit(0);
}

void error(char* msg)
{
	fprintf(stderr,"%s:%s\n",exe,msg);
	_pause();
	exit(1);
}