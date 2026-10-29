


extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;
extern float g_6628a8;

float __cdecl fcn_004fbd40(void)
{
	int s1;
	int s2;
	int i;
	unsigned char* rec;
	unsigned char* t;

	s1 = 0;
	s2 = 0;
	rec = lpGebaeudeINST + 0xa9;
	for (i = 0; i < 32; i++, rec += 0xa9) {
		if (rec[0] != 0) {
			t = lpGebaeudePROT + rec[0] * 0x24d;
			s1 += t[0x247];
			s2 += t[0x248];
		}
	}
	if (s2 != 0) {
		return (float) s1 / s2;
	}
	return g_6628a8;
}
