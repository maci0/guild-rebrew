int __cdecl fcn_00438e60(int, int, int, void*);
int __cdecl fcn_00446180(int);

void __cdecl fcn_00447860(char arg)
{
	unsigned int i;
	unsigned int count = *(unsigned int *)0xfb9084;
	unsigned char *slots = *(unsigned char **)0xfb9074;
	void *obj;
	typedef void (__stdcall *method_t)(void*);

	for (i = 0; i < count; i++)
		slots[i * 0x80 + 0x68] &= 0x7f;

	obj = *(void **)0x633418;
	((method_t)(*(void **)(*(char **)obj + 0x24)))(obj);

	fcn_00438e60(*(int*)0x5fb5b0, 0, 0x40, (void*)0x447800);

	obj = *(void **)0x633738;
	if (obj && arg)
		fcn_00446180((int)obj);

	obj = *(void **)0x633418;
	((method_t)(*(void **)(*(char **)obj + 0x28)))(obj);
}
