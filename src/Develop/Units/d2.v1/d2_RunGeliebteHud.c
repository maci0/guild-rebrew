int __cdecl main_RunFrameLoop(void*, const char*);
int __cdecl RegisterStatusText(const char*, int, int);
void __cdecl d2_ShowGeliebteDialog(int);
extern int g_14abc58;
extern int sv_ClickedObjekt;

/* ADDRESS: GOLDTL 0x005a0250 */
/* ADDRESS: GOLDDE 0x005850d0 */
void __cdecl d2_RunGeliebteHud(int building)
{
	int status;
	int value;

	status = main_RunFrameLoop((void*) d2_RunGeliebteHud, (const char*) 0x67fff);
	if (status == 0) {
		return;
	}
	while (status != 0) {
		value = RegisterStatusText("contact_GELIEBTE", g_14abc58, 0x16);
		if (sv_ClickedObjekt != 0 && sv_ClickedObjekt == value) {
			d2_ShowGeliebteDialog(building);
		}
		status = main_RunFrameLoop((void*) d2_RunGeliebteHud, (const char*) 0x67fff);
	}
}
