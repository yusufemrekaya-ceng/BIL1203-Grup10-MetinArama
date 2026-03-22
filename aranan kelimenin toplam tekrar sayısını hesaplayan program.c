#include <stdio.h>
//Aranan kelimenin toplam tekrar sayısını hesaplayan program
int main() {
    char metin[1000];
    char kelime[100];
    int i = 0, j, sayac = 0;

    // Metni al (boşluk dahil)
    printf("Metni girin: ");
    char c;
    while ((c = getchar()) != '\n' && i < 999) {
        metin[i++] = c;
    }
    metin[i] = '\0';

    // Kelimeyi al
    printf("Aranacak kelimeyi girin: ");
    i = 0;
    while ((c = getchar()) != '\n' && i < 99) {
        kelime[i++] = c;
    }
    kelime[i] = '\0';

    // Metin uzunluğunu hesapla
    int metinUzunluk = 0;
    while (metin[metinUzunluk] != '\0') {
        metinUzunluk++;
    }

    // Kelime uzunluğunu hesapla
    int kelimeUzunluk = 0;
    while (kelime[kelimeUzunluk] != '\0') {
        kelimeUzunluk++;
    }

    // Arama işlemi
    for (i = 0; i <= metinUzunluk - kelimeUzunluk; i++) {
        for (j = 0; j < kelimeUzunluk; j++) {
            if (metin[i + j] != kelime[j]) {
                break;
            }
        }
        if (j == kelimeUzunluk) {
            sayac++;
        }
    }

    printf("Kelime %d kez tekrar edildi.\n", sayac);

    return 0;
}