#include <string.h>

void* __cdecl fcn_00464650(char*);
void* __cdecl fcn_0042e5a0(char*, void*);
int __cdecl fcn_00464a90(void*, unsigned long*, char*, unsigned long, void*, unsigned long, char*, unsigned long);
void __cdecl fcn_0042e520(char*);
void __cdecl fcn_0042e540(char*);
int __cdecl fcn_00465750(void*, unsigned long*, unsigned long*);
void __cdecl fcn_0042ed00(char*, void*, void*, unsigned long, unsigned long, int, unsigned long);
int __cdecl fcn_00464eb0(void*);
void __cdecl fcn_00464a30(void*);

// FUNCTION: GOLD 0x00430130
// SIZE: 294
// FUNCTION: GOLDTL 0x42fb20
// SIZE: 294

/* Mounts every entry of a zip archive under a directory named after the
 * archive. */
void __cdecl fcn_0042fb20(char* path, void* parent, int flags)
{
	void* zip;
	void* dir;
	char* name;
	unsigned long pos;
	unsigned long num;
	unsigned long info[0x14];
	char buf[0x100];

	zip = fcn_00464650(path);
	if (zip == 0) {
		return;
	}
	strcpy(buf, path);
	*strrchr(buf, '.') = 0;
	name = strrchr(buf, '/');
	if (name == 0) {
		name = buf;
	} else {
		name++;
	}
	strcat(name, "/");
	dir = fcn_0042e5a0(name, parent);
	do {
		if (fcn_00464a90(zip, info, buf, 0x100, 0, 0, 0, 0) == 0) {
			fcn_0042e520(buf);
			fcn_0042e540(buf);
			if (info[7] > 0) {
				fcn_00465750(zip, &pos, &num);
				fcn_0042ed00(buf, dir, dir, pos, num, flags, info[4]);
			}
		}
	} while (fcn_00464eb0(zip) == 0);
	fcn_00464a30(zip);
}
