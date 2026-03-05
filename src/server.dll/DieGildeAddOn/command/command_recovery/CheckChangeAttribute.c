// FUNCTION: SERVER 0x1000cde0
// STATUS: STUB
// BLOCKER: zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 331
// CFLAGS: /O2 /Gd
// SYMBOL: _CheckChangeAttribute
// BLOCKER_DELTA: 241

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
// BLOCKER_DELTA: 241
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 331B
 *    CFlags: 
 *    Symbol: _CheckChangeAttribute
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CheckChangeAttribute(int param_1,char *param_2)
 * 
 * {
 *   char cVar1;
 *   int iVar2;
 *   int *piVar3;
 *   int iVar4;
 *   void *pvVar5;
 *   void *pvVar6;
 *   ushort *puVar7;
 *   int *piVar8;
 *   uint line;
 *   char *msg;
 *   void *local_10;
 *   uint local_c;
 *   void *local_8;
 *   void *local_4;
 *   
 *   iVar2 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(param_1 + 0x10) = iVar2;
 *   iVar2 = ResolveEntityById(&local_8,&local_4,&local_10,iVar2);
 *   if (iVar2 == 0) {
 *     msg = s_cm_ChkChangeAttribute___Invalid_I_1002c9e0;
 *     line = 0x243d;
 * LAB_1000cf11:
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
 *     return 1;
 *   }
 *   pvVar6 = local_8;
 *   if ((local_8 == (void *)0x0) && (pvVar6 = local_4, local_4 == (void *)0x0)) {
 *     pvVar6 = local_10;
 *   }
 *   piVar8 = (int *)(param_1 + 0x15);
 *   local_c = 0;
 *   pvVar5 = local_10;
 *   if (*(char *)(param_1 + 0x14) != '\0') {
 *     do {
 *       cVar1 = (char)*piVar8;
 *       iVar2 = (int)*(char *)((int)piVar8 + 1);
 *       puVar7 = (ushort *)((int)piVar8 + 2);
 *       piVar8 = piVar8 + 1;
 *       piVar3 = (int *)((uint)*puVar7 + (int)pvVar6);
 */

extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern int __cdecl LookupEntityRecordById(int);
extern void __cdecl LogMessageInternal(char*, unsigned int, char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ChkChangeAttribute___Invalid_I_1002c9e0[];
extern char s_cm_ChkChangeAttribute___Error_i_1002c9a0[];
extern char s_cm_ChkChangeAttribute___Source_obj_1002c958[];
extern char s_cm_ChkChangeAttribute___Target_obj_1002c90c[];

int __cdecl CheckChangeAttribute(int param_1, char* param_2)
{
	int id;
	void* ent_a;
	void* ent_b;
	void* ent_c;
	void* base;
	int i;
	int kind;
	int count;
	unsigned int offs;
	char* p;
	char* field;
	int value;
	int rec;

	id = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x10));
	*(int*) (param_1 + 0x10) = id;

	if (ResolveEntityById(&ent_a, &ent_b, &ent_c, id) == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x243d,
			s_cm_ChkChangeAttribute___Invalid_I_1002c9e0,
			1
		);
		return 1;
	}

	if (ent_a != (void*) 0x0) {
		base = ent_a;
	}
	else if (ent_b != (void*) 0x0) {
		base = ent_b;
	}
	else {
		base = ent_c;
	}

	p = (char*) (param_1 + 0x15);
	i = 0;
	count = *(unsigned char*) (param_1 + 0x14);

	while (i < count) {
		kind = (signed char) p[0];
		value = (signed char) p[1];
		offs = *(unsigned short*) (p + 2);
		p = p + 4;
		field = (char*) base + offs;

		if (ent_c != (void*) 0x0) {
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
				rec = LookupEntityRecordById(*(int*) p + *(int*) ((char*) ent_c + 0x5c));
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
				if ((rec != -1) && (rec != *(int*) ((char*) ent_c + 4))) {
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

		if (kind == 1) {
			if (value > 0) {
				p = p + value;
			}
		}
		else if (kind == 2) {
			if (value > 0) {
				p = p + value * 2;
			}
		}
		else if (kind == 4) {
			if (value > 0) {
				p = p + value * 4;
			}
		}

		i = i + 1;
	}
	return 0;
}
