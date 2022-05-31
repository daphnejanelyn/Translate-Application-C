#define MAXPAIR 10
#define MAXCHAR 20
#define MAXENTRY 150
#define MAXWORDS 75

typedef char str [21];
typedef char longStr[150];

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

typedef struct languagetag
{
    int languageCount[MAXWORDS];
    str languages[MAXWORDS];
} languagetype;

void getInput (char *string);
void getMenu (int *nMenu);
void getData (int *nData);
void toUpper (char *string);
void displayEntry (directorytype directory, int index, int nPairCount);
void getNewPair(directorytype * directory, int entryIndex);
void addEntry (directorytype *directory);
void addTranslation(directorytype * directory);
void sortAlphabetical(directorytype * directory, int entryIndex);
void displayAll (directorytype * directory);
void modifyEntry(directorytype * directory);
void deleteEntry (directorytype *directory);
void deleteTranslation(directorytype *directory);
void searchWord (directorytype *directory);
void searchTranslation(directorytype * directory);
void getLanguage (int *nOption);
void split(char *sentence, int *pCount, longStr words[MAXWORDS]);
int checkLanguages(languagetype * language, longStr lang);
void findWord(languagetype * language, directorytype * directory, int *nCount, str words[]);
void identifyLanguage (directorytype *directory, languagetype *language);
int findOutput(directorytype * directory, longStr language, int nPairCount, longStr output, int word, int entryIndex);
void simpleTranslation (directorytype *directory);