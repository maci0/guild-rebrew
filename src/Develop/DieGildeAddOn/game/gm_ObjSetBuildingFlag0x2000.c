


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

extern char* txt_TargetBuildingPrompt;

char* __cdecl d2_RunCityScrollMapDialog(int, Req*, char*, int, int);
char* __cdecl gm_SearchTable67(int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);

int __cdecl gm_ObjSetBuildingFlag0x2000(char* e, char* request)
{
	Req req;
	char* r;

	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		req.size = 0x410;
		req.kind = 4;
		req.c = 0xa0400300;
		req.d = 1;
		req.a = 0;
		r = d2_RunCityScrollMapDialog(1, &req, txt_TargetBuildingPrompt, 0, 0);
	}
	else {
		r = gm_SearchTable67(*(int*) (request + 4));
	}
	if (r == 0) {
		return 0;
	}
	cm_RequestChangeBits(*(int*) (r + 1), 0x5a, 2, 0x2000, 0);
	return 1;
}
