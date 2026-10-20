/* ADDRESS: GOLDTL 0x00493000 */
/* Advances the object's state machine: state 1 starts the check, state 2
 * compares the two three-byte groups, later states sum the byte arrays and
 * compare the totals with the thresholds. */
void __cdecl fcn_00493000(unsigned char* o)
{
	int state;
	int a = 0;
	int i = 0;
	int b = 0;
	int s1 = 0;
	int s2 = 0;

	state = *(int*) (o + 8);
	if (state == 1) {
		*(int*) (o + 8) = 2;
		return;
	}
	if (state == 2) {
		if (o[0x18] == o[0x19] && o[0x18] == o[0x1a]) {
			a = o[0x18] + o[0x19] + o[0x1a];
		}
		if (o[0x3c] == o[0x3d] && o[0x3c] == o[0x3e]) {
			b = o[0x3c] + o[0x3d] + o[0x3e];
		}
		if (a > b) {
			*(int*) (o + 8) = 5;
			return;
		}
		if (b > 0) {
			*(int*) (o + 8) = 6;
			return;
		}
		if (*(int*) (o + 0x28) == 4) {
			*(int*) (o + 8) = 6;
			return;
		}
		*(int*) (o + 8) = (*(int*) (o + 0x4c) == 4) ? 5 : 3;
		return;
	}
	while (i < o[0x10]) {
		s1 += o[0x18 + i];
		i++;
	}
	for (i = 0; i < o[0x34]; i++) {
		s2 += o[0x3c + i];
	}
	if (state == 3) {
		if (s1 > 0x11) {
			*(int*) (o + 8) = 6;
			return;
		}
		if (*(int*) (o + 0x28) == 4) {
			*(int*) (o + 8) = 6;
			return;
		}
		if (*(int*) (o + 0x28) != 3 || *(int*) (o + 0x4c) != 3) {
			*(int*) (o + 8) = 4;
			return;
		}
		*(int*) (o + 8) = (s1 <= s2) ? 6 : 5;
		return;
	}
	if (state == 4) {
		if (s2 > 0x11) {
			*(int*) (o + 8) = 5;
			return;
		}
		if (*(int*) (o + 0x4c) == 4) {
			*(int*) (o + 8) = 5;
			return;
		}
		if (*(int*) (o + 0x28) != 3 || *(int*) (o + 0x4c) != 3) {
			*(int*) (o + 8) = 3;
			return;
		}
		*(int*) (o + 8) = (s1 <= s2) ? 6 : 5;
		return;
	}
	*(int*) (o + 8) = 5;
}
