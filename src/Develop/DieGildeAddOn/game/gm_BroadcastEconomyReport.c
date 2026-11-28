/* DATA TODO: .data g_91abf0..g_91ac38 (floats), g_770b84 player table (stride 0x21c); verify 0x5f320c "%s%s" format arg */
#include "Develop/rebrew_types.h"
#include "Develop/rebrew_globals.h"

float __cdecl gm_GetJusticeRating(void);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl he_PostEntityMessage(int slot, int entity, char* text, int flag, int size, int extra);

/* ADDRESS: GOLD 0x004f9850 */
void __cdecl gm_BroadcastEconomyReport(void)
{
	float sum[3];
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

	if (g_current_year < 8) {
		return;
	}
	if (g_current_year % 4 != 0) {
		return;
	}
	sum[0] = ((*(float*) 0x91abf8) + (*(float*) 0x91ac0c) + (*(float*) 0x91ac20) + (*(float*) 0x91ac34)) * 0.25f;
	sum[1] = ((*(float*) 0x91abf0) + (*(float*) 0x91ac04) + (*(float*) 0x91ac18) + (*(float*) 0x91ac2c)) * 0.25f;
	sum[2] = ((*(float*) 0x91abf4) + (*(float*) 0x91ac08) + (*(float*) 0x91ac1c) + (*(float*) 0x91ac30)) * 0.25f;
	sum3 = ((*(float*) 0x91abfc) + (*(float*) 0x91ac10) + (*(float*) 0x91ac24) + (*(float*) 0x91ac38)) * 0.25f;
	lit = gm_GetJusticeRating();
	id0 = 0x1c11;
	if (!(sum[0] <= 0.15)) {
		id0 = 0x1c15;
	}
	id1 = 0x1c12;
	if (!(sum[1] <= 0.15)) {
		id1 = 0x1c16;
	}
	id2 = 0x1c13;
	if (!(lit >= 0.0)) {
		id2 = 0x1c17;
	}
	id3 = 0x1c14;
	if (!(sum[2] <= 0.15)) {
		id3 = 0x1c18;
	}
	min = sum[0];
	index = 0;
	have = 0;
	if (sum[1] > min) {
		index = 1;
	}
	min = min < sum[1] ? min : sum[1];
	if (lit > min) {
		index = 2;
	}
	min = min < lit ? min : lit;
	if (sum[2] > min) {
		index = 3;
	}
	min = min < sum[2] ? min : sum[2];
	if (min > 0.2) {
		table[0] = 0x1bf5;
		table[1] = 0x1bfb;
		table[2] = 0x1c01;
		table[3] = 0x1c07;
		if (min < 0.3) {
			index = table[index];
		}
		else if (min < 0.5) {
			index = table[index + 2];
		}
		else {
			index = table[index + 4];
		}
		io_FormatTextBuffer((char*) &table[4], (int) "%s%s", index, index + 1);
		have = 1;
	}
	if (sum3 > 0.55) {
		io_FormatTextBuffer(text, 0x1c0d, id0, id1, id2, id3, 0x1c0e);
		for (slot = (char*) 0x770b84; (int) slot < 0x7d5f84; slot += 0x21c) {
			if (*(char*) (slot - 2) == 6) {
				he_PostEntityMessage(*(int*) slot, -1, text, 1, 0x5f8, 0);
				if (have != 0) {
					he_PostEntityMessage(*(int*) slot, -1, (char*) &table[4], 0, 0x5f8, 0);
				}
			}
		}
		return;
	}
	if (sum3 < 0.45) {
		io_FormatTextBuffer(text, 0x1c0f, id0, id1, id2, id3, 0x1c10);
		for (slot = (char*) 0x770b84; (int) slot < 0x7d5f84; slot += 0x21c) {
			if (*(char*) (slot - 2) == 6) {
				he_PostEntityMessage(*(int*) slot, -1, text, 1, 0x5f8, 0);
				if (have != 0) {
					he_PostEntityMessage(*(int*) slot, -1, (char*) &table[4], 0, 0x5f8, 0);
				}
			}
		}
		return;
	}
	if (have == 0) {
		return;
	}
	for (slot = (char*) 0x770b84; (int) slot < 0x7d5f84; slot += 0x21c) {
		if (*(char*) (slot - 2) == 6) {
			he_PostEntityMessage(*(int*) slot, -1, (char*) &table[4], 0, 0x5f8, 0);
		}
	}
}
