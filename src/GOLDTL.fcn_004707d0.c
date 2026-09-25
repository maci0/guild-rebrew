extern char g_1038140[];

void __cdecl fcn_0046f540(int id);

// FUNCTION: GOLDTL 0x4707d0
// SIZE: 72
void __cdecl fcn_004707d0(int k)
{
	int j;

	for (j = 0; j < *(int*) (g_1038140 + k * 0x2bc + 0x184); j++) {
		fcn_0046f540(((int*) (g_1038140 + k * 0x2bc + 4))[j]);
	}
}
