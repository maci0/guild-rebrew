

#include <string.h>

#include "Develop/client_types.h"
typedef Msg_aed340 Msg;
// SIZE 0xf8

#include "Develop/DieGildeAddOn/command/client_packet_queue.h"
extern char g_aed438[];
extern int nt_ClientSocket;
extern int g_7749d0;

char *__cdecl gm_LookupEntityRecordById(int);
int __cdecl d2_IsPrivilegeMessageEnabled(int);
char *__cdecl he_CreateEventFromRequest(Msg *);
char *__cdecl m_alloc(int, char *);

/* ADDRESS: GOLDDE 0x004b6940 */
int __cdecl fcn_004c9160(char *packet, char *reply)
{
	Msg m;
	char *o;
	char *w;
	char *s2;

	m = *(Msg*) cm_IncomingPacketData;
	o = gm_LookupEntityRecordById(m.who);
	if (nt_ClientSocket != -1) {
		if (m.flags & 1) {
			if (o == 0) {
				return 1;
			}
			if (o[2] == 7 || (o[2] != 6 && reply == 0)) {
				return 1;
			}
		}
		if (reply == 0 && (m.flags & 2)) {
			m.flags &= ~2;
			m.flags |= 4;
		}
		g_7749d0 = *(int *) (packet + 0x10);
	}
	if (m.type == 0x11 && d2_IsPrivilegeMessageEnabled(m.f58) != 0) {
		return 0;
	}
	w = he_CreateEventFromRequest(&m);
	if (w == 0) {
		return 1;
	}
	if (*w == 0x11) {
		if (w[0xf0] & 0x10) {
			s2 = g_aed438 + strlen(g_aed438) + 1;
			*(char **) (w + 0x7c) = m_alloc(strlen(s2) + strlen(g_aed438) + 2, "messagebox");
			strcpy(*(char **) (w + 0x7c), g_aed438);
			strcpy(*(char **) (w + 0x7c) + strlen(g_aed438) + 1, s2);
			*(int *) (w + 0x80) = strlen(s2) + strlen(g_aed438) + 2;
		} else {
			*(char **) (w + 0x7c) = m_alloc(strlen(g_aed438) + 1, "messagebox");
			strcpy(*(char **) (w + 0x7c), g_aed438);
			*(int *) (w + 0x80) = strlen(*(char **) (w + 0x7c)) + 1;
		}
	}
	if (reply != 0) {
		reply[0] = 1;
		reply[1] = 4;
		*(char **) (reply + 6) = w;
	}
	return 0;
}
