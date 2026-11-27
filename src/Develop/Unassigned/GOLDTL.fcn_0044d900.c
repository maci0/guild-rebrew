char* __cdecl vfs_ReadCString(void* a, char* buf);
char* __cdecl fcn_0064d1a0(char* s, int c);

/* ADDRESS: GOLDTL 0x0044d900 */
void __cdecl d3_ReadMatBaseMap(void* stream, char* ctx)
{
	char buf[0x100];
	char* p;
	char* d;
	char c;

	vfs_ReadCString(stream, buf);
	p = fcn_0064d1a0(buf, '.');
	if (p != 0) {
		*p = 0;
	}
	p = buf;
	d = *(char**) (ctx + 0x10) + *(int*) (ctx + 8) * 0xe0;
	do {
		c = *p++;
		*d++ = c;
	} while (c != 0);
}
