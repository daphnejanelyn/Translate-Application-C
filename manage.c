#include "translate.h"

void
getInput(char * string) 
{
  int i;
  char c;
  
  i = 0;
  do 
  {
    scanf("%c", &c);
    if (c != '\n') 
	{
      string[i] = c;
      i++;
    }
  } while (c != '\n');
  string[i] = '\0';
}

void 
getMenu(int *nMenu)
{
    char temp;
    printf("\n\t\tMAIN MENU\n");
    printf("_______________________________________________\n");
    printf("\'Manage Data\' allows you to  \n");
    printf("\'Language Tools\' allows you to \n");
    printf("To select an option, enter the key enclosed in\n");
    printf("brackets to the left side of the choice\n");
    printf("\n[1] Manage Data\n");
    printf("\n[2] Language Tools\n");
    printf("\n[0] Exit\n");
    printf("_______________________________________________\n");
    printf("Select Option: ");
    scanf("%d", nMenu);
    scanf("%c", &temp);
}

void
getData(int *nData)
{
    char temp;
    printf("\n\t\tMANAGE DATA\n");
    printf("_______________________________________________\n");
    printf("To select an option, enter the key enclosed in\n");
    printf("brackets to the left side of the choice\n");
    printf("[1] Add Entry\n");
    printf("[2] Add Translations\n");
    printf("[3] Modify Entry\n");
    printf("[4] Delete Entry\n");
    printf("[5] Delete Translation\n");
    printf("[6] Display All Entries\n");
    printf("[7] Search Word\n");
    printf("[8] Search Translations\n");
    printf("[9] Export\n");
    printf("[10] Import\n");
    printf("[0] Exit\n");
    printf("_______________________________________________\n");
    printf("Select Option: ");
    scanf("%d", nData);
    scanf("%c", &temp);
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
    printf ("\tLanguage\tTranslation\n");
    for (pair = 0; pair < nPairCount; pair++)
       printf ("(%d) %s\t%s\n", pair + 1, directory.entries[index].pair[pair].language, directory.entries[index].pair[pair].translation);
}

void
getNewPair(directorytype * directory, int entryIndex)
{
    str language, translation;
    int nPairCount; 

    printf ("Enter Language:");
    
    getInput(language);

    printf ("Enter translation:");
    getInput(translation);

    // Add pair count and Append to current entry
    directory->entries[entryIndex].nPairCount += 1; 
    nPairCount = directory->entries[entryIndex].nPairCount;

    strcpy (directory->entries[entryIndex].pair[nPairCount - 1].language, language);
    strcpy (directory->entries[entryIndex].pair[nPairCount - 1].translation, translation);
}

void 
addEntry (directorytype * directory)
{
    str language; 
    str translation;
    int entry, pair;
    int nFound = 0; 
    int nEntryCount, nPairCount; 
    str newEntry, newPair;

    // Ask for Input
    printf ("Enter Language:");
    getInput(language);

    printf ("Enter translation:");
    getInput(translation);

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
        for (entry = 0; entry < nEntryCount; entry++)
        {
            nPairCount = directory->entries[entry].nPairCount;
            for (pair = 0; pair < nPairCount; pair++)
            {
                if ((strcmp(translation, directory->entries[entry].pair[pair].translation) == 0) 
                && (strcmp (language, directory->entries[entry].pair[pair].language) == 0))
                {
                    displayEntry(*directory, entry, nPairCount);
                    pair = nPairCount;
                }
            }
            printf ("\n");
        }
            

        /*Then display all other entries
        for (entry = 0; entry < nEntryCount; entry++)
        {
            nPairCount = directory->entries[entry].nPairCount;
            for (pair = 0; pair < nPairCount; pair++)
            {
                if ((strcmp (language, directory->entries[entry].pair[pair].language) != 0)
                || (strcmp(translation, directory->entries[entry].pair[pair].translation) != 0))
                {
                    displayEntry(*directory, entry, nPairCount);
                    pair = nPairCount;
                }  
            }
            printf ("\n");
        }*/

        printf ("Is this a new entry (Yes or No)?");
        getInput(newEntry);

        toUpper(newEntry);


        if (strcmp (newEntry, "YES") == 0)
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
                getInput(newPair);
                toUpper(newPair);

                if (strcmp (newPair, "YES") == 0)
                {
                    getNewPair(directory, nEntryCount - 1);
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
            getInput(newPair);
            toUpper(newPair);

            if (strcmp (newPair, "YES") == 0)
            {
                // Enter new pair
                getNewPair(directory, nEntryCount - 1);
            }

        } while (strcmp (newPair, "YES") == 0);
        
    }
}

void
addTranslation(directorytype * directory)
{
    str language, translation;
    int entry, pair, nCount = 0; 
    int tempentry [MAXENTRY];
    int i, index;
    int newentry, nPairCount;
    str newPair;
    char temp;
    
    // Enter new pair
    printf ("Enter Language:");
    getInput (language);

    printf ("Enter translation:");
    getInput (translation);

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
        if (nCount == 1 && directory->entries[tempentry[0]].nPairCount < 10)
        {
            // Enter new pair
            printf ("Enter Language:");
            getInput (language);

            printf ("Enter translation:");
            getInput (translation);

            // Add pair count and Append to current entry
            directory->entries[tempentry[0]].nPairCount += 1; 
            nPairCount = directory->entries[tempentry[0]].nPairCount;

            strcpy (directory->entries[tempentry[0]].pair[nPairCount - 1].language, language);
            strcpy (directory->entries[tempentry[0]].pair[nPairCount - 1].translation, translation);

            do
            {
                printf ("Do you want to encode another pair(Yes/No)?");
                getInput(newPair);
                toUpper(newPair);

                if (strcmp (newPair, "YES") == 0)
                {
                    //Enter new pair
                    getNewPair(directory, tempentry[0]);
                }

            } while (strcmp (newPair, "YES") == 0 && directory->entries[tempentry[0]].nPairCount <= 10);
        }
        /* if count > 1, user chooses what entry he chooses and  
        langauge translation pair is added to the entry he chooses*/
        else if (nCount > 1 && directory->entries[tempentry[0]].nPairCount < 10)
        {
            printf ("Choose Entry to add a language-translation pair:");
            scanf ("%d", &newentry);
            scanf("%c", &temp);

            // Enter new pair
            printf ("Enter Language:");
            getInput (language);

            printf ("Enter translation:");
            getInput (translation);

            // Add pair count and Append to chosen entry
            directory->entries[tempentry[newentry -1]].nPairCount += 1; 
            nPairCount = directory->entries[tempentry[newentry -1]].nPairCount;

            strcpy (directory->entries[tempentry[newentry -1]].pair[nPairCount - 1].language, language);
            strcpy (directory->entries[tempentry[newentry -1]].pair[nPairCount - 1].translation, translation);
            do
            {
                printf ("Do you want to encode another pair(Yes/No)?");
                getInput (newPair);
                toUpper(newPair);

                if (strcmp (newPair, "YES") == 0)
                {
                    // Enter new pair
                    getNewPair(directory, tempentry[newentry -1]);
                }
            } while (strcmp (newPair, "YES") == 0 && directory->entries[tempentry[newentry -1]].nPairCount <= 10);
        }
    }
}


void 
sortAlphabetical(directorytype * directory, int entryIndex)
{
    int nPairCount; 
    int i, j, position;
    str temp[2];

    nPairCount = directory->entries[entryIndex].nPairCount;

    for(i = 0; i < nPairCount - 1; i++)
	{
		position = i;
		for(j = i + 1; j < nPairCount; j++)
		{
			if(strcmp (directory->entries[entryIndex].pair[position].language, directory->entries[entryIndex].pair[j].language) > 0)
                position = j;
		}
		if(position != i)
		{
			strcpy(temp[0], directory->entries[entryIndex].pair[i].language); 
            strcpy(temp[1], directory->entries[entryIndex].pair[i].translation);
			strcpy (directory->entries[entryIndex].pair[i].language, directory->entries[entryIndex].pair[position].language);
            strcpy (directory->entries[entryIndex].pair[i].translation, directory->entries[entryIndex].pair[position].translation);
			strcpy (directory->entries[entryIndex].pair[position].language, temp[0]);
            strcpy (directory->entries[entryIndex].pair[position].translation, temp[1]);
		}
	}
}

void
displayAll (directorytype * directory)
{ 
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    int i = 0;
    char cOption;
    char cTemp;

    do
    {
        sortAlphabetical(directory, i);
        nPairCount = directory->entries[i].nPairCount;
        printf("Entry #%d\n", i+1);
        displayEntry(*directory, i, nPairCount);
        printf("_______________________________________________\n");
        printf("[N] Next Entry\n");
        printf("[P] Previous Entry\n");
        printf("[X] End Display\n");
        printf("_______________________________________________\n");
        printf("Enter option: ");
        scanf("%c", &cOption);
        scanf("%c", &cTemp);

        if (cOption == 'N')
            i++;
        else if (cOption == 'P')
            i--;
        else if (cOption == 'X')
            i = nEntryCount;
        else
            printf("Invalid Option");
            
    }
    while (i < nEntryCount);
}

void
modifyEntry(directorytype * directory)
{
    int nEntry, nPair;
    char temp;
    str choice, input, modify;
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    displayAll(directory);

    printf("Which entry do you want to modify? ");
    scanf("%d", &nEntry);
    scanf("%c", &temp);
    if (!(nEntry >= 1 && nEntry <= nEntryCount))
    {
        printf("Invalid Input\n");
    }
    else
    {
        nPairCount = directory->entries[nEntry-1].nPairCount;

        do 
        {
            
            do
            {
                printf("Which pair do you want to modify? ");
                scanf("%d", &nPair);
                scanf("%c", &temp);
                if (!(nPair >= 1 && nPair <= nPairCount))
                    printf("Invalid Input\n");

            } while (!(nPair >= 1 && nPair <= nPairCount));

            do
            {
                
                printf ("Modify language or translation: ");
                getInput(choice);
                toUpper (choice);

                if (strcmp (choice, "LANGUAGE") == 0)
                {
                    printf ("Input language:");
                    getInput (input);
                    strcpy (directory->entries[nEntry -1].pair[nPair -1].language, input);
                }
                else if (strcmp(choice, "TRANSLATION") == 0)
                {
                    printf ("Input translation:");
                    getInput (input);

                    strcpy(directory->entries[nEntry-1].pair[nPair -1].translation, input);
    
                }
                else
                    printf("Invalid Input\n");
                
            } while (!(strcmp(choice, "TRANSLATION") == 0 || strcmp (choice, "LANGUAGE") == 0));
            
            printf ("More modifications for the entry (Yes/No)?");
            getInput (modify);
            toUpper(modify);

        } while (strcmp(modify, "YES") == 0);
    
    }
}

void
deleteEntry (directorytype *directory)
{
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    int deleteEntry;
    char temp;
    int i, j;
    displayAll (directory);
    printf("Which entry do you want to delete? ");
    scanf("%d", &deleteEntry);
    scanf("%c", &temp);

    if (deleteEntry >= 1 && deleteEntry <= nEntryCount)
    {
        for (i = deleteEntry - 1; i < nEntryCount - 1; i++)
        {
            nPairCount = directory->entries[i].nPairCount;
            for (j = 0; j < nPairCount; j++)
            {
                strcpy(directory->entries[i].pair[j].translation,"\0");
                strcpy(directory->entries[i].pair[j].language,"\0");
            }

            nPairCount = directory->entries[i + 1].nPairCount;
            for (j = 0; j < nPairCount; j++)
            {
                strcpy(directory->entries[i].pair[j].translation, directory->entries[i + 1].pair[j].translation);
                strcpy(directory->entries[i].pair[j].language, directory->entries[i + 1].pair[j].language);
            }
        }

        for (j = 0; j < nPairCount; j++)
        {
            strcpy(directory->entries[nEntryCount-1].pair[j].translation,"\0");
            strcpy(directory->entries[nEntryCount-1].pair[j].language,"\0");
        }
        directory->nEntryCount -= 1;
        nEntryCount = directory->nEntryCount;
        
    }
    else printf("Invalid Input\n");

}
void
deleteTranslation(directorytype *directory)
{
    int deletePair, nPairCount, entry;
    int nEntryCount = directory->nEntryCount; 
    char temp;
    int i;
    str choice; 
    strcpy(choice, "YES");
    displayAll(directory);
    
    printf("Which entry do you want to delete from? ");
    scanf("%d", &entry);

    if (entry >= 1 && entry <= nEntryCount)
    {
        do
        {
            nPairCount = directory->entries[entry - 1].nPairCount;
            if (nPairCount == 1)
                deleteEntry(directory);
            else
            {
                do
                {
                    printf("Which language-translation pair do you want to delete? ");
                    scanf("%d", &deletePair);
                    scanf("%c", &temp);
                    if (!(deletePair >= 1 && deletePair <= nPairCount))
                    {
                        printf("Invalid Input\n");
                        printf("Do you still want to delete a pair (Yes/No)? ");
                        getInput (choice);
                        toUpper (choice);
                    }

                } while (!(!(deletePair >= 1 && deletePair <= nPairCount) || strcmp(choice, "YES") == 0));

            
                if (strcmp(choice, "YES") == 0)
                {
                    for (i = deletePair - 1; i < nPairCount - 1; i++)
                    {
                        strcpy (directory->entries[entry-1].pair[i].language, directory->entries[entry-1].pair[i+1].language);
                        strcpy (directory->entries[entry-1].pair[i].translation, directory->entries[entry-1].pair[i+1].translation);
                    } 
                    
                    strcpy(directory->entries[entry-1].pair[nPairCount-1].translation,"\0");
                    strcpy(directory->entries[entry-1].pair[nPairCount-1].language,"\0");

                    directory->entries[entry - 1].nPairCount -= 1;
    
                    printf("Do you want to delete another entry(Yes/No)? ");
                    getInput(choice);
                    toUpper(choice);
                }
            }
        } while (strcmp(choice, "YES") == 0);
    }
    else printf ("Invalid Input\n");
}

void
searchWord (directorytype *directory)
{
    str word;
    int entry, pair;
    int nEntryCount = directory->nEntryCount;
    int nPairCount, nCount = 0;
    int tempMatch[MAXENTRY];
    int index, i;

    printf ("Input word: ");
    getInput(word);

    for (entry = 0; entry < nEntryCount; entry++)
    {
        nPairCount = directory->entries[entry].nPairCount;
        for  (pair = 0; pair < nPairCount; pair++)
        {
            if (strcmp(word, directory->entries[entry].pair[pair].translation) == 0)
            {
                tempMatch[nCount] = entry; 
                nCount++; 
            }
        }
    }
    if (nCount > 0)
    {
        for (i = 0; i < nCount; i++)
        {
            index = tempMatch[i];
            printf ("Entry # %d\n", i+1);
            displayEntry(*directory, index, directory->entries[index].nPairCount);
            printf ("\n");
        }   
    }
    else printf ("No Entry Match\n");
}

void 
searchTranslation(directorytype * directory)
{
    str language, translation;
    int entry, pair;
    int nEntryCount = directory->nEntryCount;
    int nPairCount, nCount = 0;
    int tempMatch[MAXENTRY];
    int index, i;

    printf ("Input language: ");
    getInput(language);
    printf("Input translation: ");
    getInput(translation);

    for (entry = 0; entry < nEntryCount; entry++)
    {
        nPairCount = directory->entries[entry].nPairCount;
        for  (pair = 0; pair < nPairCount; pair++)
        {
            if ((strcmp(translation, directory->entries[entry].pair[pair].translation) == 0) 
            && (strcmp (language, directory->entries[entry].pair[pair].language) == 0))
            {
                tempMatch[nCount] = entry; 
                nCount++; 
            }
        }
    }

    if (nCount > 0)
    {
        for (i = 0; i < nCount; i++)
        {
            index = tempMatch[i];
            printf ("Entry # %d\n", i+1);
            displayEntry(*directory, index, directory->entries[index].nPairCount);
            printf ("\n");
        }   
    }
    else printf ("No Entry Match\n");
    
}

void
exportData ()
{
    // save all data into a text file 
    // user specifies filename (filename has 30 char max with extension)
    // use w as mode (since data will be overwritten)
    /*
        Formatting to be Used: 
        English: love<next line>
        Tagalog: mahal<next line>
        Hiligaynon: gugma<next line>
        page 4
        Cebuano: gugma<next line>
        Spanish: amor<next line>
        Chinese: ai<next line>
        <nextline>
        Tagalog: mahal<nextline>
        Kapampangan: mal<nextline>
        Cebuano: mahal<nextline>
        English: expensive<nextline>
        Chinese: gui<nextline>
        <nextline>
        <end of file>
    */
    
}

void
importData ()
{
    // open text file
    // read data stored in text file 
    // user inputs filename to load 
    // retrieves entry by entry 
    // checks if entry is already present in the list of entries

}
