O compilador **GCC (GNU Compiler Collection)** possui diversas opções (chaves) que ajudam no controle da compilação. Aqui estão 10 das mais importantes:  

1. **`-o <arquivo>`** – Especifica o nome do arquivo de saída. Exemplo: `gcc programa.c -o programa`.  
2. **`-Wall`** – Ativa a maioria dos avisos úteis do compilador para detectar possíveis erros.  
3. **`-Wextra`** – Habilita avisos adicionais que não estão incluídos em `-Wall`.  
4. **`-g`** – Gera informações de depuração para uso com o GDB (GNU Debugger).  
5. **`-O[0-3]`** – Define o nível de otimização do código, onde `-O3` aplica otimizações mais agressivas.  
6. **`-std=<padrão>`** – Especifica o padrão da linguagem C/C++, como `-std=c99` ou `-std=c++11`.  
7. **`-pedantic`** – Garante que o código siga estritamente o padrão C/C++, emitindo avisos para extensões não padronizadas.  
8. **`-E`** – Executa apenas a etapa de pré-processamento, útil para analisar macros e diretivas `#include`.  
9. **`-c`** – Compila o código-fonte, mas não gera um executável, apenas arquivos objeto (`.o`).  
10. **`-static`** – Compila o programa com bibliotecas estáticas, tornando-o independente de bibliotecas compartilhadas.  

Essas opções ajudam a melhorar a qualidade do código, depuração, otimização e portabilidade ao usar o GCC.
