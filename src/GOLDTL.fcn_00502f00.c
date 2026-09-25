// FUNCTION: GOLD 0x005000c0
// SIZE: 125
// FUNCTION: GOLDTL 0x00502f00
// SIZE: 125

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

int __cdecl fcn_00502f00(int a, int b, int c)
{
	LinkedNode** head;
	LinkedNode* node;
	LinkedNode* prev;
	int index;

	head = (LinkedNode**) a;
	node = *head;
	prev = 0;
	if (node == 0)
		return -1;
	index = 0;

	while (node != 0 && node->entity_id != b) {
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
