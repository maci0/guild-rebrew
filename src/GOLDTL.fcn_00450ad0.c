/* ADDRESS: GOLDTL 0x01041d04 */
extern void* g_1041d04;
/* ADDRESS: GOLDTL 0x006b8708 */
extern int g_6b8708;
/* ADDRESS: GOLDTL 0x006b8704 */
extern int g_6b8704;
/* ADDRESS: GOLDTL 0x006b870c */
extern void* g_6b870c;
/* ADDRESS: GOLDTL 0x006b8700 */
extern int g_6b8700;
/* ADDRESS: GOLDTL 0x006b86fc */
extern int g_6b86fc;
#include "client_lighting.h"


void __cdecl m_FreeTracked(int);

void __cdecl fcn_00450ad0(void)
{
	g_6b8708 = 0;
	g_6b8704 = 0;
	m_FreeTracked((*(int*)&g_1041d04));
	(*(int*)&g_1041d04) = 0;
	g_6b8700 = 0;
	g_6b86fc = 0;
	m_FreeTracked((*(int*)&g_6b870c));
	(*(int*)&g_6b870c) = 0;
	g_6b86d4 = 0;
}
