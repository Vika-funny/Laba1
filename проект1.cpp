#include <iostream>
#include <cstring>
#include <cstdint>

using namespace std;

int main() {
    system("chcp 65001 > nul");

    cout << "Задание 1" << endl;
    cout << "bool: " << sizeof(bool) << endl;
    cout << "char: " << sizeof(char) << endl;
    cout << "short int: " << sizeof(short int) << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "long int: " << sizeof(long int) << endl;
    cout << "float: " << sizeof(float) << endl;
    cout << "double: " << sizeof(double) << endl;
    cout << "long double: " << sizeof(long double) << endl << endl;

    auto printBits = [](uint64_t val, int width) {
        for (int i = width - 1; i >= 0; --i) {
            cout << ((val >> i) & 1);

            if (i == width - 1) {
                cout << " | "; 
            }
            else if (width == 32 && i == 23) {
                cout << " | "; 
            }
            else if (width == 64 && i == 52) {
                cout << " | "; 
            }
            else if ((width - 1 - i) % 8 == 7) {
                cout << " ";   
            }
        }
        cout << endl;
        };

    cout << "Задание 2" << endl;

    int intVar;
    cout << "Введите целое число: ";
    cin >> intVar;

    unsigned int uInt = static_cast<unsigned int>(intVar);
    cout << "Биты числа: ";
    printBits(uInt, 32);
    cout << "Первый бит — знаковый разряд. Значение как unsigned: " << uInt << endl << endl;

    cout << "Задание 3" << endl;

    float floatVar;
    cout << "Введите число float: ";
    cin >> floatVar;

    uint32_t floatBits;
    std::memcpy(&floatBits, &floatVar, sizeof(floatBits));

    int fSign = (floatBits >> 31) & 1u;
    uint32_t fExponent = (floatBits >> 23) & 0xFFu;
    uint32_t fMantissa = floatBits & ((1u << 23) - 1);

    cout << "Биты float (знак | порядок | мантисса): ";
    printBits(floatBits, 32);
    cout << "Размер полей: 1 + 8 + 23 бит. Смещение порядка: 127" << endl;
    cout << "В десятичной: знак=" << fSign << ", порядок=" << fExponent << ", мантисса=" << fMantissa << endl << endl;

    cout << "Задание 4" << endl;

    double doubleVar;
    cout << "Введите число типа double: ";
    cin >> doubleVar;

    uint64_t doubleBits;
    std::memcpy(&doubleBits, &doubleVar, sizeof(doubleBits));

    uint64_t dSign = (doubleBits >> 63) & 1ULL;
    uint64_t dExponent = (doubleBits >> 52) & 0x7FFULL;
    uint64_t dMantissa = doubleBits & ((1ULL << 52) - 1);

    cout << "Биты double (знак | порядок | мантисса): ";
    printBits(doubleBits, 64); 
    cout << "Размер полей: 1 + 11 + 52 бит. Смещение порядка: 1023" << endl;
    cout << "В десятичной: знак=" << dSign << ", порядок=" << dExponent << ", мантисса=" << dMantissa << endl << endl;

    cout << "Задание 5" << endl;
    int modValue, bitIndex, operation;
    cout << "Введите целое число: ";
    cin >> modValue;
    cout << "Введите номер бита (0-31): ";
    cin >> bitIndex;

    if (bitIndex < 0 || bitIndex > 31) {
        cout << "Номер бита должен быть от 0 до 31" << endl;
    }
    else {
        cout << "Выберите операцию (1 - Поставить 1, 2 - Сбросить в 0, 3 - Инвертировать): ";
        cin >> operation;

        if (operation < 1 || operation > 3) {
            cout << "Ошибка" << endl;
        }
        else {
            auto modifyBit = [](uint32_t value, int bit, int op) -> uint32_t {
                if (op == 1) value |= (1u << bit);
                else if (op == 2) value &= ~(1u << bit);
                else if (op == 3) value ^= (1u << bit);
                return value;
                };

            uint32_t uMod = static_cast<uint32_t>(modValue);
            uint32_t uResult = modifyBit(uMod, bitIndex, operation);

            cout << "Исходное число в битах: ";
            printBits(uMod, 32);
            cout << "Результат в битах:        ";
            printBits(uResult, 32);
            cout << "Результат в десятичной: " << static_cast<int>(uResult) << endl << endl;
        }
    }

    cout << "Индивидуальное задание (Умножение на 2 через сдвиг)" << endl;

    int indValue;
    cout << "Введите целое число для умножения на 2: ";
    cin >> indValue;

    int indResult = indValue << 1;
    cout << "Результат: " << indResult << endl;
    cout << "Биты до:   ";
    printBits(static_cast<uint32_t>(indValue), 32);
    cout << "Биты после: ";
    printBits(static_cast<uint32_t>(indResult), 32);

    return 0;
}
