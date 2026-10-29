#include <string.h>

int __cdecl fcn_00436aa0(void *flags);
int __cdecl fcn_00436f70(int enable);
void *__cdecl fcn_00437890(void *node);
int __cdecl fcn_00437ac0(int a, int b, int c, const char *s);
int __cdecl fcn_00438af0(int a);

/* ADDRESS: GOLDTL 0x00448b10 */
char __cdecl fcn_00448b10(void)
{
	unsigned char flags[8];
	char *node;
	unsigned char value;

	if ((*(char *) 0x14cf950) != *(char *) 0x6b85a5) {
		memcpy(flags, (void *) 0x1052bd0, 8);
		*(char *) 0x6b85a5 = (*(char *) 0x14cf950);
		switch ((unsigned char) (*(char *) 0x14cf950)) {
		case 0x30:
			value = flags[0];
			flags[0] = value ^
			           ((unsigned char) (~(value >> 1) * 2 ^ value) &
			            2);
			fcn_00438af0(0);
			fcn_00436aa0(flags);
			return 0;
		case 0x2e:
			node = *(char **) 0x6b8014;
			if (*(char **) 0x1041d0c == node) {
				node = *(char **) 0x1043254;
				while (*(int *) (node + 0x218) != 4) {
					if (node == (char *) 0x1042340)
						return 0;
					node = (char *) fcn_00437890(node);
				}
				if (node == (char *) 0x1042340)
					return 0;
			}
			*(char **) 0x1041d0c = node;
			return 0;
		case 0x1f:
			if (flags[0] & 0x1c) {
				if (*(char *) 0x1040600)
					flags[0] &= 0xe3;
				else
					*(char *) 0x1040600 = 1;
			} else {
				*(char *) 0x1040600 = 0;
				flags[0] = (flags[0] & 0xe7) | 4;
			}
			fcn_00437ac0(*(int *) 0x67a370, 0, 0x1ff,
			             (const char *) 0x456df0);
			fcn_00438af0(0);
			fcn_00436aa0(flags);
			return 0;
		case 0x14:
			*(char *) 0x6b8019 = !*(char *) 0x6b8019;
			return 0;
		case 0x15:
			fcn_00436f70(!*(char *) 0x6b7ff9);
			return 0;
		}
	}
	return 0;
}
