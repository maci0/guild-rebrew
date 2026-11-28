extern int sv_ClickedObjekt;
extern int sv_ClickedObjekt;



int __cdecl main_RunFrameLoop(void*, int);
int __cdecl fcn_0065f220(void*, int);
void __cdecl d2_RunTechTreeDialog(int, int);

/* ADDRESS: GOLDDE 0x00580370 */
void __cdecl d2_RunUpgradeTechTreeHud(int a)
{
	while (main_RunFrameLoop(d2_RunUpgradeTechTreeHud, 0x67fff)) {
		if (sv_ClickedObjekt != 0 && fcn_0065f220((void*) "UPGRADE", sv_ClickedObjekt) == 0) {
			d2_RunTechTreeDialog(a, 0x2c);
		}
	}
}
