#include "client_packet_builder.h"

extern char* lpGebaeudePROT;
extern float g_6629d0;
extern float g_662a3c;
extern float g_662b10;

int __cdecl gm_RandomMod(int range);
float __cdecl gm_RandomFloat01(void);
void* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
void __cdecl fcn_004c4570(int a, int b, int offset, void* value);
void __cdecl fcn_004c4670(int a, int b, int offset, void* value);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004eea30(int city, int id, float value);
void __cdecl fcn_005782f0(int a, int b);
void __cdecl fcn_005b3270(char* slot, int a, char* object);
void __cdecl fcn_005b32d0(char* slot, int a, char* object);
void __cdecl fcn_005b3330(char* slot, int a, char* object, void* record);
void __cdecl fcn_005b33a0(char* slot, int a, char* object, int id);

/* ADDRESS: GOLDTL 0x00576750 */
void __cdecl fcn_00576750(int city, char* owner, char* object, int mode)
{
	int flags[5];
	void* found[3];
	int selected;
	int vertices;
	char* record;
	int value;
	int index;
	int i;
	char byte;

	record = lpGebaeudePROT + *(unsigned char*) object * 0x24d;
	if (*record != 0x1e) {
		return;
	}
	selected = 0;
	flags[0] = 0;
	flags[1] = 0;
	flags[2] = 0;
	flags[3] = 1;
	flags[4] = 0;
	if (*(signed char*) (object + 0x5c) > 0xa) {
		flags[2] = 1;
	}
	vertices = *(int*) (object + 0x65);
	if (mode != 2) {
		for (i = 0; i < 6; i++) {
			if (*(int*) (vertices + 0xc + i * 8) != 0
			    && *(float*) (vertices + 0x10 + i * 8) > g_6629d0) {
				flags[4] = 1;
				break;
			}
		}
	}
	found[0] = fcn_00502cd0(*(int*) (object + 0x5d), 2, 6, 0, 0x24b);
	if (found[0] != 0 && *(int*) ((char*) found[0] + 0x1c) == 0) {
		flags[1] = 1;
	}
	found[1] = fcn_00502cd0(*(int*) (object + 0x5d), 2, 6, 0, 0x256);
	if (found[1] != 0 && *(int*) ((char*) found[1] + 0x1c) == 0) {
		flags[1] = 1;
	}
	found[2] = fcn_00502cd0(*(int*) (object + 0x5d), 2, 6, 0, 0x266);
	if (found[2] != 0 && *(int*) ((char*) found[2] + 0x1c) == 0) {
		flags[1] = 1;
	}
	value = (gm_RandomMod(4) & 0xffff) + 1;
	for (i = 5; i != 0; i--) {
		if (value != 0 && flags[value] != 0) {
			selected = value;
			break;
		}
		value = (value + 1) % 5;
	}
	switch (selected) {
	case 1:
		index = gm_RandomMod(3) & 0xffff;
		for (i = 3; i != 0; i--) {
			if (found[index] != 0 && *(int*) ((char*) found[index] + 0x1c) == 0) {
				value = (gm_RandomMod(4) & 0xffff) + 3;
				fcn_004c4510((char*) found[index], *(int*) ((char*) found[index] + 2));
				byte = 1;
				fcn_004c4570(4, 1, 0x1c, &byte);
				fcn_004c4570(4, 1, 0x20, &value);
				fcn_004c5360();
				fcn_005b3330((char*) (*(unsigned short*) (object + 0x27) * 0x21c + 0x7f4ca0),
				    city, object, found[index]);
				break;
			}
			index = (index + 1) % 3;
		}
		break;
	case 2:
		if (record[0x247] == 3) {
			byte = (char) (0xfc - gm_RandomMod(3));
		}
		else if (record[0x247] == 2) {
			byte = (char) (0xfa - gm_RandomMod(3));
		}
		else {
			byte = (char) (0xf8 - gm_RandomMod(3));
		}
		fcn_004c4510(object, *(int*) (object + 1));
		fcn_004c4670(1, 1, 0x5c, &byte);
		fcn_004c5360();
		fcn_005b3270((char*) (*(unsigned short*) (object + 0x27) * 0x21c + 0x7f4ca0),
		    city, object);
		break;
	case 3:
		index = gm_RandomMod(3);
		fcn_005782f0(city, index + 1);
		fcn_005b32d0((char*) (*(unsigned short*) (object + 0x27) * 0x21c + 0x7f4ca0),
		    city, object);
		break;
	case 4:
		index = gm_RandomMod(6) & 0xffff;
		for (i = 6; i != 0; i--) {
			if (*(int*) (vertices + 0xc + index * 8) != 0
			    && *(float*) (vertices + 0x10 + index * 8) > g_6629d0) {
				float f;

				f = gm_RandomFloat01();
				f = *(float*) (vertices + 0x10 + index * 8)
				    - (f * g_662a3c + g_662b10);
				fcn_004eea30(city, *(int*) (vertices + 0xc + index * 8), f);
				fcn_005b33a0((char*) (*(unsigned short*) (object + 0x27) * 0x21c + 0x7f4ca0),
				    city, object, *(int*) (vertices + 0xc + index * 8));
				break;
			}
			index = (index + 1) % 6;
		}
		break;
	default:
		return;
	}
	*(int*) ((char*) owner + 0xac) = selected;
}
