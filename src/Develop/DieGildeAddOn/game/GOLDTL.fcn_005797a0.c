#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern float g_665ef8;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char* lpGebaeudePROT;
typedef struct BuildingRow5797 {
	unsigned char kind;
	char fields[0x24c];
} BuildingRow5797;
extern unsigned char g_773d75;

extern int __cdecl fcn_00500e20(int* p);
extern void __cdecl gm_AddTime(void* clock, int a, int b, int c);
extern void __cdecl he_FreeAction(char* record);
extern void* __cdecl gm_LookupEntityRecordById(int id);
extern void* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
extern void* __cdecl fcn_00502cd0(int list, int a, int b, int c, int d);
extern int __cdecl gm_GetElapsedMinutes(void* p, int v);
extern int __cdecl fcn_0050c710(void* p, int a, int b);
extern int __cdecl fcn_005241f0(char* record);
extern int __cdecl fcn_0050dc90(void* p);
extern int __cdecl gm_eval_SlotVoll(int a, int b, int c);
extern void __cdecl fcn_004c51f0(int a, int b, int c, int d, char e, int f);
extern void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
extern void __cdecl he_MessageBoxQuickjump(int a, int b, char* c, int d, int e,
	int f, int g, int h, char* i);
extern void __cdecl fcn_00529160(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x005797a0 */
void __cdecl fcn_005797a0(char* event)
{
	char text[1024];
	char name[152];
	char line[512];
	unsigned int* p8c;
	char* entity;
	unsigned char* search;
	char* row;
	char* param;
	int count;
	int valid;
	int value;
	int handle;
	int mode;
	int i;
	int len;
	float fvalue;
	float increment;
	float v23;

	handle = fcn_00500e20(&gm_GameTime);
	search = 0;
	row = 0;
	param = 0;
	mode = 0;
	valid = 0;
	value = (int) (g_7f4c04 & 0xffff);
	if ((*(float*) (handle * 4 + 0x696550) <= (float) value
			|| (float) value < *(float*) (handle * 4 + 0x696540))
		&& *(int*) (event + 0x70) != -1 && *(int*) (event + 0x70) != -2) {
		gm_AddTime(event + 0x52, 0, 5, 0);
		return;
	}
	if (*(unsigned short*) (event + 8) == 0xffff || *(int*) (event + 0xc) == -1) {
		he_FreeAction(event);
		return;
	}
	count = 0;
	p8c = (unsigned int*) (event + 0x8c);
	for (i = 0; i < 4; i++) {
		entity = (char*) gm_LookupEntityRecordById(*p8c);
		if (entity != 0) {
			count++;
			valid++;
			if ((*(char*) (entity + 0x165) == 0x1b || *(char*) (entity + 0x165) == 0x1c)
				&& (*(unsigned char*) (entity + 0x1b4) & 1) != 0)
				valid--;
		}
		p8c++;
	}
	if (count == 0)
		*(unsigned int*) (event + 0x70) = 0xffffffff;
	search = (unsigned char*) gm_StartFilteredEntitySearch(1, 1, *(unsigned int*) (event + 0x10));
	if (search != 0) {
		row = (char*) &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*search];
		param = (char*) fcn_00502cd0(*(unsigned int*) (&search[0x5d]), 2, 6, 0, 0x2a);
		if (param == 0)
			*(unsigned int*) (event + 0x70) = 0xffffffff;
	} else {
		*(unsigned int*) (event + 0x70) = 0xffffffff;
	}
	if (*(int*) (event + 0x70) == 0) {
		value = gm_GetElapsedMinutes(event + 0xb8, 0x7f4c00);
		if (((char)((BUILDING_PROTOTYPE*)row)->category) == 0x1d) {
			fvalue = (float) fcn_0050c710(search, 0x12, 1) * 0.01f;
		} else {
			fvalue = (float) fcn_0050c710(search, 0x1e, 1) * 0.01f;
			if (handle == 3 && (search[0x5b] & 0x20) == 0)
				fvalue = fvalue - 0.5f;
		}
		increment = (fvalue + 1.0f) * (float) value * g_665ef8;
		if (valid >= 1) {
			v23 = *(float*) (event + 0xb0);
			for (i = 0; i < valid; i++) {
				v23 = v23 + increment;
			}
			*(float*) (event + 0xb0) = v23;
		}
		*(int*) (event + 0xb4) = *(int*) (event + 0xb4) - value;
		*(int*) (event + 0xb8) = gm_GameTime;
		*(int*) (event + 0xbc) = g_7f4c04;
		*(int*) (event + 0xc0) = g_7f4c08;
		*(short*) (event + 0xc4) = g_7f4c0c;
		*(int*) (event + 0x52) = gm_GameTime;
		*(int*) (event + 0x56) = g_7f4c04;
		*(int*) (event + 0x5a) = g_7f4c08;
		*(short*) (event + 0x5e) = g_7f4c0c;
		gm_AddTime(event + 0x52, 0, 5, 0);
		if (*(int*) (event + 0xb4) <= -1)
			*(unsigned int*) (event + 0x70) = 0xffffffff;
	}
	count = *(int*) (event + 0x70);
	if (count != -2 && count != -1)
		return;
	valid = (int) *(float*) (event + 0xb0);
	if (valid <= 1)
		valid = 1;
	if (count == -1 && fcn_005241f0(event) <= 0)
		valid = -1;
	if (search != 0 && param != 0 && valid >= 1) {
		count = fcn_0050dc90(search);
		valid = gm_eval_SlotVoll((int) param, *(unsigned short*) (event + 0xac), valid);
		if (valid != 0) {
			fcn_004c51f0(*(int*) (param + 2), -1, *(unsigned short*) (event + 0xac),
				valid, (char) g_773d75, 0);
			if (((char)((BUILDING_PROTOTYPE*)row)->category) != 0x1f) {
				io_FormatTextBuffer(text, 0x412c, 0x4128, 0x228, (void*) search);
				strcpy(name, "_NACHRICHTEN_FRIEDHOF_01");
				len = *(unsigned short*) (event + 0xac) * 2 + 0x9a8;
				if (valid != 1)
					io_FormatTextBuffer(line, 0x412e, valid, len);
				else
					io_FormatTextBuffer(line, 0x412d, len);
			} else {
				io_FormatTextBuffer(text, 0x4222, 0x421e, 0x22c, (void*) search);
				strcpy(name, "_NACHRICHTEN_ZIGEUNER_03");
				len = *(unsigned short*) (event + 0xac) * 2 + 0x9a8;
				if (valid != 1)
					io_FormatTextBuffer(line, 0x4224, valid, len);
				else
					io_FormatTextBuffer(line, 0x4223, len);
			}
			strcat(text, line);
		} else {
			if (((char)((BUILDING_PROTOTYPE*)row)->category) == 0x1f) {
				io_FormatTextBuffer(text, 0x4225, 0x421e, 0x22c, (void*) search);
				strcpy(name, "_NACHRICHTEN_ZIGEUNER_03");
			} else {
				io_FormatTextBuffer(text, 0x412f, 0x4128, 0x228, (void*) search);
				strcpy(name, "_NACHRICHTEN_FRIEDHOF_01");
			}
		}
		i = *(unsigned short*) (event + 8) * 0x21c;
		if ((*(char*) (i + 0x7f4ca2) == 6 || *(char*) (i + 0x7f4ca2) == 7)
			&& (count == 0 || (*(unsigned char*) (count + 0x1b4) & 1) == 0))
			he_MessageBoxQuickjump(*(int*) (i + 0x7f4ca4), -1, text, 0, 0x5ec,
				*(int*) (search + 1), -1, 0, name);
	}
	p8c = (unsigned int*) (event + 0x8c);
	for (i = 0; i < 4; i++) {
		entity = (char*) gm_LookupEntityRecordById(*p8c);
		if (entity != 0)
			fcn_00529160(0, 0, *(unsigned short*) entity, 0);
		p8c++;
	}
	he_FreeAction(event);
}
