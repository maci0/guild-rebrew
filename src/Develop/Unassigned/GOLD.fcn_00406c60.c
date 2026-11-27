int __cdecl fcn_00411be0(char*);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_DestroyObject(void*);
char* __cdecl d3_SpawnModelObject(int, float*, float*, int);
void __cdecl d3_UpdateObjectLighting(char*);
void __cdecl d3_AttachObjectBone(char*, char*);
extern int g_633444;
/* ADDRESS: GOLD 0x00406c60 */
void __cdecl ch_SetAttachedObject(char* owner, int selector, int id)
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
        d3_SelectSceneContext(fcn_00411be0(*(char**) (owner + 0x88)), 1);
        if (*slot) {
            d3_DestroyObject(*slot);
            *slot = 0;
        }
        *slot = d3_SpawnModelObject(*(int*) (owner + 0x34), position, rotation, id);
        if (!*slot) {
            d3_SelectSceneContext(previous, 1);
            return;
        }
        (*slot)[0x212] |= 0xc;
        (*slot)[0x211] &= ~2;
        (*slot)[0x213] &= ~4;
        *(int*) (*slot + 0x220) = 5;
        d3_UpdateObjectLighting(*slot);
        if (selector == 1) d3_AttachObjectBone(*slot, "d3_LeftHand");
        else if (selector == 2) d3_AttachObjectBone(*slot, "d3_RightHand");
        else if (selector == 3) d3_AttachObjectBone(*slot, "d3_Head");
        d3_SelectSceneContext(previous, 1);
        return;
    }
    previous = g_633444;
    d3_SelectSceneContext(fcn_00411be0(*(char**) (owner + 0x88)), 1);
    if (*slot) {
        d3_DestroyObject(*slot);
        *slot = 0;
    }
    d3_SelectSceneContext(previous, 1);
}
