#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int kelimeSay(char metin[], char kelime[]) {
    int i, j, sayac = 0;

    int metinUzunluk = 0;
    while (metin[metinUzunluk] != '\0') metinUzunluk++;

    int kelimeUzunluk = 0;
    while (kelime[kelimeUzunluk] != '\0') kelimeUzunluk++;

    for (i = 0; i <= metinUzunluk - kelimeUzunluk; i++) {
        for (j = 0; j < kelimeUzunluk; j++) {
            if (metin[i + j] != kelime[j]) break;
        }
        if (j == kelimeUzunluk) sayac++;
    }

    return sayac;
}


int satirdaVarMi(char satir[], char kelime[]) {
    int i, j, k;

    for (i = 0; satir[i] != '\0'; i++) {
        k = i;
        j = 0;
        while (kelime[j] != '\0' && satir[k] == kelime[j]) {
            j++;
            k++;
        }
        if (kelime[j] == '\0') return 1;
    }

    return 0;
}


#define MAX_DOSYA_SAYISI 3
#define MAX_DOSYA_ADI    256

int kullanicidan_dosya_al(char dosya_adlari[][MAX_DOSYA_ADI]) {
    int dosya_sayisi = 0;

    printf("Kac dosya taranacak? (1-%d): ", MAX_DOSYA_SAYISI);
    scanf("%d", &dosya_sayisi);

    if (dosya_sayisi < 1) {
        fprintf(stderr, "HATA: En az 1 dosya girilmelidir.\n");
        return 0;
    }
    if (dosya_sayisi > MAX_DOSYA_SAYISI) {
        fprintf(stderr, "UYARI: En fazla %d dosya girilebilir. "
                        "Ilk %d dosya isleniyor.\n",
                MAX_DOSYA_SAYISI, MAX_DOSYA_SAYISI);
        dosya_sayisi = MAX_DOSYA_SAYISI;
    }

    for (int i = 0; i < dosya_sayisi; i++) {
        printf("Dosya %d adi: ", i + 1);
        scanf("%255s", dosya_adlari[i]);
    }

    return dosya_sayisi;
}

int dosyalari_ac(char dosya_adlari[][MAX_DOSYA_ADI],
                 int dosya_sayisi,
                 FILE *fp_listesi[]) {
    int basarili = 0;
    for (int i = 0; i < dosya_sayisi; i++) {
        fp_listesi[i] = fopen(dosya_adlari[i], "r");
        if (fp_listesi[i] == NULL) {
            fprintf(stderr, "HATA: '%s' dosyasi acilamadi.\n", dosya_adlari[i]);
        }
        else {
            basarili++;
        }
    }
    return basarili;
}

void dosyalari_kapat(FILE *fp_listesi[], int dosya_sayisi) {
    for (int i = 0; i < dosya_sayisi; i++) {
        if (fp_listesi[i] != NULL) {
            fclose(fp_listesi[i]);
            fp_listesi[i] = NULL;
        }
    }
}


void sonucuDosyayaYaz(FILE *girdiDosyasi,
                      FILE *ciktiDosyasi,
                      char dosyaAdi[],
                      char kelime[]) {
    char satir[1000];
    int satirNo  = 1;
    int toplam   = 0;


    printf("\n=== %s ===\n", dosyaAdi);
    fprintf(ciktiDosyasi, "\n=== %s ===\n", dosyaAdi);

    while (fgets(satir, sizeof(satir), girdiDosyasi) != NULL) {
        int tekrar = kelimeSay(satir, kelime);

        if (tekrar > 0) {

            printf("  %d. satirda %d kez bulundu: %s",
                   satirNo, tekrar, satir);
            if (satir[strlen(satir) - 1] != '\n') printf("\n");

            fprintf(ciktiDosyasi, "%d. satirda %d kez bulundu\n",
                    satirNo, tekrar);
            fprintf(ciktiDosyasi, "%s", satir);
            if (satir[strlen(satir) - 1] != '\n')
                fprintf(ciktiDosyasi, "\n");

            toplam += tekrar;
        }

        satirNo++;
    }

    printf("  Toplam: %d kez\n", toplam);
    fprintf(ciktiDosyasi, "Toplam bulunma sayisi: %d\n", toplam);
}

int main(void) {
    char dosya_adlari[MAX_DOSYA_SAYISI][MAX_DOSYA_ADI];
    FILE *fp_listesi[MAX_DOSYA_SAYISI];
    char kelime[100];
    char ciktiAdi[] = "sonuclar.txt";


    int dosya_sayisi = kullanicidan_dosya_al(dosya_adlari);
    if (dosya_sayisi == 0) return 1;


    printf("Aranacak kelimeyi girin: ");
    scanf("%99s", kelime);


    int acilan = dosyalari_ac(dosya_adlari, dosya_sayisi, fp_listesi);
    if (acilan == 0) {
        fprintf(stderr, "Hic dosya acilamadi. Program sonlandiriliyor.\n");
        return 1;
    }
    printf("\n%d dosyadan %d tanesi basariyla acildi.\n", dosya_sayisi, acilan);


    FILE *ciktiFp = fopen(ciktiAdi, "w");
    if (ciktiFp == NULL) {
        fprintf(stderr, "HATA: '%s' cikti dosyasi acilamadi.\n", ciktiAdi);
        dosyalari_kapat(fp_listesi, dosya_sayisi);
        return 1;
    }
    fprintf(ciktiFp, "Aranan kelime: \"%s\"\n", kelime);


    for (int i = 0; i < dosya_sayisi; i++) {
        if (fp_listesi[i] == NULL) continue;
        sonucuDosyayaYaz(fp_listesi[i], ciktiFp, dosya_adlari[i], kelime);
    }


    dosyalari_kapat(fp_listesi, dosya_sayisi);
    fclose(ciktiFp);

    printf("\nSonuclar '%s' dosyasina kaydedildi.\n", ciktiAdi);
    return 0;
}
