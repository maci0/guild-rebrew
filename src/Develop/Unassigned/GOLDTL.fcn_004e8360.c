/* Office slot reassignment: validates the requesting entity, resolves the
 * slot by its byte id in the 42-entry office table, detaches the slot's former
 * occupant from its role flags, then rebinds the slot to the new entity. */

typedef struct
{
	unsigned char f00;      /* +0x00 slot / role id */
	char pad01[3];
	int f04;                /* +0x04 occupying entity id, -1 when free */
	unsigned char f08;      /* +0x08 role kind */
	char pad09[3];
	int f0c;                /* +0x0c pending count */
	unsigned char f10;      /* +0x10 status */
	char pad11[3];
	int f14;                /* +0x14 setter entity id */
} Rec18;
// SIZE 0x18
#include "client_data.h"
char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_005b2280(void* a1, void* a2);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x004e8360 */
int __cdecl fcn_004e8360(char* requestData)
{
	char* ent;
	char* setter;
	char* x;
	unsigned char* p;
	unsigned char bit;
	unsigned int flags;
	int other;
	int i;
	int k;
	int* ip;

	other = -1;
	setter = 0;
	if (*(int*) (requestData + 7) != -1) {
		setter = gm_LookupEntityRecordById(*(int*) (requestData + 7));
		if (setter == 0)
			return 0;
	}
	ent = 0;
	if (*(int*) (requestData + 1) != -1) {
		ent = gm_LookupEntityRecordById(*(int*) (requestData + 1));
		if (ent == 0)
			return 0;
		other = *(int*) (ent + 4);
	}
	for (i = 0; i < 0x2a; i++) {
		if (((Rec18*) amt_OfficeSlots)[i].f00 == *(unsigned char*) requestData)
			break;
	}
	if (i >= 0x2a)
		return 0;
	x = gm_LookupEntityRecordById(((Rec18*) amt_OfficeSlots)[i].f04);
	if (x != 0 && *(int*) (x + 4) != *(int*) (requestData + 1)) {
		bit = ((Rec18*) amt_OfficeSlots)[i].f08;
		if (*(unsigned char*) (x + 0x166) == bit) {
			*(unsigned char*) (x + 0x166) = 0;
		} else if (*(unsigned char*) (x + 0x169) == bit) {
			*(unsigned char*) (x + 0x169) = 0;
		} else if (bit == '#') {
			*(int*) (x + 0x1cc) &= 0xfffffdff;
		} else if (bit == '$') {
			*(int*) (x + 0x1cc) &= 0xfffffbff;
		} else if (bit == '%') {
			*(int*) (x + 0x1cc) &= 0xfffff7ff;
		}
	}
	if (ent != 0) {
		if (((Rec18*) amt_OfficeSlots)[i].f08 <= 0x1b) {
			if (*(unsigned char*) (ent + 0x166) != 0) {
				k = 0;
				ip = (int*) 0x9a9224;
				do {
					if (*ip == other) {
						((Rec18*) amt_OfficeSlots)[k].f04 = -1;
						((Rec18*) amt_OfficeSlots)[k].f14 = -1;
						((Rec18*) amt_OfficeSlots)[k].f10 = 4;
						((Rec18*) amt_OfficeSlots)[k].f0c = 0;
						break;
					}
					ip = (int*) ((char*) ip + 0x18);
					k++;
				} while ((int) ip < (int) 0x9a94f4);
			}
			if (*(unsigned char*) (0x68da70 + ((Rec18*) amt_OfficeSlots)[i].f08 * 0x18) >=
			    *(unsigned char*) (0x68da70 + *(unsigned char*) (ent + 0x166) * 0x18))
				*(unsigned char*) (ent + 0x167) = ((Rec18*) amt_OfficeSlots)[i].f08;
			bit = ((Rec18*) amt_OfficeSlots)[i].f08;
			*(unsigned char*) (ent + 0x166) = bit;
			if (*(unsigned char*) (ent + 0x168) == bit)
				*(unsigned char*) (ent + 0x168) = 0;
			if (((Rec18*) amt_OfficeSlots)[i].f08 == 0x0f) {
				*(int*) (ent + 0x1cc) |= 0x40;
			} else if (((Rec18*) amt_OfficeSlots)[i].f08 == 0x15) {
				*(int*) (ent + 0x1cc) |= 0x80;
			} else if (((Rec18*) amt_OfficeSlots)[i].f08 == 0x1b) {
				*(int*) (ent + 0x1cc) |= 0x100;
			}
			if (*(int*) (0x68da78 + ((Rec18*) amt_OfficeSlots)[i].f08 * 0x18) != 0) {
				k = 0;
				p = (unsigned char*) 0x9a9228;
				do {
					if (*(unsigned char*) p == ((Rec18*) amt_OfficeSlots)[i].f08 && k != i) {
						if (((Rec18*) amt_OfficeSlots)[k].f10 == 3 &&
						    ((Rec18*) amt_OfficeSlots)[k].f0c != 0) {
							((Rec18*) amt_OfficeSlots)[k].f0c =
								((Rec18*) amt_OfficeSlots)[k].f0c - 1;
							if (((Rec18*) amt_OfficeSlots)[k].f0c == 0)
								((Rec18*) amt_OfficeSlots)[k].f10 = 4;
						}
						break;
					}
					p += 0x18;
					k++;
				} while ((int) p < (int) 0x9a94f8);
			}
		} else if (((Rec18*) amt_OfficeSlots)[i].f08 >= 0x1c && ((Rec18*) amt_OfficeSlots)[i].f08 <= 0x22) {
			if (*(unsigned char*) (ent + 0x169) != 0) {
				p = (unsigned char*) 0x9a94f4;
				do {
					if (*(unsigned char*) (p + 4) == *(unsigned char*) (ent + 0x169) &&
					    *(int*) p == *(int*) (ent + 4))
						*(int*) p = -1;
					p += 0x18;
				} while ((int) p < (int) 0x9a959c);
			}
			*(unsigned char*) (ent + 0x169) = ((Rec18*) amt_OfficeSlots)[i].f08;
		} else {
			flags = *(int*) (ent + 0x1cc) & 0xfffff1ff;
			*(int*) (ent + 0x1cc) = flags;
			k = 0;
			if (((Rec18*) amt_OfficeSlots)[i].f08 == '#') {
				*(int*) (ent + 0x1cc) = flags | 0x200;
				k = 0x4000;
			} else if (((Rec18*) amt_OfficeSlots)[i].f08 == '$') {
				*(int*) (ent + 0x1cc) = flags | 0x400;
				k = 0x8000;
			} else if (((Rec18*) amt_OfficeSlots)[i].f08 == '%') {
				*(int*) (ent + 0x1cc) = flags | 0x800;
				k = 0x10000;
			}
			for (ip = (int*) 0x7f4e6c; (int) ip < (int) 0x85a26c; ip = (int*) ((char*) ip + 0x21c))
				*ip &= ~k;
		}
	}
	((Rec18*) amt_OfficeSlots)[i].f04 = other;
	((Rec18*) amt_OfficeSlots)[i].f14 = *(int*) (requestData + 7);
	((Rec18*) amt_OfficeSlots)[i].f10 = *(unsigned char*) (requestData + 5);
	if (*(unsigned char*) (requestData + 5) == 3)
		((Rec18*) amt_OfficeSlots)[i].f0c = 0;
	if (setter != 0 && ent != 0 &&
	    *(int*) ((unsigned long)&g_7f4ca4 + *(unsigned short*) &g_774970 * 0x21c) == *(int*) (ent + 4))
		fcn_005b2280(setter, ent);
	return 1;
}
