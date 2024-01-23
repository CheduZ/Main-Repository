#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearInputBuffer() {
    /* Tyhjentää syötepuskurin. Korjaa syöttövirheen kun kirjoittaa 
    syötteeseen kirjaimen, joka aiheuttaa loputtoman loopin.*/
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void tervetuloa() {
    /* Tulostaa alkutervehdyksen */
    printf("Tervetuloa pankkiautomaattiin!\n");
}

int getPIN() {
    /* Pyytää pin-koodin ja palauttaa annetun koodin */
    int pin;
    printf("Syota PIN-koodi: ");
    scanf("%d", &pin);
    return pin;
}

void paavalikko() {
    /* Esittää päävalikon jossa on mahdolliset toiminnot */
    printf("Paavalikko:\n");
    printf("1. Rahan nostaminen\n");
    printf("2. Saldo\n");
    printf("3. Poistu\n");
}

int valinnat() {
    /* Pyytää käyttäjältä valintaa jolla kutsutaan haluttua toimintafunktiota */
    int valinta;
    printf("Valitse toiminto: ");
    if (scanf("%d", &valinta) != 1) {
        clearInputBuffer();
        valinta = -1;
    }
    return valinta;
}

void naytaSaldo(int saldo) {
    /* Näyttää tilin saldon */
    printf("Tilin saldo on: %d euroa\n", saldo);
}

void nosto(int* saldo) {
    /* Funktio vähentää saldosta halutun määrän rahaa ja 
    tarkistaa, ettei anneta virheellisiä arvoja.
    Nyt myös antaa nostaa vain rahasummia, jotka ovat mahdollista 
    antaa 50e ja 20e seteleillä. */
    printf("Valitsit rahan nostamisen\n");
    naytaSaldo(*saldo);

    int nostoSumma;
    printf("Syota nostettava summa: ");

    if (scanf("%d", &nostoSumma) != 1) {
        printf("Virheellinen syote. Palaa paavalikkoon.\n");
        clearInputBuffer();
        return;
    }

    if (nostoSumma <= 0) {
        printf("Virheellinen summa. Palaa paavalikkoon.\n");
    } else if (nostoSumma > *saldo) {
        printf("Saldo ei riita. Palaa paavalikkoon.\n");
    } else {
        int seteliArvo[] = {50, 20};
        int seteliMaarat[sizeof(seteliArvo) / sizeof(seteliArvo[0])];
        int jalki = nostoSumma;
        int i, kerroin, seteliMaara;

        for (i = 0; i < sizeof(seteliArvo) / sizeof(seteliArvo[0]); i++) {
            kerroin = seteliArvo[i];
            seteliMaara = jalki / kerroin;
            seteliMaarat[i] = seteliMaara;
            jalki -= kerroin * seteliMaara;
        }

        if (jalki == 0) {
            for (i = 0; i < sizeof(seteliArvo) / sizeof(seteliArvo[0]); i++) {
                kerroin = seteliArvo[i];
                seteliMaara = seteliMaarat[i];
                if (seteliMaara > 0) {
                    printf("%d kpl %d euron setelia\n", seteliMaara, kerroin);
                }
            }

            *saldo -= nostoSumma;
            printf("Rahat nostettu: %d euroa\n", nostoSumma);
            naytaSaldo(*saldo);
        } else {
            printf("Ei mahdollista antaa pyydettya summaa seteleina. Palaa paavalikkoon.\n");
        }
    }
}

int main() {
    /* Pääohjelma joka kutsuu muita funktioita. Sisältää kortinlukua simuloivan osan, 
    joka kysyy ensin tilinumeroa ja sen perusteella etsii .tili muotoisen tiedoston, 
    jossa on tallennettuna tilin pin koodi ja saldo. Näitä käytetään ohjelman toiminnassa. */

    tervetuloa();

    char tilinumero[20];
    printf("Syota tilinumero: ");
    scanf("%s", tilinumero);
    
    int pin = getPIN();

    char tiedostonimi[30];
    sprintf(tiedostonimi, "%s.tili", tilinumero);

    FILE* tiedosto = fopen(tiedostonimi, "r");

    if (tiedosto == NULL) {
        printf("Tilinumeroa %s vastaavaa tiedostoa ei loydy. Ohjelma lopetetaan.\n", tilinumero);
        return 0;
    }

    char pinTiedostosta[10];
    fscanf(tiedosto, "%s", pinTiedostosta);

    if (strcmp(pinTiedostosta, "") == 0) {
        printf("Tiedoston %s ensimmaisen rivin sisaltoa ei loydy. Ohjelma lopetetaan.\n", tiedostonimi);
        fclose(tiedosto);
        return 0;
    }

    int pinLuetut = atoi(pinTiedostosta);

    if (pin != pinLuetut) {
        printf("Virheellinen PIN-koodi. Ohjelma lopetetaan.\n");
        fclose(tiedosto);
        return 0;
    }

    int saldo;
    fscanf(tiedosto, "%d", &saldo);
    fclose(tiedosto);

    while (1) {
        paavalikko();

        int valinta = valinnat();

        switch (valinta) {
            case 1:
                nosto(&saldo);
                break;
            case 2:
                naytaSaldo(saldo);
                break;
            case 3:
                printf("Kiitos ja hyvasti!\n");
                return 0;
            default:
                printf("Virheellinen valinta. Yrita uudelleen.\n");
        }
    }

    return 0;
}
