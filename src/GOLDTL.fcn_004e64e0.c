#include <string.h>

// SIZE 0x40
typedef struct {
	int id[16];
} Ids;

// SIZE 0x48
typedef struct {
	int who;
	Ids ids;
	int pad;
} Msg;

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004c5a20(int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_004e63e0(int*);
void __cdecl fcn_004c4eb0(char*);
int __cdecl fcn_004c6aa0(Msg*);
void __cdecl fcn_004c4ef0(char*);

// FUNCTION: GOLD 0x004e4b50
// FUNCTION: GOLDTL 0x004e64e0

int __cdecl fcn_004e64e0(int* c)
{
	Msg m;
	char* o;
	int i;
	int h;

	memset(&m, 0, sizeof(m));
	if ((*((unsigned char*) c + 0x26) & 0x80) == 0) {
		h = -1;
		for (i = 0; i < *((unsigned char*) c + 0x30); i++) {
			if (c[13 + i] != -1) {
				o = fcn_00508e40(c[13 + i]);
				if (o == 0 || (*(int*) (o + 0x20c) != -1 && *(int*) (o + 0x20c) != c[0] && (o[2] == 6 || o[2] == 7)))
					h = fcn_004c5a20(c[0], c[13 + i]);
			}
		}
		if (h != -1) {
			do {
				if (fcn_004c4450(h) != 0)
					break;
				fcn_00535960();
			} while (1);
		}
	} else {
		for (i = 0; i < *((unsigned char*) c + 0x30); i++) {
			if (c[13 + i] != -1) {
				o = fcn_00508e40(c[13 + i]);
				if (o != 0 && *(int*) (o + 0x20c) != -1 && *(int*) (o + 0x20c) != c[0] && (o[2] == 6 || o[2] == 7))
					return 0;
			}
		}
	}
	if (fcn_004e63e0(c) == 0)
		return -1;
	m.who = c[0];
	m.ids = *(Ids*) (c + 13);
	fcn_004c4eb0("cut_CutsceneReady");
	h = fcn_004c6aa0(&m);
	fcn_004c4ef0("cut_CutsceneReady");
	while (fcn_004c4450(h) == 0)
		fcn_00535960();
	return fcn_004c4450(h) != 2;
}
