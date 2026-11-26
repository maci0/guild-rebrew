


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

extern int g_14abd48;

int __cdecl d2_CheckOwnerBlocked(char*);
void __cdecl fcn_0052a0c0(char*, int);
void __cdecl fcn_005bdc30(int, Req*, int, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);
int __cdecl fcn_0059d380(int a0, char* a1);

void __cdecl fcn_0059d630(char* a)
{
	Req req;

	if (d2_CheckOwnerBlocked(a) != 0 || a == 0) {
		return;
	}
	memset(&req, 0, sizeof(req));
	req.a = 1;
	req.size = -1;
	req.kind = 6;
	req.c = 0xa07c43a0;
	req.d = 1;
	fcn_0052a0c0(a, 0);
	fcn_005bdc30(1, &req, g_14abd48, (void*) fcn_0059d380, 0);
	d2_RestoreHudAfterDialog();
	sv_ClearObjectSelection();
}
