// FUNCTION: GOLD 0x004c9d00
// SIZE: 113
// FUNCTION: GOLDTL 0x4ca8b0
// SIZE: 113

extern char g_68b0d8[];

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl fcn_004032b0(char*);
void __cdecl fcn_00406120(char*);
void __cdecl fcn_00402ab0(char*, char*, int);
void __cdecl fcn_0040c120(char*, int, int);

int __cdecl fcn_004ca8b0(char* x, char* out)
{
	char buf[0x80];
	char* o;

	fcn_0064d41a(buf, g_68b0d8, *(int*) (x + 0x10));
	o = fcn_004032b0(buf);
	if (o == 0)
		return 1;
	fcn_0040c120(o, 0x38, *(int*) (x + 0x14));
	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
