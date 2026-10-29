extern char g_7f4ca4[];
extern unsigned short g_774970;
extern unsigned short g_774970;



int __cdecl fcn_004c5790(int, void*);

void __cdecl fcn_0053d690(void)
{
	char buf[0x7c];
	*(int*) buf = *(int*) (g_7f4ca4 + (unsigned int) (unsigned short) *(unsigned short*) ((char*)&g_774970) * 135 * 4);
	fcn_004c5790(0x13, &buf);
}
