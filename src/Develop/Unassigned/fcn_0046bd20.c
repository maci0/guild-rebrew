/* Partial reconstruction of the native body: the font handle setup, the state
 * resets and the first recursive layout call are recovered; the rest is
 * listed in the row blocker. */

int __cdecl fcn_00465950(char* name);
int __cdecl d2_GetResourceData(int handle);

/* ADDRESS: GOLDTL 0x0046bd20 */
int __cdecl fcn_0046bd20(int a1, int a2, int a3, int a4, int a5, int a6,
                         int a7)
{
    int buf[0x180];
    int i;
    int* font;

    font = (int*) 0x772524;
    if (*font == 0)
        *font = d2_GetResourceData(fcn_00465950("_FONT"));
    *(int*) 0x772544 = 0;
    *(int*) 0x772548 = 0;
    *(int*) 0x77254c = 0x270f;
    *(int*) 0x772550 = a2;
    *(int*) 0x1015ea4 = *(unsigned short*) (*font + 8);
    for (i = 0; i < 0x180; i++)
        buf[i] = 0;
    if (a5 != 0 && (a7 & 0xa0) != 0)
        fcn_0046bd20(a1, a2, a3, a4, a5, a6, a7);
    return a1;
}
