#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define MAX_INDEX 150000

typedef struct genre {
	char *data;
	struct genre *link;
}genre; // 장르 데이터를 저장할 구조체 

typedef struct genreList {
	genre *head;
	genre *tail;
	int count;
}genreLists; // 장르 링크드 리스트 

typedef struct movies {
	int num;
	char title[100];
	int birth;
	char genre[200];
}movies; // movies에 대한 데이터를 저장할 구조체

movies mArray[MAX_INDEX]; // merge Sort 합병배열
movies movie[MAX_INDEX]; // movie 구조체 배열
genreLists list[MAX_INDEX]; // genreList 구조체 배열;
movies tempArray[MAX_INDEX]; // movie 구조체 배열

int index = 0; // movies 구조체 배열의 데이터 수
int readcnt = 0; // 읽어온 횟수


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
	pch = strtok(str, delimeter); // pch를 초기화시켜주고.
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
			if (temp2<1800) //만약 년도에 들어갈만한 데이터가 아니라면 title 뒤쪽에 붙인다.
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

		pch = strtok(NULL, delimeter); // 다음 문자열부터 시작

	}
	if (strncmp(temp, "19", 2) != 0 && strncmp(temp, "20", 2) != 0 && strncmp(temp, "18", 2) != 0) //만약에 birth에 년도 데이터가 없다면 삭제한다.
		index--;
	index++; // 다음 구조체로 넘어감.
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
} // 파일을 읽어온다.

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
void insertion_Sort(int index) // 년도에 대한 삽입 정렬
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

void double_insertion_sort(int index) // 타이틀에 대한 삽입 정렬 
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
		if (movie[l1].birth <= movie[l2].birth) // 만약 l1 배열의 데이터가 l2 배열의 데이터보다 작다면
			mArray[i] = movie[l1++]; // 합병 배열에 l1 배열의 해당 데이터를 넣고 한칸 이동해라.
		else
			mArray[i] = movie[l2++];
	}

	while (l1 <= mid)    // 만약 합병 배열에 들어가있지 않은 데이터가 남아있다면 그대로 다 넣어줘라.
		mArray[i++] = movie[l1++];

	while (l2 <= high)
		mArray[i++] = movie[l2++];

	for (i = low; i <= high; i++)
		movie[i] = mArray[i];
}

void sort(int low, int high) { // 년도에 대한 병합 정렬
	int mid;

	if (low < high) {
		mid = (low + high) / 2; // 합병정렬의 중간값을 구한다.
		sort(low, mid);  // 재귀호출, 더이상 나눠지지 않을 때 까지 반복
		sort(mid + 1, high); // 재귀호출
		merge_sort(low, mid, high); // 병합
	}
	else
		return;

}

void double_merge_sort(int low, int mid, int high) { // 타이틀에 대한 병합 정렬
	int l1, l2, i;

	for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
		if (strcmp(movie[l1].title, movie[l2].title) == -1 || strcmp(movie[l1].title, movie[l2].title) == 0) // 만약 l1 배열의 데이터가 l2 배열의 데이터보다 작다면
			mArray[i] = movie[l1++]; // 합병 배열에 l1 배열의 해당 데이터를 넣고 한칸 이동해라.
		else
			mArray[i] = movie[l2++];
	}

	while (l1 <= mid)    // 만약 합병 배열에 들어가있지 않은 데이터가 남아있다면 그대로 다 넣어줘라.
		mArray[i++] = movie[l1++];

	while (l2 <= high)
		mArray[i++] = movie[l2++];

	for (i = low; i <= high; i++)
		movie[i] = mArray[i];
}

void double_sort(int low, int high) {
	int mid;

	if (low < high) {
		mid = (low + high) / 2; // 합병정렬의 중간값을 구한다.
		double_sort(low, mid);  // 재귀호출, 더이상 나눠지지 않을 때 까지 반복
		double_sort(mid + 1, high); // 재귀호출
		double_merge_sort(low, mid, high); // 병합
	}
	else
		return;

}

void max_heapify(int i, int heapsize) // 힙의 구조를 계속적으로 유지시키기 위한 함수
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
void build_max_heap(int heapsize) // 선형 구조를 비선형 구조인 힙 트리로 만들어줌, 이건 년도에 대한 힙 트리
{
	int i;
	for (i = heapsize / 2; i >= 0; i--) //모든 데이터에 대하여
	{
		max_heapify(i, heapsize);
	}
}  // max_heap 구조를 만들어준다.

void double_build_max_heap(int heapsize) // 이건 타이틀에 대한 힙 트리
{
	int i;
	for (i = heapsize / 2; i >= 0; i--) //모든 데이터에 대하여
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
	printf("bulid_max_heap 소요 시간 : %dclocks\n", et - st);// max_heap 구조로 만들어줌
	for (i = heapsize; i > 0; i--)
	{
		tmp = movie[i]; // 맨 마지막 값을 따로 빼놓고
		movie[i] = movie[0]; // 맨 마지막에 가장 맨위 값을 넣어준다.
		movie[0] = tmp; // 맨위 값은 사라졌으므로 맨 마지막 값을 맨위로 올려준다.
		heapsize--; // 맨위 값이 사라졌으므로 size--
		max_heapify(0, heapsize); //가장 맨위가 틀어졌으므로 맨위 값에 대해 max_heapify 수행
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
	printf("bulid_max_heap 소요 시간 : %dclocks\n", et - st);// max_heap 구조로 만들어줌
	for (i = heapsize; i > 0; i--)
	{
		tmp = movie[i]; // 맨 마지막 값을 따로 빼놓고
		movie[i] = movie[0]; // 맨 마지막에 가장 맨위 값을 넣어준다.
		movie[0] = tmp; // 맨위 값은 사라졌으므로 맨 마지막 값을 맨위로 올려준다.
		heapsize--; // 맨위 값이 사라졌으므로 size--
		double_max_heapify(0, heapsize); //가장 맨위가 틀어졌으므로 맨위 값에 대해 max_heapify 수행
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

void quick_sort(int low, int high) //년도에 대한 퀵 정렬
{
	int q, pivot;
	if (low<high) {
		pivot = partition(low, high);
		quick_sort(low, pivot - 1);
		quick_sort(pivot + 1, high);
	}
}

int double_partition(int low, int high) // 피봇의 위치를 찾아줌
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

void double_quick_sort(int low, int high) // 타이틀에 대한 힙 정렬
{
	int q, pivot;
	if (low<high) {
		pivot = double_partition(low, high);
		double_quick_sort(low, pivot - 1);
		double_quick_sort(pivot + 1, high);
	}
}




int getMax(int n) // radixsort에서 이용하기 위한 최대 자릿수를 구하는 함수
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
	output = (movies*)malloc(n * sizeof(movies)); // 따로 담아둘 배열 선언

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

	int m = getMax(n); // 가장 큰 값을 가져온다. 가장 큰 값의 자릿수를 이용해야 하기 때문이다.


	for (int exp = 1; m / exp > 0; exp *= 10) // 1의 자리부터 가장 큰 값의 자릿수 까지 반복한다.
		countSort(n, exp); // 자릿수 별로 정렬하기 위해 countSort를 수행한다.
}




void userInterface(int cnt) // 유저 인터페이스
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
		printf("2014154030 컴퓨터공학과 이윤복\n");
		printf("정렬을 두번 수행합니다. 0번부터 4번 중에 하나를 입력해주세요.\n");
		printf("정렬에 이용할 key는 제목과 년도입니다.\n\n");
		printf("********************************************************************************************\n\n");
	}
	printf("정렬을 선택해주세요(0.Insertion Sort 1.Merge Sort 2.Heap Sort 3.Quick Sort 4.Radix Sort 5.종료) : ");
	scanf("%d", &cmd);
	if (cmd != 5)
	{
		printf("데이터를 나눌 수(c)를 입력해주세요(데이터 = 데이터 / c) : ");
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
		printf("첫번째 시간 : %d clocks\n", (et2 - st));
		printf("두번째 시간 : %d clocks\n", (et - st2));
		printf("걸린 시간 : %d clocks\n", (et - st));
		break;
	case 1:
		st = clock();
		double_sort(0, index/c ); //stable sort //oK
		et2 = clock();
		st2 = clock();
		sort(0, index/c);
		et = clock();
		printf("첫번째 시간 : %d clocks\n", (et2 - st));
		printf("두번째 시간 : %d clocks\n", (et - st2));
		printf("걸린 시간 : %d clocks\n", (et - st));
		break;
	case 2:
		st = clock();
		double_heap_sort(index/c); //unstable sort
		et2 = clock();
		st2 = clock();
		heap_sort(index/c );
		et = clock();
		printf("첫번째 시간 : %d clocks\n", (et2 - st));
		printf("두번째 시간 : %d clocks\n", (et - st2));
		printf("걸린 시간 : %d clocks\n", (et - st));
		break;
	case 3:
		st = clock();
		double_quick_sort(0, index/c); //unstable sort
		et2 = clock();
		st2 = clock();
		quick_sort(0, index/c );
		et = clock();
		printf("첫번째 시간 : %d clocks\n", (et2 - st));
		printf("두번째 시간 : %d clocks\n", (et - st2));
		printf("걸린 시간 : %d clocks\n", (et - st));
		break;
	case 4:
		st = clock();
		radixsort(index/c);
		et = clock();
		printf("걸린 시간 : %d clocks\n", (et - st));
		break;
	case 5:
		exit(1);
		break;
	default:
		printf("1~4번 사이를 입력해주세요.\n");
		invalid = 1;
		break;


	}
	if (invalid == 0)
	{
		printf("정렬이 완료되었습니다.\n\n");
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
		printf("데이터 갯수 : %d\n", index);
		//printList(); 데이터 출력 하기 
		cnt++;
	}

} // main 함수