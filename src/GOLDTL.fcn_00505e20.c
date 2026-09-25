// FUNCTION: GOLDTL 0x00505e20
// SIZE: 465

#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int a;
	int b;
	int c;
	short d;
} Stamp;
#pragma pack(pop)

#pragma pack(push, 1)
// SIZE 0x27
typedef struct {
	unsigned char office;
	int id;
	char pad5[0x20];
	unsigned short slot;
} Estate;

// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x24c];
} Office;
#pragma pack(pop)

// SIZE 0x8
typedef struct {
	unsigned short slot;
	char pad2[2];
	int id;
} Unit;

// SIZE 0x21c
typedef struct {
	char pad0[4];
	int id;
	char pad8[0x21c - 8];
} Entity;

// SIZE 0x88
typedef struct {
	char pad0[0x52];
	Stamp stamp;
	char pad60[0x24];
	int event;
} Order;

extern Office* g_868050;
extern Entity g_7f4ca0[];
extern char g_773d75;
extern Stamp g_7f4c00;

Estate* __cdecl gm_StartFilteredEntitySearch(int, int, int);
Unit* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c5f60(int, int, int);
void __cdecl fcn_004c6000(int, int);
void __cdecl fcn_00500bb0(Stamp*, int, int, int);
int __cdecl fcn_004c5620(int, Order*);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c4ef0(char*);

void __cdecl fcn_00505e20(int search, int buyer, int price, Order* o, int notify)
{
	Office* office;
	char msg[0x100];
	Estate* s;
	Unit* u;

	s = gm_StartFilteredEntitySearch(1, 1, search);
	u = fcn_00508e40(buyer);
	office = &g_868050[s->office];
	fcn_004c4eb0("buy_building");
	if (s->slot != 0xffff) {
		fcn_0051af00(msg, 0x17e6, s, u->slot, price);
		fcn_00545e80(g_7f4ca0[s->slot].id, -1, msg, 0, 0x5ff, s->id, -1, 0, "_NACHRICHTEN_HS_30");
		fcn_004c51a0(g_7f4ca0[s->slot].id, buyer, g_773d75, price);
		fcn_004c5f60(s->id, u->id, u->id);
		if (notify != 0 && office->kind == 2) {
			fcn_004c6000(u->id, s->id);
		}
	} else {
		fcn_004c5150(-1, buyer, g_773d75, price);
		fcn_004c5f60(s->id, u->id, u->id);
		if (notify != 0 && office->kind == 2) {
			fcn_004c6000(u->id, s->id);
		}
	}
	if (o != 0) {
		o->stamp = g_7f4c00;
		fcn_00500bb0(&o->stamp, 0, 0, 1);
		o->event = fcn_004c5620(-1, o);
	}
	fcn_004c5420(s->id, 0x5a, 2, 0, 2);
	fcn_004c4ef0("buy_building");
}
