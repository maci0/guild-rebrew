// FUNCTION: GOLD 0x00422b30
// FUNCTION: GOLDTL 0x0041e2e0

typedef struct Chunk Chunk;

// SIZE 0x10
struct Chunk {
	int used;
	int count;
	int stride;
	Chunk* next;
};

void __cdecl m_FreeTracked(void* p);

void __cdecl fcn_0041e2e0(Chunk** head, char* p)
{
	Chunk** hdr;
	Chunk* c;
	Chunk* prev;

	hdr = (Chunk**) (p - 4);
	if (hdr == 0) {
		return;
	}
	c = *hdr;
	if (c == 0) {
		return;
	}
	if (p < (char*) c + 0x10) {
		return;
	}
	if (p >= (char*) c + c->count * c->stride + 0x10) {
		return;
	}
	*hdr = 0;
	if (--c->used != 0) {
		return;
	}
	if (c == *head) {
		*head = c->next;
		m_FreeTracked(c);
		return;
	}
	prev = *head;
	while (prev->next != c) {
		prev = prev->next;
	}
	prev->next = c->next;
	m_FreeTracked(c);
}
