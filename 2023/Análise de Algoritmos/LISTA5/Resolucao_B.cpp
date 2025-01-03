#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calcularDistancia(const string& str1, const string& str2) {
    int tam_str1 = str1.length();
    int tam_str2 = str2.length();

    vector<vector<int>> matriz(tam_str1 + 1, vector<int>(tam_str2 + 1, 0));

    for (int i = 0; i <= tam_str1; ++i)
        matriz[i][0] = i;

    for (int j = 0; j <= tam_str2; ++j)
        matriz[0][j] = j;

    for (int i = 1; i <= tam_str1; ++i) {
        for (int j = 1; j <= tam_str2; ++j) {
            int custo_substituicao = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            int minimo = min({matriz[i - 1][j - 1] + custo_substituicao,
                              matriz[i - 1][j] + 1,
                              matriz[i][j - 1] + 1});
            matriz[i][j] = minimo;
        }
    }

    return matriz[tam_str1][tam_str2];
}

int main() {
    try {
        string str1, str2;
        while (getline(cin, str1) && getline(cin, str2)) {
            int distancia = calcularDistancia(str1, str2);
            cout << distancia << endl;
        }
    } catch (...) {
        
    }

    return 0;
}
