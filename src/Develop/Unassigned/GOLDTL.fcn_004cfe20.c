


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
#define d2_DestroyElement d2_DestroyGuiElement
#endif
void __cdecl d2_DestroyElement(int);

void __cdecl d3_ClearActionTimers(void)
{
	int i;

	for (i = 0; i < 16; i++) {
		if (g_9b4900[i].handle != -1) {
			d2_DestroyElement(g_9b4900[i].handle);
		}
		g_9b4900[i].handle = -1;
		g_9b4900[i].ticks = 0;
		g_9b4900[i].owner = 0;
	}
}
