typedef struct {
	int key;
	char pad4[0x28];
} Entry2c;

extern Entry2c* g_600f48;
extern Entry2c* g_600f4c;
extern int g_6f0714;
extern int g_6f071c;

int __cdecl fcn_004acae0(int a);

/* ADDRESS: GOLD 0x004aca90 */
int __cdecl fcn_004aca90(void)
{
	int r;

	*(int*)0x6f0710 = -1;
	*(int*)0x6f0718 = -1;
	*(int*)0x6f0714 = -1;
	*(int*)0x6f071c = -1;
	*(int*)0x6f0720 = -1;
	r = fcn_004acae0(0x600f40);
	if (r == 0) {
		g_6f0714 = g_600f48->key;
		g_6f071c = g_600f4c->key;
	}
	return r;
}
