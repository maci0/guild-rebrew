typedef struct {
	char pad0[0x188];
	unsigned char active;
	char pad189[0x93];
} fcn_004c35b0_slot;
// SIZE 0x21c

extern fcn_004c35b0_slot g_7f4ca0[768];

void __cdecl fcn_004c3540(fcn_004c35b0_slot*);

// FUNCTION: GOLDTL 0x4c35b0
// SIZE: 50

void __cdecl fcn_004c35b0(void)
{
	int i;

	for (i = 0; i < 768; i++) {
		if (g_7f4ca0[i].active != 0) {
			fcn_004c3540(&g_7f4ca0[i]);
			return;
		}
	}
}
