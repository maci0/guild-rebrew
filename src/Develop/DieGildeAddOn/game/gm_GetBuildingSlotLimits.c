extern char gm_BuildingSlotLimits[];
extern char gm_BuildingSlotLimits[];



// SIZE 0x8
typedef struct {
	int a;
	int b;
} fcn_004fac80_E;

int __cdecl gm_GetBuildingSlotLimits(int idx, int* out)
{
	fcn_004fac80_E* t;

	if (idx >= 0x58) {
		return 0;
	}
	t = (fcn_004fac80_E*) gm_BuildingSlotLimits;
	out[0] = t[idx].a;
	out[1] = t[idx].b;
	return 1;
}
