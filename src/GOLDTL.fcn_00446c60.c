// FUNCTION: GOLDTL 0x446c60

void __cdecl fcn_00401210(void*, int);
void __cdecl fcn_00446540(void*, void*);

char __cdecl fcn_00446c60(void* a1, void* a2)
{
	int saved;

	fcn_00401210(a2, 1);
	saved = *(int*) ((char*) a1 + 0x1f4);
	*(int*) ((char*) a1 + 0x1f4) = 0;
	fcn_00446540(a2, a1);
	*(int*) ((char*) a1 + 0x1f4) = saved;
	return 1;
}
