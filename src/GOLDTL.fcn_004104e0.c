

// SIZE 0x2
typedef struct {
	unsigned char kind : 5;
	unsigned char f5 : 1;
	unsigned char f6 : 1;
	unsigned char f7 : 1;
	unsigned char g0 : 1;
} Bits;

extern char* g_6b7e98;
int __cdecl m_is_tracked(char* p);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_004104e0(char** a, int* s, unsigned char* k, unsigned char* b5, unsigned char* b6, unsigned char* b7, unsigned char* c0)
{
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	*(float*) (e + 0xb4) = *s * 0.01f;
	((Bits*) (e + 0xd4))->kind = *k;
	((Bits*) (e + 0xd4))->f5 = *b5;
	((Bits*) (e + 0xd4))->f6 = *b6;
	((Bits*) (e + 0xd4))->f7 = *b7;
	((Bits*) (e + 0xd4))->g0 = *c0;
	return 0;
}
