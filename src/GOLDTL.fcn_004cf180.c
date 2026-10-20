extern unsigned int g_6b7fac;    /* 0x6b7fac */
extern char* g_772ec4;           /* 0x772ec4 */
extern unsigned short* g_772e9c; /* 0x772e9c, entity pointer */
extern double g_6640e8;          /* 0.01 */
extern float g_664ed0;           /* 1/170 */
extern float g_664ed4;           /* 170.0 */
extern double g_6629c8;          /* 1.0 */

int __cdecl fcn_004ce590(int a1);
int* __cdecl fcn_004234e0(char* bank, const char* name, int loop, int pan,
                          int vol, int a, int b);
int __cdecl fcn_00418000(int a1, float* pos, int n, float a4, float a5,
                         float a6, float a7, float a8, float a9, float* a10,
                         int a11, int a12, int a13);
int __cdecl fcn_004185a0(int a1, float* pos, int n, float a4, float a5,
                         float a6, float a7, float a8, float a9, float a10,
                         float a11, int a12);
int __cdecl fcn_00417d00(int a1, float* pos, int n, float a4, float a5,
                         float a6, float a7, int a8);
unsigned int __cdecl fcn_004e6cb0(unsigned int n);
void __cdecl fcn_004cfc40(char* a1, int a2, int a3);
int __cdecl fcn_004d4790(char* e);
int __cdecl fcn_00406340(char* e, const char* name, int param);
char __cdecl d3_DestroyObject(void* object);
double __cdecl sqrt(double x);

/* ADDRESS: GOLDTL 0x004cf180 */
int __cdecl fcn_004cf180(void)
{
    char* r;
    int count;
    int* p;
    int* q;
    int obj;
    int e;
    int m;
    int node;
    int t;
    int d;
    int flag;
    float v[8];
    float dist;
    float dx;
    float dy;
    float dz;
    unsigned char color[4];

    count = 0;
    r = (char*) fcn_004ce590(0x174);
    p = (int*) 0x9ba1c0;
    do {
        if (*p != 0) {
            count++;
            if ((unsigned int) (p[1] + 0x15e) < g_6b7fac) {
                v[0] = -243.0f;
                v[1] = -90.0f;
                v[2] = 190.0f;
                v[3] = 0.0f;
                v[4] = -50.0f;
                v[5] = 0.0f;
                v[6] = 38.0f;
                v[7] = 0.0f;
                fcn_004234e0(g_772ec4, "kampf/bauch_greifen", 1, 0x3f, 0x7f,
                             0, 0);
                obj = *p;
                v[0] = *(float*) (obj + 0x4c);
                v[1] = *(float*) (obj + 0x50);
                v[2] = *(float*) (obj + 0x54);
                color[2] = 0xc0;
                color[1] = 0xc0;
                color[0] = 0xc0;
                color[3] = 0x3f;
                fcn_00418000(0, v, 0x1e, 15.0f, 50.0f, 100.0f, 150.0f,
                             140.0f, 35.0f, &v[3], 0x190, 6,
                             *(int*) color);
                fcn_004185a0(0, v, 0x1e, 5.0f, 2.5f, 1.0f, 3.0f, -3.0f,
                             4.0f, 7.0f, 8.0f, *(int*) color);
                fcn_00417d00(0, v, 0x1e, 120.0f, 85.0f, 20.0f, 60.0f, 0x3c);
                for (q = (int*) 0x7e4260; q < (int*) 0x7e42e0; q++) {
                    e = *q;
                    if (e != 0) {
                        m = *(int*) (e + 0x184);
                        if (*(char*) (e + 8) != 0) {
                            obj = *p;
                            dx = *(float*) (obj + 0x4c) -
                                 *(float*) (*(int*) (m + 0x34) + 0x4c);
                            dy = *(float*) (obj + 0x50) -
                                 *(float*) (*(int*) (m + 0x34) + 0x50);
                            dz = *(float*) (obj + 0x54) -
                                 *(float*) (*(int*) (m + 0x34) + 0x54);
                            dist = (float) sqrt(dx * dx + dy * dy +
                                                dz * dz);
                            if (dist < g_664ed4) {
                                t = (int) fcn_004e6cb0((unsigned char) r[6] -
                                                       (unsigned char) r[5]);
                                t += (unsigned char) r[5];
                                d = (int) ((double) t *
                                           (*(float*) (e + 0x1c) *
                                            g_6640e8));
                                t = (int) ((double) d *
                                           (g_6629c8 - dist * g_664ed0));
                                node = *q;
                                *(int*) (node + 0x24) -= t;
                                flag = (*(int*) (node + 0x16c) ==
                                        *(int*) &g_772e9c) ? 1 : 2;
                                fcn_004cfc40((char*) node, t, flag);
                                if (!fcn_004d4790((char*) e)) {
                                    fcn_00406340((char*) m, "Explosion_s", 1);
                                }
                            }
                        }
                    }
                }
                d3_DestroyObject((void*) *p);
                *p = 0;
            }
        }
        p += 2;
    } while ((int) p < 0x9ba2c0);
    return count;
}
