


typedef struct {
	int p;
	int t;
} rec8;
// SIZE 0x8

extern char d3_ActiveBombs[];
extern char g_68b7b4[];
extern volatile int gm_GameTicks;

int __cdecl d3_CreateSceneModelObject(int, int, float*, char*);

rec8* __cdecl d3_SpawnBombObject(int pos)
{
	float v[3];
	int i;

	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	for (i = 0; i < 32; i++) {
		if (((rec8*)d3_ActiveBombs)[i].p == 0) {
			((rec8*)d3_ActiveBombs)[i].p = d3_CreateSceneModelObject(0, pos, v, g_68b7b4);
			((rec8*)d3_ActiveBombs)[i].t = gm_GameTicks;
			return &((rec8*)d3_ActiveBombs)[i];
		}
	}
	return 0;
}
