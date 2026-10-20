extern int g_7f4c00;
extern float g_6628bc;
extern float g_99ed10;
extern float g_99ed14;
extern float g_99ed18;
extern float g_99ed1c;
extern float g_99ed24;
extern float g_99ed28;
extern float g_99ed2c;
extern float g_99ed30;
extern float g_99ed38;
extern float g_99ed3c;
extern float g_99ed40;
extern float g_99ed44;
extern float g_99ed4c;
extern float g_99ed50;
extern float g_99ed54;
extern float g_99ed58;
extern double g_dbl_6628f0;
extern double g_dbl_662908;
extern double g_dbl_662950;
extern double g_dbl_664e60;
extern double g_dbl_6653d8;
extern double g_dbl_6653e0;
extern double g_dbl_6653e8;

float __cdecl fcn_004fc520(void);
void __cdecl fcn_0051af00(char* buf, int id, ...);
void __cdecl fcn_00545d40(int slot, int entity, char* text, int flag, int size, int extra);

/* ADDRESS: GOLDTL 0x004fbdd0 */
void __cdecl fcn_004fbdd0(void)
{
	float sum0;
	float sum1;
	float sum2;
	float sum3;
	float lit;
	float min;
	int id0;
	int id1;
	int id2;
	int id3;
	int table[132];
	char text[512];
	int index;
	int have;
	char* slot;

	if (g_7f4c00 < 8) {
		return;
	}
	if (g_7f4c00 % 4 != 0) {
		return;
	}
	sum0 = (g_99ed18 + g_99ed2c + g_99ed40 + g_99ed54) * g_6628bc;
	sum1 = (g_99ed10 + g_99ed24 + g_99ed38 + g_99ed4c) * g_6628bc;
	sum2 = (g_99ed14 + g_99ed28 + g_99ed3c + g_99ed50) * g_6628bc;
	sum3 = (g_99ed1c + g_99ed30 + g_99ed44 + g_99ed58) * g_6628bc;
	lit = fcn_004fc520();
	id0 = 0x1c11;
	if (g_dbl_6653e8 < sum0) {
		id0 = 0x1c15;
	}
	id1 = 0x1c12;
	if (g_dbl_6653e8 < sum1) {
		id1 = 0x1c16;
	}
	id2 = 0x1c13;
	if (lit < g_dbl_662950) {
		id2 = 0x1c17;
	}
	id3 = 0x1c14;
	if (g_dbl_6653e8 < sum2) {
		id3 = 0x1c18;
	}
	min = sum0;
	index = 0;
	if (sum1 < min) {
		min = sum1;
		index = 1;
	}
	if (lit < min) {
		min = lit;
		index = 2;
	}
	if (sum2 < min) {
		min = sum2;
		index = 3;
	}
	have = 0;
	if (min > g_dbl_6628f0) {
		table[0] = 0x1bf5;
		table[1] = 0x1bfb;
		table[2] = 0x1c01;
		table[3] = 0x1c07;
		if (min < g_dbl_664e60) {
			index = table[index];
		}
		else if (min < g_dbl_662908) {
			index = table[index + 2];
		}
		else {
			index = table[index + 4];
		}
		fcn_0051af00((char*) &table[4], 0x67728c, index, index + 1);
		have = 1;
	}
	if (sum3 > g_dbl_6653e0) {
		fcn_0051af00(text, 0x1c0d, id0, id1, id2, id3, 0x1c0e);
		for (slot = (char*) 0x7f4ca4; (int) slot < 0x85a0a4; slot += 0x21c) {
			if (*(char*) (slot - 2) == 6) {
				fcn_00545d40(*(int*) slot, -1, text, 1, 0x5f8, 0);
				if (have != 0) {
					fcn_00545d40(*(int*) slot, -1, (char*) &table[4], 0, 0x5f8, 0);
				}
			}
		}
		return;
	}
	if (sum3 < g_dbl_6653d8) {
		fcn_0051af00(text, 0x1c0f, id0, id1, id2, id3, 0x1c10);
		for (slot = (char*) 0x7f4ca4; (int) slot < 0x85a0a4; slot += 0x21c) {
			if (*(char*) (slot - 2) == 6) {
				fcn_00545d40(*(int*) slot, -1, text, 1, 0x5f8, 0);
				if (have != 0) {
					fcn_00545d40(*(int*) slot, -1, (char*) &table[4], 0, 0x5f8, 0);
				}
			}
		}
		return;
	}
	if (have == 0) {
		return;
	}
	for (slot = (char*) 0x7f4ca4; (int) slot < 0x85a0a4; slot += 0x21c) {
		if (*(char*) (slot - 2) == 6) {
			fcn_00545d40(*(int*) slot, -1, (char*) &table[4], 0, 0x5f8, 0);
		}
	}
}
