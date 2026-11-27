#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

/* ADDRESS: GOLDTL 0x0047cf60 */
void __cdecl ai_UpdateEntityDrives(char* e)
{
    double v;
    float best;
    float* state;
    int selected;
    int i;

    v = *(float*) (e + 0x124) + *(float*) (e + 0x12c) - *(float*) (e + 0x128) * *(float*) (e + 0x12c);
    *(float*) (e + 0x12c) = (float) MIN(MAX(v, 0.0), 1000.0);
    selected = 0;
    best = 0.0f;
    for (i = 0; i < 13; i++) {
        if (i != *(unsigned char*) (e + 0x130)) {
            if (i == 1) {
                *(float*) (e + 0x9c) = 0.0f;
            } else if (i == 0) {
                if (*(int*) (e + 0x194) > 6)
                    *(float*) (e + 0x90) = 0.0f;
                else
                    goto update;
            } else if (i == 2) {
                if (*(int*) (e + 0x170) != 0 || e[2] == 3)
                    *(float*) (e + 0xa8) = 0.0f;
                else
                    goto update;
            } else if (i == 3) {
                v = *(float*) (e + 0xac) * *(float*) (e + 0x1e4) + *(float*) (e + 0xb4)
                    - *(float*) (e + 0xb0) * *(float*) (e + 0xb4);
                *(float*) (e + 0xb4) = (float) MIN(MAX(v, 0.0), 1000.0);
            } else {
update:
                state = (float*) (e + 0x90 + i * 12);
                v = *(float*) (e + 0x88 + i * 12) + *state - *(float*) (e + 0x8c + i * 12) * *state;
                *state = (float) MIN(MAX(v, 0.0), 1000.0);
            }
        }
        if (i == *(unsigned char*) (e + 0x130)) {
            v = (2.0 - *(float*) (e + 0x12c) * 0.002) * *(float*) (e + 0x90 + i * 12);
            if (v >= best) {
                best = (float) v;
                selected = i;
            }
        } else if (*(float*) (e + 0x90 + i * 12) >= best) {
            best = *(float*) (e + 0x90 + i * 12);
            selected = i;
        }
    }
    if (selected != *(unsigned char*) (e + 0x130)) {
        state = (float*) (e + 0x90 + *(unsigned char*) (e + 0x130) * 12);
        if (*state >= 1000.0f)
            *state -= 50.0f;
        e[0x130] = (unsigned char) selected;
        *(float*) (e + 0x12c) = 0.0f;
    }
}
