#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_772514;

#include "Develop/Units/Error/error_message.h"
void __cdecl fcn_00476970(int a);

/* ADDRESS: GOLDTL 0x00472e50 */
void __cdecl fcn_00472e50(void)
{
	char* m;

	m = ((char*)g_1015f40) + g_772514 * 0x3cc;
	if (*(int*) (m + 0x290) == 0) {
		fcn_0041d9e0((const char*) 0x67d844);
		return;
	}
	if (*(int*) (m + 0x38) == 0) {
		fcn_0041d9e0((const char*) 0x67d818);
		return;
	}
	fcn_00476970(*(int*) (m + 0x38));
}
