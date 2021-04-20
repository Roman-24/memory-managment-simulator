# Spravca-pamate
Simulácia práce správcu pamäte.

<p>V štandardnej knižnici jazyka C sú pre alokáciu a uvoľnenie pamäte k dispozícii funkcie malloc a free. Tento program implementuje vlastnú verziu alokácie pamäte.
Konkrétnejšie implementuje v programovacom jazyku C nasledovné ŠTYRI funkcie:</p>

* void *memory_alloc(unsigned int size);
* int memory_free(void *valid_ptr);
* int memory_check(void *ptr);
* void memory_init(void *ptr, unsigned int size);

<p>Funkcia **memory_alloc** poskytuje služby analogické štandardnému malloc. Teda, vstupné parametre sú veľkosť požadovaného súvislého bloku pamäte a funkcia vráti: ukazovateľ na úspešne alokovaný kus voľnej pamäte, ktorý sa vyhradil, alebo NULL, keď nie je možné súvislú pamäť požadovanej veľkosť vyhradiť.</p>

<p>Funkcia **memory_free slúži** na uvoľnenie vyhradeného bloku pamäte, podobne ako funkcia free. Funkcia vráti 0, ak sa podarilo (funkcia zbehla úspešne) uvoľniť blok pamäte, inak vráti 1. Predpokladá sa však, že parameter je vždy platný ukazovateľ, vrátený z predchádzajúcich volaní funkcie memory_alloc, ktorý ešte nebol uvoľnený.</p>

<p>Funkcia **memory_check** slúži na skontrolovanie, či parameter (ukazovateľ) je platný ukazovateľ, ktorý bol v nejakom z predchádzajúcich volaní vrátený funkciou memory_alloc a zatiaľ nebol uvoľnený funkciou memory_free. Funkcia vráti 0, ak je ukazovateľ neplatný, inak vráti 1.</p>

<p>Funkcia **memory_init** slúži na inicializáciu spravovanej voľnej pamäte. Predpokladá že funkcia sa volá práve raz pred všetkými inými volaniami memory_alloc, memory_free a memory_check. Ako vstupný parameter funkcie príde blok pamäte, ktorú môžeme použiť pre organizovanie a aj pridelenie voľnej pamäte.</p>

<p>Program využíva iba jednu globálnu premennú na zapamätanie ukazovateľa na pamäť, ktorá vstupuje do funkcie memory_init. Ukazovatele, ktoré prideľuje funkcia memory_alloc musia byť výhradne z bloku pamäte, ktorá bola pridelená funkcii memory_init.</p>

## Stručný opis algoritmu
V mojom riešení som sa rozhodol využiť explicitný zoznam voľných blokov. Ako dátovú štruktúru som použil typedef struct, kt. veľkosť mi kompilátor ukazuje ako 16B. Táto štruktúra sa využíva ako hlavička pre bloky, pričom viacero týchto štruktúr vytvorí spájaný zoznam voľných blokov. 

### Memory_init
<p>Kontrola či sa vstupný pointer nerovná NULL. Nastavenie globálneho ukazovateľa na začiatok celkovej pamäte. Vytvorenie master_head, kt. obsahuje veľkosť celkovej pamäte, táto hlavička sa nikdy neprepisuje. Hneď za ňou sa vytvorí druhá hlavička, kt. je akoby prvý prázdny blok.</p>

### Memory_alloc
<p>Ako prvé sa z master_head vyberie veľkosť celkovej pamäte a skontroluje sa či sa nejde alokovať viac pamäte ako je celková pamäť.

Nasleduje while loop, kt. výsledkom sú dva pointre. Prvý je na blok v kt. sa bude alokovať (blok musí splniť podmienky na alokáciu inak vybraný nebude) požadovaná pamäť. Druhý je predošlí toho prvého. 

Ak teda bol nájdený vhodný blok, skontroluje sa či je potrebné tento blok rozdeliť a okrem vyselektovania alokovanej časti vytvoriť aj nový prázdny blok, kt. by obsahoval prebytočnú pamäť a bol by zaradený do zoznamu voľných blokov.

Funkcia vráti ukazovateľ na začiatok alokovanej pamäte prípadne vypíše chybovú hlášku ak sa pamäť nepodarí prideliť.</p>

### Memory_free
<p>Na začiatku sa opäť skontroluje či je zadaný parameter funkcie platný ukazovateľ.

V zozname voľných blokov sa nájde ukazovateľ, kt. akoby bol pred blokom, kt. sa ide uvoľňovať. Následne sa uvoľňovaný blok zaradí do zoznamu voľných blokov tak, že sa presmerujú jednotlivé ukazovatele. 

Následne sa skontroluje, či je možné spojiť tento voľný blok s nejakým v adresovom poli susedným voľným blokom. Najskôr je pokus o merge dopredu a nasleduje aj pokus o merge dozadu.</p>

### Memory_check
Funckia prejde zoznám voľných blokov a ak sa v ňom pointer nenachádza tak je daná časť alokovaná.
