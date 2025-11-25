#include <stdio.h>
#include <math.h>

int main()
{
    double dinheiro;
    scanf("%lf", &dinheiro);

    int total = (int)round(dinheiro * 100);

    int valNotas[] = {10000, 5000, 2000, 1000, 500, 200};
    int valMoedas[] = {100, 50, 25, 10, 5, 1};

    printf("NOTAS:\n");
    for (int i = 0; i < 6; i++)
    {
        int qtd = total / valNotas[i];
        total %= valNotas[i];
        printf("%d nota(s) de R$ %.2f\n", qtd, valNotas[i] / 100.0);
    }

    printf("MOEDAS:\n");
    for (int i = 0; i < 6; i++)
    {
        int qtd = total / valMoedas[i];
        total %= valMoedas[i];
        printf("%d moeda(s) de R$ %.2f\n", qtd, valMoedas[i] / 100.0);
    }

    return 0;
}
