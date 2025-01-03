#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int MAX_N = 2e5 + 1;

map<int, int> mapaTempo;
int N, inicio[MAX_N], fim[MAX_N];
struct Tarefa { int horario, id, tipo; } tarefasAgendadas[2 * MAX_N];
long long lucro[MAX_N], programacaoDinamica[2 * MAX_N];


int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        scanf("%d %d %lld", &inicio[i], &fim[i], &lucro[i]);
        tarefasAgendadas[2 * i] = {inicio[i], i, 0};
        tarefasAgendadas[2 * i + 1] = {fim[i], i, 1};
    }

    sort(tarefasAgendadas + 2, tarefasAgendadas + 2 * N + 2, [](Tarefa A, Tarefa B) {
        return A.horario == B.horario ? A.id < B.id : A.horario < B.horario;
    });

    for (int i = 2; i <= 2 * N + 1; i++)
        if (!mapaTempo[tarefasAgendadas[i].horario])
            mapaTempo[tarefasAgendadas[i].horario] = i;

    for (int i = 2; i <= 2 * N + 1; i++) {
        if (tarefasAgendadas[i].tipo == 0)
            programacaoDinamica[i] = programacaoDinamica[i - 1];
        else
            programacaoDinamica[i] = max(programacaoDinamica[i - 1], programacaoDinamica[mapaTempo[inicio[tarefasAgendadas[i].id]] - 1] + lucro[tarefasAgendadas[i].id]);
    }

    cout << programacaoDinamica[2 * N + 1] << '\n';
}
