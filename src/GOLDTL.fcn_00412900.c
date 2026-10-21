typedef struct {
	unsigned char unbekannt_000;
	unsigned char bits_1;
	unsigned char unbekannt_002[6];
	unsigned char bit_8_0 : 1;
	unsigned char bit_8_1 : 1;
	unsigned char unbekannt_8_rest : 6;
	unsigned char unbekannt_009[3];
} flags_00412900;

typedef struct {
	int unbekannt_000;
	float position[3];
	char unbekannt_010[4];
	float drehung[3];
	char unbekannt_020[0x58 - 0x20];
} frame_00412900;

#include "Develop/Units/d3/d3_camera.h"

extern char* g_6b8014;
extern int g_6b5cbc;
extern int g_6b5cc0;

int* __cdecl fcn_004339e0(char* a0, flags_00412900 a1, int a2, frame_00412900* a3);

/* ADDRESS: GOLDTL 0x00412900 */
int* __cdecl fcn_00412900(char* obj, float* pos, int id)
{
	flags_00412900 flags;
	frame_00412900 frames[5];

	flags.bits_1 = 4;
	flags.bit_8_1 = 1;
	flags.bit_8_0 = 1;
	frames[0].unbekannt_000 = id;
	frames[1].unbekannt_000 = id;
	flags.unbekannt_000 = 2;
	frames[1].position[0] = *(float*) 0x67750c - *(float*) (g_6b8014 + 0x4c);
	frames[1].position[1] = *(float*) 0x677510 - *(float*) (g_6b8014 + 0x50);
	frames[1].position[2] = *(float*) 0x677514 - *(float*) (g_6b8014 + 0x54);
	frames[1].drehung[0] = pos[0] - *(float*) (g_6b8014 + 0x84);
	frames[1].drehung[1] = pos[1] - *(float*) (g_6b8014 + 0x88);
	frames[1].drehung[2] = pos[2] - *(float*) (g_6b8014 + 0x8c);
	frames[2].unbekannt_000 = id;
	frames[2].position[0] = *(float*) 0x67751c - *(float*) (g_6b8014 + 0x4c);
	frames[2].position[1] = *(float*) 0x677520 - *(float*) (g_6b8014 + 0x50);
	frames[2].position[2] = *(float*) 0x677524 - *(float*) (g_6b8014 + 0x54);
	frames[2].drehung[0] = pos[0] - *(float*) (g_6b8014 + 0x84);
	frames[2].drehung[1] = pos[1] - *(float*) (g_6b8014 + 0x88);
	frames[2].drehung[2] = pos[2] - *(float*) (g_6b8014 + 0x8c);
	frames[3].unbekannt_000 = id;
	frames[3].position[0] = *(float*) 0x67752c - *(float*) (g_6b8014 + 0x4c);
	frames[3].position[1] = *(float*) 0x677530 - *(float*) (g_6b8014 + 0x50);
	frames[3].position[2] = *(float*) 0x677534 - *(float*) (g_6b8014 + 0x54);
	frames[3].drehung[0] = pos[0] - *(float*) (g_6b8014 + 0x84);
	frames[3].drehung[1] = pos[1] - *(float*) (g_6b8014 + 0x88);
	frames[3].drehung[2] = pos[2] - *(float*) (g_6b8014 + 0x8c);
	frames[4].unbekannt_000 = id;
	frames[4].position[0] = *(float*) 0x67753c - *(float*) (g_6b8014 + 0x4c);
	frames[4].position[1] = *(float*) 0x677540 - *(float*) (g_6b8014 + 0x50);
	frames[4].position[2] = *(float*) 0x677544 - *(float*) (g_6b8014 + 0x54);
	frames[4].drehung[0] = pos[0] - *(float*) (g_6b8014 + 0x84);
	frames[4].drehung[1] = pos[1] - *(float*) (g_6b8014 + 0x88);
	frames[4].drehung[2] = pos[2] - *(float*) (g_6b8014 + 0x8c);
	g_6b5cbc = 1;
	g_6b5cc0 = (int) fcn_004339e0(obj, flags, 5, frames);
	*((unsigned char*) g_6b5cc0 + 0x2d) |= 8;
	return (int*) g_6b5cc0;
}
