/* Inferred function/type names and unit. Native options and frames are only
 * partly initialized; untouched bytes remain unknown. Globals are declaration views. */
typedef struct {
    unsigned char unbekannt_000;
    unsigned char bit_1_0 : 1;
    unsigned char bit_1_1 : 1;
    unsigned char bit_1_2 : 1;
    unsigned char bit_1_3 : 1;
    unsigned char bit_1_4 : 1;
    unsigned char unbekannt_1_rest : 3;
    unsigned char unbekannt_002[6];
    unsigned char bit_8_0 : 1;
    unsigned char bit_8_1 : 1;
    unsigned char unbekannt_8_rest : 6;
    unsigned char unbekannt_009[3];
} D3_OBJ_ANIM_FLAGS;

typedef struct {
    int unbekannt_000;
    float position[3];
    char unbekannt_010[4];
    float drehung[3];
    char unbekannt_020[0x58 - 0x20];
} D3_OBJ_ANIM_FRAME;

/* ADDRESS: GOLDTL 0x006b5cbc */
extern int g_6b5cbc;
/* ADDRESS: GOLDTL 0x006b5cc0 */
extern int g_6b5cc0;
#include "Develop/Units/d3/d3_camera.h"
int __cdecl fcn_004339e0(char*, D3_OBJ_ANIM_FLAGS, int, D3_OBJ_ANIM_FRAME*);

/* ADDRESS: GOLDTL 0x00412d30 */
int __cdecl StartObjectTransformAnimation(char* objekt, float x, float y, float z,
                                         float rx, float ry, float rz, int parameter)
{
    D3_OBJ_ANIM_FRAME frames[2];
    D3_OBJ_ANIM_FLAGS flags;
    int ergebnis;

    if (g_6b5cbc != 0 && objekt == g_6b8014) {
        return 0;
    }
    flags.bit_1_4 = 1;
    flags.bit_1_2 = 1;
    flags.bit_8_1 = 1;
    flags.bit_1_3 = 0;
    flags.bit_1_0 = 0;
    frames[0].unbekannt_000 = parameter;
    frames[1].drehung[0] = rx;
    frames[1].drehung[1] = ry;
    frames[1].drehung[2] = rz;
    frames[1].position[0] = x;
    frames[1].position[1] = y;
    frames[1].position[2] = z;
    frames[0].drehung[0] = 0.0f;
    frames[0].drehung[1] = 0.0f;
    frames[0].drehung[2] = 0.0f;
    frames[0].position[0] = 0.0f;
    frames[0].position[1] = 0.0f;
    frames[0].position[2] = 0.0f;
    ergebnis = fcn_004339e0(objekt, flags, 2, frames);
    if (objekt == g_6b8014) {
        g_6b5cbc = 1;
        g_6b5cc0 = ergebnis;
    }
    return 1;
}
