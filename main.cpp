#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @brief Функция для вычисления длины LCS (наибольшей общей подпоследовательности) двух строк
 *        с использованием памяти только для двух строк.
 *
 * @param X Первая строка.
 * @param Y Вторая строка.
 * @return Вектор, содержащий длины LCS для каждой позиции.
 */
vector<int> lcsLength(const string& X, const string& Y) {
    int m = X.size();
    int n = Y.size();
    vector<vector<int>> L(2, vector<int>(n + 1));

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0)
                L[i % 2][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i % 2][j] = L[(i - 1) % 2][j - 1] + 1;
            else
                L[i % 2][j] = max(L[(i - 1) % 2][j], L[i % 2][j - 1]);
        }
    }

    return L[m % 2];
}

/**
 * @brief Рекурсивная функция для вычисления наибольшей общей подпоследовательности (LCS)
 *        двух строк с использованием метода Хиршберга.
 *
 * @param X Первая строка.
 * @param Y Вторая строка.
 * @return Строка, содержащая LCS.
 */
string hirschberg(const string& X, const string& Y) {
    int m = X.size();
    int n = Y.size();

    // Базовые случаи
    if (m == 0)
        return "";
    if (m == 1) {
        if (Y.find(X[0]) != string::npos)
            return string(1, X[0]);
        else
            return "";
    }
    if (n == 0)
        return "";

    int mid = m / 2;

    // Вычисляем LCS длины для двух половин
    vector<int> L1 = lcsLength(X.substr(0, mid), Y);
    vector<int> L2 = lcsLength(string(X.rbegin(), X.rend()).substr(0, m - mid), string(Y.rbegin(), Y.rend()));

    int maxIndex = 0;
    int maxSum = 0;

    // Находим точку разделения
    for (int j = 0; j <= n; ++j) {
        if (L1[j] + L2[n - j] > maxSum) {
            maxSum = L1[j] + L2[n - j];
            maxIndex = j;
        }
    }

    // Рекурсивно вычисляем LCS для подстрок
    string LCS1 = hirschberg(X.substr(0, mid), Y.substr(0, maxIndex));
    string LCS2 = hirschberg(X.substr(mid), Y.substr(maxIndex));

    return LCS1 + LCS2;
}

/**
 * @brief Главная функция программы. Точка входа.
 *
 * @return int Статус завершения программы.
 */
int main() {
    string X1 = "12345";
    string Y1 = "54321";

    string result1 = hirschberg(X1, Y1);
    cout << "The greatest common subsequence: " << result1 << endl;

    string X2 = "ABCBDAB";
    string Y2 = "BDCAB";

    string result2 = hirschberg(X2, Y2);
    cout << "The greatest common subsequence: " << result2 << endl;

    string X3 = "XMJYAUZ";
    string Y3 = "MZJAWXU";

    string result3 = hirschberg(X3, Y3);
    cout << "The greatest common subsequence: " << result3 << endl;

    string X4 = "ABCD";
    string Y4 = "EFGH";

    string result4 = hirschberg(X4, Y4);
    cout << "The greatest common subsequence: " << ((result4 == "") ? "empty string" : result4) << endl;

    return 0;
}
