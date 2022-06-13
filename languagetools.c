#include <stdio.h>
#include <string.h>
#include "translate.h"

/* 
*
*
* 
LANGUAGE TRANSLATE FUNCTIONS 
*
*
*/
void
getLanguage(int *nOption)
{
    char temp;
    printf("\n\t\tLANGUAGE TOOLS\n");
    printf("_______________________________________________\n");
    printf("To select an option, enter the key enclosed in\n");
    printf("brackets to the left side of the choice\n");
    printf("\n[1] Identify Main Language");
    printf("\n[2] Simple Translation\n");
    printf("\n[0] Exit\n");
    printf("_______________________________________________\n");
    printf("Select Option: ");
    scanf("%d", nOption);
    scanf("%c", &temp);
}

void
importDataTools(directorytype *directory)
{
    char filename[40];
    FILE *existdata;
    entrytype temp; 
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    str language;
    str translation;
    int langlength;
    str checkEntry, checkEntry2;
    int newEntry = 0;
    str tempword, tempspace;
    int i;


    // open text file
    printf("Input filename: ");
    getInput(filename);
    existdata = fopen(filename , "r");

    if (existdata != NULL)
    {
        // until it encounters a double enter, that's the time that it is considered another entry
        while (!feof(existdata))
        {
            temp.nPairCount = 0;
            nPairCount = temp.nPairCount;
            newEntry = 0;
            strcpy(checkEntry, "");
            do
            {
                if (nPairCount == 0)
                {
                    fscanf (existdata, "%s", language);
                    langlength = strlen(language);
                    language[langlength - 1] = '\0';
                    strcpy (temp.pair[nPairCount].language, language);
          
                    // store to an array
                    fscanf (existdata, "%c", tempspace);
                    fscanf (existdata, "%[^\n]s", translation);
                    strcpy (temp.pair[nPairCount].translation, translation);
                    //fgets(translation, MAXCHAR, existdata);
                    nPairCount++;
                    temp.nPairCount = nPairCount;
             
                }
                fgets (checkEntry, 2, existdata);
                fgets (checkEntry2, 2, existdata);
                
      
                if (strcmp(checkEntry2, "\n") == 0 || feof(existdata))
                {
                    // indicates a new entry
                    newEntry = 1;
                }
                else 
                {
                    strcpy (language, checkEntry2);
                    fscanf (existdata, "%s", tempword);
                    strcat(language, tempword);
                    
                    langlength = strlen(language);
                    language[langlength - 1] = '\0';
                    strcpy (temp.pair[nPairCount].language, language);
                
                    // store to an array
                    fscanf (existdata, "%c", tempspace);
                    fscanf (existdata, "%[^\n]s", translation);
                    strcpy (temp.pair[nPairCount].translation, translation);


                    nPairCount++;
                    temp.nPairCount = nPairCount;
                }
            } while (newEntry == 0);

            directory->entries[nEntryCount].nPairCount = nPairCount;
            for (i = 0; i < nPairCount; i++)
            {
                strcpy(directory->entries[nEntryCount].pair[i].language, temp.pair[i].language);
                strcpy(directory->entries[nEntryCount].pair[i].translation, temp.pair[i].translation);
            }
            (directory->nEntryCount)++;
            nEntryCount = directory->nEntryCount;
            
        } 
    }
    else printf("File cannot be opened\n");

    fclose(existdata);
    
}

void 
split(char *sentence, int *pCount, longStr words[MAXWORDS])
{
    int i, j = 0, length;
    *pCount = 0;
    //included the index where the '\0' is to include the last word
    length =  strlen(sentence);
    for (i = 0; i <= length; i++)
    {
        if (sentence[i] != ' ' && sentence[i] != '\0')
        {
            if (!(sentence[i] == '.' || sentence[i] == ',' || sentence[i] == '!' || sentence[i] == '?'))
            {
                words[*pCount][j] = sentence[i];
                j++;
            }
        }
        else 
        {
            words[*pCount][j] = '\0';
            j = 0;
            (*pCount)++;
        }
        
    }

   
}

int 
checkLanguages(languagetype * language, longStr lang)
{
    int i;
    
    for (i = 0; i < MAXWORDS; i++)
    {
        if (strcmp(language->languages[i], lang) == 0)
            return i;
    }
    return 0;
}

int 
findWord(languagetype * language, directorytype * directory, int nCount, longStr words[])
{
    int entry, pair;
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    int index;
    int word;
    int i;
    int nLangCount = 0;


    for (word = 0; word < nCount; word++)
    {
        for (entry = 0; entry < nEntryCount; entry++)
        {
            nPairCount = directory->entries[entry].nPairCount;
            for  (pair = 0; pair < nPairCount; pair++)
            {
                if (strcmp(words[word], directory->entries[entry].pair[pair].translation) == 0)
                {
                    if (checkLanguages(language, directory->entries[entry].pair[pair].language) == 0)
                    {
                        i = nLangCount;
                        strcpy (language->languages[i], directory->entries[entry].pair[pair].language);
                        nLangCount++;
                    }
                    else
                    {
                        index = checkLanguages(language, directory->entries[entry].pair[pair].language);
                        language->languageCount[index] += 1;
                    }
                    
                }
            }
        }
    }
    return nLangCount;
}


void
identifyLanguage (directorytype *directory, languagetype *language)
{
    longStr sentence;
    longStr words[MAXWORDS];
    int nCount = 0;
    int nLangCount = 0;
    int word;
    int temp = 0;
    int nHighestIndex;
    printf("Enter a phrase or sentence: ");
    getInput (sentence);

    
    split(sentence, &nCount, words);
    nLangCount = findWord (language, directory, nCount, words);

    for (word = 0; word < MAXWORDS; word++)
    {
        if (temp < language->languageCount[word])
        {
            temp = language->languageCount[word];
            nHighestIndex = word;
        }
    }

    if (nLangCount == 0)
        printf("Cannot determine the language\n");
    else 
        printf ("Main language: %s\n", language->languages[nHighestIndex]);
    
}

void
findOutput(directorytype * directory, longStr language, int nPairCount, longStr output, int entryIndex)
{
    int i;
    
    for (i = 0; i < nPairCount; i++)
    {
        if (strcmp (language, directory->entries[entryIndex].pair[i].language) == 0)
        {
           
                strcpy (output, directory->entries[entryIndex].pair[i].translation);
          
        }
            
    }
}

void
simpleTranslation (directorytype *directory)
{
    longStr source, output;
    longStr words[MAXWORDS];
    int nCount = 0, word;
    str langoutput, langsource;
    str choice;
    int entry, pair, nPairCount; 
    int nEntryCount = directory->nEntryCount;
    int translated = 0;
    int nCycle = 0;
    
    printf ("Enter language of source text:");
    getInput(langsource);
    printf("Enter source text: ");
    getInput(source);
    printf("Enter language to be translated to: ");
    getInput(langoutput);
    
    do
    {
        if (nCycle > 0)
        {
            printf("Enter source text: ");
            getInput(source);
        }

        split (source, &nCount, words);


        for (word = 0; word < nCount; word++)
        {
            translated = 0;

            for (entry = 0; entry < nEntryCount; entry++)
            {
        
                nPairCount = directory->entries[entry].nPairCount;
                for (pair = 0; pair < nPairCount; pair++)
                {
                
                    if (strcmp(words[word], directory->entries[entry].pair[pair].translation) == 0)
                    {
                        if (strcmp (langsource, directory->entries[entry].pair[pair].language) == 0)
                        {
                            findOutput (directory, langoutput, nPairCount, output, entry);
                            printf("%s ", output);
                            translated = 1;
                        }
                    }

                } 
            }
            if (translated == 0)
                printf("%s ", words[word]);
        }   
        printf ("\n");
        printf("Do you want to translate another text in %s to %s? (Yes/No)", langsource, langoutput);
        getInput(choice);
        toUpper(choice);
        
        nCycle++;
        
    } while (strcmp(choice, "YES") == 0);

}