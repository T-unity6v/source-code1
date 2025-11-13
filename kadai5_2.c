#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define ll long long int

// 配列とそれぞれの回数をリセットする関数
void array_reset(int *x, int *y, int *z, int *A, int n, ll *cmp, ll *cng)
{
    *cmp = 0;
    *cng = 0;
    for (int i = 0; i < n; i++)
    {
        x[i] = i + 1;
        y[i] = n - i;
        z[i] = A[i];
    }
}

void fisher_yates_shuffle(int *A, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;
    }
}

// 与えられた値をswapする関数
void swap(int *x, int *y)
{
    int a = *x;
    *x = *y;
    *y = a;
}

// バブルソート（通常版）
void bubbleSort_basic(int A[], int n, ll *cmp, ll *cng)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(&A[j], &A[j + 1]);
                *cng += 3;
            }
            *cmp += 1;
        }
    }
}

// バブルソート（改良版）
void bubbleSort_optimized(int A[], int n, ll *cmp, ll *cng)
{
    // 交換が行われたかを判別する変数
    bool flag = false;

    for (int i = 0; i < n - 1; i++)
    {
        flag = false;
        for (int j = 0; j < n - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(&A[j], &A[j + 1]);
                flag = true;
                *cng += 3;
            }
            *cmp += 1;
        }
        // もし一度も交換が行わなければ終了
        if (!flag)
        {
            return;
        }
        *cmp += 1;
    }
}

// 選択ソート
void selectionSort(int A[], int n, ll *cmp, ll *cng)
{
    // 最小値をメモする変数
    int MIN = 0;
    // 最小値が格納されている配列番号をメモする変数
    int num = 0;
    for (int i = 0; i < n - 1; i++)
    {
        MIN = A[i];
        num = i;
        for (int j = i + 1; j < n; j++)
        {
            if (MIN > A[j])
            {
                MIN = A[j];
                num = j;
            }
            *cmp += 1;
        }
        A[num] = A[i];
        A[i] = MIN;
        *cng += 2;
    }
}

// 挿入ソート
void insertionSort(int A[], int n, ll *cmp, ll *cng)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (A[j - 1] > A[j])
            {
                swap(&A[j], &A[j - 1]);
                *cng += 3;
            }
            *cmp += 1;
        }
    }
}

// 分割された部分列をソートする関数
void merge(int A[], int left, int mid, int right, ll *cmp, ll *cng)
{
    // 左右の配列のサイズを表す変数
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 配列をコピー
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = A[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = A[mid + 1 + i];

    *cng += n1 + n2;

    // 2つの配列をソートしながら結合
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
        k++;
        *cmp += 1;
        *cng += 1;
    }

    // Aの配列に移す
    while (i < n1)
    {
        A[k] = L[i];
        i++;
        k++;
        *cng += 1;
    }

    while (j < n2)
    {
        A[k] = R[j];
        j++;
        k++;
        *cng += 1;
    }
}

// マージソート
void mergeSort(int A[], int left, int right, ll *cmp, ll *cng)
{
    // 要素数が1になるとreturn
    if (left >= right)
        return;
    *cmp += 1;

    int mid;
    mid = (left + right) / 2;

    mergeSort(A, left, mid, cmp, cng);
    mergeSort(A, mid + 1, right, cmp, cng);

    // 結合する
    merge(A, left, mid, right, cmp, cng);
}

// 基準との大小関係で2分割する関数
int partition(int A[], int left, int right, ll *cmp, ll *cng)
{
    // ピボットを右端に仮置き
    int k = (left + right) / 2;
    swap(&A[k], &A[right]);
    *cng += 3;

    int i = left;
    int j = right - 1;

    // 左側がピボット以下、右側がピボット以上になるように分割
    while (i <= j)
    {
        while (A[i] < A[right])
            i++;
        while ((A[j] >= A[right]) && (j >= i))
            j--;
        if (i < j)
        {
            swap(&A[i], &A[j]);
            *cng += 3;
            *cmp += 1;
        }
    }

    // ピボットを適切な位置に配置
    swap(&A[i], &A[right]);
    return i;
}

// クイックソート
void quickSort(int A[], int left, int right, ll *cmp, ll *cng)
{
    if (left < right)
    {
        *cmp += 1;
        int pivot_index = partition(A, left, right, cmp, cng);

        quickSort(A, left, pivot_index - 1, cmp, cng);
        quickSort(A, pivot_index + 1, right, cmp, cng);
    }
}

// 最大ヒープ構造に変換する関数
void heapify(int A[], int n, int i, ll *cmp, ll *cng)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i)
    {
        *cng += 3;
        swap(&A[i], &A[largest]);
        heapify(A, n, largest, cmp, cng);
    }
    *cmp += 3;
}

// heapifyを繰り返す関数
void buildHeap(int A[], int n, ll *cmp, ll *cng)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(A, n, i, cmp, cng);
    }
}

// ヒープソート
void heapSort(int A[], int n, ll *cmp, ll *cng)
{
    buildHeap(A, n, cmp, cng);

    for (int i = n - 1; i > 0; i--)
    {
        *cng += 3;
        swap(&A[0], &A[i]);
        heapify(A, i, 0, cmp, cng);
    }
}

void fprintf_bubbleSort_basic(int x[], int y[], int z[], int A[], int n, FILE *fp)
{
    ll cmp = 0, cng = 0;
    // 配列をリセットする
    array_reset(x, y, z, A, n, &cmp, &cng);
    bubbleSort_basic(x, n, &cmp, &cng);
    fprintf(fp, "バブルソート（打ち切りなし）,昇順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    bubbleSort_basic(y, n, &cmp, &cng);
    fprintf(fp, "降順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    bubbleSort_basic(z, n, &cmp, &cng);
    fprintf(fp, "ランダム,%d,%d,%d, ,\n", n, cmp, cng);
}

void fprintf_bubbleSort_optimized(int x[], int y[], int z[], int A[], int n, FILE *fp)
{
    ll cmp = 0, cng = 0;
    // 配列をリセットする
    array_reset(x, y, z, A, n, &cmp, &cng);
    bubbleSort_optimized(x, n, &cmp, &cng);
    fprintf(fp, "バブルソート（打ち切りあり）,昇順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    bubbleSort_optimized(y, n, &cmp, &cng);
    fprintf(fp, "降順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    bubbleSort_optimized(z, n, &cmp, &cng);
    fprintf(fp, "ランダム,%d,%d,%d, ,\n", n, cmp, cng);
}

void fprintf_selectionSort(int x[], int y[], int z[], int A[], int n, FILE *fp)
{
    ll cmp = 0, cng = 0;
    // 配列をリセットする
    array_reset(x, y, z, A, n, &cmp, &cng);
    selectionSort(x, n, &cmp, &cng);
    fprintf(fp, "選択ソート,昇順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    selectionSort(y, n, &cmp, &cng);
    fprintf(fp, "降順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    selectionSort(z, n, &cmp, &cng);
    fprintf(fp, "ランダム,%d,%d,%d, ,\n", n, cmp, cng);
}

void fprintf_insertionSort(int x[], int y[], int z[], int A[], int n, FILE *fp)
{
    ll cmp = 0, cng = 0;
    // 配列をリセットする
    array_reset(x, y, z, A, n, &cmp, &cng);
    insertionSort(x, n, &cmp, &cng);
    fprintf(fp, "挿入ソート,昇順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    insertionSort(y, n, &cmp, &cng);
    fprintf(fp, "降順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    insertionSort(z, n, &cmp, &cng);
    fprintf(fp, "ランダム,%d,%d,%d, ,\n", n, cmp, cng);
}

void fprintf_mergeSort(int x[], int y[], int z[], int A[], int n, FILE *fp)
{
    ll cmp = 0, cng = 0;
    // 配列をリセットする
    array_reset(x, y, z, A, n, &cmp, &cng);
    mergeSort(x, 0, n - 1, &cmp, &cng);
    fprintf(fp, "マージソート,昇順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    mergeSort(y, 0, n - 1, &cmp, &cng);
    fprintf(fp, "降順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    mergeSort(z, 0, n - 1, &cmp, &cng);
    fprintf(fp, "ランダム,%d,%d,%d, ,\n", n, cmp, cng);
}

void fprintf_quickSort(int x[], int y[], int z[], int A[], int n, FILE *fp)
{
    ll cmp = 0, cng = 0;
    // 配列をリセットする
    array_reset(x, y, z, A, n, &cmp, &cng);
    quickSort(x, 0, n - 1, &cmp, &cng);
    fprintf(fp, "クイックソート,昇順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    quickSort(y, 0, n - 1, &cmp, &cng);
    fprintf(fp, "降順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    quickSort(z, 0, n - 1, &cmp, &cng);
    fprintf(fp, "ランダム,%d,%d,%d, ,\n", n, cmp, cng);
}

void fprintf_heapSort(int x[], int y[], int z[], int A[], int n, FILE *fp)
{
    ll cmp = 0, cng = 0;
    // 配列をリセットする
    array_reset(x, y, z, A, n, &cmp, &cng);
    heapSort(x, n, &cmp, &cng);
    fprintf(fp, "ヒープソート,昇順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    heapSort(y, n, &cmp, &cng);
    fprintf(fp, "降順,%d,%d,%d, ,", n, cmp, cng);
    array_reset(x, y, z, A, n, &cmp, &cng);
    heapSort(z, n, &cmp, &cng);
    fprintf(fp, "ランダム,%d,%d,%d, ,\n", n, cmp, cng);
}

int main(void)
{
    int n1 = 10;
    int n2 = 100;
    int n3 = 1000;
    int n4 = 10000;
    // 昇順：x , 降順：y , ランダム：z
    int x1[n1], y1[n1], z1[n1], A1[n1];
    int x2[n2], y2[n2], z2[n2], A2[n2];
    int x3[n3], y3[n3], z3[n3], A3[n3];
    int x4[n4], y4[n4], z4[n4], A4[n4];

    for (int i = 0; i < n1; i++)
        A1[i] = i + 1;
    for (int i = 0; i < n2; i++)
        A2[i] = i + 1;
    for (int i = 0; i < n3; i++)
        A3[i] = i + 1;
    for (int i = 0; i < n4; i++)
        A4[i] = i + 1;

    // 配列をランダムに並べ替える
    srand(0);
    fisher_yates_shuffle(A1, n1);
    fisher_yates_shuffle(A2, n2);
    fisher_yates_shuffle(A3, n3);
    fisher_yates_shuffle(A4, n4);

    FILE *fp;
    fp = fopen("results.csv", "w");
    if (fp == NULL)
    {
        printf("ファイルが開けません\n");
        return -1;
    }

    fprintf(fp, "アルゴリズム,並び方,データ数,比較回数,交換・代入回数\n");

    fprintf_bubbleSort_basic(x1, y1, z1, A1, n1, fp);
    fprintf_bubbleSort_basic(x2, y2, z2, A2, n2, fp);
    fprintf_bubbleSort_basic(x3, y3, z3, A3, n3, fp);
    fprintf_bubbleSort_basic(x4, y4, z4, A4, n4, fp);

    fprintf_bubbleSort_optimized(x1, y1, z1, A1, n1, fp);
    fprintf_bubbleSort_optimized(x2, y2, z2, A2, n2, fp);
    fprintf_bubbleSort_optimized(x3, y3, z3, A3, n3, fp);
    fprintf_bubbleSort_optimized(x4, y4, z4, A4, n4, fp);

    fprintf_selectionSort(x1, y1, z1, A1, n1, fp);
    fprintf_selectionSort(x2, y2, z2, A2, n2, fp);
    fprintf_selectionSort(x3, y3, z3, A3, n3, fp);
    fprintf_selectionSort(x4, y4, z4, A4, n4, fp);

    fprintf_insertionSort(x1, y1, z1, A1, n1, fp);
    fprintf_insertionSort(x2, y2, z2, A2, n2, fp);
    fprintf_insertionSort(x3, y3, z3, A3, n3, fp);
    fprintf_insertionSort(x4, y4, z4, A4, n4, fp);

    fprintf_mergeSort(x1, y1, z1, A1, n1, fp);
    fprintf_mergeSort(x2, y2, z2, A2, n2, fp);
    fprintf_mergeSort(x3, y3, z3, A3, n3, fp);
    fprintf_mergeSort(x4, y4, z4, A4, n4, fp);

    fprintf_quickSort(x1, y1, z1, A1, n1, fp);
    fprintf_quickSort(x2, y2, z2, A2, n2, fp);
    fprintf_quickSort(x3, y3, z3, A3, n3, fp);
    fprintf_quickSort(x4, y4, z4, A4, n4, fp);

    fprintf_heapSort(x1, y1, z1, A1, n1, fp);
    fprintf_heapSort(x2, y2, z2, A2, n2, fp);
    fprintf_heapSort(x3, y3, z3, A3, n3, fp);
    fprintf_heapSort(x4, y4, z4, A4, n4, fp);

    fclose(fp);
}
