#include <stdio.h>
#include <string.h>

// SIZE 0x84
struct log_425bf0 {
	int line;
	char text[0x80];
};

#include "client_script_runtime.h"
extern int g_6b7eb0;
extern void* g_14cb8f0;

/* ADDRESS: GOLD 0x004273d0 */
/* ADDRESS: GOLDTL 0x00425bf0 */

/* Reports a script error: logs the message with its source line. */
void __cdecl fcn_00425bf0(char* s, unsigned int pos, const char* msg)
{
	int line;
	char buf[0x200];

	line = 0;
	if (s == 0) {
		s = g_6b7e98;
		pos = *(unsigned int*) (s + 0x118);
	}
	if (g_6b7e98 != 0) {
		if (*(int*) (s + 0x11c) != 0) {
			for (line = 0; line < *(int*) (s + 0xc2c); line++) {
				if ((*(unsigned int**) (s + 0xc30))[line] + *(int*) (s + 0x11c) > pos) {
					break;
				}
			}
			if (line != 0) {
				sprintf(buf, "Line %i:%s", line, msg);
				goto log;
			}
		}
		sprintf(buf, "%s", msg);
	log:
		strncpy(((struct log_425bf0*)g_14cb8f0)[g_6b7eb0].text, buf, 0x7f);
		((struct log_425bf0*)g_14cb8f0)[g_6b7eb0].line = line;
		g_6b7eb0++;
		if (g_6b7eb0 > 0x1e) {
			g_6b7eb0 = 0;
		}
		sprintf(buf, "\"%s\" %s in Line: %i", g_6b7e98, msg, line);
	} else {
		sprintf(buf, "%s", msg);
		strncpy(((struct log_425bf0*)g_14cb8f0)[g_6b7eb0].text, buf, 0x7f);
		((struct log_425bf0*)g_14cb8f0)[g_6b7eb0].line = 0;
		g_6b7eb0++;
		if (g_6b7eb0 > 0x1e) {
			g_6b7eb0 = 0;
		}
		sprintf(buf, "%s in Line: %i", msg, 0);
	}
}
