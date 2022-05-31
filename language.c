#include "translate.h"

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
            if (!(sentence[i] == '.' || sentence[i] != ',' || sentence[i] != '!' || sentence[i] != '?'))
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

void 
findWord(languagetype * language, directorytype * directory, int *nCount, str words[])
{
    int entry, pair;
    int nEntryCount = directory->nEntryCount;
    int nPairCount;
    int index;
    int word;
    int i;

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
                        i = *nCount;
                        strcpy (language->languages[i], directory->entries[entry].pair[pair].language);
                        (*nCount)++;
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

    findWord (language, directory, &nLangCount, words);
    
    split(sentence, &nCount, words);

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

int
findOutput(directorytype * directory, longStr language, int nPairCount, longStr output, int word, int entryIndex)
{
    int i;
    
    for (i = 0; i < nPairCount; i++)
    {
        if (strcmp (language, directory->entries[entryIndex].pair[i].language) == 0)
        {
            if (word == 0)
                strcpy (output, directory->entries[entryIndex].pair[i].translation);
            else
                strcat (output, directory->entries[entryIndex].pair[i].translation);
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

    do
    {
        printf ("Enter language of source text:");
        getInput(langsource);
        printf("Enter source text: ");
        getInput(source);
        printf("Enter language to be translated to: ");
        getInput(langoutput);

        split (source, &nCount, words);

        for (word = 0; word < nCount; word++)
        {
            for (entry = 0; entry < nEntryCount; entry++)
            {
                nPairCount = directory->entries[entry].nPairCount;
                for (pair = 0; pair < nPairCount; pair++)
                {
                    if (strcmp(words[word], directory->entries[entry].pair[pair].translation) == 0)
                    {
                        if (strcmp (langsource, directory->entries[entry].pair[pair].language) == 0)
                            findOutput (directory, langoutput, nPairCount, output, word, entry);
                    }
                } 
            }
        }   
        printf("Do you want to translate another text in %s to %s? (Yes/No)", langsource, langoutput);
        getInput(choice);
        toUpper(choice);
        
    } while (strcmp(choice, "YES") == 0);


    
    

}