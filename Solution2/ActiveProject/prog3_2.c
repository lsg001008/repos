#include <stdio.h>
#define MAX(a, b) a > b ? a : b
#define MAX_DEGREE 64

typedef struct {
	int degree;
	double coef[MAX_DEGREE];
} Polynomial;

Polynomial add(Polynomial A, Polynomial B) {
	Polynomial C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree);

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else {
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

void print_poly(Polynomial p) {
	for (int i = p.degree; i > 0; i--) {
		printf("%3.1lfx^%d + ", p.coef[p.degree - i], i);
	}
	printf("%3.1lf\n", p.coef[p.degree]);
}

int main() {
	Polynomial a = { 5, {3, 6, 0, 0, 0, 10} };
	Polynomial b = { 4, {7, 0, 5, 0, 1} };
	Polynomial c;

	print_poly(a);
	print_poly(b);
	c = add(a, b);
	printf("--------------------------------------------------\n");
	print_poly(c);
}