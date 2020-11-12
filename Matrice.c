#include <stdio.h>
#include <stdlib.h>

// Functie adunare si scadere.
void adunare(float *matrix1, float *matrix2, int n1, int c1, int selectie) {
	float* matrix3 = (float*)malloc(n1*c1 * sizeof(float));
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < c1; j++) {
			if (selectie == 1) *(matrix3 + i*c1 + j) = *(matrix1 + i*c1 + j) + *(matrix2 + i*c1 + j);
			else *(matrix3 + i*c1 + j) = *(matrix1 + i*c1 + j) - *(matrix2 + i*c1 + j);
		}
	}
	printf("Matricea rezultanta este:\n");
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < c1; j++) {
			printf("%g ", *(matrix3 + i*c1 + j));
			if (j == c1 - 1) printf("\n");
		}
	}
}

// Functie inmultire.  
void inmultire(float *matrix1, float *matrix2, int a, int b, int c) {
	float*rezultat = (float*)malloc(a*c * sizeof(float));
	float element = 0;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			for (int k = 0; k < b; k++) {
				element += *(matrix1 + i*b + k) * *(matrix2 + k*c + j);
			}
			*(rezultat + i*c + j) = element;
			element = 0;
		}
	}
	printf("Matricea rezultanta este:\n");
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			printf("%g ", *(rezultat + i*c + j));
		}
		printf("\n");
	}
}


/* Functie afisare spirala. Afisam extremitatile matricei iar apoi micsoram matricea.
Spre exemplu, daca avem matricea 0 0 0
								 3 4 1
								 2 2 1
Pasul 1: afisam 0,0,0
Pasul 2: afisam 1,1
Pasul 3: afisam 2,2
Pasul 4: afisam 3
Pasul 5: afisam 4
*/
int spiral(float mat[], int linii, int coloane) {
	int n = linii - 1, c = coloane - 1, ni = 0, ci = 0, contor = 0;
	while (1) {
		for (int j = ci; j <= c; j++) {
			printf("%g ", *(mat + ni*coloane + j));
			contor++;
			if (contor == linii*coloane) return 0;
		}
		for (int i = ni + 1; i <= n; i++) {
			printf("%g ", *(mat + i*coloane + c));
			contor++;
			if (contor == linii*coloane) return 0;
		}
		for (int j = c - 1; j >= ci; j--) {
			printf("%g ", *(mat + n*coloane + j));
			contor++;
			if (contor == linii*coloane) return 0;
		}
		for (int i = n - 1; i > ni; i--) {
			printf("%g ", *(mat + i*coloane + ci));
			contor++;
			if (contor == linii*coloane) return 0;
		}
		n--;
		c--;
		ni++;
		ci++;
	}
}

/* Functie determinant. Pentru matrice > 2x2, mai intai verificam daca exista vreo linie sau coloana cu toate
elementele = 0 sau daca exista doua linii sau coloane egale. Ratinamentul pentru calcularea determinantului
este urmatorul: Definim o matrice U cu toate elementele de sub diagonala ca fiind egale cu 0 si inca o matrice L cu toate
elementele de deasupra diagonalei ca fiind egale cu 0 dar cu elementele de pe diagonala egale cu 1. Apoi aflam restul de
elemente ale matricei U folosindu-ne de urmatoarea formula:
i = 0 -> Uij = Aij
i > 0 -> Uij = Aij - [Suma(k=0)(k<i): Lik*Ukj]
Apoi aflam restul de elemente ale matricei L folosindu-ne de urmatoarea formula:
j = 0 -> Lij = Aij / Ujj
j > 0 -> Lij = {Aij - [Suma(k=0)(k<j): Lik*Ukj]} / Ujj
Determinantul matricei initiale este egal cu produsul elementelor de pe diagonala matricei U.
Algoritmul functioneaza in urmatorul fel:
// Pasul 1: se calculeaza linia 0 a matricei U (i=0 si j merge de la i la n-1)
// Pasul 2: se calculeaza coloana 0 a matricei L (deci j=0 si si i merge de j+1 la n-1)
// Pasul 3: se calculeaza linia 1 matricei U (deci i=1 si j merge de la i la n-1)
// Pasul 4: se calculeaza coloana 1 a matricei L (deci j = 1 si i merge de la j+1 la n-1)
// .......
*/
float det(float mat[], int n, int afisare) {
	switch (n) {
	case 1:
		if (afisare == 1) printf("Determinantul este %g.", *mat);
		else return *mat;
		break;
	case 2:
		if (afisare == 1) printf("Determinantul este %g.", (*mat * *(mat + 3)) - (*(mat + 2) * *(mat + 1)));
		else return (*mat * *(mat + 3)) - (*(mat + 2) * *(mat + 1));
		break;
	default:
		// Verificam daca exista vreo linie sau coloana cu toate elementele = 0.
		int contor = 0, contor2 = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (*(mat + i*n + j) == 0) contor++;
				if (*(mat + j*n + i) == 0) contor2++;
				if (contor == n || contor2 == n) {
					printf("Matricea are o linie sau o coloana cu toate elementele = 0. Determinantul este 0.");
					return 0;
				}
			}
			contor = 0;
			contor2 = 0;
		}
		// Verificam daca exista doua linii sau doua coloane egale.
		for (int i = 0; i < n; i++) {
			for (int i2 = i + 1; i2 < n; i2++) {
				for (int j = 0; j < n; j++) {
					if (*(mat + i*n + j) == *(mat + i2*n + j)) contor++;
					if (*(mat + j*n + i) == *(mat + j*n + i2)) contor2++;
					if (contor == n || contor2 == n) {
						printf("Matricea are doua linii sau doua coloane egale. Determinantul este 0.");
						return 0;
					}
				}
				contor = 0;
				contor2 = 0;
			}
		}
		// Algoritm determinant matrice > 2x2.
		float sum = 0, det = 1;
		float* lower = (float*)malloc(n*n * sizeof(float));
		float* upper = (float*)malloc(n*n * sizeof(float));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				*(lower + i*n + j) = 0;
				*(upper + i*n + j) = 0;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				if (i == 0) *(upper + i*n + j) = *(mat + i*n + j);
				else {
					for (int k = 0; k < i; k++) {
						*(upper + i*n + j) += *(lower + i*n + k) * *(upper + k*n + j);
					}
					*(upper + i*n + j) = *(mat + i*n + j) - *(upper + i*n + j);
				}
			}
			for (int j = i + 1; j < n; j++) {
				if (i == 0) *(lower + j*n + i) = *(mat + j*n + i) / *(upper + i*n + i);
				else {
					for (int k = 0; k < i; k++) {
						*(lower + j*n + i) += *(lower + j*n + k) * *(upper + k*n + i);
					}
					*(lower + j*n + i) = (*(mat + j*n + i) - *(lower + j*n + i)) / *(upper + i*n + i);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			det = det * *(upper + i*n + i);
		}
		if (afisare == 1) {
			printf("\nDeterminantul este %g", det);
			return 0;
		}
		else {
			return det;
		}
	}
}
// TRANSPUSA
void transpusa(float *matrix, int n, int c) {
	float *matrix2 = (float*)malloc(n*c * sizeof(float));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < c; j++) {
			*(matrix2 + j*n + i) = *(matrix + i*c + j);
		}
	}
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < n; j++) {
			printf("%g", *(matrix2 + i*n + j));
		}
		printf("\n");
	}
}

// Functie exponent. Algoritmul functioneaza in urmatorul fel:
// Pasul 1: Definim o matrice M identica cu cea initiala M2.
// Pasul 2: Inmultim matricea M cu matricea initiala M2 si stocam rezultatul in M3.
// Pasul 3: Inlocuim Mij cu M3ij
// ...
void exponent(float *matrix2, int n, int e) {
	float* matrix = (float*)malloc(n*n * sizeof(float));
	float* matrix3 = (float*)malloc(n*n * sizeof(float));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			*(matrix + i*n + j) = *(matrix2 + i*n + j);
		}
	}
	for (int exp = 0; exp < (e - 1); exp++) {
		float element = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					element += *(matrix + i*n + k) * *(matrix2 + k*n + j);
				}
				*(matrix3 + i*n + j) = element;
				element = 0;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				*(matrix + i*n + j) = *(matrix3 + i*n + j);
			}
		}
	}
	printf("Matricea rezultanta este:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%g ", *(matrix3 + i*n + j));
		}
		printf("\n");
	}
}

/* Functie inversa. Algoritmul functioneaza in urmatorul mod:
Pasul 1: Pentru fiecare element Mij, stergem linia i si coloana j si stocam rezultatul in cofactor.
Pasul 2: Aflam determinantul matricei cofactor.
Pasul 3: Adjoint[i][j] = determinantul de la 2.
Pasul 4: Aflam transpusa matricei adjoint
Pasul 5: Pentru fiecare element al matricei inverse, I[i][j] = adjoint[i][j] / determinantul matricei initiale.
*/
void inversa(float *matrix, int n, float determinant_matrix) {
	float *cofactor = (float*)malloc((n - 1)*(n - 1) * sizeof(float));
	float *adjoint = (float*)malloc(n*n * sizeof(float));
	float *transpose = (float*)malloc(n*n * sizeof(float));
	float *inverse = (float*)malloc(n*n * sizeof(float));
	int row = 0, column = 0, a = 0, b = 0, k1 = 0, k2 = 0;
	float determinant;
	while (true) {
		// Calculare cofactor.
		k1 = 0;
		k2 = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != a && j != b) {
					*(cofactor + k1*(n - 1) + k2) = *(matrix + i*n + j);
					k2++;
				}
				if (k2 == 2) {
					k2 = 0;
					k1++;
				}
			}
		}
		// Calculare determinant cofactor.
		determinant = det(cofactor, (n - 1), 0);
		// Introducere determinant cofactor in adjoint
		if (((row + column) % 2) == 0) {
			*(adjoint + row*n + column) = determinant;
		}
		else *(adjoint + row*n + column) = -determinant;
		column++;
		if (column == n) {
			column = 0;
			row++;
		}
		b++;
		if (b == n) {
			b = 0;
			a++;
		}
		if (a == n) break;
	}
	// Aflare transpusa adjoint
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			*(transpose + j*n + i) = *(adjoint + i*n + j);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			*(inverse + i*n + j) = *(transpose + i*n + j) / determinant_matrix;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%g ", *(inverse + i*n + j));
		}
		printf("\n");
	}
}



void main() {
	char intrebare = ' ';
	while (intrebare != '1' && intrebare != '2') {
		printf("Doriti sa efectuati operatii asupra unei singure matrice(1) sau asupra a doua matrice(2)?");
		scanf("%c", &intrebare);
	}
	if (intrebare == '2') {
		int n1, c1, n2, c2;
		printf("Introduceti numarul de linii pentru prima matrice: ");
		scanf("%d", &n1);
		printf("Introduceti numarul de coloane pentru prima matrice: ");
		scanf("%d", &c1);
		printf("Introduceti numarul de linii pentru a doua matrice: ");
		scanf("%d", &n2);
		printf("Introduceti numarul de coloane pentru a doua matrice: ");
		scanf("%d", &c2);
		float *matrix1 = (float*)malloc(n1*c1 * sizeof(float));
		float *matrix2 = (float*)malloc(n2*c2 * sizeof(float));
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < c1; j++) {
				printf("Introduceti elementul %d:%d al primei matrice: ", i, j);
				scanf("%f", &*(matrix1 + i*c1 + j));
			}
		}
		for (int i = 0; i < n2; i++) {
			for (int j = 0; j < c2; j++) {
				printf("Introduceti elementul %d:%d al matricei 2: ", i, j);
				scanf("%f", &*(matrix2 + i*c2 + j));
			}
		}
		printf("Acest program poate efectua asupra a doua matrice urmatoarele operatii (introduceti numarul aferent operatiei dorite):\n1.Adunare.\n2.Scadere.\n3.Inmultire.\n");
		intrebare = ' ';
		scanf(" %c", &intrebare);
		switch (intrebare) {
		case '1':
			if (!(n1 == n2 && c1 == c2)) {
				printf("Eroare. Operatia de adunare poate fi efectuata doar asupra matricelor cu dimensiuni egale!");
				break;
			}
			else {
				adunare(matrix1, matrix2, n1, c1, 1);
				break;
			}
		case '2':
			if (!(n1 == n2 && c1 == c2)) {
				printf("Eroare. Operatia de scadere poate fi efectuata doar asupra matricelor cu dimensiuni egale!");
				break;
			}
			else {
				adunare(matrix1, matrix2, n1, c1, 0);
				break;
			}
		case '3':
			if (!(c1 == n2)) {
				printf("Eroare. Operatia de inmultire poate fi efectuata doar atunci cand numarul de coloane al primei matrice este egal cu numarul de linii al matricei 2!");
				break;
			}
			else {
				int a = n1, b = c1, c = c2;
				inmultire(matrix1, matrix2, n1, c1, c2);
				break;
			}
		}
		int h;
		scanf("%d", &h);
	}
	else {
		int n, c;
		printf("Introduceti numarul de linii:");
		scanf("%d", &n);
		printf("Introduceti numarul de coloane:");
		scanf("%d", &c);
		float* matrix = (float*)malloc(n*c * sizeof(float));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < c; j++) {
				printf("Introduceti elementul %d:%d : ", i, j);
				scanf("%f", &*(matrix + i*c + j));
			}
		}
		intrebare = ' ';
		while (intrebare != '1' && intrebare != '2' && intrebare != '3' && intrebare != '4' && intrebare != '5' && intrebare != '6') {
			printf("Acest program poate efectua asupra unei matrice urmatoarele operatii (introduceti numarul aferent operatiei dorite):\n1.Afisare spirala.\n2.Aflare determinant.\n3.Aflare transpusa.\n4.Aflare inversa.\n5.Ridicare la putere.");
			scanf(" %c", &intrebare);
		}
		switch (intrebare) {
		case '1':
			spiral(matrix, n, c);
			break;
		case '2':
			if (!(n == c)) {
				printf("Eroare. Doar matricele care au un numar de linii egal cu cel al coloanelor au determinant!");
				break;
			}
			else {
				det(matrix, n, 1);
				break;
			}
		case '3':
			transpusa(matrix, n, c);
			break;
		case '4':
			if (!(n == c)) {
				printf("Eroare. Doar matricele care au un numar de linii egal cu cel al coloanelor au inversa!.");
				break;
			}
			else {
				float determinant = det(matrix, n, 0);
				if (determinant == 0) {
					printf("Matricea nu are inversa.");
					break;
				}
				else {
					inversa(matrix, n, determinant);
					break;
				}
			}
		case '5':
			if (!(n == c)) {
				printf("Eroare. Doar matricele care au un numar de linii egal cu cel al coloanelor pot fi ridicate la o putere!");
				break;
			}
			else {
				int putere;
				printf("Introduceti o putere: ");
				scanf("%d", &putere);
				exponent(matrix, n, putere);
				break;
			}
		}
	}
}
