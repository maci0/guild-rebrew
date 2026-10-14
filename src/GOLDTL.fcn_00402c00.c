extern void* g_14d0020[];
extern char g_10432c0[];


int __cdecl fcn_00451840(void*, int, int);

int __cdecl fcn_00402c00(int a1, int a2, int a3, int a4)
{
	int count;
	void** p;
	void* e;

	count = 0;
	p = g_14d0020;
	do {
		e = *p;
		if (e != 0) {
			if (a1 == -1 ||
			    *(int*) ((char*) e + 0x88) == (int) (g_10432c0 + a1 * 0x3dc)) {
				if (a2 != 0 ||
				    *(int*) (*(int*) ((char*) e + 0x34) + 0x218) != 1) {
					if (fcn_00451840((char*) *(int*) ((char*) e + 0x34) + 0x4c,
					                 a3, a4) != 0) {
						count++;
					}
				}
			}
		}
		p++;
	} while ((int) p < 0x14d0c20);
	return count;
}
