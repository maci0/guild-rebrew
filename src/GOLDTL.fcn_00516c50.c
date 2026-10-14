


#pragma pack(push, 1)
// SIZE 0x61
typedef struct {
	unsigned char office;
	char pad1[0x26];
	unsigned short slot;
	char pad29[0x34];
	int home;
} Player;

// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x24c];
} Office;
#pragma pack(pop)

// SIZE 0x228
typedef struct {
	char pad0[0x224];
	int shown;
} Contact;

extern unsigned char* g_868050;
extern unsigned short g_774970;
extern int g_67a370;
extern int g_6b8300;

void* __cdecl fcn_00502cd0(int, int, int, ...);
Contact* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00442c00(Contact*, int);
void __cdecl fcn_00515c60(Player*, void*);
void __cdecl fcn_00437ac0(int, int, int, void*);
void __cdecl fcn_00515e10(void);
void __cdecl fcn_00515fb0(Player*);
int __cdecl gm_CheckEntityType(Player*);
void __cdecl fcn_004379a0(int, int, int, void*, Player*);
void __cdecl fcn_005165f0(void);
void __cdecl fcn_00516de0(int, char);
void __cdecl fcn_00516040(void);
void __cdecl fcn_00443230(int);
void __cdecl fcn_0052a7d0(void);

void __cdecl fcn_00516c50(Player* p, void* unit)
{
	Office* o;
	Contact* c;

	o = &((Office*)g_868050)[p->office];
	if (unit == 0) {
		unit = fcn_00502cd0(p->home, 2, 6, 0, 0xfd);
	}
	c = fcn_00445600(0, 0xa0, 0, "contact_EINKAUF");
	if (c == 0) {
		c = fcn_00445600(0, 0xa0, 0, "contact_EINKAUF_METALL");
	}
	if (c == 0) {
		c = fcn_00445600(0, 0xa0, 0, "contact_EINKAUF_SKRIPTE");
	}
	if (c == 0) {
		c = fcn_00445600(0, 0xa0, 0, "contact_EINKAUF_HOLZ");
	}
	if (c == 0) {
		c = fcn_00445600(0, 0xa0, 0, "contact_EINKAUF_STEIN");
	}
	if (c != 0) {
		if (p->slot == g_774970) {
			fcn_00442c00(c, 0);
		} else {
			fcn_00442c00(c, 1);
			fcn_00515c60(p, unit);
		}
		c->shown = 1;
	} else if (o->kind == 5 && p->slot != g_774970) {
		fcn_00515c60(p, unit);
	}
	fcn_00437ac0(g_67a370, 0, 0x20, fcn_00515e10);
	fcn_00515fb0(p);
	if (gm_CheckEntityType(p) == 0) {
		fcn_004379a0(g_67a370, 0, 0xc0, fcn_005165f0, p);
	}
	fcn_00516de0(g_6b8300, 0);
	fcn_00516040();
	fcn_00443230(0);
	fcn_0052a7d0();
}
