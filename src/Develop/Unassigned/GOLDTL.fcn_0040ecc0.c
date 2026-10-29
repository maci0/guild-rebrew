


extern char* g_6b7e98;
void __cdecl fcn_00442d90(char* e, int v);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl ecmd_ReplaceObject(char** a, int* v)
{
	if (*a != 0) {
		fcn_00442d90(*a, *v);
		return 1;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return 1;
}
