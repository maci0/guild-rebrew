typedef struct {
	char pad00[8];
	int idx;
	char pad0c[4];
	int base;
} Ctx_44d9c0;

char* __cdecl fcn_004011a0(void* stream, char* text);
char* __cdecl strchr(const char* s, int c);

/* ADDRESS: GOLDTL 0x0044d9c0 */
void __cdecl fcn_0044d9c0(void* stream, Ctx_44d9c0* c)
{
	char buf[0x100];
	char* dot;
	char* s;
	char* d;
	char ch;

	fcn_004011a0(stream, buf);
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
