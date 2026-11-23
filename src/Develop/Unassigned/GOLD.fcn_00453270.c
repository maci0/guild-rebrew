typedef struct Query_453270 {
	char* ref;
	unsigned int count;
	char** list;
	unsigned char flag;
} Query_453270;

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
	unsigned int color;
	int i;
	int tmp;
	float v[3];
	float m;
	float s;
	float lum;
	int* pr;
	int* pg;
	int* pb;

	if (*(int*) (o + 0x1cc) == 0) {
		*(char**) (o + 0x1cc) = d3_SelectObjectLod(o);
	}
	mesh = *(char**) (o + 0x1cc);
	if (mesh == 0 || (o[0x212] & 2)) {
		return 0;
	}
	color = 0;
	(*(int*) 0x633b04)++;
	*(unsigned char*) &color = 0xff;
	fcn_00452ee0(o);
	*(int*) 0x633b18 = 0;
	for (i = 0; i < *(int*) (mesh + 8); i++) {
		p = *(char**) mesh + i * 0x50 + 0x34;
		*(int*) (p - 4) = *(int*) 0x5fcc78;
		*(int*) p = *(int*) 0x5fcc7c;
		*(int*) (p + 4) = *(int*) 0x5fcc80;
	}
	q.ref = o;
	q.count = 0;
	q.list = 0;
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
	if (*(char*) 0x633450 != 0) {
		pr = &tmp;
		pg = &tmp;
		pb = &tmp;
		for (i = 0; i < *(int*) (mesh + 8); i++) {
			p = *(char**) mesh + i * 0x50 + 0x34;
			v[0] = *(float*) (p - 4);
			v[1] = *(float*) p;
			v[2] = *(float*) (p + 4);
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
			*pr = (int) v[0];
			p[0x12] = (char) tmp;
			*pg = (int) v[1];
			p[0x11] = (char) tmp;
			*pb = (int) v[2];
			p[0x10] = (char) tmp;
			*(int*) (p + 0xc) = *(int*) (p + 0x10);
		}
	} else {
		for (i = 0; i < *(int*) (mesh + 8); i++) {
			p = *(char**) mesh + i * 0x50 + 0x34;
			lum = *(float*) (p + 4) * 0.11f + *(float*) p * 0.59f + *(float*) (p - 4) * 0.3f;
			tmp = (int) lum;
			if ((unsigned int) tmp >= 0xff) {
				tmp = 0xff;
			}
			p[0x12] = (char) tmp;
			*(int*) (p + 0xc) = *(int*) (p + 0x10);
		}
	}
	fcn_00452f90(o, mesh, 0, color);
	d3_VisitSceneObjectsUntilStopped(*(char**) (o + 0x208), 0, 4, fcn_00452d80, o);
	*(int*) 0x633b18 = 0;
	o[0x210] |= 4;
	*(int*) (o + 0x44) = *(int*) 0x6333cc;
	*(int*) (*(char**) (o + 0x1ec) + 0x95c) = *(int*) 0x633b10;
	(*(int*) 0x633b04)--;
	return 1;
}
