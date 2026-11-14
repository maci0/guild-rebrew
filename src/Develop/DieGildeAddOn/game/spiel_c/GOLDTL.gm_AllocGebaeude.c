#pragma optimize("y", off)
#include <string.h>

/* Client (GOLDTL) building allocator. Sibling of the server body in
 * Develop/DieGildeAddOn/game/spiel.c, which shares the field layout but not the
 * client's prototype-name selection. */

extern char* lpGebaeudePROT;
extern int g_699364;
extern char g_14a6558[];
extern char* lpGebaeudeINST;
extern int lpObjektePROT;
extern char g_6b5c60;
extern char s_699858[];
extern char s_69983c[];
extern char s_69982c[];
extern char s_699820[];

char* __cdecl gm_SearchStruct(void);
char* __cdecl gm_AllocObjekt(int, int, int);
char* __cdecl gm_AllocRaum(char*, int);
char* __cdecl gm_SetupEntityQuery(char*);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_CheckEntityType(char*);
void __cdecl gm_SetBuildingWorkerLimits(char*);
int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl fcn_00504250(char*);
char* __cdecl gv_AllocGraveyardField(char*);
void __cdecl fcn_004f1ad0(char*, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_005b1b30(char*);
char* __cdecl m_alloc(int, char*);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_0064d41a(char*, char*, ...);


#pragma pack(push, 1)
typedef struct {
	unsigned char unknown00[0x23];
	unsigned short components[0x40];
	unsigned char unknowna3[0x1aa];
} BuildingProto5043d0;
#pragma pack(pop)


/* Allocates a building entity for a prototype type and owner slot and fills in
 * its type defaults: name, the object ids of its prototype record, its room
 * layout, the owner's position block and the per-type fields. */
/* ADDRESS: GOLDTL 0x005043d0 */
char* __cdecl gm_AllocGebaeude(unsigned char geb_type, unsigned short owner)
{
	char tmp[0x100];
	char names[12][0x40];
	unsigned int type;
	char* list_end;
	BuildingProto5043d0* rec; BuildingProto5043d0* prototypes;
	char* geb;
	unsigned short comp;
	char* comp_rec;
	unsigned char comp_type;
	char* q;
	int i;
	int n; int room_mode;
	char** alias;

	prototypes = (BuildingProto5043d0*) lpGebaeudePROT;
	if (prototypes == 0) {
		return 0;
	}
	room_mode = 0;
	geb = gm_SearchStruct();
	if (geb == 0) {
		return 0;
	}
	type = (unsigned char) geb_type;
	*geb = (char) geb_type;
	rec = &prototypes[type];
	{
	char buf[0x100];
	char msg[0x200];
	fcn_0064d41a(buf, s_699858, g_699364, (int) type);
	*(int*) (geb + 1) = g_699364;
	g_699364 = g_699364 + 1;
	*(unsigned short*) (geb + 0x25) = owner;
	*(unsigned short*) (geb + 0x27) = owner;
	*(unsigned short*) (geb + 0x29) = 0;
	*(int*) (geb + 0x2b) = 0;
	geb[0x2f] = 0;
	*(int*) (geb + 0x5d) = 0;
	*(int*) (geb + 0x61) = 0;
	*(int*) (geb + 0x30) = 0;
	*(int*) (geb + 0x39) = 0x7d00;
	*(int*) (geb + 0x3d) = 0x64;
	*(int*) (geb + 0x41) = 2;
	*(int*) (geb + 0x45) = 0x64;
	*(int*) (geb + 0x49) = 0x3f800000;
	geb[0x5c] = 0x64;
	*(int*) (geb + 0x95) = -1;
	if (owner != 0xffff) {
		if (*(char*) (0x7f4ca2 + (int) owner * 0x21c) == 6) {
			fcn_005b1b30(geb);
		}
	}
	memset(geb + 0x99, 0, 0x10);
	*(int*) (geb + 0xa5) = -1;
	*(int*) (geb + 0x99) |= 1;
	n = 0x30; q = geb + 0x65;
	__asm {
		mov edi, q
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short fill_end
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	fill_end:
		add ecx, ebx
		rep stosb
	}
	n = 0;
	alias = (char**) (g_14a6558 + 8 + (int) type * 0x38);
	if (**alias != 0) {
		strcpy(geb + 5, *(char**) (g_14a6558 + (int) type * 0x38));
		list_end = names[0];
		i = 0;
	} else {
		geb[5] = g_6b5c60;
		list_end = names[0];
		i = 0;
	}
	for (; i < 12; i++, alias++) {
		int j;

		if (**alias == 0) {
			continue;
		}
		strcpy(tmp, *(char**) (g_14a6558 + 8 + (int) type * 0x38 + i * 4));
		for (j = 0; j < 0x100; j++) {
			if (lpGebaeudeINST[j * 0xa9] != 0 && strcmp(lpGebaeudeINST + j * 0xa9 + 5, tmp) == 0) {
				break;
			}
		}
		if (j < 0x100) {
			continue;
		}
		if (strlen(tmp) < 0x20) {
			strcpy(list_end, tmp);
			list_end += 0x40;
			n++;
		} else {
			fcn_0064d41a(msg, s_69983c, tmp);
		}
	}
	}
	if (n != 0) {
		strcpy(geb + 5, names[gm_RandomMod(n) & 0xffff]);
	}
	i = 0;
	comp_rec = (char*) rec->components;
	do {
		comp = *(unsigned short*) comp_rec;
		if (comp == 0) {
			break;
		}
		if (comp != 0xffff) {
			comp_type = *(unsigned char*) (lpObjektePROT + (int) (comp & 0x7fff) * 0x41);
			if (comp_type == 2 || comp_type == 6) {
				room_mode = 1;
			}
			if ((comp & 0x8000) != 0) {
				if (comp_type == 2 || comp_type == 6) {
					room_mode = 1;
					gm_AllocRaum(geb, comp & 0x7fff);
				} else if (room_mode == 0) {
					gm_AllocObjekt(*(int*) (geb + 1), comp & 0x7fff, 1);
				}
			}
		}
		i++;
		comp_rec += 2;
	} while (i < 0x40);
	q = fcn_00502cd0(*(int*) (geb + 0x5d), 1, 4, 2);
	while (q != 0) {
		if (*(unsigned short*) q != 0xfd) {
			*(unsigned short*) (geb + 0x29) = *(unsigned short*) q;
			break;
		}
		q = gm_NextEntityQueryMatch();
	}
	q = gm_SetupEntityQuery(geb);
	if (q != 0) {
		*(unsigned short*) (geb + 0x29) = *(unsigned short*) q;
	}
	if (gm_CheckEntityType(geb) != 0) {
		*(int*) (geb + 0x30) = 0x1388;
	}
	switch (type) {
	case 4:
	case 5:
	case 6:
	case 7:
		*(int*) (geb + 0x69) = *(int*) 0x7f4c00;
		q = geb + 0x69;
		*(int*) (q + 4) = *(int*) 0x7f4c04;
		*(int*) (q + 8) = *(int*) 0x7f4c08;
		*(unsigned short*) (q + 0xc) = *(unsigned short*) 0x7f4c0c;
		if (owner != 0xffff) {
			*(int*) (geb + 0x65) = *(int*) (0x7f4ca4 + (int) owner * 0x21c);
		} else {
			*(int*) (geb + 0x65) = -1;
		}
		break;
	case 0x14:
	case 0x15:
	case 0x16:
		comp_rec = gm_AllocObjekt(*(int*) (geb + 1), 0x1b5, 1);
		if (comp_rec != 0) {
			comp_rec[0x22] = 0;
			comp_rec[0x1c] = (char) -1;
			comp_rec[0x1d] = (char) -1;
			*(int*) (comp_rec + 0x1e) = -1;
		}
		break;
	case 0x47:
		*(int*) (geb + 0x30) = 0x13880;
		break;
	case 0x1e:
		*(int*) (geb + 0x71) = (int) m_alloc(0x600, s_69982c);
		i = 0;
		do {
			i += 0x18;
			*(unsigned char*) (i + *(int*) (geb + 0x71) - 0xb) = 0xff;
			*(int*) (i + *(int*) (geb + 0x71) - 4) = 0;
		} while (i < 0x600);
	case 0x1f:
	case 0x20:
		*(int*) (geb + 0x30) = 0x64;
		*(int*) (geb + 0x49) = 0x3f4ccccd;
		break;
	case 0x35:
	case 0x36:
	case 0x37:
		*(int*) (geb + 0x65) = 0;
		*(unsigned short*) (geb + 0x69) = 0;
		*(unsigned short*) (geb + 0x6b) = 0;
		*(int*) (geb + 0x6d) = 0;
		break;
	case 0xb:
	case 0xc:
	case 0xd:
		*(int*) (geb + 0x65) = -1;
		break;
	case 0xe:
	case 0xf:
	case 0x10:
		*(int*) (geb + 0x65) = 0xa;
		*(int*) (geb + 0x69) = 3;
		*(int*) (geb + 0x6d) = 5;
		break;
	case 0x48:
	case 0x49:
	case 0x4a:
		*(int*) (geb + 0x65) = (int) gv_AllocGraveyardField(geb);
		fcn_004f1ad0(geb, 3);
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		comp_rec = m_alloc(0x3c, s_699820);
		*(int*) (geb + 0x65) = (int) comp_rec;
		*(int*) comp_rec = -1;
		break;
	default:
		break;
	}
	if (*geb == 0x26) {
		*(unsigned short*) (geb + 0x29) = 0x10e;
	}
	gm_SetBuildingWorkerLimits(geb);
	gm_GetBuildingTypeCategory((unsigned char) *geb);
	fcn_00504250(geb);
	return geb;
}
