// FUNCTION: GOLD 0x4b5310
// SIZE: 65
// FUNCTION: GOLDTL 0x4b54e0
// SIZE: 65

// SIZE 0x24
typedef struct {
	int handle;
	int key;
	char pad[0x1c];
} Entry24;

extern int g_7e46ac;
extern char g_10069a0[];

void __cdecl fcn_004b5530(int handle, int flags);

void __cdecl fcn_004b54e0(int key)
{
	int i;
	int flags;

	flags = g_7e46ac | 0x80;
	for (i = 0; i < 128; i++) {
		if (((Entry24*)g_10069a0)[i].handle != 0 && ((Entry24*)g_10069a0)[i].key == key) {
			fcn_004b5530(((Entry24*)g_10069a0)[i].handle, flags | 0x80);
		}
	}
}
