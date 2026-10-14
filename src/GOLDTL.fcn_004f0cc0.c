

// SIZE 0x68
typedef struct {
	int d[0x1a];
} Blk4f0cc0;

extern int g_6b7fac;

char* __cdecl fcn_004f0c90(int a1);

int __cdecl fcn_004f0cc0(int* a, int flag)
{
	Blk4f0cc0 blk;
	char* p;
	char* e;
	float x;
	float v;
	int k;
	int i;

	x = *(float*) &a[1];
	k = a[2];
	blk = *(Blk4f0cc0*) &a[3];
	p = fcn_004f0c90(a[0]);
	if (p != 0) {
		for (i = 0; i < 3; i++) {
			if (*(int*) (p + 0x150 + i * 4) == 0) {
				*(int*) (p + 0x150 + i * 4) = 1;
				v = *(float*) (p + 8 + k * 4) - x;
				*(float*) (p + 8 + k * 4) = v;
				if (!(v > 0.0f)) {
					v = 0.0f;
				}
				*(float*) (p + 8 + k * 4) = v;
				e = p + i * 0x68;
				*(Blk4f0cc0*) (e + 0x18) = blk;
				*(int*) (p + 4) |= 2;
				*(int*) (e + 0x78) = *(int*) ((char*)&g_6b7fac);
				*(int*) (e + 0x74) = 1;
				*(int*) (e + 0x7c) = 0;
				if (flag != 0) {
					*(int*) (p + 4) |= 1;
				}
				return 1;
			}
		}
	}
	return 0;
}
