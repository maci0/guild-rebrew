// FUNCTION: GOLD 0x004f2750
// FUNCTION: GOLDTL 0x004f4860

#pragma pack(push, 1)
typedef struct
{
	int id;
	unsigned char k;
	int v;
	char pad[3];
} Msg0c;
// SIZE 0xc
#pragma pack(pop)

int __cdecl fcn_004f4830(unsigned char k, int* info);
int __cdecl fcn_004c63f0(Msg0c* m);

int __cdecl fcn_004f4860(unsigned short* a, unsigned char k, int v)
{
	Msg0c m;
	int info[9];
	int id;

	if (!fcn_004f4830(k, info)) {
		return -1;
	}
	if (a == 0) {
		id = -1;
	} else {
		if (*a == 0xffff) {
			return -1;
		}
		id = *(int*) (a + 2);
	}
	if (v < info[1]) {
		v = info[1];
	} else if (v > info[2]) {
		v = info[2];
	}
	m.id = id;
	m.k = k;
	m.v = v;
	return fcn_004c63f0(&m);
}
