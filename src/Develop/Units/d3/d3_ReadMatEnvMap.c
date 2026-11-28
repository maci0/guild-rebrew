typedef struct {
	char pad00[8];
	int idx;
	char pad0c[4];
	int base;
} D3_BIN_MAT_ENV_CTX;

char* __cdecl vfs_ReadCString(void* stream, char* text);
char* __cdecl strchr(const char* s, int c);

/* ADDRESS: GOLDTL 0x0044d9c0 */
/* ADDRESS: GOLDDE 0x00443700 */
void __cdecl d3_ReadMatEnvMap(void* stream, D3_BIN_MAT_ENV_CTX* c)
{
	char buf[0x100];
	char* dot;
	char* s;
	char* d;
	char ch;

	vfs_ReadCString(stream, buf);
	dot = strchr(buf, '.');
	if (dot != 0) {
		*dot = 0;
	}
	s = buf;
	d = (char*) (c->base + c->idx * 0xe0 + 0x80);
	do {
		ch = *s++;
		*d++ = ch;
	} while (ch != 0);
}
