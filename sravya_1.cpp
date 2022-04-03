#include<bits/stdc++.h>

#define pb push_back
#define all(a) a.begin(),a.end()
#define cpresent(container,element) (find(all(container),element)!=container.end())
#define rep(i, a, b)    for(int i = a; i < b; ++i)
using namespace std;

struct Bucket
{
    int ld=0;
    vector<int>a;
    int t;
};

map<int,Bucket *>bmap;
int gd,bucket_capacity,time_creation=0;

void display()
{
    cout << gd << '\n';
    set<pair<int,pair<vector<int>,int>>> s;
    rep(i,0,1<<gd)
    {
        int id = bmap[i]->ld;
        vector<int> temp = bmap[i]->a;
        int t_= bmap[i]->t;
        s.insert({t_,{temp,id}});
    }
    cout << s.size() << '\n';
    for(auto i : s){
        cout << i.second.first.size() << " " << i.second.second << '\n';
    }
}

int search(int n)
{
    int h = n & ((1<<gd) - 1);
    return cpresent(bmap[h]->a,n);
}

void split(int k,Bucket * nbucket)
{
    Bucket * newB = new Bucket;
    vector<int>temp;
    for(auto i : nbucket->a)
    {
        temp.pb(i);
    }
    
    nbucket->a.clear();
    
    if(nbucket->ld == gd)
    {
        bmap[k ^ (1<<gd)] = newB;
        bmap[k^(1<<gd)]->t=++time_creation;
        if(gd!=0)
        {
         for (int i = 0; i < (1<<gd); ++i)
            {

                if(i!=k)
                    bmap[i ^ (1<<gd)] = bmap[i];
            }
        }
        gd++;
        newB->ld = ++ nbucket->ld;
        for(auto i : temp)
        {
            int h = i & ((1<<gd) -1);
            bmap[h]->a.pb(i);
        }
    }
    else
    {
        int li = k & (1<<(nbucket->ld) - 1);
        vector<int>indices;
     for (int i = 0; i < (1<<gd); ++i)
        {
            int last = i & (1<<(nbucket->ld)) - 1;
            if(last==li)
                indices.pb(i);
        }
        newB->ld = ++nbucket->ld;
     for (int i = indices.size()/2; i < indices.size(); ++i)
        {
            bmap[indices[i]] = newB;
        }

        for(auto i : temp)
        {
            int h = i & ((1<<gd) -1);
            bmap[h]->a.pb(i);
        }
    }

}
void insert(int n)
{
    int h = n & ((1<<gd) - 1);
    if(bmap[h]->a.size() < bucket_capacity)
        bmap[h]->a.pb(n);
    else
    {
        split(h,bmap[h]);
        insert(n);
    }
}

void merge()
{
    for(int i = 0; i<(1<<(gd-1));i++)
    {
        int h = i & ( ( 1<< ((bmap[i]->ld)-1) ) - 1);
        /*Current and Matched are pair of matching data buckets having ld-1 common suffix*/
        Bucket *curr = bmap[i];
        Bucket *matched = bmap[ i ^ (1<<(bmap[i]->ld-1)) ];
        if(curr != matched)
        {
            int sz = curr->a.size() + matched->a.size();
            if(sz <= bucket_capacity)
            {
                copy(all(matched->a),back_inserter(curr->a));
                vector<int>inds;
                for(auto i : bmap)
                {
                    if(i.second==matched)
                        inds.pb(i.first);
                }
                delete matched;
                for(auto j : inds)
                    bmap[j] = bmap[i];
                bmap[i]->ld --;
            }
        }
    }
}

void shrink()
{
    set <Bucket *>buckets;
    for(auto i : bmap)
        buckets.insert(i.second);
    int count = 0;
    int sz = buckets.size();
    for(auto i : buckets)
        if ( (gd - (i->ld)) == 1)
            count++;
    if(count==sz)
        gd--;
}

void del(int n)
{
    if(search(n))
    {
        
        /*Deleting the entry */
        for(auto i : bmap)
        {
            auto it = find(all(i.second->a),n);
            if(it!=i.second->a.end())
            {
                i.second->a.erase(it);
                break;
            }
        }
        /*Merging the pair of data buckets if possible*/
        // merge();

        /*If all the buckets have local depth less than global depth then shrink the directory*/
        // shrink();

        // cout<<"Number deleted successfully\n";
    }
    else{  
        // cout<<"Element not found : \n";
    }
}
void menu()
{
    int choice;
    int n;
    while(1)
    {
        cin>>choice;
        switch(choice)
        {
            case 2:
                cin>>n;
                insert(n);
                // cout<<"Number inserted successfully\n";
                break;
            case 4:
                cin>>n;
                del(n);
                break;
            case 5:
                display();
                break;
            case 3:
                cin>>n;
                if(search(n))
                    {// cout<<"Found\n";
            }
                else
                    {// cout<<"Not Found\n";
            }
                break;
            case 6:
                exit(0);
            default:
                cout<<"Invalid choice !";
        }
    }
}
int main()
{   int gb;
    cin>>gb>>bucket_capacity;
    int gd = gb;
    bmap[0] = new Bucket;
    menu();
}