#include <string.h>

extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774a34;
extern int g_779c40;
extern int g_779ce4;
extern int g_100f1dc;

int __cdecl fcn_004ce1c0(void);
void* __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(void*);
void __cdecl fcn_00519190(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(void*);

/* Screen/registry body for the 0x68d714 dialog and the 0x779c60 status block.
 * Reconstructed prefix: the 0x57-byte clear of 0x779c60, the registry globals,
 * the fcn_004ce1c0 gate, the dialog create/attach/text calls at 0x592759 and the
 * 0x24087 registry pump loop. The remaining 0x592a42-0x593107 section (widget
 * construction for the 0x57 records and the final 0x469e70 path) is not
 * transcribed yet. */
/* ADDRESS: GOLDTL 0x005926f0 */
int __cdecl fcn_005926f0(void)
{
	void* h;

	memset((void*) 0x779c60, 0, 0x57);
	g_774a34 = 0;
	g_779c40 = -1;
	g_779ce4 = fcn_004ce1c0();
	if (g_779ce4 == 0) {
		h = fcn_00470820(0, 0, (char*) 0x68d714);
		fcn_00471b60(h);
		fcn_00519190(0x87);
		g_100f1dc = -1;
		for (;;) {
			if (g_14ce8e0 != 0)
				break;
			if (g_14cf950 == 1)
				break;
			if (fcn_005373e0((void*) fcn_005926f0, 0x24087) == 0)
				break;
		}
		fcn_00471e30(h);
	}
	return 0;
}
