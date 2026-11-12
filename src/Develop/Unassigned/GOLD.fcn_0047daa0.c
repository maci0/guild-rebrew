/* ADDRESS: GOLD 0x0047daa0 */
void __cdecl fcn_0047daa0(char* e)
{
    double v;
    float best;
    float* state;
    int selected;
    int i;

    v = *(float*) (e + 0x124) + *(float*) (e + 0x12c) - *(float*) (e + 0x128) * *(float*) (e + 0x12c);
    if (v < 0.0 || !(v < 1000.0))
        v = v < 0.0 ? 0.0 : 1000.0;
    *(float*) (e + 0x12c) = (float) v;
    best = 0.0f;
    selected = 0;
    for (i = 0; i < 13; i++) {
        state = (float*) (e + 0x88 + i * 12);
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
                if (v < 0.0 || !(v < 1000.0))
                    v = v < 0.0 ? 0.0 : 1000.0;
                *(float*) (e + 0xb4) = (float) v;
            } else {
update:
                v = state[0] + state[2] - state[1] * state[2];
                if (v < 0.0 || !(v < 1000.0))
                    v = v < 0.0 ? 0.0 : 1000.0;
                state[2] = (float) v;
            }
        }
        if (i == *(unsigned char*) (e + 0x130)) {
            v = (2.0 - *(float*) (e + 0x12c) * 0.002) * state[2];
            if (v >= best) {
                best = (float) v;
                selected = i;
            }
        } else if (state[2] >= best) {
            best = state[2];
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
