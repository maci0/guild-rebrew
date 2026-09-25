typedef struct {
	int id;
	int b;
} fcn_004be380_entry;

extern fcn_004be380_entry g_10058a0[8];
extern int g_6816d8;

int __cdecl fcn_004693b0(int, int);
void __cdecl fcn_00469470(int, int);

// FUNCTION: GOLDTL 0x4be380
// SIZE: 65

void __cdecl fcn_004be380(void)
{
	int i;

	for (i = 0; i < 8; i++) {
		if (g_10058a0[i].id != -1) {
			if (g_6816d8 == -1)
				g_6816d8 = fcn_004693b0(1, g_10058a0[i].id);
			else
				fcn_00469470(g_6816d8, g_10058a0[i].id);
		}
	}
}
