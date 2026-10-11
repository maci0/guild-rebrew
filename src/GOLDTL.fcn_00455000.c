// FUNCTION: GOLDTL 0x455000

// SIZE 0x8
typedef struct Link {
	char* e;
	struct Link* next;
} Link;

// SIZE 0x44
typedef struct Cell {
	struct Cell* child[4];
	int pad[8];
	int count;
	int pad2[2];
	Link* head;
	Link* tail;
} Cell;

extern char g_6b89a0[];
extern char g_6b89a4[];

void __cdecl m_pool_free(void*, void*);

char __cdecl fcn_00455000(char* e, Cell* c)
{
	Link* l;
	Link* prev;
	unsigned int i;
	Cell* ch;

	prev = 0;
	for (l = c->head; l != 0; l = l->next) {
		if (l->e == e) {
			break;
		}
		prev = l;
	}
	if (l == 0) {
		return 1;
	}
	if (prev != 0) {
		prev->next = l->next;
	} else {
		c->head = l->next;
	}
	if (c->tail == l) {
		c->tail = prev;
	}
	c->count--;
	m_pool_free(g_6b89a4, l);
	for (i = 0; i < 4; i++) {
		ch = c->child[i];
		if (ch != 0) {
			fcn_00455000(e, ch);
			if (ch->count == 0) {
				m_pool_free(g_6b89a0, ch);
				c->child[i] = 0;
			}
		}
	}
	e[0x217] &= ~1;
	return 1;
}
