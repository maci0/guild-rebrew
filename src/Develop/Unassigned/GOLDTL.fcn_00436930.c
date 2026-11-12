void* __cdecl fcn_00435410(char* e);
void __cdecl fcn_00435910(char* a0, int a1, int a2, int* a3);

/* ADDRESS: GOLDTL 0x00436930 */
void* __cdecl fcn_00436930(char* a0, int* a1)
{
	char* v1;
	char* v2;
	int* out = a1;

	if (out != 0) {
		*out = 0;
	}
	if (a0 == 0) {
		return 0;
	}
	v1 = *(char**) (a0 + 0x318);
	if (v1 == 0) {
		return 0;
	}
	if (*(char*) (a0 + 0x4a0) != 0) {
		if (*(int*) (v1 + 0x264) != 0 && (*(unsigned char*) (v1 + 0x2a1) & 2) != 0 && *(int*) (v1 + 0x268) == 0) {
			*(int*) (*(int*) (a0 + 0x318) + 0x268) = (int) fcn_00435410(v1);
		}
		if (*(char*) (a0 + 0x4a0) != 0) {
			v1 = *(char**) (a0 + 0x318); v2 = *(char**) (v1 + 0x268);
			if (v2 != 0) {
				if (((int (__stdcall*) (void*, int, void**)) *(void**) (*(int*) v2 + 0x38)) (v2, 0x2000, (void**) &a1) >= 0) {
					fcn_00435910(a0, *(int*) (v1 + 0x29c), (int) a1, out);
					((void (__stdcall*) (void*)) *(void**) (*(int*) v2 + 0x3c)) (v2);
				}
				return v2;
			}
		}
	}
	return *(void**) (*(int*) (a0 + 0x318) + 0x264);
}
