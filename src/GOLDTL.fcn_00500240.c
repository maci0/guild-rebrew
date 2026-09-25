// FUNCTION: GOLDTL 0x00500240
// SIZE: 416

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3[6];
	unsigned char cls;
	unsigned short age;
	char padc[0x20 - 0xc];
	float years;
	char pad24[0x164 - 0x24];
	unsigned char group;
	unsigned char kind;
	char pad166[0x16c - 0x166];
	int home;
	char pad170[0x1c8 - 0x170];
	int flags;
	char pad1cc[0x21c - 0x1cc];
} Obj;

extern Obj g_7f4ca0[];

int __cdecl gm_EntityClassCheck(int kind);
int __cdecl gm_IsInRange(int cls);
int __cdecl fcn_0050f950(int a, int i);

Obj* __cdecl fcn_00500240(char* who, int kind, int group)
{
	int i;
	int c;

	if (kind != 0) {
		for (i = 0; i < 768; i++) {
			if (g_7f4ca0[i].id != 0xffff && !(g_7f4ca0[i].flags & 0x2000) && g_7f4ca0[i].type <= 1 &&
			    (g_7f4ca0[i].kind == kind || g_7f4ca0[i].kind == 0) && g_7f4ca0[i].home == 0 &&
			    (float) g_7f4ca0[i].age >= g_7f4ca0[i].years && g_7f4ca0[i].group == group) {
				c = gm_EntityClassCheck(kind);
				if ((c == 2 || g_7f4ca0[i].cls == c) &&
				    (*(unsigned short*) (who + 0x27) == 0xffff ||
				     fcn_0050f950(*(unsigned short*) (who + 0x27), i) > -30)) {
					goto found;
				}
			}
		}
		return 0;
	}
	if (group == 0) {
		return 0;
	}
	c = gm_IsInRange((unsigned char) group);
	for (i = 0; i < 768; i++) {
		if (g_7f4ca0[i].id != 0xffff && !(g_7f4ca0[i].flags & 0x2000) && g_7f4ca0[i].type <= 1 &&
		    g_7f4ca0[i].group == group && g_7f4ca0[i].home == 0 && (c == 2 || g_7f4ca0[i].cls == c) &&
		    (*(unsigned short*) (who + 0x27) == 0xffff || fcn_0050f950(*(unsigned short*) (who + 0x27), i) > -30)) {
			goto found;
		}
	}
	return 0;
found:
	g_7f4ca0[i].flags |= 0x2000;
	return &g_7f4ca0[i];
}
