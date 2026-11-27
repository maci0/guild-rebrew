


extern char g_662d1c[];

char* __cdecl fcn_0064f026(char*, char*);
char* __cdecl fcn_0064d1a0(char*, int);
void __cdecl d3_ValidateTextureDimensions(char*, int);

void __cdecl d3_ParseMatBumpMap(int unused, int* o)
{
	char* s;
	char* p;
	char* d;
	char c;
	char* q;

	s = fcn_0064f026(0, g_662d1c);
	p = fcn_0064d1a0(s, '.');
	if (p != 0) {
		*p = 0;
	}
	q = s;
	d = (char*) o[4] + o[2] * 0xe0 + 0x40;
	do {
		c = *q++;
		*d++ = c;
	} while (c != 0);
	d3_ValidateTextureDimensions((char*) o[4] + o[2] * 0xe0 + 0x40, 1);
}
