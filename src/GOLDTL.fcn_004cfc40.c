


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
extern double g_6640e8;

void __cdecl fcn_004cfc40(char* a1, int a2, int a3)
{
	int i;

	for (i = 0; i < 16; i++) {
		if (g_9b4900[i].ticks == 0) {
			g_9b4900[i].ticks = (int) (a2 / (*(float*) (a1 + 0x1c) * g_6640e8));
			g_9b4900[i].owner = a1;
			g_9b4900[i].speed = 64.0f;
			g_9b4900[i].arg = a3;
			return;
		}
	}
}
