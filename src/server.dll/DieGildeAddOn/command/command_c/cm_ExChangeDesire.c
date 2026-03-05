// STATUS: MATCHING
// BLOCKER: register allocation - target uses only edi, compiler allocates esi+edi for saved param_1 and field writeback address
// ORIGIN: GAME
// SIZE: 214

#include "../command_internal.h"

extern void __cdecl LogMessageInternal(char*, int, char*, int);

extern double _g_stat_min_d;
extern double _g_stat_max_d;
extern char s_cm_ExChangeDesire___Invalid_Id_1002d0f4[];

// FUNCTION: SERVER 0x1000e9c0
int __cdecl cm_ExChangeDesire(uchar* param_1, uchar* param_2)
{
	float clamped;
	uchar* cmd;
	int resolve_ok;
	uchar* cursor;
	uint idx;

	cmd = param_1;
	resolve_ok = gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 0x10));
	*(int*) (cmd + 0x10) = resolve_ok;
	resolve_ok = gm_ResolveEntityById((void**) 0x0, (void**) 0x0, (void**) &param_1, resolve_ok);
	if (resolve_ok == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x33af,
			s_cm_ExChangeDesire___Invalid_Id_1002d0f4,
			1
		);
		return 1;
	}

	idx = 0;
	cursor = cmd + 0x15;
	if (cmd[0x14] != '\0') {
		do {
			resolve_ok = ((uint) *cursor * 3 + 0x24) * 4;
			cursor++;
			*(float*) (param_1 + resolve_ok) = *(float*) cursor + *(float*) (param_1 + resolve_ok);
			cursor = cursor + 4;
			if (*(float*) (param_1 + resolve_ok) < _g_stat_min_d ||
				*(float*) (param_1 + resolve_ok) < _g_stat_max_d) {
				if (_g_stat_min_d <= *(float*) (param_1 + resolve_ok)) {
					clamped = *(float*) (param_1 + resolve_ok);
				} else {
					clamped = (float) _g_stat_min_d;
				}
			} else {
				clamped = (float) _g_stat_max_d;
			}
			*(float*) (param_1 + resolve_ok) = clamped;
			idx = idx + 1;
		} while (idx < cmd[0x14]);
	}

	if (param_2 != (uchar*) 0x0) {
		*param_2 = '\x01';
	}
	return 0;
}
