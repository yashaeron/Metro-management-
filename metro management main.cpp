#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include<windows.h>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <fstream>
#include <conio.h>
#include<unistd.h>
#include <bits/stdc++.h>

using namespace std;

// Prototypes
int farecost=10;
class CreditCard;
class admin;
class station;
vector<admin> users;
vector<CreditCard> C;


int cost_calculation(station*, string, string);
void check_route(station*, string, string);
void customer_menu(station*);
int check_validity(long long);
void delCard();
void newCard();
admin *adminlogin();


class station {
    string station_name;
    int station_number;
public:
    static int count;
    station *next;
    station *previous;
    station()
    {
        cout << "Enter station name" << endl;
        cin >> station_name;
        count++;
        station_number = count;
        next = NULL;
        previous = NULL;
    }
    station(string n, int sn)
    {
        station_name = n;
        station_number = sn;
        count++;
        next = NULL;
        previous = NULL;
    }
    void printstat(){
        cout << "\t\t\t\t\tStation - " << endl;
            cout << "------------------------------------------------------------------" << endl;
            cout << "Station Number : " << station_number << endl;
            cout << "Station Name   : " << station_name << endl;
            cout << "------------------------------------------------------------------" << endl;
    }
    string getsName()
    {
        return station_name;
    }
    int getsNumber()
    {
        return station_number;
    }
    void IncreaseStationNumber()
    {
        station_number++;
    }
    void DecreaseStationNumber()
    {
        station_number--;
    }
};
int station::count = 0;


class CreditCard {
    string username;
    long long cred;
    float balance;

public:
    void create(string n, long long num, float bal)
    {
        cred = num;
        username = n;
        balance = bal;
    }
    void update_amount(string name, long long phone, string s1, string s2, int bill)
    {
        fstream tick;
        tick.open("ticket.txt", ios_base::app);
        cout << "CURRENT AMOUNT : " << balance << endl;
        cout << "CHARGES : " << bill << endl;
        if (bill > balance)
        {
            cout << "------------------------------------------------------------" << endl;
            cout << "NOT ENOUGH BALANCE IN ACCOUNT! PAYMENT FAILED!\n";
            cout << "------------------------------------------------------------" << endl;
            return;
        }
        balance -= bill;
        tick<<name<<endl<<phone<<endl<<s1<<endl<<s2<<endl<<"Card"<<endl<<bill<<endl;
        cout << "PAYMENT SUCCESSFULLY DONE! THANK YOU FOR USING NON-CONTACT METHOD OF PAYMENT." << endl;
        cout << endl<<"BALANCE LEFT : " << balance << endl;
        ofstream re;
        int counter = 0;
        re.open("creditCards.txt");
        for (CreditCard o : C)
        {
            if (counter != C.size() - 1)
            {
                re << o.info_name() << endl;
                re << o.info_cred() << endl;
                re << o.info_balance() << endl;
            }
            else
            {
                re << o.info_name() << endl;
                re << o.info_cred() << endl;
                re << o.info_balance();
            }
            counter++;
        }
        re.close();
        tick.close();
    }
    void printCred()
    {
        cout << "\t\t\t\t\tCREDIT CARD - " << endl;
        cout << "------------------------------------------------------------------" << endl;
        cout << "CARD HOLDER : " << username << endl;
        cout << "CREDIT CARD NUMBER : " << cred << endl;
        cout << "BALANCE : " << balance << endl;
        cout << "------------------------------------------------------------------" << endl;
    }

    void card_Recharge()
    {
        float recharge;
        cout << "ENTER AMOUNT TO BE TOPPED-UP : ";
        cin >> recharge;
        balance += recharge;
        cout << "CURRENT BALANCE : " << balance;
        ofstream re;
        re.open("creditCards.txt");
        int counter = 0;
        for (CreditCard o : C)
        {
            if (counter != C.size() - 1)
            {
                re << o.info_name() << endl;
                re << o.info_cred() << endl;
                re << o.info_balance() << endl;
            }
            else
            {
                re << o.info_name() << endl;
                re << o.info_cred() << endl;
                re << o.info_balance();
            }
            counter++;
        }
        re.close();
    }

    void check_balance()
    {
        cout << "BALANCE IN CARD IS : " << balance;
    }

    string info_name()
    {
        return username;
    }
    long long info_cred()
    {
        return cred;
    }
    float info_balance()
    {
        return balance;
    }
};


class admin {
    string username;
    string password;

public:
    void printStationDetails(station **list){
        station*temp=*list;
        while(temp!=NULL){
            temp->printstat();
            temp=temp->next;
        }
    }

    void printCardDetails(vector<CreditCard> C)
    {
        for (CreditCard temp : C)
        {
            temp.printCred();
        }
    }
    void setData(string n, string p)
    {
        username = n;
        password = p;
    }
    void newUser(vector<admin> &l)
    {

        admin obj;
        cout<<"-----------------------------------------------"<<endl;
        cout << "\nCREATING NEW USER...." << endl;
        cout << "ENTER USERNAME : ";
        cin >> username;
        string encryp;
        cout << "ENTER PASSWORD : ";
        cin >> encryp;
        password = encryp;
        for(admin o: l){
            string temp=o.username_info();
            if(temp==username){
                cout<<"-----------------------------------------------"<<endl;
                cout<<"userid already exists.....";
                sleep(2);
                system("cls");
                return;
            }
        }
        sleep(1);
        cout<<"-----------------------------------------------"<<endl;
        cout<<"New User added to the system....\n";
        cout<<"Press any key to continue...";
        getchar(); getchar();
        system("cls");

        obj.setData(username, password);
        l.push_back(obj);

        ofstream f2;
        f2.open("admins.txt");
        for (admin o : l)
        {
            f2 << o.username_info() << endl;
            f2 << o.password_info() << endl;
        }
        f2.close();

        /*ofstream f;
        f.open("ADMIN_INFO.dat", ios::binary | ios::app);

        f.write(reinterpret_cast<char *>(&obj), sizeof(admin));
        cout << "NEW USER SUCCESSFULLY CREATED! " << endl;
        cout << "DETAILS WILL BE REFLECTED WHEN PROGRAM IS RUN AGAIN!" << endl;
        f.close();*/
    }

    int check(string u, string p)
    {
        if (username == u && password == p)
        {
            return 1;
        }
        return 0;
    }

    void changePassword()
    {
        sleep(1);
        system("cls");

        string test;
        cout << "ENTER CURRENT PASSWORD : ";
        cin >> test;
        if (test != password)
        {
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            cout << "INCORRECT PASSWORD ENTERED! PERMISSION TO CHANGE PASSWORD DENIED!" << endl;
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            return;
        }
        cout << "CURRENT PASSWORD CORRECTLY ENTERED!" << endl;
        vector<admin>::iterator q = users.begin();
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].username_info() == username)
            {
                users.erase(users.begin() + i);
                break;
            }
        }
        cout << "ENTER NEW PASSWORD : ";
        cin >> test;
        password = test;
        cout << "PASSWORD SUCCESSFULLY CHANGED!" << endl;
        users.push_back(*this);
        ofstream f2;
        f2.open("admins.txt");
        for (admin o : users)
        {
            f2 << o.username_info() << endl;
            f2 << o.password_info() << endl;
        }
        f2.close();
    }
    string username_info()
    {
        return username;
    }
    string password_info()
    {
        return password;
    }
};


admin *adminlogin() {
    cout << "ADMIN LOGIN PORTAL - " << endl;
    if(users.size()==0) {
        cout<<"Creating new account...\n";
        admin use;
        use.newUser(users);
        return &users[0];
    }
    string name, pass;
    cout << "ENTER admin username : ";
    cin >> name;
    cout << "Enter password : ";
    cin >> pass;
    admin *now;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].check(name, pass))
        {
            now = &users[i];
            cout << "LOGIN SUCCESSFUL!" << endl;
            return now;
            break;
        }
        if (i == users.size() - 1)
        {
            cout << "NO SUCH USER FOUND! CHECK USERNAME OR PASSWORD!" << endl;
            return NULL;
        }
    }
    return NULL;
}


void AddNode(station **list, string n, int sn) {
    station *s = new station(n, sn);
    if (*list == NULL)
    {
        *list = s;
    }
    else if ((*list)->previous == NULL && (*list)->next == NULL)
    {
        (*list)->next = s;
        s->previous = *list;
    }
    else
    {
        station *p;
        for (p = *list; p->next != NULL; p = p->next)
            ;
        p->next = s;
        s->previous = p;
    }
}


void readFile(station **list) {
    ifstream f1;
    f1.open("stations.txt");
    int t;
    f1>>t;
    while (t--)
    {
        string s;
        f1 >> s;
        int i;
        f1 >> i; // 1
        AddNode(list, s, i);
    }
    f1>>farecost;
    f1.close();
}


void AddNodeByAdmin(station **list, int pos)
{
    cout << "Enter station name\n";
    string s1;
    cin >> s1;
    station* temp1=*list;
    while(temp1!=NULL){
        string tt=temp1->getsName();
        if(tt==s1) goto l1;
        temp1=temp1->next;
    }
    {station *s = new station(s1, pos);
    if (*list == NULL && pos == 1)
    {
        *list = s;
    }
    else if ((*list)->previous == NULL && (*list)->next == NULL && pos == 1)
    {
        (*list)->previous = s;
        s->next = *list;
        (*list)->IncreaseStationNumber();
        *list = s;
    }
    else if ((*list)->previous == NULL && (*list)->next == NULL && pos == 2)
    {
        (*list)->next = s;
        s->previous = *list;
    }
    else if ((*list)->previous != NULL && (*list)->next != NULL && pos == 1)
    {
        s->next = *list;
        (*list)->previous = s;
        station *p = *list;
        *list = s;
        while (p != NULL)
        {
            p->IncreaseStationNumber();
            p = p->next;
        }
    }
    else if (pos == station::count)
    {
        station *p;
        for (p = *list; p->next != NULL; p = p->next)
            ;
        p->next = s;
        s->previous = p;
    }
    else
    {
        station *p;
        for (p = *list; p != NULL; p = p->next)
        {
            if (p->getsNumber() == pos)
            {
                break;
            }
        }
        (p->previous)->next = s;
        s->previous = p->previous;
        s->next = p;
        p->previous = s;
        while (p != NULL)
        {
            p->IncreaseStationNumber();
            p = p->next;
        }
    }
    cout << "Station Added successfully\n";
    }
    if(0){
        l1: cout << "Station Already Exists\n";
    }
}


void DeleteNode(station **list, int pos)
{
    station::count--;
    if (*list == NULL)
    {
        station::count = 0;
        cout << "There are no stations\n";
    }
    else if ((*list)->next == NULL && pos == 1)
    {
        delete *list;
        *list = NULL;
    }
    else if (pos == 1)
    {
        station *p = (*list)->next;
        delete *list;
        *list = p;
        while (p != NULL)
        {
            p->DecreaseStationNumber();
            p = p->next;
        }
    }
    else if ((*list)->next == NULL && pos != 1)
    {
        station *p;
        for (p = *list; p->next != NULL; p = p->next)
            ;
        (p->previous)->next = NULL;
        delete p;
    }
    else
    {
        station *p, *p1;
        for (p = *list; p != NULL; p = p->next)
        {
            if (p->getsNumber() == pos)
                break;
        }
        (p->previous)->next = p->next;
        if(p->next!=NULL) (p->next)->previous = p->previous;
        p1 = p->next;
        delete p;
        while (p1 != NULL)
        {
            p1->DecreaseStationNumber();
            p1 = p1->next;
        }
    }
}


void writefile(station *list)
{
    ofstream f1;
    f1.open("stations.txt");
    f1<<station::count<<endl;
    for (station *p = list; p != NULL; p = p->next)
    {
        f1 << p->getsName() << endl;
        if (p->next == NULL)
            f1 << p->getsNumber();
        else
            f1 << p->getsNumber() << endl;
    }
    f1<<endl<<farecost;
    f1.close();
}


void displayList(station *list)
{
    for (station *p = list; p != NULL; p = p->next)
    {
        cout << "Station Number:" << p->getsNumber() << endl;
        cout << "Station Name:" << p->getsName() << endl
             << endl;
    }
}


int cost_calculation(station *list, string s1, string s2)
{
    int ssn = 0, esn = 0;
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
    station *p;
    for (p = list; p != NULL; p = p->next)
    {
        string s3 = p->getsName();
        transform(s3.begin(), s3.end(), s3.begin(), ::toupper);
        if (s1 == s3)
            ssn = p->getsNumber();
        if (s2 == s3)
            esn = p->getsNumber();
    }
    int tcost = (esn - ssn > 0 ? esn - ssn : ssn - esn) * farecost;
    return tcost;
}


void delCard() {
    sleep(1);
    system("cls");
    long long test;
    cout << "ENTER METRO CARD NUMBER to be deleted : ";
    cin >> test;
    int flag = 0;
    vector<CreditCard>::iterator q = C.begin();
    for (int i = 0; i < C.size(); i++)
    {
        if (C[i].info_cred() == test)
        {
            flag = 1;
            C.erase(C.begin() + i);
            cout << "CARD SUCCESSFULLY DELETED!" << endl;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "NO RECORD FOUND OF SUCH CARD! INVALID INPUT! " << endl;
        return;
    }
    ofstream re;
    re.open("creditCards.txt");
    int counter = 0;
    for (CreditCard o : C)
    {
        if (counter != C.size() - 1)
        {
            re << o.info_name() << endl;
            re << o.info_cred() << endl;
            re << o.info_balance() << endl;
        }
        else
        {
            re << o.info_name() << endl;
            re << o.info_cred() << endl;
            re << o.info_balance();
        }
        counter++;
    }
    re.close();
}


int check_station_Validity(station *list, string s1)
{
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    for (station *p = list; p != NULL; p = p->next)
    {
        string s2 = p->getsName();
        transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
        if (s1 == s2)
            return (p->getsNumber());
    }
    return -1;
}


void check_route(station *list, string s1, string s2)
{
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
    station *p;
    bool b = false;
    int n1 = check_station_Validity(list, s1), n2 = check_station_Validity(list, s2);
    if (n1 == n2 || n1 == -1 || n2 == -1)
    {
        cout << "Invalid Input" << endl;
        return;
    }
    else if (n1 < n2)
    {
        for (p = list; p != NULL; p = p->next)
        {
            string s3 = p->getsName();
            transform(s3.begin(), s3.end(), s3.begin(), ::toupper);
            if (s1 == s3)
            {
                b = true;
                cout << "STARTING POINT:" << endl
                     << endl;
            }
            if (b)
            {
                cout << "Station Number:" << p->getsNumber() << endl;
                cout << "Station Name:" << p->getsName() << endl
                     << endl;
            }
            if (s2 == s3)
            {
                b = false;
                cout << "\nENDING POINT:" << endl;
            }
        }
    }
    else
    {
        for (p = list; p != NULL; p = p->next)
        {
            if (n1 == p->getsNumber())
                break;
        }
        cout << "STARTING POINT:" << endl
             << endl;
        while (p->getsNumber() != n2)
        {
            cout << "Station Number:" << p->getsNumber() << endl;
            cout << "Station Name:" << p->getsName() << endl
                 << endl;
            p = p->previous;
        }
        cout << "Station Number:" << p->getsNumber() << endl;
        cout << "Station Name:" << p->getsName() << endl;
        cout << "\nENDING POINT:" << endl;
    }
}


void newCard()
{
    cout << "\t\t\t\tENTER DETAILS TO CREATE NEW CARD - ....\n";
    string name;
    long long credit;

    cout << "ENTER CARD HOLDER NAME : ";
    cin >> name;
    // PROMPTS THE USER TO ENTER A CREDIT CARD NUMBER
    cout << "PLEASE ENTER A CREDIT CARD NUMBER FOR VERIFICATION!\n";
    cin >> credit;
    cout << "YOUR CARD IS : ";
    if (check_validity(credit) == -1)
    {
        return;
    }
    float bal;
    cout << "ENTER BALANCE IN CARD : ";
    cin >> bal;
    CreditCard temp;
    temp.create(name, credit, bal);
    C.push_back(temp);

    ofstream re;
    re.open("creditCards.txt");
    int counter = 0;
    for (CreditCard o : C)
    {
        if (counter != C.size() - 1)
        {
            re << o.info_name() << endl;
            re << o.info_cred() << endl;
            re << o.info_balance() << endl;
        }
        else
        {
            re << o.info_name() << endl;
            re << o.info_cred() << endl;
            re << o.info_balance();
        }
        counter++;
    }
    re.close();
}


void book_a_ticket(station *list)
{
    fstream tick;
    tick.open("ticket.txt", ios_base::app);
    string name;
    int counter=0;
    long long phone;
    cout << "Please enter the name of your current station" << endl;
    string s1;
    cin >> s1;
    cout << "Please enter your destination\n";
    string s2;
    cin >> s2;
    int n1 = check_station_Validity(list, s1);
    int n2 = check_station_Validity(list, s2);
    if (n1 == -1 || n2 == -1)
    {
        cout << "INVALID INPUT\n";
        cout<<"Press any key to continue...";getchar();
        return;
    }
    else
    {
        system("cls");
        check_route(list, s1, s2);
        cout << "Number of stations to travel:" << ((n1 > n2) ? n1 - n2 : n2 - n1) << endl;
        cout << "Total Cost:" << cost_calculation(list, s1, s2) << endl;
        cout << "Do you wish to proceed?Enter Y or N: ";
        char ch;
        cin >> ch;
        if (ch == 'Y' || ch=='y')
        {
            system("cls");
            cout << "How do you wish to make the payment\n";
            cout << "1.Cash\n";
            cout << "2.Metro Card" << endl;
            cout << "3.Exit" << endl;
            cout << "Enter your choice" << endl;
            int choice1;
            cin >> choice1;
            ofstream er;
            CreditCard *temp = NULL;
            int flag = 0;
            switch (choice1)
            {
            case 1:
                cout<<"----------------------------------------------"<<endl;
                cout<<"Enter your name: ";
                cin>>name;
                cout<<"Enter your phone: ";
                cin>>phone;
                cout<<"----------------------------------------------"<<endl;
                tick<<name<<endl<<phone<<endl<<s1<<endl<<s2<<endl<<"Cash"<<endl<<cost_calculation(list, s1, s2)<<endl;
                cout << "Booking successful\n";
                sleep(2);
                cout << "Press Enter\n";
                getchar();
                break;
            case 2: // metro card fuctions
                system("cls");

                long long test;
                cout<<"----------------------------------------------"<<endl;
                cout<<"Enter your name: ";
                cin>>name;
                cout<<"Enter your phone: ";
                cin>>phone;
                cout << "ENTER METRO CARD NUMBER : ";
                cin >> test;
                cout<<"----------------------------------------------"<<endl;

                // vector<CreditCard>::iterator q = C.begin();
                for (int i = 0; i < C.size(); i++)
                {

                    if (C[i].info_cred() == test)
                    {
                        flag = 1;
                        cout << "CARD FOUND IN SYSTEM!" << endl;
                        int cost = cost_calculation(list, s1, s2);
                        temp = &C[i];
                        temp->update_amount(name, phone, s1, s2, cost);
                        sleep(2);
                        cout<<"\nPress any key to continue...\n";getchar();
                        break;
                    }
                }
                if (flag == 0)
                {
                    cout << "NO RECORD FOUND OF SUCH CARD! INVALID INPUT! " << endl;
                    return;
                }
                er.open("creditCards.txt");
                for (CreditCard o : C)
                {
                    er << o.info_name() << endl;
                    er << o.info_cred() << endl;
                    if(counter==C.size()-1) er << o.info_balance();
                    else er<<o.info_balance()<<endl;
                    counter++;
                }
                er.close();
                break;
            case 3:

                break;
            default:
                cout << "Invalid Input\n";
            }
        }
        else if (ch == 'N' || ch=='n')
        {
            cout << "BOOKING CANCELLED\n";
            cout<<"\nPress any key to continue...\n";
            getchar();
            return;
        }
        else
        {
            cout << "INVALID INPUT\n";
            return;
        }
    }
    tick.close();
}

void viewticket(){
    string name;
    long long phone;
    cout<<"Enter your name: ";
    cin>>name;
    cout<<"Enter your phone: ";
    cin>>phone;
    string tname;
    long long tphone;
    string s1, s2, mode;
    int cost;
    ifstream tick("ticket.txt");
    tick>>tname>>tphone>>s1>>s2>>mode>>cost;
    int sr=1;
    while(!tick.eof()){
        if(tname==name && tphone==phone){
            cout<<endl<<sr<<"."<<endl;
            cout<<"-------------------------------------"<<endl;
            cout<<"Source Station :     "<<s1<<endl;
            cout<<"Destination Station: "<<s2<<endl;
            cout<<"Method of Payment :  "<<mode<<endl;
            cout<<"Cost of the ticket:  "<<cost<<endl;
            cout<<"-------------------------------------"<<endl;
            sr++;
        }
        tick>>tname>>tphone>>s1>>s2>>mode>>cost;
    }
    if(sr==1){
        cout<<"No tickets found...\n";
    }
    tick.close();
}

void customer_menu(station *list)
{
    int choice;
    while(choice!=8){
    cout << "\t\t\t\t\t*****CUSTOMER MENU*****\n\n\n";
    cout << "\t\t\t\t\t1.Book a ticket\n";
    cout << "\t\t\t\t\t2.See the Metro map\n";
    cout << "\t\t\t\t\t3.Check Route\n";
    cout << "\t\t\t\t\t4.Check metro card balance\n";
    cout << "\t\t\t\t\t5.New Card Registration\n";
    cout << "\t\t\t\t\t6.Recharge metro card\n";
    cout << "\t\t\t\t\t7.View your tickets\n";
    cout << "\t\t\t\t\t8.Exit\n";
    cout << "\t\t\t\t\tENTER YOUR CHOICE\n";
    string m1, m2;
    long long test;
    int flag = 0;
    cin >> choice;
    switch (choice)
    {
    case 1:
        book_a_ticket(list);
        getchar();
        sleep(2);
        system("cls");
        break;
    case 2:
        displayList(list);
        sleep(2);
        cout<<"\nPress any key to continue...";getchar();
        getchar();
        system("cls");
        break;
    case 3:
        cout << "Enter station number 1:";
        cin >> m1;
        cout << "Enter station 2: ";
        cin >> m2;
        check_route(list, m1, m2);
        sleep(2);
        cout<<"Press any key to continue...";getchar();
        getchar();
        system("cls");
        break;
    case 4:
        cout << "ENTER METRO CARD NUMBER : ";
        cin >> test;
        flag = 0;
        // vector<CreditCard>::iterator q = C.begin();
        for (int i = 0; i < C.size(); i++)
        {

            if (C[i].info_cred() == test)
            {
                flag = 1;
                C[i].check_balance();
                break;
            }
        }
        if (flag == 0)
        {
            cout << "NO RECORD FOUND OF SUCH CARD! INVALID INPUT! " << endl;
        }
        sleep(3);
        cout<<"\nPress any key to continue...";getchar();
        getchar();
        getchar();
        system("cls");
        break;
    case 5:
        newCard();
        sleep(2);
        cout<<"\nPress any key to continue...";getchar();
        getchar();
        system("cls");
        break;
    case 6:
        long long test;
        cout << "ENTER METRO CARD NUMBER : ";
        cin >> test;
        // vector<CreditCard>::iterator q = C.begin();
        for (int i = 0; i < C.size(); i++)
        {

            if (C[i].info_cred() == test)
            {
                flag = 1;
                C[i].card_Recharge();
                break;
            }
        }
        if (flag == 0)
        {
            cout << "NO RECORD FOUND OF SUCH CARD! INVALID INPUT! " << endl;
        }
        sleep(2);
        cout<<"\nPress any key to continue...";getchar();
        getchar();
        system("cls");
        break;
    case 7:
        sleep(1);
        system("cls");
        viewticket();
        cout<<"Press any key to continue....";getchar();
        getchar();
        sleep(2);
        system("cls");
        break;
    case 8:
        cout << "YOU HAVE CHOSEN TO EXIT THE CUSTOMER PORTAL!" << endl;
        cout << "THANK YOU FOR USING OUR SERVICES, SEE U SOON!" << endl;
        cout << "RETURNING TO MAIN MENU" << endl;
        sleep(2);
        system("cls");
        break;
    default:
        cout << "Invalid Input\n";
        system("cls");
    }
    }

}


void adminmenu(station **list, admin *now) {
    l1:
    cout << "\t\t\t\t****ADMIN MENU****" << endl;
    cout << "\t\t\t\t1.View all Stations\n";
    cout << "\t\t\t\t2.New Station Registration\n";
    cout << "\t\t\t\t3.Delete an existing station\n";
    cout << "\t\t\t\t4.Change fare price" << endl;
    cout << "\t\t\t\t5.Delete a Metro Card" << endl;
    cout << "\t\t\t\t6.Print Details of all existing metro cards in the system\n";
    cout << "\t\t\t\t7.Change Password\n";
    cout << "\t\t\t\t8.Add a new user\n";
    cout << "\t\t\t\t9.Exit" << endl;
    cout << "\t\t\t\tEnter your choice\n";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        now->printStationDetails(list);
        sleep(2);
        cout<<"\nPress any key to continue...\n";
        getchar();
        getchar();
        sleep(1);
        system("cls");
        break;
    case 2:
        cout << "Enter the position which you want to add the station\n";
        int pos;
        cin >> pos;
        if(pos<1 || pos>station::count+1) {
            cout<<"Wrong station number....\n";
        }
        else{
            AddNodeByAdmin(list, pos);
            system("cls");
            writefile(*list);
        }
        cout<<"\nPress any key to continue...\n";
        getchar();
        sleep(1);
        system("cls");
        break;
    case 3:
        cout << "Enter the station number which you want to delete\n";
        int pos1;
        cin >> pos1;
        if(pos1<1 || pos1>station::count) {
            cout<<"Wrong station number....\n";
        }
        else{
            DeleteNode(list, pos1);
            cout << "Station Deleted successfully\n";
            writefile(*list);
        }
        cout<<"\nPress any key to continue...\n";
        getchar();
        sleep(1);
        system("cls");
        break;

    case 4:
        cout << "Current Fare Price = " << farecost << endl;
        cout << "Enter new fare price = ";
        cin >> farecost;
        cout << "Fare Price has been successfully changed!\n";
        writefile(*list);
        sleep(1);
        cout<<"\nPress any key to continue...\n";getchar();
        system("cls");
        break;
    case 5:
        delCard();
        sleep(1);
        cout<<"\nPress any key to continue...\n";getchar();
        system("cls");
        break;
    case 6:
        now->printCardDetails(C);
        sleep(3);
        cout<<"\nPress any key to continue...\n";getchar();
        getchar();
        system("cls");
        break;
    case 7:
        now->changePassword();
        sleep(1);
        cout<<"\nPress any key to continue...\n"; getchar(); getchar();
        system("cls");
        break;
    case 8:
        now->newUser(users);
        break;
    case 9:
        cout << "ADMIN HAS BEEN LOGGED OUT SUCCESSFULLY!" << endl;
        cout << "THANK YOU FOR USING ADMIN PORTAL" << endl;
        sleep(2);
        cout<<"Press any key to continue....";
        getchar();
        system("cls");
        goto l3;
        break;
    default:
        if(choice>7) cout << "Invalid Input\nTRY AGAIN!\n";
        sleep(1);
        cout<<"\nPress any key to continue...\n";getchar();
        system("cls");
        break;
    }
    l2: goto l1;
    l3:;

}


void menu(station **list) {

    while (true)
    {
        cout << "\t\t\t\t***********************************************************************************" << endl;
        cout << "\t\t\t\t***                         NOIDA METRO SYSTEM                                  ***" << endl;
        cout << "\t\t\t\t***********************************************************************************\n\n\n\n";
        cout << "\t\t\t\t\t\t\tWelcome to Metropolis\n";
        cout << "\t\t\t\t\t\t\tAre you a..." << endl;
        cout << "\t\t\t\t\t\t\t1.Administrator" << endl;
        cout << "\t\t\t\t\t\t\t2.Customer" << endl;
        cout << "\t\t\t\t\t\t\t3.Exit the program\n";
        cout << "\t\t\t\t\t\t\tEnter your choice\n";
        int choice;
        cin >> choice;
        if (choice == 3)
            break;
        else if (!(choice >= 1 && choice <= 3))
        {
            cout << "INVALID INPUT! TRY AGAIN!" << endl;
            sleep(1);
            cout<<"\nPress any key to continue...\n";getchar();
            system("cls");
            continue;
        }
        else
        {
            if (choice == 1)
            {
                sleep(1);
                system("cls");
                admin *now = adminlogin();
                if (now == NULL)
                {
                    continue;
                }
                adminmenu(list, now);
            }
            if (choice == 2)
            {
                sleep(1);
                system("cls");
                customer_menu(*list);
            }
        }
    }
}


void deletecompletelist(station *list) {
    station *p = list;
    list = p->next;
    while (p != NULL)
    {
        delete p;
        p = list;
        list = list->next;
    }
}


int check_validity(long long Input)
{
    int sumE = 0;
    int sumO = 0;
    long long credE = Input / 10;
    long long credO = Input;

    // final DESCRIBES THE VALUE WHEN THE SECOND LAST DIGIT IS SELECTED. IF IT IS MORE THAN 9,THEN ITS DIGITS ARE ADDED AS SHOWN BELOW

    int final = 0;

    do
    {
        // remE DESCRIBES THE REMAINDER OR THE SECOND TO LAST DIGIT IN EACH LOOP(STARTING FROM ORIGINAL INPUT VALUE)
        int remE = credE % 10;

        // multiple INDICATES THE DOUBLING OF THE SECOND TO LAST DIGIT ACCORDING TO LUHN'S ALGORITHM
        int multiple = remE * 2;

        // credE IS DIVIDED BY 100 TO PROCEED TO THE SECOND TO SECOND TO LAST DIGIT AND SO ON
        credE = credE / 100;

        // AN IF-ELSE STATEMENT TO ADD UP THE DIGITS OF FACTOR IF IT IS A DOUBLE DIGIT NUMBER
        if (multiple < 10)
        {
            final = multiple;
        }
        else
        {
            // ones AND tens DESCRIBE(OBVIOUSLY) THE ONES AND TENS DIGITS OF multiple IF IT IS A DOUBLE DIGIT NUMBER
            int ones = multiple % 10;
            int tens = multiple / 10;
            final = ones + tens;
        }
        // THE SUM OF OPERATIONS ON EVEN VALUES FROM END OF NUMBER ACCORDING TO ALGORITHM
        sumE += final;
    } while (credE > 0);

    do
    {
        int remO = credO % 10;
        credO = credO / 100;
        sumO += remO;
    } while (credO > 0);

    int sum = sumE + sumO;
    int checksum = sum % 10;

    // CALCULATING THE NUMBER OF DIGITS

    int count = 0;
    long long length = Input;
    do
    {
        length /= 10;
        count += 1;
    } while (length > 0);

    // CALCULATING THE FIRST DIGIT OF CREDIT CARD
    long long length_1 = Input;
    long long length_2 = Input;
    long long first_digit;
    long long second_digit;

    do
    {
        first_digit = length_1;
        length_1 /= 10;
    } while (length_1 > 0);

    do
    {
        second_digit = length_2;
        length_2 /= 10;
    } while (length_2 > 9);

    // TO CHECK WHICH TYPE OF CREDIT CARD NUMBER WAS THE INPUT IF IT IS EVEN VALID AT ALL.
    if (checksum == 0 && count == 13 && first_digit == 4)
    {
        cout << "VISA\n";
        return 0;
    }
    else if (checksum == 0 && count == 15 && (second_digit == 34 || second_digit == 37))
    {
        cout << "AMEX\n";
        return 0;
    }
    else if (checksum == 0 && count == 16 && first_digit == 4)
    {
        cout << "VISA\n";
        return 0;
    }
    else if (checksum == 0 && count == 16 && second_digit > 50 && second_digit < 56)
    {
        cout << "MASTERCARD\n";
        return 0;
    }
    else
    // IF THE INPUT DOESN'T EVEN PASS THE CHECKSUM,THEN OBVIOUSLY IT IS AN INVALID CREDIT CARD NUMBER
    {
        cout << "INVALID\n";
        return -1;
    }
}


void load(){
    ifstream card;
    string s;
    card.open("creditCards.txt");
    if (!card)
    {
        card.close();
        goto next;
    }
    card>>s;
    while (card.eof() == false)
    {
        // cout << "2";
        CreditCard o;
        long long i;
        card >> i;
        float b;
        card >> b;
        o.create(s, i, b);
        C.push_back(o);
        card>>s;
    }
    card.close();
next:
    // cout << "3";
    // newCard();
    ifstream a1;
    string i;
    a1.open("admins.txt");
    if (!a1)
    {
        a1.close();
        goto next2;
    }
    a1>>s;
    a1 >> i; // 1
    while (!a1.eof())
    {
        // j++;
        admin o;
        o.setData(s, i);
        users.push_back(o);
        a1>>s;
        a1>>i;
        // AddNode(vector,s,i);
    }
    // cout << j << endl;
    a1.close();
next2:
    cout << "HI!" << endl;
}


int main(){
    load();
    station *list = NULL;
    readFile(&list);
    menu(&list);
    deletecompletelist(list);
    return 0;
}
