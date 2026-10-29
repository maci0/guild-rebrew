typedef struct fcn_004c0a10_node fcn_004c0a10_node;
struct fcn_004c0a10_node {
	int* f0;
	int f4;
	int f8;
	fcn_004c0a10_node* next;
};
// SIZE 0x10

extern char* g_772d34;

void __cdecl fcn_00426170(int*, int);
void __cdecl m_FreeTracked(void*);


/* ADDRESS: GOLDTL 0x004c0a10 */
void __cdecl fcn_004c0a10(int* key)
{
	fcn_004c0a10_node* prev;
	fcn_004c0a10_node* p;

	prev = 0;
	for (p = (*(fcn_004c0a10_node**)&g_772d34); p != 0; p = p->next) {
		if (p->f0 == key) {
			if (prev != 0)
				prev->next = p->next;
			else
				(*(fcn_004c0a10_node**)&g_772d34) = p->next;
			fcn_00426170(p->f0, 0);
			m_FreeTracked(p);
			return;
		}
		prev = p;
	}
}
