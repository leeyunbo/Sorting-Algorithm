#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define MAX_INDEX 150000

typedef struct genre {
	char *data;
	struct genre *link;
}genre; // �帣 �����͸� ������ ����ü 

typedef struct genreList {
	genre *head;
	genre *tail;
	int count;
}genreLists; // �帣 ��ũ�� ����Ʈ 

typedef struct movies {
	int num;
	char title[100];
	int birth;
	char genre[200];
}movies; // movies�� ���� �����͸� ������ ����ü

movies mArray[MAX_INDEX]; // merge Sort �պ��迭
movies movie[MAX_INDEX]; // movie ����ü �迭
genreLists list[MAX_INDEX]; // genreList ����ü �迭;
movies tempArray[MAX_INDEX]; // movie ����ü �迭

int index = 0; // movies ����ü �迭�� ������ ��
int readcnt = 0; // �о�� Ƚ��


void printList()
{
	int i = 0;
	for (i; i < index; i++)
	{
		
		printf("%d,%s(%d), %s\n", movie[i].num, movie[i].title, movie[i].birth, movie[i].genre);

	}
}

void add(char *str)
{
	char *pch;
	char delimeter[20] = "*-~`%^@!&()\",.:'&+?";
	int count = 0;
	char temp[200];
	int temp2;
	pch = strtok(str, delimeter); // pch�� �ʱ�ȭ�����ְ�.
	while (pch)
	{
		if (count == 0)
		{
			movie[index].num = atoi(pch);
			count++;
		}
		else if (count == 1)
		{
			strcpy(movie[index].title, pch);
			count++;
		}
		else if (count == 2)
		{
			temp2 = atoi(pch);
			if (temp2<1800) //���� �⵵�� ������ �����Ͱ� �ƴ϶�� title ���ʿ� ���δ�.
			{
				strcat(movie[index].title, pch);
			}
			else
			{
				strcpy(temp, pch);
				movie[index].birth = atoi(pch);
				count++;
			}

		}
		else
		{
			strcpy(movie[index].genre, pch);
		}

		pch = strtok(NULL, delimeter); // ���� ���ڿ����� ����

	}
	if (strncmp(temp, "19", 2) != 0 && strncmp(temp, "20", 2) != 0 && strncmp(temp, "18", 2) != 0) //���࿡ birth�� �⵵ �����Ͱ� ���ٸ� �����Ѵ�.
		index--;
	index++; // ���� ����ü�� �Ѿ.
}

void fileRead()
{
	index = 0;
	FILE *fp = fopen("C:\\movies.txt", "r");
	char str[500];
	while (fgets(str, MAX_INDEX, fp) != NULL) {
		if (readcnt == 0)
		{
			readcnt++;
			continue;
		}
		add(str);

		readcnt++;

	}

	fclose(fp);
} // ������ �о�´�.

void findNotAscii()
{
	int i, j;
	int find = 0;
	for (i = 0; i < index; i++)
	{
		for (j = 0; j < strlen(movie[i].title); j++)
		{
			if (!(65 <= movie[i].title[j] <= 122))
			{
				find = 1;
				break;
			}

		}
		if (find == 1)
		{
			for (int k = i; k < index - 1; k++)
				movie[k] = movie[k + 1];
		}
	}
}
void insertion_Sort(int index) // �⵵�� ���� ���� ����
{
	int i, j;
	movies key;
	for (i = 1; i < index; i++) {
		key = movie[i];
		j = i - 1;
		while (j >= 0 && movie[j].birth > key.birth) {
			movie[j + 1] = movie[j];
			j--;
		}
		movie[j + 1] = key;
	}
}

void double_insertion_sort(int index) // Ÿ��Ʋ�� ���� ���� ���� 
{
	int i, j;
	movies key;
	for (i = 1; i < index; i++) {
		key = movie[i];
		j = i - 1;
		while (j >= 0 && strcmp(movie[j].title, key.title) == 1) {
			movie[j + 1] = movie[j];
			j--;
		}
		movie[j + 1] = key;
	}
}

void merge_sort(int low, int mid, int high) {
	int l1, l2, i;

	for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
		if (movie[l1].birth <= movie[l2].birth) // ���� l1 �迭�� �����Ͱ� l2 �迭�� �����ͺ��� �۴ٸ�
			mArray[i] = movie[l1++]; // �պ� �迭�� l1 �迭�� �ش� �����͸� �ְ� ��ĭ �̵��ض�.
		else
			mArray[i] = movie[l2++];
	}

	while (l1 <= mid)    // ���� �պ� �迭�� ������ ���� �����Ͱ� �����ִٸ� �״�� �� �־����.
		mArray[i++] = movie[l1++];

	while (l2 <= high)
		mArray[i++] = movie[l2++];

	for (i = low; i <= high; i++)
		movie[i] = mArray[i];
}

void sort(int low, int high) { // �⵵�� ���� ���� ����
	int mid;

	if (low < high) {
		mid = (low + high) / 2; // �պ������� �߰����� ���Ѵ�.
		sort(low, mid);  // ���ȣ��, ���̻� �������� ���� �� ���� �ݺ�
		sort(mid + 1, high); // ���ȣ��
		merge_sort(low, mid, high); // ����
	}
	else
		return;

}

void double_merge_sort(int low, int mid, int high) { // Ÿ��Ʋ�� ���� ���� ����
	int l1, l2, i;

	for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
		if (strcmp(movie[l1].title, movie[l2].title) == -1 || strcmp(movie[l1].title, movie[l2].title) == 0) // ���� l1 �迭�� �����Ͱ� l2 �迭�� �����ͺ��� �۴ٸ�
			mArray[i] = movie[l1++]; // �պ� �迭�� l1 �迭�� �ش� �����͸� �ְ� ��ĭ �̵��ض�.
		else
			mArray[i] = movie[l2++];
	}

	while (l1 <= mid)    // ���� �պ� �迭�� ������ ���� �����Ͱ� �����ִٸ� �״�� �� �־����.
		mArray[i++] = movie[l1++];

	while (l2 <= high)
		mArray[i++] = movie[l2++];

	for (i = low; i <= high; i++)
		movie[i] = mArray[i];
}

void double_sort(int low, int high) {
	int mid;

	if (low < high) {
		mid = (low + high) / 2; // �պ������� �߰����� ���Ѵ�.
		double_sort(low, mid);  // ���ȣ��, ���̻� �������� ���� �� ���� �ݺ�
		double_sort(mid + 1, high); // ���ȣ��
		double_merge_sort(low, mid, high); // ����
	}
	else
		return;

}

void max_heapify(int i, int heapsize) // ���� ������ ��������� ������Ű�� ���� �Լ�
{
	movies tmp;
	int largest, l, r;
	if (i == 0)
	{
		l = (2 * i) + 1;
		r = (2 * i) + 2;
	}
	else
	{
		l = (2 * i);
		r = (2 * i) + 1;
	}
	if ((l <= heapsize) && movie[l].birth > movie[i].birth)
		largest = l;
	else
		largest = i;
	if ((r <= heapsize) && movie[r].birth > movie[largest].birth)
		largest = r;
	if (largest != i)
	{
		tmp = movie[i];
		movie[i] = movie[largest];
		movie[largest] = tmp;
		max_heapify(largest, heapsize);
	}

}
void double_max_heapify(int i, int heapsize)
{
	movies tmp;
	int largest, l, r;
	if (i == 0)
	{
		l = (2 * i) + 1;
		r = (2 * i) + 2;
	}
	else
	{
		l = (2 * i);
		r = (2 * i) + 1;
	}
	if ((l <= heapsize) && (strcmp(movie[l].title, movie[i].title) == 1))
		largest = l;
	else
		largest = i;
	if ((r <= heapsize) && (strcmp(movie[r].title, movie[largest].title) == 1))
		largest = r;
	if (largest != i)
	{
		tmp = movie[i];
		movie[i] = movie[largest];
		movie[largest] = tmp;
		double_max_heapify(largest, heapsize);
	}

}
void build_max_heap(int heapsize) // ���� ������ ���� ������ �� Ʈ���� �������, �̰� �⵵�� ���� �� Ʈ��
{
	int i;
	for (i = heapsize / 2; i >= 0; i--) //��� �����Ϳ� ���Ͽ�
	{
		max_heapify(i, heapsize);
	}
}  // max_heap ������ ������ش�.

void double_build_max_heap(int heapsize) // �̰� Ÿ��Ʋ�� ���� �� Ʈ��
{
	int i;
	for (i = heapsize / 2; i >= 0; i--) //��� �����Ϳ� ���Ͽ�
	{
		double_max_heapify(i, heapsize);
	}
}

void heap_sort(int heapsize)
{
	int i;
	movies tmp;
	clock_t st;
	clock_t et;
	st = clock();
	build_max_heap(heapsize);
	et = clock();
	printf("bulid_max_heap �ҿ� �ð� : %dclocks\n", et - st);// max_heap ������ �������
	for (i = heapsize; i > 0; i--)
	{
		tmp = movie[i]; // �� ������ ���� ���� ������
		movie[i] = movie[0]; // �� �������� ���� ���� ���� �־��ش�.
		movie[0] = tmp; // ���� ���� ��������Ƿ� �� ������ ���� ������ �÷��ش�.
		heapsize--; // ���� ���� ��������Ƿ� size--
		max_heapify(0, heapsize); //���� ������ Ʋ�������Ƿ� ���� ���� ���� max_heapify ����
	}

}

void double_heap_sort(int heapsize)
{
	int i;
	movies tmp;
	clock_t st;
	clock_t et;
	st = clock();
	double_build_max_heap(heapsize);
	et = clock();
	printf("bulid_max_heap �ҿ� �ð� : %dclocks\n", et - st);// max_heap ������ �������
	for (i = heapsize; i > 0; i--)
	{
		tmp = movie[i]; // �� ������ ���� ���� ������
		movie[i] = movie[0]; // �� �������� ���� ���� ���� �־��ش�.
		movie[0] = tmp; // ���� ���� ��������Ƿ� �� ������ ���� ������ �÷��ش�.
		heapsize--; // ���� ���� ��������Ƿ� size--
		double_max_heapify(0, heapsize); //���� ������ Ʋ�������Ƿ� ���� ���� ���� max_heapify ����
	}

}


int partition(int low, int high)
{
	movies x;
	movies temp;
	int i, j;
	x = movie[high];
	i = low - 1;
	for (j = low; j<high - 1; j++)
	{
		if (movie[j].birth <= x.birth) {
			i = i + 1;
			temp = movie[i];
			movie[i] = movie[j];
			movie[j] = temp;
		}
	}

	temp = movie[i + 1];
	movie[i + 1] = movie[high];
	movie[high] = temp;

	return i + 1;

}

void quick_sort(int low, int high) //�⵵�� ���� �� ����
{
	int q, pivot;
	if (low<high) {
		pivot = partition(low, high);
		quick_sort(low, pivot - 1);
		quick_sort(pivot + 1, high);
	}
}

int double_partition(int low, int high) // �Ǻ��� ��ġ�� ã����
{
	movies x;
	movies temp;
	int i, j;
	x = movie[high];
	i = low - 1;
	for (j = low; j<high - 1; j++)
	{
		if (strcmp(movie[j].title, x.title) == -1 || strcmp(movie[j].title, x.title) == 0) {
			i = i + 1;
			temp = movie[i];
			movie[i] = movie[j];
			movie[j] = temp;
		}
	}

	temp = movie[i + 1];
	movie[i + 1] = movie[high];
	movie[high] = temp;

	return i + 1;

}

void double_quick_sort(int low, int high) // Ÿ��Ʋ�� ���� �� ����
{
	int q, pivot;
	if (low<high) {
		pivot = double_partition(low, high);
		double_quick_sort(low, pivot - 1);
		double_quick_sort(pivot + 1, high);
	}
}




int getMax(int n) // radixsort���� �̿��ϱ� ���� �ִ� �ڸ����� ���ϴ� �Լ�
{
	int mx = movie[0].birth;
	for (int i = 1; i < n; i++)
		if (movie[i].birth > mx)
			mx = movie[i].birth;
	return mx;
}

void countSort(int n, int exp)
{
	movies *output;
	output = (movies*)malloc(n * sizeof(movies)); // ���� ��Ƶ� �迭 ����

	int i, count[10] = { 0 }; // O(N)
	for (i = 0; i < n; i++)
		count[(movie[i].birth / exp) % 10]++; // O(N)


	for (i = 1; i < 10; i++)
		count[i] += count[i - 1]; // O(K)


	for (i = n - 1; i >= 0; i--)// O(N)
	{
		output[count[(movie[i].birth / exp) % 10] - 1] = movie[i]; 
		count[(movie[i].birth / exp) % 10]--;
	}


	for (i = 0; i < n; i++)
		movie[i] = output[i];
}


void radixsort(int n)
{

	int m = getMax(n); // ���� ū ���� �����´�. ���� ū ���� �ڸ����� �̿��ؾ� �ϱ� �����̴�.


	for (int exp = 1; m / exp > 0; exp *= 10) // 1�� �ڸ����� ���� ū ���� �ڸ��� ���� �ݺ��Ѵ�.
		countSort(n, exp); // �ڸ��� ���� �����ϱ� ���� countSort�� �����Ѵ�.
}




void userInterface(int cnt) // ���� �������̽�
{
	int cmd = 0;
	int i = 0;
	int c = 0;
	int invalid = 0;
	clock_t st, et;
	clock_t et2, st2;
	if (cnt == 0)
	{
		printf("********************************************************************************************\n\n");
		printf("2014154030 ��ǻ�Ͱ��а� ������\n");
		printf("������ �ι� �����մϴ�. 0������ 4�� �߿� �ϳ��� �Է����ּ���.\n");
		printf("���Ŀ� �̿��� key�� ����� �⵵�Դϴ�.\n\n");
		printf("********************************************************************************************\n\n");
	}
	printf("������ �������ּ���(0.Insertion Sort 1.Merge Sort 2.Heap Sort 3.Quick Sort 4.Radix Sort 5.����) : ");
	scanf("%d", &cmd);
	if (cmd != 5)
	{
		printf("�����͸� ���� ��(c)�� �Է����ּ���(������ = ������ / c) : ");
		scanf("%d", &c);
	}
	printf("\n\n********************************************************************************************\n\n");

	switch (cmd) {
	case 0:
		st = clock();
		double_insertion_sort(index/c); //stable sort 
		et2 = clock();
		st2 = clock();
		insertion_Sort(index/c);
		et = clock();
		printf("ù��° �ð� : %d clocks\n", (et2 - st));
		printf("�ι�° �ð� : %d clocks\n", (et - st2));
		printf("�ɸ� �ð� : %d clocks\n", (et - st));
		break;
	case 1:
		st = clock();
		double_sort(0, index/c ); //stable sort //oK
		et2 = clock();
		st2 = clock();
		sort(0, index/c);
		et = clock();
		printf("ù��° �ð� : %d clocks\n", (et2 - st));
		printf("�ι�° �ð� : %d clocks\n", (et - st2));
		printf("�ɸ� �ð� : %d clocks\n", (et - st));
		break;
	case 2:
		st = clock();
		double_heap_sort(index/c); //unstable sort
		et2 = clock();
		st2 = clock();
		heap_sort(index/c );
		et = clock();
		printf("ù��° �ð� : %d clocks\n", (et2 - st));
		printf("�ι�° �ð� : %d clocks\n", (et - st2));
		printf("�ɸ� �ð� : %d clocks\n", (et - st));
		break;
	case 3:
		st = clock();
		double_quick_sort(0, index/c); //unstable sort
		et2 = clock();
		st2 = clock();
		quick_sort(0, index/c );
		et = clock();
		printf("ù��° �ð� : %d clocks\n", (et2 - st));
		printf("�ι�° �ð� : %d clocks\n", (et - st2));
		printf("�ɸ� �ð� : %d clocks\n", (et - st));
		break;
	case 4:
		st = clock();
		radixsort(index/c);
		et = clock();
		printf("�ɸ� �ð� : %d clocks\n", (et - st));
		break;
	case 5:
		exit(1);
		break;
	default:
		printf("1~4�� ���̸� �Է����ּ���.\n");
		invalid = 1;
		break;


	}
	if (invalid == 0)
	{
		printf("������ �Ϸ�Ǿ����ϴ�.\n\n");
	}
	printf("********************************************************************************************\n");



}

int main(void)
{
	int cnt = 0;
	while (1)
	{
		fileRead();
		findNotAscii();
		userInterface(cnt);
		printf("������ ���� : %d\n", index);
		//printList(); ������ ��� �ϱ� 
		cnt++;
	}

} // main �Լ�