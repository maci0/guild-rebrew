// FUNCTION: GOLDTL 0x004e6650
// SIZE: 630

#pragma pack(push, 2)
typedef struct {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time;
// SIZE 0xe
#pragma pack(pop)

typedef struct {
	int id;
	int done;
	unsigned char type;
	char pad9[3];
	int key;
	char pad10[8];
	Time t;
	unsigned char flags;
	char pad27;
	int busy;
	char pad2c[4];
	char active;
	char pad31[0xe3];
} Ent;
// SIZE 0x114

typedef struct {
	int (__cdecl *fn)(Ent *);
	char pad4[0x10];
} Kind;
// SIZE 0x14

extern Ent g_9a9660[96];
extern Kind g_9b0850[];
extern char g_7f4ca4[];
extern unsigned short g_774970;
extern int g_77494c;
extern int g_7747b0;
extern Time g_7f4c00;
extern int g_7e2700;

void __cdecl fcn_00500bb0(Time *, int, int, int);
int __cdecl fcn_00500cb0(Time *, Time *);
int __cdecl fcn_004e64e0(Ent *);
void __cdecl fcn_004c6a70(int);
int __cdecl fcn_004e6200(int, Ent *);
void __cdecl fcn_004e6b10(int);
void __cdecl fcn_004e5a00(Ent *);

int __cdecl fcn_004e6650(void)
{
	Time t;
	int i;
	int r;

	for (i = 0; i < 96; i++) {
		if (g_9a9660[i].active != 0 && (g_9a9660[i].flags & 5) == 0) {
			t = g_9a9660[i].t;
			fcn_00500bb0(&t, 0, -60, 0);
			if (g_9a9660[i].key == -1 && ((g_77494c & 8) != 0 || (g_7747b0 & 8) != 0)) {
				g_9a9660[i].key = *(int *) (g_7f4ca4 + g_774970 * 0x21c);
			}
			if (*(int *) (g_7f4ca4 + g_774970 * 0x21c) == g_9a9660[i].key && g_9a9660[i].busy == 0 &&
			    fcn_00500cb0(&g_7f4c00, &t) > 0) {
				r = fcn_004e64e0(&g_9a9660[i]);
				if (r == -1) {
					fcn_00500bb0(&g_9a9660[i].t, 0, 5, 0);
					if (g_9a9660[i].t.hour >= 22) {
						fcn_00500bb0(&g_9a9660[i].t, 9, 0, 0);
					}
					continue;
				}
				if (r == 0) {
					fcn_00500bb0(&g_9a9660[i].t, 0, 30, 0);
					if (g_9a9660[i].t.hour >= 22) {
						fcn_00500bb0(&g_9a9660[i].t, 9, 0, 0);
					}
					continue;
				}
				if (g_9b0850[g_9a9660[i].type].fn != 0 && g_9b0850[g_9a9660[i].type].fn(&g_9a9660[i]) == 0) {
					fcn_004c6a70(g_9a9660[i].id);
					continue;
				}
			}
			if (g_9b0850[g_9a9660[i].type].fn == 0 && fcn_00500cb0(&g_7f4c00, &g_9a9660[i].t) > 0) {
				g_9a9660[i].done = 1;
			}
			if (fcn_00500cb0(&g_7f4c00, &g_9a9660[i].t) > 0 && g_9a9660[i].done == 0) {
				if (fcn_004e6200(*(int *) (g_7f4ca4 + g_774970 * 0x21c), &g_9a9660[i]) != 0 &&
				    (g_9a9660[i].flags & 0x80) != 0) {
					if (*(int *) (g_7f4ca4 + g_774970 * 0x21c + 0x208) == g_9a9660[i].id) {
						g_9a9660[i].done = 1;
					}
				} else if (g_9a9660[i].key == *(int *) (g_7f4ca4 + g_774970 * 0x21c) &&
					   (g_9a9660[i].flags & 2) != 0) {
					g_9a9660[i].done = 1;
				} else {
					fcn_004e6b10(g_9a9660[i].id);
				}
			}
			if (fcn_00500cb0(&g_7f4c00, &t) > 0 && g_9a9660[i].done != 0) {
				g_7e2700 = 0;
				fcn_004e5a00(&g_9a9660[i]);
				fcn_004e6b10(g_9a9660[i].id);
			}
		}
	}
	return 0;
}
