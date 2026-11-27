#include "Develop/DieGildeAddOn/game/game_data.h"
extern double g_662930;
extern double g_662aa0;
extern float g_662aac;
extern float g_662ab0;
extern float g_662ab4;
extern float g_662ab8;
extern double g_662ac0;
extern float g_662ac8;
extern double g_662ad0;

int __cdecl rand(void);

typedef struct LENS_FLARE_PARTICLE {
    float f00;
    float f04;
    float f08;
    float f0c;
    float f10;
    float f14;
    float f18;
    float f1c;
    int f20;
    float f24;
    float f28;
    float f2c;
    unsigned int f30;
    float f34;
    float f38;
    float f3c;
    float f40;
    float f44;
    float f48;
    char pad4c[3];
    char f4f;
    char pad50;
    char flags;
    char pad52[2];
} LENS_FLARE_PARTICLE; /* SIZE 0x54 */

typedef struct LENS_FLARE_EMITTER {
    float f00;
    float f04;
    float f08;
    char pad0c[0x14];
    int f20;
    char pad24[4];
    LENS_FLARE_PARTICLE* particles;
    char pad2c[0xac];
    int count;
} LENS_FLARE_EMITTER; /* SIZE 0xdc */

/* ADDRESS: GOLDTL 0x004172e0 */
unsigned char __cdecl fcn_004172e0(LENS_FLARE_EMITTER* e, unsigned int t)
{
    LENS_FLARE_PARTICLE* p;
    int i;
    float dt;

    i = 0; if (e->f20 != 0) {
        p = e->particles;
        e->f20 = 0;
        for (; i < e->count; i++, p++) {
            if (!(p->flags & 1)) {
                p->f38 = (float) ((float) rand() * 3.0518509447574615e-05f * g_662ad0) - 2.0f;
                p->f3c = (float) ((float) rand() * 3.0518509447574615e-05f * g_662930) - 1.5f;
                p->f40 = (float) ((float) rand() * 3.0518509447574615e-05f * g_662ad0) - 2.0f;
                p->f00 = (float) ((float) rand() * 3.0518509447574615e-05f * g_662aa0) - 5.0f;
                p->f04 = (float) rand() * 3.0518509447574615e-05f * g_662ac8 + 0.5f;
                p->f08 = (float) ((float) rand() * 3.0518509447574615e-05f * g_662ac0) - 4.8f;
                p->f10 = (float) ((rand() & 0x7f) + 0x7f);
                p->f30 = t;
                p->flags = p->flags | 1;
                p->f48 = (float) rand() * 3.0518509447574615e-05f + 1.0f;
            }
        }
    }
    p = e->particles;
    for (i = 0; i < e->count; i++, p++) {
        if (p->flags & 1) {
            dt = (float) (t - p->f30) * 0.33333334f;
            p->f30 = t;
            p->f38 = dt * p->f00 + p->f38;
            p->f3c = dt * p->f04 + p->f3c;
            p->f40 = dt * p->f08 + p->f40;
            if (p->f3c < e->f08) {
                p->f3c = e->f08;
                p->f04 = p->f04 * -0.37f;
                p->f00 = p->f00 - p->f00 * 0.61f;
                p->f08 = p->f08 - p->f08 * 0.59f;
            } else { p->f04 = p->f04 - dt * e->f00; }
            p->f10 = p->f10 - dt * e->f04;
            if (p->f10 > 0.0) {
                p->f4f = (char) (int) p->f10;
            } else {
                p->flags = p->flags & 0xfe;
            }
        }
    }
    return 1;
}
