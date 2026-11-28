

// SIZE 0x68
typedef struct {
	int d[0x1a];
} SLOT170_ACTION_BLK;

extern volatile int gm_GameTicks;

char* __cdecl gm_FindSlot170Entry(int a1);

int __cdecl gm_ExecCannonFire(int* a, int flag)
{
	SLOT170_ACTION_BLK blk;
	char* p;
	char* e;
	float x;
	float v;
	int k;
	int i;

	x = *(float*) &a[1];
	k = a[2];
	blk = *(SLOT170_ACTION_BLK*) &a[3];
	p = gm_FindSlot170Entry(a[0]);
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
				*(SLOT170_ACTION_BLK*) (e + 0x18) = blk;
				*(int*) (p + 4) |= 2;
				*(int*) (e + 0x78) = *(int*) ((char*)&gm_GameTicks);
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
