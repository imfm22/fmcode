// 407. Trapping Rain Water II
// https://leetcode-cn.com/problems/trapping-rain-water-ii/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Solution
#ifdef max
#undef max
#endif

#define max(a, b) ((a) > (b)) ? a : b

typedef struct voxel
{
    int m;
    int n;
    int height;
    struct voxel *next;
} Voxel;

Voxel *createVoxel(int m, int n, int height);
void insertVoxel(Voxel **wallptr, Voxel *v);
Voxel *popVoxel(Voxel **wallptr);

int trapRainWater(int **heightMap, int heightMapSize, int *heightMapColSize)
{
    int m = heightMapSize;
    int n = *heightMapColSize;
    if (heightMap == NULL || m <= 2 || n <= 2)
        return 0;

    int bound[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int checked[m][n];
    memset(checked, 0, m * n * sizeof(int));
    int volume = 0;

    Voxel *wall = NULL;
    for (int i = 0; i < m; ++i)
    {
        checked[i][0] = 1;
        insertVoxel(&wall, createVoxel(i, 0, heightMap[i][0]));
        checked[i][n - 1] = 1;
        insertVoxel(&wall, createVoxel(i, n - 1, heightMap[i][n - 1]));
    }
    for (int j = 1; j < n - 1; ++j)
    {
        checked[0][j] = 1;
        insertVoxel(&wall, createVoxel(0, j, heightMap[0][j]));
        checked[m - 1][j] = 1;
        insertVoxel(&wall, createVoxel(m - 1, j, heightMap[m - 1][j]));
    }

    while (wall)
    {
        Voxel *cur = popVoxel(&wall);
        for (int i = 0; i < 4; ++i)
        {
            int r = cur->m + bound[i][0];
            int c = cur->n + bound[i][1];
            if (r < 0 || r >= m || c < 0 || c >= n || checked[r][c])
                continue;

            int height = heightMap[r][c];
            volume += max(0, cur->height - height);
            int boundHeight = max(cur->height, height);
            insertVoxel(&wall, createVoxel(r, c, boundHeight));
            checked[r][c] = 1;
        }
        free(cur);
    }

    return volume;
}

void insertVoxel(Voxel **wallptr, Voxel *v)
{
    if (*wallptr == NULL)
    {
        *wallptr = v;
        return;
    }

    Voxel *cur = *wallptr;

    if (cur->height > v->height)
    {
        v->next = cur;
        *wallptr = v;
        return;
    }

    do
    {
        if (cur->next && cur->next->height > v->height)
        {
            v->next = cur->next;
            cur->next = v;
            break;
        }
        else if (!cur->next)
        {
            cur->next = v;
            break;
        }
    } while ((cur = cur->next));
}

Voxel *popVoxel(Voxel **wallptr)
{
    Voxel *tmp = *wallptr;
    *wallptr = (*wallptr)->next;
    return tmp;
}

Voxel *createVoxel(int m, int n, int height)
{
    Voxel *v = (Voxel *)malloc(sizeof(Voxel));
    v->m = m;
    v->n = n;
    v->height = height;
    v->next = NULL;
    return v;
}

/**************************************************/
/********************** test **********************/
/**************************************************/

int **arrFromStr(char *str, int *m, int *n);
void free2DArr(int **arr, int m, int n);
void print2DArr(int **arr, int m, int n);

int main()
{
    int m, n;
    int **arr;
    int vol = 0;

    // Example 1
    printf("==> First Example:\n");
    arr = arrFromStr("[[5,5,5,1],[5,1,1,5],[5,1,5,5],[5,2,5,8]]", &m, &n);
    print2DArr(arr, m, n);

    vol = trapRainWater(arr, m, &n);
    printf("Trapped rain water is: %d\n", vol);
    free2DArr(arr, m, n);
    assert(vol == 3);

    // Example 2
    printf("\n==> Second Example:\n");
    arr = arrFromStr("[[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]", &m, &n);
    print2DArr(arr, m, n);

    vol = trapRainWater(arr, m, &n);
    printf("Trapped rain water is: %d\n", vol);
    free2DArr(arr, m, n);
    assert(vol == 4);

    return 0;
}

int **arrFromStr(char *str, int *m, int *n)
{
    int rows = 0, cols = 0;
    int len = strlen(str);
    int ch;
    char *ptr = str;
    while ((ch = *ptr++))
    {
        if (ch == '[')
            ++rows;
        else if (ch == ',')
            ++cols;
    }

    *m = rows - 1;
    *n = cols / *m + 1;

    int **arr = (int **)malloc(*m * sizeof(int *));
    for (int i = 0; i < *m; ++i)
    {
        arr[i] = (int *)malloc(*n * sizeof(int));
    }

    ptr = str;
    for (int r = 0; r < *m; ++r)
    {
        for (int c = 0; c < *n; ++c)
        {
            int ele = 0;
            while ((ch = *ptr++))
            {
                if (isdigit(ch))
                {
                    ele = ch - '0';
                    break;
                }
            }
            while ((ch = *ptr++))
            {
                if (isdigit(ch))
                    ele = ele * 10 + (ch - '0');
                else
                    break;
            }
            arr[r][c] = ele;
        }
    }

    return arr;
}

void free2DArr(int **arr, int m, int n)
{
    for (int i = 0; i < m; ++i)
    {
        if (arr[i])
            free(arr[i]);
    }
    free(arr);
}

void print2DArr(int **arr, int m, int n)
{
    printf("The Array is: [\n");
    for (int i = 0; i < m; ++i)
    {
        putchar('[');
        for (int j = 0; j < n; ++j)
        {
            printf("%4d ", arr[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
}
