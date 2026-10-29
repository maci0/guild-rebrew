extern short g_14ce8c0;
extern int g_14cf900[];
void __cdecl fcn_004124b0(void);

/* ADDRESS: GOLDTL 0x00412630 */
void __cdecl fcn_00412630(void)
{
	int i;
	unsigned char* rec;

	if (*(int*) 0x6772c4 != 0) {
		(&g_14ce8c0)[0] = ((short*) g_14cf900)[0];
		(&g_14ce8c0)[1] = ((short*) g_14cf900)[1];
		(&g_14ce8c0)[2] = ((short*) g_14cf900)[2];
	}
	i = 0;
	((int*) &g_14ce8c0)[3] = 0;
	((int*) &g_14ce8c0)[6] = 0;
	((int*) &g_14ce8c0)[8] = 0;
	((int*) &g_14ce8c0)[11] = 0;
	((int*) &g_14ce8c0)[12] = 0;
	((int*) &g_14ce8c0)[15] = 0;
	for (; i < 32; i++) {
		if (*(int*) (0x14ce9c8 + i * 0x4c) != 0) {
			rec = (unsigned char*) (0x14ce986 + i * 0x4c);
			*(int*) 0x14ce8cc = *(int*) (rec + 6);
			*(int*) 0x14ce8d0 = *(int*) (rec + 0xa);
			*(int*) 0x14ce8d4 = *(int*) (rec + 0xe);
			*(int*) 0x14ce8d8 = *(int*) (rec + 0x12);
			*(int*) 0x14ce8dc = *(int*) (rec + 0x16);
			*(int*) 0x14ce8e0 = *(int*) (rec + 0x1a);
			*(int*) 0x14ce8e4 = *(int*) (rec + 0x1e);
			*(int*) 0x14ce8e8 = *(int*) (rec + 0x22);
			*(int*) 0x14ce8ec = *(int*) (rec + 0x26);
			*(int*) 0x14ce8f0 = *(int*) (rec + 0x2a);
			*(int*) 0x14ce8f4 = *(int*) (rec + 0x2e);
			*(int*) 0x14ce8f8 = *(int*) (rec + 0x32);
			*(int*) 0x14ce8fc = *(int*) (rec + 0x36);
			*(int*) 0x14ce904 = *(int*) (rec + 0x3e);
			*(int*) 0x14ce900 = *(int*) (rec + 0x3a);
			*(short*) 0x14ce8c6 = *(short*) (rec + 0);
			*(short*) 0x14ce8c8 = *(short*) (rec + 2);
			*(short*) 0x14ce8ca = *(short*) (rec + 4);
			*(int*) (0x14ce9c8 + i * 0x4c) = 0;
			fcn_004124b0();
			return;
		}
	}
	fcn_004124b0();
}
