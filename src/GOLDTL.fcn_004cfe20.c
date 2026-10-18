


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

#ifdef REBREW_GOLD
#define fcn_0046b2b0 fcn_0046e700
#endif
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
