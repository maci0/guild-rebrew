extern int g_6ed938;

void __cdecl fcn_004731c0(int, unsigned short, int, int);

/* ADDRESS: GOLD 0x004d8c70 */

void __cdecl fcn_004d8c70(int unused, void* a2)
{
	(void) unused;
	fcn_004731c0(0x8c, (short) (0x44 - *(short*) ((char*) a2 + 0x2c) * 10),
	    0x4df, g_6ed938);
	(*(int*) ((char*) a2 + 0x2c))++;
}
