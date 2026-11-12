extern unsigned char* g_fb9074;
extern unsigned int g_fb9084;
extern char* g_5fb5b0;
int __cdecl fcn_00438e60(int, int, int, void*);
int __cdecl fcn_00446180(int);
int __cdecl fcn_00447800();

/* ADDRESS: GOLD 0x00447860 */
void __cdecl fcn_00447860(char arg)
{
	unsigned int i;
	void* obj;
	typedef void (__stdcall* method_t)(void*);

	for (i = 0; i < g_fb9084; i++)
		g_fb9074[i * 0x80 + 0x68] &= 0x7f;
	obj = *(void**) 0x633418;
	((method_t) (*(void**) (*(char**) obj + 0x24)))(obj);
	fcn_00438e60((int) g_5fb5b0, 0, 0x40, (void*) fcn_00447800);
	obj = *(void**) 0x633738;
	if (obj != 0 && arg != 0)
		fcn_00446180((int) obj);
	obj = *(void**) 0x633418;
	((method_t) (*(void**) (*(char**) obj + 0x28)))(obj);
}
