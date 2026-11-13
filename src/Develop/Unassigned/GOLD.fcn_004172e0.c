#include <math.h>

extern char* g_6b8014;
extern char* g_6b5cf8;
extern int g_6b7fac;
extern int SonnenstrahlenAktiv;
extern int SonnenstrahlenStartZeit;

int __cdecl CompareVector3WithinTolerance(float*, float*, float);
void __cdecl fcn_00438b40(char*, float*);
void __cdecl fcn_00438cb0(char*, float*);
char* __cdecl fcn_00449690(char*, int, char*, char*);
float __cdecl fcn_004187f0(float, float, float);
void __cdecl fcn_00417560(char*);
typedef struct SUNRAY_COLOR {
	unsigned char a, b, c, d;
} SUNRAY_COLOR;
void __cdecl fcn_0043d430(char*, char*, SUNRAY_COLOR);

/* ADDRESS: GOLD 0x004172e0 */
void __cdecl fcn_004172e0(char* object)
{
	float position[3];
	float rotation[3];
	float angle;
	float horizontal;
	double delta;
	double value;
	double vertical;
	double phase;
	char* light;
	char* camera;
	SUNRAY_COLOR color;
	if (object == 0 || *(int*) (object + 0x1cc) == 0 || g_6b8014 == 0) {
		return;
	}
	position[0] = *(float*) (g_6b8014 + 0x4c);
	position[1] = *(float*) (g_6b8014 + 0x50);
	position[2] = *(float*) (g_6b8014 + 0x54);
	if (!CompareVector3WithinTolerance(position, (float*) (object + 0x4c), 0.0001f)) {
		fcn_00438b40(object, position);
	}
	light = fcn_00449690(0, 8, 0, "pLicht");
	if (light != 0) {
		delta = (double) *(float*) (light + 0x88) - *(float*) (object + 0x88);
		if (fabs(delta) >= 0.009999999776482582) {
			rotation[0] = 0.0f;
			rotation[1] = (delta > 0.0 ? 0.0002f : -0.0002f) + *(float*) (object + 0x88);
			rotation[2] = 0.0f;
			fcn_00438cb0(object, rotation);
		}
	}
	camera = g_6b8014;
	value = fmod((double) *(float*) (object + 0x88) - *(float*) (camera + 0x88), 6.2831854820251465);
	angle = (float) value;
	if (value < 0.0) {
		angle += 6.2831855f;
	}
	value = fmod(angle, 6.2831854820251465);
	if (value > 3.1415927f) {
		value = 3.1415927f - (value - 3.1415927f);
	}
	angle = (float) value;
	horizontal = fcn_004187f0(1.0995574f, 3.1415927f, angle);
	value = fmod(*(float*) (camera + 0x84), 6.2831854820251465);
	vertical = fcn_004187f0(-1.1780972f, 0.0f, (float) fmod(value, 6.2831854820251465));
	if (SonnenstrahlenAktiv == 1) {
		phase = ((double) (unsigned int) g_6b7fac - SonnenstrahlenStartZeit) * 0.002f;
		if (phase >= 1.0) {
			SonnenstrahlenAktiv = 0;
		}
	} else if (SonnenstrahlenAktiv == -1) {
		phase = 1.0f - ((double) (unsigned int) g_6b7fac - SonnenstrahlenStartZeit) * 0.002f;
		if (phase <= 0.0f) {
			SonnenstrahlenAktiv = 0;
			fcn_00417560(object);
			g_6b5cf8 = 0;
			return;
		}
	} else {
		phase = 1.0f;
	}
	color.a = (unsigned char) (phase * vertical * horizontal * 128.0f);
	color.b = 0;
	color.c = 1;
	color.d = 0;
	fcn_0043d430(object, *(char**) (object + 0x1cc), color);
}
