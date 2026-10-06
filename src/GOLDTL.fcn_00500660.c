// FUNCTION: GOLDTL 0x00500660

#include <io.h>
#include <string.h>

void __cdecl fcn_00500660(char* dir, int arg, void (__cdecl* visit)(char*))
{
	char path[0x100];
	struct _finddata_t fd;
	long h;

	strcpy(path, dir);
	strcat(path, "*");
	h = _findfirst(path, &fd);
	if (h == -1) {
		return;
	}
	do {
		if (strcmp(fd.name, ".") != 0 && strcmp(fd.name, "..") != 0) {
			if (fd.attrib & _A_SUBDIR) {
				strcpy(path, dir);
				strcat(path, fd.name);
				strcat(path, "\\");
				fcn_00500660(path, arg, visit);
			} else {
				strcpy(path, dir);
				strcat(path, fd.name);
				if (visit != 0) {
					visit(path);
				}
			}
		}
	} while (_findnext(h, &fd) == 0);
	_findclose(h);
}
