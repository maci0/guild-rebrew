/* ADDRESS: GOLDTL 0x01042a08 */
extern int g_1042a08;
/* ADDRESS: GOLDTL 0x010432a8 */
extern int g_10432a8;
/* ADDRESS: GOLDTL 0x01042a04 */
extern int g_1042a04;
/* ADDRESS: GOLDTL 0x01052bac */
extern int g_1052bac;


void __cdecl fcn_0043ad20(void*, void*);
void __cdecl fcn_0043b170(void*, void*, int, int);

void __cdecl fcn_0043b320(void* a1, void* a2, int a3)
{
	fcn_0043ad20(a1, a2);
	g_1042a08 = 0;
	g_10432a8 = 0;
	g_1042a04 = 0;
	g_1052bac = 0;
	fcn_0043b170(a1, a2, a3, 1);
}
