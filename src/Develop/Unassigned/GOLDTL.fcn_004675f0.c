extern char* g_772500;
extern char* g_1015ea0;
extern int d2_ScreenHeight;
extern int g_1040494;

int __cdecl d2_AllocateElement(void);
int __cdecl d2_GetResourceData(int);

/* ADDRESS: GOLDTL 0x004675f0 */
int __cdecl fcn_004675f0(int a0, int a1, int a2, int a3, int a4, int resourceId, int flags)
{
	int id;
	char* p0;
	char* p1;
	char* p3;
	int f1;
	short f2;
	short f3;
	int m;
	int v;

	id = d2_AllocateElement();
	p1 = g_772500 + (resourceId + 1) * 0x54;
	p0 = g_772500 + resourceId * 0x54;
	p3 = g_772500 + (resourceId + 3) * 0x54;
	if (flags & 1) {
		f2 = *(short*) (p1 + 0x50);
		f3 = *(short*) (p0 + 0x50);
		m = f2 > f3 ? f2 : f3;
		f1 = *(short*) (p3 + 0x50);
		if (m <= f1)
			m = f1;
		*(int*) (g_1015ea0 + id * 0x2f4 + 0x18) = m;
		v = a2 + *(short*) (p0 + 0x52) * 2;
		*(int*) (g_1015ea0 + id * 0x2f4 + 0x1c) = v;
	} else if (flags & 2) {
		f2 = *(short*) (p1 + 0x52);
		f3 = *(short*) (p0 + 0x52);
		m = f2 > f3 ? f2 : f3;
		f1 = *(short*) (p3 + 0x52);
		if (m <= f1)
			m = f1;
		*(int*) (g_1015ea0 + id * 0x2f4 + 0x18) = a2 + *(short*) (p0 + 0x50) * 2;
		v = m;
		*(int*) (g_1015ea0 + id * 0x2f4 + 0x1c) = v;
	}
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x20) = 0x45;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x5c) = 1;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x10) = a0;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x14) = a1;
	*(int*) (g_1015ea0 + id * 0x2f4 + 8) = 0;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x8c) = a3;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x94) = a4;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x98) = flags;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x90) = a3;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x9c) = a2;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0xa0) = a4 / 2;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0xa4) = resourceId;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x30) = 0;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x34) = d2_ScreenHeight;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x28) = 0;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0x2c) = g_1040494;
	*(int*) (g_1015ea0 + id * 0x2f4 + 0xc) = d2_GetResourceData(resourceId);
	return id;
}
