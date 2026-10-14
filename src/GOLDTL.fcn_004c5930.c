


extern int g_6b7fac;
extern char g_68ae34[];

int __cdecl sprintf(char*, const char*, ...);
int __cdecl fcn_004c4330(void*);

int __cdecl fcn_004c5930(int a1, int a2)
{
	char buf[0x19c];

	buf[0] = 0x26;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	sprintf(buf + 0x9c, g_68ae34, a1, g_6b7fac);
	return fcn_004c4330(buf);
}
