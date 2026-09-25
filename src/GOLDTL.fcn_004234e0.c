// FUNCTION: GOLD 0x00426fa0
// SIZE: 112
// FUNCTION: GOLDTL 0x004234e0
// SIZE: 112

// SIZE 0x30
typedef struct {
	int h;
	char* sample;
	int prio;
	int loop;
	int time;
	int flags;
	int f18;
	int f1c;
	int f20;
	int vol;
	int pan;
	int f2c;
} Voice;

extern int g_6b7d7c;
extern Voice g_14cbbe0;
Voice* __cdecl fcn_004229b0(void);
char* __cdecl fcn_00422530(char* bank, const char* name);
int __cdecl fcn_00423670(Voice* v, int a, int b);

Voice* __cdecl fcn_004234e0(char* bank, const char* name, int loop, int pan, int vol, int a, int b)
{
	Voice* v;

	if (g_6b7d7c == 0) {
		return &g_14cbbe0;
	}
	v = fcn_004229b0();
	if (v != 0) {
		v->sample = fcn_00422530(bank, name);
		if (v->sample != 0) {
			v->loop = loop;
			v->pan = pan;
			v->vol = vol;
			fcn_00423670(v, a, b);
		} else {
			v = 0;
		}
	}
	return v;
}
