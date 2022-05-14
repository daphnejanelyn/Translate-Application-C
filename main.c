#include <stdio.h>

#define MAX_PAIRS 20
#define MAX_CHARS 150

typedef char str[MAX_CHARS];


typedef struct pairs
{
    str translation;
    str language;
}; 

typedef struct entry
{
    struct pairs pair[10];
    int nPaircount;
};

typedef struct entries
{
    struct entry Entries[150];
    int nEntrycount;
};

void getMenu(int *nMenu)
{
    printf("\n\t\tMAIN MENU\n");
    printf("————————————————————————————————————————————————————\n");
    printf("\'Manage Data\' allows you to  \n");
    printf("\'Language Tools\' allows you to \n");
    printf("To select an option, enter the key enclosed in\n");
    printf("brackets to the left side of the choice\n");
    printf("\n[1] Manage Data\n");
    printf("\n[2] Language Tools\n");
    printf("\n[3] Exit\n");
    printf("————————————————————————————————————————————————————\n");
    printf("Select Option: ");
    scanf("%d", nMenu);
}

void toUpper(char * string)
{
    int i;
    int length = strlen(string);

    for (i = 0; i < length; i++)
    {
        if (string[i] >= 'a' && string[i] <= 'z')
        {
            string[i] -= 32;
        }
    }
    

}

void addEntry(int *nData, int nEntryCount, int nPaircount, struct entries entrydir)
{
    str tempLang;
    str tempTrans;
    str new;
    int i, j;
	str temparr;
	int nFound = 0; 
    printf("Enter language: ");
    fgets(tempLang, MAX_PAIRS, stdin);
    printf("Enter translation: ");
    fgets(tempTrans, MAX_PAIRS, stdin);

    for (i = 0; i < nEntryCount; i++)
    {
		for (j = 0; j < nPaircount; j++)
		{
			
			temparr = entrydir.Entries[i].pair[j].translation; 
			if (strcmp(temparr, tempTrans) == 0)
			{
				temparr = entrydir.Entries[i].pair[j].language;
				if (strcmp(temparr, tempLang) == 0)
					nFound = 1; 
			}
			
		}
    }


    if (nFound = 1)
    {
        /* ask user if this is a new entry */
        printf("Is this a new entry (Y/N)? ");
        scanf(" %s", &new);

        toUpper(new);
        if (strcmp(new, "YES") == 0)
        {
            /* show all entries */

        }

        else if(strcmp(new, "NO") == 0)
        {
            nData = 1;
        }

        
    }

}



int main()
{
    int nMenu, nData = 0;
    struct entries entrydir;
    do
    {
        /* Display and get menu input */
        displayMenu(&nMenu);

        if (nMenu == 1)
        {
            /* display manage data */

            
            do
            {
                /* add entry */

            }
            while (nData != 1);
        }


    } while (nMenu != 3);


}
