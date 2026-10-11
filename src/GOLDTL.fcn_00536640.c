// FUNCTION: GOLDTL 0x00536640

unsigned short __cdecl gm_RandomMod(int n);
void __cdecl fcn_004cfc40(char* o, int a, int b);
int __cdecl fcn_004d4790(char* o);
void __cdecl fcn_00417b50(int h, int n, float a, float b, float c, float d);
int __cdecl fcn_004e6cb0(int n);
void __cdecl fcn_00406340(char* o, char* anim, int loop);

void __cdecl fcn_00536640(char* o)
{
	char anims[2][32] = { "kampf/arm_greifen", "kampf/bauch_greifen" };

	fcn_004cfc40(o, 0, 0);
	*(int*) (o + 0x24) += -40 - gm_RandomMod(60);
	if (fcn_004d4790(o) == 0) {
		fcn_00417b50(*(int*) (*(char**) (o + 0x184) + 0x34), 0x40, 0.25f, 0.1f, 0.14f, 55.0f);
		if (*(int*) (*(char**) (o + 0x184) + 0x128) == 0) {
			fcn_00406340(*(char**) (o + 0x184), anims[fcn_004e6cb0(2)], 1);
		}
	}
}
