struct cut_4c9d10 {
	int f0;
	int time;
	int ready;
	int fc;
	int id;
	int rest[210];
};
// SIZE 0x35c

extern struct cut_4c9d10 g_9b0e20[16];
extern struct cut_4c9d10 g_aed340;
extern int* g_772f40;
extern int g_6b7fac;

int __cdecl fcn_0064d41a(char*, char*, ...);

// FUNCTION: GOLDTL 0x4c9d10
// SIZE: 268

int __cdecl fcn_004c9d10(char* a1, char* a2)
{
	char buf[0x100];
	int i;

	for (i = 0; i < 16; i++) {
		if (g_9b0e20[i].id == *(int*) (a1 + 0x10)) {
			if (g_772f40 != 0 && *g_772f40 == *(int*) (a1 + 0x14)) {
				g_9b0e20[i] = g_aed340;
				g_9b0e20[i].fc = 0;
				fcn_0064d41a(buf, "cm_ExSendCutInfo: PlayerId:%i Valid:%i  Ready:%i  Time:%i",
				    g_9b0e20[i].id, g_9b0e20[i].ready, g_9b0e20[i].time, g_6b7fac);
			}
			break;
		}
	}
	if (i >= 16) {
		if (g_772f40 != 0 && *g_772f40 == *(int*) (a1 + 0x14))
			fcn_0064d41a(buf, "cm_ExSendCutInfo(): io-buffer has not been written, because player not found (player id %i)",
			    *(int*) (a1 + 0x10));
		return 1;
	}
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 8;
		*(struct cut_4c9d10**) (a2 + 6) = &g_9b0e20[i];
	}
	return 0;
}
