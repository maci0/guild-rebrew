// FUNCTION: GOLDTL 0x40fe00
// SIZE: 73

// SIZE 0x217
typedef struct {
	char pad[0x216];
	unsigned char b0 : 2;
	unsigned char b2 : 1;
} S40fe00;

void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040fe00(S40fe00** a1, char* a2)
{
	S40fe00* p;

	p = *a1;
	if (p == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x6769e8);
		return 0;
	}
	p->b2 = *a2;
	return 1;
}
