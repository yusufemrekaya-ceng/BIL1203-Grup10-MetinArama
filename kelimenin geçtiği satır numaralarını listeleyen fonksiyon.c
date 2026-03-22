#include <stdio.h>

int satirdaVarMi(char satir[], char kelime[]) {
    int i, j, k;

    for (i = 0; satir[i] != '\0'; i++) {
        k = i;
        j = 0;

        while (kelime[j] != '\0' && satir[k] == kelime[j]) {
            j++;
            k++;
        }

        if (kelime[j] == '\0') {
            return 1; // bulundu
        }
    }

    return 0; // bulunamadı
}

void satirNumaralariniBul() {
    char c;
    char satir[1000];
    char kelime[100];
    int i = 0, satirNo = 1;

    printf("Aranacak kelimeyi gir: ");
    scanf("%s", kelime);

    printf("Metni gir (CTRL+Z ile bitir):\n");

    i = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            satir[i] = '\0';

            if (satirdaVarMi(satir, kelime)) {
                printf("Kelime %d. satirda bulundu\n", satirNo);
            }

            satirNo++;
            i = 0;
        } else {
            satir[i++] = c;
        }
    }

    // Son satır kontrolü (EOF'ta newline yoksa)
    if (i > 0) {
        satir[i] = '\0';
        if (satirdaVarMi(satir, kelime)) {
            printf("Kelime %d. satirda bulundu\n", satirNo);
        }
    }
}

int main() {
    satirNumaralariniBul();
    return 0;
}