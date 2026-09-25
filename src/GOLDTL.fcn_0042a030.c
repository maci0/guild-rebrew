// FUNCTION: GOLDTL 0x0042a030
// SIZE: 53
// SIZE 0xc98
typedef struct {
	char used;
	char pad1[0xff];
	int owner;
	char pad2[0x20];
	unsigned char flags;
	char pad3[0xc98 - 0x125];
} E42a030;

extern E42a030* g_6b7e94;

int __cdecl fcn_0042a030(void)
{
	int n;
	int i;
	E42a030* e;

	n = 0;
	e = g_6b7e94;
	for (i = 0; i < 0x80; i++) {
		if ((e[i].used != 0 && e[i].owner != -1) || (e[i].flags & 1)) {
			n++;
		}
	}
	return n;
}
