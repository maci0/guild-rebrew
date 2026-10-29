/* Network-session start: waits for the network state, validates the city path,
 * loads the network scene, writes the game.INI network entry, connects and
 * retries until the session exists, then hands the session to the game and
 * tears the scene down. Returns 1 when the city path check fails, 2 when the
 * network scene check fails, 0 after a completed startup. */

#pragma intrinsic(strcpy)

int __cdecl sprintf(char *buf, const char *fmt, ...);
char *__cdecl strrchr(const char *s, int c);
char *__cdecl strcpy(char *dst, const char *src);

__declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(void *module, char *name, unsigned long size);
__declspec(dllimport) int __stdcall WritePrivateProfileStringA(const char *sec, const char *key,
                                                              const char *value, const char *file);
__declspec(dllimport) unsigned long __stdcall timeGetTime(void);

void __cdecl fcn_00514570(unsigned int a0);
void __cdecl fcn_00514b50(char a0);
void __cdecl init_LocalData(void);
void __cdecl fcn_00515340(char a0);
int __cdecl ls_SendGame(char *path);
int __cdecl fcn_00525b40(void);
void __cdecl fcn_005356e0(void);
void __cdecl fcn_00535960(void);
void __cdecl fcn_00535770(int id);
void __cdecl fcn_005017a0(int i);
void __cdecl fcn_00501fe0(int i);
int __cdecl fcn_0050b750(int timeout, char who);
int __cdecl fcn_00413160(void);
int __cdecl fcn_004432d0(int a0, int a1);
int __cdecl fcn_00442e30(void);
int __cdecl fcn_00448360(char *name, int a1, int a2);
int __cdecl fcn_00471af0(int a0, int a1);
int __cdecl fcn_00476970(int a0);
short __cdecl gm_RandomMod(int a0);
int __cdecl fcn_00469e30(int a0);
int __cdecl fcn_0046ac30(void);
int __cdecl fcn_004c5790(int id, int *args);
int __cdecl fcn_004c5040(short a0, short a1, char a2, char a3, int a4,
                         char a5, char a6, char *a7, char *a8);
int __cdecl fcn_004c4450(int i);
int __cdecl fcn_004c4480(int i);
int __cdecl fcn_004b3d80(int a0, int a1, int a2);
int __cdecl fcn_004b54e0(int a0);
int __cdecl fcn_004c5150(int a0, int a1, char a2, int a3);
void __cdecl fcn_004c4860(int a0);

/* ADDRESS: GOLDTL 0x005145a0 */
int __cdecl fcn_005145a0(char *path)
{
    char text[512];
    char file[260];
    int msg[32];    /* 0x7c-byte message block for fcn_004c5790; only [0]/[1] set */
    int flag;
    int session;
    int handle;
    int stamp;
    int result;
    int i;
    char *p;

    sprintf(text, *(char **) 0x14ac600, *(unsigned char *) 0x6a375c);
    fcn_00514570((unsigned int) text);
    *(int *) 0x77494c = 0;
    do {
        fcn_005356e0();
        fcn_00535960();
    } while (*(int *) 0x77494c == 0);
    if (*(int *) 0x77494c & 1) {
        if (*path == 0)
            sprintf(path, "%s/AUGSBURG.NET", "gamedata/cities");
        fcn_00514570(*(unsigned int *) 0x14ac5f0);
        if (ls_SendGame(path) == 0)
            return 1;
    }
    flag = *(int *) 0x77494c & 1;
    fcn_00514570(*(unsigned int *) 0x14ac5f4);
    if (fcn_00525b40() == 0)
        return 2;
    GetModuleFileNameA(*(void **) 0x7e1f80, file, 0x104);
    p = strrchr(file, '\\');
    strcpy(p, "\\game.INI");
    *(int *) 0x7725c8 = 0;
    fcn_004432d0(fcn_00413160(), 0);
    fcn_00448360("scenes/*network.ed3", 0, 0);
    fcn_00471af0(*(int *) 0x7e1d40, 0);
    *(int *) 0x7725c8 = 1;
    fcn_00442e30();
    fcn_004432d0(*(int *) 0x6b8010, 0);
    fcn_00471af0(*(int *) 0x7e1d40, 1);
    WritePrivateProfileStringA("Network", "Name", (char *) 0x7e23ea, file);
    WritePrivateProfileStringA("Network", "Familienname", (char *) 0x7e240a, file);
    fcn_00476970(*(int *) 0x77250c);
    fcn_00469e30(((short) gm_RandomMod(2) != 1) ? 0x791 : 0x78e);
    fcn_0046ac30();
    if (*(int *) 0x77494c & 1) {
        msg[0] = *(unsigned char *) 0x6a375c;
        fcn_004c5790(6, msg);
    }
    session = fcn_004c5040(-1, -1, *(unsigned char *) 0x7e23e2,
                           *(unsigned char *) 0x7e23e3,
                           *(int *) 0x7e23e4 + 0x59a,
                           *(unsigned char *) 0x7e23e8,
                           *(unsigned char *) 0x7e23e9,
                           (char *) 0x7e23ea, (char *) 0x7e240a);
    while (session == -1) {
        fcn_005356e0();
        fcn_00535960();
        session = fcn_004c5040(-1, -1, *(unsigned char *) 0x7e23e2,
                               *(unsigned char *) 0x7e23e3,
                               *(int *) 0x7e23e4 + 0x59a,
                               *(unsigned char *) 0x7e23e8,
                               *(unsigned char *) 0x7e23e9,
                               (char *) 0x7e23ea, (char *) 0x7e240a);
    }
    while (fcn_004c4450(session) == 0) {
        fcn_005356e0();
        fcn_00535960();
    }
    handle = fcn_004c4480(session);
    if (*(int *) 0x77494c & 1) {
        *(unsigned char *) 0x6a3440 = 0xff;
        msg[0] = -1;
        stamp = (int) timeGetTime();
        *(int *) 0x7e1f60 = stamp;
        msg[1] = stamp;
        fcn_004c5790(9, msg);
    }
    while (*(unsigned char *) 0x6a3440 == 0xfe) {
        fcn_005356e0();
        fcn_00535960();
    }
    if (*(unsigned char *) 0x6a3440 != 0xff) {
        if (*(unsigned char *) 0x6a3440 != 5)
            *(int *) 0x7e1f60 = (int) timeGetTime();
        fcn_004b3d80(*(int *) (handle + 4), *(signed char *) 0x6a3440, 1);
    }
    result = fcn_0050b750(*(int *) 0x7747fc == 0 ? 2000 : 500000,
                          *(unsigned char *) 0x773d75);
    fcn_004c5150(*(int *) (handle + 4), -1, *(unsigned char *) 0x773d75,
                 result);
    while ((*(int *) 0x77494c & 4) == 0) {
        fcn_005356e0();
        fcn_00535960();
    }
    if (flag != 0) {
        fcn_00514570(*(unsigned int *) 0x14ac5f8);
        fcn_00514b50(*(unsigned char *) 0x773d75);
    }
    fcn_00535770(0x24087);
    fcn_00514570(*(unsigned int *) 0x14ac5fc);
    init_LocalData();
    fcn_00535770(0x24087);
    if (flag != 0) {
        fcn_00515340(*(unsigned char *) 0x773d75);
        i = 0;
        p = (char *) 0x868060;
        do {
            if (*p == 0)
                break;
            fcn_005017a0(i);
            fcn_00501fe0(i);
            p += 0x2f4;
            i++;
        } while ((int) p < 0x868c30);
        fcn_004c4860(2);
    }
    *(int *) 0x7725c8 = 0;
    if (*(signed char *) 0x6a3440 > -1 && *(signed char *) 0x6a3440 < 6) {
        fcn_004432d0(fcn_00413160(), 0);
        fcn_00448360("scenes/*network.ed3", 0, 0);
        fcn_004b54e0(*(int *) (handle + 4));
        fcn_00442e30();
        fcn_004432d0(*(int *) 0x6b8010, 0);
    }
    return 0;
}
