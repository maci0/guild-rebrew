extern float g_6628a0;
extern float g_6628cc;
extern float g_662918;
extern float g_662930;
extern float g_662950;
extern float g_662a18;
extern float g_662a68;
extern float g_662a98;
extern float g_662aa0;
extern float g_662aac;
extern float g_662ab0;
extern float g_662ab4;
extern float g_662ab8;
extern float g_662ac0;
extern float g_662ac8;
extern float g_662acc;
extern float g_662ad0;

int __cdecl rand(void);

typedef struct fcn_004172e0_Particle {
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
    float f30;
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
} fcn_004172e0_Particle; /* SIZE 0x54 */

typedef struct fcn_004172e0_Emitter {
    float f00;
    float f04;
    float f08;
    char pad0c[0x14];
    int f20;
    char pad24[4];
    fcn_004172e0_Particle* particles;
    char pad2c[0xac];
    int count;
} fcn_004172e0_Emitter; /* SIZE 0xdc */

/* ADDRESS: GOLDTL 0x004172e0 */
int __cdecl fcn_004172e0(fcn_004172e0_Emitter* e, float t)
{
    fcn_004172e0_Particle* p;
    int i;
    float cur;
    float dt;

    if (e->f20 != 0) {
        p = e->particles;
        e->f20 = 0;
        for (i = 0; i < e->count; i++, p++) {
            if (!(p->flags & 1)) {
                p->f38 = (float) rand() * g_662a18 * g_662ad0 - g_662918;
                p->f3c = (float) rand() * g_662a18 * g_662930 - g_662acc;
                p->f40 = (float) rand() * g_662a18 * g_662ad0 - g_662918;
                p->f00 = (float) rand() * g_662a18 * g_662aa0 - g_662a98;
                p->f04 = (float) rand() * g_662a18 * g_662ac8 + g_6628cc;
                p->f08 = (float) rand() * g_662a18 * g_662ac0 - g_662ab8;
                p->f10 = (float) ((rand() & 0x7f) + 0x7f);
                p->f30 = t;
                p->flags = p->flags | 1;
                p->f48 = (float) rand() * g_662a18 + g_6628a0;
            }
        }
    }
    p = e->particles;
    for (i = 0; i < e->count; i++, p++) {
        if (p->flags & 1) {
            cur = p->f30;
            p->f30 = t;
            dt = (float) (unsigned int) ((int) t - (int) cur) * g_662a68;
            p->f38 = dt * p->f00 + p->f38;
            p->f3c = dt * p->f04 + p->f3c;
            p->f40 = dt * p->f08 + p->f40;
            if (e->f08 <= p->f3c) {
                p->f04 = p->f04 - dt * e->f04;
            } else {
                p->f3c = e->f08;
                p->f04 = p->f04 * g_662ab4;
                p->f00 = p->f00 - p->f00 * g_662ab0;
                p->f08 = p->f08 - p->f08 * g_662aac;
            }
            p->f10 = p->f10 - dt * e->f04;
            if (p->f10 <= g_662950) {
                p->flags = p->flags & 0xfe;
            } else {
                p->f4f = (char) (int) p->f10;
            }
        }
    }
    return 1;
}
