extern int g_774934;
extern int g_774930;

void __cdecl fcn_005e12d0(void);
void __cdecl fcn_00500a20(void);
void __cdecl fcn_0053f8f0(void);
void __cdecl fcn_00429800(void);
void __cdecl fcn_00520f40(void);
void __cdecl fcn_00422100(void);
void __cdecl fcn_00418c60(void);
void __cdecl fcn_0041fb80(void);
void __cdecl fcn_0042a0b0(void);
void __cdecl fcn_004195f0(void);
void __cdecl fcn_0057de00(void);
void __cdecl fcn_0042d5f0(void);
void __cdecl gm_CleanupAllEntities(void);
void __cdecl fcn_005b1ef0(void);
void __cdecl fcn_004edce0(void);
void __cdecl fcn_004acf00(void);
void __cdecl fcn_004efcd0(void);
void __cdecl fcn_0040bfd0(void);
void __cdecl fcn_004c3ed0(void);

// FUNCTION: GOLDTL 0x005381a0
// SIZE: 122

/* The inventory entry also holds two more functions:
 * 0x538220 (47 bytes) and the window procedure at 0x538250. */
void __cdecl fcn_005381a0(void)
{
	fcn_005e12d0();
	fcn_00500a20();
	fcn_0053f8f0();
	fcn_00429800();
	fcn_00520f40();
	if (g_774934 != 0) {
		fcn_00422100();
		fcn_00418c60();
	}
	if (g_774930 != 0) {
		fcn_0041fb80();
	}
	if (g_774934 != 0) {
		fcn_0042a0b0();
		fcn_004195f0();
	}
	fcn_0057de00();
	fcn_0042d5f0();
	gm_CleanupAllEntities();
	fcn_005b1ef0();
	fcn_004edce0();
	fcn_004acf00();
	fcn_004efcd0();
	fcn_0040bfd0();
	fcn_004c3ed0();
}
