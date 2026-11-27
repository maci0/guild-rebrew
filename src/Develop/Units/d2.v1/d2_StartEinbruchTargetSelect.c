


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;
// SIZE 0x50

int __cdecl d2_CheckOwnerBlocked(char*);
void __cdecl d2_InitPlayerBar(char*, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_RunCityScrollMapDialog(int, Req*, char*, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl d2_ConfirmEinbruch(void);

void __cdecl d2_StartEinbruchTargetSelect(char* building)
{
	Req req;
	char text[0x80];

	if (d2_CheckOwnerBlocked(building) != 0) {
		return;
	}
	memset(&req, 0, sizeof(req));
	req.size = 0x400;
	if (building == 0) {
		return;
	}
	d2_InitPlayerBar(building, 0);
	io_FormatTextBuffer(text, 0x19e2);
	req.id = 0x727;
	req.kind = 7;
	req.c = 0xa07443b4;
	req.d = 1;
	d2_RunCityScrollMapDialog(1, &req, text, (void*) d2_ConfirmEinbruch, 0);
	d2_RestoreHudAfterDialog();
	sv_ClearObjectSelection();
}
