typedef struct {
	char pad0[0x188];
	unsigned char active;
	char pad189[0x93];
} fcn_004c35b0_slot;
// SIZE 0x21c

extern char g_7f4ca0[];

void __cdecl fcn_004c3540(fcn_004c35b0_slot*);

// FUNCTION: GOLD 0x004c2ce0
// FUNCTION: GOLDTL 0x4c35b0

void __cdecl fcn_004c35b0(void)
{
	int i;

	for (i = 0; i < 768; i++) {
		if (((fcn_004c35b0_slot*)g_7f4ca0)[i].active != 0) {
			fcn_004c3540(&((fcn_004c35b0_slot*)g_7f4ca0)[i]);
			return;
		}
	}
}
