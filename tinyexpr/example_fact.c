#include "tinyexpr.h"
#include <stdio.h>


double fact(double n) {
  if (n < 1) return 1;
  return n * fact(n - 1);
}


int main(int argc, char *argv[])
{
    const char *expression = "2 * fact(5) / 3";
    printf("Avaliando:\n\t%s\n", expression);

    te_variable vars[] = {
        {"fact", fact, TE_FUNCTION1}
    };

    int err;
    te_expr *n = te_compile(expression, vars, 1, &err);

    if (n) {
        const double r = te_eval(n);
        printf("Resultado:\n\t%f\n", r);
        te_free(n);
    } else {
        /* Show the user where the error is at. */
        printf("\t%*s^\nErro nesta posição", err-1, "");
    }

    return 0;
}
