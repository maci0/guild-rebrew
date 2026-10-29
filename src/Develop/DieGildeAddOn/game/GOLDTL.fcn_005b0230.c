extern char* g_1043370;
extern char* g_1015ea0;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl fcn_00455350(char*, float*, float*);
int __cdecl fcn_0045b990(float*, float*, int*, int*, float*);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_005b00f0(char*, int, int);
void __cdecl fcn_005b00d0(int, int);
void __cdecl fcn_00469c40(int, int, int);
int __cdecl fcn_005cfd00(unsigned short*, int*, unsigned char*);
char* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_0046c310(int);

typedef struct ScrollSlot {
	int handle;	/* 0x00 */
	char* ent;	/* 0x04 */
	int x;		/* 0x08 */
	int y;		/* 0x0c */
	float fx;	/* 0x10 */
	float fy;	/* 0x14 */
} ScrollSlot;

#define g_town_flags(t) (((unsigned char*) (t))[4])
#define g_town_dir(t) (*(int*) ((t) + 8))
#define g_town_count(t) (*(int*) ((t) + 0x27a4))
#define g_cur_dir (*(int*) 0x772514)
#define g_cur_building (*(int*) 0x77255c)
#define g_entity_type(t) ((unsigned char*) (0x7f4ca0 + (t) * 0x21c))

/* ADDRESS: GOLDTL 0x005b0230 */
void __cdecl fcn_005b0230(char* town)
{
	ScrollSlot* slot;
	ScrollSlot tmp;
	unsigned char* ent;
	unsigned char* list;
	unsigned char* next;
	char* obj;
	char* p;
	int* tab;
	char scratch[0x18];
	int offs[16] = { 0, -1, 1, 0, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1 };
	int tex;
	int base_x;
	int base_y;
	int bld_x;
	int bld_y;
	int dir;
	int mode;
	int handle;
	int count;
	int i;
	int j;
	int kind;
	float pos[4];
	float height;

	tex = *(int*) 0x1043370;
	base_x = *(int*) (*(unsigned char*) 0x773d75 * 0x2f4 + 0x86834c);
	base_y = *(int*) (*(unsigned char*) 0x773d75 * 0x2f4 + 0x868350);

	slot = (ScrollSlot*) (town + 0xdc);
	for (i = 0x100; i != 0; i--) {
		slot->handle = -1;
		slot->ent = 0;
		slot++;
	}
	for (i = 0; i < 0x80; i++) {
		*(int*) (town + 0x24dc + i * 4) = -1;
	}
	for (i = 0; i < 0x300; i++) {
		*(int*) (town + 0x18dc + i * 4) = -1;
	}
	count = 0;
	g_town_count(town) = 0;

	p = (char*) gm_StartFilteredEntitySearch(2, 5, 9, 4, *(unsigned short*) 0x774970);
	ent = gm_StartFilteredEntitySearch(1, 6);
	slot = (ScrollSlot*) (town + 0xdc);
	if (ent != 0) {
		do {
			if (count >= 0x100) {
				break;
			}
			if (*ent != 'D' && *ent != 'E' && !(ent[0x5a] & 1)
			    && (*ent != 'G' || p != 0)) {
				slot->ent = (char*) ent;
				count++;
				slot++;
			}
			ent = gm_FindNextFilteredEntity();
			g_town_count(town) = count;
		} while (ent != 0);
	}

	dir = g_town_dir(town);
	g_cur_dir = dir;
	i = 0;
	slot = (ScrollSlot*) (town + 0xdc);
	if (count >= 1) {
		do {
			obj = slot->ent;
			handle = *(int*) (obj + 0x61);
			if (handle != 0) {
				fcn_00455350((char*) handle, (float*) (handle + 0x4c), pos);
				fcn_0045b990((float*) tex, pos, &bld_x, &bld_y, &height);
				slot->x = bld_x;
				slot->y = bld_y;
				fcn_005b00f0((char*) slot, base_x, base_y);
			} else {
				g_cur_dir = dir;
				g_cur_building = dir * 0x3cc + 0x1015f40;
				bld_x = (int) ((float) *(int*) (tex + 0x20)
				               * (float) offs[2 * (unsigned char) obj[0x34]] * 5.33f
				               * ((*obj == 'G') ? 0.48f : 0.435f)
				               + (float) *(int*) (tex + 0x20) * 5.33f * 0.5f);
				bld_y = (int) ((float) *(int*) (tex + 0x20)
				               * (float) offs[2 * (unsigned char) obj[0x34] + 1] * 5.33f
				               * ((*obj == 'G') ? 0.48f : 0.435f)
				               + (float) *(int*) (tex + 0x20) * 5.33f * 0.5f);
				handle = fcn_0046f740(bld_x, bld_y, *obj + 0x47f, dir);
				slot->handle = handle;
				*(int*) (g_1015ea0 + 0x5c + handle * 0x2f4) = 1;
				*(int*) (g_1015ea0 + 0x1d0 + handle * 0x2f4) = 0x43;
				*(int*) (g_1015ea0 + 0x1cc + handle * 0x2f4) = 0x56;
				slot->x = bld_x - *(int*) (g_1015ea0 + 0x18 + handle * 0x2f4) / 2;
				slot->y = bld_y - *(int*) (g_1015ea0 + 0x1c + handle * 0x2f4) / 2;
				fcn_00469c40(*(int*) (g_cur_building + 4) + bld_x,
				             *(int*) (g_cur_building + 8) + bld_y, handle);
				if (*obj != 'G') {
					fcn_005b00d0((int) obj,
					             (int) (g_1015ea0 + 0xcc + handle * 0x2f4));
				} else {
					p = (char*) (*(int*) (obj + 0x65) * 0x2f4 + 0x868060);
					next = (unsigned char*) (g_1015ea0 + 0xcc + handle * 0x2f4);
					do {
						*next = *p;
						p++;
						next++;
					} while (*next != 0);
				}
				kind = *(unsigned short*) (obj + 0x27);
				if (kind != 0xffff) {
					j = *(unsigned char*) (0x7f4ca2 + kind * 0x21c);
					if (j == 5 || j == 6 || j == 7) {
						fcn_0046f740(bld_x - 8, bld_y - 8,
						             *(int*) (0x7f4cf4 + kind * 0x21c),
						             g_cur_dir);
					}
				}
			}
			i++;
			slot++;
		} while (i < g_town_count(town));
	}

	count = g_town_count(town);
	if (count != 1 && count - 1 >= 0) {
		for (i = 1; i < count; i++) {
			slot = (ScrollSlot*) (town + 0xe8);
			for (j = i; j < count; j++) {
				if (slot[1].y < slot[0].y) {
					tmp = slot[0];
					slot[0] = slot[1];
					slot[1] = tmp;
				}
				slot++;
			}
		}
	}

	dir = g_town_dir(town);
	g_cur_dir = dir;
	g_cur_building = dir * 0x3cc + 0x1015f40;
	for (i = 0; i < 0x10; i++) {
		*(int*) (town + 0x26dc + i * 4) = -1;
	}
	tab = (int*) (town + 0x26dc);
	i = 0;
	if (count >= 1) {
		slot = (ScrollSlot*) (town + 0xdc);
		do {
			if (slot->handle == -1) {
				bld_x = (int) slot->fx;
				bld_y = (int) slot->fy;
				handle = fcn_0046f740(bld_x, bld_y,
				                      (unsigned char) *slot->ent + 0x47f, dir);
				slot->handle = handle;
				*(int*) (g_1015ea0 + 0x5c + handle * 0x2f4) = 1;
				*(int*) (g_1015ea0 + 0x1dc + handle * 0x2f4) = -1;
				*(int*) (g_1015ea0 + 0x1e0 + handle * 0x2f4) = -1;
				*(int*) (g_1015ea0 + 0x1d0 + handle * 0x2f4) = 0x43;
				*(int*) (g_1015ea0 + 0x1cc + handle * 0x2f4) = 0x56;
				if (*slot->ent != 'G') {
					fcn_005b00d0((int) slot->ent,
					             (int) (g_1015ea0 + 0xcc + handle * 0x2f4));
				} else {
					p = (char*) (*(int*) (slot->ent + 0x65) * 0x2f4 + 0x868060);
					next = (unsigned char*) (g_1015ea0 + 0xcc + handle * 0x2f4);
					do {
						*next = *p;
						p++;
						next++;
					} while (*next != 0);
				}
				slot->x = bld_x - *(int*) (g_1015ea0 + 0x18 + handle * 0x2f4) / 2;
				slot->y = bld_y - *(int*) (g_1015ea0 + 0x1c + handle * 0x2f4) / 2;
				fcn_00469c40(*(int*) (g_cur_building + 4) + bld_x,
				             *(int*) (g_cur_building + 8) + bld_y, handle);
				if (!fcn_005cfd00((unsigned short*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c),
				                  (int*) (town + 0xc), (unsigned char*) slot->ent)) {
					*(int*) (g_1015ea0 + 0x5c + handle * 0x2f4) = 0;
					*(int*) (g_1015ea0 + 0x1d0 + handle * 0x2f4) = 0;
				}
			}
			i++;
			slot++;
		} while (i < g_town_count(town));
	}

	i = 0;
	slot = (ScrollSlot*) (town + 0xdc);
	if (count >= 1) {
		do {
			if (slot->handle != -1) {
				kind = *(unsigned short*) (slot->ent + 0x27);
				if (kind != 0xffff) {
					j = *(unsigned char*) (0x7f4ca2 + kind * 0x21c);
					if (j == 5 || j == 6 || j == 7) {
						fcn_0046f740(slot->x - 8, slot->y - 8,
						             *(int*) (0x7f4cf4 + kind * 0x21c),
						             g_cur_dir);
					}
				}
			}
			i++;
			slot++;
		} while (i < g_town_count(town));
	}

	if (g_town_flags(town) & 4) {
		mode = *(int*) 0x6b8010;
		fcn_004432d0(0, 1);
		g_cur_dir = g_town_dir(town);
		g_cur_building = g_town_dir(town) * 0x3cc + 0x1015f40;
		p = (char*) 0x6a4770;
		while (p < (char*) 0x6a4870) {
			obj = fcn_00445600(0, 0x100, 0, p);
			if (obj != 0) {
				fcn_00455350(obj, (float*) (obj + 0x4c), pos);
				fcn_0045b990((float*) tex, pos, &bld_x, &bld_y, &height);
				*(int*) (scratch + 8) = bld_x;
				*(int*) (scratch + 0xc) = bld_y;
				fcn_005b00f0(scratch, base_x, base_y);
				bld_x = (int) *(float*) (scratch + 0x10);
				bld_y = (int) *(float*) (scratch + 0x14);
				handle = fcn_0046f740(bld_x, bld_y, 0x550, g_cur_dir);
				*(int*) (g_1015ea0 + 0x5c + handle * 0x2f4) = 1;
				*(int*) (g_1015ea0 + 0x1d0 + handle * 0x2f4) = 0x43;
				*(int*) (g_1015ea0 + 0x1cc + handle * 0x2f4) = 0x56;
				*(int*) (g_1015ea0 + 0x2f0 + handle * 0x2f4) = (int) obj;
				*tab = handle;
				tab++;
			}
			p += 0x20;
		}
		fcn_004432d0(mode, 1);
	}

	if (g_town_flags(town) & 8) {
		g_cur_dir = g_town_dir(town);
		tab = (int*) (town + 0x24dc);
		list = (unsigned char*) *(int*) 0x774a68;
		for (i = 0; i < 0x100; i++) {
			obj = (char*) *(int*) (list + i * 4);
			if (obj != 0) {
				fcn_00455350(obj, (float*) (obj + 0x4c), pos);
				fcn_0045b990((float*) tex, pos, &bld_x, &bld_y, &height);
				*(int*) (scratch + 8) = bld_x;
				*(int*) (scratch + 0xc) = bld_y;
				fcn_005b00f0(scratch, base_x, base_y);
				bld_x = (int) *(float*) (scratch + 0x10);
				bld_y = (int) *(float*) (scratch + 0x14);
				handle = fcn_0046f740(bld_x, bld_y, 0x54f, g_cur_dir);
				*tab = handle;
				*(int*) (g_1015ea0 + 0x5c + handle * 0x2f4) = 1;
				*(int*) (g_1015ea0 + 0x1d0 + handle * 0x2f4) = 0x43;
			}
			tab++;
		}
	}

	if (*(int*) 0x7746c4) {
		handle = *(int*) (*(int*) 0x7746c4 + 0x61);
	} else if (*(int*) 0x7746c8) {
		handle = *(int*) (*(int*) 0x7746c8 + 0x61);
	} else {
		if (*(int*) 0x6b8014 == 0) {
			return;
		}
		handle = 0;
	}
	if (handle == 0) {
		handle = *(int*) 0x6b8014;
	}

	fcn_00455350((char*) handle, (float*) (handle + 0x4c), pos);
	fcn_0045b990((float*) tex, pos, &bld_x, &bld_y, &height);
	*(int*) (scratch + 8) = bld_x;
	*(int*) (scratch + 0xc) = bld_y;
	fcn_005b00f0(scratch, base_x, base_y);
	g_cur_dir = g_town_dir(town);
	g_cur_building = g_town_dir(town) * 0x3cc + 0x1015f40;
	bld_x = (int) *(float*) (scratch + 0x10) - *(int*) (g_cur_building + 0xc) / 2;
	bld_y = (int) *(float*) (scratch + 0x14) - *(int*) (g_cur_building + 0x10) / 2;
	if (bld_x < 0) {
		bld_x = 0;
	}
	if (*(int*) 0x778d24 - 0x200 < bld_x) {
		bld_x = *(int*) 0x778d24 - 0x200;
	}
	if (bld_y < 0) {
		bld_y = 0;
	}
	if (*(int*) 0x778d20 - 0x168 < bld_y) {
		bld_y = *(int*) 0x778d20 - 0x168;
	}
	*(int*) (g_cur_building + 0x268) = bld_x;
	*(int*) (g_cur_building + 0x258) = bld_y;
	fcn_0046c310(*(int*) g_cur_building);
}
