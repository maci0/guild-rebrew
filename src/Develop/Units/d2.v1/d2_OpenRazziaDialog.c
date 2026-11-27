


void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

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

extern char* g_14abcd0;

int __cdecl d2_CheckOwnerBlocked(int);
void __cdecl d2_InitPlayerBar(int, int);
void __cdecl d2_RunStadtwacheDispatchDialog(void);
void __cdecl d2_RunCityScrollMapDialog(int, Req*, char*, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);

void __cdecl d2_OpenRazziaDialog(int e)
{
	Req req;

	if (d2_CheckOwnerBlocked(e) == 0) {
		memset(&req, 0, sizeof(req));
		req.size = 0x400;
		req.kind = 7;
		req.c = 0x90010;
		if (e != 0) {
			req.id = 0x727;
			d2_InitPlayerBar(e, 0);
			d2_RunCityScrollMapDialog(1, &req, g_14abcd0, d2_RunStadtwacheDispatchDialog, 0);
			d2_RestoreHudAfterDialog();
			sv_ClearObjectSelection();
		}
	}
}
