// FUNCTION: GOLDTL 0x005d9ca0
// SIZE: 713

typedef struct Msg {
	int pad0;
	unsigned char type;
	char pad5[3];
	int src;
	int dst;
	char pad10[0x36 - 0x10];
	unsigned char b36;
	char pad37[0x58 - 0x37];
	int owner;
	int target;
	int who[4];
	char pad70[0xf8 - 0x70];
} Msg;
// SIZE 0xf8

typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int handle;
	char pad8[4];
	char female;
	char padd[0x166 - 0xd];
	unsigned char rank;
	char pad167[0x21c - 0x167];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[768];
extern unsigned short g_774970;
extern char* g_868050;
extern Ent* g_773dac;
extern Ent* g_773db0;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_AddObjekt(void);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_004a57a0(Ent*, int, int, unsigned short*, int, float, int*);
void __cdecl fcn_004c5530(Msg*);

int __cdecl fcn_005d9ca0(Ent* ent, Ent* other, int count, int flag)
{
	unsigned short ids[4];
	int out;
	Msg msg;
	unsigned char* q;
	unsigned int i;

	ids[0] = 0xffff;
	ids[1] = 0xffff;
	ids[2] = 0xffff;
	ids[3] = 0xffff;
	q = gm_StartFilteredEntitySearch(1, 6);
	while (q != 0) {
		if (g_868050[*q * 0x24d] == 15) {
			break;
		}
		q = gm_AddObjekt();
	}
	if (q == 0) {
		return 0x10;
	}

	msg.src = ent->handle;
	msg.dst = g_7f4ca0[g_774970].handle;
	msg.owner = ent->handle;
	msg.type = 0x2c;
	msg.b36 = 2;
	msg.target = other->handle;
	ids[0] = other->id;
	msg.who[0] = -1;
	msg.who[1] = -1;
	msg.who[2] = -1;
	msg.who[3] = -1;
	if (flag == 0) {
		for (i = 0; i < 768; i++) {
			if (g_7f4ca0[i].rank == 13) {
				msg.who[0] = g_7f4ca0[i].handle;
				ids[1] = g_7f4ca0[i].id;
				break;
			}
		}
		if (msg.who[0] == -1) {
			if ((short) fcn_0042e410(2)) {
				msg.who[0] = g_773dac->handle;
				ids[1] = g_773dac->id;
			} else {
				msg.who[0] = g_773db0->handle;
				ids[1] = g_773db0->id;
			}
		}
	} else {
		msg.who[0] = !ent->female ? g_773dac->handle : g_773db0->handle;
		ids[1] = !ent->female ? g_773dac->id : g_773db0->id;
	}
	if (other->rank != 0x11 && ent->rank != 0x11) {
		for (i = 0; i < 768; i++) {
			if (g_7f4ca0[i].rank == 0x11) {
				if (count > 2) {
					msg.who[3] = g_7f4ca0[i].handle;
				}
				ids[2] = g_7f4ca0[i].id;
				break;
			}
		}
	}
	if (!fcn_004a57a0(ent, 0xc00, 4, ids, 0, 100.0f, &out)) {
		return 0x40;
	}
	if (ids[2] == 0xffff) {
		ids[2] = (unsigned short) out;
	} else {
		ids[3] = (unsigned short) out;
	}
	msg.who[1] = g_7f4ca0[out & 0xffff].handle;
	if (!fcn_004a57a0(ent, 0xc00, 4, ids, 0, 100.0f, &out)) {
		return 0x40;
	}
	msg.who[2] = g_7f4ca0[out & 0xffff].handle;
	fcn_004c5530(&msg);
	return 0x10;
}
