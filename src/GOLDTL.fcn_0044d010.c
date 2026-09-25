#include <string.h>

typedef struct
{
	char pad00[0x80];
	char name[0x40];
	char pad0c0[0xe0 - 0xc0];
} fcn_0044d010_Rec;
// SIZE 0xe0

typedef struct
{
	int pad00[2];
	int n;
	int pad0c;
	fcn_0044d010_Rec* recs;
} fcn_0044d010_Ctx;
// SIZE 0x14

extern char s_662d1c[];

char* __cdecl fcn_0064f026(char* s, char* delim);
char* __cdecl fcn_0064d1a0(char* s, int c);
void __cdecl fcn_0044cbd0(char* name, int flag);

// FUNCTION: GOLDTL 0x44d010
// SIZE: 112
void __cdecl fcn_0044d010(void* stream, fcn_0044d010_Ctx* c)
{
	char* tok;
	char* dot;

	tok = fcn_0064f026(0, s_662d1c);
	dot = fcn_0064d1a0(tok, '.');
	if (dot != 0) {
		*dot = 0;
	}
	strcpy(c->recs[c->n].name, tok);
	fcn_0044cbd0(c->recs[c->n].name, 1);
}
