


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

extern __int64 g_666018;
extern int g_66601c;

void __cdecl io_FormatTextBuffer(char*, int, ...);
char* __cdecl fcn_005cd440(Req*, char*, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
char* __cdecl fcn_005c6220(int, int*);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005df8f0(char* e, char* a2)
{
	int out;
	Req req;
	char text[0x100];
	char buf[0x200];
	char line[0x400];
	char* r;
	char* p;

	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(&req.pad[2], -1, 0x20);
		io_FormatTextBuffer(text, 0x9c);
		req.c = (*(int*)&g_666018);
		req.a = 1;
		req.size = 0x400;
		req.kind = 6;
		req.d = g_66601c;
		r = fcn_005cd440(&req, text, 0, 0);
	}
	else {
		r = gm_LookupEntityRecordById(*(int*) (a2 + 4));
	}
	if (r == 0) {
		return 0;
	}
	fcn_004c5420(*(int*) (r + 4), 0x1cc, 4, 0x400000, 0);
	if (e[2] == 6) {
		p = fcn_005c6220(**(unsigned short**) a2, &out);
		io_FormatTextBuffer(buf, *(unsigned short*) (p + 0x18) + 1, *(unsigned short*) r);
		io_FormatTextBuffer(line, 0xfe8, buf);
		fcn_005dbe90(line);
	}
	*(int*) (a2 + 0x10) = 1;
	return 1;
}
