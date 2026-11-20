char* __cdecl he_StartHandlungSearch(int, ...);
char* __cdecl he_fn_Handlung(void);
/* ADDRESS: GOLD 0x004eb180 */
int __cdecl fcn_004eb180(char* owner, int* id, float* fraction, int include)
{
    char* event;
    float value;
    float rest;
    event = he_StartHandlungSearch(1, 3, *(int*) (owner + 1));
    while (event) {
        switch (*(unsigned char*) event) {
        case 149:
            value = (float) (((double) *(int*) (event + 0xb8) -
                (double) *(int*) (event + 0xb4)) / (double) *(int*) (event + 0xb8));
            *fraction = value;
            if (!(1.0f > value)) *fraction = 1.0f;
            else if (!(value > 0.0f)) *fraction = 0.0f;
            else if (!(1.0f > value)) *fraction = 1.0f;
            return 1;
        case 150:
            rest = (float) (((double) *(int*) (event + 0xbc) -
                (double) *(int*) (event + 0xb8)) / (double) *(int*) (event + 0xbc));
            *fraction = rest;
            if (!(1.0f > rest)) *fraction = 1.0f;
            else if (!(rest > 0.0f)) *fraction = 0.0f;
            else if (!(1.0f > rest)) *fraction = 1.0f;
            *id = *(int*) (event + 0xb0);
            return 2;
        case 151:
            rest = (float) (((double) *(int*) (event + 0xbc) -
                (double) *(int*) (event + 0xb8)) / (double) *(int*) (event + 0xbc));
            *fraction = rest;
            if (!(1.0f > rest)) *fraction = 1.0f;
            else if (!(rest > 0.0f)) *fraction = 0.0f;
            else if (!(1.0f > rest)) *fraction = 1.0f;
            *id = *(int*) (event + 0xb0);
            return 3;
        case 4:
            if (!include) return 0;
            *fraction = 0.0f;
            *id = 0;
            return 4;
        }
        event = he_fn_Handlung();
    }
    return 0;
}
