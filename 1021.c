#include <stdio.h>

int main()
{
    double dinheiro, troco;
    int valNotas[] = {100, 50, 20, 10, 5, 2};
    int valMoedas[] = {100, 50, 25, 10, 5, 1};
    int notas[6] = {};
    int moedas[6] = {};

    scanf("%lf", &dinheiro);

    printf("NOTAS:\n");

    int nNotas = sizeof(valNotas) / sizeof(valNotas[0]);
    for (int i = 0; i < nNotas; i++)
    {
        printf("teste %i\n", i);
        notas[i] = dinheiro / valNotas[i];
        if (valNotas[i] == 100)
        {
            troco = dinheiro - (notas[i] * valNotas[i]);
        }
        else
        {
            troco -= notas[i] * valNotas[i];
        }
        printf("%d nota(s) de R$ %d.00\n", notas[i], valNotas[i]);
    }
}