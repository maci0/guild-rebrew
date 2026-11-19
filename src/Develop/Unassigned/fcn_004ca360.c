int __cdecl sprintf(char* buf, const char* fmt, ...);
int __cdecl ch_FindCharacterByName(void* name);
int __cdecl ch_CreateAction(int a1, int a2, int a3, int a4, int a5);

/* ADDRESS: GOLDTL 0x004ca360 */
int __cdecl fcn_004ca360(void* params, char* out)
{
	char buf[0x80];
	int handle;

	sprintf(buf, "sp_%i", *(int*) ((char*) params + 0x10));
	handle = ch_FindCharacterByName(buf);
	if (handle == 0)
		return 0;
	ch_CreateAction(handle, 0x2d, *(int*) ((char*) params + 0x14), *(int*) ((char*) params + 0x18), *(int*) ((char*) params + 0x1c));
	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
