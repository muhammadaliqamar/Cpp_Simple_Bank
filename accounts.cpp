/* 
    Menu Driven Bank Program Uses Classes To 
    Manage Basic Transactions

    Muhammad Ali Qamar
    2020/23/10
*/

#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
using namespace std;

int number_system_get();
void number_system_put(int n);
//Class Declaration for Accounts
class Bank_account
{
    protected:
        int accNo;
        char name[50];
        float bal;

    public:
        //Account Creation
        void open_account()
        {
            cout<<"\t------ New Account Opening Form ------\n";
            cout<<"Enter Account Holder Name : ";
            cin.ignore();
            cin.getline(name, 50);
            accNo = number_system_get();
            cout<<"Dear "<<name<<" Your Account Number Is : "<<accNo<<endl;
            Deposit:
                cout<<"Please Mention The Initial Deposit Of Minimum 1000 In PKR : ";
                cin>>bal;
            if (bal <= 1000)
            {
                system("cls");
                cout<<"Please Deposit Minimum Required Balance To Open An Account.\n";
                goto Deposit;
            }
            cout<<"\nThe Account Of Mr./Mrs. "<<name<<" Has Been Created Successfully.\n";
            number_system_put(accNo);
        }

        //Account View
        void view_account()
        {
            cout<<"Account Holder Name : "<<name<<endl;
            cout<<"Account No. : "<<accNo<<endl;
            cout<<"Available Balance : "<<bal<<endl;
        }

        //Fund Transfer



        //Amount Deposit
        void deposit_amount(int x)
        {
            bal += x;
            cout<<"\nDear "<<name<<" Your New Balance is : "<<bal<<endl;
        }

        //Amount Withdraw
        void withdraw_amount(int x)
        {
            bal -= x;
            cout<<"\nDear "<<name<<" Your Remaining Balance is : "<<bal<<endl;
        }

        const void account_report()
        {
            cout<<accNo<<setw(10)<<" "<<name<<setw(6)<<" "<<bal<<endl;
        }

        //returning constant values

        const int retaccNo()
        {
            return accNo;
        }

        const float retbalance()
        {
            return bal;
        }
}; //Class Ends

//Global Declaraation Of Object
Bank_account acc;

//Functions
void Intro()
{
    cout<<"   ********************\n";
	cout<<"\t  BANK\n";
	cout<<"\n\tMANAGEMENT\n";
	cout<<"\n\t  SYSTEM\n";
    cout<<"   ********************\n";
    cout<<"--- By Muhammad Ali Qamar ---\n";
    cin.get();
}

//Writing Into File
void write_account()
{
    ofstream accFile;
    accFile.open("accounts.dat", ios::binary |ios::app);
    acc.open_account();
    accFile.write(reinterpret_cast<char *> (&acc), sizeof(Bank_account));
    accFile.close();
}

//access specific record
void record_specific(int x)
{
    bool f = false;
    ifstream fileAcc;
    fileAcc.open("accounts.dat", ios:: binary);
    if(!fileAcc)
    {
        cout<<"File Not Opened. Press any Key....\n";
        return;
    }
    cout<<"\t\t\t------ Your Account Details Are As  ------\n";
    while (fileAcc.read(reinterpret_cast<char *> (&acc), sizeof(Bank_account)));
    {
        if(acc.retaccNo() == x)
        {
            acc.view_account();
            f = true;
        }
    }
    fileAcc.close();
    if (f == false)
    {
        cout<<"Account Does Not Exist.\n";
    }
}

//delete record
void delete_record(int x)
{
    ifstream inFile;
    ofstream outFile;
    inFile.open("accounts.dat", ios::binary);
    if(!inFile)
    {
        cout<<"File Not Opened. Press any Key....\n";
        return;
    }
    outFile.open("temp.dat", ios::binary);
    inFile.seekg(0,ios::beg);
    while (inFile.read(reinterpret_cast<char *> (&acc), sizeof(Bank_account)))
    {
        if (acc.retaccNo() != x)
        {
            outFile.write(reinterpret_cast<char *> (&acc), sizeof(Bank_account));
        }  
    }
    inFile.close();
    outFile.close();
    remove("accounts.dat");
    rename("temp.dat","accounts.dat");
    cout<<"\n\t\t\t Account Closed Successfully.......\n";
}
// Fund Transfering


//Display all accounts

void display_all()
{
    ifstream inFile;
    inFile.open("accounts.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File Not Opened. Press any Key....\n";
        return;
    }
    cout<<"\t\t\t--- Account Holders List ---\n";
    cout<<"\n====================================================\n";
    cout<<"AC No.                  Name                Balance\n";
    cout<<"====================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(Bank_account)))
    {
        acc.account_report();
    }
    inFile.close();
}

//Deposit/Withdraw 
void deposit_withdraw(int x, int opt)
{
    int a;
    bool f = false;
    fstream File;
    File.open("accounts.dat", ios::binary | ios::in | ios::out);
    if(!File)
    {
        cout<<"File Not Opened. Press any Key....\n";
        return;
    }
    while(!File.eof() && f == false)
    {
        File.read(reinterpret_cast<char *> (&acc), sizeof(Bank_account));
        if(acc.retaccNo() == x)
        {
            if (opt == 1)
            {
                cout<<"\t\t\t--- Money Deposit ---\n";
                cout<<"Enter Amount To Be Deosited : ";
                cin>>a;
                acc.deposit_amount(a);
            }

            if (opt == 2)
            {
                cout<<"\t\t\t--- Money Withdraw ---\n";
                cout<<"Enter Amount To Be Withdrawn : ";
                cin>>a;
                if(a > acc.retbalance())
                {
                    cout<<"Insufficience balance";
                }
                else
                {
                acc.withdraw_amount(a);
                cout<<"\nAmount Successfully Withdrawn.....";
                }     
            }
            int pos=(-1)*static_cast<int>(sizeof(acc));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&acc), sizeof(Bank_account));
            f =true; 
        }   
    }
    File.close();
    if (f == false)
    {
        cout<<"Record Not Found.\n";
    } 
}



//Main
int main()
{
    int opt, num;
    Intro();
    do
    {
        system("cls");
        cout<<"\t\t\tWelcome To Royal Bank Pvt. Ltd.\n";
        cout<<"\n\tMain Menu\n";
        cout<<"\t1) Open New Account.\n";
        cout<<"\t2) Balance Enquiry.\n";
        cout<<"\t3) Deposit Amount.\n";
        cout<<"\t4) Withdraw Amount.\n";
        cout<<"\t5) Fund Transfer.\n";
        cout<<"\t6) All Account Holders List.\n";
        cout<<"\t7) Close An Account.\n";
        cout<<"\t8) Exit.\n";
        cout<<"\tSelect Your Option : ";
        cin>>opt;
        system("cls");
        switch (opt)
        {
        case 1:
            write_account();
            break;

        case 2:
            cout<<"Enter Account Number : ";
            cin>>num;
            record_specific(num);
            break; 
            
        case 3:
            cout<<"Enter Account Number : ";
            cin>>num;
            deposit_withdraw(num, 1);
            break;        

        case 4:
            cout<<"Enter Account Number : ";
            cin>>num;
            deposit_withdraw(num, 2);
            break;
        case 5:
            cout<<"Enter Account Number : ";
            cin>>num;
            break;
        case 6:
            display_all();
            break;
        case 7:
            cout<<"Enter Account Number : ";
            cin>>num;
            delete_record(num);
            break;
        case 8:
            cout<<"\t\t\tThanks For Using Royal Bank Management System. ";
            break;
        default: 
            cout<<"\a";
            break;
        }
        cin.ignore();
        cin.get();

    } while (opt != 8);
    return 0;

}


//Function for Account Number 
int number_system_get()
{
	int number;
	ifstream number_read("number.dat", ios::binary | ios::in);
	number_read >>number;
	return number;
}

void number_system_put(int n)
{
	n = n+1;
	ofstream number_write("number.dat",ios::binary | ios::out);	
	number_write <<n;
}

