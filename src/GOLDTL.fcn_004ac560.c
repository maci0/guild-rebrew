#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "Develop/Units/m_alloc/m_alloc.h"

extern char g_6b5c60[];

typedef struct HistRec {
	int id;
	int begin;
	int end;
	char nname[16];
	char vname[16];
} HistRec;
/* SIZE 0x2c */

int __cdecl fcn_004ac9c0(void* p);

/* ADDRESS: GOLDTL 0x004ac560 */
unsigned int __cdecl fcn_004ac560(void)
{
	char path[0x104];
	char buf[0x100];
	char key[0x100];
	char val[0x100];
	HistRec* krec;
	HistRec* prec;
	int kcnt;
	int pcnt;
	int i;
	int id;
	char* p;

	GetModuleFileNameA(*(HMODULE*) 0x7e1f80, path, 0x104);
	p = strrchr(path, '\\');
	if (p != 0) {
		p[1] = 0;
	}
	strcat(path, "historical.ini");
	GetPrivateProfileStringA("main", "kcnt", g_6b5c60, buf, 0x100, path);
	kcnt = atoi(buf);
	if (kcnt <= 0) {
		return 0xffffffff;
	}
	GetPrivateProfileStringA("main", "pcnt", g_6b5c60, buf, 0x100, path);
	pcnt = atoi(buf);
	if (pcnt <= 0) {
		return 0xffffffff;
	}
	krec = m_alloc((unsigned int) kcnt * sizeof(HistRec), "hmt_CreateBinaryFile");
	if (krec == 0) {
		return 0xffffffff;
	}
	prec = m_alloc((unsigned int) pcnt * sizeof(HistRec), "hmt_CreateBinaryFile");
	if (prec == 0) {
		m_FreeTracked(krec);
		return 0xffffffff;
	}
	memset(krec, 0, (unsigned int) kcnt * sizeof(HistRec));
	memset(prec, 0, (unsigned int) pcnt * sizeof(HistRec));
	id = 0;
	for (i = 0; i < kcnt; i++) {
		krec[i].id = id;
		id++;
		sprintf(key, "k_%i", i);
		GetPrivateProfileStringA(key, "begin", "-1", val, 0x100, path);
		krec[i].begin = atoi(val);
		GetPrivateProfileStringA(key, "nname", g_6b5c60, val, 0x100, path);
		strncpy(krec[i].nname, val, 0xf);
		GetPrivateProfileStringA(key, "end", "-1", val, 0x100, path);
		krec[i].end = atoi(val);
		GetPrivateProfileStringA(key, "vname", g_6b5c60, val, 0x100, path);
		strncpy(krec[i].vname, val, 0xf);
	}
	for (i = 0; i < pcnt; i++) {
		prec[i].id = id;
		id++;
		sprintf(key, "p_%i", i);
		GetPrivateProfileStringA(key, "begin", "-1", val, 0x100, path);
		prec[i].begin = atoi(val);
		GetPrivateProfileStringA(key, "nname", g_6b5c60, val, 0x100, path);
		strncpy(prec[i].nname, val, 0xf);
		GetPrivateProfileStringA(key, "end", "-1", val, 0x100, path);
		prec[i].end = atoi(val);
		GetPrivateProfileStringA(key, "vname", g_6b5c60, val, 0x100, path);
		strncpy(prec[i].vname, val, 0xf);
	}
	if (fcn_004ac9c0(&prec) != 0) {
		m_FreeTracked(krec);
		m_FreeTracked(prec);
		return 0xffffffff;
	}
	m_FreeTracked(krec);
	m_FreeTracked(prec);
	return 0;
}
