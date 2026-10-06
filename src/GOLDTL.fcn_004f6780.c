// FUNCTION: GOLD 0x4f4390
// FUNCTION: GOLDTL 0x004f6780

#pragma pack(push, 1)
typedef struct
{
	int id;
	char p4[0xe];
	int x12;
	int x16;
	char p1a[2];
	unsigned char x1c;
	char p1d[8];
	unsigned int x25;
	char p29[4];
} Rec2d;
// SIZE 0x2d
#pragma pack(pop)

void __cdecl fcn_004f6780(int n, Rec2d* arr)
{
	Rec2d tmp;
	int i;
	int j;

	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (arr[i].x1c > arr[j].x1c) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}
