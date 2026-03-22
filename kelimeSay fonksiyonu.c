#include <stdio.h>

// Kelimeyi metin içinde sayan fonksiyon
int kelimeSay(char metin[], char kelime[]) {
    int i, j, sayac = 0;

    // metin uzunluğu hesaplama
    int metinUzunluk = 0;
    while (metin[metinUzunluk] != '\0') {
        metinUzunluk++;
    }

    // kelime uzunluğu hesaplama
    int kelimeUzunluk = 0;
    while (kelime[kelimeUzunluk] != '\0') {
        kelimeUzunluk++;
    }

    // arama işlemi burada gerçekleşiyor
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

    return sayac;
}

int main() {
    char metin[1000];
    char kelime[100];
    int i = 0;
    char c;

    // Metni alma
    printf("Metni girin: ");
    while ((c = getchar()) != '\n' && i < 999) {
        metin[i++] = c;
    }
    metin[i] = '\0';

    // Kelimeyi alma
    printf("Aranacak kelimeyi girin: ");
    i = 0;
    while ((c = getchar()) != '\n' && i < 99) {
        kelime[i++] = c;
    }
    kelime[i] = '\0';

    // Fonksiyonu çağırma
    int sonuc = kelimeSay(metin, kelime);

    printf("Kelime %d kez tekrar edildi.\n", sonuc);

    return 0;
}