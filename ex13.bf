,>++++++++++[<-------->-]<      // Lê 1º dígito e subtrai 48
> ,>++++++++++[<-------->-]<    // Lê 2º dígito e subtrai 48

<<<                             // Volta para o primeiro número
[                               // Loop externo (multiplicador)
    > [->+>+<<]                 // Copia o multiplicando
    >> [-<<+>>]                 // Move uma cópia para resultado
    <<                          // Volta
    -                           // Decrementa o multiplicador
]

>>>                             // Vamos imprimir o resultado
+++++ +++++                     // Adiciona 10 (para divisão)
[                               // Divide o resultado por 10
    > ++++++++++                // Adiciona 10 ao quociente
    < -                         // Decrementa o total
]
>                               // Move para quociente
.                               // Imprime dezena

< ++++++++++                    // Corrige unidade
[->+<]                          // Move unidade para próxima célula
> .                             // Imprime unidade
