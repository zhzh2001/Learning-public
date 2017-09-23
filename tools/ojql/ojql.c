#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct oj
{
	char *name, *url;
	int cnt;
} a[] =
	{
		{"bzoj", "start http://www.lydsy.com/JudgeOnline/problem.php?id=%s", 1},
		{"luogu", "start https://www.luogu.org/problem/show?pid=%s", 1},
		{"dluogu", "start https://daniu.luogu.org/problem/show?pid=%s", 1},
		{"cf", "start http://codeforces.com/contest/%s/problem/%s", 2},
		{"poj", "start http://poj.org/problem?id=%s", 1},
		{"hdu", "start http://acm.hdu.edu.cn/showproblem.php?pid=%s", 1},
		{"codevs", "start http://codevs.cn/problem/%s/", 1},
		{"51", "start http://www.51%s.com/onlineJudge/questionCode.html#!problemId=%s", 2},
		{"vijos", "start https://vijos.org/p/%s", 1},
		{"uoj", "start http://uoj.ac/problem/%s", 1}};

#define CNT sizeof(a) / sizeof(struct oj)
#define MAXLEN 10
#define MAXARGC 10
#define MAXCLEN 100

char res[MAXARGC][MAXLEN];
void ssplit(char *s);
//s->res

void error(char *msg, int code);
//report error

enum exitcode
{
	SUCC,
	FEW_ARG,
	INVALID_ARG,
	FAIL,
	UNKNOW_ERR
};

int main(int argc, char *argv[])
{
	size_t i;

	if (argc < 2)
		error("Too few arguments\nusage:ojql <str>\n", FEW_ARG);
	ssplit(argv[1]);
	for (i = 0; i < CNT; i++)
		if (!strcmp(a[i].name, res[0]))
		{
			char cmd[MAXCLEN];

			if (i == 3)
				res[2][0] = toupper(res[2][0]);
			if (a[i].cnt == 1)
				sprintf(cmd, a[i].url, res[1]);
			else
				sprintf(cmd, a[i].url, res[1], res[2]);
			if (system(cmd))
				error("Failed to excute command.\n", FAIL);
			else
				return SUCC;
		}
	error("Invalid argument.\n", INVALID_ARG);
	return 0;
}

void ssplit(char *s)
{
	char *p = res[0];
	int i, cc = 0;

	for (i = 0; s[i]; i++)
	{
		if (i && (islower(s[i]) ^ islower(s[i - 1])))
			p = res[++cc];
		if (s[i] != '_')
			*p++ = s[i];
	}
}

void error(char *msg, int code)
{
	fprintf(stderr, "Error code %d:%s", code, msg);
	exit(code);
}
