int __cdecl fcn_004fffb0(unsigned short id);
char* __cdecl gm_LookupEntityRecordById(int a1);

/* ADDRESS: GOLDTL 0x00509480 */
int __cdecl fcn_00509480(char* a, char* b)
{
	char* other; int* refs; int* p;
	int age_diff;
	int i;
	int first;

	age_diff = (unsigned char) b[0x58] - (unsigned char) a[0x58];
	if (b[8] == 0) {
		return 0;
	}
	refs = (int*) (a + 0x5c); for (i = 0, p = refs; i < 8; i++, p++) {
		if (*p == *(int*) (b + 4)) {
			break;
		}
	}
	if (i < 8) {
		if (i == 1 || i == 2) {
			return 0;
		}
		if (i == 0) {
			first = 2;
		} else
			return fcn_004fffb0(*(unsigned short*) b) == 0;
	}
	else {
		if (age_diff != 0 || *(unsigned short*) (a + 0x50) != *(unsigned short*) (b + 0x50)) {
			return 0;
		}
		first = 3;
	}
	for (i = 3, p = refs + 3; i < 8; i++, p++) {
		if (*p == -1) {
			continue;
		}
		other = (char*) gm_LookupEntityRecordById(*p);
		if (other != 0 && fcn_004fffb0(*(unsigned short*) other) == 0 && (unsigned char) other[8] > 0) {
			break;
		}
	}
	if (i < 8) return 0; if (first > 2) {
		other = (char*) gm_LookupEntityRecordById(*refs);
		if (other != 0 && (unsigned char) other[8] > 0) {
			return 0;
		}
	}
	return 1;
}
