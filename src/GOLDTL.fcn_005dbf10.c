// FUNCTION: GOLD 0x005cf9f0
// FUNCTION: GOLDTL 0x005dbf10

typedef struct Ent {
	char pad0[2];
	unsigned char kind;
	char pad3;
	int handle;
	char pad8[0x170 - 8];
	char* home;
	char pad174[0x1ec - 0x174];
	int flags;
} Ent;
// SIZE 0x1f0

typedef struct Cmd {
	unsigned short* rec;
	char pad4[8];
	int shown;
	int done;
} Cmd;
// SIZE 0x14

typedef struct Desc {
	char pad0[4];
	int value;
	int action;
	char padc[4];
	int flags;
	int (__cdecl* run)(Ent*, Cmd*);
} Desc;
// SIZE 0x18

extern char* g_aed32c;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c06;
extern int g_7f4c0a;
extern unsigned char g_773d75;

Desc* __cdecl fcn_005c61e0(int);
double __cdecl gm_RandomFloat01(void);
void __cdecl fcn_0057e880(int, int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c4510(unsigned short*, int);
int __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl fcn_004f4f60(int, int, int, int, int);
char* __cdecl fcn_005c6220(int, int*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005dbf10(Ent* ent, Cmd* cmd)
{
	char one;
	int result;
	int v8;
	int vc;
	char text[0x800];
	Desc* d;
	char* rec;

	if (ent == 0) {
		return -1;
	}
	if (cmd == 0) {
		return -2;
	}
	cmd->done = 0;
	if (cmd->rec == 0) {
		return -3;
	}
	d = fcn_005c61e0(*cmd->rec);
	if (d == 0) {
		return -4;
	}
	if (ent->flags & d->flags) {
		return -5;
	}
	cmd->shown = *cmd->rec != 0x175 || gm_RandomFloat01() >= 0.66;
	if (d->run != 0) {
		result = d->run(ent, cmd);
	} else {
		result = 1;
	}
	if (result != 0) {
		fcn_0057e880(0x2d, 0, 0, *cmd->rec);
		if (d->flags != 0) {
			fcn_004c5420(ent->handle, 0x1ec, 4, d->flags, 0);
		}
		if (d->value != 0) {
			vc = d->value;
			v8 = 1;
			one = 1;
			fcn_004c4510(cmd->rec, *(int*) (cmd->rec + 1));
			fcn_004c4570(4, 1, (unsigned short) ((int) cmd->rec - (*(int*)&g_aed32c) + 0x1c), &vc);
			fcn_004c4570(4, 1, (unsigned short) ((int) cmd->rec - (*(int*)&g_aed32c) + 0x21), &v8);
			fcn_004c4570(1, 1, (unsigned short) ((int) cmd->rec - (*(int*)&g_aed32c) + 0x20), &one);
			fcn_004c4570(4, 1, (unsigned short) ((int) cmd->rec - (*(int*)&g_aed32c) + 0x2d), &(*(int*)&g_7f4c00));
			fcn_004c4570(2, 1, (unsigned short) ((int) cmd->rec - (*(int*)&g_aed32c) + 0x31), &(*(short*)&g_7f4c04));
			fcn_004c4570(4, 1, (unsigned short) ((int) cmd->rec - (*(int*)&g_aed32c) + 0x33), &g_7f4c06);
			fcn_004c4570(4, 1, (unsigned short) ((int) cmd->rec - (*(int*)&g_aed32c) + 0x37), &g_7f4c0a);
			fcn_004c5360();
		}
		if (d->value == 0) {
			fcn_004c51f0(-1, ent->handle, *cmd->rec, 1, g_773d75, 0);
		}
		if (d->action != -1) {
			if (ent->home) {
				fcn_004f4f60(d->action, 1, ent->handle, -1, *(int*) (ent->home + 1));
			} else {
				fcn_004f4f60(d->action, 1, ent->handle, -1, -1);
			}
		}
		if (ent->kind == 6 && cmd->done == 0) {
			rec = fcn_005c6220(*cmd->rec, &v8);
			if (cmd->shown == 1) {
				fcn_0051af00(text, 0xfe8, *(unsigned short*) (rec + 0x18) + 1);
			}
			fcn_005dbe90(text);
		}
	}
	return result;
}
