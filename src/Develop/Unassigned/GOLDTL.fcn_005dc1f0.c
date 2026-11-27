


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

void __cdecl cm_RequestChangeFloat(int, int, float);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowUseObjDialog(char*);

int __cdecl gm_ObjBoostEntityHealth(Ent* ent, Cmd* cmd)
{
	char text[0x800];

	if (cmd->shown == 1) {
		cm_RequestChangeFloat(ent->handle, 0x1c, ent->mood * 0.1f);
		return 1;
	}
	if (cmd->shown == 0 && ent->kind == 6) {
		cmd->done = 1;
		io_FormatTextBuffer(text, 0xff0);
		d2_ShowUseObjDialog(text);
	}
	return 1;
}
