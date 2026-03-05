/* STATUS: STUB */
/* ORIGIN: GAME */
/* SIZE: 331 */
/* CFLAGS: /O2 /Gd */
/* SYMBOL: _CheckChangeAttribute */
/* FUNCTION: SERVER 0x1000cde0 */

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

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
	unsigned int i;
	int kind;
	unsigned int value;
	int* piVar;
	char* p;
	char* field;
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

	if (ent_a != (void*) 0) {
		base = ent_a;
	}
	else {
		base = ent_b;
		if (ent_b == (void*) 0) {
			base = ent_c;
		}
	}

	piVar = (int*) (param_1 + 0x15);
	i = 0;

	while (i < *(unsigned char*) (param_1 + 0x14)) {
		kind = (signed char) *(char*) piVar;
		value = (int) *(signed char*) ((int) piVar + 1);
		p = (char*) ((unsigned int) *(unsigned short*) ((int) piVar + 2) + (int) base);
		piVar = piVar + 1;
		field = p;

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
				rec = LookupEntityRecordById(*(int*) piVar + *(int*) ((char*) ent_c + 0x5c));
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
				piVar = (int*) ((char*) piVar + value);
			}
			break;
		case 2:
			if (value > 0) {
				piVar = (int*) ((char*) piVar + value * 2);
			}
			break;
		case 4:
			if (value > 0) {
				piVar = (int*) ((char*) piVar + value * 4);
			}
			break;
		}

		i++;
	}
	return 0;
}
