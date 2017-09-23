#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *exe;

void print_help(void);

void process(FILE *fin,char* filename);

int main(int argc,char* argv[])
{
	int i;
	exe=argv[0];
	if(argc==1)
		print_help();
	for(i=1;i<argc;i++)
	{
		if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"--help")||!strcmp(argv[i],"/h")||!strcmp(argv[i],"/?"))
			print_help();
		if(!strcmp(argv[i],"-"))
			process(stdin,"stdin");
		else
			process(fopen(argv[i],"r"),argv[i]);
	}
	return 0;
}

void print_help(void)
{
	printf("usage:\n%s -h|--help|/h|/?\nshow help\n%s filename|- [filename|-...]\nusing - to read from stdin\noutput to filename.out",exe,exe);
	exit(0);
}

#define MAX_FNAME 255
char endl[]="&#x000A;";
char quote[]="&quot;";
char and[]="&amp;";
char less[]="&lt;";
char greater[]="&gt;";

void process(FILE *fin,char* filename)
{
	char c[2],out[MAX_FNAME+1],*tag;
	FILE *fout;
	c[1]='\0';
	if(!fin)
	{
		fprintf(stderr,"%s:Unable to open %s\n",exe,filename);
		exit(1);
	}
	if(fin!=stdin)
	{
		strcpy(out,filename);
		strcat(out,".out");
		fout=fopen(out,"w");
	}
	else
		fout=stdout;
	if(!fout)
	{
		fprintf(stderr,"%s:Unable to open %s\n",exe,out);
		exit(1);
	}
	for(c[0]=getc(fin);c[0]!=EOF;c[0]=getc(fin))
	{
		switch(c[0])
		{
			case '\n':
#ifdef __WIN32
				fputs("<Action type=\"1\" message=\"2170\" wParam=\"0\" lParam=\"0\" sParam=\"&#x000D;\" />\n",fout);
#endif
				tag=endl;
				break;
			case '"':tag=quote;break;
			case '&':tag=and;break;
			case '<':tag=less;break;
			case '>':tag=greater;break;
			default:tag=c;
		}
		fprintf(fout,"<Action type=\"1\" message=\"2170\" wParam=\"0\" lParam=\"0\" sParam=\"%s\" />\n",tag);
	}
	fclose(fin);
	fclose(fout);
}