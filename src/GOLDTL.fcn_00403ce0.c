// SIZE 0x218
struct node_403ce0 {
	char pad0[0x214];
	unsigned char pad214 : 7;
	unsigned char shown : 1;
	unsigned char pad215;
	unsigned char attached : 1;
	unsigned char detached : 1;
	unsigned char pad216 : 6;
	unsigned char moving : 1;
};

// SIZE 0x18
struct link_403ce0 {
	struct node_403ce0* node;
	char pad[0x10];
	int next;
};

extern float g_6628a8;
extern float g_6628b8;

struct link_403ce0* __cdecl m_AllocTracked(int size, const char* tag);
void __cdecl fcn_00438b40(struct node_403ce0*, float*);
void __cdecl fcn_00438cb0(struct node_403ce0*, char*);

// FUNCTION: GOLDTL 0x403ce0

/* Attaches a transport node to an object at the object's anchor point. */
struct link_403ce0* __cdecl fcn_00403ce0(char* obj, struct node_403ce0* node)
{
	struct link_403ce0* link;
	char* n;
	float pos[4];

	link = m_AllocTracked(0x18, "ch:ch_AttachTransport");
	n = *(char**) (obj + 0x34);
	pos[0] = (*(float*) (n + 0x19c) + *(float*) (n + 0x18c)) * g_6628a8 - *(float*) (n + 0x1ac) * 70.0f + *(float*) (n + 0x1bc);
	pos[1] = (*(float*) (n + 0x1a0) + *(float*) (n + 0x190)) * g_6628a8 - *(float*) (n + 0x1b0) * 70.0f + *(float*) (n + 0x1c0);
	pos[2] = (*(float*) (n + 0x1a4) + *(float*) (n + 0x194)) * g_6628a8 - *(float*) (n + 0x1b4) * 70.0f + *(float*) (n + 0x1c4);
	fcn_00438b40(node, pos);
	fcn_00438cb0(node, *(char**) (obj + 0x34) + 0x84);
	node->moving = 0;
	node->attached = 1;
	node->detached = 0;
	node->shown = 0;
	*(struct link_403ce0**) (obj + 0x124) = link;
	link->next = 0;
	link->node = node;
	return link;
}
