typedef struct
{
	unsigned char id;
	char pad1[3];
	int x4;
	unsigned char type;
	char pad9[3];
	int xc;
	unsigned char x10;
	char pad11[7];
} Rec18;
// SIZE 0x18

extern Rec18 g_68da68[];
extern Rec18 g_9a9220[];

// FUNCTION: GOLDTL 0x004e7b70
// SIZE: 121
int __cdecl fcn_004e7b70(char* e, Rec18* kind, Rec18* slot)
{
	int r;
	int i;
	int key;

	r = 0;
	if (e == 0 || *(unsigned short*) e == 0xffff || e[0x166] == 0) {
		return 0;
	}
	key = *(int*) (e + 4);
	for (i = 0; i < 0x1e; i++) {
		if (key == g_9a9220[i].x4) {
			r = 1;
			*slot = g_9a9220[i];
			*kind = g_68da68[g_9a9220[i].type];
			break;
		}
	}
	return r;
}

// FUNCTION: GOLDTL 0x004e7bf0
// SIZE: 124
int __cdecl fcn_004e7bf0(char* e, Rec18* kind, Rec18* slot)
{
	int r;
	int i;
	int key;

	r = 0;
	if (e == 0 || *(unsigned short*) e == 0xffff || e[0x169] == 0) {
		return 0;
	}
	key = *(int*) (e + 4);
	for (i = 0x1e; i < 0x25; i++) {
		if (key == g_9a9220[i].x4) {
			r = 1;
			*slot = g_9a9220[i];
			*kind = g_68da68[g_9a9220[i].type];
			break;
		}
	}
	return r;
}
