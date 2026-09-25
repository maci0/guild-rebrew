typedef struct
{
	char pad00[0x18];
	int a;
	int b;
	int c;
	char pad24[0x38 - 0x24];
} fcn_0044d3f0_Rec;
// SIZE 0x38

typedef struct
{
	char pad00[0x18];
	int n;
	int pad1c;
	fcn_0044d3f0_Rec* recs;
	char pad24[0x2c - 0x24];
	int base;
} fcn_0044d3f0_Ctx;
// SIZE 0x30

extern char s_662d18[];

char* __cdecl fcn_0064f026(char* s, char* delim);
int __cdecl fcn_0064eeec(char* s);

// FUNCTION: GOLDTL 0x44d3f0
// SIZE: 142
// FUNCTION: GOLD 0x0044eb70
// SIZE: 142
void __cdecl fcn_0044d3f0(void* stream, fcn_0044d3f0_Ctx* c)
{
	char* tok;

	tok = fcn_0064f026(0, s_662d18);
	c->recs[c->n].a = fcn_0064eeec(tok) + c->base;
	tok = fcn_0064f026(0, s_662d18);
	c->recs[c->n].b = fcn_0064eeec(tok) + c->base;
	tok = fcn_0064f026(0, s_662d18);
	c->recs[c->n].c = fcn_0064eeec(tok) + c->base;
}
