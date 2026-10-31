

#include <string.h>

#include "client_types.h"
typedef Msg_aed340 Msg;
// SIZE 0xf8

#include "client_packet_queue.h"
extern char g_aed438[];
extern int g_14cbca0;
extern int g_7749d0;

char *__cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_0057de80(int);
char *__cdecl fcn_00545fe0(Msg *);
char *__cdecl m_alloc(int, char *);

int __cdecl fcn_004c9160(char *a1, char *a2)
{
	Msg m;
	char *o;
	char *w;
	char *s2;

	m = *(Msg*) g_aed340;
	o = gm_LookupEntityRecordById(m.who);
	if (g_14cbca0 != -1) {
		if (m.flags & 1) {
			if (o == 0) {
				return 1;
			}
			if (o[2] == 7 || (o[2] != 6 && a2 == 0)) {
				return 1;
			}
		}
		if (a2 == 0 && (m.flags & 2)) {
			m.flags &= ~2;
			m.flags |= 4;
		}
		g_7749d0 = *(int *) (a1 + 0x10);
	}
	if (m.type == 0x11 && fcn_0057de80(m.f58) != 0) {
		return 0;
	}
	w = fcn_00545fe0(&m);
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
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 4;
		*(char **) (a2 + 6) = w;
	}
	return 0;
}
