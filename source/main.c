#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gmp.h>

void get_pi(unsigned long int digit, mpf_t result)
{
	mp_bitcnt_t backup;
	mpf_t n1, n2, n3, n4;
	mpf_t part, total;

	unsigned long int iteration;

	if (digit < 3)
		return ;

	iteration = (digit / log(16) + 10) * 1.0001;

	backup = mpf_get_default_prec();
	mpf_set_default_prec(digit * log2(10) + 10);

	mpf_inits(n1, n2, n3, n4, NULL);
	mpf_inits(part, total, result, NULL);

	mpf_set_default_prec(backup);

	for (unsigned long long int k = 0; k < iteration; k++)
	{
		mpf_set_d(n1, 4.0 / ((8 * k) + 1));
		mpf_set_d(n2, 2.0 / ((8 * k) + 4));
		mpf_set_d(n3, 1.0 / ((8 * k) + 5));
		mpf_set_d(n4, 1.0 / ((8 * k) + 6));

		mpf_set(part, n1);
		mpf_sub(part, part, n2);
		mpf_sub(part, part, n3);
		mpf_sub(part, part, n4);

		mpf_div_2exp(total, part, 4 * k);

		mpf_add(result, result, total);
	}

	mpf_clears(n1, n2, n3, n4, NULL);
	mpf_clears(part, total, NULL);
}

char *get_pi_string(int digit)
{
	mp_exp_t bitcnt;
	mpf_t result;
	char *output = malloc(digit + 2);

	get_pi(digit, result);

	mpf_get_str(&output[1], &bitcnt, 10, digit, result);
	output[0] = '3'; output[1] = '.';

	mpf_clear(result);

	return output;
}

int main(int argc, char *argv[])
{
	int digit;
	char *output;

	if (argc != 2) {
		printf("usage: %s <digit>\n", argv[0]);
		return 1;
	}

	digit = strtol(argv[1], NULL, 10);
	if (digit < 3) {
		printf("<digit> at least greater than 3\n");
		return 1;
	}

	printf("%s\n", (output = get_pi_string(digit)));

	free(output);

	return 0;
}
