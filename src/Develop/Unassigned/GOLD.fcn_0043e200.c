void __cdecl fcn_00435fb0(void*);
void __cdecl fcn_0041e100(void*, unsigned char, unsigned char, unsigned char);
float __cdecl fcn_00446990(void*, void*, void*);
void __cdecl fcn_00438840(float, float);
void __cdecl fcn_004439e0(void*, int);
void __cdecl fcn_0045c9e0(void);
char __cdecl fcn_00438d40(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
char __cdecl fcn_0043a160(char*, void*);
char __cdecl fcn_004550d0(char*, void*);
void __cdecl fcn_00455a80(char*);
void __cdecl fcn_0045d4f0(void*);
void __cdecl fcn_00452e00(void);
void __cdecl fcn_0043b600(void);

/* ADDRESS: GOLD 0x0043e200 */
void __cdecl fcn_0043e200(unsigned int pass, int overlay)
{
    char* p;
    char* next;
    char* object;
    float distance;
    float density;

    if (*(int*) 0x633b04 < 0)
        *(int*) 0x633b04 = 0;
    if (!*(unsigned char*) 0x633451 || *(int*) 0x633b04 || !*(void**) 0xfc2dec)
        return;
    *(int*) 0x633b04 = 1;
    if (*(unsigned char*) 0x633450)
        fcn_00435fb0((void*) 0xfc2930);
    else
        fcn_0041e100((void*) 0xfc2930, *(unsigned char*) 0x6334a2,
            *(unsigned char*) 0x6334a1, *(unsigned char*) 0x6334a0);
    *(int*) 0x633b08 = 0;
    *(int*) 0x633b0c = 0;
    *(float*) 0xfc5338 = 0.0f;
    *(float*) 0xfc5344 = 10000000000.0f;
    object = *(char**) 0x633448;
    *(int*) (*(char**) (object + 0x1ec) + 0x100) = 0;
    object = *(char**) 0x633448;
    *(int*) (*(char**) (object + 0x1ec) + 0xfc) = 0;
    if (*(void**) 0x633738) {
        if (*(unsigned char*) 0x6334a4 && *(unsigned char*) 0x6334a5) {
            object = *(char**) 0xfc2dec;
            distance = fcn_00446990(*(void**) 0x633738, object + 0x4c, object + 0x18c);
            if (distance < *(float*) 0xfc5340) {
                density = (1.0f - (*(float*) 0xfc5340 - distance) / *(float*) 0xfc5340)
                    * *(float*) 0xfc29bc;
                fcn_00438840(density, distance);
            } else
                fcn_00438840(*(float*) 0xfc29bc, *(float*) 0xfc5340);
        }
        fcn_004439e0(*(void**) 0x633738, overlay);
    }
    *(int*) 0x63344c = 0;
    fcn_0045c9e0();
    *(int*) 0x633498 = 0;
    *(int*) 0x633494 = 0;
    fcn_00438d40(*(char**) 0x5fb5b0, 0, pass, fcn_0043a160, 0);
    object = *(char**) 0x633448;
    if (*(int*) (*(char**) (object + 0x1ec) + 0x100) > 0 &&
        (*(unsigned char*) 0xfe7671 & 7))
        fcn_0043a160(object, 0);
    p = *(char**) 0xfb98f4;
    while (p != (char*) 0xfb9280) {
        next = *(char**) (p + 0x314);
        fcn_00455a80(p);
        p = next;
    }
    if (*(void**) 0x633dd4)
        fcn_0045d4f0(*(void**) 0x633dd4);
    if ((unsigned char) overlay)
        fcn_00452e00();
    if ((*(unsigned char*) 0xfe7670 & 0x40) && *(int*) 0x63344c &&
        *(int*) 0xfb9904 && *(int*) 0xfb9908 && (*(unsigned char*) 0xfb9928 & 1))
        fcn_00438d40(*(char**) 0x5fb5b0, 0, pass, fcn_004550d0, (void*) 0xfb9900);
    if (*(float*) 0xfc5344 == 10000000000.0f)
        *(float*) 0xfc5344 = 0.0f;
    *(int*) 0x633470 = *(int*) 0xfc2dcc;
    *(int*) 0x633488 = *(int*) 0xfe75b0;
    *(int*) 0x633474 = *(int*) 0xfc7b60;
    *(int*) 0x633484 = *(int*) 0xfc2dc4;
    object = *(char**) (*(char**) 0x633448 + 0x1cc);
    *(int*) 0x633478 = *(int*) (object + 0xc);
    fcn_0043b600();
    *(int*) 0x63347c = *(int*) 0xfe75b4;
    *(int*) 0x633480 = *(int*) 0xfc2dc0;
    --*(int*) 0x633b04;
}
