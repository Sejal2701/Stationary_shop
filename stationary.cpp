#include <iostream>
#include <conio.h>         //for getch
#include <unistd.h>        //for sleep
#include <stdlib.h>        //for system()  pause and clr
#include <iomanip>         //setw to set space for table
#include <windows.h>       //for setting color for backgroung and foreground
#include <fstream>         //File handling
using namespace std;
void Bill();

class shop
{
    protected:
    string name;
};

void setConsoleColor(WORD c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

class admin:public shop
{
    int id;
    string password="default";

    public:
    admin(int i,string n)                   //parameterized constructor
    {
        id=i;
        name=n;
    }

    void displayName()
    {
        cout<<name;
    }

    int dispalyID()
    {
        return id;
    }

    bool verify(string pass)
    {
        return pass==password;
    }
};

bool check(string email)
{
    if (!isalpha(email[0])) 
    {
        return 0;
    }
    int At = -1, Dot = -1;
    for (int i = 0;i < email.length(); i++) 
    {
        if (email[i] == '@') 
        {  
            At = i;
        }
        else if (email[i] == '.') 
        {
            Dot = i;
        }
    }
  
    if (At == -1 || Dot == -1 || At > Dot|| Dot>=(email.length() - 1))
    {return 0;}
    return 1;
}

bool checkID(string id)
{
    string file_name=id+".txt";
    ifstream File;
    File.open(file_name);
    if(File)
    {
        File.close();
        return true;
    }    
    else
    {
        return false;
    }
}

class customer:public shop
{
    string phone;
    string mail;

    public:
    customer(string n,string p,string m)
    {
        name=n;
        phone=p; 
        mail=m;
    }

    customer()
    {}

    void displayName()
    {
        cout<<name;
    }

    friend void Bill();             //friend function
};

class records
{
    protected:
    double profit;
    public:
    void show()
    {
        ifstream rec; 
        rec.open("records.txt");
        if(!rec)
        {
            cout<<"\n\t\t\tPROFIT = 0";
        }
        else
        {
            system("CLS");
            rec>>profit;
            cout<<"\n\t\t\tTOTAL PROFIT : "<<profit<<endl;
            system("pause");
            rec.close();
        }
    }
};

class product:public virtual records           //virtual function
{
    public:
        string name;
        int quantity;
        string id;
        double percost;
        double persell;
        
        void file();
        void get();

};

void product::get()
{
    int s;
    system("CLS");
    cout<<"\n\t\t\tNumber of products to be entered : ";
    cin>>s;
    for(int i=0;i<s;i++)
    {
        cout<<"\n\n\t\t\tInput product id : ";
        cin>>id;
        string file_name=id+".txt";
        fstream File;
        File.open(file_name);
        if(!File)
        {
            cout<<"\t\t\tInput product name : ";
            cin>>name;
            cout<<"\t\t\tInput cost price of product : ";
            cin>>percost;
            cout<<"\t\t\tInput selling price of product : ";
            cin>>persell;
            cout<<"\t\t\tTotal product quantity : ";
            cin>>quantity;
            cout<<"\nProduct is added.."<<endl;
            system("pause");
            file();
        }
        else
        {
            cout<<"\n\t\t\tId already exists"<<endl;
            sleep(1);
        }
        File.close();
    }
}

void product::file()
{
    string file_name;
    file_name=id;
    file_name=file_name+".txt";
    ofstream File;
    File.open(file_name,ios::out);
    File<<"\nProduct name: "<<product::name<<"\nProduct id: "<<id<<"\nProduct cost price: "<<percost<<"\nProduct sell price: "<<persell<<"\nProduct quantity: "<<quantity<<endl;
    File.close();
}

class staff:public virtual records
{
    protected:
    double salary;
    string name;
    string emp_id;
    product x;                                //containership

    void getstaff()
    {
        system("CLS");
        cout<<"\n\t\t\tEnter employee id: ";
        cin>>emp_id;
        string file_name=emp_id+".txt";
        fstream File;
        File.open(file_name);
        if(!File)
        {
            cout<<"\t\t\tEnter first name: ";
            cin>>name;
            cout<<"\t\t\tInput salary: ";
            cin>>salary;
            cout<<"\nEmployee details are added..\n";
            system("pause");
            file();
        }
        else
        {
            cout<<"\t\t\tId already exists"<<endl;
            sleep(1);
        }
        File.close();
    }
    void file();
};


void staff::file()
{
    string file_name;
    file_name=emp_id+".txt";
    ofstream File;
    File.open(file_name,ios::out);
    File<<"\nEmployee name: "<<name<<"\nEmployee id: "<<emp_id<<"\nEmployee salary: "<<salary<<endl;
    File.close();
}

class update:public staff,public product
{
    public:
    void add();
    void update_product();
    void update_emp();
};

void update::add()
{
    int s;
    string name;
    while(1)
    {
        system("CLS");
        cout<<"\n\n\t\t\t1. Input for product\n\t\t\t2. Input for employee\n\t\t\t3. Exit\n\n\t\t\tSelect your choice: ";
        cin>>s;
        if(s==1)
        {
            get();
        }
        else if(s==2)
        {
            getstaff();
        }
        else if(s==3)
        {
            break;
        }
        else
        {
            cout<<"\n\t\t\tEnter valid option."<<endl;
            sleep(1);
        }
    }
}

void update::update_product()
{
    string id;
    system("CLS");
    cout<<"\n\t\t\tEnter product id to update: ";
    cin>>id;
    string file_name=id+".txt";
    fstream File(file_name);
    if(!File)
    {
        cout<<"\n\t\t\tNo such ID exists"<<endl;
        sleep(1);
    }
    else
    {
        cout<<"\n\t\t\tFile found!!"<<endl;
        cout<<"\t\t\tUpdate product name: ";
        cin>>product::name;
        cout<<"\t\t\tUpdate cost price of product: ";
        cin>>percost;
        cout<<"\t\t\tUpdate sell price of product: ";
        cin>>persell;
        cout<<"\t\t\tUpdate product quantity: ";
        cin>>quantity;
        cout<<"\nProduct details are updated..\n";
        system("pause");
        profit=profit+(persell-percost)*(quantity);
        File<<"\nProduct name: "<<product::name<<"\nProduct id: "<<id<<"\nProduct cost price: "<<percost<<"\nProduct sell price: "<<persell<<"\nProduct quantity: "<<quantity<<endl;
        File.close();
    }
}

void update::update_emp()
{
    string id;
    system("CLS");
    cout<<endl<<"\t\t\tEnter employee ID to modify: ";
    cin>>id;
    string file_name;
    file_name=id+".txt";
    fstream File;
    File.open(file_name);
    if(!File)
    {
        cout<<"\n\t\t\tNo such ID exists"<<endl;
        sleep(1);
    }
    else
    {
        cout<<"\t\t\tUpdate Employee's first name: ";
        cin>>staff::name;
        cout<<"\t\t\tUpdate employee salaray: ";
        cin>>salary;
        cout<<"\nEmployee details are added..\n";
        system("pause");
        File<<"Employee id: "<<id<<"\nEmployee name: "<<staff::name<<"\nEmployee salary: "<<salary<<endl;
        File.close();
    }
}

class Node
{
    public: 
    pair<string,int> data;
    Node* next;

    Node()
    {
        next=NULL;
    }
};

int checkStock(string id,int quan)
{   
    fstream file;
    string word,filename;
  
    filename = id+".txt";
  
    file.open(filename);
  
    while(word!="quantity:")
    {
        file >> word;
    }
    file>>word;
    int ans=stoi(word);
    int final=min(quan,ans);
    file.close();

    fstream file2;
    string filename2;
    filename2 = id+".txt";  
    file2.open(filename2);
    string strReplace="quantity:";
    string strTemp;
    int tw=ans-final;
    string t=to_string(tw)+"\n";
    while(file2 >> strTemp)
    {
        if(strTemp == strReplace)
        {
            break;
        }
    }
    file2<<t;
    file2.close();
    return final;
}


Node* Getlist()
{
    cout<<"\n\t\t\t\e[1mEnter q to end the list....\e[0m"<<endl;
    Node* head=NULL;
    Node* tail=NULL;
    string ids;
    while(ids!="q")
    {
        cout<<"\n\t\t\tEnter the id of item: ";
        cin>>ids;
        if(ids=="q")
        {break;}
        if(!checkID(ids))
        {
            cout<<"\t\t\tId dosen't exist"<<endl;
            sleep(1);
        }
        else
        {
            Node* newNode=new Node;
            newNode->data.first=ids;
            cout<<"\t\t\tEnter quantity of the item: ";
            int quan;
            cin>>quan;
            int max=checkStock(ids,quan);
            if(max<quan)
            {
                cout<<"\n\t\t\tOnly "<<max<<" in stock."<<endl;
            }
            newNode->data.second=max;
            
            if(head==NULL)
            {
                head=newNode;
                tail=newNode;
            }
            else
            {
                tail->next=newNode;
                tail=newNode;
            }
        }
    }
    if(ids=="q")
    {
        cout<<"\n\t\t\tWrapping up your bill "<<endl<<endl<<endl;
        sleep(1);
    }
    return head;
}

string findName(string id)
{
    fstream file;
    string word,filename;
  
    filename = id+".txt";
    file.open(filename);
  
    while (file >> word)
    {
        if(word=="name:")
        {break;}
    }
    file>>word;
    return word;
}

double findCPrice(string id)
{
    fstream file;
    string word,filename;
  
    filename = id+".txt";
    file.open(filename);
  
    while (file >> word)
    {
        if(word=="cost")
        {break;}
    }
    file>>word;
    file>>word;
    double ans=stod(word);
    file.close();
    return ans;
}

double findPrice(string id)
{
    fstream file;
    string word,filename;
    
    filename=id+".txt";
    file.open(filename);
  
    while (file >> word)
    {
        if(word=="sell")
        {break;}
    }
    file>>word;
    file>>word;
    double ans=stod(word);
    file.close();
    return ans;
}

double GetBill(Node* head)
{
    double total=0;
    Node* temp=head;
    while(temp!=NULL)
    {
        string id=temp->data.first;
        double price=findPrice(id);
        total+=price*(temp->data.second);
        temp=temp->next;
    }
    return total;
}

void Bill()
{
    customer c;
    setConsoleColor(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_BLUE);
    system("CLS");
    cout<<"\n\n\t\t\t\e[1mCustomer Details\e[0m"<<endl;
    cout<<"\t\t\tEnter customer name: ";
    cin>>c.name;
    while(1)
    {
        cout<<"\t\t\tEnter customer mail: ";
        string mail;
        cin>>mail;
        if(check(mail))
        {
            c.mail=mail;
            break;
        }
        else
        {
            cout<<"\t\t\tEnter valid mail address \n\n"<<endl;
        }
    }
    cout<<"\t\t\tEnter phone number: ";
    cin>>c.phone;

    string file_name=c.phone+".txt";
    fstream File;
    File.open(file_name);
    if(!File)
    {
        ofstream file_new;
        file_new.open(file_name,ios::out);
        file_new<<"Customer name:"<<c.name<<"\nCustomer mail: "<<c.mail<<"\nCustomer phone number: "<<c.phone;  
        file_new.close();       
    }
    Node* head=Getlist();
    double ans=GetBill(head);
    File.close();
    cout<<endl;
    system("CLS");
    setConsoleColor(BACKGROUND_BLUE|BACKGROUND_GREEN);
    cout<<"\e[1m----------------------------------";
    setConsoleColor(7);
    cout<<"\e[1m  Bill  \e[0m";
    setConsoleColor(BACKGROUND_BLUE|BACKGROUND_GREEN);
    cout<<"------------------------------------\e[0m"<<endl;
    setConsoleColor(7);
    cout<<left<<setw(60)<<"\e[1mItem Name\e[0m"<<left<<setw(25)<<"\e[1mPrice\e[0m"<<left<<setw(25)<<"\e[1mQuantity\e[0m"<<""<<endl;
    Node* temp2=head;
    double p=0;
    while(temp2!=NULL)
    {   
        p+=(findPrice(temp2->data.first)-findCPrice(temp2->data.first))*(temp2->data.second);
        cout<<left<<setw(53)<<findName(temp2->data.first)<<left<<setw(18)<<findPrice(temp2->data.first)<<left<<setw(18)<<temp2->data.second;
        cout<<endl;
        temp2=temp2->next;
    }
    double oldP;
    ifstream ProfitFile;
    ProfitFile.open("records.txt");
    if(!ProfitFile)
    {
        oldP=0;
    }
    else
    {
        ProfitFile>>oldP;
        p+=oldP;
        ProfitFile.close();
    }
    ofstream PFile;
    PFile.open("records.txt");
    PFile<<p;
    PFile.close();
    cout<<endl<<endl;
    cout<<"\n\t\t\t\e[1mThank you for shopping with us!!\e[0m"<<endl;
    cout<<"\t\t\t\e[1mPlease visit again!!\e[0m"<<endl;
    cout<<endl<<endl;
    setConsoleColor(FOREGROUND_GREEN);
    cout<<"\t\t\t\e[1mTotal Bill : Rs. "<<ans<<"\e[0m"<<endl;
    cout<<"..........................................................................."<<endl<<endl<<endl;
    system("pause");
}

void systemD()
{
    while(1)
    {
        setConsoleColor(FOREGROUND_BLUE|FOREGROUND_GREEN);
        system("CLS");
        cout<<"\n\e[1m**************************** WELCOME ***************************\e[0m";
        cout<<"\n\t\t\t1. Add Entries\n\t\t\t2. Modify details\n\t\t\t3. Search details\n\t\t\t4. Show profit\n\t\t\t5. Generate Bill\n\t\t\t6. Exit"<<endl<<endl;
        cout<<"\n\t\t\tSelect your choice : ";
        int c;
        cin>>c;
        setConsoleColor(7);
            if(c==1)
            {
                update a ;
                a.add();
            }
            else if(c==2)       
            {
                system("CLS");
                cout<<"\n\n\n\t\t\t1. Modify employee details\n\t\t\t2. Modify product details"<<endl<<endl;
                cout<<"\n\t\t\tEnter your choice : ";
                int w;
                cin>>w;
                if(w==1)
                {
                    update a;
                    a.update_emp();
                }
                else if(w==2)
                {
                    update a;
                    a.update_product();
                }
                else
                {
                    cout<<"\n\t\t\tEnter valid choice..\n";
                    sleep(1);
                }
            }
            else if(c==3)
            {
                string id;
                system("CLS");
                cout<<"\n\t\t\tEnter id to be searched: ";
                cin>>id;
                string file_name;
                file_name=id+".txt";
                ifstream File;
                File.open(file_name,ios::in);
                if(!File)
                {
                    cout<<"\n\t\t\tID not found."<<endl;
                    sleep(1);
                }
                else
                {
                    cout<<endl;
                    while(File)
                    {
                        char c;
                        File.get(c);
                        cout<<c;
                    }
                    system("pause");
                }
                File.close();
            }
            else if(c==4)
            {
                update a;
                a.show();
                cout<<endl;
            }
            else if(c==5)
            {
                Bill();
            }
            else if(c==6)
            {
                break;
            }
            else
            {
                cout<<"\n\n#######------------------Enter valid choice-----------------#######"<<endl<<endl<<endl;
                sleep(1);
            }
        
    }
}

int main()
{
    admin Owner(21103137,"Admin");
    int id;
    cout<<"\nAdmin, Enter your id - ";
    cin>>id;
    if(Owner.dispalyID()!=id)
    {
        cout<<"Wrong id entered.."<<endl<<endl;
        return 0;
    } 
        bool flag=true;
        for(int i=0;i<3;i++)
        {
            string pass ="";
            char ch;
            cout << "Enter pass\n";
            ch = _getch();
            while(ch != 13)
            {
                //character 13 is enter
                pass.push_back(ch);
                cout << '*';
                ch = _getch();
            }
        
            if(Owner.verify(pass))
            {
                cout<<"\n\nWelcome ";
                Owner.displayName();
                cout<<endl;
                flag=false;
                break;
            }
            else
            {
                cout<<"\n\nWrong password entered... "<<endl;
            }
        }
        if(flag==true)
        {
            cout<<"Many login attempts failed"<<endl;
            return 0;
        } 
        else
        {
            system("pause");
        }
    
    while(1)
    {
        system("CLS");
        setConsoleColor(BACKGROUND_BLUE|BACKGROUND_GREEN);
        cout<<"\n-----------------------";
        setConsoleColor(FOREGROUND_BLUE);
        cout<<"\e[1m Welcome to the shop \e[0m";
        setConsoleColor(BACKGROUND_BLUE|BACKGROUND_GREEN);
        cout<<"------------------------";
        setConsoleColor(7);
        cout<<endl;
        cout<<"\n\t\t\t1. USE THE SYSTEM \n\t\t\t2. EXIT"<<endl;
        cout<<"\n\t\t\tENTER YOUR CHOICE : ";
        int s=0;
        cin>>s;
        switch(s)
        {
            case 1:
                systemD();
                break;

            case 2:
                setConsoleColor(FOREGROUND_RED|FOREGROUND_BLUE);
                cout<<"\n\e[1m.......................Hope you enjoyed the visit..............................\e[0m"<<endl;
                cout<<"\n============================ \e[1mExiting\e[0m ==================================="<<endl<<endl;
                return 0;
            
            default:
                cout<<"\n\n#######------------------Enter valid choice-----------------#######"<<endl<<endl<<endl;
                sleep(1);
                break;
        }
    }
}