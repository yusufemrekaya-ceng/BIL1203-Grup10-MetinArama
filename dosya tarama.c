#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DOSYA_SAYISI   3
#define MAX_DOSYA_ADI      256
#define BLOK_BOYUTU        4096

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
                        "Ilk %d dosya isleniyor.\n", MAX_DOSYA_SAYISI, MAX_DOSYA_SAYISI);
        dosya_sayisi = MAX_DOSYA_SAYISI;
    }
    for (int i = 0; i < dosya_sayisi; i++) {
        printf("Dosya %d adi: ", i + 1);
        scanf("%255s", dosya_adlari[i]);
    }

    return dosya_sayisi;
}

int dosyalari_ac(char dosya_adlari[][MAX_DOSYA_ADI], int dosya_sayisi, FILE *fp_listesi[]) {
   
    int basarili = 0;
    for (int i = 0; i < dosya_sayisi; i++) {
        fp_listesi[i] = fopen(dosya_adlari[i], "r");
        if (fp_listesi[i] == NULL) {
            fprintf(stderr, "HATA: '%s' dosyasi acilamadi.\n", dosya_adlari[i]);
        } else {
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

void dosyalari_oku(FILE *fp_listesi[], char dosya_adlari[][MAX_DOSYA_ADI], int dosya_sayisi) {
    char blok[BLOK_BOYUTU + 1];
    size_t okunan_byte;

    for (int i = 0; i < dosya_sayisi; i++) {
        if (fp_listesi[i] == NULL) continue;

        long toplam_byte = 0;
        int blok_no = 0;

        printf("\n--- %s blok blok okunuyor ---\n", dosya_adlari[i]);

        while ((okunan_byte = fread(blok, 1, BLOK_BOYUTU, fp_listesi[i])) > 0) {
            blok[okunan_byte] = '\0';
            blok_no++;
            toplam_byte += okunan_byte;

            printf("Blok %d: %zu byte okundu\n", blok_no, okunan_byte);

            /* İleride: kelime_ara_blokta(blok, okunan_byte, aranan_kelime) buraya gelecek */
        }

        printf("--- %s bitti, toplam %ld byte, %d blok ---\n",
               dosya_adlari[i], toplam_byte, blok_no);
    }
}

int main() {
   
    char dosya_adlari[MAX_DOSYA_SAYISI][MAX_DOSYA_ADI];
    FILE *fp_listesi[MAX_DOSYA_SAYISI];

    int dosya_sayisi = kullanicidan_dosya_al(dosya_adlari);
    if (dosya_sayisi == 0) return 1;

    int acilan = dosyalari_ac(dosya_adlari, dosya_sayisi, fp_listesi);
    if (acilan == 0) {
        fprintf(stderr, "Hic dosya acilamadi. Program sonlandiriliyor.\n");
        return 1;
    }

    printf("\n%d dosyadan %d tanesi basariyla acildi.\n", dosya_sayisi, acilan);

    dosyalari_oku(fp_listesi, dosya_adlari, dosya_sayisi);

    dosyalari_kapat(fp_listesi, dosya_sayisi);

    return 0;
}
