extern int g_6ed938;
extern int g_6f0d6c;
extern int g_6f0d68;
extern int g_6f0d70;

void __cdecl fcn_00472d10(int, int);
void __cdecl fcn_00517700(void*, int, ...);
void* __cdecl fcn_00473640(int, int, char*, int);
void __cdecl fcn_004760a0(void*, int);
void __cdecl fcn_004731c0(int, int, int, int);

/* ADDRESS: GOLD 0x004d8cb0 */
/* Twin of GOLDTL 0x4da510 without its (short) truncation of the x argument. */

void __cdecl fcn_004d8cb0(int a1, int a2, int a3)
{
	char buf[0x40];
	void* h;

	if (a2 != 0) {
		fcn_00472d10(g_6ed938, 1);
		fcn_00517700(buf, 0x12d3);
		h = fcn_00473640(0, 0x20, buf, g_6ed938);
		fcn_004760a0(h, 0x54);
		fcn_00517700(buf, 0x12d4);
		h = fcn_00473640(0, 0x3e, buf, g_6ed938);
		fcn_004760a0(h, 0x54);
		fcn_00517700(buf, 0x12d5);
		h = fcn_00473640(0, 0x2f, buf, g_6ed938);
		fcn_004760a0(h, 0x54);
		g_6f0d6c = 0;
		g_6f0d68 = 0;
		g_6f0d70 = 0;
		return;
	}
	if (a3 == 0) {
		fcn_004731c0((g_6f0d6c * 5 + 40) * 2, 0x20, 0x4df, g_6ed938);
		g_6f0d6c++;
		return;
	}
	if (a3 == 1) {
		fcn_004731c0((g_6f0d68 * 5 + 40) * 2, 0x3e, 0x4df, g_6ed938);
		g_6f0d68++;
		return;
	}
	if (a3 == 2) {
		fcn_004731c0((g_6f0d70 * 5 + 40) * 2, 0x2f, 0x4df, g_6ed938);
		g_6f0d70++;
	}
}
