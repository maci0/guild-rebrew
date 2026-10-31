/* Kidnapping transaction: picks the strongest free transporter of the guild,
 * sends the two captives (victim of the guild and the player's pick) to the
 * client with scaled visual slots, and posts the notification message. */

typedef struct {
	unsigned short id;
	char pad2[0xe];
	int f10;
	int f14;
	int f18;
	int f1c;
	float f20;
	float f24;
	float f28;
	float f2c;
	int f30;
	int f34;
	float f38;
	char pad3c[0x44];
} slot80;
// SIZE 0x80

int __cdecl fcn_00507080(int k);
void* __cdecl gm_StartFilteredEntitySearch(int a1, int a2, int a3);
void* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl fcn_00508cf0(int a1, int* a2);
float __cdecl gm_GetEntitySkill(char* entity, int index);
float __cdecl gm_RandomFloat01(void);
slot80* __cdecl gm_FindSlotById(int a1, int a2);
float __cdecl fcn_00502780(int a1, int a2);
int __cdecl fcn_004c61d0(slot80* e, unsigned char kind);
void __cdecl fcn_004c5420(int a1, int a2, int a3, int a4, int a5);
void __cdecl fcn_005100f0(int a1, int a2);
int __cdecl gm_RandomMod(int a1);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl fcn_00545d40(int a1, int a2, void* p, int a4, int a5, void* p6);
int __cdecl fcn_00526120(void* a1, int a2);

/* ADDRESS: GOLDTL 0x004eb3e0 */
unsigned int __cdecl fcn_004eb3e0(int* packet, char* self)
{
	slot80 ent;
	char buf1[512];
	char buf2[2048];
	int ids[10];
	int pick[2];
	slot80* e;
	unsigned char* q;
	float t;
	float scale;
	unsigned int v20;
	unsigned int v25;
	int found;
	int best;
	int k;
	int n;
	int i;
	int id;

	v20 = 0;
	v25 = 0;
	packet[3] = 0;
	packet[4] = 0;
	if (packet[0] != 3)
		return 0;
	if (packet[2] != 1 && packet[2] != -1)
		return 0;
	if (packet[1] < 1 || packet[1] > 7)
		return 0;
	found = fcn_00507080(packet[1]);
	if (found == 0)
		return 0;
	e = (slot80*) gm_StartFilteredEntitySearch(1, 5, found);
	if (e == 0)
		return 0;
	best = 0;
	do {
		q = (unsigned char*) (0x868050 + *(unsigned char*) e * 0x24d + 0x247);
		if (best < (int) *q) {
			v20 = *(unsigned char*) e;
			best = (int) *q;
		}
		e = (slot80*) gm_FindNextFilteredEntity();
	} while (e != 0);
	if (v20 == 0)
		return 0;
	k = 0;
	q = (unsigned char*) 0x699058;
	while (*q != v20) {
		q += 0x15;
		k++;
		if ((int) q >= 0x699361)
			return 0;
	}
	if (k >= 0x25)
		return 0;
	n = 0;
	q = (unsigned char*) (0x699058 + k * 0x15 + 1);
	for (i = 0; i < 10; i++) {
		if (*(unsigned short*) q != 0) {
			ids[n] = *(unsigned short*) q;
			n++;
		}
		q += 2;
	}
	if (n == 0)
		return 0;
	fcn_00508cf0(n, pick);
	if (n != 1) {
		v25 = (unsigned int) ids[pick[1]];
		v20 = (unsigned int) ids[pick[0]];
	} else {
		v20 = (unsigned int) ids[pick[0]];
	}
	t = gm_GetEntitySkill(self, 2);
	if (packet[2] == 1) {
		scale = (gm_RandomFloat01() + 1.0f) * t * *(float*) 0x6628d8 + *(float*) 0x664198;
	} else {
		scale = *(double*) 0x6629c8 -
			((gm_RandomFloat01() + 1.0f) * t * *(float*) 0x66414c + *(double*) 0x6628f0);
	}
	id = *(unsigned char*) 0x773d75;
	e = gm_FindSlotById(id, v20);
	if (e != 0) {
		ent = *e;
		ent.f24 = ent.f20 * scale;
		ent.f38 = fcn_00502780(id, v20);
		fcn_004c61d0(&ent, (unsigned char) id);
		packet[3] = v20;
		e = gm_FindSlotById(id, v25);
		if (e != 0) {
			ent = *e;
			ent.f24 = ent.f20 * scale;
			ent.f38 = fcn_00502780(id, v25);
			fcn_004c61d0(&ent, (unsigned char) id);
			packet[4] = v25;
		}
		fcn_004c5420(*(int*) (self + 4), 0x1c8, 4, 0x4000000, 0);
		fcn_005100f0(*(int*) (self + 4), -1);
		found = gm_RandomMod(3);
		if (packet[2] != 1) {
			io_FormatTextBuffer(buf1, (found & 0xffff) + 0x165a, packet[1] + 0x1648);
			io_FormatTextBuffer(buf2, 0x1659, buf1, v20 * 2 + 0x9a8, v25 * 2 + 0x9a8);
		} else {
			io_FormatTextBuffer(buf1, (found & 0xffff) + 0x1656, packet[1] + 0x1648);
			io_FormatTextBuffer(buf2, 0x1655, buf1, v20 * 2 + 0x9a8, v25 * 2 + 0x9a8);
		}
		for (q = (unsigned char*) 0x7f4ca4; (int) q < (int) 0x85a0a4; q += 0x21c) {
			if ((*(unsigned char*) (q - 2) == 7 || *(unsigned char*) (q - 2) == 6) &&
			    *(int*) (self + 4) != *(int*) q)
				fcn_00545d40(*(int*) q, -1, buf2, 1, 0x5ec, (void*) 0x6b5c60);
		}
		if (*(unsigned char*) (self + 2) == 6)
			fcn_00526120(buf2, 0x10);
	}
	return 0;
}
