int __cdecl fcn_004f4830(int, void*);
float __cdecl gm_RandomFloat01(void);
void __cdecl cm_RequestChangeFloat(int, int, float);
void __cdecl cm_BeginPacketFieldDelta(void*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_StepCommandQueue(void);
int __cdecl gm_TryRecordCrime(int, int, int, int, int);

extern int gm_GameTime;
extern int g_773d48;

/* Per-frame object tick: on every fourth frame, walks the object table and
 * either advances the animation of the visible objects or updates the state of
 * the objects selected by the current filter. */

/* ADDRESS: GOLDTL 0x004fd780 */
void __cdecl gm_TickObjectTable(void)
{
	char info[0x1c];
	char* p;
	int mode;
	unsigned char kind;
	int count;
	int arg;

	if ((gm_GameTime % 4) != 0) {
		return;
	}
	fcn_004f4830(2, info);
	mode = *(int*) (info + 0x18);
	if (mode == 2) {
		p = (char*) 0x7f4ca2;
		g_773d48 = 0;
		do {
			if (*(short*) (p - 2) != -1) {
				kind = *(unsigned char*) p;
				if (kind < 10 && kind > 0 && kind != 6 && kind != 7
					&& kind != 8 && *(unsigned short*) (p + 8) >= 0xc) {
					if (gm_RandomFloat01() * 0.2f > *(float*) (p + 0x1ce)) {
						count = (p[0xa] == 0);
						cm_RequestChangeFloat(*(int*) (p + 2), 0x1d0,
							gm_RandomFloat01() * 0.5f + 0.25f);
						g_773d48++;
						cm_BeginPacketFieldDelta(p - 2, *(int*) (p + 2));
						cm_AppendPacketFieldDelta(1, 1, 0xc, &count);
						cm_RequestChangeAttribute();
						g_773d48++;
						if (g_773d48 > 0x40) {
							cm_StepCommandQueue();
							g_773d48 = 0;
						}
					}
				}
			}
			p += 0x21c;
		} while ((int) p < 0x85a0a2);
		g_773d48 = 0;
		return;
	}
	g_773d48 = 0;
	p = (char*) 0x7f4ca2;
	do {
		if (*(short*) (p - 2) != -1) {
			kind = *(unsigned char*) p;
			if (kind < 10 && kind > 0 && kind != 6 && kind != 7 && kind != 8
				&& *(unsigned short*) (p + 8) >= 0xc
				&& *(unsigned char*) (p + 0xa) != (mode != 0)) {
				arg = -1;
				if (*(int*) (p + 0x16e) != 0) {
					arg = *(int*) (*(int*) (p + 0x16e) + 1);
				}
				if (gm_TryRecordCrime(2, mode == 0, *(int*) (p + 2), -1, arg) != -1) {
					g_773d48++;
				}
				if (*(float*) (p + 0x1ce) > 0.1f) {
					cm_RequestChangeFloat(*(int*) (p + 2), 0x1d0, -0.1f);
				}
				g_773d48++;
				if (g_773d48 > 0x40) {
					cm_StepCommandQueue();
					g_773d48 = 0;
				}
			}
		}
		p += 0x21c;
	} while ((int) p < 0x85a0a2);
	g_773d48 = 0;
}
