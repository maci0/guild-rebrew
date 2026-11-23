/* Builds the bounding box of an object and its descendants, then splits the
 * node into four quadrants until either the size limit or the recursion depth
 * limit is reached.  Leaves that survive one level are collapsed. */

char __cdecl fcn_004546e0(char* e, float* lo, float* hi);
char* __cdecl d3_CollectObjectsInBounds(char* src, float* lo, float* hi);
void __cdecl fcn_00454560(char** n);

/* ADDRESS: GOLDTL 0x00454850 */
void __cdecl fcn_00454850(unsigned int* node, unsigned int a1, unsigned int depth, unsigned int maxDepth)
{
	float lo[4];
	float hi[4];
	float d[4];
	unsigned int* p;
	unsigned int v;
	int first;
	char ok;
	unsigned int i;

	if (node[0xc] > 0) {
		*((float*) (node + 4)) = 1.0e10f;
		*((float*) (node + 5)) = 1.0e10f;
		*((float*) (node + 6)) = 1.0e10f;
		*((float*) (node + 8)) = -1.0e10f;
		*((float*) (node + 9)) = -1.0e10f;
		*((float*) (node + 10)) = -1.0e10f;
		if (depth <= 1) {
			for (p = (unsigned int*) node[0xf]; p != 0; p = (unsigned int*) p[1]) {
				if (fcn_004546e0((char*) *p, lo, hi)) {
					*((float*) (node + 4)) = (*((float*) (node + 4)) < lo[0])
						? *((float*) (node + 4)) : lo[0];
					*((float*) (node + 5)) = (*((float*) (node + 5)) < lo[1])
						? *((float*) (node + 5)) : lo[1];
					*((float*) (node + 6)) = (*((float*) (node + 6)) < lo[2])
						? *((float*) (node + 6)) : lo[2];
					*((float*) (node + 8)) = (*((float*) (node + 8)) > hi[0])
						? *((float*) (node + 8)) : hi[0];
					*((float*) (node + 9)) = (*((float*) (node + 9)) > hi[1])
						? *((float*) (node + 9)) : hi[1];
					*((float*) (node + 10)) = (*((float*) (node + 10)) > hi[2])
						? *((float*) (node + 10)) : hi[2];
				}
			}
		} else {
			for (p = (unsigned int*) node[0xf]; p != 0; p = (unsigned int*) p[1]) {
				*((float*) (node + 4)) = (*((float*) (*(unsigned int*) (*p + 0x1ec) + 0x90)) > *((float*) (node + 4)))
					? *((float*) (node + 4)) : *((float*) (*(unsigned int*) (*p + 0x1ec) + 0x90));
				*((float*) (node + 5)) = (*((float*) (*(unsigned int*) (*p + 0x1ec) + 0x94)) > *((float*) (node + 5)))
					? *((float*) (node + 5)) : *((float*) (*(unsigned int*) (*p + 0x1ec) + 0x94));
				*((float*) (node + 6)) = (*((float*) (*(unsigned int*) (*p + 0x1ec) + 0x98)) > *((float*) (node + 6)))
					? *((float*) (node + 6)) : *((float*) (*(unsigned int*) (*p + 0x1ec) + 0x98));
				*((float*) (node + 8)) = (*((float*) (*(unsigned int*) (*p + 0x1ec) + 0xa0)) < *((float*) (node + 8)))
					? *((float*) (node + 8)) : *((float*) (*(unsigned int*) (*p + 0x1ec) + 0xa0));
				*((float*) (node + 9)) = (*((float*) (*(unsigned int*) (*p + 0x1ec) + 0xa4)) < *((float*) (node + 9)))
					? *((float*) (node + 9)) : *((float*) (*(unsigned int*) (*p + 0x1ec) + 0xa4));
				*((float*) (node + 10)) = (*((float*) (*(unsigned int*) (*p + 0x1ec) + 0xa8)) < *((float*) (node + 10)))
					? *((float*) (node + 10)) : *((float*) (*(unsigned int*) (*p + 0x1ec) + 0xa8));
			}
		}
	}
	if (depth < maxDepth && node[0xc] > a1) {
		ok = 1;
		d[0] = (*((float*) (node + 8)) - *((float*) (node + 4))) * 0.5f;
		d[2] = (*((float*) (node + 10)) - *((float*) (node + 6))) * 0.5f;
		first = -1;
		lo[0] = *((float*) (node + 4));
		lo[2] = *((float*) (node + 6));
		hi[0] = d[0] + *((float*) (node + 4));
		hi[2] = d[2] + *((float*) (node + 6));
		node[0] = (unsigned int) d3_CollectObjectsInBounds((char*) node, lo, hi);
		lo[0] = d[0] + *((float*) (node + 4));
		lo[2] = *((float*) (node + 6));
		hi[0] = *((float*) (node + 8));
		hi[2] = d[2] + *((float*) (node + 6));
		node[1] = (unsigned int) d3_CollectObjectsInBounds((char*) node, lo, hi);
		lo[0] = d[0] + *((float*) (node + 4));
		lo[2] = d[2] + *((float*) (node + 6));
		hi[0] = *((float*) (node + 8));
		hi[2] = *((float*) (node + 10));
		node[2] = (unsigned int) d3_CollectObjectsInBounds((char*) node, lo, hi);
		lo[0] = *((float*) (node + 4));
		lo[2] = d[0] + *((float*) (node + 6));
		hi[0] = d[0] + *((float*) (node + 4));
		hi[2] = *((float*) (node + 10));
		node[3] = (unsigned int) d3_CollectObjectsInBounds((char*) node, lo, hi);
		for (i = 0; i < 4; i++) {
			v = node[i];
			if (v != 0) {
				if (first < 0) {
					first = *(int*) (v + 0x30);
				} else {
					if (first != *(int*) (v + 0x30))
						ok = 0;
				}
			}
		}
		for (i = 0; i < 4; i++) {
			v = node[i];
			if (v != 0) {
				if (ok != 0) {
					fcn_00454560((char**) v);
					node[i] = 0;
				} else {
					fcn_00454850((unsigned int*) v, a1, depth + 1, maxDepth);
				}
			}
		}
	}
}
