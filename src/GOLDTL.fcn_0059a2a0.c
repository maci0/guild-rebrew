// FUNCTION: GOLD 0x591560
// SIZE: 150
// FUNCTION: GOLDTL 0x0059a2a0
// SIZE: 150

// SIZE 0x8
typedef struct {
	void* fn;
	int arg;
} Mode59a2;

extern char g_14cf950;
extern int g_6b8014;
extern int g_774650;
extern int g_7e35c0[];

void __cdecl fcn_0059a340(void);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_00451840(float*, float*, float);
void __cdecl fcn_00412cf0(char*, float*, float*, int, int);

void __cdecl fcn_0059a2a0(void)
{
	float v[3];
	float x;

	if (g_14cf950 == '1' && (*(char**)&g_6b8014) != 0 && ((Mode59a2*)g_7e35c0)[g_774650].fn == (void*) fcn_0059a340) {
		fcn_0057e880(0x16, 0, 0, 0);
		x = *(float*) ((*(char**)&g_6b8014) + 0x84);
		v[0] = x;
		v[1] = 0;
		x = *(float*) ((*(char**)&g_6b8014) + 0x8c);
		v[2] = x;
		if (fcn_00451840(v, (float*) ((*(char**)&g_6b8014) + 0x84), 0.1f) == 0) {
			fcn_00412cf0((*(char**)&g_6b8014), (float*) ((*(char**)&g_6b8014) + 0x4c), v, 0x1e, 0x28);
		}
	}
}
