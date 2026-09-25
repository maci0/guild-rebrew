// FUNCTION: GOLD 0x004ffff0
// SIZE: 141
// FUNCTION: GOLDTL 0x00502e30
// SIZE: 141

#pragma pack(push, 1)
typedef struct LinkedNode
{
	unsigned short type;
	int entity_id;
	char pad0[0x0e];
	struct LinkedNode* children;
	char pad1[0x27];
	struct LinkedNode* next;
} LinkedNode;
// SIZE 0x43
#pragma pack(pop)

extern int g_773d8c;

void __cdecl fcn_00502f80(void* children);
void __cdecl fcn_00502ec0(void* node);

int __cdecl fcn_00502e30(int a, int b, int c)
{
	LinkedNode** head;
	LinkedNode* node;
	LinkedNode* prev;
	int index;

	head = (LinkedNode**) a;
	prev = 0;
	if (a == 0)
		return -1;
	node = *head;
	if (node == 0)
		return -1;
	index = 0;

	while (node != 0 && node->type != b) {
		prev = node;
		node = node->next;
		index++;
	}
	if (node == 0)
		return -2;

	if (node->children != 0)
		fcn_00502f80(&node->children);
	fcn_00502ec0(node);
	if (index == 0)
		*head = node->next;
	else
		prev->next = node->next;
	node->type = 0;
	g_773d8c--;
	return 0;
}
