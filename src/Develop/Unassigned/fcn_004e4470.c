extern int g_772f3c;

int __cdecl fcn_00426fd0(int);
void __cdecl fcn_00442830(void*);

/* ADDRESS: GOLDTL 0x004e4470 */
int __cdecl fcn_004e4470(int a)
{
	void* p;

	p = 0;
	if (g_772f3c == 0) {
		p = (void*) fcn_00426fd0(a);
		if (p != 0) {
			fcn_00442830(p);
			return *(int*) ((char*) p + 0x100);
		}
	}
	return 0;
}
