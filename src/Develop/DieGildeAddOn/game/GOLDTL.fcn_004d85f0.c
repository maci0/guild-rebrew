


typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

extern stamp14 g_68bf38;

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
char* __cdecl fcn_0040c230(int, void*, int, int, int);
void __cdecl fcn_004d4ec0(void);

void __cdecl fcn_004d85f0(int* a)
{
	char* e;
	char* o;

	if (a[1] == 0 || a[0] == -1)
		return;
	e = gm_LookupEntityRecordIn32SlotTable(a[0]);
	o = fcn_0040c230(*(int*) (e + 0x184), fcn_004d4ec0, 5, 0x2e, 1);
	*(char**) (o + 0x17c) = e;
	*(stamp14*) (o + 0xf0) = g_68bf38;
}
