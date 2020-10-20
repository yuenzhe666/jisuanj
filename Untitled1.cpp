#include <iostream>
#include <string>
#include <cmath>
using namespace std;

long long Poww(long long a,long long b)
{
	long long ans=1;long long base=a;
	while(b!=0)
	{
		if(b&1)ans*=base;
		base*=base;
		b>>=1;
	}
	return ans;
}

long long f(int n){
	long long sum;
	if(n==1)return 1;
	if(n>1)return n*f(n-1);
} 

double cal(double s, double e, string str);

double getVal(double &s, double e, string str)
{
	if (str[s] == '('||str[s] == '['||str[s] == '{')
	{
		double news, newe, i;
		i = 1;
		news = s + 1;
		while (i)
		{
			s++;
			if (s == e)
				break;
			if (str[s] == '('||str[s] == '['||str[s] == '{')
				i++;
			else if (str[s] == ')'||str[s] == ']'||str[s] == '}')
				i--;
		}
		newe = s - 1;
		s++;
		return cal(news, newe, str);
	}
	double val;
	if(str[s]=='s')
	{
		s=s+3;
		val=sin(getVal(s,e,str));
	}
	if(str[s]=='c')
	{
		s=s+3;
		val=cos(getVal(s,e,str));
	}
	if(str[s]=='t')
	{
		s=s+3;
		val=tan(getVal(s,e,str));
	}
	if(str[s]=='a')
	{
		s++;
		if(str[s]=='s')
		{
			s=s+3;
			val=sin(getVal(s,e,str));
		}
		if(str[s]=='c')
		{
			s=s+3;
			val=cos(getVal(s,e,str));
		}
		if(str[s]=='t')
		{
			s=s+3;
			val=tan(getVal(s,e,str));
		}
	}
	if(str[s]>='0'&&str[s]<='9')
	{
		val = str[s++] - '0';
		while (s<e && str[s] >= '0'&&str[s] <= '9')
		{
			val *= 10;
			val += str[s++] - '0';
		}
		if(str[s]=='!'){
			val=f(val);
			s++;
		} 
		if(str[s]=='.')
		{
			s=s+1;
			double val2=str[s++] - '0';
			while (s<e && str[s] >= '0'&&str[s] <= '9')
			{
				val2 *= 10;
				val2 += str[s++] - '0';
			}
			while(val2>=1)
			{
				val2/=10;
			}
			val=val+val2;
		}
	}
	return val;
}


double getVal1(double &s, double e, string str)
{
	double val;
	val = getVal(s, e, str);
	while (1)
	{
		if (s < e&&str[s] == '*') val*=getVal(++s,e,str);
		else if (s<e && str[s] == '/')val /= getVal(++s, e, str);
		else if (s<e && str[s] == '^')val=Poww(val,getVal(++s,e,str));
		else return val;
	}
}

double cal(double s, double e, string str)
{
	double sum = 0;
	if (str[s] != '-')
		sum = getVal1(s, e, str);
	while (s < e)
	{
		if (str[s] == '+')
		{
			sum += getVal1(++s, e, str);
		}
		if (str[s] == '-')
		{
			sum -= getVal1(++s, e, str);
		}
	}
	return sum;
}


int main()
{
	
	string x;
	while (cin >> x)
		cout << cal(0, x.length(),x) << endl;
}

