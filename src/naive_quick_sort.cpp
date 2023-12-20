#include <iostream>
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

    std::pair<int, int> partition(int q[], int l, int r)
    {
        int i = l - 1, j = r + 1, x = q[l];
        while (i < j)
        {
            do
                i++;
            while (q[i] < x);
            do
                j--;
            while (q[j] > x);
            if (i < j)
            {
                swap(q[i], q[j]);
            }
        }
        return std::make_pair(j, j + 1);
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
        }
    }
}
