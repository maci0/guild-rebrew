extern char g_773dd4;



int __cdecl strncmp(const char*, const char*, unsigned int);
void __cdecl SelectTextureSet(char*, int, char, int);

void __cdecl fcn_00516550(char* e)
{
	if (!strncmp(e, "pfl_", 4) || !strncmp(e, "vg_", 3) || strncmp(e, "!vg_", 4) == 0) {
		SelectTextureSet(e, *(int*) (e + 0x1cc), g_773dd4, 1);
	}
}
