#include <stdlib.h>
#include <stdio.h>
#include <conio.h>


void afisare_mat(float *matrix, int r, int c) {
	for (int p = 0; p < r*c; p++) {
		if (p == 0) goto print;
		else if (p % c == 0) printf("\n");
	print:
		printf("%g ", *(matrix + (p / c) * c + (p % c)));
	}
	printf("\n");
}



void adunare(float *matrix1, float *matrix2, int rows, int columns, int selectie) {
	float* matrix3 = (float*)malloc(rows*columns * sizeof(float));
	
	for (int i = 0; i < rows*columns; i++) {
		if (selectie == 1) *(matrix3 + (i / columns)*columns + (i%columns)) = *(matrix1 + (i / columns)*columns + (i%columns)) + *(matrix2 + (i / columns)*columns + (i%columns));
		else *(matrix3 + (i / columns)*columns + (i%columns)) = *(matrix1 + (i / columns)*columns + (i%columns)) - *(matrix2 + (i / columns)*columns + (i%columns));
	}
	afisare_mat(matrix3, rows, columns);
}


void inmultire(float *matrix1, float *matrix2, int r, int rc, int c) {
	float* matrix3 = (float*)malloc(r*c * sizeof(float));
	
	for (int p = 0; p < r*c; p++) {		// De p ne folosim pentru a accesa pozitiile matricei3.
		*(matrix3 + (p / c)*c + (p%c)) = 0; 
		for (int k = 0; k < rc; k++) {  // De k ne folosim pentru a itera pe coloanele matricei1 si liniile matricei2
			*(matrix3 + (p / c)*c + (p%c)) += *(matrix1 + (p / rc)*rc + k) * *(matrix2 + k*c + (p%c));
		}
	}
	afisare_mat(matrix3, r, c);
}


int exponent(float *matrix2, int n, int e) {
	
	// Functie exponent. Algoritmul functioneaza in urmatorul fel:
	// Pasul 1: Definim o matrice M identica cu cea initiala M2.
	// Pasul 2: Inmultim matricea M cu matricea initiala M2 si stocam rezultatul in M3.
	// Pasul 3: Inlocuim Mij cu M3ij
	// ...
	// Daca exponentul este 0, rezultatul este matricea identitate.
	
	if (e == 0) {
		for (int i = 0; i < n*n; i++) {
			if (i%n == 0) printf("\n");
			if ((i / n) == (i%n)) printf("%d", 1);
			else printf("%d", 0);
		}
		return 0;
	}
	else {
		// Verificam daca toate elementele matricei sunt 0. Daca sunt, afisam matricea zero.
		for (int i = 0, verificare_m0 = 0; i < n*n; i++) {
			if (*(matrix2 + (i / n)*n + (i%n))) break;
			if (i == (n*n)-1) {
				for (int j = 0; j < n*n; j++) {
					if (j%n == 0) printf("\n");
					printf("%d", 0);
					if (j == (n*n)-1) return 0;
				}
			}
		}
		float* matrix = (float*)malloc(n*n * sizeof(float));
		float* matrix3 = (float*)malloc(n*n * sizeof(float));
		for (int i = 0; i < n*n; i++) *(matrix + (i / n)*n + (i%n)) = *(matrix2 + (i / n)*n + (i%n));
		for (int exp = 0; exp < (e - 1); exp++) {
			for (int i = 0; i < n*n; i++) {
				*(matrix3 + (i / n)*n + (i%n)) = 0;
				for (int k = 0; k < n; k++) *(matrix3 + (i / n)*n + (i%n)) += *(matrix + (i / n)*n + k) * *(matrix2 + k*n + (i%n));
			}
			for (int i = 0; i < n*n; i++) *(matrix + (i / n)*n + (i%n)) = *(matrix3 + (i / n)*n + (i%n));
		}
		afisare_mat(matrix3, n, n);
		return 0;
	}
}


int spiral(float mat[], int linii, int coloane) {
	
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

void transpusa(float *matrix, int n, int c) {
	float *matrix2 = (float*)malloc(n*c * sizeof(float));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < c; j++) {
			*(matrix2 + j*n + i) = *(matrix + i*c + j);
		}
	}
	afisare_mat(matrix2, c, n);
}

float det(float *mat, int n, int afisare) {
	
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

void inversa(float *matrix, int n, float determinant_matrix) {
	
	/* Functie inversa. Algoritmul functioneaza in urmatorul mod:
	Pasul 1: Pentru fiecare element Mij, stergem linia i si coloana j si stocam rezultatul in cofactor.
	Pasul 2: Aflam determinantul matricei cofactor.
	Pasul 3: Adjoint[i][j] = determinantul de la 2.
	Pasul 4: Aflam transpusa matricei adjoint
	Pasul 5: Pentru fiecare element al matricei inverse, I[i][j] = adjoint[i][j] / determinantul matricei initiale.
	*/
	
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


int main() {
	int operatie;
	printf("Operatiile pe care acest program le poate efectua sunt:\n1.Adunare.\n2.Scadere.\n3.Inmultire.\n4.Ridicare la putere.\n5.Afisare in spirala.\n6.Aflare transpusa.\n7.Aflare determinant.\n8.Aflare inversa.\nIntroduceti numarul operatiei dorite: ");
	scanf("%d", &operatie);
	while (operatie != 1 && operatie != 2 && operatie != 3 && operatie != 4 && operatie != 5 && operatie != 6 && operatie != 7 && operatie != 8) {
		printf("Numar incorect. Introduceti numarul operatiei dorite: ");
		scanf("%d", &operatie);
	}
	if (operatie == 1 || operatie == 2 || operatie == 3) {
		int r1, c1, r2, c2;
		printf("Introduceti numarul de linii pentru M1: ");
		scanf("%d", &r1);
		printf("Introduceti numarul de coloane pentru M1: ");
		scanf("%d", &c1);
		printf("Introduceti numarul de linii pentru M2: ");
		scanf("%d", &r2);
		printf("Introduceti numarul de coloane pentru M2: ");
		scanf("%d", &c2);
		if (operatie == 1 || operatie == 2) {
			if (!(r1 == r2 && c1 == c2)) {
				printf("Pentru a putea aduna sau scadea doua matrici, acestea trebuie sa aiba acelasi numar de linii si coloane!.\n");
				printf("Introduceti numarul de linii pentru M1: ");
				scanf("%d", &r1);
				printf("Introduceti numarul de coloane pentru M1: ");
				scanf("%d", &c1);
				printf("Introduceti numarul de linii pentru M2: ");
				scanf("%d", &r2);
				printf("Introduceti numarul de coloane pentru M2: ");
				scanf("%d", &c2);
			}
		}
		if (operatie == 3) {
			if (!(c1 == r2)) {
				printf("Pentru a putea inmulti doua matrici, numarul de coloane pentru M1 trebuie sa fie egal cu numarul de linii pentru M2!.\n");
				printf("Introduceti numarul de linii pentru M1: ");
				scanf("%d", &r1);
				printf("Introduceti numarul de coloane pentru M1 si numarul de linii pentru M2: ");
				scanf("%d", &c1);
				printf("Introduceti numarul de coloane pentru M2: ");
				scanf("%d", &c2);
			}
		}
		float *matrix1 = (float*)malloc(r1*c1 * sizeof(float));
		float *matrix2 = (float*)malloc(r2*c2 * sizeof(float));
		for (int p = 0; p < r1 * c1; p++) {
			printf("Introduceti elementul %d:%d pentru M1: ", p / c1, p%c1);
			scanf("%f", &*(matrix1 + (p / c1)*c1 + (p%c1)));
		}
		for (int p = 0; p < r2 * c2; p++) {
			printf("Introduceti elementul %d:%d pentru M2: ", p / c2, p%c2);
			scanf("%f", &*(matrix2 + (p / c2)*c2 + (p%c2)));
		}
		switch (operatie) {
		case 1 :
			printf("Matricea rezultanta in urma operatiei de adunare este:\n");
			adunare(matrix1, matrix2, r1, c1, 1);
			break;
		case 2:
			printf("Matricea rezultanta in urma operatiei de scadere este:\n");
			adunare(matrix1, matrix2, r1, c1, 0);
			break;
		case 3:
			printf("Matricea rezultanta in urma operatiei de inmultire este:\n");
			inmultire(matrix1, matrix2, r1, c1, c2);
			break;
		}
	}
	else {
		int r, c;
		printf("Introduceti numarul de linii: ");
		scanf("%d", &r);
		printf("Introduceti numarul de coloane: ");
		scanf("%d", &c);
		float *matrix = (float*)malloc(r*c * sizeof(float));
		for (int p = 0; p < r * c; p++) {
			printf("Introduceti elementul %d:%d: ", p / c, p%c);
			scanf("%f", &*(matrix + (p / c)*c + (p%c)));
		}
		switch (operatie) {
		case 4:
			while (!(r == c)) {
				printf("Doar matricele care au un numar egal de linii si coloane pot fi ridicate la putere!\nIntroduceti numarul de linii si coloane: ");
				scanf("%d", &r);
			}
			int exp;
			printf("Introduceti exponentul: ");
			scanf("%d", &exp);
			printf("Matricea obtinuta in urma ridicarii la putere este:\n");
			exponent(matrix, r, exp);
			break;
		case 5:
			printf("Matricea afisata in spirala este: ");
			spiral(matrix, r, c);
			break;
		case 6:
			printf("Matricea transpusa este:\n");
			transpusa(matrix, r, c);
			break;
		case 7:
			while (!(r == c)) {
				printf("Numarul de linii trebuie sa fie egal cu numarul de coloane!\nIntroduceti numarul de linii si coloane: ");
				scanf("%d", r);
			}
			det(matrix, r, 1);
			break;
		case 8:
			while (!(r == c)) {
				printf("Numarul de linii trebuie sa fie egal cu numarul de coloane!\nIntroduceti numarul de linii si coloane: ");
				scanf("%d", r);
			}
			int determinant = det(matrix, r, 0);
			if (determinant == 0) printf("Matricea nu are inversa!");
			else inversa(matrix, r, determinant);
			break;
		}
	}
	_getch();
	return 0;
}
