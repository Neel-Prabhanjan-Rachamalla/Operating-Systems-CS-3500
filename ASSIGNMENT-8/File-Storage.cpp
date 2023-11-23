#include <bits/stdc++.h>
using namespace std;

class inode
{
    public:
    string fname;
    string dcreated;
    string dmodified;
    string finfo;
    queue <int> table;
    int ftype;
    int fsize;
    int iba; 
    int nblocksfile;
    int nodeb;
    vector<int> directblocks;
    vector<int> indirectblocks;

    inode(string file, int block)
    {
        fname = file;
        time_t now = time(0);
        dcreated = ctime(&now);
        nblocksfile = 0;
        fsize = 0;
        for(int i=0;i<3;i++)
            directblocks.push_back(0);
        finfo = "";
        iba = -1;
        nodeb = block;
        for(int i=0;i<3;i++)
            directblocks[i] = -1;
    }
};

class disk
{
    public:

    map <string,inode*> files;
    int size;
    int blocks;
    int bsize;
    double stackablefile;
    queue <int> free_blocks_list;
    string dname;
    disk(string name, int size)
    {
        blocks = 32*size;
        for(int i=0;i<blocks;i++)
        {
            free_blocks_list.push(i+1);
        }
        dname = name;
        size = size;
    } 
};

void printinode(disk *disk)
{
    string file_name;
    cin >> file_name;
    if(disk->files.find(file_name) == disk->files.end())
    {
        cout << "FILE DOES NOT EXIST" << endl;
        return;
    }

    inode* temp = (disk->files)[file_name];
    cout << "\n****************************" << endl;
    cout << "fname: " << file_name << endl;
    cout << "Size: " << temp->fsize << endl;
    cout << "Date Created: " << temp->dcreated;
    cout << "Date Last Modified: " << temp->dmodified;
    cout << "Direct block values: ";
    int j = 0;
    while(temp->directblocks[j] >0  && j<3)
    {
        cout << temp->directblocks[j] << " ";
        j++;
    }
    cout << endl;
    cout << "Index block is stored in: " << temp->iba << endl;
    cout << "Index block contents: ";
    for(int i=0;i<temp->indirectblocks.size();i++)
    {
        cout << temp->indirectblocks[i] << " ";
    }
    cout << endl;
    cout << "****************************\n" << endl;
}

void freespacen(disk *disk)
{
    cout << "Free blocks - " << disk->free_blocks_list.size() << endl;
    cout << "Free size (in B) - " << (128)*(disk->free_blocks_list.size())<< endl;
}

void displayn(disk *disk)
{
    for(auto &i : disk->files)
    {
        cout << i.first << " - " << i.second->fsize << endl;
    }
}

void appendn(disk *disk)
{
    string file_name;
    cin >> file_name;
    if(disk->files.find(file_name) == disk->files.end())
    {
        cout << "FILE DOES NOT EXIST" << endl;
        return;
    }
    string input;
    getline(cin,input);

    inode* temp = disk->files[file_name];

    time_t dt = time(0);
    temp->dmodified = ctime(&dt);

    string newstr = input.substr(1);

    temp->finfo += newstr;
    temp->fsize = temp->finfo.size();

    int old = temp->nblocksfile;

    if(temp->fsize%128 == 0)
        temp->nblocksfile = temp->fsize/128;
    else
        temp->nblocksfile = 1 + temp->fsize/128;

    int new_blocks = temp->nblocksfile - old;

    int i = 0;
    if(temp->directblocks[0]>0)
        i=1;
    if(temp->directblocks[1]>0)
        i=2;
    if(temp->directblocks[2]>0)
        i=3;
            
    if(i==3)
    {
        temp->iba = disk->free_blocks_list.front();
        disk->free_blocks_list.pop();
        for(int i=0;i<new_blocks;i++)
        {
            int x = disk->free_blocks_list.front();
            temp->indirectblocks.push_back(x);
            disk->free_blocks_list.pop();
        }
    }
    else
    {
        while(i < 3)
        {
            if(new_blocks==0)
                break;
            temp->directblocks[i] = disk->free_blocks_list.front();
            disk->free_blocks_list.pop();
            new_blocks--;
            i++;
        }

        temp->iba = disk->free_blocks_list.front();
        disk->free_blocks_list.pop();
        for(int i=0;i<new_blocks;i++)
        {
            int x = disk->free_blocks_list.front();
            temp->indirectblocks.push_back(x);
            disk->free_blocks_list.pop();
        }
    }
}

void printn(disk *disk)
{
    string file_name;
    cin >> file_name;
    if(disk->files.find(file_name) == disk->files.end())
    {
        cout << "FILE DOES NOT EXIST" << endl;
        return;
    }

    cout << (disk->files)[file_name]->finfo <<endl;
}

void deleten(disk *disk)
{
    string file_name;
    cin >> file_name;
    if(disk->files.find(file_name) == disk->files.end())
    {
        cout << "FILE DOES NOT EXIST" << endl;
        return;
    }

    inode* temp = (disk->files)[file_name];
    disk->free_blocks_list.push(temp->nodeb);
    int j = 0;

    if(temp->directblocks[0] > 0)
    {
        disk->free_blocks_list.push(temp->directblocks[0]);
        disk->free_blocks_list.push(temp->directblocks[1]);
        disk->free_blocks_list.push(temp->directblocks[2]);
    }
    else if(temp->directblocks[1] > 0)
    {
        disk->free_blocks_list.push(temp->directblocks[1]);
        disk->free_blocks_list.push(temp->directblocks[2]);
    }
    else if(temp->directblocks[2] > 0)
        disk->free_blocks_list.push(temp->directblocks[2]);

    if(temp->iba > 0)
        disk->free_blocks_list.push(temp->iba);

    for(int i=0;i<temp->indirectblocks.size();i++)
    {
        disk->free_blocks_list.push(temp->indirectblocks[i]);
    }
    disk->files.erase(file_name);
    free(temp);
}

void load(disk *disk)
{
    string file_name;
    cin >> file_name;
    if(disk->free_blocks_list.empty())
    {
        cout << "No space available on disk" << endl;
    }
    else
    {
        inode* new_file = new inode(file_name,disk->free_blocks_list.front());
        disk->free_blocks_list.pop();
        disk->files[file_name] = new_file;
    }
}

int main()
{
    string D;
    cout << "Enter diskfile name" << endl;
    cin >> D;
    int size;
    cout << "Enter disk size" << endl;
    cin >> size;

    disk diskobj = disk(D,size);

    while(true)
    {
        string opcode;
        string file_name;
        cout << "\nEnter next instruction" << endl;
        cin >> opcode;

        if(opcode == "load")
        {
            load(&diskobj);

        }
        else if(opcode == "delete")
        {
            deleten(&diskobj);
        }
        else if(opcode == "print")
        {
            printn(&diskobj);
        }
        else if(opcode == "append")
        {
            appendn(&diskobj);
        }
        else if(opcode == "display")
        {
            displayn(&diskobj);
        }
        else if(opcode == "freespace")
        {
            freespacen(&diskobj);
        }
        else if(opcode == "printinode")
        {
            printinode(&diskobj);
        }
        else if(opcode == "exit")
        {
            return 0;
        }
        else
        {
            cout << "Invalid opcode" << endl;
        }
    }
}