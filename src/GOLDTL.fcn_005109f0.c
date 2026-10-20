#pragma intrinsic(strcpy, strcmpi)

int __cdecl fcn_005105a0(int a0);
int __cdecl fcn_005043d0(int a0, int a1);
char* __cdecl fcn_0064d1a0(int a0, int a1);
int __cdecl fcn_0065f220(const char* a0, const char* a1);
char* __cdecl strcpy(char* a0, const char* a1);
int __cdecl strcmpi(const char* a0, const char* a1);
int __cdecl sprintf(char* a0, const char* a1, ...);

/* ADDRESS: GOLDTL 0x005109f0 */
void __cdecl fcn_005109f0(int a0)
{
	char name[128];
	char buf[256];
	int id;
	int v;
	int i;
	char* p;

	if (fcn_005105a0(a0) == 0) {
		return;
	}
	if (*(int*) (a0 + 0x48) != -1 &&
	    *(char*) (a0 + 0x4b) == 2 &&
	    *(int*) (a0 + 0x218) != 0) {
		id = *(int*) (a0 + 0x48) & 0xffffff;
		if (id == 0x47) {
			v = fcn_005043d0(0x47, 0xffff);
			strcpy(name, (char*) fcn_0064d1a0(a0, 0x5f) + 1);
			i = 1;
			p = (char*) 0x868354;
			while (*p != 0) {
				if (strcmpi(name, p) == 0) {
					*(int*) (v + 0x65) = i;
					strcpy((char*) (v + 5), (char*) (0x868060 + i * 0x2f4));
					break;
				}
				p += 0x2f4;
				i++;
				if (p >= (char*) 0x868c30) {
					break;
				}
			}
		} else {
			v = fcn_005043d0(id, 0xffff);
		}
		if (v != 0) {
			sprintf(buf, (char*) 0x6a1bdc, *(int*) (0x14a6558 + id * 56));
			*(int*) (v + 0x61) = a0;
			*(int*) (a0 + 0x204) = v;
		}
	}
	if (*(int*) (a0 + 0x218) == 0 && *(int*) (a0 + 0x1fc) != 0) {
		*(int*) (a0 + 0x204) = *(int*) (*(int*) (a0 + 0x1fc) + 0x204);
	}
}
