#include <stdio.h>

int main() {
    int idade = 20;
    int tem_convite = 0; // 0 = Falso (não tem)

    // E (&&): Precisa ter mais de 18 E ter convite
    if ( (idade >= 18) && (tem_convite == 1) ) {
        printf("1. Pode entrar na festa VIP.\n");
    } else {
        printf("1. Nao pode entrar na festa VIP.\n");
    }

    // OU (||): Precisa ter mais de 18 OU ter convite
    if ( (idade >= 18) || (tem_convite == 1) ) {
        printf("2. Pode entrar na festa Pista.\n");
    } else {
        printf("2. Nao pode entrar na festa Pista.\n");
    }
    
    return 0;
}
