int __cdecl fcn_005de7a2(char* dst, char* fmt, char* prefix, char* name);
int __cdecl fcn_00428530(char* path);

/* ADDRESS: GOLD 0x004287b0 */
int __cdecl fcn_004287b0(char* name)
{
	char path[0x100];

	fcn_005de7a2(path, "%s%s", "x:\\engine\\gfx\\scripts\\", name);
	return fcn_00428530(path);
}
