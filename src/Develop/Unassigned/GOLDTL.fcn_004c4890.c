char g_68a9cc[2] = {
    0x02, 0x00,
};
extern char g_68a9cc[];



void __cdecl fcn_004c5790(int, void*);

void __cdecl fcn_004c4890(void)
{
	char buf[0x7c];

	if (*(unsigned*) g_68a9cc < 4) {
		*(int*) buf = *(unsigned*) g_68a9cc + 1;
		fcn_004c5790(0x12, buf);
	}
}
