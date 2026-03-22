#include <stdio.h>
#include <string.h>

int kelimeSay(char metin[], char kelime[]);

void sonucuDosyayaYaz(FILE *girdiDosyasi, FILE *ciktiDosyasi, char kelime[]) {
    char satir[1000];
    int satirNo = 1;
    int tekrar;
    int toplam = 0;

    while (fgets(satir, sizeof(satir), girdiDosyasi) != NULL) {
        tekrar = kelimeSay(satir, kelime);

        if (tekrar > 0) {
            fprintf(ciktiDosyasi, "%d. satirda %d kez bulundu\n", satirNo, tekrar);
            fprintf(ciktiDosyasi, "%s", satir);

            if (satir[strlen(satir) - 1] != '\n') {
                fprintf(ciktiDosyasi, "\n");
            }

            toplam += tekrar;
        }

        satirNo++;
    }

    fprintf(ciktiDosyasi, "\nToplam bulunma sayisi: %d\n", toplam);
}