extern unsigned char* g_entity_ptr;
/* AI step: take out a credit. Picks a target building of the right kind and a
 * lender, rates the lender's credit offers and fills the two action packets
 * with the best one; 0x33 on success. */

/* SIZE 0x24d */
typedef struct {
	unsigned char kind;
	char pad[0x246];
	unsigned char level;
	char pad248[0x24d - 0x248];
} BuildingRow;

extern int g_6643d8[];
extern int g_7f4c04;
extern unsigned char* lpGebaeudePROT;
extern float g_662a3c;
extern float g_662a94;
extern float g_6628a8;

extern unsigned short __cdecl gm_RandomMod(int);
extern char* __cdecl fcn_005463a0(int, int, int, int, int);
extern char* __cdecl he_fn_Handlung(void);
extern int __cdecl fcn_0050d6d0(char*, short*, int, int*);
extern int __cdecl fcn_004f4830(int, int*);

/* ADDRESS: GOLDTL 0x0049e900 */
int __cdecl ai_StartKreditNehmen(int code, short* target, char* ent, char* out1, char* out2)
{
	int v[4];
	int rec[9];
	int msg[9];
	float score[4];
	int n;
	int i;
	int j;
	int t;
	int best;
	char* e;
	char* e2;
	BuildingRow* row;
	float d;

	v[0] = g_6643d8[gm_RandomMod(0x10)];
	if (ent[2] == 3)
		return 0;
	if (code != 0x33 && code != 0x13 && code != 0x10 && code != 0x11)
		return 0;
	n = 0;
	if (fcn_005463a0(2, 0, 0x23, 2, *(unsigned short*) ent) != 0) {
		do {
			n++;
		} while (he_fn_Handlung() != 0);
	}
	if (gm_RandomMod(10) < n + 1)
		return 0;
	if (code == 0x33) {
		t = (g_7f4c04 & 0xffff) - 8;
		if (t <= 0 || t < 10)
			t = t > 0 ? t : 0;
		else
			t = 10;
		d = (10 - t) * g_662a3c;
		d = d * d;
		v[1] = (int) (*(float*) 0x664378 * d);
		v[2] = (int) (*(float*) 0x664374 * d);
		v[3] = (int) (d * *(float*) 0x664370);
		j = gm_RandomMod(0x100);
		for (i = 0x100; ; ) {
			e = (char*) g_entity_ptr + j * 0xa9;
			if (e[0] != 0 && *(short*) (e + 0x27) == *target) {
				row = &((BuildingRow*) lpGebaeudePROT)[*(unsigned char*) e];
				if (((1 << row->kind) & 0x7d4390) != 0 && *(int*) (e + 0x39) < v[row->level])
					break;
			}
			j = (j + v[0]) % 0x100;
			if (--i == 0)
				return 0;
		}
		j = gm_RandomMod(0x100);
		for (i = 0x100; ; ) {
			e2 = (char*) g_entity_ptr + j * 0xa9;
			if (e2[0] != 0 && *(short*) (e2 + 0x27) != *target
			    && ((BuildingRow*) lpGebaeudePROT)[*(unsigned char*) e2].kind == 5)
				break;
			j = (j + v[0]) % 0x100;
			if (--i == 0)
				return 0;
		}
		n = fcn_0050d6d0(e2, target, 3, rec);
		if (n <= 0)
			return 0;
		fcn_004f4830(0xe, msg);
		for (i = 0; i < n; i++)
			score[i + 1] = (float) (msg[6] - 2) / rec[i * 3 + 2] * (rec[i * 3 + 1] * *(float*) 0x662dbc) * rec[i * 3];
		d = g_6628a8;
		best = -1;
		for (i = 0; i < n; i++) {
			if (d < score[i + 1]) {
				d = score[i + 1];
				best = i;
			}
		}
		if (best < 0 && best > 2)
			return 0;
		out1[0] = 4;
		*(int*) (out1 + 4) = *(int*) (e2 + 1);
		*(int*) (out1 + 8) = *(int*) (e + 1);
		out2[0] = 0x14;
		*(int*) (out2 + 4) = rec[best * 3];
		*(int*) (out2 + 8) = rec[best * 3 + 1];
		*(int*) (out2 + 0x10) = rec[best * 3 + 2];
		return 0x33;
	}
	if (*(unsigned char*) out1 != 0x12)
		return 0;
	j = gm_RandomMod(0x100);
	for (i = 0x100; ; ) {
		e2 = (char*) g_entity_ptr + j * 0xa9;
		if (e2[0] != 0 && *(short*) (e2 + 0x27) != *target
		    && ((BuildingRow*) lpGebaeudePROT)[*(unsigned char*) e2].kind == 5)
			break;
		j = (j + v[0]) % 0x100;
		if (--i == 0)
			return 0;
	}
	n = fcn_0050d6d0(e2, target, 3, rec);
	if (n <= 0)
		return 0;
	fcn_004f4830(0xe, msg);
	for (i = 0; i < n; i++) {
		if ((unsigned int) rec[i * 3] > *(unsigned int*) (out1 + 8))
			score[i + 1] = (float) (msg[6] - 2) / rec[i * 3 + 2] * (rec[i * 3 + 1] * *(float*) 0x662dbc) * rec[i * 3];
		else
			score[i + 1] = g_662a94;
	}
	d = g_6628a8;
	best = -1;
	for (i = 0; i < n; i++) {
		if (d < score[i + 1]) {
			d = score[i + 1];
			best = i;
		}
	}
	if (best < 0 || best > 2)
		return 0;
	out1[0] = 4;
	*(int*) (out1 + 4) = *(int*) (e2 + 1);
	*(int*) (out1 + 8) = -1;
	*(int*) (out2 + 4) = rec[best * 3];
	*(int*) (out2 + 8) = rec[best * 3 + 1];
	out2[0] = 0x14;
	*(int*) (out2 + 0x10) = rec[best * 3 + 2];
	return 0x33;
}
