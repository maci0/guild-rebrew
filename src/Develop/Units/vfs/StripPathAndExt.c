



char* __cdecl strchr(const char*, int);

/* ADDRESS: GOLDDE 0x00401040 */
char* __cdecl StripPathAndExt(char* path)
{
	char* p;
	char* q;

	q = strchr(path, '\\');
	p = q + 1;
	if (q == 0) {
		p = path;
	}
	q = strchr(p, '/');
	if (q != 0) {
		p = q + 1;
	}
	q = strchr(path, '.');
	if (q != 0) {
		*q = 0;
	}
	return p;
}
