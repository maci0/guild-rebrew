


int __cdecl fcn_00545580(int, void*, void*);
void __cdecl fcn_005759b0(void);
void __cdecl fcn_00575ab0(void);
void __cdecl fcn_00575cf0(void);
void __cdecl fcn_00575e10(void);
void __cdecl fcn_00576070(void);
void __cdecl fcn_00576180(void);
void __cdecl fcn_00576400(void);
void __cdecl fcn_005764f0(void);
int __cdecl fcn_00530ab0(int, char*, int, int, int);

int __cdecl fcn_00575900(void)
{
	if (fcn_00545580(0x95, (void*) fcn_005759b0, (void*) fcn_00575ab0) != 0 ||
	    fcn_00545580(0x96, (void*) fcn_00575cf0, (void*) fcn_00575e10) != 0 ||
	    fcn_00545580(0x97, (void*) fcn_00576070, (void*) fcn_00576180) != 0 ||
	    fcn_00545580(0x98, (void*) fcn_00576400, (void*) fcn_005764f0) != 0) {
		return 1;
	}
	fcn_00530ab0(0x95, "erforschen", 1, 0x500, -1);
	fcn_00530ab0(0x96, "erforschen", 1, 0x500, -1);
	return 0;
}
