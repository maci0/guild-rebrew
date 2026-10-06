// FUNCTION: GOLDTL 0x410600

// SIZE 0xd5
typedef struct {
	char pad[0xd4];
	unsigned char b0 : 6;
	unsigned char b6 : 1;
} S410600;

int __cdecl fcn_0041dd90(void*);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_00410600(S410600** a1, char* a2)
{
	S410600* p;

	p = *a1;
	if (fcn_0041dd90(p) == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676c24);
		return 0;
	}
	p->b6 = *a2;
	return 0;
}
