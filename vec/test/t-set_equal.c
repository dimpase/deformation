#include "vec.h"

#include "flint.h"
#include "fmpz.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;

    int c;
    __mat_ctx_struct *ctx;
    mat_ctx_t *CTX;

    printf("set_equal... ");
    fflush(stdout);

    flint_randinit(state);

    CTX = malloc(2 * sizeof(mat_ctx_t));
    mat_ctx_init_long(CTX[0]);
    mat_ctx_init_mpq(CTX[1]);

    for (c = 0; c < 2; c++)
    {
        ctx = CTX[c];

        for (i = 0; i < 100; i++)
        {
            char *A, *B;
            long n;

            n = n_randint(state, 100) + 1;

            A = _vec_init(n, ctx);
            B = _vec_init(n, ctx);
            _vec_randtest(A, n, state, ctx);

            _vec_set(B, A, n, ctx);

            result = _vec_equal(A, B, n, ctx);
            if (!result)
            {
                printf("FAIL:\n\n");
                abort();
            }

            _vec_clear(A, n, ctx);
            _vec_clear(B, n, ctx);
        }
    }

    mat_ctx_clear(CTX[0]);
    mat_ctx_clear(CTX[1]);
    free(CTX);

    flint_randclear(state);
    _fmpz_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}
