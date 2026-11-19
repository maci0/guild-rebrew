


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

void __cdecl fcn_004cfc40(char* owner, int a2, int arg)
{
	int i;

	for (i = 0; i < 16; i++) {
		if (g_9b4900[i].ticks == 0) {
			g_9b4900[i].ticks = (int) (a2 / (*(float*) (owner + 0x1c) * 0.01));
			g_9b4900[i].owner = owner;
			g_9b4900[i].speed = 64.0f;
			g_9b4900[i].arg = arg;
			return;
		}
	}
}
