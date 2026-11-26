


// SIZE 0x50
typedef struct {
	int a;
	int size;
	int c;
	int d;
	int kind;
	int pad[14];
	int id;
} Req;

extern char* g_14abce8;

int __cdecl d2_CheckOwnerBlocked(int);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_005afa50(void);
void __cdecl fcn_005bdc30(int, Req*, char*, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);

void __cdecl d2_StartZollkasseTargetSelect(int building)
{
	Req req;

	if (d2_CheckOwnerBlocked(building) == 0 && building != 0) {
		req.a = 1;
		req.size = -1;
		req.kind = 6;
		req.c = 0xa0744300;
		req.d = 1;
		req.id = 0x727;
		fcn_0052a0c0(building, 0);
		fcn_005bdc30(1, &req, g_14abce8, fcn_005afa50, 0);
		d2_RestoreHudAfterDialog();
		sv_ClearObjectSelection();
	}
}
