typedef struct
{
	char pad[0x100];
	int id;
	int state;
	char mid[0x1c];
	unsigned char flags;
	char tail[0xb73];
} Obj;
// SIZE 0xc98

extern char* g_6b7e94;

int __cdecl fcn_005373e0(int, int);

static __inline int any_pending(void)
{
	int i;

	for (i = 0; i < 128; i++) {
		if (((Obj*)g_6b7e94)[i].id != -1 && ((Obj*)g_6b7e94)[i].state == -2) {
			return 1;
		}
	}
	return 0;
}

// FUNCTION: GOLD 0x004e2e00
// FUNCTION: GOLDTL 0x4e4680

void __cdecl fcn_004e4680(void)
{
	while (fcn_005373e0(0, 0x79706) != 0) {
		if (!any_pending()) {
			return;
		}
	}
}
