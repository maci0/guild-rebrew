typedef unsigned short u16;

/* Partial reconstruction of the native body: the query setup and the first
 * result check are recovered; the rest is listed in the row blocker. */

int __cdecl fcn_0050dac0(int id);
int __cdecl fcn_005cd440(void* a, int b, int c, int d);
int __cdecl fcn_00577ab0(int h);
void __cdecl io_FormatTextBuffer(char* out, int id, int a);
int __cdecl fcn_00526120(char* out, int a);

/* ADDRESS: GOLDTL 0x0058a6b0 */
int __cdecl fcn_0058a6b0(void)
{
    int query[6];
    int slots[8];
    char text[0x160];
    int i;
    int h;
    int ent;

    i = 0;
    for (i = 0; i < 6; i++)
        query[i] = 0;
    for (i = 0; i < 8; i++)
        slots[i] = -1;
    query[0] = 1;
    query[1] = 0x400;
    query[3] = 6;
    fcn_0050dac0((int) *(u16*) 0x774970);
    ent = fcn_005cd440(query, *(int*) 0x14b53d0, 0, 0);
    if (fcn_00577ab0(ent) != 0)
        return 0;
    io_FormatTextBuffer(text, 0x4030, (int) *(u16*) ent);
    fcn_00526120(text, 0);
    return 0;
}
