

// SIZE 0x4
typedef struct Col {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} Col;

// SIZE 0x7c
typedef struct Slot {
	char* name;
	int rest[30];
} Slot;

typedef void (__cdecl* fcn_00439c90_f)(char*);

void __cdecl fcn_0043a3f0(int, char*, Col);
void __cdecl fcn_0045bfb0(int);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_00434760(char*, int);

void __cdecl fcn_00439c90(char* o)
{
	Col col;
	int i;
	Slot* slots;

	if (*(unsigned char*) (o + 0x49c) < 0xff || (o[0x49e] & 1) != 0) {
		*(int*) &col = 0;
		col.c = 0;
		col.a = 0xff;
		fcn_0043a3f0(*(int*) (o + 0x320), o, col);
	}
	*(int*) (o + 0x310) = 0;
	*(int*) (o + 0x314) = 0;
	if (*(int**) (o + 0x31c) != 0) {
		if (*(char**) (o + 0x318) != 0) {
			for (i = 0; i < *(int*) (*(char**) (o + 0x318) + 0x1e4); i++) {
				if ((*(int**) (o + 0x31c))[i] != 0) {
					fcn_0045bfb0((*(int**) (o + 0x31c))[i]);
				}
			}
		}
		m_FreeTracked(*(int**) (o + 0x31c));
		*(int**) (o + 0x31c) = 0;
	}
	if (*(char**) (o + 0x318) != 0) {
		(*(fcn_00439c90_f*) (*(char**) (o + 0x318) + 0x1ec))(*(char**) (o + 0x318));
		*(char**) (o + 0x318) = 0;
	}
	slots = (Slot*) (o + 0x390);
	for (i = 0; i < 3; i++) {
		if (slots[i].name != 0) {
			fcn_00434760(slots[i].name, 0);
			slots[i].name = 0;
		}
	}
}
