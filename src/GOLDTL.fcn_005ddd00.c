// FUNCTION: GOLD 0x005d17d0
// SIZE: 425
// FUNCTION: GOLDTL 0x005ddd00
// SIZE: 425

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

extern int g_666018;
extern int g_66601c;

void __cdecl fcn_0051af00(char*, int, ...);
char* __cdecl fcn_005cd440(Req*, char*, int, int);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

int __cdecl fcn_005ddd00(char* e, char* a2)
{
	Req req;
	char text[0x100];
	char msg[0x400];
	char* a;
	char* b;
	int result;

	result = 0;
	if (e[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(&req.pad[2], -1, 0x20);
		fcn_0051af00(text, 0x9c);
		req.c = g_666018;
		req.a = 0;
		req.size = 0x400;
		req.kind = 6;
		req.d = g_66601c;
		a = fcn_005cd440(&req, text, 0, 0);
		if (a == 0) {
			goto done;
		}
		req.pad[0] = 3;
		*(short*) &req.pad[2] = *(short*) a;
		fcn_0051af00(text, 0x9e);
		b = fcn_005cd440(&req, text, 0, 0);
	} else {
		a = fcn_00508e40(*(int*) (a2 + 4));
		b = fcn_00508e40(*(int*) (a2 + 8));
		if (a == 0) {
			goto done;
		}
	}
	if (b != 0) {
		result = 1;
		fcn_004c54c0(*(int*) (a + 4), *(int*) (b + 4), -0x19, result);
		fcn_004c54c0(*(int*) (b + 4), *(int*) (a + 4), -0x19, result);
		if (a[2] == 6 || a[2] == 7) {
			fcn_0051af00(msg, 0xfee, *(unsigned short*) b);
			fcn_00545d40(*(int*) (a + 4), -1, msg, 0, 0x5fb, 0);
		}
		if (b[2] == 6 || b[2] == 7) {
			fcn_0051af00(msg, 0xfee, *(unsigned short*) a);
			fcn_00545d40(*(int*) (b + 4), -1, msg, 0, 0x5fb, 0);
		}
	}
done:
	return result;
}
