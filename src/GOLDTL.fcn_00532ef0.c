// FUNCTION: GOLDTL 0x00532ef0
// FUNCTION: GOLD 0x0052d7d0

// SIZE 0x90
typedef struct {
	char pad0[0x4c];
	float pos[3];
	char pad58[0x84 - 0x58];
	float rot[3];
} View;

extern int g_6b5cc0;
extern int g_6b5cbc;
extern float g_14ce880[3];
extern float g_7e3a40[3];
extern float g_7e3a50[3];
extern int g_6b8014;
extern int g_774650;
extern int g_774654;
extern int g_774658;
extern int g_77465c;
extern char* g_7746a8;
extern int g_7e2a9c;

int __cdecl fcn_00451840(float* a, float* b, float eps);
void __cdecl fcn_00433780(View* v);
void __cdecl fcn_00438b40(View* v, float* p);
void __cdecl fcn_00438cb0(View* v, float* r);
void __cdecl fcn_0052d820(void);
void __cdecl fcn_00530510(void);

void __cdecl fcn_00532ef0(void)
{
	int done;
	char* e;

	done = 0;
	if (g_6b5cc0 != 0) {
		if (fcn_00451840(g_14ce880, g_7e3a40, 0.1f)) {
			fcn_00433780(((View*)g_6b8014));
			g_6b5cc0 = 0;
			g_6b5cbc = 0;
			done = 1;
			fcn_00438b40(((View*)g_6b8014), g_7e3a40);
			fcn_00438cb0(((View*)g_6b8014), g_7e3a50);
		} else {
			fcn_00433780(((View*)g_6b8014));
			g_6b5cc0 = 0;
			g_6b5cbc = 0;
		}
	}
	if (g_774650 > g_774658 && done == 0) {
		if (g_77465c >= g_774650 - g_774654) {
			fcn_0052d820();
			g_77465c = g_774650 - g_774654;
			if (g_7746a8 != 0) {
				e = *(char**) (g_7746a8 + 0x1d4);
				if (e != 0 && *(void**) (e + 0x18c) != 0) {
					(*(void(__cdecl**)(char*, int, char*, int)) (e + 0x18c))(g_7746a8, 3, e + 0x190, 0);
				}
				g_7746a8 = 0;
			}
			if (g_7e2a9c != 0) {
				fcn_00530510();
			}
		}
	} else if ((!fcn_00451840(((View*)g_6b8014)->rot, g_7e3a50, 0.1f) || !fcn_00451840(((View*)g_6b8014)->pos, g_7e3a40, 0.1f)) &&
		   done == 0) {
		fcn_0052d820();
		if (g_7746a8 != 0) {
			e = *(char**) (g_7746a8 + 0x1d4);
			if (e != 0 && *(void**) (e + 0x18c) != 0) {
				(*(void(__cdecl**)(char*, int, char*, int)) (e + 0x18c))(g_7746a8, 3, e + 0x190, 0);
			}
			g_7746a8 = 0;
		}
	}
	if (g_7e2a9c != 0) {
		fcn_00530510();
	}
}
