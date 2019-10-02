#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream.h>
struct teacher
{
	int teacher_code;
	char name[20];
	int noofclasses;
};
struct division
{
	int tt[6][6];
	int t_subs[5];
};
void teacherprofile()
{
	fstream fteach("Teacher.dat",ios::binary|ios::app);
	teacher temp;
	int ch;
	do
	{
			cout<<"This is where you enter the  details of the teacher"<<endl;
			cout<<"1. Store a new teacher profile"<<endl;
			cout<<"2. Exit"<<endl;
			cout<<"Enter your choice:";
			cin>>ch;
			cout<<"Recommended subject codes"<<endl;
			cout<<"Maths: 100 series"<<endl;
			cout<<"Physics: 200 series"<<endl;
			cout<<"Chemistry: 300 series"<<endl;
			cout<<"English: 400 series"<<endl;
			cout<<"Computers: 500 series"<<endl;
				switch(ch)
				{
					case 1:
						cout<<"Enter the name of the teacher:"<<endl;
						gets(temp.name);
						cout<<"Enter the teacher code:"<<endl;
						cin>>temp.teacher_code;
						temp.noofclasses=0;
						fteach.write((char*)&temp,sizeof(temp));
						break;
					case 2:
						break;
					default:
						cout<<"Enter correct value"<<endl;
				}
	}while(ch!=2);
	fteach.close();
}

void generatett()
{
	randomize();
	ofstream fclass("Classes.dat",ios::binary|ios::trunc);
	ifstream fteach("Teacher.dat",ios::binary);
	division d;
	teacher t;
	for(int k=0;k<6;k++)
	{
		d.tt[0][0]=-1;
		int rundweek[5]={0,0,0,0,0},v,looper=1;
		for(int i=1;i<=5;i++)
		{
			d.tt[i][0]=-1;
			int runday[5]={0,0,0,0,0};
			for(int j=1;j<=5;j++)
			{
				d.tt[0][j]=-1;
				while(looper>0)
				{
					v=random(5);
					if(runday[v]<2 && rundweek[v]<6)
					{
						d.tt[i][j]=v;
						runday[v]++;
						rundweek[v]++;
						break;
					}
					else
						 continue;
				}
			}
		}

		int z;
		for(int j=0;j<=4;j++)
		{
			z=j*100+100+random(3)+1;
		 //	while(fteach.read((char*)&t,sizeof(t)))
		 //	{
		 //	if(t.teacher_code==z && t.noofclasses<=2)
		 //		{
					d.t_subs[j]=z;
		 //			cout<<z;
		 //		}		       //		else
		 //			continue;
		 //	}
			 cout<<k<<"-"<<z;   //I used this to check if values were entering the array
	       }
		fclass.write((char*)&d,sizeof(d));
	}
	fteach.close();
	fclass.close();
}

void display()
{
	division d;
	teacher t;
	fstream fteach("Teachers.dat",ios::binary|ios::in|ios::out);
	fstream fclass("Classes.dat",ios::binary|ios::in);
	while(fclass.read((char*)&d,sizeof(d)))
	{
		cout<<endl<<endl;
		for(int i=0;i<6;i++)
		{
			for(int j=0;j<6;j++)
			{
				if(i==0)
				{
					while(j!=0)
					{
						switch(j)
						{
							case 1:
							cout<<"\t\tMon\t";
							break;
							case 2:
							cout<<"Tues\t";
							break;
							case 3:
							cout<<"Wed\t";
							break;
							case 4:
							cout<<"Thu\t";
							break;
							case 5:
							cout<<"Fri";
							break;
						}
						break;
					}
				}
				if(i==1 && j==0)
					cout<<endl<<"8:00-9:00\t";
				else if(i==2 && j==0)
					 cout<<endl<<"9:00-10:00\t";
				else if(i==3 && j==0)
					 cout<<endl<<"10:30-11:30\t";
				else if(i==4 && j==0)
					 cout<<endl<<"11:30-12:30\t";
				else if(i==5 && j==0)
					 cout<<endl<<"12:30-1:30\t";
				else if(d.tt[j][i]==0)
					 cout<<"Maths\t";
				else if(d.tt[j][i]==1)
					 cout<<"Physics\t";
				else if(d.tt[j][i]==2)
					 cout<<"Chem\t";
				else if(d.tt[j][i]==3)
					 cout<<"English\t";
				else if(d.tt[j][i]==4)
					 cout<<"Comp\t";
			}
		}
		cout<<endl;
		cout<<"Teacher information"<<endl;
		for(int h=0;h<5;h++)
		{
			cout<<d.t_subs[h]<<endl;
			fteach.seekg(0,ios::beg);
			while(fteach.read((char*)&t,sizeof(t))) //this loop doesn't execute for some reason
			{
				if(d.t_subs[h]==t.teacher_code)
				{
					if(h==0)
						cout<<"Maths:"<<t.name<<endl;
					else if(h==1)
						cout<<"Physics:"<<t.name<<endl;
					else if(h==2)
						cout<<"Chemistry:"<<t.name<<endl;
					else if(h==3)
						cout<<"English:"<<t.name<<endl;
					else if(h==4)
						cout<<"Computer:"<<t.name<<endl;
				}
			}
		}
	}
	fteach.close();
	fclass.close();
}

void main()
{
	int ch,flag=0,count;
	teacher temp;
	do
	{
		cout<<"\t\t WELCOME TO TIME TABLE GENERATOR"<<endl<<endl;
		cout<<"1. Enter information for new teacher"<<endl;
		cout<<"2. Generate new time table for 6 classes"<<endl;
		cout<<"3. Display current saved time table along with teachers"<<endl;
		cout<<"4. Exit"<<endl;
		cin>>ch;

		switch(ch)
		{
			case 1:
			{	teacherprofile();
				break;
			}
			case 2:
			{	fstream fteach("Teacher.dat",ios::binary|ios::in);
				count=0;
				while(fteach.read((char*)&temp,sizeof(temp)))
					count++;
				if(count<15)
					cout<<"Not enough number of teachers"<<endl;
				else
					generatett();
				fteach.close();
				break;
			}
			case 3:
			{	display();
				break;
			}
			case 4:
			{	flag=1;
				break;
			}
			default:
				cout<<"Enter correct value"<<endl;
		 }

	 }while(flag==0);
}
