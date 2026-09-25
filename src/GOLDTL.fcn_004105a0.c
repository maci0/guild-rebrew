// FUNCTION: GOLDTL 0x4105a0
// SIZE: 82

// SIZE 0xd5
typedef struct {
	char pad[0xd4];
	unsigned char b0 : 5;
	unsigned char b5 : 1;
} S4105a0;

int __cdecl fcn_0041dd90(void*);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_004105a0(S4105a0** a1, char* a2)
{
	S4105a0* p;

	p = *a1;
	if (fcn_0041dd90(p) == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676bfc);
		return 0;
	}
	p->b5 = *a2;
	return 0;
}
