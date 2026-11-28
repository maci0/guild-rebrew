char* __cdecl gm_NextEntityQueryMatch(void);

// SIZE 0x21c
struct s_7f4ca0 {
	unsigned short id;
	char kind;
	char pad[0x169];
	char* p;
	char pad2[0x44];
	unsigned char flags;
	char pad3[0x67];
};

extern char gm_EntitySlotTable[];




char* __cdecl gm_QueryEntities(int, int, int, int, int);

/* ADDRESS: GOLDDE 0x0051a500 */
void __cdecl gm_UpdateGraveyardFlags(void)
{
	char* e;
	int i;

	for (e = gm_QueryEntities(0, 2, 7, 4, 0x1d); e != 0; e = gm_NextEntityQueryMatch()) {
		*(int*) (e + 0x20) = 0;
		for (i = 0; i < 768; i++) {
			if (((struct s_7f4ca0*)gm_EntitySlotTable)[i].id != 0xffff && ((struct s_7f4ca0*)gm_EntitySlotTable)[i].kind == 1 && ((struct s_7f4ca0*)gm_EntitySlotTable)[i].p != 0 &&
			    *(int*) (((struct s_7f4ca0*)gm_EntitySlotTable)[i].p + 1) == *(int*) (e + 0x1c) && (((struct s_7f4ca0*)gm_EntitySlotTable)[i].flags & 1) != 0) {
				*(int*) (e + 0x20) |= 1;
			}
		}
	}
}
