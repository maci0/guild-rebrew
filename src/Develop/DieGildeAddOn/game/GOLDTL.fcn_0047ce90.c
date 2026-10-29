extern int g_100dc00;
extern int g_100dc04;
extern int g_100dc14;
extern int g_100e774;
extern int g_100e730;
extern int g_100e764;
extern int g_100e760;
extern int g_100e768;
extern int g_100e76c;
extern int g_100e770;
extern int g_100e720;
extern int g_100e724;
extern int g_100e728;
extern int g_100e72c;

void __cdecl sim_SetSyncParams(void* target, int type_id, int field_6, int field_10);
int __cdecl fcn_00494820(void);

/* ADDRESS: GOLDTL 0x0047ce90 */
int __cdecl fcn_0047ce90(void)
{
	g_100dc00 = 0;
	g_100dc04 = 0;
	sim_SetSyncParams(&g_100dc04, 6, 0, 0);
	g_100dc14 = 0;
	if (!fcn_00494820())
		return 0;
	g_100e774 = 0;
	g_100e730 = 0;
	g_100e764 = 0x154;
	g_100e760 = 0x156;
	g_100e768 = 0x158;
	g_100e76c = 0x172;
	g_100e770 = 0x16e;
	g_100e720 = 0x174;
	g_100e724 = 0x176;
	g_100e728 = 0x15e;
	g_100e72c = 0x160;
	return 1;
}
