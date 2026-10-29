extern int g_100f1dc;
extern int g_100f1dc;



void __cdecl fcn_00535550(void);
void __cdecl fcn_00535560(void);

void __cdecl fcn_00534c20(void)
{
	int v;

	v = *(int*) ((char*)&g_100f1dc);
	if (v == 0x767) {
		fcn_00535550();
	} else if (v == 0x768) {
		fcn_00535560();
	}
}
