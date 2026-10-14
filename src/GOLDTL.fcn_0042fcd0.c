#include <io.h>
#include <direct.h>
#include <string.h>

char* __cdecl fcn_0042f420(char* node, char* stop, char* out);

/* ADDRESS: GOLD 0x004302e0 */
/* ADDRESS: GOLDTL 0x0042fcd0 */

/* Creates every missing directory on the way to a file path. */
char __cdecl fcn_0042fcd0(char* path, char* node)
{
	char* s;
	long h;
	char p[0x100];
	char rest[0x100];
	char cur[0x100];
	char base[0x100];
	struct _finddata_t fd;

	if (path == 0 || *path == 0) {
		return 0;
	}
	strcpy(p, path);
	s = strrchr(p, '/');
	if (s != 0) {
		fcn_0042f420(node, 0, base);
		s[1] = 0;
		strcpy(rest, p);
		s = strchr(rest, '/');
		while (s != 0) {
			s++;
			strcpy(p, s);
			*s = 0;
			strcat(base, rest);
			strcpy(cur, base);
			s = strrchr(cur, '/');
			if (s != 0) {
				*s = 0;
			}
			h = _findfirst(cur, &fd);
			if (h == -1) {
				if (_mkdir(cur) != 0) {
					return 0;
				}
			} else {
				_findclose(h);
			}
			strcpy(rest, p);
			s = strchr(rest, '/');
		}
	}
	return 1;
}
