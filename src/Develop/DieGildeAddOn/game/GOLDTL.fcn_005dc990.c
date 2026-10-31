

#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int pad14[2];
	int ids[8];
	int pad3c[5];
} Req;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x26];
	char b36;
	char pad37[0x21];
	char b58;
	char b59;
	char pad5a[2];
	float f5c;
	float f60;
	int f64;
	char pad68[0x90];
};

extern __int64 g_666018;

unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004c5530(struct msg*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
unsigned char* __cdecl fcn_005cd440(Req*, char*, int, void*);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* One result variable set on every path keeps the two arms' tails apart (no
   cross-jump). Each arm has its own message struct: with one shared struct,
   arm 2's b4 store written before the e+4 load issues ahead of the push. */
int __cdecl fcn_005dc990(unsigned char* obj, int* arg)
{
	Req req;
	char text[0x100];
	char text2[0x800];
	unsigned char* e;
	int result;

	if (obj[2] == 6) {
		memset(&req, 0, sizeof(req));
		memset(req.ids, 0xff, sizeof(req.ids));
		io_FormatTextBuffer(text, 0x9c);
		req.a = 0;
		req.size = 0x400;
		req.kind = 6;
		req.cd = g_666018;
		e = fcn_005cd440(&req, text, 0, 0);
		if (e != 0) {
			struct msg m;

			m.f8 = *(int*) (e + 4);
			m.b4 = (char) 0x82;
			m.fc = -1;
			m.b36 = 2;
			m.b58 = 3;
			m.f5c = -0.16666667f;
			m.b59 = 2;
			m.f60 = -0.16666667f;
			m.f64 = 0x18;
			fcn_004c5530(&m);
			if (e[2] == 6 || e[2] == 7) {
				io_FormatTextBuffer(text2, 0xff8);
				fcn_00545d40(*(int*) (e + 4), -1, text2, 0, 0x5fb, 0);
			}
			result = 1;
		} else {
			result = 0;
		}
	} else {
		e = gm_LookupEntityRecordById(arg[1]);
		if (e != 0) {
			struct msg m;

			m.b4 = (char) 0x82;
			m.f8 = *(int*) (e + 4);
			m.fc = -1;
			m.b36 = 2;
			m.b58 = 3;
			m.f5c = -0.16666667f;
			m.b59 = 2;
			m.f60 = -0.16666667f;
			m.f64 = 0x18;
			fcn_004c5530(&m);
			if (e[2] == 6 || e[2] == 7) {
				io_FormatTextBuffer(text2, 0xff8);
				fcn_00545d40(*(int*) (e + 4), -1, text2, 0, 0x5fb, 0);
			}
			result = 1;
		} else {
			result = 0;
		}
	}
	return result;
}
