
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cmath>
#include <string>
//#include <termios.h>
#include <unistd.h>
#include <time.h>

using namespace std;

class person;
class admin;
class passport;
class passenger;
class city;
class Airport;
class Airplane;
class Flight;
class System;

//////////////////////////////////////////////////////////////////////////
class person{
	protected:
	string loginID;
	string password;
	public:
	void setLogInID(string n);
	void setPassword(string n);
	string getLogInID(string n);
	string getPassword(string n);
	bool passwordValidation();
	virtual void login()=0;
};
void person :: setLogInID(string n)
{
	loginID = n;
}
void person :: setPassword(string n)
{
	password = n;
}
string person :: getLogInID(string n)
{
	return loginID;
}
string person :: getPassword(string n)
{
	return password;
}
bool person :: passwordValidation()
{
	int size= password.length();
	bool checkNum=0;
	bool checkChar=0;
	bool checkAlphabet=0;
	bool checkLen=0;
	if(size>=8)
	{
		checkLen=1;
	}
	for(int i=0; i<size;i++)
	{
		if(password[i]>='0' && password[i]<='9')
		{
			checkNum=1;
		}
		if(password[i]>='a' && password[i]<='z')
		{
			checkAlphabet=1;
		}
		if(password[i]>='A' && password[i]<='Z')
		{
			checkAlphabet=1;
		}
		else
		{
			checkChar=1;
		}
	}
	if(checkChar==1 && checkAlphabet==1 && checkNum==1 && checkLen==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//////////////////////////////////////////////////////////////////////////
struct Passport{
	char type;
	bool VISAstamp;
	string country;
};
//////////////////////////////////////////////////////////////////////////
class passenger: public person{
	string CNIC;
	Passport passport;
	public: 
	Flight *hptr;
	Flight *bptr;
	void setCNIC( string n);
	void setPassportType( char t);
	void setPassportVISA( bool b);
	string getCNIC();
	char getPassportType();
	bool getPassportVISA();
	void login();
	bool CNIC_check();
};
void passenger :: setCNIC( string n)
{
	CNIC = n;
}
void passenger :: setPassportType( char t)
{
	passport.type = t;
}
void passenger :: setPassportVISA( bool b)
{
	passport.VISAstamp = b;
}
string passenger :: getCNIC()
{
	return CNIC;
}
char passenger :: getPassportType()
{
	return passport.type;
}
bool passenger :: getPassportVISA()
{
	return passport.VISAstamp;
}
bool passenger :: CNIC_check()
{
	bool t=true;
	if(CNIC[13]=='\0')
	{
		for(int i=0; i<13; i++)
		{
			if(CNIC[i]<48 || CNIC[i]>57 )
			{
				cout << "INVALID CNIC\n";
				t=false;
				break;
			}
		}
	}
	else
	{
		t= false;
	}
	return t;
}
void passenger :: login()
{

	bool x=0;
	do{
		cout << "Enter CNIC: ";
		cin >> CNIC;
		if(CNIC_check()==0)
		{
			cout << "INVALID CNIC\n";
		}
	}while(CNIC_check()==0);
	
	cout << "For local passport, Enter 'l'\nFor International Passport, Enter 'i'\n";
	cin >> passport.type;
	if(passport.type=='l')
		passport.VISAstamp=0;
	else
		passport.VISAstamp=1;
	char check;
	cout << "Do you have an account in the NPAFS:[y/n]\n";
	cin >> check;
	if(check=='y')
	{
		do{
			cout << "Enter log in ID: ";
			cin >> loginID;
			cout << "Enter password: ";
			cin >> password;
			fstream data("passenger.txt", ios::in);
			
			if(!data.is_open())
				cout<<"File not found\n";
			else
			{
			
				
				bool str=0;	
				while(!data.eof())
				{
					string buff="\0";
					getline(data, buff);
					if(buff==loginID)
					{
						string pass="\0";
						getline(data, pass);
						if(pass==password)
						{
							cout << "LOG IN SUCCESSFUL\n";
							x=1;
							break;
						}
						else
						{
							cout << "PASSWORD DOES NOT MATCH\n";
						}
					}
					
				}
			}
			data.close();
		}while(x==0);
		
	}	
	if (check=='n')
	{
		fstream data("passenger.txt", ios::app);
		cout << "REGISTER NOW\n";
		cout << "Enter log in ID: ";
		cin >> loginID;
		do{
			cout << "Enter password with atleast 1 digit, 1 alphabet and 1 special chharacter: ";
			cin >> password;
			if(passwordValidation()==0)
			{
				cout << "PASSWORD DOES NOT MEET CRITERIA\n";
			}
		}while(passwordValidation()==0);
		data << loginID << endl;
		data << password << endl;
		data.close();
	}
}

//////////////////////////////////////////////////////////////////////////
struct Airplane{
	int ID=-1;
	int capacityE=50;
	int capacityB=10;
};
///////////////////////////////////////////////////////////////////////////
struct Airport{
	int ID;
	Airplane runway[5];
};
///////////////////////////////////////////////////////////////////////////
class city{
	string name;
	Airport port[2]; //0 index for North, 1 for South
	Airplane planes[20];
	public:
	void setName(string n);
	string getName();
	void setAirport(int index,int id);
};
void city :: setName(string n)
{
	name=n;
}
string city :: getName()
{
	return name;
}
void city :: setAirport(int index,int id)
{
	port[index].ID=id;
}
///////////////////////////////////////////////////////////////////////////
struct Time{
	int min;
	int hours;
};
///////////////////////////////////////////////////////////////////////////
class Flight{
	string depCity="\0";
	Airplane AP;
	string destinationCity="\0";
	Time arr;
	Time dep;
	int ID;
	char type;// local or international
	int durationInHours;
	int ticketPrice;
	int tax;
	int OccupancyB;//business class
	int OccupancyE;//economy class
	int stops;
	int distance;
	string stopovers[5];
	public:
	void calculateDistance();
	void changeCapacity(int a,int b);
	int getPlaneID();
	void setPlaneID(int n);
	string getdepCityName();
	void setdestinationCity(string y);
	string getDestinationCity();
	void addingPassenger();
	void setDepTime(int x, int y);
	void setArrTime(int x, int y);
	void setStops(int n);
	void calPrice();
	int getPrice();
	friend ostream& operator<< (ostream& out, Flight& right);
	void RandInitializationL(int n);
	void RandInitializationI(int n);
	void SF();
	void calP();
};
void Flight :: calculateDistance()
{
	if (type=='l')
	{
		distance=rand()%500+750;
	}
	else
	{
		distance=6000+(1000*stops);
	}
}	
void Flight :: changeCapacity(int a,int b)
{
	AP.capacityB=a;
	AP.capacityE=b;
}
int Flight :: getPlaneID()
{
	return AP.ID;
}
void Flight :: setPlaneID(int n)
{
	AP.ID =n;
}
string Flight :: getdepCityName()
{
	return depCity;
}
void Flight :: setdestinationCity(string y)
{
	destinationCity=y;
}
string Flight :: getDestinationCity()
{
		return destinationCity;
}
void Flight :: addingPassenger()
{
	char ch;
	cout << "Do you want to book a seat in business class or economic class:\nEnter 'b' for Business\nEnter 'e' for Economic\n";
	cin >> ch;
	if (ch=='b')
	{
		OccupancyB++;
	}
	if (ch=='e')
	{
		OccupancyE++;
	}
	cout << "********Passenger added to flight******\n";
}
void Flight :: setDepTime(int x, int y)
{
	dep.hours=x;
	dep.min=y;
}
void Flight :: setArrTime(int x, int y)
{
	arr.hours=x;
	arr.min=y;
}
void Flight :: setStops(int n)
{
	if(n>5)
	{
		cout << "A flight can have a maximum of 5 stopovers!\nEnter new number of stopovers:";
		cin >> n;
	}
	stops = n;
	for(int i=0; i<n; i++)
	{
		cout << "Enter Stopover#" << i+1 << " :";
		cin >> stopovers[i];
	}
	calculateDistance();
}
void Flight :: calPrice()
{
	int rs;
	if(type=='l')
	{
		rs=10000;
		rs=rs*durationInHours;
		tax=(rs/100)*5;
	}
	else
	{
		rs=20000;
		rs=rs*durationInHours;
		tax=(rs/100)*10;
	}
	ticketPrice=rs+tax;
	cout << endl << "Tax: " << tax << "Rs" << endl << "Ticket Price inclusive of tax: " << ticketPrice << "Rs" << endl;
}
void Flight :: calP()
{
	int rs;
	if(type=='l')
	{
		rs=10000;
		rs=rs*durationInHours;
		tax=(rs/100)*5;
	}
	else
	{
		rs=20000;
		rs=rs*durationInHours;
		tax=(rs/100)*10;
	}
	ticketPrice=rs+tax;
}
int Flight :: getPrice()
{
	return ticketPrice;
}
ostream& operator<< (ostream& out, Flight& right)
{
		cout << "\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		cout << "FLIGHT DETAILS ID#" << right.ID << endl;
		cout << "Departure: " << right.depCity << "          Destination: " << right.destinationCity <<"        Distance: "<< right.distance;
		cout << "\nDeparture Time: " << right.dep.hours <<":" << right.dep.min << "      Arrival Time: " << right.arr.hours <<":" << right.arr.min;
		cout << "\nAirplane ID: " <<right.AP.ID<< "          Airplane Capacity:   Ecomonic Class: " << right.AP.capacityE <<"     Business Class: " << right.AP.capacityB; 
		cout<< "\nSeats Occupied:     Business Class:" << right.OccupancyB << "     Economy Class: " << right.OccupancyE << endl;
		if(right.stops==0)
		{
			cout << "No Stopovers: Direct Flight\n";
		}
		else
		{
			cout << "STOPOVERS: ";
			for(int i=0;i<right.stops;i++)
			{
				cout << right.stopovers[i];
				if(i!=right.stops-1)
				{
					cout << ",";
				}
			}
			cout << endl;
		}
		right.calPrice();
		cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
		return out;
}
void Flight :: RandInitializationL(int n)
{
	string c[5]={"Islamabad\0","Karachi\0","Lahore\0","Peshawar\0","Quetta\0"};
	ID=n;
	int x=rand()%5;
	depCity=c[x];
	setPlaneID(n);
	int y;
	do{
		y=rand()%5;
	}while(x==y);
	setdestinationCity(c[y]);
	arr.min=rand()%59+1;
	dep.hours=rand()%12;
	dep.min=rand()%59+1;
	arr.hours=dep.hours+rand()%10;
	type='l';
	durationInHours=arr.hours-dep.hours;
	OccupancyB=rand()%8;
	OccupancyE=rand()%45;
	calculateDistance();
	calP();
}
void Flight:: RandInitializationI(int n)
{
	string c[5]={"Islamabad\0","Karachi\0","Lahore\0","Peshawar\0","Quetta\0"};
	ID=n;
	int x=rand()%5;
	depCity=c[x];
	setPlaneID(n);
	string C[25]={"UAE\0","USA\0","UK\0","India\0","China\0","Oman\0","Yemen\0","Iran\0","Iraq\0","Qatar\0","Kuwait\0","Bhutan\0","Nepal\0","Kyrgyzstan\0","Tajikistan\0","Greenland\0","Iceland\0","Russia\0","Egypt\0","Syria\0","Japan\0","Bangladesh\0","Mali\0","Libya\0","Korea\0"};
	int y=rand()%25;
	setdestinationCity(C[y]);
	arr.min=rand()%59+1;
	dep.hours=rand()%12;
	dep.min=rand()%59+1;
	arr.hours=dep.hours+rand()%10;
	type='i';
	durationInHours=arr.hours-dep.hours;
	OccupancyB=rand()%8;
	OccupancyE=rand()%45;
	stops=rand()%4;
	calculateDistance();
	calP();
	for(int i=0;i<stops;i++)
	{
		int z;
		do{
			z=rand()%25;
		}while(z==y);
		stopovers[i]=C[z];
	}
}
void Flight:: SF()
{
	ID=12345;
	depCity="Islamabad\0";
	setdestinationCity("USA\0");
	dep.hours=12;
	dep.min=30;
	arr.hours=17;
	arr.min=35;
	type='l';
	durationInHours=5;
	OccupancyB=3;
	OccupancyE=7;
	stops=0;
	calculateDistance();
	calP();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
class admin: public person{
	string designation;
	public:
	void changeSchedule(Flight &f);
	void changeFlightRoute(Flight &f);
	void updateCapacity(Flight &f);
	void setDes(string n);
	void login();
};
void admin :: setDes(string n)
{
	designation=n;
}
void admin :: changeFlightRoute(Flight &f)
{
	int n;
	cout << "Enter the new number of stops for flight:";
	cin >> n;
	f.setStops(n);
}
void admin :: changeSchedule(Flight &f)
{
	Time x;
	cout << "For new Departure time\nEnter hour:";
	cin >> x.hours;
	cout << "Enter min:";
	cin >> x.min;
	f.setDepTime( x.hours, x.min);
	cout << "For new Arrival time\nEnter hour:";
	cin >> x.hours;
	cout << "Enter min:";
	cin >> x.min;
	f.setArrTime( x.hours, x.min);
}
void admin :: updateCapacity(Flight &f)
{
	int x,y;
	cout << "Enter Business Class Capacity of Plane: ";
	cin >> x;
	cout << "Enter Economic Class Capacity of Plane: ";
	cin >> y;
	f.changeCapacity(x,y);
}
void admin :: login()
{
	bool x=0;
	cout << "Enter designation: ";
	cin >> designation;
	do{
	cout << "Enter log in ID (username): ";
	cin >> loginID;
	cout << "Enter password: ";
	cin >> password;
	fstream data("admin.txt", ios::in);
	int size=20;
	
	if(!data.is_open())
		cout<<"File not found\n";
	else
	{
	
		int count=0;
		bool str=0;	
		while(!data.eof()&&count<size)
		{
				string buff="\0";
				getline(data, buff);
				if(buff==loginID)
				{
					string pass="\0";
					getline(data, pass);
					if(pass==password)
					{
						cout << "Successful log in\n";
						x=1;
						break;
					}
					else
					{
						cout << "PASSWORD DOES NOT MATCH\n";
						count++;
					}
				}
				else 
					count +=2;
		}
	}
	}while(x==0);
}
///////////////////////////////////////////////////////////////////////////
class System{
	city Cities[5];
	Flight *FlightsL;
	Flight *FlightsI;
	admin Emp;
	passenger P[15];
	Flight SF;
	public:
	System();
	void menuAdmin();
	void Initialization();
	void menuPassenger(int n);
	
					
};
System :: System()
{
	Initialization();
	SF.SF();
	int p=0;
	int x;
	do{
		
		cout << "Enter '1', to log in as an employee\nEnter '2', to log in as a passenger\nEnter '3' to end Program\n";
		cin >> x;
		if(x==1)
		{
			menuAdmin();
		}
		else if(x==2)
		{
			menuPassenger(p);
			p++;
		}
		else if(x==3)
		{
			cout << "EXITTING PROGRAM\n";
		}
	}while(x!=3);
		
}
void System :: menuAdmin()
{
	int choice;
	Emp.login();
	do{
		char n;
		cout << "Do you wish to make changes to local or international Flights\nEnter 'l' for local\nEnter 'i' for International\nEnter 'q' to quit\n";
		
		cin >> n;
		if (n=='q')
		{
			choice=4;
		}
		else
		{
			int i;
			cout << "Enter ID of Flight you wish to make changes to: ";
			cin >> i;
			cout << "BEFORE CHANGES\n";
			 if(n=='l')
			 {
			 	cout << FlightsL[i];
			 }
			 if(n=='i')
			 {
				cout << FlightsI[i];
			 }	
			
			do{
			
				cout << "Enter 1,  to change flight schedule\n";
				cout << "Enter 2, to change flight route \n";
				cout << "Enter 3, to change plane capacity\n";
				cout << "Enter 4, to exit and move to different flight\n";
				cin >> choice;
				
				switch(choice)
				{
					case 1:
					{
						
						if(n=='l')
						{
							Emp.changeSchedule( FlightsL[i]);
						}
						if(n=='i')
						{
							Emp.changeSchedule( FlightsI[i]);
						}
						break;
					}
					case 2:
					{
						if(n=='l')
						{
							Emp.changeFlightRoute( FlightsL[i]);
						}
						if(n=='i')
						{
							Emp.changeFlightRoute( FlightsI[i]);
						}
						break;
					}
					case 3:
					{
						if(n=='l')
						{
							Emp.updateCapacity(FlightsL[i] );
						}
						if(n=='i')
						{
							Emp.updateCapacity( FlightsI[i]);
						}
						break;
					}
					case 4:
					{
						cout << "EXITING ADMIN PANEL\n";
						break;
					}
					default:
					{
						cout << "INVALID REQUEST\n";
					}
				
				 }
			}while(choice!=4);
			cout << "AFTER CHANGES:\n";
			if(n=='l')
			{
			 	cout << FlightsL[i];
			}
			if(n=='i')
			{
				cout << FlightsI[i];
			}	
		}
		
	}while(choice!=4);
}		
void System :: menuPassenger(int p)	
{
	int choice;
	int flights;
	P[p].login();
	int a=rand()%7+1;
	P[p].hptr= new Flight[a];//Maintaining History
	int b=0;
	P[p].bptr= new Flight[3];
	for(int i=0;i<a;i++)
	{
		if(i%2==0)
		{

			P[p].hptr[i].RandInitializationI(i);
		}
		else
			P[p].hptr[i].RandInitializationL(i);
	}
	do{
		cout << "\n\n\t\t\t\t********WELCOME TO PAK-AIRLINE**************\n";
		cout << "\t\t\t\tEnter 1,  to view flight schedule\n";
		cout << "\t\t\t\tEnter 2, to view history\n";
		cout << "\t\t\t\tEnter 3, to book flights\n";
		cout << "\t\t\t\tEnter 4, to view payment details\n";
		cout << "\t\t\t\tEnter 5, to view SF details\n";
		cout << "\t\t\t\tEnter 6, to cancel a flight\n";
		cout << "\t\t\t\tEnter 7, to exit passenger panel\n";
		cin >> choice;
		switch(choice)
		{
			case 1:
			{
				string n;
				int counter=0;
				cout << "Enter your destination:\n";
				cin >> n;
				cout << "FLIGHTS TO YOUR DESTINATION\n";
				for(int i=0;i <100; i++)
				{
					if(n==FlightsL[i].getDestinationCity())
					{
						cout << FlightsL[i];
						counter++;
					}
				}
				for(int i=0;i <50; i++)
				{
					if(n==FlightsI[i].getDestinationCity())
					{
						cout << FlightsI[i];
						counter++;
					}
				}
				if(counter==0)
					cout << "No Airplanes Flying to Desired Destination\n";
				break;
			}
			case 2:
			{
				cout << "YOUR TRAVEL HISTORY FOR THE LAST MONTH\n";
				for(int i=0;i<a;i++)
				{
					cout << P[p].hptr[i];
				}			
				break;
			}
			case 3:
			{
				if(b==3)
				{
					cout << "CANNOT BOOK MORE THAN 3 FLIGHTS AT THE SAME TIME\n";
					break;
				}
				char n;
				cout << "Are you looking for local or international Flights\nEnter 'l' for local\nEnter 'i' for international\n";
				cin >> n;
				if(P[p].getPassportType()=='l' && n=='i')
				{
					cout << "!!!NO VISA STAMP!!! can not book an International Flight\n";
				}
				else{
					int id;
					cout << "Enter ID of Flight you want to book\n";
					cin >> id;
					if(n=='l')
		 			{
		 				P[p].bptr[b]=FlightsL[id];
		 				FlightsL[id].addingPassenger();
		 				P[p].bptr[b].calPrice();
		 				b++;
		 			}
					if(n=='i')
		 			{
						P[p].bptr[b]=FlightsI[id];
						FlightsI[id].addingPassenger();
						P[p].bptr[b].calPrice();
						b++;
					}
					string check;
					cout << "Enter CNIC for Payment\n";
					cin >> check;
					if(P[p].getCNIC()==check)
					{
						cout << "PAYMENT SUCCESSFUL\n";
					}
					else
					{
						b--;
						cout << "PAYMENT FAILED\nFlight booking cancelled\n";
					}
				}
				break;
			}
			case 4:
			{
				for(int i=0;i<a;i++)
				{
					cout <<"\n\nFlight "<< i+1 << " from History\n";
					P[p].hptr[i].calPrice();
				}
				if(a>=4&&b>0)
				{
					cout << "CONGRATULATIONS!!!\nYOU GET A 10% DISCOUNT FOR BEING LOYAL CUSTOMER\n";
					cout << "Previously:\n";
					P[p].bptr[b-1].calPrice();
					int newP=P[p].bptr[b-1].getPrice();
					newP=(newP/10)*9;
					cout << "Discounted Price for you:" << newP << "Rs\n";
				}
				
				break;
			}
			case 5:
			{
				string n="USA\0";
				int counter=0;
				for(int i=0;i <a; i++)
				{
					if(n==P[p].hptr[i].getDestinationCity())
					{
						cout << SF;
						counter++;
						break;
					}
				}
				if(counter==0)
				{
					cout << "UNAVAILABLE\nonly for users who have max availed NPAFS services\n";
				}
				break;
			}
			case 6:
			{
				if(b==0)
				{
					"NO FLIGHTS BOOKED\n";
				}
				else
				{
					for(int i=0;i<b;i++)
					{
						cout << "BOOKING#" << i+1 << endl;
						cout << P[p].bptr[i];
					}
					int num;
					cout << "Enter booking# of flight to cancel\n";
					cin >> num;
					int Penalty = P[p].bptr[num-1].getPrice();
					Penalty=(Penalty/100)*25;
					cout << "FLIGHT CANCELLED\nPenalty: " << Penalty << "Rs.\n";
					b--;			
				}
				break;
			}				
			case 7:
			{
				cout << "EXITING PASSENGER PANEL\n";
			}	
				
		}
	}while(choice!=7);
}
void System :: Initialization()
{
	//city and airport data initialization
	Cities[0].setName("Islamabad");
	Cities[1].setName("Lahore");
	Cities[2].setName( "Karachi" );
	Cities[3].setName( "Peshawar");
	Cities[4].setName( "Quetta");
	int portID=0;
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<2; j++)
		{
			Cities[i].setAirport(j, portID);
			portID++;
		}
	}
	//Flight initialization
	FlightsL= new Flight[100];
	for(int i=0;i <100; i++)
	{
		FlightsL[i].RandInitializationL(i);
	}
	FlightsI= new Flight[50];
	for(int i=0;i <50; i++)
	{
		FlightsI[i].RandInitializationI(i);
	}
}
		
//////////////////////////////////////////////////////////////////////////////////(° ͜°)
int main()
{
	srand(time(NULL));
	System m;	
		
}		
