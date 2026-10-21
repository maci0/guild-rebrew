#include <math.h>

typedef struct {
	float u;
	float v;
} UvPair;

/* SIZE 0x38 */
typedef struct {
	UvPair uv[3];
	int idx[3];
	int mat;
	int tex;
	int n[3];
} MeshFace;

typedef struct {
	char pad0[0x40];
	void* verts;
	int nverts;
	MeshFace* faces;
	int nfaces;
	char pad50[0x240];
	int total;
	UvPair* uvs;
	unsigned short* indices;
	int* vrepeat;
} MeshObj;

void* __cdecl m_alloc(unsigned int size, const char* file_and_line);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x0044a9f0 */
void __cdecl fcn_0044a9f0(MeshObj* m)
{
	int* counts;
	int* repeat;
	int* list;
	int max;
	int v;
	int f;
	int k;
	int i;
	int j;
	int cnt;
	int total;
	int entry;
	int other;
	int face;
	int corner;
	int uv_index;
	int stride;
	unsigned short* ip;

	counts = (int*) m_alloc(m->nverts * 4, (char*) 0x67ae90);
	m->indices = (unsigned short*) m_alloc(m->nfaces * 6, (char*) 0x67ae78);
	for (f = 0; f < m->nfaces; f++) {
		for (k = 0; k < 3; k++) {
			m->indices[f * 3 + k] = (unsigned short) m->faces[f].idx[k];
		}
	}
	for (f = 0; f < m->nfaces; f++) {
		for (k = 0; k < 3; k++) {
			counts[m->faces[f].idx[k]]++;
		}
	}
	max = 0;
	for (v = 0; v < m->nverts; v++) {
		max = counts[v] > max ? counts[v] : max;
	}
	max = max + 1;
	m_FreeTracked(counts);
	repeat = (int*) m_alloc(m->nverts * max * 4, (char*) 0x67ae90);
	for (f = 0; f < m->nfaces; f++) {
		for (k = 0; k < 3; k++) {
			v = m->faces[f].idx[k];
			repeat[v * max + 1 + repeat[v * max]] = k | 0x40000000;
			repeat[v * max]++;
		}
	}
	total = 0;
	list = repeat;
	for (v = 0; v < m->nverts; v++) {
		cnt = list[0];
		total += cnt;
		if (cnt > 0) {
			for (i = 1; i < cnt; i++) {
				entry = list[i];
				if (!(entry & 0x40000000)) {
					continue;
				}
				face = (entry & 0x3ffffff) / 3;
				corner = (entry & 0x3ffffff) % 3;
				for (j = i + 1; j < cnt; j++) {
					other = list[j];
					if (!(other & 0x40000000)) {
						continue;
					}
					if (fabs(m->faces[face].uv[corner].u -
					         m->faces[(other & 0x3ffffff) / 3].uv[(other & 0x3ffffff) % 3].u) <= *(float*) 0x662d04
					    && fabs(m->faces[face].uv[corner].v -
					         m->faces[(other & 0x3ffffff) / 3].uv[(other & 0x3ffffff) % 3].v) <= *(float*) 0x662d04) {
						list[j] = other & 0x3fffffff;
						total--;
					}
				}
			}
		}
		list += max;
	}
	if (total <= m->nverts) {
		total = m->nverts;
	}
	m->uvs = (UvPair*) m_alloc(total * 8, (char*) 0x67ae64);
	m->vrepeat = (int*) m_alloc(m->nverts * 4, (char*) 0x67ae44);
	uv_index = 0;
	list = repeat;
	stride = max * 4;
	for (v = 0; v < m->nverts; v++) {
		cnt = list[0];
		for (i = 0; i < cnt; i++) {
			entry = list[i + 1];
			if (!(entry & 0x40000000)) {
				continue;
			}
			face = (entry & 0x3ffffff) / 3;
			corner = (entry & 0x3ffffff) % 3;
			m->uvs[uv_index].u = m->faces[face].uv[corner].u;
			m->uvs[uv_index].v = m->faces[face].uv[corner].v;
			if (m->vrepeat[v] > 0) {
				for (k = 0; k < m->nfaces * 3; k++) {
					ip = &m->indices[k];
					other = *ip & 0xffff;
					if (other >= uv_index) {
						(*ip)++;
					}
					else if (other == uv_index - m->vrepeat[v]) {
						if (fabs(m->faces[k / 3].uv[k % 3].u -
						         m->uvs[uv_index].u) <= *(float*) 0x662d04
						    && fabs(m->faces[k / 3].uv[k % 3].v -
						         m->uvs[uv_index].v) <= *(float*) 0x662d04) {
							*ip = (unsigned short) uv_index;
						}
					}
				}
			}
			m->vrepeat[v]++;
			uv_index++;
		}
		list = (int*) ((char*) list + stride);
	}
	m->total = total;
	m_FreeTracked(repeat);
}
