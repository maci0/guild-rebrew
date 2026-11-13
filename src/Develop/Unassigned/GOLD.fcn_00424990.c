#include <windows.h>
#include <winsock.h>
#include <stdio.h>

extern int g_14cbca0;
extern int g_14cbcb0;
extern int g_6b7d40;
void __cdecl fcn_00420b70(void);
void __cdecl fcn_00424510(int);

/* ADDRESS: GOLD 0x00424990 */
int __cdecl fcn_00424990(const char* host, unsigned short port)
{
    WSADATA startup;
    unsigned long value;
    struct sockaddr_in address;
    struct hostent* resolved;
    fd_set writable;
    struct timeval timeout;
    char text[128];
    SOCKET sock;
    int i;
    int ready;
    int length;

    fcn_00420b70();
    g_14cbca0 = -1;
    *(int*) 0x1460ae4 = 0;
    *(int*) 0x1460ae8 = 0;
    *(short*) 0x1460aec = 0;
    *(short*) 0x1460aee = 0;
    g_14cbcb0 = 0;
    if (host == 0)
        return -1;
    WSAStartup(2, &startup);
    g_6b7d40 = 1;
    sock = socket(2, 1, 6);
    if (sock == INVALID_SOCKET)
        goto cleanup;



    value = 1;
    if (setsockopt(sock, 0xffff, 4, (char*) &value, 4) == -1)
        goto fail;
    value = 1;
    if (setsockopt(sock, 0xffff, -129, (char*) &value, 4) == -1)
        goto fail;
    value = 0x40000;
    if (setsockopt(sock, 0xffff, 0x1002, (char*) &value, 4) == -1)
        goto fail;
    value = 0x20000;
    if (setsockopt(sock, 0xffff, 0x1001, (char*) &value, 4) == -1)
        goto fail;
    value = 1;
    if (ioctlsocket(sock, 0x8004667e, &value) == -1)
        goto fail;
    address.sin_family = 2;
    address.sin_addr.s_addr = inet_addr(host);
    if (address.sin_addr.s_addr == INADDR_NONE) {
        resolved = gethostbyname(host);
        if (resolved == 0)
            goto fail;
        address.sin_addr.s_addr = *(unsigned long*) resolved->h_addr_list[0];
    }
    address.sin_port = htons(port);
    if (connect(sock, (struct sockaddr*) &address, 16) != 0 && WSAGetLastError() != 10035) {
        fcn_00424510(WSAGetLastError());
        goto fail;
    }
    timeout.tv_sec = 0;
    timeout.tv_usec = 500000;
    i = 0;
    do {
        writable.fd_array[0] = sock;
        writable.fd_count = 1;
        ready = select(1, 0, &writable, 0, &timeout);
        if (ready == -1)
            break;
        if (ready != 0) {
            length = 4;
            if (getsockopt(sock, 0xffff, 0x1001, (char*) &value, &length) != -1)
                sprintf(text, (char*) 0x5f7e54, value);
            length = 4;
            if (getsockopt(sock, 0xffff, 0x1002, (char*) &value, &length) != -1)
                sprintf(text, (char*) 0x5f7e38, value);
            g_14cbca0 = sock;
            return sock;
        }
        i++;
    } while (i < 16);
    fcn_00424510(WSAGetLastError());
fail:
    shutdown(sock, 2);
    closesocket(sock);
cleanup:
    g_6b7d40 = 0;
    WSACleanup();
    return -1;
}
