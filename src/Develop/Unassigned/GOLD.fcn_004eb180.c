char* __cdecl he_StartHandlungSearch(int, ...);
char* __cdecl he_fn_Handlung(void);
/* ADDRESS: GOLD 0x004eb180 */
int __cdecl he_QueryActionProgress(char* owner, int* id, float* fraction, int include)
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
            *fraction = (((1.0f < value) ? 1.0f : value) > 0.0f) ? ((1.0f < value) ? 1.0f : value) : 0.0f;



            return 1;
        case 150:
            rest = (float) (((double) *(int*) (event + 0xbc) -
                (double) *(int*) (event + 0xb8)) / (double) *(int*) (event + 0xbc));
            *fraction = rest;
            *fraction = (((1.0f < rest) ? 1.0f : rest) > 0.0f) ? ((1.0f < rest) ? 1.0f : rest) : 0.0f;



            *id = *(int*) (event + 0xb0);
            return 2;
        case 151:
            rest = (float) (((double) *(int*) (event + 0xbc) -
                (double) *(int*) (event + 0xb8)) / (double) *(int*) (event + 0xbc));
            *fraction = rest;
            *fraction = (((1.0f < rest) ? 1.0f : rest) > 0.0f) ? ((1.0f < rest) ? 1.0f : rest) : 0.0f;



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
