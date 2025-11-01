#include <stdio.h>

int main() {
    int idade;
    int tem_convite; // 0 = Nao, 1 = Sim

    // --- ENTRADA DE DADOS ---
    printf("Digite a sua idade: ");
    scanf("%d", &idade);

    printf("Voce tem convite? (Digite 1 para SIM ou 0 para NAO): ");
    scanf("%d", &tem_convite);

    printf("\n--- Verificando Acessos ---\n");

    // --- LÓGICA VIP (E / &&) ---
    // Precisa ter mais de 18 E ter convite
    if ( (idade >= 18) && (tem_convite == 1) ) {
        printf("1. (VIP): Acesso LIBERADO.\n");
    } else {
        printf("1. (VIP): Acesso NEGADO.\n");
    }

    // --- LÓGICA PISTA (OU / ||) ---
    // Precisa ter mais de 18 OU ter convite
    if ( (idade >= 18) || (tem_convite == 1) ) {
        printf("2. (Pista): Acesso LIBERADO.\n");
    } else {
        // Só entra aqui se for menor de 18 E não tiver convite
        printf("2. (Pista): Acesso NEGADO.\n");
    }
    
    return 0;
}
