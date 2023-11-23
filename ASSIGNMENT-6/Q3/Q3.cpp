#include <bits/stdc++.h>
using namespace std;

void print(vector <int> pagetable)
{
    int n=pagetable.size();
    int i,j,k;

    for(i=0 ; i<n ; i++)
    {
        cout << pagetable[i] << " ";
    }
    cout << endl;

    return;
}

int main()
{
    int n,m;
    int i,j,k;

    cout << "Sequence Length: ";
    cin >> n;

    vector <int> pages(n);

    cout << "Enter Sequence: ";
    for(i=0 ; i<n ; i++)
    {
        cin >> pages[i];
    }

    cout << "Page-frame size: ";
    cin >> m;

    cout << "\nFIFO - 1" << endl;
    cout << "Optimal - 2" << endl;
    cout << "LRU - 3\n" << endl;

    int prs;
    cout << "Enter Page replacement strategy: " << endl;
    cin >> prs;

    switch(prs)
    {
        case 1 :
        {
            cout << "\nFIFO\n" << endl;

            vector <int> pagetable;
            int count=0;

            for(i=0 ; i<n ; i++)
            {
                if(find(pagetable.begin(),pagetable.end(),pages[i])!=pagetable.end())
                {
                    cout << "No page fault" << endl;
                    count++;
                }
                else if(pagetable.size()==m)
                {
                    pagetable.erase(pagetable.begin());
                    pagetable.push_back(pages[i]);

                    print(pagetable);
                }
                else
                {
                    pagetable.push_back(pages[i]);

                    print(pagetable);
                }
            }

            cout << "\nTotal number of page faults = " << n-count << endl;
            cout << endl;

            break;
        }

        case 2 :
        {
            cout << "\nOptimal\n" << endl;

            vector <int> pagetable;
            int count=0;

            for(i=0 ; i<n ; i++)
            {
                if(find(pagetable.begin(),pagetable.end(),pages[i])!=pagetable.end())
                {
                    cout << "No page fault" << endl;
                    count++;
                }
                else if(pagetable.size()==m)
                {
                    int k=INT_MIN;
                    int f;

                    for(j=0 ; j<m ; j++)
                    {
                        int a=(find(pages.begin()+i,pages.end(),pagetable[j]))-(pages.begin());
                        if(a>k)
                        {
                            k=a;
                            f=j;
                        }
                    }

                    pagetable.erase(pagetable.begin()+f);
                    pagetable.push_back(pages[i]);

                    print(pagetable);
                }
                else
                {
                    pagetable.push_back(pages[i]);

                    print(pagetable);
                }
            }

            cout << "\nTotal number of page faults = " << n-count << endl;
            cout << endl;

            break;
        }

        case 3 :
        {
            cout << "\nLRU\n" << endl;

            vector <int> pagetable;
            int count=0;

            for(i=0 ; i<n ; i++)
            {
                if(find(pagetable.begin(),pagetable.end(),pages[i])!=pagetable.end())
                {
                    pagetable.erase(find(pagetable.begin(),pagetable.end(),pages[i]));
                    pagetable.push_back(pages[i]);

                    cout << "No page fault" << endl;
                    count++;
                }
                else if(pagetable.size()==m)
                {
                    pagetable.erase(pagetable.begin());
                    pagetable.push_back(pages[i]);

                    print(pagetable);
                }
                else
                {
                    pagetable.push_back(pages[i]);

                    print(pagetable);
                }
            }

            cout << "\nTotal number of page faults = " << n-count << endl;
            cout << endl;

            break;
        }
    }

    return 0;
}