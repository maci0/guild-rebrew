unsigned short *__cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short *__cdecl fcn_00502cd0(int, int, ...);
void *__cdecl gm_FindNextFilteredEntity(void);
void *__cdecl gm_NextEntityQueryMatch(void);

/* ADDRESS: GOLDTL 0x00510100 */
void __cdecl fcn_00510100(void)
{
    char *entity;
    int state;

    entity = (char *)gm_StartFilteredEntitySearch(1, 0, 0x1e);
    while (entity != 0) {
        state = 2;
        entity = (char *)fcn_00502cd0(*(int *)(entity + 0x5d), 1, 0, 0xff);
        if (entity != 0) {
            entity = (char *)fcn_00502cd0(*(int *)(entity + 0x14), 1, 5);
            while (entity != 0) {
                if (*(int *)(entity + 0xe) != state) {
                    *(int *)(entity + 0xe) = state;
                }
                entity = (char *)gm_NextEntityQueryMatch();
            }
        }
        entity = (char *)gm_FindNextFilteredEntity();
    }
}
