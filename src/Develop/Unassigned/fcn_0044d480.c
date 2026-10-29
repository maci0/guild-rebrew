typedef struct {
    float x;
    float y;
} PAIR;

extern char *__cdecl strtok(char *s, const char *delim);
extern double __cdecl atof(const char *s);
extern char g_00662d18;

/* ADDRESS: GOLDTL 0x0044d480 */
void __cdecl fcn_0044d480(int unused, char *obj)
{
    int i;

    for (i = 0; i < 3; i++)
        ((PAIR *)(*(char **)(obj + 0x20)))[*(int *)(obj + 0x18) * 7 + i].x =
            (float)atof(strtok(0, &g_00662d18));
    for (i = 0; i < 3; i++)
        ((PAIR *)(*(char **)(obj + 0x20)))[*(int *)(obj + 0x18) * 7 + i].y =
            (float)atof(strtok(0, &g_00662d18));
}
