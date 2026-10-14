


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

// SIZE 0x84
typedef struct {
	int ids[32];
	int count;
} IdList;

extern int g_67a370;
extern int g_776664;

void __cdecl fcn_005982d0(void);
void __cdecl fcn_004379a0(int, int, int, void*, IdList*);
void __cdecl fcn_00442d50(int, int);

void __cdecl fcn_00598330(int a, int flag)
{
	IdList list;
	int i;
	int id;

	memset(&list, 0, sizeof(list));
	fcn_004379a0(g_67a370, a, 0x2c0, fcn_005982d0, &list);
	for (i = 0; i < list.count; i++) {
		id = list.ids[i];
		if (flag != 0 && (i < (g_776664 & 0xff) || (char) g_776664 == 2)) {
			fcn_00442d50(id, 1);
		}
		else {
			fcn_00442d50(id, 0);
		}
	}
}
