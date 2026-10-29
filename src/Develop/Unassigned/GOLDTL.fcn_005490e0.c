

extern unsigned short g_774970;
extern char g_7f4ca4[];

void __cdecl fcn_004c5530(char*);

void __cdecl fcn_005490e0(void)
{
	char msg[0xf8];

	msg[4] = 0x3a;
	*(int*) (msg + 0xc) = -1;
	msg[0x36] = 1;
	*(int*) (msg + 8) = *(int*) (g_7f4ca4 + g_774970 * 0x21c);
	fcn_004c5530(msg);
}
