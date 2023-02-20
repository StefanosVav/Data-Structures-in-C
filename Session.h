/* Ergasia 2 (Sessions simulation) - Domes dedomenwn 2019  */
/* Session.h linker file for Session.c */
/* Stefanos Vavoulas - AM: 1115201800014 */

#ifndef __SESSION__
#define __SESSION__

typedef struct TabNode *TabNodePtr;
typedef struct SiteNode *SiteNodePtr;
typedef struct InfoSession *InfoSessionPtr;

/* The rest of the interface functions follow */
void PrintError();
InfoSessionPtr SessionNew(char *);
void SessionNewTab(InfoSessionPtr,int *);
void SessionTabShow(InfoSessionPtr,int *);
void SessionTabNext(InfoSessionPtr,int *);
void SessionTabPrev(InfoSessionPtr,int *);
void SessionTabMoveLeft(InfoSessionPtr,int *);
void SessionTabMoveRight(InfoSessionPtr,int *);
void SessionNewOpeningAddress(char *,InfoSessionPtr);
void SessionShowOpeningAddress(InfoSessionPtr);
void SessionSiteNext(InfoSessionPtr,int *);
void SessionSitePrev(InfoSessionPtr,int *);
void SessionSiteShow(InfoSessionPtr,int *);
void SessionTabClose(InfoSessionPtr,int *);
void SessionClose(InfoSessionPtr, int *);
void SessionNewAddress(InfoSessionPtr, int *, char *);
#endif
