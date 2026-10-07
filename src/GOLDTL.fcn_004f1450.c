// FUNCTION: GOLDTL 0x004f1450

typedef struct
{
	int id;
	char pad4[0x20];
	unsigned char b[5];
	char pad29[0x1b];
} Rec44;
// SIZE 0x44

int __cdecl fcn_004f1450(Rec44* arr, int n)
{
	Rec44* best;
	int bestsum;
	int sum;
	int i;
	int j;
	int result;

	result = -1;
	best = 0;
	bestsum = 0;
	for (i = 0; i < n; i++) {
		if (arr[i].id != -1) {
			if (best == 0) {
				best = &arr[i];
				for (j = 0; j < 5; j++) {
					bestsum += arr[i].b[j];
				}
			} else {
				sum = 0;
				for (j = 0; j < 5; j++) {
					sum += arr[i].b[j];
				}
				if (sum > bestsum) {
					best = &arr[i];
					bestsum = sum;
				}
			}
		}
	}
	if (best != 0) {
		result = best->id;
	}
	return result;
}
