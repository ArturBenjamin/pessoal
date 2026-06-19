# Projeto Final — Simulação de Propagação de Calor em Barra Metálica

Projeto desenvolvido para o **Vídeo 6** (Projeto Final + Debug + Análise) do
Grupo 1 — Programação.

Este programa simula a propagação de calor ao longo de uma barra metálica,
usando o método numérico de diferenças finitas. Ele inclui interação com o
usuário (com validação de entrada) e um modo de análise comparativa entre
dois cenários diferentes.

> **Atenção:** este arquivo (`projeto_com_bugs.cpp`) contém **3 bugs
> intencionais**, propositais para a parte de debug do vídeo. Veja a seção
> [Bugs Intencionais](#bugs-intencionais-para-o-vídeo-de-debug) abaixo.

---

## Requisitos

- Compilador C++ com suporte a C++17 (ex: `g++` 9 ou superior)
- Sistema Linux, macOS ou Windows (com WSL, MinGW ou similar)

Para verificar se você tem o `g++` instalado:

```bash
g++ --version
```

---

## Como Compilar

Na pasta onde está o arquivo `projeto_com_bugs.cpp`, rode:

```bash
g++ -std=c++17 -Wall -o projeto projeto_com_bugs.cpp
```

**Explicando os parâmetros:**
- `-std=c++17` → usa o padrão C++17 da linguagem
- `-Wall` → ativa avisos (warnings) do compilador, útil para pegar problemas
- `-o projeto` → nome do arquivo executável gerado

> **Nota:** como o arquivo contém um bug de compilação proposital (veja
> abaixo), essa primeira tentativa de compilar **vai falhar**. Isso é
> esperado — faz parte da demonstração de debug do vídeo.

---

## Como Rodar

Depois de compilar com sucesso:

```bash
./projeto
```

O programa vai exibir um menu interativo:

```
Escolha o modo:
  1 - Simulacao simples (interativa)
  2 - Comparacao entre dois cenarios
Opcao:
```

**Modo 1 — Simulação simples:** pede o tamanho da barra, número de
iterações, temperaturas das extremidades e se você quer ver todos os
passos ou só o resultado final.

**Modo 2 — Comparação de cenários:** pede os parâmetros de dois cenários
(A e B) e exibe os resultados finais lado a lado, para facilitar a
análise comparativa.

### Exemplo de uso (Modo 1)

```
Opcao: 1
Tamanho da barra (numero de posicoes, ex: 10): 10
Numero de iteracoes (ex: 50): 50
Temperatura na extremidade esquerda (ex: 100): 100
Temperatura na extremidade direita (ex: 0): 0
Mostrar todos os passos? (1-Sim 0-Nao): 0
```

---

## Bugs Intencionais (para o vídeo de debug)

Este código foi propositalmente "quebrado" em 3 pontos diferentes, cada um
representando um tipo de erro comum em programação. Eles aparecem **na
ordem em que devem ser corrigidos**, já que o Bug 1 impede até de compilar.

| # | Tipo | Onde | Sintoma |
|---|------|------|---------|
| 1 | Erro de **compilação** | `inicializar()` | O programa nem compila |
| 2 | Erro **lógico** | `simular()` | Compila e roda, mas o resultado está errado |
| 3 | Erro de **runtime** | `simular()` | Acesso fora dos limites do vetor (pode crashar) |

Cada um está marcado no código com um comentário `// BUG N:` e uma
explicação de como corrigir, logo abaixo da função correspondente.

### Roteiro de testes sugerido

1. **Compile o arquivo como está.** Vai falhar com o erro do Bug 1.
   Leia a mensagem do compilador — ele aponta a linha exata.

2. **Corrija o Bug 1** (troque `tempertura` por `temperatura` na função
   `inicializar()`) e compile novamente. Agora deve compilar sem erros.

3. **Rode o programa** com uma barra pequena (ex: 10 posições, 20
   iterações, temperaturas 100 e 0). Observe que a primeira posição da
   barra (que deveria ficar fixa em 100) muda de valor — esse é o Bug 2.

4. **Teste com uma barra maior** (ex: 30 posições, 200 iterações) para
   evidenciar o Bug 3. Para visualizar o erro de forma mais clara, compile
   com o **AddressSanitizer**, uma ferramenta que detecta acessos
   inválidos de memória:

   ```bash
   g++ -std=c++17 -Wall -fsanitize=address -g -o projeto_asan projeto_com_bugs.cpp
   ./projeto_asan
   ```

   Isso vai apontar exatamente a linha do `heap-buffer-overflow`.

5. **Corrija os Bugs 2 e 3 juntos**, trocando o loop dentro de `simular()`:

   ```cpp
   // Antes (com bug):
   for (int i = 0; i < n; i++) {

   // Depois (corrigido):
   for (int i = 1; i < n - 1; i++) {
   ```

6. **Compile e rode novamente.** Com tudo corrigido, a extremidade
   esquerda deve permanecer fixa em 100°C durante toda a simulação, e o
   programa deve rodar sem erros mesmo com barras grandes.

---

## Estrutura do Código

| Função | Responsabilidade |
|---|---|
| `inicializar()` | Configura o vetor da barra com as temperaturas iniciais |
| `simular()` | Executa as iterações da equação de diferenças finitas |
| `exibirResultados()` | Formata e imprime o estado da barra |
| `comparar()` | Roda dois cenários e exibe os resultados lado a lado |
| `lerInteiro()` / `lerDouble()` | Leem e validam entradas do usuário |
| `main()` | Orquestra o fluxo do programa |

---

## Arquivos do Projeto

- `projeto_com_bugs.cpp` — código-fonte com os 3 bugs intencionais
- `README.md` — este arquivo
