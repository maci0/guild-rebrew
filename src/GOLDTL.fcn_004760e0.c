// SIZE 0x50
typedef struct {
	char pad0[0x4c];
	int f4c;
} fcn_004760e0_obj;

int __cdecl fcn_004760c0(fcn_004760e0_obj*, void*);

// FUNCTION: GOLDTL 0x4760e0

int __cdecl fcn_004760e0(fcn_004760e0_obj* o)
{
	int desc[8];

	if (fcn_004760c0(o, desc) != 0) {
		o->f4c = desc[4] + 0x5c;
		return 1;
	}
	return 0;
}
