
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

char s_cm_ChkChangeAttribute___Invalid_I_1002c9e0[] = "cm_ChkChangeAttribute() Invalid Id";
char s_cm_ChkChangeAttribute___Error_i_1002c9a0[] = "cm_ChkChangeAttribute() Invalid action on player <<Change ID>>";
char s_cm_ChkChangeAttribute___Source_obj_1002c958[] = "cm_ChkChangeAttribute() Invalid action on player <<ID does not exist>>";
char s_cm_ChkChangeAttribute___Target_obj_1002c90c[] = "cm_ChkChangeAttribute() Invalid action on player <<PartnerID already set>>";

#pragma pack(push, 1)
// SIZE 0x4
#pragma pack(pop)

/* Validation handler: resolves entity by ID and validates each
 * attribute field descriptor (kind/value/offset) in the command
 * payload. Returns 1 on invalid entity ID. */

// FUNCTION: SERVER 0x1000cde0
// cm_ChkChangeAttribute

int __cdecl cm_ChkChangeAttribute(int cmd, char* result)
{
	char* t_a;
	char* t_b;
	char* t_d;
	unsigned int i;
	char* p;
	char* base;
	int addr;
	int kind;
	int n;
	char* rec;
	int s;

	*(int *) (cmd + 0x10) = gm_GetFieldByType((char *) cmd, *(int *) (cmd + 0x10));
	if (!gm_ResolveEntityById((void **) &t_b, (void **) &t_a, (void **) &t_d, *(int *) (cmd + 0x10))) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x243d, s_cm_ChkChangeAttribute___Invalid_I_1002c9e0, 1);
		return 1;
	}
	if (t_b)
		base = t_b;
	else if (t_a)
		base = t_a;
	else
		base = t_d;
	p = (char *) cmd + 0x15;
	for (i = 0; i < *(unsigned char *) (cmd + 0x14); i++) {
		kind = *(signed char *) p;
		p++;
		n = *(signed char *) p;
		p++;
		addr = *(unsigned short *) p + (int) base;
		p += 2;
		if (t_d != 0) {
			if (addr == (int) t_d + 4) {
				LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2479, s_cm_ChkChangeAttribute___Error_i_1002c9a0, 1);
				return 1;
			}
			if (addr == (int) t_d + 0x5c) {
				s = *(int *) p + *(int *) (t_d + 0x5c);
				rec = (char *) gm_LookupEntityRecordById(s);
				if (rec == 0) {
					LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x249b, s_cm_ChkChangeAttribute___Source_obj_1002c958, 1);
					return 1;
				}
				if (*(int *) (rec + 0x5c) != -1 && *(int *) (rec + 0x5c) != *(int *) (t_d + 4)) {
					LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x24a5, s_cm_ChkChangeAttribute___Target_obj_1002c90c, 1);
					return 1;
				}
			}
		}
		switch (kind) {
		case 1:
			if ((unsigned) n > 0) p += n;
			break;
		case 2:
			if ((unsigned) n > 0) p += 2 * n;
			break;
		case 4:
			if ((unsigned) n > 0) p += 4 * n;
			break;
		}
	}
	return 0;
}
