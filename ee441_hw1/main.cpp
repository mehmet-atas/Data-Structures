#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Student{
private:
    int Id;
    string Name;
    string Surname;
    int *Quiz_scores;
    int *Hw_scores;
    int Final_scores;
public:
    Student(int id, string name, string surname);
    Student(){}
    ~Student();
    void set_id(int id);
    int get_id();
    void set_name(string name);
    string get_name() ;
    void set_surname(string surname);
    string get_surname();
    void set_quiz_scores(int* quiz_scores);
    int *get_quiz_scores() ;
    void set_hw_scores(int* hw_scores);
    int *get_hw_scores() ;
    void set_final_scores(int final_scores);
    int get_final_scores() ;

    int overallCourseScore(int weightQ,int weightHW, int weightF)
    {
        int quizTotal=0,hwTotal=0;
        for(int i=0;i<4;i++)
            quizTotal+=Quiz_scores[i]/4;
        for(int i=0;i<3;i++)
            hwTotal+=Hw_scores[i]/3;
        return (quizTotal*weightQ + hwTotal*weightHW + Final_scores*weightF)/100.0;
    }

};
class Course{
private:
    Student students[10];
    int num;
    int weightQ;
    int weightHW;
    int weightF;
public:
    Course(int Qweight=30,int HWweight=30,int Fweight=40)
    {
        num=0;
        weightQ=Qweight;
        weightHW=HWweight;
        weightF=Fweight;
    }
    Student * getStudents()
    {
        return students;
    }
    int getWeightQ()
    {
        return weightQ;
    }
    int getWeightHW()
    {
        return weightHW;
    }
    int getWeightFin()
    {
        return weightF;
    }
    void setWeights(int q,int hw,int f)
    {
        weightQ=q;
        weightHW=hw;
        weightF=f;
    }

    int getNum()
    {
        return num;
    }
    //created and added new student to the Student array and returned pointer of created one.
    Student* addNewStudent(int id, string name, string surname)
    {
        if(num>10)
            cout<<"Number of students in class cant be exceed 10!"<<endl;

        students[num]=Student( id,  name,  surname);
        num++;
        return &students[num-1];

    }
    void updateWeights(int Qweight,int HWweight,int Fweight)
    {
        weightQ=Qweight;
        weightHW=HWweight;
        weightF=Fweight;
    }
    //search through the Student array if find appropriate one return pointer of that. Else return null
    Student* getStudentInfo(int id)
    {
        for(int i=0;i<num;i++)
            if(students[i].get_id()==id)
                return &students[i];
        return NULL;
    }
    float calculateAverageQuiz()
    {
        float quizTotal=0,quizTemp=0;
        for(int i=0;i<num;i++)
        {
            for(int j=0;j<4;j++)
                quizTemp+=(students[i].get_quiz_scores())[j]/4.0;
            quizTotal+=quizTemp;
            quizTemp=0;
        }
        return quizTotal/num;
    }

    float calculateAverageHW()
    {
        float quizTotal=0,quizTemp=0;
        for(int i=0;i<num;i++)
        {
            for(int j=0;j<3;j++)
                quizTemp+=students[i].get_hw_scores()[j]/3.0;
            quizTotal+=quizTemp;
            quizTemp=0;
        }
        return quizTotal/num;
    }
    float calculateAverageFinal()
    {
        float quizTotal=0;
        for(int i=0;i<num;i++)
        {
            quizTotal+=students[i].get_final_scores();
        }
        return quizTotal/(float)num;
    }
    float calculateAverageOverall()
    {
        return (weightQ*calculateAverageQuiz()+weightHW*calculateAverageHW()+weightF*calculateAverageFinal())/100.0;
    }

};

//globally defined to make it reachable in functions
Course course=Course();

//uses Class Course's member function to add new student. Returns pointer to the added student.
Student* addNewStudent(int id, string name,string surname)
{
    return course.addNewStudent(id,name,surname);
}

//finds student pointer based on its id and prints needed infos.
void showStudent(int id)
{
    Student *temp=course.getStudentInfo(id);
    if(temp!=NULL)
    cout<<temp->get_id()<<" "<<temp->get_name()<<" "<<temp->get_surname()<<" "<<temp->get_quiz_scores()[0]<< " "
        << temp->get_quiz_scores()[1]<<" "<<temp->get_quiz_scores()[2]<<" "<<temp->get_quiz_scores()[3]<<" "<<temp->get_hw_scores()[0]<< " "
        << temp->get_hw_scores()[1] << " "<<temp->get_hw_scores()[2]<<" "<<temp->get_final_scores()<<endl;
    else
        cout<<"invalid id."<<endl;

}

//finds student pointer based on its id and edits scores using setters.
void changeStudentScores(int id, int* quiz_scores, int *hw_scores, int final_score)
{
    Student *temp=course.getStudentInfo(id);
    temp->set_quiz_scores(quiz_scores);
    temp->set_hw_scores(hw_scores);
    temp->set_final_scores(final_score);
}

 void changeWeights(int weightQ, int weightHW, int weightF)
 {
     course.setWeights(weightQ,weightHW,weightF);
 }
 void showAverage()
 {
     cout<<fixed << setprecision(2)<<"Quizzes Average: "<<course.calculateAverageQuiz()<<" HWs Average: "<< course.calculateAverageHW()
     <<" Final Average: "<<course.calculateAverageFinal()<<" Overall: "<<course.calculateAverageOverall()<<endl;
 }

void printStudent(Student* temp)
{
     cout<<temp->get_id()<<" "<<temp->get_name()<<" "<<temp->get_surname()<<" "<<temp->get_quiz_scores()[0]<< " "
        << temp->get_quiz_scores()[1]<<" "<<temp->get_quiz_scores()[2]<<" "<<temp->get_quiz_scores()[3]<<" "<<temp->get_hw_scores()[0]<< " "
        << temp->get_hw_scores()[1] << " "<<temp->get_hw_scores()[2]<<" "<<temp->get_final_scores()<<endl;

}

//traverses the student array of course object and print student infos according to the given threshold.
void showAbove(int threshold)
{
    for(int i=0;i<course.getNum();i++)
    {
        if(course.getStudents()[i].overallCourseScore(course.getWeightQ(),course.getWeightHW(),course.getWeightFin())>threshold)
        {
            printStudent(&course.getStudents()[i]);
        }
    }
}
//traverses the student array of course object and print student infos according to the given threshold.
void showBelow(int threshold)
{
    for(int i=0;i<course.getNum();i++)
    {
        if(course.getStudents()[i].overallCourseScore(course.getWeightQ(),course.getWeightHW(),course.getWeightFin())<threshold)
        {
            printStudent(&course.getStudents()[i]);
        }
    }
}
int main()
{
    int option;
    cout << "1. Add student" << endl;
    cout << "2. Search a student by ID" << endl;
    cout << "3. Change a student’s score" << endl;
    cout << "4. Update weights" << endl;
    cout << "5. Show classroom average" << endl;
    cout << "6. Show students with overall score above a threshold" << endl;
    cout << "7. Show students with overall score below a threshold" << endl;
    cout << "8. Exit" << endl<<endl;
    cout << "Enter your option:" << endl;
    cin>>option;
    while(option!=8)
    {
        switch(option)
        {
        case 1:
        {
            int id,fin;
            int quizScores[4];
            int hwScores[3];
            string name,surname;
            cout<<"Enter student's ID, name, surname and scores (quizzes, homeworks, final)"<<endl;

            cin>>id>>name>>surname>>quizScores[0]>>quizScores[1]>>quizScores[2]>>quizScores[3]>>hwScores[0]>>hwScores[1]>>hwScores[2]>>fin;

            while(quizScores[0]>100 ||quizScores[1]>100 || quizScores[2]>100|| quizScores[3]>100 ||hwScores[0]>100 || hwScores[1]>100 || hwScores[2]>100 || fin>100 )
            {
                cout<<"Values cannot be higher than 100."<<endl;
                cout<<"Enter student's ID, name, surname and scores (quizzes, homeworks, final)"<<endl;
                cin>>id>>name>>surname>>quizScores[0]>>quizScores[1]>>quizScores[2]>>quizScores[3]>>hwScores[0]>>hwScores[1]>>hwScores[2]>>fin;

            }
            while(quizScores[0]<0 ||quizScores[1]<0 || quizScores[2]<0 || quizScores[3]<0 ||hwScores[0]<0 || hwScores[1]<0 || hwScores[2]<0 || fin<0 )
            {
                cout<<"Values cannot be negative."<<endl;
                cout<<"Enter student's ID, name, surname and scores (quizzes, homeworks, final)"<<endl;
                cin>>id>>name>>surname>>quizScores[0]>>quizScores[1]>>quizScores[2]>>quizScores[3]>>hwScores[0]>>hwScores[1]>>hwScores[2]>>fin;

            }
            Student* student=addNewStudent(id,name,surname);
            student->set_quiz_scores(quizScores);
            student->set_hw_scores(hwScores);
            student->set_final_scores(fin);
            break;
        }
        case 2:
        {
            cout<<"Enter student ID"<<endl;
            int id;
            cin>>id;
            showStudent(id);
            break;
        }
        case 3:
        {
            int id,fin;
            int quizScores[4];
            int hwScores[3];
            cout<< "enter id, quiz scores, hw scores, final score"<<endl;
            cin>>id>>quizScores[0]>>quizScores[1]>>quizScores[2]>>quizScores[3]>>hwScores[0]>>hwScores[1]>>hwScores[2]>>fin;
            changeStudentScores(id,quizScores,hwScores,fin);
            break;
        }
        case 4:
        {
            int weightQ,weightHW,weightF;
            cout<<"Enter weights.."<<endl;
            cin>>weightQ>>weightHW>>weightF;
            changeWeights(weightQ, weightHW, weightF);
            break;
        }
        case 5:
            showAverage();
            break;
        case 6:
        {
            int threshold;
            cout<<"Enter a threshold."<<endl;
            cin>>threshold;
            showAbove(threshold);
            break;
        }
        case 7:
        {
            int threshold;
            cout<<"Enter a threshold."<<endl;
            cin>>threshold;
            showBelow(threshold);
            break;
        }
        default:
            cout<<"Please select 1-8."<<endl;
        }

        cout << "Enter your option:" << endl;
        cin.clear();
fflush(stdin);
        cin>>option;
    }
    cout << "Program closed." << endl;
    return 0;
}

Student::Student(int id, string name, string surname){
    Id=id;
    Name=name;
    Surname=surname;
    Final_scores=0;
    Quiz_scores=new int[4];
    Hw_scores=new int[3];
    for(int i=0;i<4;i++)
        Quiz_scores[i]=0;
    for(int i=0;i<3;i++)
        Hw_scores[i]=0;


}
Student::~Student()
{
    delete [] Quiz_scores;
    delete [] Hw_scores;
}

void Student::set_id(int id){Id=id;}
int Student::get_id(){return Id;}
void Student::set_name(string name){Name=name;}
string Student::get_name(){return Name;}
void Student::set_surname(string surname){Surname=surname;}
string Student::get_surname(){return Surname;}

void Student::set_quiz_scores(int *quiz_scores)
{
    for(int i=0;i<4;i++)
    {
        Quiz_scores[i]=quiz_scores[i];
    }
}
int* Student::get_quiz_scores(){return Quiz_scores;}

void Student::set_hw_scores(int *hw_scores){
    for(int i=0;i<4;i++)
    {
        Hw_scores[i]=hw_scores[i];
    }
}

int *Student::get_hw_scores(){return Hw_scores;}


void Student::set_final_scores(int final_scores){Final_scores=final_scores;}
int Student::get_final_scores(){return Final_scores;}


