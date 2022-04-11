#include <bits/stdc++.h>

using namespace std;

class node
{
    bool isleaf;
    vector<int> keys;
    vector<node *> ptr;
    friend class bptree;
};

class bptree
{
    int dsize, isize;
    node *root;
    int ci = 0, cd = 0;
    void insertinternal(int, node *, node *);
    node *findparent(node *, node *);
    void dis(node *);

public:
    bptree(int dsize, int isize);
    int insert(int);
    void display();
};

bptree::bptree(int dsize, int isize)
{
    this->dsize = dsize;
    this->isize = isize;
    root = nullptr;
}

node *bptree::findparent(node *cursor, node *child)
{
    node *parent;
    if (cursor->isleaf || cursor->ptr[0]->isleaf)
    {
        return (nullptr);
    }
    for (int i = 0; i < cursor->ptr.size(); i++)
    {
        if (cursor->ptr[i] == child)
        {
            parent = cursor;
            return parent;
        }
        else
        {
            parent = findparent(cursor->ptr[i], child);
            if (parent != NULL)
                return parent;
        }
    }
    return parent;
}

void bptree::insertinternal(int n, node *cursor, node *newleaf)
{
    if (cursor->keys.size() < 2 * isize + 1)
    {
        node *dump = new node;
        cursor->keys.push_back(n);
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = find(cursor->keys.begin(), cursor->keys.end(), n);
        int i = it - cursor->keys.begin();
        cursor->ptr.push_back(dump);
        for (int j = cursor->ptr.size() - 1; j > i + 1; j--)
        {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->ptr[i + 1] = newleaf;
    }
    else
    {
        node *newinter = new node;
        cursor->keys.push_back(n);
        node *dump = new node;
        newinter->isleaf = false;
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = find(cursor->keys.begin(), cursor->keys.end(), n);
        int i1 = it - cursor->keys.begin();
        cursor->ptr.push_back(dump);
        for (int j = cursor->ptr.size() - 1; j > i1 + 1; j--)
        {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->ptr[i1 + 1] = newleaf;
        auto k = cursor->keys.begin() + isize + 1;
        for (auto i = k; i != cursor->keys.end(); i++)
        {
            newinter->keys.push_back(*i);
        }

        cursor->keys.erase(k, cursor->keys.end());
        k = cursor->keys.begin() + isize;
        int no = *k;
        cursor->keys.erase(k);

        auto it2 = cursor->ptr.begin() + isize + 1;
        for (auto i = it2; i != cursor->ptr.end(); i++)
        {
            newinter->ptr.push_back(*i);
        }
        cursor->ptr.erase(it2, cursor->ptr.end());
        if (cursor == root)
        {
            node *newroot = new node;

            newroot->keys.push_back(no);
            newroot->ptr.push_back(cursor);
            newroot->ptr.push_back(newinter);
            newroot->isleaf = false;
            root = newroot;
            ci++;
        }
        else
        {
            insertinternal(no, findparent(root, cursor), newinter);
        }
        ci++;
    }
}

int bptree::insert(int n)
{
    if (root == nullptr)
    {
        root = new node();
        root->keys.push_back(n);
        root->isleaf = true;
        cd++;
        return (1);
    }
    node *cursor = root;
    node *parent;
    while (cursor->isleaf == false)
    {
        parent = cursor;
        for (int i = 0; i < cursor->keys.size(); i++)
        {
            if (n < cursor->keys[i])
            {
                cursor = cursor->ptr[i];
                break;
            }
            if (i == cursor->keys.size() - 1)
            {
                cursor = cursor->ptr[i + 1];
                break;
            }
        }
    }
    if (cursor->keys.size() < 2 * dsize)
    {
        cursor->keys.push_back(n);
        sort(cursor->keys.begin(), cursor->keys.end());
    }
    else
    {
        node *newleaf = new node;
        cursor->keys.push_back(n);
        newleaf->isleaf = true;
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = cursor->keys.begin() + dsize;
        for (auto i = it; i != cursor->keys.end(); i++)
        {
            newleaf->keys.push_back(*i);
        }
        cursor->keys.erase(it, cursor->keys.end());
        if (cursor == root)
        {
            node *newroot = new node;

            newroot->keys.push_back(newleaf->keys[0]);
            newroot->ptr.push_back(cursor);
            newroot->ptr.push_back(newleaf);
            newroot->isleaf = false;
            root = newroot;
            ci++;
        }
        else
        {
            insertinternal(newleaf->keys[0], parent, newleaf);
        }
        cd++;
    }
    return (1);
}

void bptree::display()
{
    cout << ci << " " << cd << " ";
    for (auto i = root->keys.begin(); i != root->keys.end(); i++)
    {
        cout << (*i) << " ";
    }
    cout << endl;
}

/*void bptree::dis(node *cursor)
{
    for (int i = 0; i < cursor->keys.size(); i++)
    {
        cout << cursor->keys[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < cursor->ptr.size(); i++)
    {
        dis(cursor->ptr[i]);
    }
}

void bptree::display()
{
    dis(root);
}*/

int main()
{
    int d, t;
    cin >> d;
    cin >> t;

    bptree bp(d, t);

    int mode;
    int j;
    while (mode != 3)
    {
        cin >> mode;
        if (mode == 1)
        {
            cin >> j;
            bp.insert(j);
        }
        else if (mode == 2)
        {
            bp.display();
        }
    }
    /*bptree bp(2, 1);
    bp.insert(100);
    bp.insert(200);
    bp.insert(300);
    bp.insert(400);
    // bp.display();
    bp.insert(500);
    // bp.display();
    bp.insert(600);
    bp.insert(700);
    // bp.display();
    bp.insert(850);
    bp.insert(150);
    bp.insert(350);
    bp.insert(250);
    // bp.display();
    bp.insert(251);
    // bp.display();
    bp.insert(252);
    bp.insert(253);
    bp.insert(851);
    bp.insert(401);
    bp.insert(402);
    bp.display(); */
    return (0);
}#include <bits/stdc++.h>

using namespace std;

class node
{
    bool isleaf;
    vector<int> keys;
    vector<node *> ptr;
    friend class bptree;
};

class bptree
{
    int dsize, isize;
    node *root;
    int ci = 0, cd = 0;
    void insertinternal(int, node *, node *);
    node *findparent(node *, node *);
    void dis(node *);

public:
    bptree(int dsize, int isize);
    int insert(int);
    void display();
};

bptree::bptree(int dsize, int isize)
{
    this->dsize = dsize;
    this->isize = isize;
    root = nullptr;
}

node *bptree::findparent(node *cursor, node *child)
{
    node *parent;
    if (cursor->isleaf || cursor->ptr[0]->isleaf)
    {
        return (nullptr);
    }
    for (int i = 0; i < cursor->ptr.size(); i++)
    {
        if (cursor->ptr[i] == child)
        {
            parent = cursor;
            return parent;
        }
        else
        {
            parent = findparent(cursor->ptr[i], child);
            if (parent != NULL)
                return parent;
        }
    }
    return parent;
}

void bptree::insertinternal(int n, node *cursor, node *newleaf)
{
    if (cursor->keys.size() < 2 * isize + 1)
    {
        node *dump = new node;
        cursor->keys.push_back(n);
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = find(cursor->keys.begin(), cursor->keys.end(), n);
        int i = it - cursor->keys.begin();
        cursor->ptr.push_back(dump);
        for (int j = cursor->ptr.size() - 1; j > i + 1; j--)
        {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->ptr[i + 1] = newleaf;
    }
    else
    {
        node *newinter = new node;
        cursor->keys.push_back(n);
        node *dump = new node;
        newinter->isleaf = false;
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = find(cursor->keys.begin(), cursor->keys.end(), n);
        int i1 = it - cursor->keys.begin();
        cursor->ptr.push_back(dump);
        for (int j = cursor->ptr.size() - 1; j > i1 + 1; j--)
        {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->ptr[i1 + 1] = newleaf;
        auto k = cursor->keys.begin() + isize + 1;
        for (auto i = k; i != cursor->keys.end(); i++)
        {
            newinter->keys.push_back(*i);
        }

        cursor->keys.erase(k, cursor->keys.end());
        k = cursor->keys.begin() + isize;
        int no = *k;
        cursor->keys.erase(k);

        auto it2 = cursor->ptr.begin() + isize + 1;
        for (auto i = it2; i != cursor->ptr.end(); i++)
        {
            newinter->ptr.push_back(*i);
        }
        cursor->ptr.erase(it2, cursor->ptr.end());
        if (cursor == root)
        {
            node *newroot = new node;

            newroot->keys.push_back(no);
            newroot->ptr.push_back(cursor);
            newroot->ptr.push_back(newinter);
            newroot->isleaf = false;
            root = newroot;
            ci++;
        }
        else
        {
            insertinternal(no, findparent(root, cursor), newinter);
        }
        ci++;
    }
}

int bptree::insert(int n)
{
    if (root == nullptr)
    {
        root = new node();
        root->keys.push_back(n);
        root->isleaf = true;
        cd++;
        return (1);
    }
    node *cursor = root;
    node *parent;
    while (cursor->isleaf == false)
    {
        parent = cursor;
        for (int i = 0; i < cursor->keys.size(); i++)
        {
            if (n < cursor->keys[i])
            {
                cursor = cursor->ptr[i];
                break;
            }
            if (i == cursor->keys.size() - 1)
            {
                cursor = cursor->ptr[i + 1];
                break;
            }
        }
    }
    if (cursor->keys.size() < 2 * dsize)
    {
        cursor->keys.push_back(n);
        sort(cursor->keys.begin(), cursor->keys.end());
    }
    else
    {
        node *newleaf = new node;
        cursor->keys.push_back(n);
        newleaf->isleaf = true;
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = cursor->keys.begin() + dsize;
        for (auto i = it; i != cursor->keys.end(); i++)
        {
            newleaf->keys.push_back(*i);
        }
        cursor->keys.erase(it, cursor->keys.end());
        if (cursor == root)
        {
            node *newroot = new node;

            newroot->keys.push_back(newleaf->keys[0]);
            newroot->ptr.push_back(cursor);
            newroot->ptr.push_back(newleaf);
            newroot->isleaf = false;
            root = newroot;
            ci++;
        }
        else
        {
            insertinternal(newleaf->keys[0], parent, newleaf);
        }
        cd++;
    }
    return (1);
}

void bptree::display()
{
    cout << ci << " " << cd << " ";
    for (auto i = root->keys.begin(); i != root->keys.end(); i++)
    {
        cout << (*i) << " ";
    }
    cout << endl;
}

/*void bptree::dis(node *cursor)
{
    for (int i = 0; i < cursor->keys.size(); i++)
    {
        cout << cursor->keys[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < cursor->ptr.size(); i++)
    {
        dis(cursor->ptr[i]);
    }
}

void bptree::display()
{
    dis(root);
}*/

int main()
{
    int d, t;
    cin >> d;
    cin >> t;

    bptree bp(d, t);

    int mode;
    int j;
    while (mode != 3)
    {
        cin >> mode;
        if (mode == 1)
        {
            cin >> j;
            bp.insert(j);
        }
        else if (mode == 2)
        {
            bp.display();
        }
    }
    /*bptree bp(2, 1);
    bp.insert(100);
    bp.insert(200);
    bp.insert(300);
    bp.insert(400);
    // bp.display();
    bp.insert(500);
    // bp.display();
    bp.insert(600);
    bp.insert(700);
    // bp.display();
    bp.insert(850);
    bp.insert(150);
    bp.insert(350);
    bp.insert(250);
    // bp.display();
    bp.insert(251);
    // bp.display();
    bp.insert(252);
    bp.insert(253);
    bp.insert(851);
    bp.insert(401);
    bp.insert(402);
    bp.display(); */
    return (0);
}
