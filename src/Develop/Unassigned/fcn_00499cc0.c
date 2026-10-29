typedef struct B18_499cc0 {
	char c0;
	char pad1[3];
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
} B18_499cc0;

int __cdecl fcn_00495400(int kind, int id, int a3, B18_499cc0* b1, B18_499cc0* b2);

/* ADDRESS: GOLDTL 0x00499cc0 */
int __cdecl fcn_00499cc0(int a1, unsigned short* a2, int a3, B18_499cc0* out1, B18_499cc0* out2)
{
	B18_499cc0 b1;
	B18_499cc0 b2;
	unsigned char* rec;
	int id;
	int i;

	if (a3 != 0) {
		return 0;
	}
	b1.f8 = 1;
	b2.f8 = 1;
	b1.c0 = 0;
	b1.f4 = 0;
	b2.c0 = 0;
	b2.f4 = 0;
	id = fcn_00495400(0x1a, *a2, 0, &b1, &b2);
	if (id != 0) {
		rec = (unsigned char*) (0x1008540 + id * 0x94);
		for (i = 0; i < 4; i++) {
			if (rec[0x30 + i * 8] == 0 && *(float*) (rec + 0x34 + i * 8) < *(float*) 0x6628a8) {
				return 0x1a;
			}
		}
		for (i = 0; i < 4; i++) {
			if (rec[0x70 + i * 8] == 0 && *(float*) (rec + 0x74 + i * 8) < *(float*) 0x6628a8) {
				return 0x1a;
			}
		}
		*out1 = b1;
		*out2 = b2;
		return id;
	}
	return 0x1a;
}
