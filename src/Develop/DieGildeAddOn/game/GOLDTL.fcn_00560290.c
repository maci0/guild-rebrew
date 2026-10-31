#include <math.h>
#include <string.h>

extern char* g_entity_type_table;
extern int g_7f4c00;
extern int g_7f4c04;
extern unsigned char g_773d75;

int __cdecl fcn_00500e20(int*);
void __cdecl fcn_00500bb0(int, int, int, int);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_00455350(int, int, float*);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
int __cdecl fcn_00529670(int, int);
void __cdecl fcn_00529160(int, int, int, int);
int __cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_0050c710(unsigned char*, int, int);
int __cdecl gm_RandomMod(int);
int __cdecl gm_eval_SlotVoll(char*, int, int);
char* __cdecl fcn_0050dc90(unsigned char*);
int __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00546190(char*);

/* One step of the building placement state machine: validate the current
 * cell, pick the nearest matching entity or neighbour, place the icon and
 * advance the state. */
/* ADDRESS: GOLDTL 0x00560290 */
void __cdecl fcn_00560290(char* a0)
{
	char text[1024];
	char name[512];
	float here[3];
	float nextp[3];
	float best;
	float dist;
	double scale;
	int win;
	int value;
	int state;
	int sel;
	int rec;
	int row;
	int i;
	int t;
	int found;
	char* e;
	char* q;
	unsigned char* v9;
	unsigned short* id;

	win = fcn_00500e20(&g_7f4c00);
	value = g_7f4c04 & 0xffff;
	sel = 0;
	if (((*(float*) (win * 4 + 0x696550) <= (float) value) || ((float) value < *(float*) (win * 4 + 0x696540))) && (*(int*) (a0 + 0x70) != -1) && (*(int*) (a0 + 0x70) != -2)) {
		fcn_00500bb0((int) (a0 + 0x52), 0, 5, 0);
		return;
	}
	if (*(short*) (a0 + 8) != -1 && *(int*) (a0 + 0xc) != -1) {
		state = *(int*) (a0 + 0x70);
		switch (state) {
		case 1:
			e = (char*) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10));
			if (!e) {
				break;
			}
			best = 1.0e8f;
			fcn_00455350(*(int*) (e + 0x61), *(int*) (e + 0x61) + 0x4c, here);
			e = (char*) gm_StartFilteredEntitySearch(1, 5, 0xb);
			if (!e) {
				break;
			}
			do {
				fcn_00455350(*(int*) (e + 0x61), *(int*) (e + 0x61) + 0x4c, nextp);
				dist = (float) sqrt((nextp[0] - here[0]) * (nextp[0] - here[0]) + (nextp[1] - here[1]) * (nextp[1] - here[1]) + (nextp[2] - here[2]) * (nextp[2] - here[2]));
				if (dist < best) {
					sel = (int) e;
					best = dist;
				}
				e = (char*) gm_FindNextFilteredEntity();
			} while (e);
			if (sel) {
				rec = 0;
				*(unsigned int*) (a0 + 0xb4) = *(unsigned int*) (sel + 1);
				if (*(char*) (a0 + 0xac)) {
					i = 0;
					e = a0 + 0x8c;
					do {
						id = (unsigned short*) gm_LookupEntityRecordById(*(int*) e);
						if (id) {
							fcn_004c5c80(*(int*) e);
							fcn_004c5da0(*(int*) e, *(unsigned int*) (sel + 1), -1, 0, 0, (char*) 0x6a6508);
						}
						i++;
						e += 4;
					} while (i < (int) (unsigned char) *(a0 + 0xac));
				}
				*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
				return;
			}
			*(unsigned int*) (a0 + 0x70) = 0xffffffff;
			return;
		case 2:
			sel = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0xb4));
			if (!sel) {
				*(unsigned int*) (a0 + 0x70) = 0xffffffff;
				return;
			}
			i = 0;
			if (*(char*) (a0 + 0xac)) {
				e = a0 + 0x8c;
				do {
					rec = gm_LookupEntityRecordById(*(int*) e);
					if (rec && !fcn_00529670(rec, sel)) {
						*(unsigned int*) (a0 + 0x70) = 2;
						fcn_00500bb0((int) (a0 + 0x52), 0, 5, 0);
						return;
					}
					i++;
					e += 4;
				} while (i < (int) (unsigned char) *(a0 + 0xac));
			}
			*(unsigned int*) (a0 + 0x70) = 3;
			fcn_00500bb0((int) (a0 + 0x52), 0, 10, 0);
			return;
		case 3:
			found = 0;
			sel = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10));
			if (!sel) {
				*(unsigned int*) (a0 + 0x70) = 0xffffffff;
				return;
			}
			i = 0;
			if (*(char*) (a0 + 0xac)) {
				e = a0 + 0x8c;
				do {
					id = (unsigned short*) gm_LookupEntityRecordById(*(int*) e);
					if (id) {
						found = 1;
						fcn_004c5c80(*(int*) e);
						fcn_004c5da0(*(int*) e, *(unsigned int*) (sel + 1), *(unsigned int*) (a0 + 0xb0), 0, 0, (char*) 0x6a6508);
					}
					i++;
					e += 4;
				} while (i < (int) (unsigned char) *(a0 + 0xac));
				if (found) {
					*(unsigned int*) (a0 + 0x70) = 4;
					fcn_00500bb0((int) (a0 + 0x52), 0, 5, 0);
					return;
				}
			}
			break;
		case 4:
			v9 = (unsigned char*) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10));
			if (!v9) {
				break;
			}
			i = 0;
			if (*(char*) (a0 + 0xac)) {
				e = a0 + 0x8c;
				do {
					rec = gm_LookupEntityRecordById(*(int*) e);
					if (rec && !fcn_00529670(rec, (int) v9)) {
						*(unsigned int*) (a0 + 0x70) = 4;
						fcn_00500bb0((int) (a0 + 0x52), 0, 5, 0);
						return;
					}
					i++;
					e += 4;
				} while (i < (int) (unsigned char) *(a0 + 0xac));
			}
			i = 0;
			if (*(char*) (a0 + 0xac)) {
				e = a0 + 0x8c;
				do {
					id = (unsigned short*) gm_LookupEntityRecordById(*(int*) e);
					if (id) {
						fcn_00529160(0, 0, *id, 0);
					}
					i++;
					e += 4;
				} while (i < (int) (unsigned char) *(a0 + 0xac));
			}
			q = (char*) fcn_00502cd0(*(int*) (v9 + 0x5d), 2, 6, 0, 0x2a);
			if (!q) {
				break;
			}
			win = fcn_00500e20(&g_7f4c00);
			if (*(char*) (g_entity_type_table + (unsigned int) *v9 * 0x24d) != 0x20) {
				scale = (double) fcn_0050c710(v9, 0xb, 1) * *(double*) 0x665eb0 + *(double*) 0x6629c8;
			} else {
				scale = (double) fcn_0050c710(v9, 0x1e, 1) * *(double*) 0x665eb0 + *(double*) 0x6629c8;
			}
			t = gm_RandomMod(6) & 0xffff;
			t = (int) ((double) (t + 9) * (double) (unsigned char) *(a0 + 0xac) * scale);
			if (win == 3 && !(*(v9 + 0x5b) & 0x20)) {
				t = (int) ((double) t * *(double*) 0x662908);
			}
			rec = gm_eval_SlotVoll(q, *(unsigned short*) (a0 + 0xae), t);
			if (!*(unsigned short*) (a0 + 0xae)) {
				break;
			}
			id = (unsigned short*) fcn_0050dc90(v9);
			if (rec) {
				fcn_004c51f0(*(int*) (q + 2), -1, *(unsigned short*) (a0 + 0xae), rec, g_773d75, 0);
				io_FormatTextBuffer(text, 0x1802, 0x17fd, v9);
				io_FormatTextBuffer(name, 0x1803, rec, (unsigned int) *(unsigned short*) (a0 + 0xae) * 2 + 0x9a8);
				strcat(text, name);
			} else {
				io_FormatTextBuffer(text, 0x1804, 0x17fd, v9);
			}
			if ((*(char*) (*(unsigned short*) (a0 + 8) * 0x21c + 0x7f4ca2) == 6 || *(char*) (*(unsigned short*) (a0 + 8) * 0x21c + 0x7f4ca2) == 7) && (!id || !(*(unsigned char*) ((int) id + 0x1b4) & 1))) {
				he_MessageBoxQuickjump(*(int*) (*(unsigned short*) (a0 + 8) * 0x21c + 0x7f4ca4), -1, text, 0, 0x5ec, *(int*) (v9 + 1), *(int*) (a0 + 0xb0), 0, 0);
				fcn_00546190(a0);
				return;
			}
			break;
		case 0xfffffffe:
		case 0xffffffff:
			sel = (int) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (a0 + 0x10));
			if (sel && *(char*) (a0 + 0xac)) {
				i = 0;
				e = a0 + 0x8c;
				do {
					id = (unsigned short*) gm_LookupEntityRecordById(*(int*) e);
					if (id) {
						fcn_004c5c80(*(int*) e);
						fcn_004c5da0(*(int*) e, *(unsigned int*) (sel + 1), *(unsigned int*) (a0 + 0xb0), 0, 0, (char*) 0x6a6508);
					}
					i++;
					e += 4;
				} while (i < (int) (unsigned char) *(a0 + 0xac));
			}
			break;
		}
	}
	fcn_00546190(a0);
}
