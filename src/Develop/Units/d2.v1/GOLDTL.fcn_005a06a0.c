
int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(int k);
int __cdecl d2_SetForm(int k, int i);
void __cdecl io_AppendText(int a);
int __cdecl fcn_005373e0(void* p, int a);
float __cdecl fcn_004ff210(unsigned short id, int delta);
int __cdecl fcn_005095d0(char* e, int* out_count);
int __cdecl fcn_00526120(char* text, int flags);
int __cdecl fcn_00471e30(int k);

/* ADDRESS: GOLDTL 0x005a06a0 */
void __cdecl fcn_005a06a0(void)
{
	char* slot;
	int h;
	int n;
	int mode;

	slot = (char*) 0x7f4ca0 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c;
	h = fcn_00470820(0, 0, "locations\\wohnsitz\\weinkeller");
	fcn_00471b60(h);
	d2_SetForm(h, 1);
	io_AppendText(0x42cf);
	d2_SetForm(h, 2);
	io_AppendText(0x42d1);
	while (fcn_005373e0((void*) fcn_005a06a0, 0x677c7) != 0) {
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
		else if (*(char*) 0x14cf701 != 0) {
			*(int*) 0x774654 = 1;
		}
		else if ((mode = *(int*) 0x100f1dc) == 2) {
			n = 0;
			if (fcn_005095d0(slot, &n) != 0) {
				fcn_004ff210(*(unsigned short*) slot, -2000);
			}
			else {
				fcn_00526120((char*) *(int*) (0x14a5320 + (n != 0 ? 0x42d3 : 0x42d2) * 4), 0);
				*(int*) 0x774654 = 1;
			}
		}
		else if (mode == 1) {
			*(int*) 0x774654 = 1;
		}
	}
	fcn_00471e30(h);
}
