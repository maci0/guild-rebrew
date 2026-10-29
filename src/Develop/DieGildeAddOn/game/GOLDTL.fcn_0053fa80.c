/* Global shutdown of the game runtime. */

extern int g_6b5c60;
extern int g_538060;
extern int g_7725c8;
extern int g_772f3c;
extern int g_7749cc;
extern int g_774934;
extern int g_7747bc;
extern int g_7747c0;
extern int g_7747c4;
extern int g_7747c8;
extern int g_7747cc;
extern int g_6b5c2c;
extern int g_7e453c;
extern int g_7e4538;
extern int g_6b89c0;
extern char g_6b8061;
extern int g_6b5cf8;
extern int g_6b5cc0;
extern int g_77497c;
extern int g_7e2aa0;
extern int g_7746cc;
extern int g_7746c4;
extern int g_7746c8;

void __cdecl fcn_00533880(void);
void __cdecl fcn_00475220(void* p);
void __cdecl fcn_00533a40(void* p);
void __cdecl fcn_0042def0(void* p);
void __cdecl fcn_004298e0(void);
void __cdecl fcn_0044c440(int p);
void __cdecl fcn_004c09b0(void);
void __cdecl fcn_00418f50(void);
void __cdecl fcn_004230e0(int p);
void __cdecl fcn_004b1f80(void);
void __cdecl fcn_004b3b60(void);
void __cdecl fcn_00545510(void);
void __cdecl fcn_00545930(void);
void __cdecl fcn_00545550(void);
void __cdecl fcn_00527420(void);
void __cdecl gm_KillAllSpieler(void);
void __cdecl gm_ResetAllEntities(void);
void __cdecl gm_CleanupObjectEntities(void);
void __cdecl fcn_004030e0(int p);
void __cdecl fcn_004162c0(int p);
void __cdecl fcn_004154e0(int p);
void __cdecl fcn_004597f0(int a, int b);
void __cdecl fcn_00459b40(int a);
void __cdecl fcn_00418ae0(int p);
void __cdecl fcn_00510930(void);
void __cdecl fcn_005c80d0(void);
void __cdecl fcn_004bbd50(void);
void __cdecl fcn_004c3e30(void);
void __cdecl fcn_00402320(void);
void __cdecl fcn_00421050(void);
void __cdecl fcn_00473a90(int a, int b);

/* ADDRESS: GOLDTL 0x0053fa80 */
void __cdecl fcn_0053fa80(void)
{
    register int _dummy_reg_88 = 0;
    register int _dummy_reg_63 = 0;
    register int _dummy_reg_14 = 0;
	int* entry;

	fcn_00533880();
	fcn_00475220(&g_6b5c60);
	fcn_00533a40(&g_6b5c60);
	g_7725c8 = 1;
	fcn_0042def0(&g_538060);
	g_772f3c = 0;
	fcn_004298e0();
	if (g_7749cc != 0) {
		fcn_0044c440(g_7749cc);
	}
	if (g_774934 != 0) {
		fcn_004c09b0();
		fcn_00418f50();
		if (g_7747bc != 0) {
			fcn_004230e0(g_7747bc);
			g_7747bc = 0;
			fcn_004230e0(g_7747c0);
			g_7747c0 = 0;
			fcn_004230e0(g_7747c4);
			g_7747c4 = 0;
			fcn_004230e0(g_7747c8);
			g_7747c8 = 0;
			fcn_004230e0(g_7747cc);
			g_7747cc = 0;
			fcn_004230e0(g_6b5c2c);
			g_6b5c2c = 0;
		}
	}
	fcn_004b1f80();
	fcn_004b3b60();
	fcn_00545510();
	fcn_00545930();
	fcn_00545550();
	fcn_00527420();
	gm_KillAllSpieler();
	gm_ResetAllEntities();
	gm_CleanupObjectEntities();
	for (entry = (int*) 0x14d0020; (int) entry < 0x14d0c20; entry++) {
		if (*entry != 0) {
			fcn_004030e0(*entry);
		}
	}
	if (g_7e453c != 0) {
		((int (*)(char)) fcn_004162c0)(g_7e453c);
		g_7e453c = 0;
	}
	if (g_7e4538 != 0) {
		fcn_004154e0(g_7e4538);
		g_7e4538 = 0;
	}
	if (g_6b89c0 != 0) {
		for (entry = (int*) 0x7e4540; (int) entry < 0x7e4558; entry++) {
			if (*entry != 0) {
				fcn_004597f0(g_6b89c0, *entry);
				*entry = 0;
			}
		}
		fcn_00459b40(g_6b89c0);
		g_6b89c0 = 0;
	}
	g_6b8061 = 0;
	if (g_6b5cf8 != 0) {
		fcn_00418ae0(g_6b5cf8);
		g_6b5cf8 = 0;
	}
	g_6b5cc0 = 0;
	fcn_00510930();
	fcn_005c80d0();
	fcn_004bbd50();
	fcn_004c3e30();
	fcn_00402320();
	fcn_00421050();
	g_77497c = 0;
	fcn_00473a90(0, 0);
	g_7e2aa0 = 0;
	g_7746cc = 0;
	g_7746c4 = 0;
	g_7746c8 = 0;
}
