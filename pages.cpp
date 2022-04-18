#include <bits/stdc++.h>

using namespace std;

class page
{
    int fptr;
    vector<int> ptrs;
    vector<int> key;
    friend class file;
};

class file
{
    int psize;
    vector<page *> f;

public:
    file(int psize);
    void insert(int, int);
    void status();
    void search(int);
};

file::file(int psize)
{
    this->psize = psize;
}

void file::insert(int Rsize, int n)
{
    if (f.size() == 0)
    {
        page *temp = new page();
        temp->ptrs.push_back(0);
        temp->fptr = 16 + Rsize + 4;
        temp->key.push_back(n);
        f.push_back(temp);
        return;
    }

    for (int i = 0; i < f.size(); i++)
    {
        int temp = psize - f[i]->fptr;
        if (Rsize + 4 < temp)
        {
            f[i]->key.push_back(n);
            f[i]->ptrs.push_back(f[i]->fptr - 16);
            f[i]->fptr = f[i]->fptr + Rsize + 4;
            return;
        }
    }
    page *newpage = new page();
    newpage->fptr = 16 + Rsize + 4;
    newpage->ptrs.push_back(0);
    newpage->key.push_back(n);
    f.push_back(newpage);
}

void file::status()
{
    if (f.size() == 0)
    {
        cout << 0 << endl;
        return;
    }
    cout << f.size() << " ";
    for (int i = 0; i < f.size(); i++)
    {
        cout << f[i]->key.size() << " ";
    }
    cout << endl;
}

void file::search(int key)
{
    for (int i = 0; i < f.size(); i++)
    {
        auto it = find(f[i]->key.begin(), f[i]->key.end(), key);
        if (it != f[i]->key.end())
        {
            cout << i << " " << it - f[i]->key.begin() << endl;
            return;
        }
    }
    cout << -1 << " " << -1 << endl;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int size;
    cin >> size;
    file f(size);

    int mode;
    int i, j;
    while (mode != 4)
    {
        cin >> mode;
        if (mode == 1)
        {
            cin >> i >> j;
            f.insert(i, j);
        }
        else if (mode == 2)
        {
            f.status();
        }
        else if (mode == 3)
        {
            cin >> j;
            f.search(j);
        }
    }

    return (0);
}
