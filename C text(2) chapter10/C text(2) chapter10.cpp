#include<conio.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define _1005

#define swap(type, x, y)	do { type t = x; x = y; y = t;} while(0);

#ifdef _1000
#define QNO 12
#define CNO 4

const char* jptr[] = {
	"動物", "車", "花", "家", "机", "本",
	"椅子", "父", "母", "愛", "平和", "雑誌"
};
const char* eptr[] = {
	"animal", "car", "flower", "house", "desk", "book",
	"chair", "father", "mother", "love", "peace", "magazine"
};

//10-7
int qNO;
char** JPptr;
char** ENptr;
void print_cand2(const int c[], int sw) {
	for (int i = 0; i < CNO; i++) {
		printf("(%d) %s  ", i, sw ? JPptr[c[i]] : ENptr[c[i]]);
	}
	printf(" : ");
}
int make_cand2(int c[], int n) {
	int j = 0, x = 0;
	c[0] = n;
	for (int i = 1; i < CNO; i++) {
		do {
			x = rand() % qNO;
			for (j = 0; j < i; j++) {
				if (c[j] == x) break;
			}
		} while (i != j);
		c[i] = x;
	}

	j = rand() % CNO;
	if (j != 0) swap(int, c[0], c[j]);
	return j;
}

void print_cand(const int c[], int sw) {
	for (int i = 0; i < CNO; i++) {
		printf("(%d) %s  ", i, sw ? jptr[c[i]] : eptr[c[i]]);
	}
	printf(" : ");
}
int make_cand(int c[], int n) {
	int j = 0, x = 0;
	c[0] = n;
	for (int i = 1; i < CNO; i++) {
		do {
			x = rand() % QNO;
			for (j = 0; j < i; j++) {
				if (c[j] == x) break;
			}
		} while (i != j);
		c[i] = x;
	}

	j = rand() % CNO;
	if (j != 0) swap(int, c[0], c[j]);
	return j;
}
	int read_word() {
		FILE* fp = nullptr;
		fopen_s(&fp, "WORDS", "r");
		if (fp == NULL) return 1;
		fscanf_s(fp, "%d", &qNO);
		if ((JPptr = (char**)calloc(qNO, sizeof(char*))) == NULL) return 1;
		if ((ENptr = (char**)calloc(qNO, sizeof(char*))) == NULL) return 1;
		for (int i = 0; i < qNO; i++) {
			char etemp[64]{};
			char jtemp[64]{};
			
			fscanf_s(fp, "%s%s", etemp, 64, jtemp, 64);
			if ((ENptr[i] = (char*)malloc(strlen(etemp) + 1)) == NULL) return 1;
			if ((JPptr[i] = (char*)malloc(strlen(jtemp) + 1)) == NULL) return 1;
			strcpy_s(ENptr[i], strlen(etemp) + 1, etemp);
			strcpy_s(JPptr[i], strlen(jtemp) + 1, jtemp);
		}
		fclose(fp);

		return 0;
	}

//10-1
int main_01() {
	int nq = 0, pq = 0;
	int sw = 0;
	int retry = 0;

	srand((unsigned)time(NULL));

	pq = QNO;
	do {
		do {
			nq = rand() % QNO;
		} while (nq == pq);
		sw = rand() % 2;
		printf("%s\n", sw ? eptr[nq] : jptr[nq]);
		pq = nq;
		printf("もう一度？ (0)いいえ/(1)はい : ");
		scanf_s("%d", &retry);
	} while (retry == 1);

	return 0;
}
//10-3
int main_03() {
	int nq = 0, pq = 0;
	int na = 0;
	int sw = 0;
	int retry = 0;
	int cand[CNO]{};

	srand((unsigned)time(NULL));
	pq = QNO;

	do {
		int no = 0;
		do {
			nq = rand() % QNO;
		} while (nq == pq);

		na = make_cand(cand, nq);
		sw = rand() % 2;

		printf("%sはどれですか？\n", sw ? eptr[nq] : jptr[nq]);
		do {
			print_cand(cand, sw);
			scanf_s("%d", &no);
			if (no != na) puts("\a違います。");
		} while (no != na);
		puts("正解です。");

		pq = nq;
		printf("もう一度？ (0)いいえ/(1)はい : ");
		scanf_s("%d", &retry);
	} while (retry == 1);

	return 0;
}
//10-4
int main_04() {
	char st[64]{};
	char* pt = nullptr;

	printf("文字列stを入力してください : ");
	scanf_s("%s", st, 16);
	pt = (char*)malloc(strlen(st) + 1);

	if (pt) {
		strcpy_s(pt, strlen(st) + 1, st);
		puts("その文字列の複製ptを作りました。");
		printf("st = %s\n", st);
		printf("pt = %s\n", pt);
		free(pt);
	}

	return 0;
}
//10-5
int main_05() {
	int num = 0;
	char(*p)[15] = nullptr;
	
	printf("文字列は何個 : ");
	scanf_s("%d", &num);

	p = (char(*)[15])malloc(static_cast<size_t>(num) * 15);

	if (p == NULL) puts("記憶域の確保に失敗しました。");
	else {
		int i = 0;
		for (i = 0; i < num; i++) {
			printf("p[%d] : ", i);
			scanf_s("%s", p[i], 15);
		}
		putchar('\n');
		for (i = 0; i < num; i++) {
			printf("p[%d] = %s\n", i, p[i]);
		}
		free(p);
	}

	return 0;
}
//10-6
int main_06() {
	int num = 0;
	char** pt = nullptr;

	printf("文字列は何個 : ");
	scanf_s("%d", &num);

	pt = (char**)calloc(num, sizeof(char*));

	if (pt == NULL) {
		puts("記憶域の確保に失敗しました。");
	}
	else {
		int i = 0;
		for (i = 0; i < num; i++) {
			pt[i] = NULL;
		}
		for (i = 0; i < num; i++) {
			char temp[64]{};
			printf("pt[%d] : ", i);
			scanf_s("%s", temp, 64);

			pt[i] = (char *)malloc(strlen(temp) + 1);

			if (pt[i] != NULL) strcpy_s(pt[i], strlen(temp) + 1, temp);
			else {
				puts("記憶域の確保に失敗しました。");
				goto Free;
			}
		}
		putchar('\n');
		for (i = 0; i < num; i++) {
			printf("pt[%d] = %s\n", i, pt[i]);
		}
Free:
		for (i = 0; i < num; i++) {
			free(pt[i]);
		}
		free(pt);
	}

	return 0;
}
//10-7
int main_07() {
	int nq = 0, pq = 0;
	int na = 0;
	int sw = 0;
	int retry = 0;
	int cand[CNO]{};

	if (read_word() == 1) {
		puts("\a単語ファイルの読み込みに失敗しました。");
		return 1;
	}
	srand((unsigned)time(NULL));
	pq = qNO;
	do {
		int no = 0;
		do {
			nq = rand() % qNO;
		} while (nq == pq);
		na = make_cand2(cand, nq);
		sw = rand() % 2;

		printf("%sはどれですか？\n", sw ? ENptr[nq] : JPptr[nq]);
		do {
			print_cand2(cand, sw);
			scanf_s("%d", &no);
			if (no != na) puts("違います。");
		} while (no != na);
		puts("正解です。");
		pq = nq;
		printf("もう一度？ (0)いいえ/(1)はい : ");
		scanf_s("%d", &retry);
	} while (retry == 1);

	for (int i = 0; i < qNO; i++) {
		free(ENptr[i]);
		free(JPptr[i]);
	}
	free(JPptr);
	free(ENptr);

	return 0;
}

int main(void) {
	return main_07();

	return 0;
}
#endif

#ifdef _1001
const char* month[12]{ "January", "February", "March", "April", "May", "June",
						"July", "August", "September", "October", "November", "December" };
int go(int m) {
	int re = 1;
	int c = 0;
	int n = 0;
	char buf[16]{};
	char abuf[16]{};
	strcpy_s(abuf, strlen(month[m]) + 1, month[m]);
	c = -1; 
	while (abuf[++c] != '\0') {
		abuf[c] = tolower(abuf[c]);
	}

	do {
		printf("%d月 : ", m + 1);
		scanf_s("%s", buf, 16);

		c = -1;
		while (buf[++c] != '\0') {
			buf[c] = tolower(buf[c]);
		}

		if (strcmp(buf, abuf) == 0) {
			puts("正解です。\n");
			re = 0;
		}
		else {
			if (++n == 5) {
				printf("\a%d月は%sです。\n\n", m + 1, month[m]);
				re = 0;
			}
			else {
				printf("\a違います。");
				int flag = 0;
				do {
					printf("正解を見ますか？ (0)いいえ / (1)はい : ");
					scanf_s("%d", &flag);
				} while (!(flag == 0 || flag == 1));
				if (flag == 1) {
					printf("\a%d月は%sです。\n\n", m + 1, month[m]);
					re = 0;
				}
			}
		}
	} while (re);

	if (n == 0)return 1;
	else return 0;
}
int main(void) {
	int clr = 0;
	int los = 0;
	int ans[13]{};
	int num[12]{};
	srand((unsigned)time(NULL));
	for (int i = 0; i < 12; i++) {
		int j = 0;
		int tmp = 0;
		do {
			tmp = rand() % 12;
			for (j = 0; j < i; j++) {
				if (tmp == num[j]) break;
			} 
		} while (j < i);
		num[i] = tmp;
	}

	puts("月名の英語を入力してください。\n※入力は大文字でも小文字でも構いません。");
	for (int i = 0; i < 12; i++) {
		ans[num[i]] = go(num[i]);
	}
	putchar('\n');
	for (int i = 0; i < 12; i++) if (ans[i]) clr++;
	los = 12 - clr;
	printf("12個のうち%d個が正解でした。\n", clr);
	printf("正解した月 : ");
	for (int i = 0; i < 12; i++) {
		if (ans[i]) {
			printf("%d月", i + 1);
			if (--clr) printf(", ");
		}
	}
	putchar('\n');
	printf("間違えた月 : ");
	for (int i = 0; i < 12; i++) {
		if (ans[i] == 0) {
			printf("%d月", i + 1);
			if (--los) printf(", ");
		}
	}
	putchar('\n');

	return 0;
}
#endif

#ifdef _1002
const char* day[7]{ "Sunday", "Monday", "Tuesday", "Wednesday", "Thersday", "Friday", "Satuaday" };
const char* Jday[7]{ "日曜日", "月曜日", "火曜日", "水曜日", "木曜日", "金曜日", "土曜日" };
int go(int d) {
	int re = 1;
	int c = 0;
	int n = 0;
	char buf[16]{};
	char abuf[16]{};
	strcpy_s(abuf, strlen(day[d]) + 1, day[d]);
	c = -1; 
	while (abuf[++c] != '\0') {
		abuf[c] = tolower(abuf[c]);
	}

	do {
		printf("%s : ", Jday[d]);
		scanf_s("%s", buf, 16);

		c = -1;
		while (buf[++c] != '\0') {
			buf[c] = tolower(buf[c]);
		}

		if (strcmp(buf, abuf) == 0) {
			puts("正解です。\n");
			re = 0;
		}
		else {
			if (++n == 5) {
				printf("\a%sは%sです。\n\n", Jday[d], day[d]);
				re = 0;
			}
			else {
				printf("\a違います。");
				int flag = 0;
				do {
					printf("正解を見ますか？ (0)いいえ / (1)はい : ");
					scanf_s("%d", &flag);
				} while (!(flag == 0 || flag == 1));
				if (flag == 1) {
					printf("\a%sは%sです。\n\n", Jday[d], day[d]);
					re = 0;
				}
			}
		}
	} while (re);

	if (n == 0)return 1;
	else return 0;
}
int main(void) {
	int clr = 0;
	int los = 0;
	int ans[8]{};
	int num[7]{};
	srand((unsigned)time(NULL));
	for (int i = 0; i < 7; i++) {
		int j = 0;
		int tmp = 0;
		do {
			tmp = rand() % 7;
			for (j = 0; j < i; j++) {
				if (tmp == num[j]) break;
			} 
		} while (j < i);
		num[i] = tmp;
	}

	puts("月名の英語を入力してください。\n※入力は大文字でも小文字でも構いません。");
	for (int i = 0; i < 7; i++) {
		ans[num[i]] = go(num[i]);
	}
	putchar('\n');
	for (int i = 0; i < 7; i++) if (ans[i]) clr++;
	los = 7 - clr;
	printf("7個のうち%d個が正解でした。\n", clr);
	printf("正解した曜日 : ");
	for (int i = 0; i < 7; i++) {
		if (ans[i]) {
			printf("%s", Jday[i]);
			if (--clr) printf(", ");
		}
	}
	putchar('\n');
	printf("間違えた曜日 : ");
	for (int i = 0; i < 7; i++) {
		if (ans[i] == 0) {
			printf("%s", Jday[i]);
			if (--los) printf(", ");
		}
	}
	putchar('\n');

	return 0;
}
#endif

#ifdef _1003
#define CNO 4

int qNO;
char** JPptr;
char** ENptr;
void print_cand2(const int c[], int sw) {
	for (int i = 0; i < CNO; i++) {
		printf("(%d) %s  ", i, sw ? JPptr[c[i]] : ENptr[c[i]]);
	}
	printf(" : ");
}
int make_cand2(int c[], int n) {
	int j = 0, x = 0;
	c[0] = n;
	for (int i = 1; i < CNO; i++) {
		do {
			x = rand() % qNO;
			for (j = 0; j < i; j++) {
				if (c[j] == x) break;
			}
		} while (i != j);
		c[i] = x;
	}

	j = rand() % CNO;
	if (j != 0) swap(int, c[0], c[j]);
	return j;
}
int read_word() {
	FILE* fp = nullptr;
	fopen_s(&fp, "WORDS", "r");
	if (fp == NULL) return 1;
	fscanf_s(fp, "%d", &qNO);
	if ((JPptr = (char**)calloc(qNO, sizeof(char*))) == NULL) return 1;
	if ((ENptr = (char**)calloc(qNO, sizeof(char*))) == NULL) return 1;
	for (int i = 0; i < qNO; i++) {
		char etemp[64]{};
		char jtemp[64]{};

		fscanf_s(fp, "%s%s", etemp, 64, jtemp, 64);
		if ((ENptr[i] = (char*)malloc(strlen(etemp) + 1)) == NULL) return 1;
		if ((JPptr[i] = (char*)malloc(strlen(jtemp) + 1)) == NULL) return 1;
		strcpy_s(ENptr[i], strlen(etemp) + 1, etemp);
		strcpy_s(JPptr[i], strlen(jtemp) + 1, jtemp);
	}
	fclose(fp);

	return 0;
}

int main(void) {
	int nq = 0, pq = 0;
	int na = 0;
	int sw = 0;
	int retry = 0;
	int cand[CNO]{};

	if (read_word() == 1) {
		puts("\a単語ファイルの読み込みに失敗しました。");
		goto Free;
		return 1;
	}
	srand((unsigned)time(NULL));
	pq = qNO;
	do {
		int no = 0;
		do {
			nq = rand() % qNO;
		} while (nq == pq);
		na = make_cand2(cand, nq);
		sw = rand() % 2;

		printf("%sはどれですか？\n", sw ? ENptr[nq] : JPptr[nq]);
		do {
			print_cand2(cand, sw);
			scanf_s("%d", &no);
			if (no != na) puts("違います。");
		} while (no != na);
		puts("正解です。");
		pq = nq;
		printf("もう一度？ (0)いいえ/(1)はい : ");
		scanf_s("%d", &retry);
	} while (retry == 1);

Free:
	for (int i = 0; i < qNO; i++) {
		free(ENptr[i]);
		free(JPptr[i]);
	}
	free(JPptr);
	free(ENptr);

	return 0;
}

#endif

/*
TANGO1 英単語
TANGO2 月
TANGO3 曜日
*/
#ifdef _1004
//10-7
#define CNO 3
int qNO;
char** JPptr;
char** ENptr;
char fname[16]{};
void print_cand2(const int c[], int sw) {
	for (int i = 0; i < CNO; i++) {
		printf("(%d) %s  ", i, sw ? JPptr[c[i]] : ENptr[c[i]]);
	}
	printf(" : ");
}
int make_cand2(int c[], int n) {
	int j = 0, x = 0;
	c[0] = n;
	for (int i = 1; i < CNO; i++) {
		do {
			x = rand() % qNO;
			for (j = 0; j < i; j++) {
				if (c[j] == x) break;
			}
		} while (i != j);
		c[i] = x;
	}

	j = rand() % CNO;
	if (j != 0) swap(int, c[0], c[j]);
	return j;
}
int read_word() {
	FILE* fp = nullptr;
	fopen_s(&fp, fname, "r");
	if (fp == NULL) return 1;
	fscanf_s(fp, "%d", &qNO);
	if ((JPptr = (char**)calloc(qNO, sizeof(char*))) == NULL) return 1;
	if ((ENptr = (char**)calloc(qNO, sizeof(char*))) == NULL) return 1;
	for (int i = 0; i < qNO; i++) {
		char etemp[64]{};
		char jtemp[64]{};

		fscanf_s(fp, "%s%s", etemp, 64, jtemp, 64);
		if ((ENptr[i] = (char*)malloc(strlen(etemp) + 1)) == NULL) return 1;
		if ((JPptr[i] = (char*)malloc(strlen(jtemp) + 1)) == NULL) return 1;
		strcpy_s(ENptr[i], strlen(etemp) + 1, etemp);
		strcpy_s(JPptr[i], strlen(jtemp) + 1, jtemp);
	}
	fclose(fp);

	return 0;
}

int main(int argc, char* argv[]) {
	int nq = 0, pq = 0;
	int na = 0;
	int sw = 0;
	int retry = 0;
	int cand[CNO]{};
	strcpy_s(fname, 16, argv[2]);

	if (read_word() == 1) {
		puts("\a単語ファイルの読み込みに失敗しました。");
		goto Free;
	}
	srand((unsigned)time(NULL));
	pq = qNO;
	do {
		int no = 0;
		do {
			nq = rand() % qNO;
		} while (nq == pq);
		na = make_cand2(cand, nq);
		sw = rand() % 2;

		printf("%sはどれですか？\n", sw ? ENptr[nq] : JPptr[nq]);
		do {
			print_cand2(cand, sw);
			scanf_s("%d", &no);
			if (no != na) puts("違います。");
		} while (no != na);
		puts("正解です。");
		pq = nq;
		printf("もう一度？ (0)いいえ/(1)はい : ");
		scanf_s("%d", &retry);
	} while (retry == 1);

Free:
	for (int i = 0; i < qNO; i++) {
		free(ENptr[i]);
		free(JPptr[i]);
	}
	free(JPptr);
	free(ENptr);

	return 0;

}
#endif

/*
TANGO1 英単語
TANGO2 月
TANGO3 曜日
*/
#ifdef _1005
char fname[16]{};
char** JPptr;
char** ENptr;
int* order;
int qNO;

void go(const char* ENstr, const char* JPstr) {
	printf("%s ", JPstr);
	int len = (int)strlen(ENstr);
	for (int i = 0; i < len; i++) {
		printf("%s ", &ENstr[i]);
		for (int j = -1; j < len - i; j++) printf("\b");
		fflush(stdout);
		while (_getch() != ENstr[i]);
	}
}
int read_word() {
	FILE* fp = nullptr;
	fopen_s(&fp, fname, "r");
	if (fp == NULL) return 1;
	fscanf_s(fp, "%d", &qNO);
	if ((order = (int*)calloc(qNO, sizeof(int))) == NULL) return 1;
	if ((JPptr = (char**)calloc(qNO, sizeof(char*))) == NULL) return 1;
	if ((ENptr = (char**)calloc(qNO, sizeof(char*))) == NULL) return 1;
	for (int i = 0; i < qNO; i++) {
		char etemp[64]{};
		char jtemp[64]{};

		fscanf_s(fp, "%s%s", etemp, 64, jtemp, 64);
		if ((ENptr[i] = (char*)malloc(strlen(etemp) + 1)) == NULL) return 1;
		if ((JPptr[i] = (char*)malloc(strlen(jtemp) + 1)) == NULL) return 1;
		strcpy_s(ENptr[i], strlen(etemp) + 1, etemp);
		strcpy_s(JPptr[i], strlen(jtemp) + 1, jtemp);
	}
	fclose(fp);

	return 0;
}

int main(int argc, char* argv[]) {
	strcpy_s(fname, 16, argv[2]);

	if (read_word() == 1) {
		puts("\a単語ファイルの読み込みに失敗しました。");
		goto Free;
	}
	srand((unsigned)time(NULL));
	for (int i = 0; i < qNO; i++) {
		int tmp = 0, j = 0;
		do {
			tmp = rand() % qNO;
			for (j = 0; j < i; j++) {
				if (order[j] == tmp) break;
			}
		} while (i != j);
		order[i] = tmp;
	}

	for (int i = 0; i < qNO; i++) {
		printf("残り%2d : ", qNO - i);
		go(ENptr[order[i]], JPptr[order[i]]);
		printf("\r%*s\r", (int)(strlen(ENptr[order[i]]) + strlen(JPptr[order[i]])) + 8, "");
	}

Free:
	for (int i = 0; i < qNO; i++) {
		free(ENptr[i]);
		free(JPptr[i]);
	}
	free(JPptr);
	free(ENptr);
	free(order);

	return 0;
}
#endif