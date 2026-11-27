

unsigned short __cdecl gm_RandomMod(int n);
void __cdecl d3_ScheduleActionTimer(char* o, int a, int b);
int __cdecl cut_HandleUnitDefeat(char* o);
void __cdecl d3_SpawnBlutEffect(int h, int n, float a, float b, float c, float d);
int __cdecl cut_RandMod(int n);
void __cdecl ch_QueuePlayAnimation(char* o, char* anim, int loop);

void __cdecl cut_PlayHitReaction(char* o)
{
	char anims[2][32] = { "kampf/arm_greifen", "kampf/bauch_greifen" };

	d3_ScheduleActionTimer(o, 0, 0);
	*(int*) (o + 0x24) += -40 - gm_RandomMod(60);
	if (cut_HandleUnitDefeat(o) == 0) {
		d3_SpawnBlutEffect(*(int*) (*(char**) (o + 0x184) + 0x34), 0x40, 0.25f, 0.1f, 0.14f, 55.0f);
		if (*(int*) (*(char**) (o + 0x184) + 0x128) == 0) {
			ch_QueuePlayAnimation(*(char**) (o + 0x184), anims[cut_RandMod(2)], 1);
		}
	}
}
