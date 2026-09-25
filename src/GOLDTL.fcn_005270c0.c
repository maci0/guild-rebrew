// FUNCTION: GOLDTL 0x005270c0
// SIZE: 377

// SIZE 0x3cc
typedef struct {
	char pad0[0x27c];
	int panel;
	char pad280[0x3cc - 0x280];
} Slot;

extern int g_6a25b8;
extern int g_6a2be0;
extern int g_6a25fc;
extern int g_6a2598;
extern Slot g_1015f40[];
extern int g_7ea380[15];
extern int g_6a2578;
extern int g_6a257c;
extern int g_6a2580;
extern int g_6a2584;
extern int g_6a2588;
extern int g_6a258c;
extern int g_6a259c;
extern int g_6a2590;
extern int g_6a2594;
extern int g_6a25a0;
extern int g_6a25a4;

void __cdecl fcn_00471af0(int h, int v);
void __cdecl fcn_00545a80(int v);
void __cdecl fcn_00472170(int h, int v);

void __cdecl fcn_005270c0(int show)
{
	int i;

	g_6a2be0 = show;
	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, show);
	}
	fcn_00545a80(show);
	if (g_6a25b8 != -1) {
		fcn_00471af0(g_6a25b8, show);
	}
	if (g_6a2578 != -1) {
		fcn_00472170(g_6a2578, show);
	}
	if (g_6a257c != -1) {
		fcn_00472170(g_6a257c, show);
	}
	if (g_6a2580 != -1) {
		fcn_00472170(g_6a2580, show);
	}
	if (g_6a2584 != -1) {
		fcn_00472170(g_6a2584, show);
	}
	if (g_6a2588 != -1) {
		fcn_00472170(g_6a2588, show);
	}
	if (g_6a258c != -1) {
		fcn_00472170(g_6a258c, show);
	}
	if (g_6a259c != -1) {
		fcn_00472170(g_6a259c, show);
	}
	if (g_6a2590 != -1) {
		fcn_00472170(g_6a2590, show);
	}
	if (g_6a2594 != -1) {
		fcn_00472170(g_6a2594, show);
	}
	if (g_6a25fc != -1 && show == 0) {
		fcn_00472170(g_6a25fc, show);
	}
	if (g_6a25a0 != -1) {
		fcn_00472170(g_6a25a0, show);
	}
	if (g_6a25a4 != -1) {
		fcn_00472170(g_6a25a4, show);
	}
	if (g_6a2598 != -1) {
		fcn_00472170(g_1015f40[g_6a2598].panel, show);
	}
	for (i = 0; i < 15; i++) {
		if (g_7ea380[i] != -1) {
			fcn_00472170(g_7ea380[i], show);
		}
	}
}
