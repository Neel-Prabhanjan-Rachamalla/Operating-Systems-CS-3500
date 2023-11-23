#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    int i,j,k;

    cout << "Enter the Number of Blocks: ";
    cin >> n;

    vector <vector <int>> blocks(n);

    cout << "Enter " << n << " Block Sizes: ";
    for(i=0 ; i<n ; i++)
    {
        int a;
        cin >> a;
        blocks[i]=vector <int> {a,i+1,1};
    }

    cout << "Enter Number of Processes: ";
    cin >> m;

    vector <int> processes(m);
    
    cout << "Enter " << m << " Process Sizes: ";
    for(i=0 ; i<m ; i++)
    {
        cin >> processes[i];
    }

    vector <pair <int,int>> ff(m,pair <int,int>(-1,-1));
    
    for(i=0 ; i<m ; i++)
    {
        for(j=0 ; j<n ; j++)
        {
            if(blocks[j][0]>=processes[i] && blocks[j][2]==1)
            {
                ff[i]=pair <int,int> (blocks[j][0],j+1);
                blocks[j][2]=0;
                break;
            }
        }
    }

    for(i=0 ; i<n ; i++)
    {
        blocks[i][2]=1;
    }

    sort(blocks.begin(),blocks.end());


    vector <pair <int,int>> bf(m,pair <int,int> (-1,-1));

    for(i=0 ; i<m ; i++)
    {
        for(j=0 ; j<n ; j++)
        {
            if(blocks[j][0]>=processes[i] && blocks[j][2]==1)
            {
                bf[i]=pair <int,int> (blocks[j][0],blocks[j][1]);
                blocks[j][2]=0;
                break;
            }
        }
    }

    for(i=0 ; i<n ; i++)
    {
        blocks[i][2]=1;
    }

    vector <pair <int,int>> wf(m,pair <int,int> (-1,-1));

    for(i=0 ; i<m ; i++)
    {
        for(j=n-1 ; j>=0 ; j--)
        {
            if(blocks[j][0]>=processes[i] && blocks[j][2]==1)
            {
                wf[i]=pair <int,int> (blocks[j][0],blocks[j][1]);
                blocks[j][2]=0;
                break;
            }
        }
    }

    cout << "\nFirst Fit" << endl;
    cout << "Process number | Process size | Block size | Block number" << endl;
    for(i=0 ; i<m ; i++)
    {
        if(ff[i].first!=-1) cout << (i+1) << "              " << processes[i] << "              " << ff[i].first << "              " << ff[i].second << endl;
        else cout << (i+1) << "              " << processes[i] << "              " << "Not Allocated" << endl;
    }
    cout << endl;

    cout << "Best Fit" << endl;
    cout << "Process number | Process size | Block size | Block number" << endl;
    for(i=0 ; i<m ; i++)
    {
        if(bf[i].first!=-1) cout << (i+1) << "    " << processes[i] << "    " << bf[i].first << "    " << bf[i].second << endl;
        else cout << (i+1) << "    " << processes[i] << "    " << "Not Allocated" << endl;
    }
    cout << endl;

    cout << "Worst Fit" << endl;
    cout << "Process number | Process size | Block size | Block number" << endl;
    for(i=0 ; i<m ; i++)
    {
        if(wf[i].first!=-1) cout << (i+1) << "    " << processes[i] << "    " << wf[i].first << "    " << wf[i].second << endl;
        else cout << (i+1) << "    " << processes[i] << "    " << "Not Allocated" << endl;
    }
    cout << endl;

    return 0;
}