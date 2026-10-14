


extern char g_68a9cc[];

int __cdecl fcn_004c5790(int, void*);

void __cdecl fcn_004c4860(unsigned int a1)
{
	char buf[0x7c];

	if (a1 >= 4) {
		a1 = 4;
	}
	if (a1 != (*(unsigned int*)g_68a9cc)) {
		*(unsigned int*) buf = a1;
		fcn_004c5790(0x12, buf);
	}
}
