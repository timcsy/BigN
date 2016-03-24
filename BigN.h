#ifndef BigN_h
#define BigN_h

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int blockLength=1000;
const int base=10000; //blockbase^basepower
const int blockbase=10;
const int basepower=4;
class Big
{
	friend int max(Big a,Big b)
	{if(a[-2]>=b[-2]) return a[-2];else return b[-2];}
	friend int compare(Big a,Big b);
	template<class T,class U>
	friend Big operator+(T a,U b){return Big(a)+Big(b);}
	template<class T,class U>
	friend Big operator-(T a,U b){return Big(a)-Big(b);}
	template<class T,class U>
	friend Big operator*(T a,U b){return Big(a)*Big(b);}
	template<class T,class U>
	friend Big operator/(T a,U b){return Big(a)/Big(b);}
	template<class T,class U>
	friend Big operator%(T a,U b){return Big(a)%Big(b);}
	template<class T,class U>
	friend Big operator^(T a,U b){return Big(a)^Big(b);}//need ()to meet priority
	template<class T,class U>
	friend bool operator>(T a,U b){return compare(Big(a),Big(b))==1;}
	template<class T,class U>
	friend bool operator<(T a,U b){return compare(Big(a),Big(b))==-1;}
	template<class T,class U>
	friend bool operator>=(T a,U b){return !(compare(Big(a),Big(b))==-1);}
	template<class T,class U>
	friend bool operator<=(T a,U b){return !(compare(Big(a),Big(b))==1);}
	template<class T,class U>
	friend bool operator==(T a,U b){return compare(Big(a),Big(b))==0;}
	template<class T,class U>
	friend bool operator!=(T a,U b){return compare(Big(a),Big(b))!=0;}
	friend ostream& operator<<(ostream& output,Big a)
	{output<<a.toString();return output;}
	friend istream& operator>>(istream& input,Big& a)
	{string s;input>>s;a=s;return input;}
	private:
		int block[blockLength];
		bool sign;
		int digit;//the max index now
	public:
		Big();
		Big(int n);
		Big(Big& b,int n,int m);
		Big(string s);
		Big(char* c){string s=c;*this=s;}
		int getBlock(int blk){return block[blk];}
		void setBlock(int blk,int num){block[blk]=num;}
		bool getSign(){return sign;}
		void setSign(int sgn){sign=sgn;}
		int getDigit(){return digit;}
		void setDigit(int dig){digit=dig;}
		void initial()
		{sign=1;digit=0;for(int i=0;i<blockLength;i++) block[i]=0;}
		void carry();
		void borrow();
		void renew();
		int decide(Big& b,Big& g,int n=0,int m=base-1);
		void shift(int addition);
		string toString();
		template<class T>
		Big& operator+=(T b){*this=*this+b;return *this;}
		template<class T>
		Big& operator-=(T b){*this=*this-b;return *this;}
		template<class T>
		Big& operator*=(T b){*this=*this*b;return *this;}
		template<class T>
		Big& operator/=(T b){*this=*this/b;return *this;}
		template<class T>
		Big& operator%=(T b){*this=*this%b;return *this;}
		template<class T>
		Big& operator^=(T b){*this=*this^b;return *this;}
		Big operator-(){Big c=*this;if(c!=0)c(1)=!c(1);return c;}
		Big& operator++(){*this+=1;return *this;}
		Big& operator--(){*this-=1;return *this;}
		Big operator++(int){Big t=*this;++*this;return t;}
		Big operator--(int){Big t=*this;--*this;return t;}
		int& operator [](int i)
		{if(i==-2)return digit;else return block[i];}
		bool& operator ()(int i)
		{if(i==1)return sign;}
		template<class T>
		Big& operator=(T b){*this=Big(b);return *this;}
		void print(string name);
};
Big::Big()
{
	initial();
}
Big::Big(int n)
{
	initial();
	if(n<0){sign=0;n=-n;}
	digit--;
	if(n==0) digit=0;
	while(n>0)
	{
		block[++digit]=n%base;
		n/=base;
	}
}
Big::Big(Big& b,int n,int m)
{
	initial();
	if(n>m){int t=n;n=m;m=t;}
	for(int i=0;i<=m-n;i++) block[i]=b[n+i];
	digit=m-n;
}
Big::Big(string s)
{
	initial();
	if(s[0]!='-' && s[0]!='+') block[0]=s[0]-48;
	for(int i=1;i<s.length();i++) *this=*this*blockbase+(s[i]-48);
	if(s[0]=='-') sign=0;
	renew();
}
void Big::carry()
{
	for(int i=0;i<digit;i++)
	{
		block[i+1]+=block[i]/base;
		block[i]=block[i]%base;
	}
	while(block[digit]>=base)
	{
		block[digit+1]+=block[digit]/base;
		block[digit]=block[digit]%base;
		digit++;
	}
	renew();
}
void Big::borrow()
{
	for(int i=0;i<digit;i++)
	{
		if(block[i]<0)
		{
			block[i+1]--;
			block[i]+=base;
		}
	}
	renew();
}
void Big::renew()
{
	for(int i=digit;i>0;i--)
	{
		if(block[i]==0) digit--;
		else break;
	}
	if(digit==0 && block[0]==0) sign=1;
}
int Big::decide(Big& b,Big& g,int n,int m)
{
	if(n==m) return n;
	else
	{
		int mid=(n+m)/2;
		if(b<g*mid) return decide(b,g,n,mid-1);
		else if(b-g*mid>=g) return decide(b,g,mid+1,m);
		else return mid;
	}
}
void Big::shift(int addition)
{
	while(block[digit]==0 && digit>0) digit--;
	digit++;
	for(int i=digit;i>0;i--) block[i]=block[i-1];
	block[0]=addition;
}
string Big::toString()
{
	stringstream ss;
	string s;
	if(sign==0) ss<<"-";
	ss<<block[digit];
	for(int i=digit-1;i>=0;i--)
	{
		int t=base/blockbase;
		int n=0;
		for(int j=1;j<basepower;j++)
		{
			if(block[i]/t==0){n++;t/=blockbase;}
			else break;
		}
		for(int j=0;j<n;j++) ss<<"0";
		ss<<block[i];
	}
	ss>>s;
	return s;
}
void Big::print(string name)
{
	cout<<"Big "<<name<<":"<<endl;
	cout<<" sign = "<<sign<<endl;
	cout<<" digit = "<<digit<<endl;
	cout<<" toString = "<<toString()<<endl;
	for(int i=0;i<digit+4;i++) cout<<" block["<<i<<"] = "<<block[i]<<endl;
}
//define friend functions
int compare(Big a,Big b)
{
	int p=a(1)?1:-1;
	int q=b(1)?1:-1;
	if(p*q==-1) return p;
	else
	{
		bool m=0;
		for(int i=max(a,b);i>=0;i--)
		{
			if(a[i]>b[i]){m=1;return 1*p;break;}
			else if(a[i]<b[i]){m=1;return -1*p;break;}
		}
		if(!m) return 0;
	}
}
Big operator+(Big a,Big b)
{
	Big c;
	if(a(1)^b(1)==0)
	{
		c(1)=a(1);
		c[-2]=max(a,b);
		for(int i=0;i<=c[-2];i++) c[i]=a[i]+b[i];
		c.carry();
	}
	else if(a(1)==1 && b(1)==0) c=a-(-b);
	else  c=b-(-a);
	return c;
}
Big operator-(Big a,Big b)
{
	int p=a(1)?1:-1;
	int q=b(1)?1:-1;
	int r=(a>=b)?1:-1;
	Big c;
	if(a(1)^b(1)==0)
	{
		c(1)=(a>=b);
		c[-2]=max(a,b);
		for(int i=0;i<=c[-2];i++) c[i]=(a[i]-b[i])*p*r;
		c.borrow();
	}
	else
	{
		b(1)=!b(1);
		c=a+b;
		b(1)=!b(1);
	}
	return c;
}
Big operator*(Big a,Big b)
{
	Big c;
	c(1)=!(a(1)^b(1));
	c[-2]=a[-2]+b[-2];
	for(int i=0;i<=a[-2];i++)
	 for(int j=0;j<=b[-2];j++)
	  c[i+j]+=a[i]*b[j];
	c.carry();
	return c;
}
Big operator/(Big a,Big b)
{
	if(b==0) throw "divide by 0";
	else
	{
		Big c;
		bool as=a(1),bs=b(1);
		c(1)=!(as^bs);
		if(!as)a(1)=1; if(!bs)b(1)=1;
		if(a<b) c=0;
		else
		{
			c[-2]=a[-2]-b[-2]+2;
			Big t(a,a[-2]-b[-2],a[-2]);
			for(int i=a[-2]-b[-2];i>0;i--)
			{
				int q=a.decide(t,b);
				c[i]=q; t-=b*q;
				t.shift(a[i-1]);
			}
			c[0]=a.decide(t,b);
			c.renew();
		}
		a(1)=as; b(1)=bs;
		return c;
	}
}
Big operator%(Big a,Big b)
{
	if(b==0) throw "divide by 0";
	else
	{
		bool as=a(1),bs=b(1);
		if(!as) a(1)=1; if(!bs) b(1)=1;
		if(a<b)
		{
			Big t=a;
			a(1)=as;
			if(as||t==0){b(1)=bs;return t;}
			else if(!as){t=b-t;b(1)=bs;return t;}
		}
		else
		{
			Big t(a,a[-2]-b[-2],a[-2]);
			for(int i=a[-2]-b[-2];i>0;i--)
			{
				t-=b*a.decide(t,b);
				t.shift(a[i-1]);
			}
			t-=b*a.decide(t,b);
			a(1)=as;
			if(as||t==0){t.renew();b(1)=bs;return t;}
			else if(!as){t=b-t;b(1)=bs;return t;}
		}
	}
}
Big operator^(Big a,Big b)
{
	if(a==0 && b==0) throw "0^0";
	else
	{
		if(b==0) return Big(1);
		else if(b>0)
		{
			for(Big i=1;i<b;i++) a*=a;
			return a;
		}
		else throw "negative power";
	}
}
#endif
