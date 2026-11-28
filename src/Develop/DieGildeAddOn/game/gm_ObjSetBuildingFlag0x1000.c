


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

extern char str_empty[];

char* __cdecl d2_RunCityScrollMapDialog(int, Req*, char*, int, int);
char* __cdecl gm_SearchTable67(int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);

int __cdecl gm_ObjSetBuildingFlag0x1000(char* e, char* context)
{
	Req req;
	char* entry;

	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		req.size = 0x410;
		req.kind = 4;
		req.c = 0xa0747980;
		req.d = 1;
		req.a = 0;
		entry = d2_RunCityScrollMapDialog(1, &req, str_empty, 0, 0);
		if (entry == 0) {
			return 0;
		}
	}
	else {
		entry = gm_SearchTable67(*(int*) (context + 4));
		if (entry == 0) {
			return 0;
		}
	}
	cm_RequestChangeBits(*(int*) (entry + 1), 0x5a, 2, 0x1000, 0);
	return 1;
}
