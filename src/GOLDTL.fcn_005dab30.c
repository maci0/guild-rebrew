


typedef struct
{
	int x0;
	int id;
	char pad8[0x10];
} Rel;
// SIZE 0x18

int __cdecl fcn_004e6f10(int);
int __cdecl fcn_004e8b80(int, int, Rel*);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c5420(int, int, int, int, int);

void __cdecl fcn_005dab30(unsigned short* who, char* e)
{
	int n;
	Rel list[6];
	char a[0x200];
	char b[0x200];
	int i;
	char* o;

	n = fcn_004e6f10(*(unsigned char*) (e + 0x166));
	n = fcn_004e8b80(n, 6, list);
	for (i = 0; i < n; i++) {
		if (list[i].id == -1) {
			continue;
		}
		if (*(int*) (e + 4) == list[i].id) {
			fcn_004c54c0(*(int*) (who + 2), list[i].id, 100, 1);
			if (e[2] == 6 || e[2] == 7) {
				fcn_0051af00(a, 0x1e0a, *who);
				fcn_00545d40(*(int*) (e + 4), -1, a, 0, 0x5fb, "_NACHRICHTEN_NEU_05");
			}
		} else {
			o = fcn_00508e40(list[i].id);
			if (o != 0) {
				fcn_004c54c0(*(int*) (who + 2), list[i].id, -20, 1);
				if (o[2] == 6 || o[2] == 7) {
					fcn_0051af00(b, 0x1e0b, *who, *(unsigned short*) e, *who);
					fcn_00545d40(*(int*) (o + 4), -1, b, 0, 0x5fb, "_NACHRICHTEN_NEU_06");
				}
			}
		}
	}
	fcn_004c5420(*(int*) (who + 2), 0x1cc, 4, 0x80000, 0);
}
