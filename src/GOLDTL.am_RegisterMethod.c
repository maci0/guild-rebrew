#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client_method_registry.h"
#pragma function(memcpy)

extern char g_1008420[];
extern char g_6b5c60[];
extern AM_METHOD g_1008540[];
int __cdecl amt_GetDesireByName(char* name);
/* ADDRESS: GOLDTL 0x00494ed0 */
/* ADDRESS: GOLD 0x00495510 */
int __cdecl am_RegisterMethod(AM_METHOD* d, char* ini)
{
 char key[64];
 char value[128];
 int i;
 int present;
 char* name;
 if(d->type > 0 && d->type < 0x49) {
  if(ini != 0) {
   name=d->name;
   for(i=0;i<4;i++) {
    sprintf(key,"ShortDesire%li",i+1);
    if(GetPrivateProfileStringA(name,key,g_6b5c60,value,128,g_1008420)) {
     d->effects[i].type=amt_GetDesireByName(value);
     sprintf(key,"ShortChange%li",i+1);
     GetPrivateProfileStringA(name,key,g_6b5c60,value,128,g_1008420);
     d->effects[i].value=(float)atof(value);
    } else {d->effects[i].type=0xff;d->effects[i].value=0;}
    sprintf(key,"LongDesire%li",i+1);
    if(GetPrivateProfileStringA(name,key,g_6b5c60,value,128,g_1008420)) {
     d->other_effects[i].type=amt_GetDesireByName(value);
     sprintf(key,"LongChange%li",i+1);
     GetPrivateProfileStringA(name,key,g_6b5c60,value,128,g_1008420);
     d->other_effects[i].value=(float)atof(value);
    } else {d->other_effects[i].type=0xff;d->other_effects[i].value=0;}
   }
   present=0;
   for(i=0; !present; i++) {
    if(i>=4) {
     if(!present) sprintf(value,"am_RegisterMethod(): Methode '%s' hat keinerlei Auswirkungen!!!",name);
     break;
    }
    if((d->effects[i].type != -1 && d->effects[i].value != 0) ||
       (d->other_effects[i].type != -1 && d->other_effects[i].value != 0)) present=1;
   }
   memcpy(d->saved_effects,d->effects,32);
  } else {
   for(i=0;i<4;i++) {
    d->effects[i].type=0xff;d->effects[i].value=0;
    d->other_effects[i].type=0xff;d->other_effects[i].value=0;
    d->saved_effects[i].type=0xff;d->saved_effects[i].value=0;
   }
  }
  g_1008540[d->type]=*d;
 }
 return 1;
}
