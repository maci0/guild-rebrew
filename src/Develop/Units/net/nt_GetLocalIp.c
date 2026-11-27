#include <windows.h>
#include <winsock2.h>
#include <string.h>

extern int g_6b7d40;
extern char g_6b7d44[];

/* ADDRESS: GOLDTL 0x00420d20 */
char *__cdecl nt_GetLocalIp(void)
{
    char host[512];
    WSADATA wsa;
    struct hostent *h;
    struct in_addr addr;

    if (!g_6b7d44[0]) {
        if (!g_6b7d40)
            WSAStartup(2, &wsa);
        if (!gethostname(host, sizeof(host)) && (h = gethostbyname(host)) != 0) {
            addr = *(struct in_addr *)h->h_addr_list[0];
            strcpy(g_6b7d44, inet_ntoa(addr));
        }
        if (!g_6b7d40)
            WSACleanup();
    }
    return g_6b7d44;
}
