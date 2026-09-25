// FUNCTION: GOLDTL 0x0041e2e0
// SIZE: 112

typedef struct Chunk Chunk;

// SIZE 0x10
struct Chunk {
	int used;
	int count;
	int stride;
	Chunk* next;
};

void __cdecl fcn_0041ddd0(void* p);

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
		fcn_0041ddd0(c);
		return;
	}
	prev = *head;
	while (prev->next != c) {
		prev = prev->next;
	}
	prev->next = c->next;
	fcn_0041ddd0(c);
}
