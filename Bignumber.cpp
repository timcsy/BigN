#include "BigN.h" 
using namespace std;

int main()
{
	Big a="123456789";
	Big b=45678;
		a.print("a");b.print("b");
		cout<<" a+b = "<< a+b <<endl;
		cout<<" a-b = "<< a-b <<endl;
		cout<<" a*b = "<< a*b <<endl;
		cout<<" a/b = "<< a/b <<endl;
		cout<<" a%b = "<< a%b <<endl;
		//cout<<" a^b = "<< (a^b) <<endl;
		a=-a;
		a.print("a");b.print("b");
		cout<<" a+b = "<< a+b <<endl;
		cout<<" a-b = "<< a-b <<endl;
		cout<<" a*b = "<< a*b <<endl;
		cout<<" a/b = "<< a/b <<endl;
		cout<<" a%b = "<< a%b <<endl;
		//cout<<" a^b = "<< (a^b) <<endl;
		b=-b;
		a.print("a");b.print("b");
		cout<<" a+b = "<< a+b <<endl;
		cout<<" a-b = "<< a-b <<endl;
		cout<<" a*b = "<< a*b <<endl;
		cout<<" a/b = "<< a/b <<endl;
		cout<<" a%b = "<< a%b <<endl;
		//cout<<" a^b = "<< (a^b) <<endl;
		a=-a;
		a.print("a");b.print("b");
		cout<<" a+b = "<< a+b <<endl;
		cout<<" a-b = "<< a-b <<endl;
		cout<<" a*b = "<< a*b <<endl;
		cout<<" a/b = "<< a/b <<endl;
		cout<<" a%b = "<< a%b <<endl;
		//cout<<" a^b = "<< (a^b) <<endl;
	return 0;
}

