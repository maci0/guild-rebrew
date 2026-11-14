#include <stdio.h>
#include <string.h>

extern int g_6798d4;
extern unsigned char* lpGebaeudePROT;
extern int g_6b7fdc;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern int g_772514;

int __cdecl fcn_0042f690(char* a, int b, int c, char* out);
int __cdecl fcn_0050d200(int a, int b);
char* __cdecl _strupr(char* s);
void __cdecl fcn_005986f0(char* a, int b);
void __cdecl fcn_00598740(float* out, int obj);
void __cdecl fcn_004c5530(int a1);

extern int g_6b8010;
extern char* g_773da8;
extern int g_6798d4;    
extern char g_7e1ae0[]; 
extern char g_67f0ac[]; 
extern char g_68de2c[]; 

void __cdecl ReportClientMessage(const char*);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00455350(char*, char*, int*);
void __cdecl fcn_004c5530(int a1);
int __cdecl fcn_004e8240(unsigned char, char*, char*, int, int);
void __cdecl fcn_004ea4b0(void*, unsigned int);
void __cdecl fcn_004ea560(void*, unsigned int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl fcn_00597ff0(int, char*);
int __cdecl fcn_00598150(char*, int*);
void __cdecl fcn_00598740(float* out, int obj);
int __cdecl sprintf(char*, const char*, ...);
char* __cdecl strupr(char*);

/* Collects building candidates of the requested office type, narrows them to
 * the receiver range, then either upgrades the entity the office already
 * points at or picks the free building with the highest chain value. The
 * candidate records are handed to the guild request buffer at 0x80..0x98. */
/* ADDRESS: GOLDTL 0x004eab40 */
void __cdecl amt_calc_zuenfte(unsigned int kind)
{
	union {
		int office[6];
		float position[3];
	} info;
	unsigned int cand[16];
	char names[128];
	int ids[64];
	char path[128];
	char buf[128];
	unsigned char req[0xf8];
	char* t;
	char* rec;
	char* rowbase;
	char* best;
	char* existing;
	unsigned int found;
	int pass;
	int sel;
	int row;
	int min;
	int count;
	int max;
	int total;
	int i;
	int n;
	int value;
	float rotation[3];

	memset(info.office, 0, sizeof(info.office));
	info.office[1] = -1;
	if (kind == 0x1e) {
		pass = 0xe;
		sel = 0x17;
		min = 0x22;
		max = 0x27;
		row = 0x38;
	}
	else if (kind == 0x1f) {
		pass = 0x12;
		sel = 0x18;
		min = 0x2e;
		max = 0x33;
		row = 0x3b;
	}
	else if (kind == 0x20) {
		pass = 0x14;
		sel = 0x19;
		min = 0x3a;
		max = 0x3f;
		row = 0x3e;
	}
	else if (kind == 0x21) {
		pass = 0x15;
		sel = 0x1a;
		min = 0x40;
		max = 0x45;
		row = 0x41;
	}
	else {
		return;
	}
	memset(cand, 0, sizeof(cand));
	count = 0;
	total = 0;
	t = gm_StartFilteredEntitySearch(1, 5, pass);
	if (t != 0) {
		do {
			if (count >= 0x10) {
				break;
			}
			if (*(unsigned short*) (t + 0x27) != 0xffff &&
			    (t[0x5a] & 1) == 0) {
				total++;
				i = *(unsigned short*) (t + 0x27);
				rec = (char*) (0x7f4ca0 + i * 0x21c);
				n = *(unsigned char*) (rec + 0x164);
				if (n >= min && n <= max) {
					for (i = 0; i < 0x10; i++) {
						if (cand[i] == (unsigned int) rec) {
							break;
						}
					}
					if (i == 0x10) {
						cand[count] = (unsigned int) rec;
						count++;
					}
				}
			}
			t = gm_FindNextFilteredEntity();
		} while (t != 0);
		if (total >= 3 && count != 0) {
			t = gm_StartFilteredEntitySearch(1, 5, sel);
			if (t == 0) {
				found = (unsigned int) g_6b8010;
				fcn_004432d0(0, 1);
				rowbase = (char*) (lpGebaeudePROT + row * 0x24d);
				fcn_00597ff0(row, names);
				n = fcn_00598150(names, ids);
				rec = (char*) ids[gm_RandomMod(n) & 0xffff];
				i = 0;
				if (rec == 0) {
					do {
						if (i >= n) {
							break;
						}
						if (ids[i] != 0) {
							rec = (char*) ids[i];
						}
						i++;
					} while (rec == 0);
					if (rec == 0) {
						ReportClientMessage(g_68de2c);
						return;
					}
				}
				fcn_00455350(rec, (float*) (rec + 0x4c), info.position);
				fcn_00598740(rotation, (int) rec);
				fcn_004432d0((int) found, 1);
				cand[0] = (unsigned int) g_6798d4;
				strcat((char*) cand, rowbase + 1);
				strupr((char*) cand + 2);
				sprintf(buf, g_67f0ac, g_7e1ae0, (char*) cand);
				req[4] = 0xd;
				*(int*) (req + 0x08) = *(int*) (g_773da8 + 4);
				*(int*) (req + 0x0c) = -1;
				*(int*) (req + 0x28) = g_7f4c00;
				*(int*) (req + 0x2c) = g_7f4c04;
				*(int*) (req + 0x30) = g_7f4c08;
				*(unsigned short*) (req + 0x34) = g_7f4c0c;
				req[0x36] = 2;
				*(int*) (req + 0x58) = *(int*) (g_773da8 + 4);
				*(int*) (req + 0x5c) = row;
				*(int*) (req + 0x60) = 0;
				memcpy(req + 0x80, info.position, sizeof(info.position));
				memcpy(req + 0x90, rotation, sizeof(rotation));




				strcpy((char*) (req + 0x9c), buf);
				fcn_004c5530(req);
				return;
			}
			if ((t[0x5a] & 1) == 0) {
				/* re-read the office type entry from the table */
				n = 1;
				rec = (char*) 0x9a9580;
				do {
					if (n == 0) {
						break;
					}
					if ((unsigned char) rec[8] == kind) {
						n--;
						memcpy(info.office, rec, 0x18);
					}
					rec -= 0x18;
				} while ((int) rec >= 0x9a9220);
				existing = 0;
				value = 0;
				if (info.office[1] != -1 &&
				    (existing = gm_LookupEntityRecordById(info.office[1])) != 0) {
					value = gm_WalkEntityChain(*(unsigned short*) existing);
				}
				best = 0;
				for (i = 0; i < count; i++) {
					rec = (char*) cand[i];
					n = gm_WalkEntityChain(*(unsigned short*) rec);
					if (n > value) {
						best = rec;
						value = n;
					}
				}
				if (best != 0 && best != existing) {
					if (existing != 0) {
						fcn_004e8240((unsigned char) info.office[0], best, 0, 1, 0xff);
						fcn_004ea560(existing, kind);
						fcn_004ea4b0(best, kind);
						return;
					}
					fcn_004e8240((unsigned char) info.office[0], best, 0, 1, 0xff);
					fcn_004ea4b0(best, kind);
				}
			}
		}
	}
}
