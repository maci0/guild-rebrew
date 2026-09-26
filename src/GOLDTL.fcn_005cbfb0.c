typedef struct Sel {
	char* who;
	char pad4[0x28];
	int x2c;
	int x30;
	int x34;
} Sel;
// SIZE 0x38

typedef struct Player {
	unsigned short id;
	char pad2[0x166];
	unsigned char x168;
	char pad169[0xb3];
} Player;
// SIZE 0x21c

extern char g_7f4ca0[];

int __cdecl fcn_004e9310(int k, int max, char** out);
int __cdecl fcn_005ca560(Sel* s);
int __cdecl fcn_005cf720(unsigned short a, unsigned short b, void* q, int c);

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// FUNCTION: GOLDTL 0x005cbfb0
// SIZE: 335

/* Fills out[] with the entries fcn_004e9310 lists for e[0x168], then up to
 * three players whose byte 0x168 matches. Returns the count filled; with
 * max == 0, the count available. The inventory entry also holds a second
 * function at 0x5cc100 (314 bytes). */
unsigned int __cdecl fcn_005cbfb0(char* e, unsigned int max, Sel* out, void* q)
{
	int m;
	unsigned int n;
	Player* pl[3];
	char* ids[6];
	unsigned int k;
	int j;
	int i;

	if (*(unsigned char*) (e + 0x168) == 0) {
		return 0;
	}
	n = fcn_004e9310(*(unsigned char*) (e + 0x168), 6, ids);
	m = 0;
	for (i = 0; i < 768; i++) {
		if (m >= 3) {
			break;
		}
		if (((Player*)g_7f4ca0)[i].id != 0xffff && ((Player*)g_7f4ca0)[i].id != *(unsigned short*) e &&
		    ((Player*)g_7f4ca0)[i].x168 == *(unsigned char*) (e + 0x168)) {
			pl[m] = &((Player*)g_7f4ca0)[i];
			m++;
		}
	}
	if (max == 0) {
		return m + n;
	}
	out->x34 = *(unsigned char*) (e + 0x168);
	for (k = 0; k < MIN(max, n); k++) {
		out[k].who = ids[k];
		out[k].x2c = 0;
		fcn_005ca560(&out[k]);
		out[k].x30 = fcn_005cf720(*(unsigned short*) e, *(unsigned short*) out[k].who, q, 0);
	}
	for (j = 0; j < m; j++) {
		if (k >= max) {
			break;
		}
		out[k].who = (char*) pl[j];
		out[k].x2c = 1;
		fcn_005ca560(&out[k]);
		out[k].x30 = fcn_005cf720(*(unsigned short*) e, *(unsigned short*) out[k].who, q, 0);
		k++;
	}
	return k;
}
