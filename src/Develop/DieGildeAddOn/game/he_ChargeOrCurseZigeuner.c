


unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_ModifyHealth(int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
void __cdecl he_DispatchZigeunerEvent(char*, char*, int);

/* ADDRESS: GOLDDE 0x00562460 */
void __cdecl he_ChargeOrCurseZigeuner(char* o, int lvl)
{
	char buf[0x200];
	int n;

	if (lvl < 2) {
		n = gm_RandomMod(2) + 2;
	} else if (lvl == 2) {
		n = gm_RandomMod(2) + 3;
	} else if (lvl == 3) {
		n = gm_RandomMod(lvl) + lvl;
	} else {
		n = gm_RandomMod(4);
		if (lvl == 4) {
			n += 3;
		} else {
			n += 4;
		}
	}
	if (*(int*) (o + 0x194) >= n) {
		gm_ModifyHealth(*(int*) (o + 4), -n);
		io_FormatTextBuffer(buf, 0x41db, n);
		he_PostEntityMessage(*(int*) (o + 4), -1, buf, 1, 0x5fa, "_NACHRICHTEN_ZIGEUNER_00");
	} else {
		he_DispatchZigeunerEvent(o, o, lvl);
	}
}
