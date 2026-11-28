#include "Develop/DieGildeAddOn/game/game_data.h"
extern float d3_UnitAxisVectors[3];
extern void *__cdecl sub_4cef30(int);
extern void *__cdecl sub_4ce610(void *);
extern int __cdecl sub_64d41a(char *, unsigned long, int, int);
extern void *__cdecl sub_445600(int, int, int, char *);
extern int __cdecl sub_455350(void *, void *, float *);
extern char __cdecl sub_45b990(void *, float *, int *, int *, float *);
extern int __cdecl sub_407e30(void *, float *, float *, int, int, int *, int *, int, int);
extern int __cdecl sub_45b920(void *, int, int, float *);
extern int __cdecl sub_402ab0(void *, float *, int);
extern int __cdecl sub_455140(void *, float *, float *);
extern float __cdecl sub_451380(float *, float *);
extern void __cdecl sub_438cb0(void *, float *);

/* ADDRESS: GOLDTL 0x004d2c80 */
void __cdecl cut_PlaceCombatTeamAtDummies(int *arr, int teamTag)
{
    char buf[0x100]; float direction[3], position[4], rotation[3], height;
    void *floor, *actor, *dummy, *p;
    int j, v, ok, col, row, x, y, special = 1, ordinary = 1;
    unsigned long *q;

    floor = *(void **)(d3_ActiveScene + 0xb0);
    for (j = 0; j < 0x10; j++) {
        v = arr[j];
        if (v == -1)
            continue;
        actor = sub_4cef30(v);
        if (actor == 0)
            continue;
        p = sub_4ce610(actor);
        q = (unsigned long *)p;
        if (q != 0 && (*q == 0x174 || *q == 0x176 || *q == 0x15e || *q == 0x160)) {

            sub_64d41a(buf, 0x68bcd8, teamTag, special++);


        } else {
            sub_64d41a(buf, 0x68bcc4, teamTag, ordinary++);
        }
        dummy = sub_445600(0, 0x100, 0, buf);
        if (dummy == 0)
            continue;
        sub_455350(dummy, (char *)dummy + 0x4c, position);
        ok = sub_45b990(floor, position, &col, &row, &height);
        if (!ok)
            return;
        p = (char *)*(void **)((char *)*(void **)((char *)actor + 0x184) + 0x34) + 0x4c;
        sub_407e30(floor, p, p, col, row, &x, &y, 2, 0);
        sub_45b920(floor, x, y, position);
        sub_402ab0(*(void **)((char *)actor + 0x184), position, 1);
        rotation[0] = 0.0f; rotation[1] = 0.0f; rotation[2] = 0.0f; sub_455140(dummy, d3_UnitAxisVectors, direction);
        rotation[1] = sub_451380(d3_UnitAxisVectors, direction);
        sub_438cb0(*(void **)((char *)*(void **)((char *)actor + 0x184) + 0x34), rotation);
    }
    return;
}
