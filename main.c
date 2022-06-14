#include <stdio.h>
#include <string.h>

#include "translate.h"
#include "managetools.c"
#include "languagetools.c"

int 
main ()
{
    int entry, pair;
    int nMenu, nOption = 0;
    int languagecount;
    directorytype directory;
    languagetype language;
    
    directory.nEntryCount = 0;

    for (entry = 0; entry < MAXENTRY; entry++)
    {
        directory.entries[entry].nPairCount = 0;
        for (pair = 0; pair < MAXPAIR; pair++)
        {
            strcpy(directory.entries[entry].pair[pair].translation, "\0");
            strcpy(directory.entries[entry].pair[pair].language, "\0");
        }
    }

    for (languagecount = 0; languagecount < MAXWORDS; languagecount++)
        language.languageCount[languagecount] = 0;

    do
    {
        /* Display and get menu input */
        getMenu(&nMenu);

        if (nMenu == 1)
        {
            /* display manage data */
    
            do
            {
                getData(&nOption);
                switch (nOption)
                {
                    case 1: addEntry(&directory);
                            break;
                    case 2: addTranslation (&directory);
                            break;
                    case 3: modifyEntry(&directory);
                            break;
                    case 4: deleteEntry(&directory);
                            break;
                    case 5: deleteTranslation(&directory);
                            break;
                    case 6: displayAll(&directory);
                            break;
                    case 7: searchWord(&directory);
                            break;
                    case 8: searchTranslation(&directory);
                            break;
                    case 9: exportData(directory);
                            break;
                    case 10: importData(&directory);
                             break;
                    default: printf ("Please enter a valid input: ");
                             scanf ("%d", &nOption);
                             break;
                }

            }
            while (nOption != 0);

            /* clear all entries*/
            directory.nEntryCount = 0;

            for (entry = 0; entry < MAXENTRY; entry++)
            {
                directory.entries[entry].nPairCount = 0;
                for (pair = 0; pair < MAXPAIR; pair++)
                {
                    strcpy(directory.entries[entry].pair[pair].translation,"\0");
                    strcpy(directory.entries[entry].pair[pair].language,"\0");
                }
            }
        }

        if (nMenu == 2)
        {
            /* display language tools */
            importDataTools (&directory);
            do
            {
                getLanguage(&nOption);
                switch (nOption)
                {
                    case 1: identifyLanguage (&directory, &language);
                            break;
                    case 2: simpleTranslation (&directory);   
                            break; 
                    default: printf ("Please enter a valid input: ");
                             scanf ("%d", &nOption);
                             break;
                }
                    
            } while (nOption != 0);
        }


    } while (nMenu != 0);


    return 0;
}
