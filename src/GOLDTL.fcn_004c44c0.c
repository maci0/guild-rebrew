// FUNCTION: GOLD 0x4c3b50
// SIZE: 80
// FUNCTION: GOLDTL 0x4c44c0
// SIZE: 65

// SIZE 0xa
typedef struct {
	unsigned char state;
	char pad[9];
} Slot10;

extern unsigned int g_100581c;
extern unsigned int g_aed204;
extern Slot10 g_fb5760[];

int __cdecl fcn_004c44c0(void)
{
	unsigned int i;
	unsigned int end;
	int r;

	i = g_100581c;
	end = g_aed204;
	r = 1;
	while (i != end) {
		if (i >= end) {
			break;
		}
		if (g_fb5760[i & 0x7fff].state == 0) {
			return 0;
		}
		if (g_fb5760[i & 0x7fff].state == 2) {
			r = -1;
		}
		i++;
		if (i >= end) {
			break;
		}
	}
	return r;
}
