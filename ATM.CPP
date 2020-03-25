#include<iostream>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<stdio.h>
void menu();

using namespace std;

class cstmr
{
public:
long int  account_no;
char name[20];
char adds[40];
char mobile[13];
char email[30];
long int balance;
int pin;
void take();
void give()                // give details of already existing account
	{
	cout<<"\nYour details are:"
	    <<"\n\n\tName         :"<<name
	    <<"\n\n\tAccount no.  :"<<account_no
	    <<"\n\n\tAddress      :"<<adds
	    <<"\n\n\tMobile no.   :"<<mobile
	    <<"\n\n\tEmail ID.    :"<<email
	    <<"\n\n\tYour Balance :"<<balance;
       }

};

void cstmr::take()                 // for taking details for creating new account
{
cstmr c;
cout<<"\t\t\t\Creating Account";
cout<<"\nEnter Your Name         : ";
gets(name);
cout<<"\nEnter Your Address      : ";
gets(adds);
error:
cout<<"\nEnter Your Mobile number: +91";
gets(mobile);
if(strlen(mobile)<10 || strlen(mobile)>10)
	{
	cout<<"Wrong mobile number";
	goto error;
	}
cout<<"\nEnter Your Email ID     : ";
gets(email);
cout<<"\nEnter balance           : ";
cin>>balance;
ifstream f("bank.dat",ios::binary);
again:
account_no=rand()+1000000;
while(f.read((char*)&c,sizeof(c)))
	if(account_no==c.account_no)
		goto again;
cout<<"Your account no. is "<<account_no;
wrong:
pin=rand()+1000;
while(f.read((char*)&c,sizeof(c)))
	if(pin==c.pin)
		goto wrong;
cout<<"\nYour pin is "
    <<pin;
getch();
cout<<"\nDon't disclose this pin to anyone.";
getch();
cout<<"\nThanks for choosing our service.\n";

getch();
f.close();
}

class record
{
public:
long int acc_no;
char type[15];
int amt,no;
char dob;
void rec(long int a,int b,char ch[]);
void give()
	{
	cout<<no<<"/t"
	    <<acc_no<<"/t/t"
	    <<amt<<"/t"
	    <<type<<"/t/t";
	}
};

void clrscr()
{
system("cls");
}
void create()          // creating an account
{
system("cls");
ofstream f("bank.dat",ios::binary|ios::app);
cstmr c;
char ch;
do
{
clrscr();
c.take();
f.write((char*)&c,sizeof(c));
cout<<"Do you want to continue ?\n"
    <<"If yes,Press 'y'\n";
cin>>ch;
}while(ch=='y');
f.close();
}

void display()                  // to display details of a particular account
{
clrscr();
int pin,fp=0,l=0;
long int ch1;
cstmr c;
cout<<"Enter account number \n";
cin>>ch1;
ifstream f("bank.dat",ios::binary);
while(f.read((char*)&c,sizeof(c)))
	if(ch1==c.account_no)
		while(l==0)
		{
		fp=1;
		cout<<"Enter your 4 digit pin\n";
		cin>>pin;
		if(pin==c.pin)
		   c.give();
		else
		   cout<<"Wrong pin";
		l=1;
		}
if(fp==0)
	cout<<"Wrong account no.";
getch();
f.close();
}

void bill(long int ch,int amt,long int bh)
{
cstmr c1,c;
int b=0,d=0;
record r;
clrscr();
ifstream f("bank.dat",ios::binary);
if(bh==0)
	while(f.read((char*)&c,sizeof(c)))
		if(c.account_no==ch && b==0)
			{
			b=1;
			cout<<"\t\t\t\tReceipt\n"
			    <<"Dear "<<c.name
			    <<", your acoount no. "<<ch
			    <<" has been debited with Rs."<<amt
			    <<"\nYour current balance is Rs."<<c.balance
			    <<"\n\t\tThank you for choosing our services";
			}
if(bh!=1)
        while(f.read((char*)&c,sizeof(c)))
				if(ch==c.account_no && d==0)
					{
					d=1;
					cout<<"\t\t\t\t\tReceipt\n"
					    <<"Dear "<<c.name<<", Rs."<<amt
					    <<" has been transferred from your account no."
					    <<ch<<" to\n"<<"'s account no."<<bh
					    <<"\nYour current balance is Rs."<<c.balance
					    //<<" "<<c1.name<<"'s current balance is Rs. "<<c1.balance
					    <<"\n\t\tThank you for choosing our services";
					 //r.rec(bh,amt,"received");
					 //r.rec(ch,amt,"transferred");
					 }
getch();
f.close();
}

void trans()
{
clrscr();
cstmr c;
long int ch;
int amt,byte,pin,fp=0;
cout<<"\t\t\tTransaction\n";
cout<<"Enter account number \n";
cin>>ch;
byte=sizeof(c);
fstream f("bank.dat",ios::in|ios::out|ios::binary);
while(f.read((char*)&c,sizeof(c)))
	if(ch==c.account_no)
		{
		fp=1;
		cout<<"Enter Your Pin \n";
		cin>>pin;
		if(pin==c.pin)
			{
			cout<<"Enter Amount \n";
			cin>>amt;
			if(c.balance>=amt)
				{
				c.balance-=amt;
				f.seekg(-byte,ios::cur);
				f.write((char*)&c,sizeof(c));
				f.close();
				bill(ch,amt,0);
				}
			else
				cout<<"\nInsufficient balance\n";
			}
		else
			{
			cout<<"Wrong Pin";
			getch();
			}
	}
if(fp==0)
	cout<<"Wrong account no.";
getch();
f.close();
}

void pin()
{
clrscr();
cstmr c;
char a;
long int ch;
int pin1,pin2,byte=sizeof(c),fp=0,fs=0;
clrscr();
fstream f("bank.dat",ios::binary|ios::in|ios::out);
cout<<"\n\t\t\tPin Change\n";
cout<<"\nEnter Account Number: ";
cin>>ch;
while(f.read((char*)&c,sizeof(c)))
	if(ch==c.account_no)
		if(fs==0)
		{
		fp=1;
		cout<<"\nEnter Original Pin :";
		cin>>pin1;
		if(pin1==c.pin)
			{
			cout<<"\nEnter New Pin :";
			cin>>pin2;
			c.pin=pin2;
			f.seekg(-byte,ios::cur);
			f.write((char*)&c,sizeof(c));
			cout<<"Your new pin is "<<c.pin;
			fs=1;
			getch();
			}
		else
			cout<<"Wrong Pin \n";
	}
if(fp==0)
	{
	cout<<"Wrong account no.";
	getch();
	}
f.close();
}

void amount(int n,long int ch)
{
cstmr c;
int byte=sizeof(c);
fstream f("bank.dat",ios::in|ios::out|ios::binary);
while(f.read((char*)&c,sizeof(c)))
	if(ch==c.account_no)
		{
		c.balance-=n;
		f.seekg(-byte,ios::cur);
		f.write((char*)&c,sizeof(c));
		f.close();
		bill(ch,n,0);
		}
f.close();
}

void fast()
{
clrscr();
cstmr c;
int byte,pin1,fp=0;
long int  ano;
char ch;
ifstream f("bank.dat",ios::binary);
again:
clrscr();
cout<<"\n--------------------------------Fast Withdrawal------------------------------"
     <<"\n1) Rs.200"
     <<"\n2) Rs.500"
     <<"\n3) Rs.1000"
     <<"\n4) Rs.2000"
     <<"\n5) Rs.5000"
     <<"\nEnter amount to be withdrawn(option) ";
cin>>ch;
clrscr();
if(ch<54)
	{
	cout<<"Enter Account Number\n";
	cin>>ano;
	while(f.read((char*)&c,sizeof(c)))
		if(ano==c.account_no)
			{
			fp=1;
			cout<<"Enter pin\n";
			cin>>pin1;
			if(c.pin==pin1)
				{
				switch(ch)
				{
				case '1':if(c.balance>=200)
						amount(200,ano);
					else
						{
						cout<<"\n Insufficient Balance";
						getch();
						}
					break;
				case '2':if(c.balance>=500)
						amount(500,ano);
					else
						{
						cout<<"\n Insufficient Balance";
						getch();
						}
					break;
			       case '3':if(c.balance>=1000)
						amount(1000,ano);
					else
						{
						cout<<"\n Insufficient Balance";
						getch();
						}
					break;
			       case '4':if(c.balance>=2000)
						amount(2000,ano);
					 else
						{
						cout<<"\n Insufficient Balance";
						getch();
						}
					 break;
			       case '5':if(c.balance>=5000)
						amount(5000,ano);
					 else
						{
						cout<<"\n Insufficient Balance";
						getch();
						}
					 break;
				}
				}

			else
				{
				cout<<"Wrong Pin";
				goto again;
				}
	}
if(fp==0)
	{
	cout<<"Wrong account no.";
	getch();
	}
f.close();
}
}
void transfer()
{
clrscr();
//record r;
cstmr c1,c2;
int amt,byte,spot,pin,fp=0,fs,find;
byte=sizeof(c1);
long int ch1,ch2;
fstream f("bank.dat",ios::binary|ios::in|ios::out);
again:
clrscr();
cout<<"\t\t\tTransfer\n\n";
cout<<"Enter acount no. from which money has to be transfered\n";
cin>>ch1;
while(f.read((char*)&c1,sizeof(c1)))
	if(ch1==c1.account_no)
		{
		fp=1;
		fs=3;
		cout<<"Enter pin\n";
		cin>>pin;
		if(c1.pin==pin)
			{
			spot=f.tellp()/byte - 1;
			cout<<"Enter account no. in which money has to be transfered\n";
			cin>>ch2;
			while(f.read((char*)&c2,sizeof(c2)))
				if(c2.account_no==ch2)
					{
					fs=1;
					find=f.tellp()/byte - 1;
					cout<<"Enter money to be transferd\n";
					cin>>amt;
					if(c1.balance>=amt)
						{
						f.seekg(find*byte,ios::beg);
						c2.balance+=amt;
						f.write((char*)&c2,sizeof(c2));
						f.seekg(spot*byte,ios::beg);
						c1.balance-=amt;
						f.write((char*)&c1,sizeof(c1));
						bill(ch1,amt,ch2);
						f.close();
						}
					else
						cout<<"Insufficient balance\n";
					}
			}
		else
			{
			cout<<"Wrong Pin";
			fs=4;
			getch();
			}
		}
if(fp==0)
	{
	cout<<"Wrong account no.";
	getch();
	}
if(fs==3)
	{
	cout<<"Wrong account no.";
	getch();
	}
}

int main()
{
clrscr();
cout<<"\n\n\n\n\n\n"
    <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FRIEND'S BANK~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
getch();
menu();
}
void menu()
{
hi:
clrscr();
char ch;
cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    <<"\n\t\t1) CREATE ACCOUNT"
    <<"\n\t\t2) BALANCE ENQUIRY"
    <<"\n\t\t3) TRANSACTION"
    <<"\n\t\t4) FAST WITHDRAWL"
    <<"\n\t\t5) TRANSFER"
    <<"\n\t\t6) PIN CHANGE"
    <<"\n\t\t7) EXIT"
    <<"\n\t\t\t CHOOSE AN OPTION:";
cin>>ch;
switch(ch)
	{
	case '1': create();
		  break;
	case '2': display();
		  break;
	case '3': trans();
		  break;
	case '4': fast();
		  break;
	case '5': transfer();
		  break;
	case '6': pin();
		  break;
	/*case '7': last();
		  break;*/
	case '7': exit(0);
		  break;
	default : cout<<"\n\t\tWRONG INPUT"
		      <<"\n\t\tPlease try again";
		  getch();
	}
goto hi;
}
