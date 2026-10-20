#pragma optimize("s", on)

typedef struct State613478 {
	int w[0x39];
} State613478;

int __cdecl fcn_0062abbc(void* p);
int __cdecl fcn_006131cd(int a, void* b, int* c, int d);
int __cdecl fcn_006133c4(int feature);
void __cdecl fcn_0062a4f5(void* p);
void __cdecl fcn_0062a310(void* p);
void __cdecl fcn_0062a200(void* p);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00613478 */
int __stdcall fcn_00613478(int mode)
{
	if (mode == 0) {
		*(State613478*) 0x6ad638 = *(State613478*) 0x6ad720;
		*(int*) 0x6ad80c = 0xffff;
	} else if (*(int*) 0x6ad80c == 0xffff) {
		*(int*) 0x6ad80c = 0;
		*(State613478*) 0x6ad638 = *(State613478*) 0x6ad720;
		fcn_0062abbc((void*) 0x6ad638);
		if (fcn_006131cd(4, (void*) 0x66700c, &mode, 4) == 0) {
			mode = 0;
		}
		if (mode != 1) {
			if (fcn_006133c4(7) != 0) {
				fcn_0062a4f5((void*) 0x6ad638);
				*(int*) 0x6ad80c = 1;
			} else if (fcn_006133c4(10) != 0) {
				fcn_0062a310((void*) 0x6ad638);
				*(int*) 0x6ad80c = 2;
			} else if (fcn_006133c4(6) != 0) {
				fcn_0062a200((void*) 0x6ad638);
				*(int*) 0x6ad80c = 3;
			}
		}
	}
	return *(int*) 0x6ad80c;
}
