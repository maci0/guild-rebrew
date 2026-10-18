extern int g_6a23ac;

// SIZE 0x18c
struct s_7e43a8 {
	int a[24];
	int b[24];
	int pad[2];
	int c[24];
	int d[24];
	int e;
};

#include "client_types.h"
extern Tabs_7e43a8 g_7e43a8;




#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
int __cdecl fcn_005e8d00(void* stream);
int __cdecl fcn_004ef770(void* stream, int version);

int __cdecl fcn_005255b0(void* x)
{
	int i;

	if (ls_ReadVfsDataChecked(&(*(struct s_7e43a8*)&g_7e43a8).e, 4, 1, x) == 0) {
		return 0;
	}
	for (i = 0; i < 24; i++) {
		if (ls_ReadVfsDataChecked(&(*(struct s_7e43a8*)&g_7e43a8).a[i], 4, 1, x) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(&(*(struct s_7e43a8*)&g_7e43a8).b[i], 4, 1, x) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(&(*(struct s_7e43a8*)&g_7e43a8).c[i], 4, 1, x) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(&(*(struct s_7e43a8*)&g_7e43a8).d[i], 4, 1, x) == 0) {
			return 0;
		}
	}
	if (g_6a23ac >= 0x10050 && fcn_005e8d00(x) != 0 && fcn_004ef770(x, g_6a23ac) != 0) {
		return 1;
	}
	return 0;
}
