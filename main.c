#include <stdio.h>
#include <string.h>

#define MAXPAIR 10
#define MAXCHAR 20
#define MAXENTRY 150

typedef char str [21];

typedef struct pairtag
{
    str language;
    str translation; 
}pairtype; 

typedef struct entrytag
{
    pairtype pair [MAXPAIR];
    int nPairCount;
}entrytype;

typedef struct directorytag
{
    entrytype entries [MAXENTRY];
    int nEntryCount; 
}directorytype;

void 
getMenu(int *nMenu)
{
    printf("\n\t\tMAIN MENU\n");
    printf("_______________________________________________\n");
    printf("\'Manage Data\' allows you to  \n");
    printf("\'Language Tools\' allows you to \n");
    printf("To select an option, enter the key enclosed in\n");
    printf("brackets to the left side of the choice\n");
    printf("\n[1] Manage Data\n");
    printf("\n[2] Language Tools\n");
    printf("\n[3] Exit\n");
    printf("_______________________________________________\n");
    printf("Select Option: ");
    scanf("%d", nMenu);
}

void 
toUpper(char * string)
{
    int i;
    int length = strlen(string);

    for (i = 0; i < length; i++)
    {
        if (string[i] >= 'a' && string[i] <= 'z')
            string[i] -= 32;
    }
}

void 
displayEntry (directorytype directory, int index, int nPairCount)
{
    int pair;
    printf ("Language\tTranslation\n");
    for (pair = 0; pair < nPairCount; pair++)
       printf ("%s\t%s\n",directory.entries[index].pair[pair].language, directory.entries[index].pair[pair].translation);
}

void 
addEntry (directorytype * directory, int *nData)
{
    str language; 
    str translation;
    int entry, pair, nCount = 0;
    int nFound = 0; 
    int nEntryCount, nPairCount;
    str newEntry, newPair;

    // Ask for Input
    printf ("Enter Language:");
    scanf ("%s", language);

    printf ("Enter translation:");
    scanf ("%s", translation);

    // Check if pair exists
    for (entry = 0; entry < MAXENTRY; entry++)
    {
        for  (pair = 0; pair < MAXPAIR; pair++)
        {
            if ((strcmp(translation, directory->entries[entry].pair[pair].translation) == 0) 
            && (strcmp (language, directory->entries[entry].pair[pair].language) == 0))
                nFound = 1; 
        }
    }

    // if nFound == 1, show entries with the same information as the one entered first
    if (nFound == 1)
    {
        // Display first entries with the same info
        nEntryCount = directory->nEntryCount;
        nPairCount = directory->entries[nEntryCount -1].nPairCount;
        for (entry = 0; entry < nEntryCount; entry++)
        {
            for  (pair = 0; pair < nPairCount; pair++)
            {
                if ((strcmp(translation, directory->entries[entry].pair[pair].translation) == 0) 
                && (strcmp (language, directory->entries[entry].pair[pair].language) == 0))
                {
                    displayEntry(*directory, entry, nPairCount);
                    nCount++;
                }
            }
            printf ("\n");
        }

        /* Then display all other entries
        for (entry = 0; entry < nEntryCount - nCount; entry++)
        {
            printf ("Language\tTranslation\n");
            for  (pair = 0; pair < nPairCount; pair++)
            {
                if ((strcmp(translation, directory->entries[entry].pair[pair].translation) != 0) 
                || (strcmp (language, directory->entries[entry].pair[pair].language) != 0))
                    displayEntry(*directory, entry, nPairCount);  
            }
            printf ("\n");
        }*/

        printf ("Is this a new entry (Yes or No)?");
        scanf ("%s", newEntry);

        toUpper(newEntry);

        if (strcmp (newEntry, "N0") == 0)
            *nData = -1; // return -1 to return to Manage Data Options
        else if (strcmp (newEntry, "YES") == 0)
        {
            directory->nEntryCount += 1;
            nEntryCount = directory->nEntryCount;
            directory->entries[nEntryCount -1].nPairCount += 1; 
            nPairCount = directory->entries[nEntryCount -1].nPairCount;

            strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].language, language);
            strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].translation, translation);

            // do while user does not choose NO
            do
            {
                printf ("Do you want to encode another pair(Yes/No)?");
                scanf ("%s", newPair);
                toUpper(newPair);

                if (strcmp (newPair, "YES") == 0)
                {
                // Enter new pair
                printf ("Enter Language:");
                scanf ("%s", language);

                printf ("Enter translation:");
                scanf ("%s", translation);

                // Add pair count and Append to current entry
                directory->entries[nEntryCount -1].nPairCount += 1; 
                nPairCount = directory->entries[nEntryCount -1].nPairCount;

                strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].language, language);
                strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].translation, translation);
                }

            } while (strcmp (newPair, "YES") == 0);

        }
    }

    else if (nFound == 0)
    {
        directory->nEntryCount += 1;
        nEntryCount = directory->nEntryCount;
        directory->entries[nEntryCount -1].nPairCount += 1; 
        nPairCount = directory->entries[nEntryCount -1].nPairCount;

        strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].language, language);
        strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].translation, translation);

        // do while user does not choose NO
        do
        {
            printf ("Do you want to encode another pair(Yes/No)?");
            scanf ("%s", newPair);
            toUpper(newPair);

            if (strcmp (newPair, "YES") == 0)
            {
                // Enter new pair
                printf ("Enter Language:");
                scanf ("%s", language);

                printf ("Enter translation:");
                scanf ("%s", translation);

                // Add pair count and Append to current entry
                directory->entries[nEntryCount -1].nPairCount += 1; 
                nPairCount = directory->entries[nEntryCount -1].nPairCount;

                strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].language, language);
                strcpy (directory->entries[nEntryCount -1].pair[nPairCount - 1].translation, translation);
            }

        } while (strcmp (newPair, "YES") == 0);
        *nData = 1; 
    }
}

void
addTranslation(directorytype *directory, int *nData)
{
    str language, translation;
    int entry, pair, nCount = 0; 
    int tempentry [MAXENTRY];
    int i, index;

    printf ("Input Language-Translation pair:");
    scanf ("%s %s", language, translation); 

    // Check if entry exists
    for (entry = 0; entry < MAXENTRY; entry++)
    {
        for  (pair = 0; pair < MAXPAIR; pair++)
        {
            if ((strcmp(translation, directory->entries[entry].pair[pair].translation) == 0) 
            && (strcmp (language, directory->entries[entry].pair[pair].language) == 0))
            {
                tempentry[nCount] = entry; 
                nCount++;
            }
        }
    }
    // entry does not exist, when count is equal to 0
    if (nCount == 0)
    {
        printf ("Entry does not exist.\n");
        printf ("Please press the Add Entry Option");
        *nData = 1; 
    }   
    // entry exist, count is > 0
    else if (nCount > 0)
    {
        for (i = 0; i < nCount; i++)
        {
            index = tempentry[i];
            printf ("Entry # %d\n", i+1);
            displayEntry(*directory, index, directory->entries[index].nPairCount);
            printf ("\n");
        }

        // if count == 1, language translation pair is asked and added to the same entry
        /* if count > 1, user chooses what entry he chooses and  
        langauge translation pair is added to the entry he chooses*/
        

    }

    


}


int 
main ()
{
    int entry, pair;
    int nMenu, nData = 0;
    directorytype directory;
    directory.nEntryCount = 0;

    for (entry = 0; entry < MAXENTRY; entry++)
    {
        directory.entries[entry].nPairCount = 0;
        for (pair = 0; pair < MAXPAIR; pair++)
        {
            directory.entries[entry].pair[pair].translation[MAXCHAR] = '\0';
            directory.entries[entry].pair[pair].language[MAXCHAR] = '\0';
        }
    }

    do
    {
        /* Display and get menu input */
        getMenu(&nMenu);

        if (nMenu == 1)
        {
            /* display manage data */
    
            do
            {
                /* add entry */
                addEntry(&directory, &nData);

            }
            while (nData != 1);
        }


    } while (nMenu != 3);
    printf("%d\n", nMenu);

    return 0;
}
