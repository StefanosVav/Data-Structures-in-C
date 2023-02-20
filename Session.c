/* Ergasia 2 (Sessions simulation) - Domes dedomenwn 2019  */
/* Stefanos Vavoulas - AM: 1115201800014 */

#include <stdlib.h>
#include <stdio.h>
#include "Session.h"

struct InfoSession {
	TabNodePtr FirstTab;
	TabNodePtr LastTab;
	TabNodePtr CurrTab;
	TabNodePtr AuxTab;
	char* 	  OpeningAddress;
};

struct TabNode {	
	TabNodePtr PrevTab, NextTab;
	SiteNodePtr FirstSite;
	SiteNodePtr CurrSite;
};

struct SiteNode{
	SiteNodePtr PrevSite, NextSite;
	TabNodePtr UpTab;
	char *Address;
};

/* The rest of the interface functions follow */
void PrintError(){
	printf("Error! Session has not yet been created\n");
}

InfoSessionPtr SessionNew(char * OpeningAddress){
	InfoSessionPtr Session = malloc(sizeof(struct InfoSession));
	TabNodePtr Tab = malloc(sizeof(struct TabNode));
	SiteNodePtr Site = malloc(sizeof(struct SiteNode));
	Session->FirstTab = Tab;
	Session->LastTab = Tab;	
	Session->CurrTab = Tab;	
	Session->AuxTab = NULL;
	Session->OpeningAddress = malloc(50*sizeof(char));
	Session->OpeningAddress = OpeningAddress;
	Tab->NextTab=NULL;
	Tab->PrevTab=NULL;
	Tab->CurrSite=Site;
	Tab->FirstSite=Site;
	Site->NextSite=NULL;
	Site->PrevSite=NULL;
	Site->UpTab=Tab;
	Site->Address = malloc(50*sizeof(char));
	Site->Address = OpeningAddress;
	printf("Session created!\n");
	
	return Session;
}

void SessionNewTab(InfoSessionPtr Session, int *error){
	if(Session){
		*error=0;
		TabNodePtr TabNew = malloc(sizeof(struct TabNode));
		SiteNodePtr SiteNew = malloc(sizeof(struct SiteNode));
		Session->LastTab->NextTab = TabNew;
		Session->FirstTab->PrevTab = TabNew;
		TabNew->PrevTab = Session->LastTab;
		TabNew->NextTab = Session->FirstTab;
		Session->LastTab = TabNew;
		Session->CurrTab = TabNew;
		TabNew->FirstSite = SiteNew;
		TabNew->CurrSite = SiteNew;
		SiteNew->NextSite=NULL;
		SiteNew->PrevSite=NULL;
		SiteNew->UpTab=TabNew;
		SiteNew->Address = malloc(50*sizeof(char));
		SiteNew->Address = Session->OpeningAddress;
		printf("Success!\n");
	}else
		*error=1;
}

void SessionTabShow(InfoSessionPtr Session,int *error){
	if(Session){
		*error=0;
		printf("The content of the current tab is: %s",Session->CurrTab->CurrSite->Address);
	}else
		*error=1;
}

void SessionTabNext(InfoSessionPtr Session,int *error){
	if(!Session)
		*error=1;
	else if(Session->CurrTab->NextTab == NULL){
		*error=0;
		printf("Error! There is only one tab in this session\n");
		}
	else{
		*error=0;
		Session->CurrTab = Session->CurrTab->NextTab;
		printf("Success!\n");
	}
}

void SessionTabPrev(InfoSessionPtr Session,int *error){
	if(!Session)
		*error=1;
	else if(Session->CurrTab->PrevTab == NULL){
		*error=0;
		printf("Error! There is only one tab in this session\n");
		}
	else{
		*error=0;
		Session->CurrTab = Session->CurrTab->PrevTab;
		printf("Success!\n");
	}
}
	
void SessionTabMoveLeft(InfoSessionPtr Session,int *error){
	if(!Session)
		*error=1;
	else if(Session->CurrTab->PrevTab == NULL){
		*error=0;
		printf("Error! There is only one tab in this session\n");
		}
	else if(Session->CurrTab == Session->FirstTab){
		*error=0;
		printf("You are currently at the first tab of the session and thus can't swap with the one to the left\n");
		}
	else{
		*error=0;
		if(Session->FirstTab->NextTab==Session->LastTab)
		{
			TabNodePtr temp = malloc(sizeof(struct TabNode));
			temp = Session->FirstTab;
			Session->FirstTab=Session->LastTab;
			Session->LastTab = temp;
			free (temp);
			printf("Success!\n");
		}else{
			Session->CurrTab->PrevTab->PrevTab->NextTab = Session->CurrTab;
			Session->CurrTab->NextTab->PrevTab = Session->CurrTab->PrevTab;
			Session->CurrTab->NextTab = Session->CurrTab->PrevTab;
			Session->CurrTab->PrevTab = Session->CurrTab->PrevTab->PrevTab;
			Session->CurrTab->PrevTab->NextTab = Session->CurrTab->NextTab;
			Session->CurrTab->PrevTab->PrevTab = Session->CurrTab;
			printf("Success!\n");
		}
	}
}

void SessionTabMoveRight(InfoSessionPtr Session,int *error){
	if(!Session)
		*error=1;
	else if(Session->CurrTab->NextTab == NULL){
		*error=0;
		printf("Error! There is only one tab in this session\n");
		}
	else if(Session->CurrTab == Session->LastTab){
		*error=0;
		printf("You are currently at the last tab of the session and thus can't swap with the one to the right\n");
		}
	else{
		*error=0;
		if(Session->FirstTab->NextTab==Session->LastTab)
		{
			TabNodePtr temp;
			temp = Session->FirstTab;
			Session->FirstTab=Session->LastTab;
			Session->LastTab = temp;
			printf("Success!\n");
		}else{
			Session->CurrTab->PrevTab->NextTab = Session->CurrTab->NextTab;
			Session->CurrTab->NextTab->NextTab->PrevTab = Session->CurrTab;
			Session->CurrTab->NextTab = Session->CurrTab->NextTab->NextTab;
			Session->CurrTab->PrevTab = Session->CurrTab->NextTab;
			Session->CurrTab->NextTab->NextTab = Session->CurrTab;
			Session->CurrTab->NextTab->PrevTab = Session->CurrTab->PrevTab;
			printf("Success!\n");
		}
	}
}

void SessionNewOpeningAddress(char *NewOA,InfoSessionPtr Session)
{
	Session->OpeningAddress = NewOA;
}

void SessionShowOpeningAddress(InfoSessionPtr Session)
{
	printf("Default opening address is %s\n",Session->OpeningAddress);
}

void SessionSiteNext(InfoSessionPtr Session,int *error)
{
	if(!Session)
		*error=1;
	else if(Session->CurrTab->CurrSite->NextSite!=NULL){
		*error=0;
		Session->CurrTab->CurrSite = Session->CurrTab->CurrSite->NextSite;
		printf("Success!\n");
	}
	else{
		*error=0;
		printf("You are currently in the last site and thus can't move to the next one\n");	
	}
}

void SessionSitePrev(InfoSessionPtr Session,int *error)
{
	if(!Session)
		*error=1;
	else if(Session->CurrTab->CurrSite->PrevSite!=NULL){
		*error=0;
		Session->CurrTab->CurrSite = Session->CurrTab->CurrSite->PrevSite;
		printf("Success!\n");
	}
	else{
		*error=0;
		printf("You are currently in the first site and thus can't move to the previous one\n");
	}
}

void SessionSiteShow(InfoSessionPtr Session,int *error)
{
	if(!Session)
		*error=1;
	else
	{	
		*error=0;
		printf("Current site address is %s\n",Session->CurrTab->CurrSite->Address);
	}
}

void SessionTabClose(InfoSessionPtr Session,int *error){
	if(!Session)
		*error=1;
	else if(Session->CurrTab->NextTab==NULL){				//If there is only one tab
		*error=0;
		while(Session->CurrTab->FirstSite->NextSite!=NULL){	//Delete all site nodes
			Session->CurrTab->FirstSite=Session->CurrTab->FirstSite->NextSite;
			free(Session->CurrTab->FirstSite->PrevSite);
		}
		free(Session->CurrTab->CurrSite);
		free(Session->CurrTab);								//Delete the tab node
		free(Session);										//Delete Session
		Session=NULL;
		printf("This was the last tab, session has been deleted\n");
	}
	else if(Session->CurrTab->PrevTab==Session->CurrTab->NextTab){
		*error=0;
		if(Session->FirstTab==Session->CurrTab)
			Session->FirstTab=Session->CurrTab->NextTab;
		if(Session->LastTab==Session->CurrTab)
			Session->LastTab=Session->CurrTab->PrevTab;
		Session->CurrTab=Session->CurrTab->NextTab;					 //Move to the next tab node so you can delete the current one
		while(Session->CurrTab->PrevTab->FirstSite->NextSite!=NULL){ //Delete all site nodes
			Session->CurrTab->PrevTab->FirstSite=Session->CurrTab->PrevTab->FirstSite->NextSite;
			free(Session->CurrTab->PrevTab->FirstSite->PrevSite);
		}
		free(Session->CurrTab->PrevTab->FirstSite);
		free(Session->CurrTab->PrevTab);
		Session->CurrTab->NextTab=NULL;
		Session->CurrTab->PrevTab=NULL;
		printf("Current Tab deleted, you were moved to the next one\n");
	}
	else{
		*error=0;
		if(Session->FirstTab==Session->CurrTab)
			Session->FirstTab=Session->CurrTab->NextTab;
		if(Session->LastTab==Session->CurrTab)
			Session->LastTab=Session->CurrTab->PrevTab;
		Session->CurrTab=Session->CurrTab->NextTab;					 //Move to the next tab node so you can delete the current one
		while(Session->CurrTab->PrevTab->FirstSite->NextSite!=NULL){ //Delete all site nodes
			Session->CurrTab->PrevTab->FirstSite=Session->CurrTab->PrevTab->FirstSite->NextSite;
			free(Session->CurrTab->PrevTab->FirstSite->PrevSite);
		}
		free(Session->CurrTab->PrevTab->FirstSite);
		Session->CurrTab->PrevTab=Session->CurrTab->PrevTab->PrevTab;
		Session->CurrTab->PrevTab->PrevTab->NextTab=Session->CurrTab;
		free(Session->CurrTab->PrevTab);							//Delete the tab node
		printf("Current Tab deleted, you were moved to the next one\n");
	}
}

void SessionClose(InfoSessionPtr Session, int *error)
{
	if(!Session)
		*error=1;
	else if(Session->CurrTab->NextTab==NULL){				//If there is only one tab
		*error=0;
		while(Session->CurrTab->FirstSite->NextSite!=NULL){	//Delete all site nodes
			Session->CurrTab->FirstSite=Session->CurrTab->FirstSite->NextSite;
			free(Session->CurrTab->FirstSite->PrevSite);
		}
		free(Session->CurrTab->CurrSite);
		free(Session->CurrTab);								//Delete the tab node
		free(Session);										//Delete Session
		Session=NULL;
		printf("Session has been deleted\n");
	}
	else{
		*error=0;
		while(Session->CurrTab->NextTab!=Session->CurrTab)				//Delete all tab nodes
		{
			Session->CurrTab=Session->CurrTab->NextTab;					 //Move to the next tab node so you can delete the current one
			while(Session->CurrTab->PrevTab->FirstSite->NextSite!=NULL){ //Delete all site nodes
				Session->CurrTab->PrevTab->FirstSite=Session->CurrTab->PrevTab->FirstSite->NextSite;
				free(Session->CurrTab->PrevTab->FirstSite->PrevSite);
			}
			free(Session->CurrTab->PrevTab->FirstSite);
			Session->CurrTab->PrevTab=Session->CurrTab->PrevTab->PrevTab;
			Session->CurrTab->PrevTab->PrevTab->NextTab=Session->CurrTab;
			free(Session->CurrTab->PrevTab);							//Delete the tab node
		}
		free(Session->CurrTab);
		free(Session);										//Delete Session
		Session=NULL;
		printf("Session has been deleted\n");
	}
	
}

void SessionNewAddress(InfoSessionPtr Session, int *error, char *NewAddress)
{
	if(!Session)
		*error=1;
	else{
		*error=0;												//This first part is about deleting the sites next to the CurrSite in case it's not the last one
		if(Session->CurrTab->CurrSite->NextSite!=NULL)			//If we are not at the last site
		{
			SiteNodePtr temp;
			temp = Session->CurrTab->CurrSite;
			while(Session->CurrTab->CurrSite->NextSite!=NULL)	//Move to the next site until you reach the last one
				Session->CurrTab->CurrSite = Session->CurrTab->CurrSite->NextSite;
			while(Session->CurrTab->CurrSite!=temp){			//Then move to the previous sites, each time clearing the space of the site you are in
				Session->CurrTab->CurrSite = Session->CurrTab->CurrSite->PrevSite;
				free(Session->CurrTab->CurrSite->NextSite);
				Session->CurrTab->CurrSite->NextSite = NULL;	
			}
		}
		SiteNodePtr NewSite = malloc(sizeof(struct SiteNode));
		Session->CurrTab->CurrSite->NextSite = NewSite;
		NewSite->PrevSite = Session->CurrTab->CurrSite;
		NewSite->NextSite = NULL;
		NewSite->UpTab = Session->CurrTab;
		NewSite->Address = malloc(50*sizeof(char));
		NewSite->Address = NewAddress;
	}
}
