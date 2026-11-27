int __cdecl cm_RequestModifyHealth(unsigned int, int);
int __cdecl cm_SendCopyEntityData(void *);

/* ADDRESS: GOLDTL 0x00496480 */
int __cdecl ai_RunBildungBeruf(int *a, unsigned char *b)
{
    char t[0xf8];

    cm_RequestModifyHealth(a[1], -(int)(*(unsigned int *)(b + 0x10)));
    *(unsigned int *)(t + 0x08) = a[1];
    *(unsigned int *)(t + 0x0c) = a[1];
    t[0x36] = 1;
    t[0x04] = 0x60;
    t[0x5a] = b[4];
    cm_SendCopyEntityData(t);
    return 5;
}
