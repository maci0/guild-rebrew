// FUNCTION: GOLDTL 0x005b1aa0
// SIZE: 102

// SIZE 0x15
typedef struct {
	char key;
	char rest[0x14];
} Entry;

extern Entry g_666044[];
extern Entry g_699058[];

Entry* __cdecl fcn_005b1aa0(char* c)
{
	int i;

	if (*c == 0x20 || *c == 0x1e || *c == 0x1f) {
		for (i = 0; i < 3; i++) {
			if (g_666044[i].key == *c) {
				return &g_666044[i];
			}
		}
	}
	for (i = 0; i < 37; i++) {
		if (g_699058[i].key == *c) {
			return &g_699058[i];
		}
	}
	return 0;
}
