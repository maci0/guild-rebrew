import re

# 1. cm_ExFree.c
with open('src/server.dll/DieGildeAddOn/command/command_c/cm_ExFree.c', 'r') as f:
    content = f.read()
content = re.sub(r'extern int __cdecl ResolveEntityById\(void\*\*, void\*\*, ushort\*\*, int\);\n', '', content)
with open('src/server.dll/DieGildeAddOn/command/command_c/cm_ExFree.c', 'w') as f:
    f.write(content)

# 2. aemter.c
with open('src/server.dll/DieGildeAddOn/game/aemter.c', 'r') as f:
    content = f.read()
content = content.replace('dep_slot_status;', 'dep_slot_status = 0;')
content = content.replace('target_ptr = &aemter_records[office_index].slots;', 'target_ptr = (char*)&aemter_records[office_index].slots;')
content = content.replace('child_ptr = &aemter_records[office_index].slots;', 'child_ptr = (char*)&aemter_records[office_index].slots;')
content = content.replace('office_state = calloc(1, 0x140);', 'office_state = (int)calloc(1, 0x140);')
content = content.replace('office_state = calloc(1, 0x110);', 'office_state = (int)calloc(1, 0x110);')
with open('src/server.dll/DieGildeAddOn/game/aemter.c', 'w') as f:
    f.write(content)

# 3. alchemistry_logic.c
with open('src/server.dll/DieGildeAddOn/game/alchemistry_logic.c', 'r') as f:
    content = f.read()
content = content.replace('entity_ptr = StartFilteredEntitySearch(0, 1, building_index);', 'entity_ptr = (int)StartFilteredEntitySearch(0, 1, building_index);')
content = content.replace('RemoveObjectByType(target_building, 0xcb, 1);', 'RemoveObjectByType((int*)target_building, 0xcb, 1);')
content = content.replace('extern int get_field_by_type(int, int);', 'extern int get_field_by_type(char*, int);')
content = content.replace('return;', 'return 0;') # for warning C4715 in get_field_by_type (if it returns int)
with open('src/server.dll/DieGildeAddOn/game/alchemistry_logic.c', 'w') as f:
    f.write(content)

