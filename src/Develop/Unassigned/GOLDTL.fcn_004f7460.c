


int  __cdecl fcn_005d4fa0(void*, void*);
extern char g_679060[];
void __cdecl io_FormatTextBuffer(void*, int, int);

int __cdecl fcn_004f7460(void* a1, void* a2)
{
	int v;

	v = *(int*) a2;
	if (v == 3 || v == 1) {
		if ((*(char*) ((char*) a1 + 0x1c8) & 0x40) == 0) {
			if ((double) *(int*) ((char*) a1 + 0x24) < -20.0 ||
			    (*(int*) ((char*) a1 + 0x2c) & 0xfffffff0) != 0) {
				if (v == 3) {
					return fcn_005d4fa0(a1, a2);
				}
				if (v == 1 && *(char*) ((char*) a1 + 2) == 6) {
					io_FormatTextBuffer((char*) a2 + 0x14, (int) g_679060, 0x1d3a);
				}
				return 2;
			}
		}
	}
	return 1;
}
