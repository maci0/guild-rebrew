


#pragma pack(push, 1)

typedef struct
{
	int a;
	int b;
	int c;
	short d;
} S14b;

#pragma pack(pop)
// SIZE 0xe

int __cdecl gm_RandomMod(int);
void __cdecl he_FreeAction(void*);

void __cdecl fcn_00550da0(void* record)
{
	*(S14b*) ((char*) record + 0x52) = *(S14b*) ((char*) record + 0x44);
	if ((short) gm_RandomMod(2) != 0) {
		he_FreeAction(record);
	}
}
