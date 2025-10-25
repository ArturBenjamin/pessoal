 int opcao;
    do {
        printf("Menu:\n");
        printf("1 - Sortear bola\n");
        printf("2 - Mostrar bolas restantes\n");
        printf("0 - Encerrar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int bola = sortear_bola(&saco);
                if (bola != -1)
                    printf("\n🎱 Bola sorteada: %d\n\n", bola);
                break;
            }
