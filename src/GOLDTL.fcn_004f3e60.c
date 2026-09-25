#pragma pack(push, 1)
typedef struct Kind4f3e60 {
	unsigned char kind;
	char pad1[0x230];
	unsigned char b231;
	unsigned char b232;
	char pad233[0x24d - 0x233];
} Kind4f3e60;
#pragma pack(pop)
// SIZE 0x24d

extern Kind4f3e60* g_868050;
extern char g_7f4ca0[];

// FUNCTION: GOLD 0x4f1d50
// SIZE: 144
// FUNCTION: GOLDTL 0x004f3e60
// SIZE: 137
int __cdecl fcn_004f3e60(unsigned char* s, int* count)
{
	Kind4f3e60* k;
	int cap;
	int n;
	int p;

	k = &g_868050[*s];
	if (k->kind != 0x1d) {
		return -1;
	}
	if (*(int*) (s + 0x65) == 0) {
		return -1;
	}
	cap = k->b232 + k->b231;
	n = 0;
	for (p = (int) (g_7f4ca0 + 0x16c); p < (int) (g_7f4ca0 + 0x16c + 0x65400); p += 0x21c) {
		if (*(unsigned short*) (p - 0x16c) != 0xffff && *(char*) (p - 0x16a) == 0x14 && *(unsigned char**) p == s) {
			n++;
		}
	}
	if (count != 0) {
		*count = n;
	}
	return n < cap;
}
