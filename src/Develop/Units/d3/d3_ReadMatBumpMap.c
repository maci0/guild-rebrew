


char* __cdecl vfs_ReadCString(void* stream, char* text);
char* __cdecl fcn_0064d1a0(char*, int);

/* ADDRESS: GOLDDE 0x004436a0 */
void __cdecl d3_ReadMatBumpMap(void* r, int* o)
{
	char buf[0x100];
	char* p;
	char* d;
	char* q;
	char c;

	vfs_ReadCString(r, buf);
	p = fcn_0064d1a0(buf, '.');
	if (p != 0) {
		*p = 0;
	}
	q = buf;
	d = (char*) o[4] + o[2] * 0xe0 + 0x40;
	do {
		c = *q++;
		*d++ = c;
	} while (c != 0);
}
