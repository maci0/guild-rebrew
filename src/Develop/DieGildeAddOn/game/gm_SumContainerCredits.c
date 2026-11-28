unsigned short *__cdecl gm_QueryEntities(int container_id, int arg_count, ...);
void *__cdecl gm_NextEntityQueryMatch(void);

/* ADDRESS: GOLDTL 0x0050d270 */
int __cdecl gm_SumContainerCredits(int containerId)
{
    int total;
    unsigned short *entry;

    total = 0;
    entry = gm_QueryEntities(containerId, 1, 4, 9);
    if (entry != 0) {
        do {
            total += *(int *) ((char *) entry + 0xe);
            entry = (unsigned short *) gm_NextEntityQueryMatch();
        } while (entry != 0);
    }
    return total;
}
