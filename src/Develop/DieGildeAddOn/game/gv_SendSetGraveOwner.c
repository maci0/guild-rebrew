


#pragma pack(push, 1)
typedef struct
{
	int type;
	int a;
	int b;
	int c;
	char d;
	short e;
	int f;
	char pad[9];
} GV_SLOT_CMD_MSG;
// SIZE 0x20
#pragma pack(pop)

int __cdecl gv_EnqueueSlotCommand(GV_SLOT_CMD_MSG* m);

/* ADDRESS: GOLDDE 0x004dead0 */
int __cdecl gv_SendSetGraveOwner(int* a, char* b, int c, int d)
{
	GV_SLOT_CMD_MSG m;
	int t;

	if (b == 0 || d == -1) {
		return -1;
	}
	if (a == 0) {
		t = -1;
	} else {
		t = a[1];
	}
	m.a = t;
	m.b = *(int*) (b + 1);
	m.type = 3;
	m.c = c;
	m.d = (char) d;
	m.e = 0;
	m.f = 0;
	return gv_EnqueueSlotCommand(&m);
}
