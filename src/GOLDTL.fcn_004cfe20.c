// FUNCTION: GOLD 0x004cefa0
// SIZE: 51
// FUNCTION: GOLDTL 0x4cfe20
// SIZE: 51

typedef struct
{
	float speed;
	int ticks;
	int handle;
	char* owner;
	int arg;
} Timer14;
// SIZE 0x14

extern Timer14 g_9b4900[16];

void __cdecl fcn_0046b2b0(int);

void __cdecl fcn_004cfe20(void)
{
	int i;

	for (i = 0; i < 16; i++) {
		if (g_9b4900[i].handle != -1) {
			fcn_0046b2b0(g_9b4900[i].handle);
		}
		g_9b4900[i].handle = -1;
		g_9b4900[i].ticks = 0;
		g_9b4900[i].owner = 0;
	}
}
