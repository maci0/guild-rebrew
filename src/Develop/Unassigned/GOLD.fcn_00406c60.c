int __cdecl fcn_00411be0(char*);
void __cdecl fcn_004478e0(int, int);
void __cdecl d3_DestroyObject(void*);
char* __cdecl fcn_00446e10(int, float*, float*, int);
void __cdecl fcn_00453270(char*);
void __cdecl fcn_0043d6c0(char*, char*);
extern int g_633444;
/* ADDRESS: GOLD 0x00406c60 */
void __cdecl fcn_00406c60(char* owner, int selector, int id)
{
    char** slot = 0;
    float position[4] = {0,0,0,0};
    float rotation[3] = {0,0,0};
    int previous;

    if (selector == 1) slot = (char**) (owner + 0x68);
    else if (selector == 2) slot = (char**) (owner + 0x64);
    else if (selector == 3) slot = (char**) (owner + 0x6c);
    if (id) {
        previous = g_633444;
        fcn_004478e0(fcn_00411be0(*(char**) (owner + 0x88)), 1);
        if (*slot) {
            d3_DestroyObject(*slot);
            *slot = 0;
        }
        *slot = fcn_00446e10(*(int*) (owner + 0x34), position, rotation, id);
        if (!*slot) {
            fcn_004478e0(previous, 1);
            return;
        }
        (*slot)[0x212] |= 0xc;
        (*slot)[0x211] &= ~2;
        (*slot)[0x213] &= ~4;
        *(int*) (*slot + 0x220) = 5;
        fcn_00453270(*slot);
        if (selector == 1) fcn_0043d6c0(*slot, "d3_LeftHand");
        else if (selector == 2) fcn_0043d6c0(*slot, "d3_RightHand");
        else if (selector == 3) fcn_0043d6c0(*slot, "d3_Head");
        fcn_004478e0(previous, 1);
        return;
    }
    previous = g_633444;
    fcn_004478e0(fcn_00411be0(*(char**) (owner + 0x88)), 1);
    if (*slot) {
        d3_DestroyObject(*slot);
        *slot = 0;
    }
    fcn_004478e0(previous, 1);
}
