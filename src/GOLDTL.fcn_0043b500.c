typedef struct Named24 {
	char name[0x20];
	int value;
} Named24;
// SIZE 0x24

extern Named24 g_67a470[8];

int __cdecl fcn_0065f220(const char* a, const char* b);

// FUNCTION: GOLD 0x0043e6c0
// SIZE: 68
// FUNCTION: GOLDTL 0x43b500
// SIZE: 68
int __cdecl fcn_0043b500(const char* name)
{
	unsigned int i;

	for (i = 0; i < 8; i++) {
		if (fcn_0065f220(name, g_67a470[i].name) == 0) {
			return g_67a470[i].value;
		}
	}
	return 0;
}
