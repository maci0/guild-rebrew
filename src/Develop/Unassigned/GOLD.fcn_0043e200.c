void __cdecl d3_ClearViewport(void*);
void __cdecl d3_ClearSoftwareViewport(void*, unsigned char, unsigned char, unsigned char);
float __cdecl d3_CalcFloorFogDistance(void*, void*, void*);
void __cdecl d3_SetFogRange(float, float);
void __cdecl d3_RenderFloor(void*, int);
void __cdecl d3_CollectFlaggedObjects(void);
char __cdecl d3_VisitSceneObjectsUntilStopped(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
char __cdecl d3_RenderSceneObject(char*, void*);
char __cdecl d3_RenderMirroredObject(char*, void*);
void __cdecl d3_UpdateAndRenderEffect(char*);
void __cdecl fcn_0045d4f0(void*);
void __cdecl d3_UpdateSceneOverlayObjects(void);
void __cdecl d3_FlushRenderQueues(void); extern float g_5ebaa4;
#include "client_lighting.h"
#include "Develop/Units/d3/d3_camera.h"
/* ADDRESS: GOLD 0x0043e200 */
void __cdecl d3_RenderScene(unsigned int pass, int overlay)
{
    char* p;
    char* next;
    char* object;
    unsigned char c633450;
    float distance;
    float density;
    if (g_6b86d4 < 0)
        g_6b86d4 = 0;
    if (!*(unsigned char*) 0x633451 || g_6b86d4 || !d3_ActiveCamera)
        return;
    c633450 = *(unsigned char*) 0x633450;
    g_6b86d4 = 1;
    if (c633450)
        d3_ClearViewport((void*) 0xfc2930);
    else
        d3_ClearSoftwareViewport((void*) 0xfc2930, *(unsigned char*) 0x6334a2,
            *(unsigned char*) 0x6334a1, *(unsigned char*) 0x6334a0);
    *(int*) 0x633b08 = 0;
    *(int*) 0x633b0c = 0;
    *(float*) 0xfc5338 = 0.0f;
    *(float*) 0xfc5344 = 10000000000.0f;
    object = *(char**) 0x633448;
    *(int*) (*(char**) (object + 0x1ec) + 0x100) = 0;
    object = *(char**) 0x633448;
    *(int*) (*(char**) (object + 0x1ec) + 0xfc) = 0;
    if ((void*) g_6b8300) {
        if (*(unsigned char*) 0x6334a4 && *(unsigned char*) 0x6334a5) {
            object = d3_ActiveCamera;
            distance = d3_CalcFloorFogDistance((void*) g_6b8300, object + 0x4c, object + 0x18c);
            if (distance < *(float*) 0xfc5340) {
                density = (1.0f - (*(float*) 0xfc5340 - distance) / *(float*) 0xfc5340)
                    * *(float*) 0xfc29bc;
                d3_SetFogRange(density, distance);
            } else
                d3_SetFogRange(*(float*) 0xfc29bc, *(float*) 0xfc5340);
        }
        d3_RenderFloor((void*) g_6b8300, overlay);
    }
    *(int*) 0x63344c = 0;
    d3_CollectFlaggedObjects();
    *(int*) 0x633498 = 0;
    *(int*) 0x633494 = 0;
    d3_VisitSceneObjectsUntilStopped(*(char**) 0x5fb5b0, 0, pass, d3_RenderSceneObject, 0);
    object = *(char**) 0x633448;
    if (*(int*) (*(char**) (object + 0x1ec) + 0x100) > 0 &&
        (*(unsigned char*) 0xfe7671 & 7))
        d3_RenderSceneObject(object, 0);
    p = *(char**) 0xfb98f4;
    while (p != (char*) 0xfb9280) {
        next = *(char**) (p + 0x314);
        d3_UpdateAndRenderEffect(p);
        p = next;
    }
    if (*(void**) 0x633dd4)
        fcn_0045d4f0(*(void**) 0x633dd4);
    if ((unsigned char) overlay)
        d3_UpdateSceneOverlayObjects();
    if ((*(unsigned char*) 0xfe7670 & 0x40) && *(int*) 0x63344c &&
        *(int*) 0xfb9904 && *(int*) 0xfb9908 && (*(unsigned char*) 0xfb9928 & 1))
        d3_VisitSceneObjectsUntilStopped(*(char**) 0x5fb5b0, 0, pass, d3_RenderMirroredObject, (void*) 0xfb9900);
    if (*(float*) 0xfc5344 == g_5ebaa4)
        *(float*) 0xfc5344 = 0.0f;
    *(int*) 0x633470 = *(int*) 0xfc2dcc;
    *(int*) 0x633488 = *(int*) 0xfe75b0;
    *(int*) 0x633474 = *(int*) 0xfc7b60;
    *(int*) 0x633484 = *(int*) 0xfc2dc4;
    object = *(char**) (*(char**) 0x633448 + 0x1cc);
    *(int*) 0x633478 = *(int*) (object + 0xc);
    d3_FlushRenderQueues();
    *(int*) 0x63347c = *(int*) 0xfe75b4;
    *(int*) 0x633480 = *(int*) 0xfc2dc0;
    --g_6b86d4;
}
