#ifndef SERVER_STATS_H
#define SERVER_STATS_H

void __cdecl srv_FormatStatAttributes(char* entity, char* out);
void __cdecl srv_FormatStatSkills(unsigned char* entity, char* out);
void __cdecl srv_FormatStatTreasury(unsigned short* entity, char* out);
void __cdecl srv_FormatStatAemter(unsigned char* entity, char* out);

void __cdecl srv_FormatStatDumpBegin(void);
void __cdecl srv_FormatStatDumpEnd(void);

extern char g_68d780[][24];
extern char* g_14a6544[];
extern char* g_14a6538[];
extern char* g_14a5770[];
extern char* g_14a57e0[];
extern char* g_14a5b54[];

void __cdecl srv_FormatStatIdentity(unsigned char* entity, char* out);

#endif
