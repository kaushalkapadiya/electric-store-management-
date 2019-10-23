#include<conio.h>
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class company
	{
		int price;
		int p;
		char cname[10];
	public:
		company()
			{
			}
		company(int price,char *cname)
			{
			this->price=price;
			strcpy(this->cname,cname);

			}
		void prin()
			{
			cout<<p<<'\t';

			cout<<"cname"<<cname<<'\t';
			cout<<"price"<<price<<endl;

			}
		int rprice()
			{
			return price;
			}
		/*int compare(company &c)
		{
		  if(strcmp(cname,c.cname))
		  {
		    if(price==c.price)
		    {
		      return 1;
		    }
		    else return -1;
		  }
		  else return -1;
		}*/
		friend void addcompanyfile(ofstream &,int n,company *c);
		friend void outcompanyfile(ifstream &,int n,company *c);
	};
class item
	{
		char name[10];
		int p;
		char size[12];
		company *c;
		int n;
	public:
		item() {}
		item(char *name,char *size,company c1[],int n,int p=0)
			{
				this->p=p;
			this->n=n;
			strcpy(this->name,name);
			strcpy(this->size,size);
			c=new company[n];
			for(int i=0; i<n; i++)
				{
				c[i]=c1[i];
				//  c[i].prin();
				}

			}
		void prin()
			{
			cout<<p<<'\t'<<"name"<<name<<'\t'<<"size"<<size<<endl;
			for(int i=0; i<n; i++)
				{
				c[i].prin();
				}
			}
		char* rname()
			{
			return name;
			}
		int rprice()
			{
			return c->rprice();
			}
		/*int compare(item &i)
		{
		  if(strcmp(name,i.name))
		    {
		      if(c->compare(i.c))
		      return 1;
		      else return -1;

		    }
		    else
		    return -1;
		}*/
		friend void outitemfile(ifstream &,item *i);
		friend void additemfile(ofstream &,item *i,int n);
		friend void addcompanyfile(ofstream &,int n,company *c);
		friend void outcompanyfile(ifstream &,int n,company *c);

		friend item search(int i,int j);
	};
item search(int j,int k)
	{
	company c;
	item i,i1;
	ifstream fin;
	fin.open("item.txt",ios::app);
	while(!fin.eof())
		{
		outitemfile(fin,&i);
		if(i.p==j)
			{
			c=i.c[k-1];
			i1=item(i.name,i.size,&c,1);
			fin.close();
			return i1;
			}
		}
	fin.close();
	}

void additemfile(ofstream &fout,item *i,int n)
	{

	fout<<n<<'\t'<<i->name<<"\t"<<i->size<<"\t"<<i->n;
	addcompanyfile(fout,i->n,i->c);
	fout<<'\n';

	}
void outitemfile(ifstream &fin,item *i)
	{
//	while(!fin.eof())
	int p;
	char name[10];
	char size[15];
	int n;
	company *c;

//		{
		fin>>p>>name>>size>>n;
		outcompanyfile(fin,n,c);
		*i=item(name,size,c,n,p);
		//k.prin();
	}

void addcompanyfile(ofstream &fout,int n,company *c)
	{
	for(int i=0; i<n; i++)
		{
		fout<<"\t"<<i<<'\t'<<c[i].cname<<'\t'<<c[i].price;
		}
	}
void outcompanyfile(ifstream &fin,int n,company *c)
	{

	for(int i=0; i<n; i++)
		{
		fin>>c[i].p>>c[i].cname>>c[i].price;
		}
	}


class cart
	{
		item i[10];
		int n;
		int amount;
	public:
		cart()
			{
			n=-1;
			amount=0;
			}
		/*  int search(item i)
		  {
		    for(int j=0;j<n;j++)
		    {
		    if(i[j]->compare(i)==1)
		    return j;
		    }
		    return -1;
		  }*/
		void add(item &i)
			{
			n++;
			i.prin();
			this->i[n]=i;
			i.prin();
			}
		void remove(int n1)
			{
			if(n1>n)
				cout<<"it is not present";
			else if(n==n1)
				n--;
			else
				{
				for(int j=n1; j<n; j++)
					{
					i[j]=i[j+1];
					}
				n--;
				}

			}
		void list()
			{
			for(int j=0; j<=n; j++)
				{
				i[j].prin();
				}
			}
		int totalamount()
			{
			for(int j=0; j<=n; j++)
				{
				amount+=i[j].rprice();
				}
			return amount;
			}

	};

class user
	{
		char name[10];
		char pass[10];
		cart c;
	public:
		user() {}
		user(char *name,char *pass)
			{
			strcpy(this->name,name);
			strcpy(this->pass,pass);
			}
		void add(item &i)
			{
			c.add(i);
			}
		void remove(int n1)
			{
			c.remove(n1);
			}
		void list()
			{
			c.list();
			}
		char* uname()
			{
			return name;
			}
		char* upass()
			{
			return pass;
			}
		void prin()
			{
			cout<<"uname"<<name<<endl<<"pass"<<pass<<endl;
			}
		int totalamount()
			{
			return c.totalamount();
			}
		friend void adduserfile(ofstream &,user *u);
		friend void outuserfile(ifstream &,user *u);
	};
void adduserfile(ofstream &fout,user *u)
	{
	fout<<u->name<<"\t"<<u->pass<<endl;
	}
void outuserfile(ifstream &fin,user *u)
	{
	fin>>u->name>>u->pass;
	}
class bill
	{

	public:
		void prin(user *u)
			{
			cout<<u->totalamount();
			}

	};
class store
	{
		user u;
		item i;
		char name[10];
		char pass[10];
		int n1;
		int n2;
	public:
		store()
			{
			n1=n2=-1;
			}
		store(char *name,char *pass)
			{
			ofstream fout;
			fout.open("sulogin.txt",ios::app);
			strcpy(this->name,name);
			strcpy(this->pass,pass);
			fout<<this->name<<'\t'<<this->pass;
			fout.close();
			}
		int sulogin(char *name,char *pass)
			{

			ifstream fin;
			fin.open("sulogin.txt",ios::app);
			fin>>this->name>>this->pass;

			if(strcmp(this->name,name)==0)
				{
				if(strcmp(this->pass,pass)==0)
					return 1;
				else return 0;
				}
			else return 0;
			fin.close();
			}
		int  login(char *name,char *pass)
			{
			ifstream fin;
			fin.open("login.txt",ios::app);

			while(!fin.eof())
				{
				outuserfile(fin,&u);
				if(strcmp(name,u.uname())==0)
					{
					if(strcmp(pass,u.upass())==0)
						return 1;
					else return 0;
					}
				else return 0;
				}
			fin.close();
			}
		void newuser(user *u1)
			{
			n1++;
			ofstream fout;
			fout.open("login.txt",ios::app);
			adduserfile(fout,u1);
			fout.close();
			}
		void newitem(item *i1)
			{
			n2++;
			ofstream fout;
			fout.open("item.txt",ios::app);
			//ifstream fin;
			//fin.open("item.txt",ios::app);
			//fin>>n2;
			//fin.close();
			additemfile(fout,i1,n2++);
			fout.close();
			}
		void removeuser(char *name)
			{
			ofstream fout;
			fout.open("login.txt",ios::out);
			ifstream fin;
			fin.open("login.txt",ios::app);
			while(!fin.eof())
				{
				outuserfile(fin,&u);
				if(strcmp(name,u.uname()))
					{
					continue;
					}
				else
					{
					adduserfile(fout,&u);
					}
				}
			fout.close();
			fin.close();
			}
		void removeitem(char *name)
			{
			int n=-1;
			int lineno=-1;
			int x=0;
			ofstream fout;
			fout.open("item.txt",ios::app);
			ifstream fin;
			fin.open("item.txt",ios::app);
			while(!fin.eof())
				{

				outitemfile(fin,&i);
				if(strcmp(name,i.rname()))
					{
						lineno=x;
					x++;
					}
				else
					{
					x++;
					//additemfile(fout,&i,n);
					}
				}
				fin.clear();
	fin.seekg(0);
		char record[100];
	x=0;
	while(fin.getline(record,100,'\n'))
	{
	  //strcpy(ine=fin,getline('\n');
	  if(x!=lineno){
	   fout<<record<<endl;
	   // cout<<record<<endl;

	   }
	   x++;

       }
			fout.close();
			fin.close();
			}

		void listuser()
			{
			ifstream fin;
			fin.open("login.txt",ios::app);
			while(!fin.eof())
				{
				outuserfile(fin,&u);
				cout<<u.uname()<<"\t"<<u.upass()<<endl;
				}
			fin.close();
			}
		void listitem()
			{
			ifstream fin;
			fin.open("item.txt",ios::in);
			fin.seekg(ios::beg);

			while(!fin.eof())
				{
				outitemfile(fin,&i);
				i.prin();

				}
			fin.close();
			}
		void search(char *name)
			{
			ifstream fin;
			fin.open("item.txt",ios::app);
			while(!fin.eof())
				{
				outitemfile(fin,&i);
				if(strcmp(name,i.rname())==0)
					{
					i.prin();
					break;
					}
				}

			fin.close();
			}


	};


int main()
	{
	company c[10];
	item i;
	store s;
	user u;
	ofstream fout;
	ifstream fin;
	char name[5];
	char password[5];
	int flag;
	int choice;

	while(1)
		{
		cout<<"enter 1 to superlogin, 2 to user login, 3 to new user, 4 to new superuser,5 to quit"<<endl;
		cin>>choice;
		switch (choice)
			{
			case 1:
				cout<<"enter name"<<endl;
				cin>>name;
				cout<<"enter password"<<endl;
				cin>>password;
				flag=s.sulogin(name,password);
				if(flag==1)
					{
					cout<<"login successfully"<<endl;
					goto x;
					}
				else
					cout<<"incorrect details"<<endl;
				break;


			case 2:

				cout<<"enter name"<<endl;
				cin>>name;
				cout<<"enter password"<<endl;
				cin>>password;
				flag=s.login(name,password);
				if(flag==1)
					{
					cout<<"login successfully"<<endl;
					goto y;
					}
				else
					cout<<"incorrect details"<<endl;
				break;
			case 3:

				cout<<"enter name"<<endl;
				cin>>name;
				cout<<"enter password"<<endl;
				cin>>password;
				u=user(name,password);
				s.newuser(&u);
				break;
			case 4:
				cout<<"enter name"<<endl;
				cin>>name;
				cout<<"enter password"<<endl;
				cin>>password;
				s=store(name,password);
				break;
			case 5:

				exit(0);
			default:


				cout<<"wrong choice"<<endl;
			}
		}
x:
	while(1)
		{
		cout<<"enter 1 to listitem,2 to listuser,3 to add item,4 to removeitem,5 to removeuser, 6 to search item,7 to quit"<<endl;
		cin>>choice;
		switch(choice)
			{
			case 1:
				s.listitem();
				break;
			case 2:
				s.listuser();
				break;
			case 3:
				int n;

				int price;
				char size[5];
				cout<<"enter the number of company"<<endl;
				cin>>n;
				for(int i=0; i<n; i++)
					{
					cout<<"enter the comapny name"<<endl;
					cin>>name;
					cout<<"enter the price"<<endl;
					cin>>price;
					c[i]=company(price,name);
					}
				cout<<"enter the item name"<<endl;
				cin>>name;
				cout<<"enter the size"<<endl;
				cin>>size;
				i=item(name,size,c,n);
				s.newitem(&i);
				cout<<"added successfully";
				break;
			case 4:

				cout<<"enter the name of the item "<<endl;
				cin>>name;
				s.removeitem(name);
				cout<<"removed sucessfully"<<endl;
				break;
			case 5:

				cout<<"enter the name of user"<<endl;
				cin>>name;
				s.removeuser(name);
				cout<<"removed sucessfully"<<endl;

				break;
			case 6:
				cout<<"enter the name"<<endl;
				cin>>name;
				s.search(name);
				break;
			case 7:

				exit(0);
			default:
				cout<<"enter wrong choice"<<endl;

			}
		}
	goto z;
y:
	while(1)
		{
		int choice;
		cout<<"enter 1 to listitem,2 to add,3 to listcart,4 to remove,5 to get bill "<<endl;
		cin>>choice;
		switch(choice)
			{
			case 1:
				s.listitem();
				break;
			case 2:
				int j,k;
				cout<<"enter the j,k"<<endl;
				cin>>j>>k;
				i=search(j,k);
				u.add(i);
				break;
			case 3:
				u.list();
				break;
			case 4:
				int n;
				cout<<"enter the number"<<endl;
				cin>>n;
				u.remove(n);
				break;
			case 5:

				bill b;
				b.prin(&u);
				cout<<"thankyou !"<<endl;

				exit(0);
				break;
			default:
				cout<<"wrong choice"<<endl;


			}

		}

z:
	cout<<"thankyou !"<<endl;
	}
