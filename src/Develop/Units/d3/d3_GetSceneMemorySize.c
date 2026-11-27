

// SIZE 0x8
typedef struct Count {
	int n;
	int flags;
} Count;

extern int g_67a370;
extern int g_6b8300;

void __cdecl d3_ResetMemoryCountFlags(unsigned int);
void __cdecl d3_VisitSceneObjects(int, int, int, void*, void*);
void __cdecl d3_AccumulateObjectMemorySize(void);
int __cdecl d3_GetTerrainMemorySize(int, int);
int __cdecl d3sm_GetMemorySize(int);

int __cdecl d3_GetSceneMemorySize(int mask, int flags, char keep)
{
	Count c;
	int r;

	if (keep == 0) {
		d3_ResetMemoryCountFlags(0);
	}
	c.flags = flags | 0x114;
	c.n = 0;
	d3_VisitSceneObjects(g_67a370, 0, mask, d3_AccumulateObjectMemorySize, &c);
	if ((flags & 0x200) != 0 && g_6b8300 != 0) {
		c.n += d3_GetTerrainMemorySize(g_6b8300, 1);
		r = c.n;
	} else {
		r = c.n;
	}
	if ((flags & 0x400) != 0 && *(int*) (g_67a370 + 0xb0) != 0) {
		r += d3sm_GetMemorySize(*(int*) (g_67a370 + 0xb0));
	}
	return r;
}
