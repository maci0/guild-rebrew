typedef struct
{
	int id;
	int f04;
	char* ent;
	char* obj;
	int f10;
	int f14;
	int f18;
	float f1c;
	float f20;
	int f24;
	int f28;
	int f2c;
	int f30;
	int f34;
	int f38;
	int f3c;
} fcn_00485970_EntA;
/* SIZE 0x40 */

typedef struct
{
	int id;
	int f04;
	int f08;
	int f0c;
	int f10;
	char* ent;
	char* obj;
	int f1c;
	int f20;
	int f24;
	int f28;
	int f2c;
	int f30;
	float f34;
	int f38;
	int f3c;
	int f40;
	int f44;
	int f48;
	int f4c;
	int f50;
	int f54;
} fcn_00485970_EntB;
/* SIZE 0x58 */

extern int g_100b0a8;
extern int g_100b0ac;
extern int g_662910;
extern int g_773d78;
extern signed char g_773d75;

char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl fcn_00502cd0(int container, int a, ...);
char* __cdecl gm_FindSlotById(int a, int b);
int __cdecl gm_GetBuildingTypeCategory(int a);
float __cdecl fcn_0050bb50(int id, unsigned char a);
float __cdecl fcn_0050b980(int id, int a);
int __cdecl fcn_0050dfa0(int a, int b);
int __cdecl gm_eval_SlotVoll(int a, int b, int c);
char* __cdecl fcn_00503d10(int id);
char* __cdecl fcn_005463a0(int a, int b, int c, int d, int e);
char* __cdecl fcn_005462a0(void);
char* __cdecl gm_FindRecordById(int id);
void __cdecl fcn_0050de80(int a, int* out);

/* ADDRESS: GOLDTL 0x00485970 */
int __cdecl fcn_00485970(char* a0, int a1, int a2)
{
	fcn_00485970_EntA* pa;
	fcn_00485970_EntB* pb;
	fcn_00485970_EntA ta;
	fcn_00485970_EntB tb;
	char* ent;
	char* cont;
	char* slot;
	char* q;
	char* obj;
	char* rec;
	char* recs2;
	int recs[18];
	short slots[16];
	int vals[20];
	int i;
	int j;
	int k;
	int id;
	int idx;
	int found;
	int t;
	float f0;
	float f1;
	float f2;
	float fa;
	float fb;

	pa = (fcn_00485970_EntA*) 0x100b0c0;
	pb = (fcn_00485970_EntB*) 0x100d0c0;
	g_100b0ac = 0;
	g_100b0a8 = 0;
	if (!a2) {
		ent = gm_StartFilteredEntitySearch(1, 0, 0x47);
		while (ent) {
			cont = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 0, 0x1db, 6);
			if (cont) {
				slot = fcn_00502cd0(*(int*) (cont + 0x14), 1, 5);
				while (slot) {
					id = *(unsigned short*) slot;
					obj = gm_FindSlotById(*(int*) (ent + 0x65), id);
					if (obj && *(int*) (obj + 4)) {
						f1 = fcn_0050bb50(id, (unsigned char) *(char*) (ent + 0x65));
						f0 = fcn_0050b980(id, 100) - f1;
						idx = 0;
						if (1 <= g_100b0a8) {
							while (idx < g_100b0a8) {
								if (pa[idx].id == id) {
									if (f0 < pa[idx].f20)
										goto label_485b77;
									break;
								}
								idx++;
							}
							if (0x80 <= idx)
								goto label_485b77;
						}
						pa[idx].f20 = f0;
						pa[idx].id = id;
						pa[idx].f04 = -1;
						pa[idx].ent = ent;
						pa[idx].obj = cont;
						pa[idx].f10 = 0;
						pa[idx].f14 = 0;
						pa[idx].f18 = 0;
						pa[idx].f1c = f1;
						pa[idx].f24 = 0;
						pa[idx].f28 = fcn_0050dfa0(a1, id);
						pa[idx].f2c = gm_eval_SlotVoll(a1, id, 1000000);
						pa[idx].f30 = 0x81;
						pa[idx].f34 = 0;
						pa[idx].f38 = fcn_0050dfa0((int) cont, id);
						pa[idx].f3c = 0x80;
						if (idx == g_100b0a8)
							g_100b0a8++;
						q = fcn_00502cd0(*(int*) (cont + 0x14), 1, 5);
						while (q && q != slot)
							q = gm_NextEntityQueryMatch();
					}
label_485b77:
					slot = gm_NextEntityQueryMatch();
				}
				cont = fcn_00502cd0(*(int*) (ent + 0x5d), 2, 0, 0x1db, 6);
				if (cont) {
					slot = fcn_00502cd0(*(int*) (cont + 0x14), 1, 5);
					while (slot) {
						id = *(unsigned short*) slot;
						obj = gm_FindSlotById(*(int*) (ent + 0x65), id);
						if (obj && *(int*) (obj + 4)) {
							f0 = fcn_0050b980(id, 100);
							f1 = fcn_0050bb50(id, (unsigned char) *(char*) (ent + 0x65)) - f0;
							idx = 0;
							if (1 <= g_100b0ac) {
								while (idx < g_100b0ac) {
									if (pb[idx].id == id) {
										if (f1 < pb[idx].f34)
											goto label_485d61;
										break;
									}
									idx++;
								}
							}
							if (g_100b0ac <= 0x1f) {
								pb[idx].id = id;
								pb[idx].f04 = -1;
								pb[idx].f08 = -1;
								pb[idx].f0c = -1;
								pb[idx].f10 = -1;
								pb[idx].ent = ent;
								pb[idx].obj = cont;
								pb[idx].f34 = f1;
								pb[idx].f1c = 0;
								pb[idx].f24 = 0;
								pb[idx].f28 = 0;
								pb[idx].f2c = 0;
								pb[idx].f38 = 0;
								pb[idx].f3c = fcn_0050dfa0(a1, id);
								pb[idx].f40 = gm_eval_SlotVoll(a1, id, 1000000);
								pb[idx].f44 = 0;
								pb[idx].f48 = 0x21;
								pb[idx].f4c = 0;
								pb[idx].f50 = gm_eval_SlotVoll((int) cont, id, 1000000);
								pb[idx].f54 = 0x100;
								if (idx == g_100b0ac)
									g_100b0ac++;
								q = fcn_00502cd0(*(int*) (cont + 0x14), 1, 5);
								while (q && q != slot)
									q = gm_NextEntityQueryMatch();
							}
						}
label_485d61:
						slot = gm_NextEntityQueryMatch();
					}
				}
			}
			ent = gm_FindNextFilteredEntity();
		}
	}
	for (i = 0; i < 0xa900; i += 0xa9) {
		rec = (char*) 0x90e094 + i;
		t = *(char*) rec;
		if (gm_GetBuildingTypeCategory(t) != 2)
			continue;
		cont = fcn_00502cd0(*(int*) (rec + 0x5d), 2, 0, 0x2a, 6);
		if (!cont)
			continue;
		slot = fcn_00502cd0(*(int*) (cont + 0x14), 1, 5);
		while (slot) {
			id = *(unsigned short*) slot;
			obj = gm_FindSlotById(g_773d75, id);
			if (obj && *(int*) (obj + 4)) {
				f1 = fcn_0050bb50(id, (unsigned char) g_773d75) * (float) *(int*) (rec + 0x45)
				    * (float) g_662910;
				f0 = fcn_0050b980(id, 100) - f1;
				idx = 0;
				if (1 <= g_100b0a8) {
					while (idx < g_100b0a8) {
						if (pa[idx].id == id) {
							if (f0 < pa[idx].f20)
								goto label_485f7e;
							break;
						}
						idx++;
					}
					if (0x80 <= idx)
						goto label_485f7e;
				}
				pa[idx].f20 = f0;
				pa[idx].ent = rec;
				pa[idx].id = id;
				pa[idx].f04 = -1;
				pa[idx].obj = cont;
				pa[idx].f10 = 0;
				pa[idx].f14 = 0;
				pa[idx].f18 = 0;
				pa[idx].f1c = f1;
				pa[idx].f24 = 0;
				pa[idx].f30 = 0x81;
				pa[idx].f3c = 0;
				pa[idx].f28 = fcn_0050dfa0(a1, id);
				pa[idx].f2c = gm_eval_SlotVoll(a1, id, 1000000);
				pa[idx].f34 = 0;
				pa[idx].f38 = fcn_0050dfa0((int) cont, id);
				if (idx == g_100b0a8)
					g_100b0a8++;
				q = fcn_00502cd0(*(int*) (cont + 0x14), 1, 5);
				while (q && q != slot)
					q = gm_NextEntityQueryMatch();
			}
label_485f7e:
			slot = gm_NextEntityQueryMatch();
		}
	}
	idx = 0;
	while (idx < g_100b0a8) {
		found = 0;
		for (i = 0; i < g_100b0ac; i++) {
			if (pa[idx].id == pb[i].id) {
				found = 1;
				break;
			}
		}
		if (!found) {
			obj = fcn_00503d10(pa[idx].id);
			if (obj) {
				f0 = fcn_0050b980(pa[idx].id, 100);
				if (g_100b0ac <= 0x1f) {
					i = g_100b0ac;
					pb[i].id = pa[idx].id;
					pb[i].f04 = -1;
					pb[i].f08 = -1;
					pb[i].f0c = -1;
					pb[i].f10 = -1;
					pb[i].ent = (char*) g_773d78;
					pb[i].obj = obj;
					pb[i].f44 = 0;
					pb[i].f24 = 0;
					pb[i].f34 = fcn_0050bb50(pa[idx].id, (unsigned char) g_773d75) - f0;
					pb[i].f38 = 0;
					pb[i].f48 = 0x21;
					pb[i].f54 = 0;
					pb[i].f3c = fcn_0050dfa0(a1, pa[idx].id);
					pb[i].f40 = gm_eval_SlotVoll(a1, pa[idx].id, 1000000);
					pb[i].f4c = 0;
					pb[i].f50 = gm_eval_SlotVoll((int) obj, pa[idx].id, 1000000);
					g_100b0ac++;
				}
			}
			else {
				*(int*) &pa[idx].f20 = (int) 0xc9742400u;
			}
		}
		idx++;
	}
	rec = fcn_005463a0(2, 0, 0xb, 3, *(int*) (*(char**) (a0 + 0x16c) + 1));
	while (rec) {
		recs2 = gm_FindRecordById(*(int*) (rec + 0xac));
		if (recs2) {
			fcn_0050de80((int) recs2, recs);
			for (i = 0; i < recs[0]; i++) {
				if (!slots[i])
					continue;
				found = 0;
				for (j = 0; j < 3; j++) {
					if (*(unsigned short*) (rec + 0xd0 + j * 2) == slots[i]) {
						found = 1;
						break;
					}
				}
				if (found)
					continue;
				for (j = 0; j < g_100b0ac; j++) {
					if (pb[j].id == (slots[i] & 0xffff))
						pb[j].f38 += vals[i];
				}
				for (j = 0; j < g_100b0a8; j++) {
					if (pa[j].id == (slots[i] & 0xffff))
						pa[j].f24 += vals[i];
				}
			}
			for (j = 0; j < 3; j++) {
				if (!*(unsigned short*) (rec + 0xd6 + j * 2))
					continue;
				id = *(unsigned short*) (rec + 0xd6 + j * 2);
				k = *(int*) (rec + 0xdc + j * 4);
				for (i = 0; i < g_100b0ac; i++) {
					if (pb[i].id == id)
						pb[i].f38 += k;
				}
				for (i = 0; i < g_100b0a8; i++) {
					if (pa[i].id == id)
						pa[i].f24 += k;
				}
			}
		}
		rec = fcn_005462a0();
	}
	for (i = 0; i < g_100b0a8; i++) {
		for (j = 0; j < g_100b0ac; j++) {
			if (pa[i].id != pb[j].id)
				continue;
			t = pa[i].f2c;
			if (pb[j].f50 < t)
				t = pb[j].f50;
			fa = (float) t;
			fb = (float) (*(int*) (a0 + 0x1b8) / 4) / pa[i].f1c;
			if (fa > fb)
				fa = fb;
			pa[i].f34 = (int) fa;
		}
	}
	for (i = 0; i < g_100b0ac; i++) {
		t = pb[i].f3c;
		if (pb[i].f50 < t)
			t = pb[i].f50;
		pb[i].f4c = t;
	}
	for (i = 0; i < g_100b0a8; i++) {
		for (j = i + 1; j < g_100b0a8; j++) {
			if ((float) pa[i].f34 * pa[i].f20 < (float) pa[j].f34 * pa[j].f20) {
				ta = pa[i];
				pa[i] = pa[j];
				pa[j] = ta;
			}
		}
	}
	for (i = 0; i < g_100b0ac; i++) {
		for (j = i + 1; j < g_100b0ac; j++) {
			if ((float) pb[i].f4c * pb[i].f34 < (float) pb[j].f4c * pb[j].f34) {
				tb = pb[i];
				pb[i] = pb[j];
				pb[j] = tb;
			}
		}
	}
	for (i = 0; i < g_100b0ac; i++)
		pb[i].f48 = i;
	for (i = 0; i < g_100b0a8; i++)
		pa[i].f30 = i;
	return 0;
}
