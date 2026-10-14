


typedef struct Ent {
	char pad0[2];
	unsigned char kind;
	char pad3;
	int handle;
	char pad8[0x1c - 8];
	float mood;
} Ent;
// SIZE 0x20

typedef struct Cmd {
	char pad0[0xc];
	int shown;
	int done;
} Cmd;
// SIZE 0x14

void __cdecl fcn_004c5480(int, int, float);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005dc1f0(Ent* ent, Cmd* cmd)
{
	char text[0x800];

	if (cmd->shown == 1) {
		fcn_004c5480(ent->handle, 0x1c, ent->mood * 0.1f);
		return 1;
	}
	if (cmd->shown == 0 && ent->kind == 6) {
		cmd->done = 1;
		fcn_0051af00(text, 0xff0);
		fcn_005dbe90(text);
	}
	return 1;
}
