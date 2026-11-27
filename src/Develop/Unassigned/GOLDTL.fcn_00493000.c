/* Advances the object's state machine: state 1 starts the check, state 2
 * compares the two three-byte groups, later states sum the byte arrays and
 * compare the totals with the thresholds. */
/* ADDRESS: GOLDTL 0x00493000 */
void __cdecl gm_UpdateBlackjackState(unsigned char* bj)
{
	int state;
	int s2 = 0;
	int b = 0;
	int s1 = 0;
	int i = 0;
	int a = 0;

	state = *(int*) (bj + 8);
	if (state == 1) {
		*(int*) (bj + 8) = 2;
		return;
	}
	if (state == 2) {
		if (bj[0x18] == bj[0x19] && bj[0x18] == bj[0x1a]) {
			a = bj[0x18] + bj[0x19] + bj[0x1a];
		}
		if (bj[0x3c] == bj[0x3d] && bj[0x3c] == bj[0x3e]) {
			b = bj[0x3c] + bj[0x3d] + bj[0x3e];
		}
		if (a > b) {
			goto win;

		}
		if (b > 0) {
			*(int*) (bj + 8) = 6;
			return;
		}
		if (*(int*) (bj + 0x28) == 4) {
			*(int*) (bj + 8) = 6;
			return;
		}
		*(int*) (bj + 8) = (*(int*) (bj + 0x4c) == 4) ? 5 : 3;
		return;
	}
	while (i < bj[0x10]) {
		s1 += bj[0x18 + i];
		i++;
	}
	for (i = 0; i < bj[0x34]; i++) {
		s2 += bj[0x3c + i];
	}
	if (state == 3) {
		if (s1 > 0x11) {
			goto lose;
		}
		if (*(int*) (bj + 0x28) == 4) {
			goto lose;
		}
		if (*(int*) (bj + 0x28) != 3 || *(int*) (bj + 0x4c) != 3) {
			*(int*) (bj + 8) = 4;
			return;
		}
		*(int*) (bj + 8) = (s1 <= s2) ? 6 : 5;
		return;
	}
	if (state == 4) {
		if (s2 > 0x11) {
			goto win;

		}
		if (*(int*) (bj + 0x4c) == 4) {
			goto win;

		}
		if (*(int*) (bj + 0x28) != 3 || *(int*) (bj + 0x4c) != 3) {
			*(int*) (bj + 8) = 3;
			return;
		}
		*(int*) (bj + 8) = (s1 <= s2) ? 6 : 5;
		return;
	}
	return;
lose:
	*(int*) (bj + 8) = 6;
	return;
win:
	*(int*) (bj + 8) = 5;
}
