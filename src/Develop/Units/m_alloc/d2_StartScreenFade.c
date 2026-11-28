typedef struct Sprite {
	int a7;
	char pad4[0x44 - 4];
	int a1;
	int a2;
	int a3;
	int a4;
	int a6;
	int t0;
	int t1;
	void* tex;
} Sprite;
// SIZE 0x64

extern char* d2_OverlaySprites[];
extern volatile int tb_TimerTicks;
extern char s_67d8b0[];

void* __cdecl m_alloc(int size, const char* tag);
void* __cdecl d3_LoadTextureWithDefaultTint(int name, int a2);

/* ADDRESS: GOLDTL 0x004730c0 */
Sprite* __cdecl d2_StartScreenFade(int a1, int a2, int a3, int a4, int textureName, int a6, int a7)
{
	int i;
	Sprite* sprite;

	for (i = 0; i < 0x20; i++) {
		if (((Sprite**)d2_OverlaySprites)[i] == 0) {
			break;
		}
	}
	if (i >= 0x20) {
		return 0;
	}
	sprite = (Sprite*) m_alloc(100, s_67d8b0);
	sprite->a1 = a1;
	sprite->a2 = a2;
	sprite->a3 = a3;
	sprite->a4 = a4;
	sprite->a7 = a7;
	sprite->a6 = a6;
	sprite->tex = d3_LoadTextureWithDefaultTint(textureName, 0);
	sprite->t0 = tb_TimerTicks;
	sprite->t1 = tb_TimerTicks;
	((Sprite**)d2_OverlaySprites)[i] = sprite;
	return sprite;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_f8f0a0[94104];
#endif
