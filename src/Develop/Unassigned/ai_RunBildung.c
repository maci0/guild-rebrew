extern void __cdecl cm_RequestModifyHealth(int, int);
extern void __cdecl cm_SendCopyEntityData(void *);

typedef struct tagS495F80 {
    unsigned char gap_00[4];
    unsigned char f04;
    unsigned char gap_05[3];
    int f08;
    int f0c;
    unsigned char gap_10[0x26];
    unsigned char f36;
    unsigned char gap_37[0x23];
    unsigned char f5a;
    unsigned char gap_5b[0x9d];
} AI_BILDUNG_MSG;

/* ADDRESS: GOLDTL 0x00495f80 */
int __cdecl ai_RunBildung(int *actor, int *req)
{
    AI_BILDUNG_MSG s;

    cm_RequestModifyHealth(actor[1], -req[4]);
    s.f36 = 1;
    s.f04 = 0x60;
    s.f08 = actor[1];
    s.f0c = -1;
    s.f5a = *((unsigned char *)req + 4);
    cm_SendCopyEntityData(&s);
    return 4;
}
