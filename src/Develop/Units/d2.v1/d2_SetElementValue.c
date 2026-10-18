#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "d2_gui.h"

#ifdef REBREW_GOLD
#define d2_GUI_POOL g_00f8f080
#define d2_GUI_ID_LIMIT 0x300
#define d2_GUI_NUMBER_OFFSET 0x80
#define d2_GUI_DIRTY_OFFSET 0x48
#define d2_GUI_STATE_OFFSET 0x28
#else
#define d2_GUI_POOL g_1015ea0
#define d2_GUI_ID_LIMIT 0x400
#define d2_GUI_NUMBER_OFFSET 0x90
#define d2_GUI_DIRTY_OFFSET 0x58
#define d2_GUI_STATE_OFFSET 0x38
#endif

/* Inferred interface: widget kind and flags select the payload. */
/* ADDRESS: GOLD 0x00475ca0 */
/* ADDRESS: GOLDTL 0x00472380 */
void __cdecl d2_SetElementValue(int id, ...)
{
	D2_GUI_ITEM* e;
	char* sub;
	int fl;
	int step;
	int v;
	int n;
	int a2;
	int a3;
	int a4;
	int a5;
	char* text;
	va_list ap;

	if (id == -1 || id > d2_GUI_ID_LIMIT) {
		return;
	}
	va_start(ap, id);
	e = &((D2_GUI_ITEM*)d2_GUI_POOL)[id];
	if (e->kind == 0x41) {
		sub = e->data;
		if (*(int*) (sub + 0x28) & 1) {
			text = va_arg(ap, char*);
			if (strlen(text) > 0xfe) {
				va_end(ap);
				return;
			}
			strcpy(sub + 0x2c, text);
			va_end(ap);
			return;
		}
		if (*(int*) (sub + 0x28) & 2) {
			a2 = va_arg(ap, int);
			a3 = va_arg(ap, int);
			a4 = va_arg(ap, int);
			*(int*) (sub + 0x1c) = a2;
			*(int*) (sub + 0x18) = a3;
			*(int*) (sub + 0x12c) = a4;
			_itoa(a4, sub + 0x2c, 10);
			fl = *(int*) (sub + 0x28);
			if (fl & 0x80) {
				step = fcn_004722c0(sub);
				*(int*) (sub + 0x18) -= (*(int*) (sub + 0x18) - *(int*) (sub + 0x1c)) % step;
				*(int*) (sub + 0x1c) += (*(int*) (sub + 0x18) - *(int*) (sub + 0x1c)) % step;
				v = *(int*) (sub + 0x12c) / step * step;
				n = (*(int*) (sub + 0x18) - *(int*) (sub + 0x1c)) / step;
				*(int*) (sub + 0x12c) = v;
				if (n > 0x19) {
					*(int*) (sub + 0x18) = step * 25;
				}
				if (v == -1 && (fl & 0x40)) {
					va_end(ap);
					return;
				}
				*(int*) (sub + 0x12c) = *(int*) (sub + 0x1c) > v ? *(int*) (sub + 0x1c) : v;
			}
			va_end(ap);
			return;
		}
	}
	if (e->kind == 0x45) {
		a2 = va_arg(ap, int);
		a3 = va_arg(ap, int);
		a4 = va_arg(ap, int);
		*(int*) ((char*) e + d2_GUI_NUMBER_OFFSET) = a2;
		*(int*) ((char*) e + d2_GUI_NUMBER_OFFSET + 4) = a3;
		*(int*) ((char*) e + d2_GUI_NUMBER_OFFSET - 4) = a4;
		if (*((unsigned char*) e + d2_GUI_NUMBER_OFFSET + 8) & 0x10) {
			a5 = va_arg(ap, int);
			*(int*) ((char*) e + d2_GUI_NUMBER_OFFSET + 0x10) = a5;
		}
	} else if (*(int*) ((char*) e + d2_GUI_DIRTY_OFFSET) != 0 || *(int*) ((char*) e + d2_GUI_DIRTY_OFFSET + 4) != 0) {
		a2 = va_arg(ap, int);
		*(int*) ((char*) e + d2_GUI_STATE_OFFSET + 4) = *(int*) ((char*) e + d2_GUI_STATE_OFFSET) = (unsigned char) a2;
	}
	va_end(ap);
}
