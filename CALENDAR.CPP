#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdio.h>
using namespace std;

void menu();

int i,dd,mm,week,leap,leap1,leap4;
long int yy;
char days[7][10]={"Sunday","Monday","Tueday","Wednesday","Thursday","Friday","Saturday"},era[3];

class mnth       //class of month with name and last date of month
{
public:
char name[11];
int last;
void enter()
	{
	cout<<"Month : ";
	cin>>name;
	cout<<"No.of days : ";
	cin>>last;
	}
};

void store()   //function to store details of months before hand
{
mnth m;
ofstream f("moth.dat",ios::binary|ios::app);
cout<<"Enter details of each month\n";
for(i=0;i<12;i++)
	{
	m.enter();
	f.write((char*)&m,sizeof(m));
	}
f.close();
exit(0);
}

void print(mnth m)   //prints the given month
{
dd=m.last;
if(leap==0 && mm==2 && (leap1!=0 || leap4==0))
	dd++;
cout<<endl<<endl;
cout<<"\t\t      "<<m.name<<endl;
for(i=0;i<7;i++)
	{
	for(int j=0;j<3;j++)
		cout<<days[i][j];
	cout<<"\t";
	}
cout<<endl;
for(i=0;i<week;i++)
	cout<<"   \t";
for(i=1;i<=dd;i++)
	{
	if(i<10)
		cout<<" ";
	cout<<i<<" ";
	cout<<"\t";
	week++;
	if(week==7)
		{
		week=0;
		cout<<endl;
		}
	}
}

void yearcheck()   //returns the first day of the year
{
int check=0,rem;
while(check==0)
	{
	if(yy==2000 || yy==2005)
		{
		week=6;
		check=1;
		}
	else
	if(yy==2001)
		{
		week=1;
		check=1;
		}
	else
	if(yy==2002)
		{
		week=2;
		check=1;
		}
	else
	if(yy==2003)
		{
		week=3;
		check=1;
		}
	else
	if(yy==2004)
		{
		week=4;
		check=1;
		}
	else
	if(yy==2006)
		{
		week=0;
		check=1;
		}
	else
	if(yy==1999)
		{
		week=5;
		check=1;
		}
	rem=yy%4;
	if(check!=1)
		if(yy<1999)
			if(rem==0)
				yy+=5;
			else
			if(rem==1)
				yy+=6;
			else
			if(rem==2)
				yy+=6;
			else
			if(rem==3)
				yy+=11;
		if(yy>2006)
			if(rem==0)
				yy-=6;
			else
			if(rem==1)
				yy-=5;
			else
			if(rem==2)
				yy-=11;
			else
			if(rem==3)
				yy-=6;
	}
check=0;
}

void monthcheck() //returns the first day of the month
{
mnth c;
ifstream f("moth.dat",ios::binary);
for(i=1;i<mm;i++)
	{
	f.read((char*)&c,sizeof(c));
		week+=c.last;
	}
if(leap==0 && mm>2 && (leap1!=0 || leap4==0))
	week++;
week%=7;
}

void day()  //function to show day of the given date
{
system("cls");
cout<<"Enter Date (dd)   : ";
cin>>dd;
if(dd<1 || dd>31)
	{
	cout<<"Sorry there is no such date in a month ";
	getch();
	menu();
	}
cout<<"      Month (mm)  : ";
cin>>mm;
if(mm<1 || mm>12)
	{
	cout<<"Sorry there are only 12 months in a year ";
	getch();
	menu();
	}
else if(mm==2 && dd>29)
	{
	cout<<"February has only 29 days max";
	getch();
	menu();
	}
else if(dd>30 && (mm==4 || mm==6 || mm==9 || mm==11))
	{
	cout<<"Apr, Jun, Sep and  Nov have only 30 days";
	getch();
	menu();
	}
cout<<"      Year (yyyy) : ";
cin>>yy;
leap=yy%4;
leap1=yy%100;
leap4=yy%400;
if((leap!=0 || (leap1==0 && leap4!=0))&& mm==2 && dd==29)
    {
    cout<<"February has only 28 days in this year";
    getch();
    menu();
    }
yearcheck();
monthcheck();
week+=dd;
week--;
week%=7;
cout<<"\nIt's a "<<days[week];
getch();
menu();
}

void month() //function to take and show details of a month
{
system("cls");
char per[4],per1[4];
mnth c;
cout<<"Enter first three letters of the month : ";
cin>>per;
if(strlen(per)!=3)
	{
	cout<<"Only three letters allowed";
	getch();
	menu();
	}
for(i=0;i<3;i++)
	per[i]=toupper(per[i]);
cout<<"Enter year : ";
cin>>yy;
ifstream f("moth.dat",ios::binary);
while(f.read((char*)&c,sizeof(c)))
	{
	mm++;
	for(i=0;i<3;i++)
		per1[i]=c.name[i];
	if(strcmp(per1,per)==0)
		break;
	}
f.close();
leap=yy%4;
leap1=yy%100;
leap4=yy%400;
yearcheck();
monthcheck();
print(c);
getch();
menu();
}

void year() //function to print the calendar of given year
{
system("cls");
mnth c;
ifstream f("moth.dat",ios::binary);
cout<<"Enter the year (yyyy) : ";
cin>>yy;
leap=yy%4;
leap1=yy%100;
leap4=yy%400;
yearcheck();
while(f.read((char*)&c,sizeof(c)))
	{
	mm++;
	print(c);
	}
getch();
menu();
}

void menu()
{
system("cls");
int n=0;
week=0;
mm=0;
mnth c;
ifstream f("moth.dat",ios::binary);
while(f.read((char*)&c,sizeof(c)))
	n++;
if(n!=12)
	store();
f.close();
cout<<"\t\t\tMenu\n"
	<<"   What do you seek\n"
	<<"1) Day\n"
	<<"2) Month\n"
	<<"3) Year\n"
	<<"4) Exit\n"
	<<"Enter index number : ";
cin>>n;
if(n==1)
	day();
else if(n==2)
	month();
else if(n==3)
	year();
else if(n==4)
	exit(0);
else
	{
	cout<<"Wrong input";
	getch();
	menu();
	}
}

int main()
{
menu();
return 0;
}
