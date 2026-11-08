extern char* g_6b7e98;

void __cdecl fcn_00428720(char*);
extern char g_675bbc[];

void __cdecl fcn_00425bf0(void*, int, void*);
extern char g_675be8[];

void __cdecl fcn_00425bf0(void*, int, void*);

/* Iterate the 128 0xc98-byte records behind g_6b7e94 and call fcn_00428720
 * for each active record whose owner differs from g_6b7e98's record. */
/* ADDRESS: GOLDTL 0x0040c6d0 */
int __cdecl fcn_0040c6d0(void)
{
    int i;
    int id;
    char* obj;

    for (i = 0; i < 128; i++) {
        obj = *(char**) 0x6b7e94 + i * 0xc98;
        id = *(int*) (obj + 0x100);
        if (id == -1)
            continue;
        if ((*(unsigned char*) (obj + 0x124) & 1) == 0)
            continue;
        if (*(int*) (obj + 0x104) != *(int*) (g_6b7e98 + 0x104))
            continue;
        if (id == *(int*) (g_6b7e98 + 0x100))
            continue;
        fcn_00428720(obj);
    }
    return 0;
}

/* ADDRESS: GOLD 0x0040b820 */
/* ADDRESS: GOLDTL 0x0040c740 */
int __cdecl fcn_0040c740(int** pp, int** pp2)
{
	void* g;

	if (*pp == 0) {
		g = g_6b7e98;
		fcn_00425bf0(g, *(int*) ((char*) g + 0x118), g_675bbc);
		return 0;
	}
	((int (__cdecl*) (int*)) * pp)(*pp2);
	return 1;
}

/* ADDRESS: GOLD 0x0040b860 */
/* ADDRESS: GOLDTL 0x0040c780 */
int __cdecl fcn_0040c780(int** pp, int** pp2, int** pp3)
{
	void* g;

	if (*pp == 0) {
		g = g_6b7e98;
		fcn_00425bf0(g, *(int*) ((char*) g + 0x118), g_675be8);
		return 0;
	}
	((int (__cdecl*) (int*, int*)) * pp)(*pp2, *pp3);
	return 1;
}
