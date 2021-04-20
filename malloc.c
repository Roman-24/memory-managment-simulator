/*
Roman Bitarovský
DSA LS 2020/2021
projekt: Správca pamäte
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct head {
    unsigned int size;
    char is_free;
    struct head *next;
} HEAD;

// Nejaký jeden globálny poiter
void *pointer_global = NULL;



// Takže sú potrebné tieto 4 funkcie
void *memory_alloc(unsigned int size); // malloc
int memory_free(void *valid_ptr);
int memory_check(void *ptr);
void memory_init(void *ptr, unsigned int size);



/*..................................... Vedľajšie funkcie .....................................*/

void *vypis_zoznam(int mem_size) { // funkcia vypíše spájaný zoznam prázdnych blokov
    HEAD *akt = pointer_global;
    printf("Vypisok zoznamu prazdnych blokov:\n");
    while (akt != NULL) {
        printf("adresa %d size: %d ukazujem na: %d \n", akt, akt->size, akt->next);
        akt = akt->next;
    }
}

int vypis_memory_check(char *pointer) {
    if (memory_check(pointer) == 1) {
        printf("vypis_memory_check: Pointer na adrese %d je platny \n", pointer);
        return 1;
    } else {
        printf("vypis_memory_check: Pointer na adrese %d je NEplatny \n", pointer);
        return 0;
    }
}

/*..................................... Vedľajšie funkcie KONIEC .....................................*/



/* ..................................... TESTY ..................................... */

void test_1(unsigned int celkova_pamat) {
#define TEST1 6
    printf("Test jedna - pamat: %dB - bloky 16B\n", celkova_pamat);
    int pole[TEST1] = {NULL};
    unsigned int malokovane = 0, size = 0;

    for (int i = 1; i <= TEST1; i++) {

        size = 16;
        pole[i] = (char *) memory_alloc(size);

        if (pole[i] != NULL) {
            malokovane += size;
        }
    }

#define INDEX_T1 5
    memory_free(pole[INDEX_T1]);
    pole[INDEX_T1] = (char *) memory_alloc(size);

    if(pole[INDEX_T1]!=NULL){
        malokovane += size;
    }

    // final výpisok testu
    float vyysledok_bajt = ((float) malokovane / (float) celkova_pamat) * 100;
    printf("Velkost celkovej pamate %d B: alokovane %.2f%%B.\n \n", celkova_pamat, vyysledok_bajt);
}

void test_2(unsigned int celkova_pamat) {
#define TEST2 5
    printf("Test dva - pamat: %dB - bloky 8-24B\n", celkova_pamat);
    int pole[TEST2] = {NULL};
    unsigned int malokovane = 0, size = 0;

    for (int i = 2; i <= TEST2; i++) {

        size = 4 * i;

        pole[i] = (char *) memory_alloc(size);

        if (pole[i] != NULL && malokovane + size < celkova_pamat) {
            malokovane += size;
        }
    }

#define INDEX_T2 5
    memory_free(pole[INDEX_T2]);
    pole[INDEX_T2] = (char *) memory_alloc(size);
    memory_free(pole[INDEX_T2-2]);
    memory_free(pole[INDEX_T2-1]);

    if(pole[INDEX_T2]!=NULL && malokovane + size < celkova_pamat){
        malokovane += size;
    }

    size = 24;
    pole[INDEX_T2+1] = (char *) memory_alloc(size);
    if(pole[INDEX_T2+1]!=NULL && malokovane + size < celkova_pamat){
        malokovane += size;
    }

    // final výpisok testu
    float vyysledok_bajt = ((float) malokovane / (float) celkova_pamat) * 100;
    printf("Velkost celkovej pamate %d B: alokovane %.2f%%B.\n \n", celkova_pamat, vyysledok_bajt);
}

void test_3(unsigned int celkova_pamat) {
#define TEST3 20
    printf("Test tri - pamat: %dB - bloky 450-%dB\n", celkova_pamat, TEST3*46 + 400);
    int pole[TEST3] = {NULL};
    unsigned int malokovane = 0, size = 0;

    for (int i = 1; i <= TEST3; i++) {

        size = 400 + i*46;

        pole[i] = (char *) memory_alloc(size);

        if(i%3 == 0){
            memory_free(pole[i]);
            memory_free(pole[i-1]);
        }

        if (pole[i] != NULL && malokovane + size < celkova_pamat) {
            malokovane += size;
        }
    }

#define INDEX_T3 5
    memory_free(pole[INDEX_T3]);
    pole[INDEX_T3] = (char *) memory_alloc(size);

    if(pole[INDEX_T3]!=NULL && malokovane + size < celkova_pamat){
        malokovane += size;
    }

    // final výpisok testu
    float vyysledok_bajt = ((float) malokovane / (float) celkova_pamat) * 100;
    printf("Velkost celkovej pamate %d B: alokovane %.2f%%B.\n \n", celkova_pamat, vyysledok_bajt);
}

void test_4(unsigned int celkova_pamat) {
#define TEST4 55
    printf("Test 4 - pamat: %dB - bloky 450-%dB\n", celkova_pamat, TEST4*46 + 400);
    int pole[TEST4] = {NULL};
    unsigned int malokovane = 0, size = 0;

    for (int i = 1; i <= TEST4; i++) {

        size = 400 + i*46;

        pole[i] = (char *) memory_alloc(size);

        if(i%3 == 0){
            memory_free(pole[i]);
            memory_free(pole[i-1]);
        }

        if (pole[i] != NULL && malokovane + size < celkova_pamat) {
            malokovane += size;
        }
    }

#define INDEX_T4 5
    memory_free(pole[INDEX_T4]);
    pole[INDEX_T4] = (char *) memory_alloc(size);

    if(pole[INDEX_T4]!=NULL && malokovane + size < celkova_pamat){
        malokovane += size;
    }

    // final výpisok testu
    float vyysledok_bajt = ((float) malokovane / (float) celkova_pamat) * 100;
    printf("Velkost celkovej pamate %d B: alokovane %.2f%%B.\n \n", celkova_pamat, vyysledok_bajt);
}

void test_5(unsigned int celkova_pamat) {

    printf("Test 5 - pamat: %dB test mergovania dozadu\n", celkova_pamat);

    char* pointer1 = (char *) memory_alloc(20);
    char* pointer2 = (char *) memory_alloc(20);
    char* pointer3 = (char *) memory_alloc(20);
    char* pointer4 = (char *) memory_alloc(20);
    char* pointer5 = (char *) memory_alloc(40);

    memory_free(pointer2);
    memory_free(pointer3);

    pointer5 = (char *) memory_alloc(40);
    /*
    for(int i=0; i<20; i++){
        printf("obsah: %d\n", pointer1 + i);
    }
    */
}

/* ..................................... TESTY END ..................................... */



/* ..................................... MAIN ..................................... */

int main() {
    printf("*** Spusta sa DSA projekt 1 *** \n \n");

    //..................................... TESTER .....................................

#define REGION1 200
    char region_1[REGION1];
    memory_init(region_1, REGION1);
    test_1(REGION1);

    // test_2 má rovná REGION ako test_1 zámerne
    char region_2[REGION1];
    memory_init(region_2, REGION1);
    test_2(REGION1);

#define REGION3 4000
    char region_3[REGION3];
    memory_init(region_3, REGION3);
    test_3(REGION3);

#define REGION4 35000
    char region_4[REGION4];
    memory_init(region_4, REGION4);
    test_4(REGION4);

    //test mergovania dozadu
    char region_5[REGION1];
    memory_init(region_5, REGION1);
    test_5(REGION1);

    /*char region_x[1000];
    memory_init(region_x, 1000);
    char* pointer_x = (char *) memory_alloc(20);
    //memory_free(pointer_x);
    vypis_memory_check(pointer_x+10);*/
    //..................................... TESTER END .....................................

    printf("\n \n*** Ukoncuje sa DSA projekt 1 ***\n");
    return 0;
}

/* ..................................... MAIN END ..................................... */



/* ..................................... POTREBNÉ FUKNIONALITY ..................................... */

void *memory_alloc(unsigned int size) {
    //printf("memory_alloc: Prebieha alokacia...\n");

    HEAD *pom = (HEAD *) pointer_global;
    HEAD *alok_blok = (HEAD *) pointer_global;

    unsigned int all_size = pom->size; // z master_head sa vyberie veľkosť celkovej pamäte
    // printf("all_size je: %d \n", all_size);
    unsigned int head_size = sizeof(HEAD);

    if (size > all_size - head_size) { // ak je požadovaná pamäť väčšia ako celková možná použiteľná pamäť
        printf("memory_alloc: Nieje mozne alkovovat viac pamate ako je celkova velkost pamate \n");
        return NULL;
    }

    int flag = 0;
    while (alok_blok != NULL) { // prechadza zoznam voľných blokov
        if (alok_blok->is_free == 1 && size + head_size <= alok_blok->size) { // ak sa nájde vhodný blok tak stop
            flag = 1;
            break;
        }
        pom = alok_blok; // pom si pamätá si pamätá predošlí pred blokom do kt. ideme alokovať
        alok_blok = alok_blok->next; // posun v zozname
    }

    if (flag) {

        // ak je blok väčší ako potrebujeme
        if (alok_blok > size + head_size) {

            // vytvoríme nový blok
            HEAD *novy_blok = (HEAD *) ((char *) alok_blok + head_size + size);
            novy_blok->is_free = 1;
            novy_blok->size = alok_blok->size - head_size - size; // z veľkosti starého bloku sa odpočíta nová hlavička a veľkosť, kt. sa alokovala
            novy_blok->next = NULL; // next zatiaľ ukazuje na NULL
            pom->next = novy_blok; // predchádzajúci (pred alokovaným kusom) bude ukazovať na nový voľný blok
        }

        // úprava vlastnosti alokovaného bloku bloku
        alok_blok->size = size;
        alok_blok->is_free = 0;

        printf("memory_alloc: Bolo alokovanych %d bajtov so zaciatkom na adrese: %d ale returnlo sa: %d\n", size, alok_blok, (char*)alok_blok + head_size +1);
        return (char*)alok_blok + head_size +1;
    } else if (!flag) {
        printf("memory_alloc: Nedostatok pamate na alokovanie %d bajtov \n", size);
        return NULL;
    }
}

int memory_free(void *valid_ptr) {

    if (valid_ptr == NULL) {
        printf("memory_free: Neplatny pointer pre uvolnenie pamate \n");
        return 1;
    }

    unsigned int head_size = sizeof(HEAD);
    HEAD *uvolni_ptr = (HEAD *) ((char*)valid_ptr - head_size - 1);
    HEAD *pom = (HEAD *) pointer_global;

    uvolni_ptr->is_free = 1;

    while (pom->next < uvolni_ptr && pom->next != NULL) { // nájde sa blok, kt. je pred blokom, kt. sa ide uvolniť
        pom = pom->next;
    }

    // do zoznamu voľných blokov sa pridá blok kt. sa uvolnil
    // presmerujú sa pointre
    uvolni_ptr->next = pom->next;
    pom->next = uvolni_ptr;

    printf("memory_free: Pointer na adrese %d bol uvolneny \n", uvolni_ptr);

    // merge dopredu
    if ((HEAD *) ((char *) uvolni_ptr + head_size + uvolni_ptr->size) == uvolni_ptr->next && uvolni_ptr->is_free == 1 && uvolni_ptr->next->is_free == 1) {
        HEAD* temp = uvolni_ptr->next;
        temp->is_free = 1;
        printf("memory_free: Merge dopredu\n");
        uvolni_ptr->size = uvolni_ptr->size + uvolni_ptr->next->size + head_size;
        uvolni_ptr->next = temp;
    }

    // merge dozadu
    if ((HEAD *) ((char *) pom + head_size + pom->size) == uvolni_ptr && pom->is_free == 1 && uvolni_ptr->next->is_free == 1) {
        HEAD* temp = uvolni_ptr->next;
        temp->is_free = 1;
        printf("memory_free: Merge dozadu\n");
        pom->size = uvolni_ptr->size + head_size + uvolni_ptr->size;
        pom->next = temp;
    }

    return 0;
}

int memory_check(void *ptr) {

    int all_size = ((HEAD*)pointer_global)->size;
    unsigned int head_size = sizeof(HEAD);

    if (ptr == NULL && ptr < (char*)pointer_global && ptr > (char*)pointer_global + head_size + all_size) {
        printf("memory_check: Pointer neukazuje na platnu pamat\n");
        return 0;
    }

    HEAD *ptr_check = (HEAD *) ptr;
    HEAD *akt = pointer_global;

    akt = akt->next;
    while (akt != NULL) {

        // ak sa má kontrolovať nie len začiatok alokovanej pamäte ale hoc aká alokovaná časť
        if ( (char*)ptr_check > (char*)akt && (char*)ptr_check < (char*)akt + akt->size) {
            return 0;
        }

        // ak kontrolujeme iba začiatočný pointer na alokovanú pamäť
        /*if(ptr_check == (char*)akt + head_size + 1){
            return 0;
        }*/

        akt = akt->next;
    }
    return 1;
}

void memory_init(void *ptr, unsigned int size) { // funkcia na vytvorenie pamäte resp. jej priradenie k globálnemu pointru

    if (ptr == NULL) {
        printf("memory_init: Bol zadany nespravny pointer na pamat \n");
        exit(1);
    }

    pointer_global = ptr; // do globalnej premennej sa pridelí začiatok celkovej pamäte
    //memset(pointer_global, 0, size); // celá pamäť sa znuluje
    unsigned int head_size = sizeof(HEAD);

    // master_head
    HEAD *master_head = (HEAD *) pointer_global; // vytvorenie hlavičky pre celkovú pamäť
    master_head->is_free = '*'; // táto hlavička nieje free a ani nikdy nebude preto bosahuje nejaký úplne iný znak
    master_head->size = size - head_size; // prvá hlavička obsahuje rozmer celkovej pamäte kt bude možné teoreticky použiť
    master_head->next = NULL; // NEXT je NULL lebo zatiaľ žiadny ďalší blok nieje

    // head_02
    HEAD *head_02 = (char*)pointer_global + head_size; // za master_head sa vytvorí druhá hlavička
    head_02->is_free = 1; // blok je voľný
    head_02->size = master_head->size - head_size; // size je celková pamäť - tie dve hlavičky
    head_02->next = NULL; // next bude NULL lebo už voľný blok nemám


    master_head->next = head_02;
}

/* ..................................... KONIEC FUNKCIONALIT ..................................... */



// The end