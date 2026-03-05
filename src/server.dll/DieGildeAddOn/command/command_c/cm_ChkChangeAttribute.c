// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 331
// BLOCKER: struct field access scheduling (inc;inc vs lea+add pattern)
// BLOCKER_DELTA: 14

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

#include "../command_internal.h"

extern void __cdecl LogMessageInternal(char*, unsigned int, char*, int);

extern char s_cm_ChkChangeAttribute___Invalid_I_1002c9e0[];
extern char s_cm_ChkChangeAttribute___Error_i_1002c9a0[];
extern char s_cm_ChkChangeAttribute___Source_obj_1002c958[];
extern char s_cm_ChkChangeAttribute___Target_obj_1002c90c[];

#pragma pack(push, 1)
typedef struct {
	signed char kind;
	signed char value;
	unsigned short offs;
} AttrEntry;
#pragma pack(pop)

// FUNCTION: SERVER 0x1000cde0
int __cdecl cm_ChkChangeAttribute(int param_1, char* param_2)
{
	int id;
	void* ent_a;
	void* ent_b;
	void* ent_c;
	void* base;
	unsigned int i;
	int kind;
	unsigned int value;
	AttrEntry* entry;
	char* p;
	char* field;
	int rec;

	id = gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 0x10));
	*(int*) (param_1 + 0x10) = id;

	if (gm_ResolveEntityById(&ent_a, &ent_b, &ent_c, id) == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x243d,
			s_cm_ChkChangeAttribute___Invalid_I_1002c9e0,
			1
		);
		return 1;
	}

	if (ent_a != (void*) 0) {
		base = ent_a;
	}
	else {
		base = ent_b;
		if (ent_b == (void*) 0) {
			base = ent_c;
		}
	}

	p = (char*) (param_1 + 0x15);
	i = 0;

	while (i < *(unsigned char*) (param_1 + 0x14)) {
		entry = (AttrEntry*) p;
		kind = entry->kind;
		value = entry->value;
		p = (char*) (entry + 1);
		field = (char*) base + entry->offs;

		if (ent_c != (void*) 0) {
			if (field == ((char*) ent_c + 4)) {
				LogMessageInternal(
					s_D__Develop_DieGildeAddOn_command_1002c748,
					0x2479,
					s_cm_ChkChangeAttribute___Error_i_1002c9a0,
					1
				);
				return 1;
			}
			if (field == ((char*) ent_c + 0x5c)) {
				rec = gm_LookupEntityRecordById(*(int*) p + *(int*) ((char*) ent_c + 0x5c));
				if (rec == 0) {
					LogMessageInternal(
						s_D__Develop_DieGildeAddOn_command_1002c748,
						0x249b,
						s_cm_ChkChangeAttribute___Source_obj_1002c958,
						1
					);
					return 1;
				}
				rec = *(int*) (rec + 0x5c);
				if (rec != -1 && rec != *(int*) ((char*) ent_c + 4)) {
					LogMessageInternal(
						s_D__Develop_DieGildeAddOn_command_1002c748,
						0x24a5,
						s_cm_ChkChangeAttribute___Target_obj_1002c90c,
						1
					);
					return 1;
				}
			}
		}

		switch (kind) {
		case 1:
			if (value > 0) {
				p = p + value;
			}
			break;
		case 2:
			if (value > 0) {
				p = p + value * 2;
			}
			break;
		case 4:
			if (value > 0) {
				p = p + value * 4;
			}
			break;
		}

		i++;
	}
	return 0;
}
