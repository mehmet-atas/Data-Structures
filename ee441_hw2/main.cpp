#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include<algorithm>
using namespace std;
#ifndef NULL
const int NULL = 0;
#endif // NULL
//write indexes

class Student{
private:
   // int Id;
    //string P1, P2, P3;
public:
    string Id;
    string P1, P2, P3;
    Student(string id, string p1, string p2, string p3);
    Student(){}

   // void set_id(int id);
    //int get_id();

};

Student::Student(string id, string p1, string p2, string p3){
    Id=id;
    P1=p1;
    P2=p2;
    P3=p3;
}


//void Student::set_id(int id){Id=id;}
//int Student::get_id(){return Id;}


template <class T>
class Stack{
private:
    T* stacklist;
    int maxstacksize;
    int top;
public:
    Stack(int Size){
        maxstacksize = Size;
        stacklist = new T[Size];
        top = -1;
    };

    void push(const T& item);
    T pop();
    void clearstack();
    T peek()const;
    int stackempty() const;
    int stackfull() const;
};



template<class T>
int Stack<T>::stackempty() const{
    return top == -1;
}

template<class T>
int Stack<T>::stackfull() const{
    return top == (maxstacksize - 1);
}

template<class T>
void Stack<T>::push(const T& item){
    if (stackfull()){
        cout << " stack is full already." << endl;
        exit(1);
    }
    top++;
    stacklist[top]=item;
}

template<class T>
T Stack<T>::pop(){
    T temp;
    if (stackempty()){
        cout << " stack is empty already." << endl;
        exit (1);
    }
    temp = stacklist[top];
    top--;
    return temp;
}
template<class T>
T Stack<T>::peek() const{
    return stacklist[top];
}
template<class T>
void Stack<T>::clearstack(){
    top = -1;
}


template <class Type >
class Queue{
private:
    int frontier, rear, counter;
    int MaxQueSize;
    Type* queuelist;
public:
    Queue(int Sizeq){
        MaxQueSize = Sizeq;
        queuelist = new Type[Sizeq];
        frontier = 0;
        rear = 0;
        counter = 0;
    };
    void Qadd(Type& item);
    Type Qdelete();
    void ClearQueue();
    Type QFront();
    int Qlength();
    int Qempty();
    int Qfull();
};


template<class Type>
int Queue<Type>::Qlength()
{return counter;};

template<class Type>
int Queue<Type>::Qempty()
{return (counter==0);};

template<class Type>
int Queue<Type>::Qfull()
{return (counter==MaxQueSize);};

template<class Type>
void Queue<Type>::Qadd(Type& item){
    if (Qfull()){
        cout << "Queue is full already." <<endl;
        exit(1);
    }
    counter ++;
    queuelist[rear]=item;
    rear=(rear+1)%MaxQueSize;
}

template<class Type>
Type Queue<Type>::Qdelete(){
    Type temp;
    if (Qempty()){
        cout << "Queue is empty already." << endl;
        exit (1);
    }
    temp = queuelist[frontier];
    counter --;
    frontier=(frontier+1)% MaxQueSize;
return temp;
}
template<class Type>
Type Queue<Type>::QFront(){
    return queuelist[frontier];
}


/*
void test() {
    Stack<string> W(2);
    Stack<string> T(3);
    Stack<string> F(3);
    W.push("sq");
    W.push("qw");
    W.push("we");


    while (!W.stackempty()) {
        cout << W.pop() << endl;
    }



}
*/


bool check(Student stu,string Day1,string Day2,string Day3, Stack<string> &D1 , Stack<string> &D2, Stack<string> &D3,Stack<string> &unassigned)
{
            if((D1.stackfull() && D2.stackfull() && D3.stackfull())
               ||(((stu.P1 == Day1 && D1.stackfull()) || (stu.P1 == Day2 && D2.stackfull()) || (stu.P1 == Day3 && D3.stackfull()))
               &&(((stu.P2 == Day1 && D1.stackfull()) || (stu.P2 == Day2 && D2.stackfull()) || (stu.P2 == Day3 && D3.stackfull()))&&(stu.P3=="1")))
               ||(((stu.P1 == Day1 && D1.stackfull()) || (stu.P1 == Day2 && D2.stackfull()) || (stu.P1 == Day3 && D3.stackfull()))&&(stu.P2=="1")&&(stu.P3=="1")))
            {
                //cout<<"stackful::"<<stu.Id<<endl;
                unassigned.push(stu.Id);
                return false;
            }

            else if(stu.P2=="1" && stu.P3=="1"){
                   // cout<<"0::"<<stu.Id<<endl;
                if(stu.P1==Day1)
                D1.push(stu.Id);
                if(stu.P1==Day2)
                D2.push(stu.Id);
                if(stu.P1==Day3)
                D3.push(stu.Id);
                return true;
            }
            //insert 1st preference
            else if(((stu.P1 == Day1 && (~D1.stackfull())) || (stu.P1 == Day2 && (~D2.stackfull())) || (stu.P1 == Day3 && (~D3.stackfull())))
                     &&((stu.P2 == Day1 && D1.stackfull()) || (stu.P2 == Day2 && D2.stackfull()) || (stu.P2 == Day3 && D3.stackfull()))
                    &&((stu.P3=="1")||((stu.P3 == Day1 && D1.stackfull()) || (stu.P3 == Day2 && D2.stackfull()) || (stu.P3 == Day3 && D3.stackfull()))))
                     {
                        //cout<<"1  "<<stu.Id<<endl;
                        if(stu.P1==Day1)
                        D1.push(stu.Id);
                        if(stu.P1==Day2)
                        D2.push(stu.Id);
                        if(stu.P1==Day3)
                        D3.push(stu.Id);

                     }
             //insert 2nd preference
             else if(((stu.P1 == Day1 && D1.stackfull()) || (stu.P1 == Day2 && D2.stackfull()) || (stu.P1 == Day3 && D3.stackfull()))
                     &&((stu.P2 == Day1 && (~D1.stackfull())) || (stu.P2 == Day2 && (~D2.stackfull())) || (stu.P2 == Day3 && (~D3.stackfull())))
                        &&((stu.P3=="1")||(stu.P3 == Day1 && D1.stackfull()) || (stu.P3 == Day2 && D2.stackfull()) || (stu.P3 == Day3 && D3.stackfull())))

                     {
                          //cout<<"2 "<<stu.Id<<endl;
                        if(stu.P2==Day1)
                        D1.push(stu.Id);
                        if(stu.P2==Day2)
                        D2.push(stu.Id);
                        if(stu.P2==Day3)
                        D3.push(stu.Id);

                     }
              //insert 3rd preference
              else if(((stu.P1 == Day1 && D1.stackfull()) || (stu.P1 == Day2 && D2.stackfull()) || (stu.P1 == Day3 && D3.stackfull()))
                     &&((stu.P2 == Day1 && D1.stackfull()) || (stu.P2 == Day2 && D2.stackfull()) || (stu.P2 == Day3 && D3.stackfull()))
                     &&((stu.P3 == Day1 && (~D1.stackfull())) || (stu.P3 == Day2 && (~D2.stackfull())) || (stu.P3 == Day3 && (~D3.stackfull()))))
                     {
                          //cout<<"3  "<<stu.Id<<endl;
                        if(stu.P3==Day1)
                        D1.push(stu.Id);
                        if(stu.P3==Day2)
                        D2.push(stu.Id);
                        if(stu.P3==Day3)
                        D3.push(stu.Id);
                     }
            else{
                 //cout<<"else  "<<stu.Id<<endl;
                return false;
            }
            return true;
}

int main()
{
    string G1;
    string G2;
    string G3;
    string G4 = "Unassigned: ";
    string Day1;
    string Day2;
    string Day3;
    string limit1;
    string limit2;
    string limit3;
    int mylimit1;
    int mylimit2;
    int mylimit3;
    int studentnumber;

    ofstream outputtxt;


    ifstream inputtxt;
    inputtxt.open("preferences.txt");
    string x;
    string* output;
    output = new string[20];
    ifstream myFile("preferences.txt");
    std::size_t numberoflines = 0;
    std::string line;
    while (std::getline(myFile, line))
        ++numberoflines;
    inputtxt >> noskipws;
    int index1[numberoflines];
    int index2[numberoflines];
    int index3[numberoflines];
    if (inputtxt.is_open()) {
        //erase spaces
        for (int i=0; getline(inputtxt, x)&&i<numberoflines; i++) {
                x.erase(std::remove(x.begin(), x.end(), ' '), x.end());
                output[i]= x;
                //cout <<output[i] << endl;

        }

            //find indices
           for (int i = 0; i < numberoflines; i++) {
               index1[i] = output[i].find(",");
               index2[i] = output[i].find(",",index1[i]+1);
               //index3[i] = output[i].find_last_of(",");
               index3[i] = output[i].find(",", 6);


             // cout << index3[i] <<endl;
           }
           //indicate days and limits
           Day1 = output[0].substr(0, index1[0]);
           Day2 = output[1].substr(0, index1[0]);
           Day3 = output[2].substr(0, index1[0]);
           limit1 = output[0].substr(index1[0] + 1);
           limit2 = output[1].substr(index1[0] + 1);
           limit3 = output[2].substr(index1[0] + 1);
           //convert to int
           mylimit1 = stoi(limit1);
           mylimit2 = stoi(limit2);
           mylimit3 = stoi(limit3);

        inputtxt.close();

    }
    //declaraiton of student objects
   Student stu[numberoflines-3];
    for(int k=3; k< numberoflines ; k++){
        stu[k-3].Id = output[k].substr(0, index1[k]);
        stu[k-3].P1 = output[k].substr(index1[k] + 1,1);
        stu[k-3].P2 = output[k].substr(index2[k] + 1,1);
        stu[k-3].P3 = output[k].substr(index3[k] + 1,1);
        studentnumber++;

    }
    //declaraiton of stacks and queue
    Stack<string> D1(mylimit1);
    Stack<string> D2(mylimit2);
    Stack<string> D3(mylimit3);
    Stack<string> unassigned(studentnumber);
    Queue<Student> Que(studentnumber);

        for(int j=0; j < studentnumber; j++){

            //if stu[i] can go to the stack
            if(check(stu[j],Day1,Day2,Day3,D1,D2,D3,unassigned))
            {

                for(int i = 0;i<Que.Qlength();i++)
                {

                    Student temp = Que.Qdelete();
                    //cout<<"Qdlt: "<<temp.Id<<endl;
                    //if temp can go to the stack
                    if(check(temp,Day1,Day2,Day3,D1,D2,D3,unassigned))
                    {
                        // queue reset
                        for(int k = i;k<Que.Qlength();k++)
                        {
                            Student temp2=Que.Qdelete();
                            Que.Qadd(temp2);
                            //cout << "WWW: " << temp2.Id<<endl;
                        }
                        i=0;
                    }
                    else
                        {
                            Que.Qadd(temp);
                            //cout<<"Qaddedin: "<<temp.Id<<endl;
                        }
                }
            }


           else{
                Que.Qadd(stu[j]);
                //cout<<"Qaddedouter: "<<stu[j].Id<<endl;
            }
        }


        for(int i=0;i<Que.Qlength();i++)
        {
            Student temp = Que.Qdelete();
                if(((temp.P1 == Day1 && (~D1.stackfull())) || (temp.P1 == Day2 && (~D2.stackfull())) || (temp.P1 == Day3 && (~D3.stackfull()))))
                        D1.push(temp.Id);
                else if((temp.P2 == Day1 && (~D1.stackfull())) || (temp.P2 == Day2 && (~D2.stackfull())) || (temp.P2 == Day3 && (~D3.stackfull())))
                        D2.push(temp.Id);
                else if((temp.P3 == Day1 && (~D1.stackfull())) || (temp.P3 == Day2 && (~D2.stackfull())) || (temp.P3 == Day3 && (~D3.stackfull())))
                        D3.push(temp.Id);


                for(int j=0;j<Que.Qlength();j++)
                {
                    Student temp2 = Que.Qdelete();
                    if(check(temp2,Day1,Day2,Day3,D1,D2,D3,unassigned))
                    {
                        for(int k = j;k<Que.Qlength();k++)
                        {
                            Student temp2=Que.Qdelete();
                            Que.Qadd(temp2);
                            //cout << "qqq: " << temp2.Id<<endl;
                        }
                        j=0;
                    }
                    else
                        {
                            Que.Qadd(temp2 );
                            //cout<<"QQQ: "<<temp.Id<<endl;
                        }

                }

        }
        Student temp2 = Que.Qdelete();
        unassigned.push(temp2.Id);
        if (Day1 == "F") G1 = "Friday:"; else if (Day1 == "T")  G1 = "Thursday:"; else if (Day1 == "W")  G1 = "Wednesday:";
        if (Day2 == "F") G2 = "Friday:"; else if (Day2 == "T")  G2 = "Thursday:"; else if (Day2 == "W")  G2 = "Wednesday:";
        if (Day3 == "F") G3 = "Friday:"; else if (Day3 == "T")  G3 = "Thursday:"; else if (Day3 == "W")  G3 = "Wednesday:";

    outputtxt.open("results.txt");
    outputtxt << G1 <<  endl;
    while (!D1.stackempty()) {

        outputtxt << D1.pop() << endl;
    }
    outputtxt << G2 << endl;
    while (!D2.stackempty()) {
        outputtxt << D2.pop() << endl;
    }
    outputtxt << G3 << endl;
    while (!D3.stackempty()) {
        outputtxt << D3.pop() << endl;
    }
    outputtxt << "Unassigned:" << endl;
    while (!unassigned.stackempty()) {
        outputtxt << unassigned.pop() << endl;
    }



    outputtxt.close();

    /*
    while (!D1.stackempty()) {
        cout << G1 << " " << D1.pop() << endl;    }
    while (!D2.stackempty()) {
        cout << G2 << " " << D2.pop() << endl;
    }
    while (!D3.stackempty()) {
        cout << G3 << " " << D3.pop() << endl;
    }
    while (!unassigned.stackempty()) {
        cout << G4 << unassigned.pop() << endl;
    }
    */
    return 0;
}


