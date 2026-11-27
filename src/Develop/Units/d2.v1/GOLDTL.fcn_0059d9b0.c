


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

int __cdecl d2_CheckOwnerBlocked(int);
void __cdecl d2_InitPlayerBar(int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowBriberyDialog(void);
void __cdecl fcn_005bdc30(int, Req*, char*, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);

void __cdecl d2_SelectBriberyTarget(int e)
{
	Req req;
	char text[0x400];

	if (d2_CheckOwnerBlocked(e) == 0) {
		memset(&req, 0, sizeof(req));
		req.size = 0x400;
		if (e != 0) {
			d2_InitPlayerBar(e, 0);
			req.id = 0x727;
			req.kind = 6;
			req.c = 0;
			io_FormatTextBuffer(text, 0x19f6);
			fcn_005bdc30(1, &req, text, d2_ShowBriberyDialog, 0);
			d2_RestoreHudAfterDialog();
			sv_ClearObjectSelection();
		}
	}
}
