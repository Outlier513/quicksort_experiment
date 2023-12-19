#include <iostream>
#include <chrono>
#include <random>
const int maxn = 1e8;
int st[maxn], t = 0;
extern "C"
{
    void swap(int &a, int &b)
    {
        int t = a;
        a = b;
        b = t;
    }

    unsigned int generateSeedFromTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

        return static_cast<unsigned int>(timestamp.count());
    }
    unsigned int seed = generateSeedFromTimestamp();
    std::mt19937 engine(seed);
    std::pair<int, int> partition(int q[], int l, int r)
    {
        int i = l, j = l, k = r, x = q[l + engine() % (r - l + 1)];
        while (i <= k)
        {
            if (q[i] < x)
                swap(q[i++], q[j++]);
            else if (q[i] > x)
                swap(q[i], q[k--]);
            else
                ++i;
        }
        return std::make_pair(j - 1, k + 1);
    }
    void insertSort(int q[], int l, int r)
    {
        for (int i = l + 1; i <= r; i++)
        {
            int j = i;
            while (j > l)
            {
                if (q[j] < q[j - 1])
                {
                    swap(q[j], q[j - 1]);
                    j--;
                }
                else
                {
                    break;
                }
            }
        }
    }
    void sort(int q[], int l, int r)
    {
        if (l < r)
        {
            std::pair<int, int> pa = partition(q, l, r);
            int j = pa.first, k = pa.second;
            if (j > l)
            {
                st[t++] = l;
                st[t++] = j;
            }
            if (k < r)
            {
                st[t++] = k;
                st[t++] = r;
            }
            while (t != 0)
            {
                int sr = st[--t];
                int sl = st[--t];
                if (sr - sl > 16)
                {
                    pa = partition(q, sl, sr);
                    j = pa.first, k = pa.second;
                    if (j > sl)
                    {
                        st[t++] = sl;
                        st[t++] = j;
                    }
                    if (k < sr)
                    {
                        st[t++] = k;
                        st[t++] = sr;
                    }
                }
                else
                {
                    insertSort(q, sl, sr);
                }
            }
        }
    }
}

int main()
{
    int a[] = {6, 5, 4, 3, 2, 1};
    sort(a, 0, 5);
    for (int i = 0; i < 6; ++i)
        std::cout << a[i] << " ";
    return 0;
}