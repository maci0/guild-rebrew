#include "Develop/DieGildeAddOn/game/game_player.h"

char* __cdecl gm_LookupEntityRecordById(int a1);
int __cdecl fcn_005d3120(int a1, int* a2);
char* __cdecl fcn_005463a0(int a1, int a2, int a3);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char* buf, int fmt, int arg);

/* ADDRESS: GOLDTL 0x004f7210 */
int __cdecl fcn_004f7210(int entity, int* command)
{
	char* e;
	char* s;
	char* p;
	int r;

	if ((*command == 3 || *command == 1)
	    && (*(int*) (entity + 0x5c) == -1
	        || ((s = gm_LookupEntityRecordById(*(int*) (entity + 0x5c))) != 0
	            && (*(char*) (s + 8) == 0 || *(char*) (s + 2) == 0x0f)))) {
		r = 2;
		if (*command == 3) {
			r = fcn_005d3120(entity, command) | 2;
		} else if (*command == 1 && *(char*) (entity + 2) == 6) {
			for (e = fcn_005463a0(1, 0, 0x41); e != 0; e = he_fn_Handlung()) {
				if (*(int*) (e + 0xac) == *(int*) (g_774970 * 0x21c + 0x7f4ca4)) {
					p = gm_LookupEntityRecordById(*(int*) (e + 0xb0));
					io_FormatTextBuffer((char*) command + 0x14, 0x1ce2, *(unsigned short*) p);
					return r;
				}
			}
			io_FormatTextBuffer((char*) command + 0x14, 0x679060, 0x1ce1);
		}
		return r;
	}
	return 1;
}
