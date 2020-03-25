using namespace std;
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <string.h>

char num[25];
int length,i,k,pwr,j,n,m,l,str,lim,counter,c0unt=0,opr,mlt;
 float digit[100],ans;

void check();
void bracket();
void clrscr()
{
system("cls");
}

void answer() //Prints answer
{
char a;
counter=0;
cout<<"Ans = "<<ans<<endl
	<<"Press 0 to enter new expression : ";
cin>>a;
if(a=='0')
	check();
else
	{
	clrscr();
	cout<<"Have a nice day";
	exit(0);
	}
}

void order() // Main calculation
{
for(k=lim-1;k>str;k--) //To calculate exponent
	if(num[k]=='^')
		{
		opr=k-1;
		while(digit[opr]==NULL)
			opr--;
		if(digit[k+1]==0)
			digit[opr]=1;
		mlt=digit[opr];
		for(j=1;j<digit[k+1];j++)
			digit[opr]*=mlt;
		ans=digit[opr];
		digit[k+1]=NULL;
		num[k]=NULL;
		--c0unt;
		}

for(k=str+1;k<lim;k++)  //To calculate division
	if(num[k]=='/')
		{
		opr=k-1;
		while(digit[opr]==NULL)
			opr--;
		digit[opr]/=digit[k+1];
		ans=digit[opr];
		digit[k+1]=NULL;
		num[k]=NULL;
		--c0unt;
		}
for(k=str+1;k<lim;k++)//To calculate multiply
	if(num[k]=='*')
		{
		opr=k-1;
		while(digit[opr]==NULL)
			opr--;
		digit[opr]*=digit[k+1];
		ans=digit[opr];
		digit[k+1]=NULL;
		num[k]=NULL;
		--c0unt;
		}
for(k=str+1;k<lim;k++)  // To calculate subtraction
	if(num[k]=='-')
		{
		opr=k-1;
		while(digit[opr]==NULL)
			opr--;
		digit[opr]-=digit[k+1];
		ans=digit[opr];
		digit[k+1]=NULL;
		num[k]=NULL;
		--c0unt;
		}
for(k=str+1;k<lim;k++) //To calculate addition
	if(num[k]=='+')
		{
		opr=k-1;
		while(digit[opr]==NULL)
			opr--;
		digit[opr]+=digit[k+1];
		ans=digit[opr];
		digit[k+1]=NULL;
		num[k]=NULL;
		c0unt--;
		}
if(counter==3 && isdigit(num[str-2])==0)
	{
	digit[opr-1]=digit[opr];
	digit[opr]=NULL;
	}
if(c0unt==0 && counter!=3)
	answer();
else
	bracket();
}

void bracket() //Chosses the shortest bracket
{
i=0;
lim=length;
str=i;
for(i;i<length;i++)
	if(isalnum(num[i])==0)
		{
		c0unt++;
		if(num[i]=='(')
			{
			str=i+1;
			counter=2;
			break;
			}
		else
			counter=1;
		}

if(c0unt>0)
	c0unt=0;
else if(c0unt==0)
	{
	ans=digit[0];
	answer();
	}

if(counter==1)
	{
	counter=0;
	goto times;
	}

for(k=str+1;k<length;k++) //To find bracket inside
	if(num[k]=='(')			//another bracket
		{
		str=k+1;
		counter=3;
		}
	else if(num[k]==')')
		{
		lim=k;
		if(isdigit(num[k+1])!=0)
			num[k]='*';
		else
			num[k]=NULL;
		if(counter!=3 && lim<length-1)
			counter=3;
		break;
		}
if(counter==2)
	{
	counter=0;
	if(isdigit(num[str-2])!=0)
		num[str-1]='*';
	else
		num[str-1]=NULL;
	if(str>1)
		counter=3;
	}
else if(counter==3)
	{
	if(isdigit(num[str-2])!=0)
		num[str-1]='*';
	else
		num[str-1]=NULL;
	}

times: //counts no. of operator in a bracket
for(j=str;j<lim;j++)
	if(isalnum(num[j])==0)
		c0unt++;
for(j=str;j<lim;j++)
	if(num[j]==NULL)
		--c0unt;
if(c0unt==0)
	{
	if(num[str-1]!='*')
		digit[str-1]=digit[str];
	bracket();
	}
order();
}

void check() //Checks validity of expression
{
n=0;
m=0;
char a,b;
int j;
clrscr();
cout<<"Enter your expression\n";
cin>>num;
length=strlen(num);

if(isdigit(num[length-1])==0 && num[length-1]!=')')
	goto wrong;

for(i=0;i<length;i++)
	if(isalnum(num[i])==0)
		if(num[i]=='/' || num[i]=='*' || num[i]=='+' || num[i]=='-' || num[i]=='(' || num[i]==')' || num[i]=='^')
			{
            if(num[i]==')' && num[i+1]=='(')
                {
                num[i+1]='*';
                a=num[i+2];
                num[i+2]='(';
                for(j=3;j<i+3;j++)
                    {
                    b=num[i+j];
                    num[i+j]=a;
                    a=b;
                    }
                length++;
                }
			if(num[i]=='('&& isdigit(num[i+1])!=0 || num[i]==')'&& isdigit(num[i-1])!=0)
					{
					if(num[i]=='(')
						++n;
					else
						++m;
					}
			else if(num[i]=='('&& num[i+1]=='(' || num[i]==')'&& num[i-1]==')')
					{
					if(num[i]=='(')
						++n;
					else
						++m;
					}
			else if(num[i]=='('&& num[i+1]=='-')
					{
					++n;
					c0unt=-2;
					}
			else if(num[i]!='('&& num[i]!=')')
					if(isalnum(num[i+1])==0 && num[i+1]!='(')
						goto wrong;
			else if(num[0]=='*' || num[0]=='/' || num[0]=='^')
					goto wrong;
			}
		else if(counter==1)
			counter=0;
		else
			{
			wrong:
			cout<<"Invalid";
			exit(0);
			}
	else if(isalpha(num[i])==0)
		{
		j=i+1;
		digit[i]=num[i]-48;
		while(isdigit(num[j])!=0)
			{
			pwr++;
			j++;
			}
		for(k=1;k<=pwr;k++)
			digit[i]=digit[i]*10 + num[i+k]-48;
		for(k=l;k<i;k++)
				digit[k]=NULL;
		if(num[i-2]=='('&& num[i-1]=='-')
			{
			num[i-1]=NULL;
			if(isdigit(num[i-3])!=0)
				{
				digit[i-1]=-digit[i];
				num[i-2]='*';
				}
			else
				{
				digit[i-2]=-digit[i];
				num[i-2]=NULL;
				}
			digit[i]=NULL;
			num[j]=NULL;
			++m;
			counter=1;
			}
		else if(num[0]=='-')
			{
			ans=-digit[1];
			answer();
			}
		else if(num[0]=='+')
			{
			ans=digit[1];
			answer();
			}
		l=i+1;
		i=j-1;
		pwr=0;
		}
	else
		goto wrong;

for(k=l;k<i;k++)
		digit[k]=NULL;
if(n!=m)
	goto wrong;
bracket();
}

int main()
{
check();
}
