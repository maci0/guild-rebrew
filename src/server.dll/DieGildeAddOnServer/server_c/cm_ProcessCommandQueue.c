/* cm_ProcessCommandQueue — Master Command Router (0x1000aac0). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000aac0

#include <string.h>

typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
extern unsigned char g_connections[]; /* 0x101deb00 */
int __cdecl ahm_ProcessEntityChain(char* cmd_payload);
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);

int __cdecl cm_ProcessCommandQueue(void* a)
{
	char* tab;
	char* pkt;
	char* held;
	char* next;
	char* slot;
	int i;
	int ok;

	(void) a;
	for (tab = (char*) 0x10442cf0; (int) tab < 0x11764010; tab += 0x264264) {
		pkt = *(char**) tab;
		held = 0;
		while (pkt != 0) {
			next = *(char**) (pkt + 0x95);
			ok = 1;
			if (held == 0) {
				if (*(unsigned char*) pkt == 5) {
					held = pkt;
					pkt = next;
					continue;
				}
			} else if (*(unsigned char*) pkt == 6) {
				if (ahm_ProcessEntityChain(held) == 0) {
					ok = 0;
				}
				next = *(char**) (held + 0x95);
				pkt = held;
				held = 0;
				if (!ok) {
					pkt = next;
					continue;
				}
			} else {
				pkt = next;
				continue;
			}
			/* Unlink pkt from the incoming queue head and push it onto the freelist. */
			if (pkt == *(char**) tab) {
				*(char**) tab = next;
			} else {
				*(char**) (*(char**) (pkt + 0x91) + 0x95) = next;
				*(char**) (next + 0x91) = *(char**) (pkt + 0x91);
			}
			*(char**) (pkt + 0x91) = 0;
			*(char**) (pkt + 0x95) = *(char**) (tab + 8);
			*(char**) (tab + 8) = pkt;

			if (*(unsigned char*) pkt >= 0x6a) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x756, "Command-Type out of Range!\n", 1);
			} else {
				if (*(unsigned char*) pkt == 0x20 && *(unsigned char*) (pkt + 0x10) == 0xe) {
					slot = (char*) g_connections + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264;
					if ((*(unsigned char*) slot & 0x40) != 0) {
						LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x72e, "Multisync!!!", 1);
					}
				}
				if (g_dispatch_table[*(unsigned char*) pkt](pkt, 0) != 0) {
					slot = (char*) g_connections + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264;
					if ((*(unsigned char*) slot & 1) == 0) {
						goto advance;
					}
					*(unsigned char*) pkt = 2;
					if (cm_QueuePlayerCommand((unsigned int*) slot, (unsigned char*) pkt) == -1) {
						return -1;
					}
					goto advance;
				}
				if (*(unsigned char*) pkt == 0x20 && *(unsigned char*) (pkt + 0x10) == 0xe) {
					slot = (char*) g_connections + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264;
					memcpy((char*) 0x10442c54 + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264, pkt, 0x99);
					goto advance;
				}
				slot = (char*) g_connections + (unsigned int) *(unsigned char*) (pkt + 3) * 0x264264;
				if ((*(unsigned char*) slot & 1) != 0) {
					if (cm_QueuePlayerCommand((unsigned int*) slot, (unsigned char*) pkt) == -1) {
						return -1;
					}
				}
				*(int*) (pkt + 4) = -1;
				for (i = 0, slot = (char*) g_connections; (int) slot < 0x114ffe20; slot += 0x264264, i++) {
					if (i == (int) *(unsigned char*) (pkt + 3)) {
						continue;
					}
					if ((*(unsigned char*) slot & 1) == 0) {
						continue;
					}
					if (cm_QueuePlayerCommand((unsigned int*) slot, (unsigned char*) pkt) == -1) {
						return -1;
					}
				}
			}
		advance:
			pkt = next;
		}
	}
	return 0;
}
