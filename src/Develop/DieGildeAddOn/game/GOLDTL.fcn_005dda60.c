


typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3;
	int handle;
	char pad8;
	char side;
	char pada[0x166 - 0xa];
	char ready;
	char pad167[0x21c - 0x167];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];

int __cdecl gm_RandomMod(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
char* __cdecl gm_LookupSpecialObjectRecord(int, int*);
void __cdecl d2_ShowUseObjDialog(char*);

int __cdecl gm_ObjBefriendThreeRivals(Ent* ent, int* arg)
{
	Ent* picks[3];
	int tmp;
	char text[0x800];
	char* rec;
	int r;
	int n;
	int m;
	int i;

	arg[4] = 1;
	r = gm_RandomMod(0x300) & 0xffff;
	n = 0x300;
	while (n != 0) {
		if (r != ent->id && ((Ent*)g_7f4ca0)[r].id != 0xffff && ((Ent*)g_7f4ca0)[r].kind < 10 &&
		    ((Ent*)g_7f4ca0)[r].side != ent->side && ((Ent*)g_7f4ca0)[r].ready != 0) {
			picks[0] = &((Ent*)g_7f4ca0)[r];
			break;
		}
		n--;
		r = (r + 1) % 0x300;
	}
	r = gm_RandomMod(0x300) & 0xffff;
	m = 0x300;
	while (m != 0) {
		if (r != ent->id && r != picks[0]->id && ((Ent*)g_7f4ca0)[r].id != 0xffff &&
		    ((Ent*)g_7f4ca0)[r].kind < 10 && ((Ent*)g_7f4ca0)[r].side != ent->side) {
			picks[1] = &((Ent*)g_7f4ca0)[r];
			break;
		}
		m--;
		r = (r + 7) % 0x300;
	}
	r = gm_RandomMod(0x300) & 0xffff;
	m = 0x300;
	while (m != 0) {
		if (r != ent->id && r != picks[0]->id && r != picks[1]->id && ((Ent*)g_7f4ca0)[r].id != 0xffff &&
		    ((Ent*)g_7f4ca0)[r].kind < 10 && ((Ent*)g_7f4ca0)[r].side != ent->side) {
			picks[2] = &((Ent*)g_7f4ca0)[r];
			break;
		}
		m--;
		r = (r + 13) % 0x300;
	}
	cm_RequestCopyEntityData(ent->handle, picks[0]->handle, 0x14, 1);
	cm_RequestCopyEntityData(ent->handle, picks[1]->handle, 0x14, 1);
	cm_RequestCopyEntityData(ent->handle, picks[2]->handle, 0x14, 1);
	io_FormatTextBuffer(text, 0xfef, ent->id);
	for (i = 0; i < 3; i++) {
		if (picks[i]->kind == 6 || picks[i]->kind == 7) {
			he_PostEntityMessage(picks[i]->handle, -1, text, 0, 0x5ec, 0);
		}
	}
	if (ent->kind == 6) {
		rec = gm_LookupSpecialObjectRecord(**(unsigned short**) arg, &tmp);
		io_FormatTextBuffer(text, 0xfe8, *(unsigned short*) (rec + 0x18) + 1, picks[0]->id, picks[1]->id,
		    picks[2]->id);
		d2_ShowUseObjDialog(text);
	}
	return 1;
}
