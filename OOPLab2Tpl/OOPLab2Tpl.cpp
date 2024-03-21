#include <iostream>
#include <clocale>
using namespace std;

int main1() {
    setlocale(LC_CTYPE, "ukr");

    cout << "Введiть значення a, b, c, d: ";
    int a, b, c, d, x, y;
    cin >> a >> b >> c >> d;

    x = ((a << 1) + (a << 2)) + (((d << 4) - d + (b << 1) + (b << 2)) >> 10) - (c << 1) + (c << 2) + (d << 4) - d;

    y = 12 * a + (d * 15 + 12 * b) / 1024 - 12 * c + d * 15;

    cout << " x=" << x << " y=" << y << " a=" << a << " b=" << b << " c=" << c << " d=" << d << endl;

    return 0;
}

// Функція для доповнення рядків пробілами до 32 символів
void padStrings(char text[][33], int numStrings) {
    for (int i = 0; i < numStrings; ++i) { //Цикл проходить через кожен рядок масиву text.
        int len = strlen(text[i]); // Отримання довжини поточного рядка
        if (len < 32) { 
            for (int j = len; j < 32; ++j) { //Цикл додає пробіли до кінця рядка, починаючи з кількості символів, рівної поточній довжині len, і досягаючи 32 символів.
                text[i][j] = ' ';// Доповнення рядка пробілами до 32 символів
            }
            text[i][32] = '\0'; // Закінчуємо рядок
        }
    }
}

// Функція для шифрування тексту
void encryptText(char text[][33], int numStrings, unsigned short Out[][33]) {
    for (int i = 0; i < numStrings; ++i) {
        for (int j = 0; j < 32; ++j) {
            char character = text[i][j]; // Отримання символу з рядка
            unsigned short encryptedChar = 0;

            // Позиція символу в рядку (5 біт)
            encryptedChar |= (j & 0x1F);

            // Номер рядка символу (2 біти)
            encryptedChar |= ((i & 0x03) << 5);

            // ASCII-код букви (8 біт)
            encryptedChar |= ((character & 0xFF) << 7);

            // Розрахунок біту парності
            int parityBit = 0;
            for (int k = 0; k < 15; ++k) {
                parityBit ^= (encryptedChar >> k) & 0x1;
            }
            encryptedChar |= (parityBit << 15); // Біт парності (1 біт)

            // Вивід результату
            cout << hex << encryptedChar << " ";
             Out[i][j] =encryptedChar;
        }
        cout << endl;
    }
}
void decryptText(unsigned short In[][33], int numStrings, char decryptedText[][33]) {
    for (int i = 0; i < numStrings; ++i) {
        for (int j = 0; j < 32; ++j) {
            unsigned short encryptedChar = In[i][j];
            int parityBit = (encryptedChar >> 15) & 0x1; // Відокремлення біту парності
            unsigned char character = (encryptedChar >> 7) & 0xFF; // Відновлення ASCII-коду символу
            int row = (encryptedChar >> 5) & 0x03; // Відокремлення номеру рядка
            int position = encryptedChar & 0x1F; // Відокремлення позиції символу в рядку

            // Відновлення символу
            decryptedText[row][position] = character;

            // Перевірка біту парності
            int calculatedParityBit = 0;
            for (int k = 0; k < 15; ++k) {
                calculatedParityBit ^= (encryptedChar >> k) & 0x1;
            }


            cout << decryptedText[row][position];
        }
        cout << endl;
    }
}




int main() {
    setlocale(LC_CTYPE, "ukr");

    //Створюємо змінні та пояснюємо завдання
    int task;
    std::cout << "Обчислення виразiв з використанням побiтових операцiй.Задано цiлi числа a, b, c та d.Обчислити вираз без використання операцiй множення та дiлення(замiнивши на їх операцiй зсувiв)." << endl;
    std::cout << endl;
    std::cout << " Задано 4 рядки тексту. У рядку до 32 символiв. Доповнити пробiлами рядки до 32 символiв" << endl;
    std::cout << " Шифрувати тексти таким чином, щоб кожний символ тексту записувався у два байти.Два байти " << endl;
    std::cout << " мають таку структуру : " << endl;
    std::cout << " у бiтах 0 - 4 позицiя символу в рядку(5 бiти), " << endl;
    std::cout << " у бiтах 5 - 6 знаходиться номер рядка символу(2 бiти), " << endl;
    std::cout << " у бiтах 7 - 14 ASCII - код букви(8 бiт), " << endl;
    std::cout << " 15 бiт - бiт парностi(1 бiт)." << endl;
    std::cout << endl;

    //Вибір завдання
    std::cout << "Вибрати завдання 1 або 2:" << endl;
    std::cin >> task;

    //Виклик функції
    if (task == 1) {
        main1();
    }
    else if (task == 2) {


        char text[4][33];
        cout << "Введiть 4 рядки тексту (до 32 символiв кожен):\n";
        cin.ignore();
        for (int i = 0; i < 4; ++i) {
            cin.getline(text[i], 33);
        }

        padStrings(text, 4);
     unsigned short Cod [4][33];
        cout << "Шифрований текст:\n";
        encryptText(text, 4, Cod);

        char decryptedText[4][33];
        cout << "Розшифрований текст:\n";
        decryptText(Cod, 4, decryptedText);

    }
}

