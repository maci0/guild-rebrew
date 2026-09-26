// FUNCTION: GOLDTL 0x00504130
// SIZE: 288
// FUNCTION: GOLD 0x005012e0
// SIZE: 288

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3[0x16c - 3];
	unsigned char* home;
	unsigned char* work;
	char pad174[0x21c - 0x174];
} Obj;

extern char g_7f4ca0[];

void __cdecl fcn_005b1c90(int h);
void __cdecl fcn_0041ddd0(void* p);
void __cdecl gv_FreeFieldAllocs(int* slot);
int __cdecl gm_FreeObjectListRecursive(char** list);

int __cdecl fcn_00504130(unsigned char* o)
{
	int i;

	if (o == 0) {
		return -1;
	}
	if (*o == 0) {
		return -2;
	}
	if (*(unsigned short*) (o + 0x27) != 0xffff && ((Obj*)g_7f4ca0)[*(unsigned short*) (o + 0x27)].type == 6) {
		fcn_005b1c90(*(int*) (o + 1));
	}
	switch (*o) {
	case 0x1e:
		if (*(void**) (o + 0x71) != 0) {
			fcn_0041ddd0(*(void**) (o + 0x71));
			*(void**) (o + 0x71) = 0;
		}
		*(void**) (o + 0x71) = 0;
		break;
	case 0x48:
	case 0x49:
	case 0x4a:
		gv_FreeFieldAllocs(*(int**) (o + 0x65));
		*(void**) (o + 0x65) = 0;
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		fcn_0041ddd0(*(void**) (o + 0x65));
		*(void**) (o + 0x65) = 0;
		break;
	}
	for (i = 0; i < 768; i++) {
		if (((Obj*)g_7f4ca0)[i].work == o) {
			((Obj*)g_7f4ca0)[i].work = 0;
		}
		if (((Obj*)g_7f4ca0)[i].home == o) {
			((Obj*)g_7f4ca0)[i].home = 0;
		}
	}
	if (*(char**) (o + 0x5d) != 0) {
		gm_FreeObjectListRecursive((char**) (o + 0x5d));
	}
	*o = 0;
	return 0;
}
