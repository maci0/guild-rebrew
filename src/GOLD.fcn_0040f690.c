extern char* g_6b7e98;
// GLOBAL: GOLD 0x5f2b7c
extern char g_676bfc[];
// FUNCTION: GOLD 0x40f690
// SIZE: 82

// SIZE 0xcd
typedef struct {
	char pad[0xcc];
	unsigned char b0 : 5;
	unsigned char b5 : 1;
} S4105a0;

int __cdecl fcn_0041dd90(void*);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040f690(S4105a0** a1, char* a2)
{
	S4105a0* p;

	p = *a1;
	if (fcn_0041dd90(p) == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) ((char*) g_6b7e98 + 0x118), g_676bfc);
		return 0;
	}
	p->b5 = *a2;
	return 0;
}
