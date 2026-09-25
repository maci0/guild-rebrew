extern int g_14cbca0;
extern int g_699364;
extern int g_68a9d4;
extern unsigned char g_7f4ca0[];

// SIZE 0x30
typedef struct {
	int d[12];
} copy_12_dwords;

int __cdecl fcn_004c4dc0(char*, int);
char* __cdecl fcn_005043d0(unsigned char, int);

// FUNCTION: GOLDTL 0x004c76c0
// SIZE: 206

int __cdecl fcn_004c76c0(int cmd, char* result)
{
	char* building;
	int field_id;
	int i;

	if (g_14cbca0 != -1)
		g_699364 = *(int*) (cmd + 0x10);
	if (*(int*) (cmd + 0x16) == -1) {
		i = 0xffff;
	}
	else {
		field_id = fcn_004c4dc0((char*) cmd, *(int*) (cmd + 0x16));
		*(int*) (cmd + 0x16) = field_id;
		i = 0;
		while ((unsigned short) i < 0x300) {
			if (*(unsigned short*) (g_7f4ca0 + (unsigned int) (unsigned short) i * 0x21c) != (unsigned short) 0xffff &&
				*(int*) (g_7f4ca0 + (unsigned int) (unsigned short) i * 0x21c + 4) == field_id) {
				break;
			}
			i = i + 1;
		}
		if ((unsigned short) i >= 0x300)
			return 1;
	}
	building = fcn_005043d0(*(unsigned char*) (cmd + 0x14), i);
	if (building == (char*) 0)
		return 1;
	g_68a9d4 = *(int*) (building + 1);
	*(unsigned short*) (building + 0x5a) = *(unsigned short*) (cmd + 0x1a);
	if (*(int*) (cmd + 0x1c) != 0) {
		*(copy_12_dwords*) (building + 0x65) = *(copy_12_dwords*) (cmd + 0x20);
	}
	if (result != (char*) 0) {
		*result = '\x01';
		result[1] = '\x02';
		*(char**) (result + 6) = building;
	}
	return 0;
}
