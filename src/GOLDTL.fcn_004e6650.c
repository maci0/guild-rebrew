#include "Develop/DieGildeAddOn/game/event_callbacks.h"


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
	EVENT_CHECK fn;
	char pad4[0x10];
} Kind;
// SIZE 0x14

extern char g_9a9660[];
extern char g_7f4ca4[];
extern unsigned short g_774970;
extern int g_77494c;
extern unsigned char g_7747b0;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_7e2700;

void __cdecl fcn_00500bb0(Time *, int, int, int);
int __cdecl fcn_00500cb0(Time *, Time *);
void __cdecl fcn_004c6a70(int);
void __cdecl fcn_004e6b10(int);

/* ADDRESS: GOLDTL 0x004e6650 */
/* ADDRESS: GOLD 0x004e4cc0 */
int __cdecl fcn_004e6650(void)
{
	Time t;
	int i;
	int r;

	for (i = 0; i < 96; i++) {
		if (((Ent*)g_9a9660)[i].active != 0 && (((Ent*)g_9a9660)[i].flags & 5) == 0) {
			t = ((Ent*)g_9a9660)[i].t;
			fcn_00500bb0(&t, 0, -60, 0);
			if (((Ent*)g_9a9660)[i].key == -1 && ((g_77494c & 8) != 0 || ((*(int*)&g_7747b0) & 8) != 0)) {
				((Ent*)g_9a9660)[i].key = *(int *) (g_7f4ca4 + g_774970 * 0x21c);
			}
			if (*(int *) (g_7f4ca4 + g_774970 * 0x21c) == ((Ent*)g_9a9660)[i].key && ((Ent*)g_9a9660)[i].busy == 0 &&
			    fcn_00500cb0(&(*(Time*)&g_7f4c00), &t) > 0) {
				r = cut_CutsceneReady((int*) &((Ent*)g_9a9660)[i]);
				if (r == -1) {
					fcn_00500bb0(&((Ent*)g_9a9660)[i].t, 0, 5, 0);
					if (((Ent*)g_9a9660)[i].t.hour >= 22) {
						fcn_00500bb0(&((Ent*)g_9a9660)[i].t, 9, 0, 0);
					}
					continue;
				}
				if (r == 0) {
					fcn_00500bb0(&((Ent*)g_9a9660)[i].t, 0, 30, 0);
					if (((Ent*)g_9a9660)[i].t.hour >= 22) {
						fcn_00500bb0(&((Ent*)g_9a9660)[i].t, 9, 0, 0);
					}
					continue;
				}
				if (((Kind*) (g_9b0840 + 0x10))[((Ent*)g_9a9660)[i].type].fn != 0 && ((Kind*) (g_9b0840 + 0x10))[((Ent*)g_9a9660)[i].type].fn((char*) &((Ent*)g_9a9660)[i]) == 0) {
					fcn_004c6a70(((Ent*)g_9a9660)[i].id);
					continue;
				}
			}
			if (((Kind*) (g_9b0840 + 0x10))[((Ent*)g_9a9660)[i].type].fn == 0 && fcn_00500cb0(&(*(Time*)&g_7f4c00), &((Ent*)g_9a9660)[i].t) > 0) {
				((Ent*)g_9a9660)[i].done = 1;
			}
			if (fcn_00500cb0(&(*(Time*)&g_7f4c00), &((Ent*)g_9a9660)[i].t) > 0 && ((Ent*)g_9a9660)[i].done == 0) {
				if (fcn_004e6200(*(int *) (g_7f4ca4 + g_774970 * 0x21c), (unsigned char*) &((Ent*)g_9a9660)[i]) != 0 &&
				    (((Ent*)g_9a9660)[i].flags & 0x80) != 0) {
					if (*(int *) (g_7f4ca4 + g_774970 * 0x21c + 0x208) == ((Ent*)g_9a9660)[i].id) {
						((Ent*)g_9a9660)[i].done = 1;
					}
				} else if (((Ent*)g_9a9660)[i].key == *(int *) (g_7f4ca4 + g_774970 * 0x21c) &&
					   (((Ent*)g_9a9660)[i].flags & 2) != 0) {
					((Ent*)g_9a9660)[i].done = 1;
				} else {
					fcn_004e6b10(((Ent*)g_9a9660)[i].id);
				}
			}
			if (fcn_00500cb0(&(*(Time*)&g_7f4c00), &t) > 0 && ((Ent*)g_9a9660)[i].done != 0) {
				g_7e2700 = 0;
				fcn_004e5a00((int*) &((Ent*)g_9a9660)[i]);
				fcn_004e6b10(((Ent*)g_9a9660)[i].id);
			}
		}
	}
	return 0;
}
