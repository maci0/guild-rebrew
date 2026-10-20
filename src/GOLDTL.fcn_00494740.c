#include <string.h>

extern float g_664320;
extern float g_662a3c;
extern float g_6628a0;

float __cdecl fcn_00507e70(char* a, char* b, int c);
float __cdecl fcn_0042e450(void);
int __cdecl fcn_004fa5b0(int a1, char* a2, int a3);

/* ADDRESS: GOLDTL 0x00494740 */
int __cdecl fcn_00494740(int a0, int entity, int* level_out, int unused)
{
	float v;
	float w;
	int level;

	v = fcn_00507e70((char*) a0, (char*) entity, 3);
	w = fcn_0042e450() + v;
	{
		float f = 0.0f;
		int buf[0x88];

		level = 0x3b;
		memset(buf, 0, sizeof(buf));
		buf[0] = 1;
		if ((fcn_004fa5b0(0xd, (char*) entity, (int) buf) & 2) != 0) {
			f = g_664320;
			level = 0xd;
		}
		else if ((fcn_004fa5b0(0xa, (char*) entity, (int) buf) & 2) != 0) {
			f = g_662a3c;
			level = 0xa;
		}
		if (level_out != 0) {
			*level_out = level;
		}
		return (w + f) > g_6628a0;
	}
}
