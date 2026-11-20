char* __cdecl vfs_ReadCString(void* a, char* buf);
char* __cdecl fcn_0064d1a0(char* s, int c);

/* ADDRESS: GOLDTL 0x0044d900 */
void __cdecl fcn_0044d900(void* a, char* s)
{
	char buf[0x100];
	char* p;
	char* d;
	char c;

	vfs_ReadCString(a, buf);
	p = fcn_0064d1a0(buf, '.');
	if (p != 0) {
		*p = 0;
	}
	p = buf;
	d = *(char**) (s + 0x10) + *(int*) (s + 8) * 0xe0;
	do {
		c = *p++;
		*d++ = c;
	} while (c != 0);
}
