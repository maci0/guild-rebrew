// FUNCTION: GOLD 0x004ff450
// FUNCTION: GOLDTL 0x00501fe0

// SIZE 0x80
typedef struct {
	unsigned short id;
	char pad2[2];
	int active;
	char pad8[0x20 - 8];
	float base;
	float price;
	char pad28[0x38 - 0x28];
	float value;
	char pad3c[0x80 - 0x3c];
} Offer;

extern char g_85ab90[];
extern unsigned char g_773d75;

unsigned short __cdecl fcn_0042e410(int n);
float __cdecl fcn_0050b980(int id, int pct);
void __cdecl fcn_004c61d0(Offer* o, char who);

void __cdecl fcn_00501fe0(void)
{
	Offer copy;
	Offer* row;
	int n;
	int r;

	if (fcn_0042e410(2) == 0) {
		return;
	}
	for (n = fcn_0042e410(2); n > 0; n--) {
		r = fcn_0042e410(0x54);
		row = (Offer*) (g_85ab90 + g_773d75 * 0x2a90 + r * 0x80);
		if (row->id != 0 && row->active != 0) {
			copy = *row;
			if (fcn_0042e410(1) != 0) {
				copy.price = copy.base * 1.5;
				copy.value = fcn_0050b980(row->id, 100) * 1.5;
			} else {
				copy.price = copy.base * 0.5;
				copy.value = fcn_0050b980(row->id, 100) * 0.5;
			}
			fcn_004c61d0(&copy, g_773d75);
		}
	}
}
