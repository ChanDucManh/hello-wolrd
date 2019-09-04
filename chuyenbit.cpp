#include<iostream>
using namespace std;

int main()
{
	char s;
	cin >> s;
	//for(int i = 0; i < sizeof(char)*8; i++)
	//{
	//	cout << bool(s & 128);
	//	s = s << 1; 
	//}
	for(int i = sizeof(char)*7; i >= 0;i--)
	{
		cout << ((s >> i) & 1);
	}
	return 0;
}
