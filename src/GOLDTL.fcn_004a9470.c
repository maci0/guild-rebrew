typedef struct Info {
	int pad0[2];
	unsigned char level;
	char pad9[0x18 - 9];
} Info;
// SIZE 0x18

int __cdecl fcn_004f6040(int* ids, int* d, unsigned short id);
char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_004e8b40(int job, Info* info);

// FUNCTION: GOLD 0x004a9350
// SIZE: 206
// FUNCTION: GOLDTL 0x4a9470
// SIZE: 206
int __cdecl fcn_004a9470(int a1, char* e, int a3, int a4, char* out)
{
	Info info;
	int d[32];
	int ids[32];
	int n;
	int i;
	int k;
	char* p;

	if (*(int*) (e + 0x194) < 2 || (*(int*) (e + 0x1c8) & 0x100)) {
		return 0;
	}
	n = fcn_004f6040(ids, d, *(unsigned short*) e);
	if (n <= 0) {
		return 0;
	}
	i = 0;
	k = n;
	do {
		if (d[i] >= 4) {
			p = fcn_00508e40(ids[i]);
			if (p && !(*(int*) (p + 0x1c8) & 0x200) && fcn_004e8b40(*(unsigned char*) (p + 0x166), &info) && info.level >= 4) {
				out[0] = 7;
				*(int*) (out + 4) = *(int*) (p + 4);
				return 1;
			}
		}
		k--;
		i = (i + 1) % n;
	} while (k);
	return 0;
}
