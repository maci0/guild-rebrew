typedef struct fcn_0047c520_dev fcn_0047c520_dev;
typedef struct {
	char pad0[0xf4];
	int(__stdcall* ff4)(fcn_0047c520_dev*, int, int);
	char padf8[0x54];
	int(__stdcall* f14c)(fcn_0047c520_dev*, int, int, int);
} fcn_0047c520_vtbl;
// SIZE 0x150
struct fcn_0047c520_dev {
	fcn_0047c520_vtbl* vtbl;
};

extern int g_772618;
extern void* g_6b5de0;


/* ADDRESS: GOLDTL 0x0047c520 */
void __cdecl fcn_0047c520(void)
{
	if (g_772618 != 0) {
		((fcn_0047c520_dev*)g_6b5de0)->vtbl->f14c(((fcn_0047c520_dev*)g_6b5de0), 0, 0, 0);
		((fcn_0047c520_dev*)g_6b5de0)->vtbl->ff4(((fcn_0047c520_dev*)g_6b5de0), 0, 0);
		g_772618 = 0;
	}
}
