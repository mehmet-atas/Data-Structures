#include <iostream>
#include <fstream>
//REFERENCES
//Ford &Topp, Data Structures with C++, Prentice-Hall, 1996.
//Preiss, B.R., Data Structures and Algorithms with Object-Oriented Design Patterns in C++,Wiley, 1999.
// Shaffer, C., Data Structures & Algorithm Analysis in C++, Dover Publications, 2012
//https://github.com/atakancelikkol
//EE441_LectureNotes_ch6_linkedlist
//EE441_LectureNotes_ch7_trees

//Time complexity of LL     Avg: Search -> O(n)         Avg: Insertion -> O(1)          Avg: Deletion -> O(1)
//Time complexity of LL     Worst:Search -> O(n)  	    Worst: Insertion -> O(1)        Worst: Deletion -> O(1)
//Space complexity of LL    Worst: O(n)
//Time complexity of BST   	Avg:Search -> O(log (n))	Avg: Insertion -> O(log (n))	Avg: Deletion -> O(log (n))
//Time complexity of BST   	Worst:Search -> O(n)	Worst: Insertion -> O(n)	Worst: Deletion -> O(n)

//A binary tree has a better time complexity for searching O(log N) but in the worst case can be the same as a linked list O(n).
//This means searching a binary tree will be faster than searching a linked list in most cases.
using namespace std;

class Nodes
{
    public:
        int ID; //Process ID
        int ART; //Arrival Time
        int RT; //Run Time
        int PR; //Priority
        Nodes *next;
        Nodes (const int &id=0,const int &art=0,const int &rt=0,const int &pr=0, Nodes* ptrnext=0)
        {
            ID=id;
            ART=art;
            RT=rt;
            PR=pr;
            next=ptrnext;
        }

        void Insert(Nodes *newnode)
            {
            newnode->next=next;
            next=newnode;
            }
};

class Tree
{
    public:
        Tree(const int &id=0,const int &art=0,const int &rt=0,const int &pr=0, Tree*rightptr=0, Tree*leftptr=0)
        {
            Left=leftptr;
            Right=rightptr;
            ID=id;
            ART=art;
            RT=rt;
            PR=pr;
        }
    int ID;
    int ART;
    int RT;
    int PR;
    Tree *Right;
    Tree *Left;
};

//a function dynamically allocate memory for a new object
Nodes *GetNode(const int& id,const int& art,const int& rt,const int& pr, Nodes* ptrnext=NULL)
{
    Nodes *nodenew;
    nodenew=new Nodes(id, art, rt, pr, ptrnext);
    if (nodenew==NULL)//if "new" was unsuccesful
    {
        cerr<<"Memory allocation failed"<<endl;
        exit(1);
    }
    return nodenew;
}

Tree* GetTree(Tree item, Tree* rptr=0, Tree* lptr=0)
{
    Tree* newnode;
    newnode=new Tree(item.ID,item.ART,item.RT,item.PR,rptr,lptr);
    if(newnode==NULL)
    {
        cout<< "Memory allocation failed"<<endl;
        exit(1);
    }
    return newnode;
}

// passing in the address of the head pointer by & in order to modify
//function to delete the new item
void DeleteFront(Nodes* & head)
{
    Nodes *newnode = head;
    if (head != NULL)
    {
        head = head->next;
        delete newnode;
    }
}

//function to insert a new item
void InsertFront(int id, int art, int rt,int pr, Nodes* & head)
{
    head=GetNode(id,art,rt,pr,head);
}
// Inserts the nodes considering their priority
void InsertPriority(int id, int art, int rt,int pr, int &i, Nodes* & head)
{
    Nodes *newNode, *currentPtr, *previousPtr;
    currentPtr = head;
    previousPtr = NULL;
    //find insertion point
    for (;currentPtr != NULL;i++)
    {
	if (pr < currentPtr->PR)
		break;
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
    }

    if (previousPtr != 0)
    {

        newNode = GetNode(id,art,rt,pr);
        previousPtr->Insert(newNode);
    }
    else
    {
        InsertFront(id,art,rt,pr,head);
    }
}

// Simple dynamically created a new tree node
void InsertTree(int&i, Tree*& tree,Tree extra)
{
    Tree* curr=tree;
    if(tree!=0)
    {
        i++;
        // insert it to its left if it is lower than the current node
        if(extra.PR<curr->PR)
        {
            InsertTree(i,tree->Left,extra);
        }
        // insert it to its right
        else
        {
            InsertTree(i,tree->Right,extra);
        }
    }
    else
    {
        tree=GetTree(extra);
    }
}
Tree* FindMinPr(int&i, Tree*&tree)
{

    Tree* curr;
    curr=tree;
    Tree* next;
    next=tree->Left;
    Tree* minpr;

    if(tree!=0 && tree->Left !=0)
    {
        i++;
        for(;next->Left!=0;i++)
        {
            curr=next;
            next=next->Left;
        }

        minpr=next;
        if(next->Right!=0)
        {
            i++;
            curr->Left=next->Right;
            next->Right=0;
        }
        // we dont have right child
        else
        {
            curr->Left=0;
        }
        return minpr;

    }
    else if(tree->Left==0 && tree!=0)
    {
        i++;
        minpr=tree;
        tree=tree->Right;
        return minpr;
    }
    else
    // there is no root node
    {
        cout<< "Tree is empty !"<<endl;
        return 0;
    }
}
int main()
{
    //CODE 1: Reading the Contents of ‘processes.txt’ into the Array
    ifstream processesFile;
    processesFile.open ("processes.txt");
    int numProcesses;
    processesFile >> numProcesses;
    cout << "Total number of Processes:"<< numProcesses << endl;
    cout<< "Start of Linked List Implementation"<<endl;
    Nodes process[numProcesses];
    Tree process2[numProcesses];
    int ID, ART, RT, PR;
    for(int i=0; i<numProcesses; ++i)
{
    processesFile >> ID >> ART >> RT >> PR;
    process[i] = Nodes(ID, ART, RT, PR);
    process2[i]=Tree(ID, ART, RT, PR);
}
 processesFile.close();
 //CODE 2: Translation of Pseudocode of the Process Scheduler
int processIndex=0;
int c1=0;
int c2=0;
int cp[4]; //current procces
int time=0;
bool Busy=false;
Nodes *RQ=0;  // head pointer of Linked List RQ Implementation
for(time; RQ!=0 || processIndex<numProcesses || Busy==true; time++)
    {
        if(Busy==false && RQ!=0)
        {
            c2++;
            cp[0]=RQ->ID;
            cp[1]=RQ->ART;
            cp[2]=RQ->RT;
            cp[3]=RQ->PR;
            DeleteFront(RQ);
            Busy=true;
        }
        if(processIndex<numProcesses)   // there are processes not inserted into RQ
        {
            if(process[processIndex].ART==time)
            {
                InsertPriority(process[processIndex].ID,process[processIndex].ART,process[processIndex].RT,process[processIndex].PR,c1,RQ);
                processIndex++;
            }
        }
        if(Busy==true)
        {
            cp[2]-- ;

            if(cp[2]==0)
            {
                cout<<cp[0]<<endl;
                Busy=false;
            }
        }
}
cout<<"\n" << "End of Linked List Implementation"<<endl;
cout<<" " <<endl;
cout << "Start of Binary Search Tree"<< endl;
int processIndex2=0; // Process index
int c3=0; //
int c4=0;//
int cp2[4];// currrent procces,
int time2=0; // CPU Time
bool Busy2=false;
Tree*TR=0; // Tree Node
Tree*z;
for(time2;(TR!=0 || processIndex2<numProcesses || Busy2==true); time2++)
    {
        if(Busy2==false && TR!=0)
        {
            c4++;
            z=FindMinPr(c4,TR);
            cp2[0]=z->ID;
            cp2[1]=z->ART;
            cp2[2]=z->RT;
            cp2[3]=z->PR;
            Busy2=true;
        }
        if(processIndex2<numProcesses)   // there are processes not inserted into TRQ
        {
            if(process2[processIndex2].ART==time2)
            {
                InsertTree(c3,TR,process2[processIndex2]);
                processIndex2++;
            }
        }
        if(Busy2==true)
        {
            cp2[2]-- ;

            if(cp2[2]==0)
            {
                cout<<cp2[0]<<endl;
                Busy2=false;
            }
        }
    }

//Deletion should be equal to the search
cout << "End of Binary Search Tree"<< endl;
cout << "Number of nodes visited for insertion in Linked List: "<< c1 << endl;
cout << "Number of nodes visited for searching in Linked List: "<< c2 << endl;
cout << "Number of nodes visited for deletion in Linked List: "<< c2 << endl;
cout << "Number of nodes visited for insertion in Binary Search Tree:"<< c3 <<endl;
cout << "Number of nodes visited for searching in Binary Search Tree:"<< c4 <<endl;
cout << "Number of nodes visited for deletion in Binary Search Tree:"<< c4 <<endl;

cout << "Gonlum hep seni ariyor, neredesin sen?" << endl;
    return 0;
}
