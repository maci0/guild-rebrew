// FUNCTION: GOLD 0x00476700
// SIZE: 77

extern char g_00f8f120[]; /* 0x00f8f120 */
extern int g_006ed938; /* 0x006ed938 */
extern char s_005feb68[]; /* 0x005feb68 */
extern char s_005feb3c[]; /* 0x005feb3c */

void __cdecl fcn_004222b0(const char* msg);
void __cdecl fcn_004796b0(int a);

void __cdecl fcn_00476700(void)
{
	char* m;

	m = g_00f8f120 + g_006ed938 * 0x3c4;
	if (*(int*) (m + 0x280) == 0) {
		fcn_004222b0(s_005feb68);
		return;
	}
	if (*(int*) (m + 0x28) == 0) {
		fcn_004222b0(s_005feb3c);
		return;
	}
	fcn_004796b0(*(int*) (m + 0x28));
}
