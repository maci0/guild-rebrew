#include <string.h>

int __cdecl rt_CountRoutePoints(char *p);
int __cdecl cm_StageRawPacketPayload(unsigned short n, void *src);
int __cdecl cm_EnqueueClientPacket(void *buf);

/* ADDRESS: GOLDTL 0x004c6e20 */
void __cdecl cm_SendSetObjektRoute(char *record, char *head)
{
    char buf[0x9c];
    char items[0x200];
    int count;
    int i;
    char *p;
    char *dst;
    char *src;

    p = head;
    count = rt_CountRoutePoints(p);
    buf[0] = 0x68;
    *(int *)(buf + 0x10) = *(int *)(record + 2);
    *(int *)(buf + 0x14) = count;
    if (count > 0) {
        dst = items;
        for (i = count; i > 0; i--) {
            src = p;
            p = *(char **)(p + 0x3c);
            memcpy(dst, src, 0x40);
            dst += 0x40;
        }
    }
    cm_StageRawPacketPayload((unsigned short)(count << 6), items);
    cm_EnqueueClientPacket(buf);
}
