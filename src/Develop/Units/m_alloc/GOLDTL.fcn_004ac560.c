#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "Develop/Units/m_alloc/m_alloc.h"

extern char g_6b5c60[];
extern int g_7e1f80;

typedef struct HistRec {
	int id;
	int begin;
	int end;
	char nname[16];
	char vname[16];
} HistRec;
/* SIZE 0x2c */

typedef struct HistPair {
	int n0;
	int n1;
	HistRec* r0;
	HistRec* r1;
} HistPair;
/* SIZE 0x10 */

int __cdecl fcn_004ac9c0(HistPair* p);

/* ADDRESS: GOLDTL 0x004ac560 */
unsigned int __cdecl fcn_004ac560(void)
{
	char path[0x104];
	char buf[0x100];
	char key[0x20];

	int i;
	int id;
	char* p;
	HistPair hist;

	memset(&hist, 0, sizeof(hist));

	GetModuleFileNameA((HMODULE) g_7e1f80, path, 0x104);
	p = strrchr(path, '\\');
	p[1] = 0;
	strcat(path, "historical.ini");
	GetPrivateProfileStringA("main", "kcnt", g_6b5c60, buf, 0x100, path);
	hist.n1 = atoi(buf);
	if (hist.n1 <= 0) {
		return 0xffffffff;
	}
	GetPrivateProfileStringA("main", "pcnt", g_6b5c60, buf, 0x100, path);
	hist.n0 = atoi(buf);
	if (hist.n0 <= 0) {
		return 0xffffffff;
	}
	hist.r1 = (HistRec*) m_alloc((unsigned int) hist.n1 * sizeof(HistRec), "hmt_CreateBinaryFile");
	if (hist.r1 == 0) {
		goto err;
	}
	hist.r0 = (HistRec*) m_alloc((unsigned int) hist.n0 * sizeof(HistRec), "hmt_CreateBinaryFile");
	if (hist.r0 == 0) {
		goto err;
	}
	memset(hist.r1, 0, (unsigned int) hist.n1 * sizeof(HistRec));
	memset(hist.r0, 0, (unsigned int) hist.n0 * sizeof(HistRec));
	id = 0;
	for (i = 0; i < hist.n1; i++) {
		hist.r1[i].id = id;
		id++;
		sprintf(key, "k_%i", i);
		GetPrivateProfileStringA(key, "begin", "-1", buf, 0x100, path);
		hist.r1[i].begin = atoi(buf);
		GetPrivateProfileStringA(key, "nname", g_6b5c60, buf, 0x100, path);
		strncpy(hist.r1[i].nname, buf, 0xf);
		GetPrivateProfileStringA(key, "vname", g_6b5c60, buf, 0x100, path);
		strncpy(hist.r1[i].vname, buf, 0xf);
		GetPrivateProfileStringA(key, "end", "-1", buf, 0x100, path);
		hist.r1[i].end = atoi(buf);
	}
	for (i = 0; i < hist.n0; i++) {
		hist.r0[i].id = id;
		id++;
		sprintf(key, "p_%i", i);
		GetPrivateProfileStringA(key, "begin", "-1", buf, 0x100, path);
		hist.r0[i].begin = atoi(buf);
		GetPrivateProfileStringA(key, "nname", g_6b5c60, buf, 0x100, path);
		strncpy(hist.r0[i].nname, buf, 0xf);
		GetPrivateProfileStringA(key, "vname", g_6b5c60, buf, 0x100, path);
		strncpy(hist.r0[i].vname, buf, 0xf);
		GetPrivateProfileStringA(key, "end", "-1", buf, 0x100, path);
		hist.r0[i].end = atoi(buf);
	}
	if (fcn_004ac9c0(&hist) != 0) {
		goto err;
	}
	m_FreeTracked(hist.r1);
	hist.r1 = 0;
	m_FreeTracked(hist.r0);
	return 0;
err:
	if (hist.r1 != 0) {
		m_FreeTracked(hist.r1);
		hist.r1 = 0;
	}
	if (hist.r0 != 0) {
		m_FreeTracked(hist.r0);
	}
	return 0xffffffff;
}
