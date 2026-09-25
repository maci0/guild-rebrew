extern int g_774650;
extern int g_774654;
extern int g_7e35c0[];
// FUNCTION: GOLD 0x0052fb80
// SIZE: 38
// FUNCTION: GOLDTL 0x005356b0
// SIZE: 38

void __cdecl fcn_005356b0(int v)
{
	int i;

	for (i = g_774650; i >= 0; i--) {
		if (g_7e35c0[i * 2] == v) {
			g_774654 = g_774650 - i;
			return;
		}
	}
}
