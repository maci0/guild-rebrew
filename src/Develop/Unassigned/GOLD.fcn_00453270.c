typedef struct Query_453270 {
	char* ref;
	unsigned int count;
	char** list;
	unsigned char flag;
} Query_453270;

typedef union Color_453270 {
	unsigned int u;
	unsigned char b[4];
} Color_453270;

char* __cdecl d3_SelectObjectLod(char* object);
void __cdecl fcn_00452ee0(char* o);
void __cdecl fcn_004522a0(char* o, Query_453270* q);
void __cdecl fcn_00452f90(char* o, char* mesh, int zero, unsigned int color);
char __cdecl fcn_00453100(char* o, void* q);
char __cdecl fcn_00452d80(char* o, void* ctx);
char __cdecl d3_VisitSceneObjectsUntilStopped(char* scene, char* node, unsigned int flags,
	char (__cdecl* callback)(char*, void*), void* context);
void* __cdecl m_alloc(unsigned int, const char*);
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLD 0x00453270 */
char __cdecl fcn_00453270(char* o)
{
	char* mesh;
	char* p;
	Query_453270 q;
	Color_453270 color;
	int i;
	int tmp;
	float v[3];
	float m;
	float s;
	float lum;

	if (*(int*) (o + 0x1cc) == 0) {
		*(char**) (o + 0x1cc) = d3_SelectObjectLod(o);
	}
	mesh = *(char**) (o + 0x1cc);
	if (mesh == 0 || (o[0x212] & 2)) {
		return 0;
	}
	color.u = 0;
	color.b[0] = 0xff;
	(*(int*) 0x633b04)++;
	fcn_00452ee0(o);
	*(int*) 0x633b18 = 0;
	p = *(char**) mesh;
	for (i = 0; i < *(int*) (mesh + 8); i++, p += 0x50) {
		*(int*) (p + 0x30) = *(int*) 0x5fcc78;
		*(int*) (p + 0x34) = *(int*) 0x5fcc7c;
		*(int*) (p + 0x38) = *(int*) 0x5fcc80;
	}
	q.count = 0;
	q.list = 0;
	q.ref = o;
	q.flag = ((unsigned char) o[0x210] >> 5) & 1;
	d3_VisitSceneObjectsUntilStopped(*(char**) (o + 0x208), 0, 10, (char (__cdecl*)(char*, void*)) fcn_00453100, &q);
	if (q.count > 0) {
		q.list = (char**) m_alloc(q.count * 4, "d3_light:cache");
		q.count = 0;
		d3_VisitSceneObjectsUntilStopped(*(char**) (o + 0x208), 0, 10, (char (__cdecl*)(char*, void*)) fcn_00453100, &q);
		fcn_004522a0(o, &q);
		m_FreeTracked(q.list);
		q.list = 0;
	}
	p = *(char**) mesh;
	if (*(char*) 0x633450 != 0) {
		for (i = 0; i < *(int*) (mesh + 8); i++, p += 0x50) {
			v[0] = *(float*) (p + 0x30);
			v[1] = *(float*) (p + 0x34);
			v[2] = *(float*) (p + 0x38);
			m = v[0];
			if (!(m > v[1])) {
				m = v[1];
			}
			if (!(m > v[2])) {
				m = v[2];
			}
			if (m > 255.0f) {
				s = 255.0f / m;
				v[0] = v[0] * s;
				v[1] = v[1] * s;
				v[2] = v[2] * s;
			}
			tmp = (int) v[0];
			p[0x46] = (char) tmp;
			tmp = (int) v[1];
			p[0x45] = (char) tmp;
			tmp = (int) v[2];
			p[0x44] = (char) tmp;
			*(int*) (p + 0x40) = *(int*) (p + 0x44);
		}
	} else {
		for (i = 0; i < *(int*) (mesh + 8); i++, p += 0x50) {
			lum = *(float*) (p + 0x30) * 0.3f + (*(float*) (p + 0x34) * 0.59f + *(float*) (p + 0x38) * 0.11f);
			tmp = (int) lum;
			if ((unsigned int) tmp >= 0xff) {
				tmp = 0xff;
			}
			p[0x46] = (char) tmp;
			*(int*) (p + 0x40) = *(int*) (p + 0x44);
		}
	}
	fcn_00452f90(o, mesh, 0, color.u);
	d3_VisitSceneObjectsUntilStopped(*(char**) (o + 0x208), 0, 4, fcn_00452d80, o);
	*(int*) 0x633b18 = 0;
	o[0x210] |= 4;
	*(int*) (o + 0x44) = *(int*) 0x6333cc;
	*(int*) (*(char**) (o + 0x1ec) + 0x95c) = *(int*) 0x633b10;
	(*(int*) 0x633b04)--;
	return 1;
}
