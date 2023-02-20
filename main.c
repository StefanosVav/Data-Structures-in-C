/* Ergasia 2 (Sessions simulation) - Domes dedomenwn 2019  */
/* main.c file */
/* Stefanos Vavoulas */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Session.h"
#define MAX_OPTIONS 18
#define MAX_LIMIT 50

void print_options()
{
	printf("\n");
	printf("0. Exit\n");
	printf("1. Create new session\n");
	printf("2. Create new tab\n");
	printf("3. Show content of tab\n");
	printf("4. Move to the next tab\n");
	printf("5. Move to the previous tab\n");
	printf("6. Switch current tab with the one to the left\n");
	printf("7. Switch current tab with the one to the right\n");	
	printf("8. Set new opening address\n");
	printf("9. Show the default opening address\n");
	printf("10. Move to the next site\n");
	printf("11. Move to the previous site\n");
	printf("12. Show content of current site\n");
	printf("13. Delete current tab(if it's the only one left, end session)\n");	
	printf("14. Completely end session\n");
	printf("15. Open new site\n");	
	printf("\nExtra options to move within sessions\n\n");
	printf("16. Switch to the next session(if you are at the last one, you'll be moved to the first)\n");
	printf("17. Switch to the previous session(if you are at the first one, you'll be moved to the last)\n");
	printf("18. Print number of current session\n");
	printf("Enter your input (0-%d): ", MAX_OPTIONS);
}

int get_option()
{
	char buf[100];
	int option;

	option = -1;
	while (option < 0 || option > MAX_OPTIONS) {
		print_options();
		fgets(buf, sizeof(buf), stdin);
		sscanf(buf, "%d", &option);
	}
	return option;
}

int main(int argc, char *argv[]) {
	InfoSessionPtr 	*Session;
	int option, error, i, n;
	
	printf("Give number of sessions for the simulation\n");
	scanf("%d",&n); getchar();
	printf("The total of sessions is %d, from session number 0 to session number %d\n",n,n-1);
	Session = malloc(n*sizeof(InfoSessionPtr));
	for(i=0; i<n; i++){
		Session[i]=NULL;
	}
	
	printf("Before you start your first session, set a default opening address(max %d characters)\n",MAX_LIMIT);
	char doa[MAX_LIMIT]; //doa stands for default opening address;
	char noa[MAX_LIMIT]; //noa stands for new opening address
	fgets(doa,MAX_LIMIT,stdin);
	i=0;
	do {
		option = get_option();
		switch (option) {
		case 1:
			Session[i] = SessionNew(doa);
			break;
		case 2:
			SessionNewTab(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 3:
			SessionTabShow(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 4:
			SessionTabNext(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 5:
			SessionTabPrev(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 6:
			SessionTabMoveLeft(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 7:
			SessionTabMoveRight(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 8:
			printf("Give new default address:\n");
			if(Session[i]!=NULL){
				fgets(noa,MAX_LIMIT,stdin);
				SessionNewOpeningAddress(noa,Session[i]);
			}else{
				fgets(noa,MAX_LIMIT,stdin);
				strcpy(doa,noa);
			}
			break;
		case 9:
			if(Session[i]!=NULL)
				SessionShowOpeningAddress(Session[i]);
			else
				printf("Default opening address is %s\n",doa);
			break;
		case 10:
			SessionSiteNext(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 11:
			SessionSitePrev(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 12:
			SessionSiteShow(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 13:
			SessionTabClose(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 14:
			SessionClose(Session[i],&error);
			if(error)
				PrintError();
			break;
		case 15:
			printf("Give address for the new site:\n");
			char address[MAX_LIMIT];
			fgets(address,MAX_LIMIT,stdin);
			SessionNewAddress(Session[i],&error,address);
			if(error)
				PrintError();
			break;
		case 16:
			if(i==n-1)
				i=0;
			else
				i++;
			printf("You moved to session number %d\n",i);
			break;
		case 17:
			if(i==0)
				i=n-1;
			else 
				i--;
			printf("You moved to session number %d\n",i);
			break;
		case 18:
			printf("You are at session number %d\n",i);
		break;
		}
	}	while (option);
	free(Session);
	return(0);
}
