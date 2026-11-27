int __cdecl cm_EnqueueClientPacket(void *);

/* ADDRESS: GOLDTL 0x004c59e0 */
int __cdecl cm_RequestAddCutsceneParticipant(int a1, int a2)
{
    char buf[0x9c];

    buf[0] = 0x29;
    *(int *)(buf + 0x10) = a1;
    *(int *)(buf + 0x14) = a2;
    return cm_EnqueueClientPacket(buf);
}
