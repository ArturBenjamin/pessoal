/*
 * ============================================================================
 * PROJETO FINAL - Simulação de Propagação de Calor em Barra Metálica
 * Grupo 1 - Programação (Vídeo 6: Projeto Final + Debug + Análise)
 * ============================================================================
 *
 * VERSÃO COM ERROS INTENCIONAIS (para fins didáticos no vídeo de debug)
 *
 * Este programa contém 3 bugs propositais, na ordem em que aparecem
 * na apresentação:
 *
 *   BUG 1 (Compilação) -> dentro de inicializar()   [linha ~38]
 *   BUG 2 (Lógico)      -> dentro de simular()       [linha ~62]
 *   BUG 3 (Runtime)     -> dentro de simular()       [linha ~62, mesma área]
 *
 * Cada bug está marcado com um comentário "// BUG N:" para facilitar
 * localizar durante a gravação do vídeo.
 *
 * COMO USAR ESTE ARQUIVO:
 *   1) Tente compilar como está -> vai falhar (Bug 1, erro de compilação).
 *   2) Corrija o Bug 1 (veja a dica no comentário) e recompile.
 *   3) Rode o programa -> vai compilar e rodar, mas o resultado estará
 *      sutilmente errado (Bug 2, erro lógico). Use os prints de debug
 *      indicados para perceber o problema.
 *   4) Depois de corrigir o Bug 2, rode novamente com uma barra grande
 *      (ex: 30 posições) -> o programa pode travar/crashar (Bug 3,
 *      erro de runtime / acesso fora dos limites do vetor).
 *   5) Corrija o Bug 3 e o programa deve funcionar perfeitamente.
 *
 * Para compilar:
 *   g++ -std=c++17 -Wall -o projeto projeto_com_bugs.cpp
 *
 * Para rodar:
 *   ./projeto
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// ----------------------------------------------------------------------------
// Função: inicializar()
// Configura o vetor da barra com temperaturas iniciais e fixa as
// extremidades conforme os valores informados pelo usuário.
// ----------------------------------------------------------------------------
void inicializar(vector<double>& barra, double tempEsq, double tempDir) {
    int n = barra.size();

    // Preenchimento inicial: todas as posições internas começam em 0
    for (int i = 0; i < n; i++) {
        barra[i] = 0.0;
    }

    // BUG 1 (Erro de Compilação): typo no nome da variável.
    // 'tempertura' foi declarada, mas seria usada como 'temperatura'.
    // O compilador vai acusar: "'temperatura' was not declared in this scope"
    double tempertura = tempEsq;
    barra[0]   = temperatura;   // <-- ERRO: nome errado, não compila
    barra[n-1] = tempDir;

    // DICA DE CORREÇÃO:
    // Troque a declaração para "double temperatura = tempEsq;"
    // (ou troque o uso para "tempertura" - mas o certo é corrigir o nome
    // para "temperatura", que é o que faz sentido semanticamente).
}

// ----------------------------------------------------------------------------
// Função: exibirResultados()
// Formata e imprime o estado da barra. Pode mostrar apenas o resultado
// final ou cada passo da simulação, dependendo do parâmetro 'rotulo'.
// ----------------------------------------------------------------------------
void exibirResultados(const vector<double>& barra, int passo) {
    cout << "Passo " << setw(3) << passo << ": ";
    cout << fixed << setprecision(1);
    for (double v : barra) {
        cout << setw(7) << v;
    }
    cout << endl;
}

// ----------------------------------------------------------------------------
// Função: simular()
// Executa o loop de iterações aplicando a equação de diferenças finitas
// para condução de calor. Usa um vetor auxiliar para não sobrescrever
// valores que ainda serão lidos durante o cálculo da mesma iteração.
// ----------------------------------------------------------------------------
void simular(vector<double>& barra, int iteracoes, bool verbose) {
    int n = barra.size();
    vector<double> aux(n); // vetor auxiliar

    for (int t = 0; t < iteracoes; t++) {

        // Copia as extremidades (temperaturas fixas / condição de contorno)
        aux[0]   = barra[0];
        aux[n-1] = barra[n-1];

        // BUG 2 (Erro Lógico) + BUG 3 (Erro de Runtime):
        // O loop deveria ir de i=1 até i=n-2 (preservando as extremidades
        // e nunca acessando além do vetor). Aqui ele está incorreto:
        //   - Começa em i=0  -> sobrescreve a extremidade esquerda
        //     (Bug 2: resultado fica sutilmente errado, sem erro nenhum
        //      do compilador ou do sistema).
        //   - Vai até i<n    -> na última iteração, i = n-1, e o código
        //     tenta acessar barra[i+1] = barra[n], que está FORA do vetor
        //     (Bug 3: comportamento indefinido / possível segmentation fault,
        //      principalmente em barras maiores).
        for (int i = 0; i < n; i++) {
            aux[i] = (barra[i-1] + barra[i] + barra[i+1]) / 3.0;
        }

        barra = aux; // atualiza com os novos valores

        // DEBUG: descomente a linha abaixo para rastrear a extremidade
        // esquerda e perceber o Bug 2 (ela não deveria mudar de valor!)
        // cout << "[debug] barra[0] = " << barra[0] << endl;

        if (verbose) {
            exibirResultados(barra, t);
        }
    }

    // DICA DE CORREÇÃO (Bugs 2 e 3):
    // Troque o loop para:
    //   for (int i = 1; i < n - 1; i++) {
    //       aux[i] = (barra[i-1] + barra[i] + barra[i+1]) / 3.0;
    //   }
    // Isso resolve os dois problemas ao mesmo tempo: preserva as
    // extremidades fixas (Bug 2) e nunca acessa índice fora do vetor (Bug 3).
}

// ----------------------------------------------------------------------------
// Função: comparar()
// Recebe dois conjuntos de parâmetros, roda ambas as simulações e exibe
// os resultados finais lado a lado para facilitar a análise.
// ----------------------------------------------------------------------------
void comparar(int nA, int iterA, int nB, int iterB,
              double tempEsq, double tempDir) {

    vector<double> barraA(nA);
    vector<double> barraB(nB);

    inicializar(barraA, tempEsq, tempDir);
    inicializar(barraB, tempEsq, tempDir);

    cout << "\n--- Rodando Cenario A (n=" << nA
         << ", iteracoes=" << iterA << ") ---\n";
    simular(barraA, iterA, false);

    cout << "\n--- Rodando Cenario B (n=" << nB
         << ", iteracoes=" << iterB << ") ---\n";
    simular(barraB, iterB, false);

    cout << "\n========== COMPARACAO DE RESULTADOS ==========\n";
    cout << "\nCenario A (barra de " << nA << " posicoes):\n";
    exibirResultados(barraA, iterA);

    cout << "\nCenario B (barra de " << nB << " posicoes):\n";
    exibirResultados(barraB, iterB);

    cout << "\nObservacao: compare como o tamanho da barra e o numero de\n";
    cout << "iteracoes afetam a velocidade com que o calor se distribui.\n";
}

// ----------------------------------------------------------------------------
// Função: lerInteiro()
// Lê e valida entradas inteiras do usuário, dentro de um intervalo
// [minVal, maxVal]. Em caso de entrada inválida, exibe mensagem de erro
// e pede para digitar novamente.
// ----------------------------------------------------------------------------
int lerInteiro(const string& msg, int minVal, int maxVal) {
    int valor;
    while (true) {
        cout << msg;
        if (cin >> valor && valor >= minVal && valor <= maxVal) {
            return valor; // entrada válida
        }
        // Entrada inválida: limpar o estado de erro e o buffer do cin
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Valor invalido. Digite um numero entre "
             << minVal << " e " << maxVal << ".\n";
    }
}

double lerDouble(const string& msg) {
    double valor;
    while (true) {
        cout << msg;
        if (cin >> valor) {
            return valor;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Valor invalido. Digite um numero (ex: 100 ou 100.0).\n";
    }
}

// ----------------------------------------------------------------------------
// Função: main()
// Orquestra as chamadas: apresenta o menu, coleta os parâmetros do
// usuário e chama as funções na ordem correta.
// ----------------------------------------------------------------------------
int main() {
    cout << "============================================================\n";
    cout << " SIMULACAO DE PROPAGACAO DE CALOR EM BARRA METALICA\n";
    cout << " Projeto Final - Video 6 (versao COM BUGS para debug)\n";
    cout << "============================================================\n\n";

    int opcao = lerInteiro(
        "Escolha o modo:\n"
        "  1 - Simulacao simples (interativa)\n"
        "  2 - Comparacao entre dois cenarios\n"
        "Opcao: ",
        1, 2
    );

    if (opcao == 1) {
        int n = lerInteiro("\nTamanho da barra (numero de posicoes, ex: 10): ", 3, 200);
        int iteracoes = lerInteiro("Numero de iteracoes (ex: 50): ", 1, 5000);
        double tempEsq = lerDouble("Temperatura na extremidade esquerda (ex: 100): ");
        double tempDir = lerDouble("Temperatura na extremidade direita (ex: 0): ");
        int verboseOpc = lerInteiro("Mostrar todos os passos? (1-Sim 0-Nao): ", 0, 1);

        vector<double> barra(n);
        inicializar(barra, tempEsq, tempDir);

        cout << "\nEstado inicial:\n";
        exibirResultados(barra, 0);

        cout << "\nIniciando simulacao...\n";
        simular(barra, iteracoes, verboseOpc == 1);

        cout << "\nEstado final:\n";
        exibirResultados(barra, iteracoes);

    } else {
        cout << "\n--- Configuracao do Cenario A ---\n";
        int nA = lerInteiro("Tamanho da barra A (ex: 10): ", 3, 200);
        int iterA = lerInteiro("Iteracoes do Cenario A (ex: 50): ", 1, 5000);

        cout << "\n--- Configuracao do Cenario B ---\n";
        int nB = lerInteiro("Tamanho da barra B (ex: 30): ", 3, 200);
        int iterB = lerInteiro("Iteracoes do Cenario B (ex: 200): ", 1, 5000);

        double tempEsq = lerDouble("\nTemperatura na extremidade esquerda (ex: 100): ");
        double tempDir = lerDouble("Temperatura na extremidade direita (ex: 0): ");

        comparar(nA, iterA, nB, iterB, tempEsq, tempDir);
    }

    cout << "\nFim do programa.\n";
    return 0;
}
