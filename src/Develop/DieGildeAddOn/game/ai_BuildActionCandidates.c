#include <stdlib.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/entity_candidate.h"
extern char gm_EntitySlotTable[];

typedef struct
{
	int x0;
	int id;
	unsigned char x8;
	char pad9[0xf];
} Rec18;
/* SIZE 0x18 */

extern int g_664418[];
extern int g_664440[];
extern int* g_664448;
extern int gm_EntityCandidateCount;
extern int gm_DifficultyLevel;

int __cdecl amt_GetRoleLevel(int c);
int __cdecl amt_GetRoleTemplate(int idx, Rec18* out);
int __cdecl amt_CollectOfficeSlotsByGroup(int group, int max, Rec18* out);
int __cdecl amt_CollectOfficeCandidates(int k, int max, char** out);
char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x004a3530 */
void __cdecl ai_BuildActionCandidates(char* subjectEnt)
{
	Rec18 out[6];
	Rec18 r;
	int arr[8];
	int x10;
	int cls;
	int grp;
	int cnt;
	int i;
	int j;
	int n;

	int flag;
	int divisor;
	int* pv;
	char* e;
	char* q;

	n = 0;
	gm_EntityCandidateCount = 0;
	memset(g_10082a0, 0, 0x180);
	if (0 == *(unsigned char*) (subjectEnt + 0x166)) {
		cnt = amt_CollectOfficeSlotsByGroup(1, 6, out);
		for (i = 0; i < cnt; i++) {
			if (amt_GetRoleLevel(out[i].x8) >= 3)
				continue;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == subjectEnt)
				continue;
			g_10082a0[n].flags = 0x40;
			g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
			g_10082a0[n].entity = e;
			n++;
		}
		cnt = amt_CollectOfficeSlotsByGroup(2, 6, out);
		for (i = 0; i < cnt; i++) {
			if (amt_GetRoleLevel(out[i].x8) >= 3)
				continue;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == subjectEnt)
				continue;
			g_10082a0[n].flags = 0x40;
			g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
			g_10082a0[n].entity = e;
			n++;
		}
		cnt = amt_CollectOfficeSlotsByGroup(3, 6, out);
		for (i = 0; i < cnt; i++) {
			if (amt_GetRoleLevel(out[i].x8) >= 3)
				continue;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == subjectEnt)
				continue;
			g_10082a0[n].flags = 0x40;
			g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
			g_10082a0[n].entity = e;
			n++;
		}
	}
	else {
		grp = 0;
		flag = 0;
		arr[0] = 0;
		arr[1] = 0;
		arr[2] = 0;
		arr[3] = 0;
		arr[4] = 0;
		cls = amt_GetRoleLevel(*(unsigned char*) (subjectEnt + 0x166));
		amt_GetRoleTemplate(*(unsigned char*) (subjectEnt + 0x166), &r);
		x10 = r.id;
		if (x10 > 0 && x10 < 4) {
			grp = 3;
			if (x10 != 1) {
				flag = 1;
				if (x10 != 2)
					grp = 2;
			}
			else
				flag = 2;
			if (cls == 3) {
				arr[0] = 4;
				arr[1] = 5;
			}
		}
		else if (x10 > 3 && x10 < 6) {
			flag = (x10 == 4) + 4;
			if (cls == 6)
				arr[0] = 6;
			else if (cls == 4) {
				arr[2] = 1;
				arr[3] = 2;
				arr[4] = 3;
			}
		}
		else if (cls == 7) {
			arr[2] = 4;
			arr[3] = 5;
		}
		cnt = amt_CollectOfficeSlotsByGroup(x10, 6, out);
		for (i = 0; i < cnt; i++) {
			if (n >= 32)
				break;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == subjectEnt)
				continue;
			g_10082a0[n].flags = 0x10;
			g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
			g_10082a0[n].entity = e;
			n++;
		}
		cnt = amt_CollectOfficeSlotsByGroup(flag, 6, out);
		for (i = 0; i < cnt; i++) {
			if (n >= 32)
				break;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == subjectEnt)
				continue;
			g_10082a0[n].flags = 1;
			g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
			g_10082a0[n].entity = e;
			n++;
		}
		cnt = amt_CollectOfficeSlotsByGroup(grp, 6, out);
		for (i = 0; i < cnt; i++) {
			if (n >= 32)
				break;
			e = gm_LookupEntityRecordById(out[i].id);
			if (!e || e == subjectEnt)
				continue;
			g_10082a0[n].flags = 1;
			g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
			g_10082a0[n].entity = e;
			n++;
		}
		if (cls == 3 || cls == 6) {
			cnt = amt_CollectOfficeSlotsByGroup(arr[0], 6, out);
			for (i = 0; i < cnt; i++) {
				if (n >= 32)
					break;
				if (abs(amt_GetRoleLevel(out[i].x8) - cls) > 1)
					continue;
				e = gm_LookupEntityRecordById(out[i].id);
				if (!e || e == subjectEnt)
					continue;
				g_10082a0[n].flags = 0x40;
				g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
				g_10082a0[n].entity = e;
				n++;
			}
			cnt = amt_CollectOfficeSlotsByGroup(arr[1], 6, out);
			for (i = 0; i < cnt; i++) {
				if (n >= 32)
					break;
				if (abs(amt_GetRoleLevel(out[i].x8) - cls) > 1)
					continue;
				e = gm_LookupEntityRecordById(out[i].id);
				if (!e || e == subjectEnt)
					continue;
				g_10082a0[n].flags = 0x40;
				g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
				g_10082a0[n].entity = e;
				n++;
			}
		}
		if (cls == 4 || cls == 7) {
			cnt = amt_CollectOfficeSlotsByGroup(arr[2], 6, out);
			for (i = 0; i < cnt; i++) {
				if (n >= 32)
					break;
				if (abs(amt_GetRoleLevel(out[i].x8) - cls) > 1)
					continue;
				e = gm_LookupEntityRecordById(out[i].id);
				if (!e || e == subjectEnt)
					continue;
				g_10082a0[n].flags = 0x80;
				g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
				g_10082a0[n].entity = e;
				n++;
			}
			cnt = amt_CollectOfficeSlotsByGroup(arr[3], 6, out);
			for (i = 0; i < cnt; i++) {
				if (n >= 32)
					break;
				if (abs(amt_GetRoleLevel(out[i].x8) - cls) > 1)
					continue;
				e = gm_LookupEntityRecordById(out[i].id);
				if (!e || e == subjectEnt)
					continue;
				g_10082a0[n].flags = 0x80;
				g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
				g_10082a0[n].entity = e;
				n++;
			}
			cnt = amt_CollectOfficeSlotsByGroup(arr[4], 6, out);
			for (i = 0; i < cnt; i++) {
				if (n >= 32)
					break;
				if (abs(amt_GetRoleLevel(out[i].x8) - cls) > 1)
					continue;
				e = gm_LookupEntityRecordById(out[i].id);
				if (!e || e == subjectEnt)
					continue;
				g_10082a0[n].flags = 0x80;
				g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
				g_10082a0[n].entity = e;
				n++;
			}
		}
	}
	if (*(unsigned char*) (subjectEnt + 0x168)) {
		cnt = amt_CollectOfficeCandidates(*(unsigned char*) (subjectEnt + 0x168), 6, (char**) &arr[2]);
		for (i = 0; i < cnt; i++) {
			e = (char*) arr[2 + i];
			if (e == subjectEnt)
				continue;
			
			for (j = 0; j < n; j++) {
				if (g_10082a0[j].entity == e) {
					g_10082a0[j].flags |= 2;
					
					break;
				}
			}
			if (j < n)
				continue;
			if (n >= 32)
				continue;
			g_10082a0[n].flags = 2;
			g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) e, *(unsigned short*) subjectEnt, 1);
			g_10082a0[n].entity = e;
			n++;
		}
	}
	if (*(unsigned char*) (subjectEnt + 0x168) || *(unsigned char*) (subjectEnt + 2) == 5) {
		for (q = gm_EntitySlotTable; (int) q < (int) (gm_EntitySlotTable + 0x65400); q += 0x21c) {
			if (q == subjectEnt)
				continue;
			if (*(unsigned short*) q == 0xffff)
				continue;
			flag = 0;
			if ((*(unsigned char*) (q + 2) == 6 || *(unsigned char*) (q + 2) == 7
			     || *(unsigned char*) (q + 2) == 5) && *(unsigned char*) (subjectEnt + 2) == 5)
				flag |= 1;
			if (*(unsigned char*) (q + 0x168) == *(unsigned char*) (subjectEnt + 0x168))
				flag |= 4;
			if (!flag)
				continue;
			
			for (j = 0; j < n; j++) {
				if (g_10082a0[j].entity == q) {
					g_10082a0[j].flags |= flag;
					
					break;
				}
			}
			if (j < n)
				continue;
			if (n >= 32)
				continue;
			g_10082a0[n].flags = flag;
			g_10082a0[n].score = gm_CalcEntityFavor(*(unsigned short*) q, *(unsigned short*) subjectEnt, 1);
			g_10082a0[n].entity = q;
			n++;
		}
	}
	flag = (4 - gm_DifficultyLevel) * 5;
	for (i = 0; i < n; i++) {
		if (*(unsigned char*) (g_10082a0[i].entity + 2) == 6
		    || *(unsigned char*) (g_10082a0[i].entity + 2) == 7)
			g_10082a0[i].score += (float) flag;
	}
	gm_EntityCandidateCount = n;
	if (n > 3) {
		divisor = 0xb;
		pv = g_664440;
		while (divisor) {
			if (*pv < n)
				break;
			divisor--;
			pv--;
		}
		g_664448[0] = (int) &g_10082a0[gm_RandomMod(n) & 0xffff];
		g_664448[1] = g_664418[gm_RandomMod(divisor) & 0xffff];
		if (g_664448[1] > 1) {
			if (gm_EntityCandidateCount % g_664448[1] == 0) {
				i = ((unsigned short) gm_RandomMod(2) != 0) ? 1 : -1;
				g_664448[1] += i;
				return;
			}
			return;
		}
		return;
	}
	g_664448[0] = (int) &g_10082a0[0];
	g_664448[1] = 1;
	return;
}
