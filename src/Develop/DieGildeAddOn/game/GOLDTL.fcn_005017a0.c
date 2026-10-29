#include "client_packet_builder.h"

extern char g_85ab90[];
extern char* g_773d78;
extern unsigned char g_773d75;
extern char* g_entity_type_table;
extern char* g_item_def_table;

/* SIZE 0x80 */
typedef struct {
	unsigned short id;
	char pad2[2];
	int active;
	char pad8[0x28 - 8];
	unsigned char value;
	char pad29[0x3c - 0x29];
	unsigned short target;
	char pad3e[0x80 - 0x3e];
} Slot;

unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl fcn_00503e50(int);
char* __cdecl fcn_00502cd0(int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
void __cdecl fcn_004c44a0(void);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_004c4670(int, int, int, void*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c51f0(int, int, int, int, char, int);
void __cdecl fcn_004c6190(char*, char);
int __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_00535960(void);

/* ADDRESS: GOLDTL 0x005017a0 */
void __cdecl fcn_005017a0(int a0)
{
	Slot rec;
	Slot* p;
	Slot* s;
	Slot* q;
	char* ent;
	char* ent2;
	char* o;
	unsigned char* e;
	unsigned short* item;
	unsigned short* item2;
	unsigned short id;
	int* ip;
	int v;
	int n;
	int i;
	int count;
	int codes[8] = { 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x2db, 0 };

	g_773d78 = (char*) gm_StartFilteredEntitySearch(1, 5, 10);
	if (g_773d78 == 0) {
		return;
	}
	s = (Slot*) (g_85ab90 + a0 * 0x2a90);
	if (a0 == g_773d75) {
		p = s;
		for (n = 0x55; n != 0; n--) {
			p->active = 0;
			p = (Slot*) ((char*) p + 0x80);
		}
		e = (unsigned char*) gm_StartFilteredEntitySearch(1, 6);
		while (e != 0) {
			if (*(char*) (g_entity_type_table + *e + *e * 0x24c) != 0x0a) {
				ent = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0xff);
				i = 0;
				if (ent != 0) {
					for (p = s; i < 0x55; i++, p = (Slot*) ((char*) p + 0x80)) {
						if (p->id != 0 &&
						    fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, p->id) != 0) {
							p->active = 1;
							item = (unsigned short*) (g_item_def_table + p->id * 0x41 + 0x2e);
							for (q = s, n = 0x55; n != 0; n--) {
								for (v = 4, item2 = item; v != 0; v--) {
									if (q->id == *item2) {
										q->active = 1;
									}
									item2++;
								}
								q = (Slot*) ((char*) q + 0x80);
							}
						}
					}
				}
			}
			e = (unsigned char*) gm_FindNextFilteredEntity();
		}
		p = s;
		for (n = 0x55; n != 0; n--) {
			rec = *s;
			id = p->target;
			ent = fcn_00502cd0(*(int*) (g_773d78 + 0x5d), 1, 0, id);
			if (ent != 0) {
				ent2 = fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, 0xff);
				if (ent2 == 0) {
					v = fcn_004c51f0(*(int*) (ent + 2), -1, 0xff, 1, (char) g_773d75, 0);
					while (fcn_004c4450(v) == 0) {
						fcn_00535960();
					}
					ent2 = fcn_004c4480(v);
				}
				if (p->active != 0) {
					if (fcn_00502cd0(*(int*) (ent2 + 0x14), 1, 0, p->id) == 0) {
						v = fcn_004c51f0(*(int*) (ent2 + 2), -1, p->id, 1, (char) g_773d75, 0);
						while (fcn_004c4450(v) == 0) {
							fcn_00535960();
						}
					}
				} else {
					o = fcn_00502cd0(*(int*) (ent2 + 0x14), 1, 0, p->id);
					if (o != 0) {
						v = fcn_004c51f0(-1, *(int*) (ent2 + 2), p->id,
								 *(int*) (o + 0xe), (char) g_773d75, 0);
						while (fcn_004c4450(v) == 0) {
							fcn_00535960();
						}
					}
				}
				fcn_004c6190((char*) &rec, (char) a0);
			}
			s = (Slot*) ((char*) s + 0x80);
			p = (Slot*) ((char*) p + 0x80);
		}
		ip = codes;
		for (v = *ip; v != 0; v = *++ip) {
			ent = fcn_00502cd0(*(int*) (g_773d78 + 0x5d), 1, 0, v);
			if (ent != 0) {
				ent2 = fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, 0xff);
				if (ent2 != 0) {
					count = 0;
					o = fcn_00502cd0(*(int*) (ent2 + 0x14), 1, 5);
					while (o != 0) {
						count++;
						o = (char*) gm_NextEntityQueryMatch();
					}
					o = fcn_00502cd0(*(int*) (ent + 0x14), 1, 4, 0x11);
					if (o != 0 && count > (int) *(unsigned char*) (o + 0x1c)) {
						count -= *(unsigned char*) (o + 0x1c);
						fcn_004c4510(o, *(int*) (o + 2));
						fcn_004c4670(1, 1, o - g_aed32c + 0x1c, &count);
						fcn_004c5360();
					}
				}
			}
		}
	} else {
		e = (unsigned char*) fcn_00503e50(a0);
		if (e == 0) {
			return;
		}
		ent = fcn_00502cd0(*(int*) (e + 0x5d), 2, 0, 0x1db, 6);
		if (ent == 0) {
			return;
		}
		ent2 = fcn_00502cd0(*(int*) (e + 0x5d), 2, 0, 0x1dc, 6);
		if (ent2 == 0) {
			return;
		}
		fcn_004c44a0();
		p = s;
		for (n = 0x55; n != 0; n--) {
			rec = *p;
			if (rec.id != 0) {
				if (fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, rec.id) == 0 &&
				    fcn_00502cd0(*(int*) (ent2 + 0x14), 1, 0, rec.id) == 0) {
					rec.active = 0;
				} else {
					if (rec.value != 0) {
						rec.value += (unsigned char) gm_RandomMod(8) + 0x18;
						rec.active = rec.value <= 0x80;
					} else {
						rec.value = (unsigned char) gm_RandomMod(0xff);
						rec.active = rec.value <= 0x80;
					}
				}
				fcn_004c6190((char*) &rec, (char) a0);
			}
			p = (Slot*) ((char*) p + 0x80);
		}
		fcn_004c44b0();
		while (fcn_004c44c0() == 0) {
			fcn_00535960();
		}
	}
}
