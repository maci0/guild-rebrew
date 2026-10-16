typedef struct {
	int key;
	char pad4[0x28];
} Entry2c;

extern Entry2c* g_600f48;
extern Entry2c* g_600f4c;
extern int g_6f0714;
extern int g_6f071c;

/* ADDRESS: GOLD 0x004acdc0 */

void __cdecl fcn_004acdc0(void)
{
	g_6f0714 = g_600f48->key;
	g_6f071c = g_600f4c->key;
}
