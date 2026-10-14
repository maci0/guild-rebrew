typedef struct
{
	void* pad[2];
	int (__stdcall* Release)(void*);
} fcn_00456cf0_Vtbl;
// SIZE 0xc

extern unsigned long g_14ce728;
extern unsigned int g_10405fc;
extern unsigned int g_104061c;
extern int* g_6b89e4;

void __cdecl fcn_00456560(void);
void __cdecl gv_Free3Fields(int* slot);

/* ADDRESS: GOLDTL 0x00456cf0 */
void __cdecl fcn_00456cf0(void)
{
	int a;
	void* o;

	for (a = 0x1040610; a <= 0x1040618; a += 4) {
		o = *(void**) a;
		if (o != 0) {
			(*(int*)&g_14ce728) = (*(fcn_00456cf0_Vtbl**) o)->Release(o);
			*(void**) a = 0;
		}
	}
	(*(int*)&g_10405fc) = 0;
	(*(int*)&g_104061c) = 0;
	fcn_00456560();
	if (g_6b89e4 != 0) {
		gv_Free3Fields(g_6b89e4);
		g_6b89e4 = 0;
	}
}
