#include <math.h>

extern int d3_ActiveScene;
extern int g_772f10;
extern char* g_9b46c0[];
extern double dbl_10;
extern double g_6628d0;
extern double g_664f08;

char __cdecl d3_CollectConquerNode(char*);
int __cdecl gm_EntitiesDifferByOwnerPtr(char*, char*);
void __cdecl d3_VisitSceneObjects(char*, int, int, char(__cdecl*)(char*), char*);
void __cdecl d3_TransformPoint(char*, char*, float*);

/* ADDRESS: GOLDTL 0x004d36e0 */
char* __cdecl d3_FindNearestConquerNode(char* e)
{
    float best;
    float pos[4];
    char* res;
    char* c;
    char* parent;
    float dx;
    float dy;
    float dz;
    float d;
    int i;

    best = 1000000.0f;
    res = 0; i = 0;
    g_772f10 = 0;
    d3_VisitSceneObjects(((char*) d3_ActiveScene), 0, 0x40, d3_CollectConquerNode, e);
    c = *(char**) (*(char**) (e + 0x184) + 0x34);
    d3_TransformPoint(c, c + 0x4c, pos);
    for (; i < g_772f10; i++) {
        c = g_9b46c0[i];
        dx = pos[0] - *(float*) (c + 0x4c);
        dy = pos[1] - *(float*) (c + 0x50);
        dz = pos[2] - *(float*) (c + 0x54);
        parent = *(char**) (c + 0x204);
        d = sqrt(dz * dz + dy * dy + dx * dx);
        if (parent != 0) {
            if (gm_EntitiesDifferByOwnerPtr(e, parent) != 0) {
                d = d * 10.0;
            } else if (parent != 0) {
                if (gm_EntitiesDifferByOwnerPtr(e, parent) != 0 || parent == e) {
                    if (parent != 0) {
                        d = d * g_664f08;
                    }
                } else {
                    d = d * g_6628d0;
                }
            }
        }
        if (d < best) {
            best = d;
            res = c;
        }
    }
    if (*(char**) (res + 0x204) == e) {
        res = 0;
    }
    return res;
}
