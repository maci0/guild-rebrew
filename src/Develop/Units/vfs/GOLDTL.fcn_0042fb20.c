#include <string.h>

void* __cdecl unzOpen(const char* path);
void* __cdecl fcn_0042e5a0(char*, void*);
int __cdecl unzGetCurrentFileInfo(void* file, unsigned long* info, char* name, unsigned long name_size, void* extra, unsigned long extra_size, char* comment, unsigned long comment_size);
void __cdecl fcn_0042e520(char*);
void __cdecl fcn_0042e540(char*);
int __cdecl unzGetFilePos(void* file, unsigned long* pos, unsigned long* num);
void __cdecl fcn_0042ed00(char*, void*, void*, unsigned long, unsigned long, int, unsigned long);
int __cdecl unzGoToNextFile(void* file);
void __cdecl unzClose(void*);


/* Mounts every entry of a zip archive under a directory named after the
 * archive. */
/* ADDRESS: GOLDTL 0x0042fb20 */
void __cdecl fcn_0042fb20(char* path, void* parent, int flags)
{
	void* zip;
	void* dir;
	char* name;
	unsigned long pos;
	unsigned long num;
	unsigned long info[0x14];
	char buf[0x100];

	zip = unzOpen(path);
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
		if (unzGetCurrentFileInfo(zip, info, buf, 0x100, 0, 0, 0, 0) == 0) {
			fcn_0042e520(buf);
			fcn_0042e540(buf);
			if (info[7] > 0) {
				unzGetFilePos(zip, &pos, &num);
				fcn_0042ed00(buf, dir, dir, pos, num, flags, info[4]);
			}
		}
	} while (unzGoToNextFile(zip) == 0);
	unzClose(zip);
}
