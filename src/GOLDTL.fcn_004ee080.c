// FUNCTION: GOLDTL 0x4ee080
// SIZE: 48

typedef struct
{
	int used;
	char pad[0x14];
} Slot18;
// SIZE 0x18

extern Slot18 g_772f90[3];

void __cdecl fcn_004ee080(Slot18* p)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (&g_772f90[i] == p) {
			g_772f90[i].used = 0;
			return;
		}
	}
}
