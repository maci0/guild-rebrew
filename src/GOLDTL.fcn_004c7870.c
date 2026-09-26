extern int g_14cbca0;
extern int g_699364;
extern char g_68a9d0[];
extern char g_7f4ca0[];

int __cdecl rand(void);
void __cdecl fcn_0042e4c0(int);
unsigned short __cdecl fcn_0050a7e0(unsigned int, int, int, unsigned short, int, unsigned int, unsigned int, unsigned int);
char* __cdecl strncpy(char*, const char*, unsigned int);
short* __cdecl fcn_00509570(char*);
char* __cdecl fcn_00508e40(int);

// FUNCTION: GOLD 0x004c6cd0
// SIZE: 314
// FUNCTION: GOLDTL 0x004c7870
// SIZE: 314

int __cdecl fcn_004c7870(int cmd, char* result)
{
	unsigned int entity;
	short* entry;
	char* r2;
	int off;

	{
		char* c = (char*) cmd;
		unsigned int kind;

		if (g_14cbca0 != -1)
			g_699364 = *(int*) (c + 0x10);
		else
			*(int*) (c + 0x45) = rand();
		fcn_0042e4c0(*(int*) (c + 0x22));
		if (result)
			kind = 6;
		else
			kind = 7;
		entity = fcn_0050a7e0(kind,
			*(int*) (c + 0x14), *(int*) (c + 0x18),
			*(unsigned short*) (c + 0x1c), 0,
			(unsigned char) *(char*) (c + 0x1e), 0,
			(unsigned char) *(char*) (c + 0x23));
	}
	entity = entity & 0xffff;
	if (entity == 0xffff)
		return 1;
	off = entity * 0x21c;
	(*(int*)g_68a9d0) = *(int*) (g_7f4ca0 + off + 4);
	strncpy(g_7f4ca0 + off + 0x30, (char*) cmd + 0x25, 0x10);
	entry = fcn_00509570(g_7f4ca0 + off);
	if (entry != 0) {
		*(unsigned short*) entry = *(unsigned short*) (g_7f4ca0 + off + 0x50);
		strncpy((char*) entry + 2, (char*) cmd + 0x35, 0x10);
		strncpy(g_7f4ca0 + off + 0x40, (char*) cmd + 0x35, 0x10);
		r2 = fcn_00508e40(*(int*) (g_7f4ca0 + off + 0x60));
		if (r2 != 0)
			strncpy(r2 + 0x40, (char*) cmd + 0x35, 0x10);
		*(float*) ((char*) entry + 0x88) = -1.0f;
	}
	*(int*) (g_7f4ca0 + off + 0x54) = *(int*) (cmd + 0x1f);
	*(unsigned char*) (g_7f4ca0 + off + 0xc) = *(unsigned char*) (cmd + 0x24);
	if (result != (char*) 0) {
		result[0] = 1;
		result[1] = 1;
		*(char**) (result + 6) = g_7f4ca0 + off;
	}
	return 0;
}
