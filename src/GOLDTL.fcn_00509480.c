int __cdecl fcn_004fffb0(int a1);
char* __cdecl fcn_00508e40(int a1);

/* ADDRESS: GOLDTL 0x00509480 */
int __cdecl fcn_00509480(char* a, char* b)
{
	char* other;
	int age_diff;
	int i;
	int first;

	age_diff = (unsigned char) b[0x58] - (unsigned char) a[0x58];
	if (b[8] == 0) {
		return 0;
	}
	for (i = 0; i < 8; i++) {
		if (*(int*) (a + 0x5c + i * 4) == *(int*) (b + 4)) {
			break;
		}
	}
	if (i < 8) {
		if (i == 1 || i == 2) {
			return 0;
		}
		if (i != 0) {
			return fcn_004fffb0(*(unsigned short*) b) == 0;
		}
		first = 2;
	}
	else {
		if (age_diff != 0 || *(unsigned short*) (a + 0x50) != *(unsigned short*) (b + 0x50)) {
			return 0;
		}
		first = 3;
	}
	for (i = 3; i < 8; i++) {
		if (*(int*) (a + 0x5c + i * 4) == -1) {
			continue;
		}
		other = (char*) fcn_00508e40(*(int*) (a + 0x5c + i * 4));
		if (other != 0 && fcn_004fffb0(*(unsigned short*) other) == 0 && other[8] != 0) {
			return 0;
		}
	}
	if (first > 2) {
		other = (char*) fcn_00508e40(*(int*) (a + 0x5c));
		if (other != 0 && other[8] != 0) {
			return 0;
		}
	}
	return 1;
}
