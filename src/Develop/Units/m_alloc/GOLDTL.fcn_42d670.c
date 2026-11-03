extern int g_149d188[];
extern int g_149d188[];



int __cdecl fcn_0042d630(int);
int __cdecl m_FreeTracked(int);

void __cdecl fcn_0042d670(int a)
{
	int i;
	int x;
	i = fcn_0042d630(a);
	if (i == -1) {
		return;
	}
	x = g_149d188[i * 29];
	m_FreeTracked(x);
	g_149d188[i * 29] = 0;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_1052c50[4498744];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_1052c54[12];
unsigned char _dpad_1052c64[380];
unsigned char _dpad_1052de4[28];
unsigned char _dpad_1052e01[255];
unsigned char _dpad_1052f01[255];
unsigned char _dpad_1053002[1474558];
unsigned char _dpad_11bb004[73724];
unsigned char _dpad_1334fb0[80];
unsigned char _dpad_1335001[287];
unsigned char _dpad_1335121[1474559];
unsigned char _dpad_149d122[102];
#endif
