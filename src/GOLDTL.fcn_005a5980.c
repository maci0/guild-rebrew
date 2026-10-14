


extern int g_14ce8d8;
extern int g_67d370;

// SIZE 0x1c
typedef struct {
	int id;
	int pad[6];
} Slot;

int __cdecl fcn_005a5980(Slot* tbl)
{
	int i;

	if (g_14ce8d8 != 0) {
		for (i = 0; i < 16; i++) {
			if (tbl[i].id != -1 && g_67d370 == tbl[i].id) {
				return i;
			}
		}
	}
	return -1;
}
