// SIZE 0x214
struct node_4034e0 {
	char pad0[0x211];
	unsigned char pad211 : 1;
	unsigned char shown : 1;
	unsigned char pad211b : 6;
	unsigned char pad212 : 2;
	unsigned char attached : 1;
	unsigned char detached : 1;
	unsigned char pad212b : 4;
	unsigned char pad213 : 2;
	unsigned char moving : 1;
};

// SIZE 0x18
struct link_4034e0 {
	struct node_4034e0* node;
	char pad[0x10];
	int next;
};

extern float g_6628a8;

struct link_4034e0* __cdecl m_alloc(int size, const char* tag);
void __cdecl fcn_0043b790(struct node_4034e0*, float*);
void __cdecl fcn_0043b860(struct node_4034e0*, char*);

// FUNCTION: GOLD 0x4034e0

/* Attaches a transport node to an object at the object's anchor point. */
struct link_4034e0* __cdecl fcn_004034e0(char* obj, struct node_4034e0* node)
{
	struct link_4034e0* link;
	char* n;
	float pos[4];

	link = m_alloc(0x18, "ch:ch_AttachTransport");
	n = *(char**) (obj + 0x34);
	pos[0] = (*(float*) (n + 0x19c) + *(float*) (n + 0x18c)) * g_6628a8 - *(float*) (n + 0x1ac) * 70.0f + *(float*) (n + 0x1bc);
	pos[1] = (*(float*) (n + 0x1a0) + *(float*) (n + 0x190)) * g_6628a8 - *(float*) (n + 0x1b0) * 70.0f + *(float*) (n + 0x1c0);
	pos[2] = (*(float*) (n + 0x1a4) + *(float*) (n + 0x194)) * g_6628a8 - *(float*) (n + 0x1b4) * 70.0f + *(float*) (n + 0x1c4);
	fcn_0043b790(node, pos);
	fcn_0043b860(node, *(char**) (obj + 0x34) + 0x84);
	node->moving = 0;
	node->attached = 1;
	node->detached = 0;
	node->shown = 0;
	*(struct link_4034e0**) (obj + 0x124) = link;
	link->next = 0;
	link->node = node;
	return link;
}
