#include<iostream>
#include<cstdio>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<windows.h>
using namespace std;
int overWrite(FILE* fileOW,long fileSize,int fill)
{
	if(fileOW == NULL)
	    return 1;
	if(fileSize < 0)
	    return 2;
	if(fill < 0)
		return 3;
	int check;
	long count=0;
	check = fseek(fileOW,0,SEEK_SET);
	if(check != 0)
		return 4;
    while(count < fileSize)
    {
    	check = fprintf(fileOW,"%c",fill);
    	if(check < 0)
    		return 5;
    	count++;
    }
    return 0;	
}
int overWriteRandom(FILE* fileOW,long fileSize)
{
	if(fileOW == NULL)
	    return 1;
	if(fileSize < 0)
	    return 2;
	long count = 0;
	int check;
	HCRYPTPROV hProv = 0;
	BYTE pbBuffer[4];
	if(!CryptAcquireContextA(&hProv,NULL,NULL,PROV_RSA_FULL,CRYPT_VERIFYCONTEXT))
		return 3;	
	check = fseek(fileOW,0,SEEK_SET);
	if(check != 0)
		return 4;
	while(count < fileSize)
    {
    	if(!CryptGenRandom(hProv,4,pbBuffer))
			return 5;
    	check = fprintf(fileOW,"%c",pbBuffer[0]);
    	if(check < 0)
    		return 6;
    	count++;
    }
    if(!CryptReleaseContext(hProv,0))	
    	return 7;
	return 0;
}
int getSizeFile(char* dir, int& fileSize)
{
	int checkError;
	FILE* fileToDelete = fopen(dir,"r");
	if(fileToDelete == NULL)
		return 1;
	checkError = fseek(fileToDelete,0,SEEK_END);
	if(checkError != 0)
		return 2;
	fileSize = ftell(fileToDelete);
	if(fileSize == -1)
		return 3;
	checkError = fclose(fileToDelete);
	if(checkError == EOF)
		return 4;
	return 0;
}
////////////////////////
int main()
{
	char choose;
	int check;
	long fileSize = 0;
	char access;
	char change;
	int mode;
	int numberOfPass;
	char *dir;
	try
	{
		dir = new char[MAX_PATH];
	}
	catch(bad_alloc & e)
	{
		cout <<"Allocation error(The program ends).";
		_getch();
		return 0;
	}
	cout <<"Program <Secure file deletion>";
	cout <<"\nEnter file or directory [with extension] (Exp: C:\\Document\\delete.txt): ";
	cin >> dir;
	check = fflush(stdin);
	if(check == EOF)
	{
		delete[] dir;
		cout <<"Error in the fflush function";
		cout <<"\nEnter any key to finish program.";
		_getch();
		return 0;
	}
	FILE* fileD = fopen(dir,"r");
	if(fileD == NULL)
	{
		delete[] dir;
		cout <<"File not exists or directory incorrect.";
		cout <<"\nEnter any key to finish program.";
		_getch();
		return 0;
	}
	check = fseek(fileD,0,SEEK_END);
	if(check != 0)
	{
		delete[] dir;
		cout <<"Error in the fseek function";
		cout <<"\nEnter any key to finish program.";
		_getch();
		return 0;
	}
	fileSize = ftell(fileD);
	if(fileSize == -1)
	{
		delete[] dir;
		cout <<"Error in the ftell function";
		cout <<"\nEnter any key to finish program.";
		_getch();
		return 0;
	}
	check = fclose(fileD);
	if(check == EOF)
	{
		delete[] dir;
		cout <<"Error in the fclose function";
		cout <<"\nEnter any key to finish program.";
		_getch();
		return 0;
	}
	cout <<"1. Use VSITR Wipe Method [German Wipe Standard](7 pass). ";
	cout <<"\n2. You enter number of overwrite passes. ";
	cout << "\nChoose the mode you want: ";
	check = scanf("%d",&mode);
	while(check == 0||(mode != 1 && mode != 2))
	{
		check = fflush(stdin);
		if(check == EOF)
		{
			delete[] dir;
			cout <<"Error in the fflush function";
			cout <<"\nEnter any key to finish program.";
			_getch();
			return 0;
		}
		cout <<"You choosed wrong !!";
		cout <<"\nChoose again [1 or 2]: ";
		check = scanf("%d",&mode);
	}
	check = fflush(stdin);
	if(check == EOF)
	{
		delete[] dir;
		cout <<"Error in the fflush function";
		cout <<"\nEnter any key to finish program.";
		_getch();
		return 0;
	}
	if(mode == 1)
	{
		int fill;
		cout <<"You want to delete the file [y/n] ?: ";
		check = scanf("%c",&choose);
		while(check == 0 || (choose != 'y' && choose != 'n'))
		{
			check = fflush(stdin);
			if(check == EOF)
			{
				delete[] dir;
				cout <<"Error in the fflush function";
				cout <<"\nEnter any key to finish program.";
				_getch();
				return 0;
			}
			cout <<"You choosed wrong !!";
			cout <<"\nChoose again [y/n]: ";
			check = scanf("%c",&choose);
		}
		if(choose == 'n')
		{
			delete[] dir;
			cout <<"Not delete the file.";
			cout <<"\nEnter any key to finish program.";
			_getch();
			return 0;
		}
		for(int i = 0;i < 7;i++)
		{
			fileD = fopen(dir,"r+");
			if(fileD == NULL)
			{
				delete[] dir;
				cout <<"Not can open file (file not exist or openning).";
				cout <<"\nEnter any key to finish program.";
				_getch();
				return 0;
			}
			if(i == 6)
			{
				check = overWriteRandom(fileD,fileSize);
				if(check != 0)
				{
					delete[] dir;
					cout <<"Error in the overWriteRandom funcion";
					switch(check)
					{
						case 1:
						{
							cout <<"\n Error in the pointer fileOW";
							break;
						}
						case 2:
						{
							cout <<"\n Error in the parameter fileSize";
							break;	
						}
						case 3:
						{
							cout <<"\nIn the CryptAcquireRandom function ";
							break;
						}
						case 4:
						{
							cout <<"\nIn the fseek function ";
							break;
						}
						case 5:
						{
							cout <<"\nIn the CryptGenRandom function";
							break;
						}
						case 6:
						{
							cout <<"\nIn the fprintf function";
							break;
						}
						case 7:
						{
							cout <<"\nIn the CryptReleaseContext function";
							break;
						}	
					}
					return 0;
				}
			}
			else 
			{
				if(i%2 == 0)
					fill = 0x00;
				else
				 	fill = 0xFF;
				check = overWrite(fileD,fileSize,fill);
				if(check != 0)
				{
					delete[] dir;
					cout <<"Error in the overWrite function.";
					switch(check)
					{
						case 1:
						{
							cout <<"\n Error in the pointer fileOW";
							break;
						}
						case 2:
						{
							cout <<"\n Error in the parameter fileSize";
							break;
						}
						case 3:
					 	{
					 		cout <<"\n Error in the parameter fill";
							break;
						}
						case 4:
						{
							cout <<"\nIn the fseek function.";
							break;
						}
						case 5:
						{
							cout <<"\nIn the fprintf function.";
							break;
						}
					}	
					cout <<"\nEnter any key to finish program.";
					_getch();
					return 0;
				}		
			}
			check = fclose(fileD);
			if(check == EOF)
			{
			delete[] dir;
			cout <<"Error in the fclose function.";
			cout <<"\nEnter any key to finish program.";
			_getch();
			return 0;
			}
		}
	}
	if(mode == 2)
	{
		int countPass = 0;
		unsigned int* pass;
		cout <<"Enter number of overwrite passes: ";
		check = scanf("%d",&numberOfPass);
		while(check == 0 || numberOfPass < 1)
		{
			check = fflush(stdin);
			if(check == EOF)
			{
				delete[] dir;
				cout <<"Error in the fflush function";
				cout <<"\nEnter any key to finish program.";
				_getch();
				return 0;
			}
			cout <<"You entered wrong !!";
			cout <<"\nEnter again [positive number]: ";
			check = scanf("%d",&numberOfPass);
		}
		try
		{
			pass = new unsigned int[numberOfPass];
		}
		catch(bad_alloc & e)
		{
			delete[] dir;
			cout <<"Allocation error.";
			cout <<"\nEnter any key to finish program.";
			_getch();
			return 0;
		}
		check = fflush(stdin);
		if(check == EOF)
		{
			delete[] dir;
			delete[] pass;
			cout <<"Error in the fflush function";
			cout <<"\nEnter any key to finish program.";
			_getch();
			return 0;
		}
		while(countPass < numberOfPass)
		{
			cout <<"Enter byte value with which to fill the file (" << countPass+1 <<" pass): ";
			check = scanf("%x",&pass[countPass]);
			while(check == 0)
			{
				check = fflush(stdin);
				if(check == EOF)
				{
					delete[] dir;
					delete[] pass;
					cout <<"Error in the fflush function";
					cout <<"\nEnter any key to finish program.";
					_getch();
					return 0;
				}
				cout <<"You entered wrong !!";
				cout <<"\nEnter again [number] ("<< countPass+1 <<" pass): ";
				check = scanf("%x",&pass[countPass]);
			}
			check = fflush(stdin);
			if(check == EOF)
			{
				delete[] dir;
				delete[] pass;
				cout <<"Error in the fflush function";
				cout <<"\nEnter any key to finish program.";
				_getch();
				return 0;
			}
			countPass++;
		}
		check = fflush(stdin);
		if(check == EOF)
		{
			delete[] dir;
			delete[] pass;
			cout <<"Error in the fflush function";
			cout <<"\nEnter any key to finish program.";
			_getch();
			return 0;
		}
		cout <<"You want to delete the file [y/n] ?: ";
		check = scanf("%c",&choose);
		while(check == 0 || (choose != 'y' && choose != 'n'))
		{
			check = fflush(stdin);
			if(check == EOF)
			{
				delete[] dir;
				delete[] pass;
				cout <<"Error in the fflush function";
				cout <<"\nEnter any key to finish program.";
				_getch();
				return 0;
			}
			cout <<"You choosed wrong !!";
			cout <<"\nChoose again [y/n]: ";
			check = scanf("%c",&choose);
		}
		if(choose == 'n')
		{
			delete[] dir;
			delete[] pass;
			cout <<"Not delete the file.";
			cout <<"\nEnter any key to finish program.";
			_getch();
			return 0;
		}
		for(int i = 0;i < numberOfPass;i++)
		{
			fileD = fopen(dir,"r+");
			if(fileD == NULL)
			{
				delete[] dir;
				delete[] pass;
				cout <<"Not can open file (file not exists or openning).";
				cout <<"\nEnter any key to finish program.";
				_getch();
				return 0;
			}
			check = overWrite(fileD,fileSize,pass[i]);
			if(check != 0)
			{
				delete[] dir;
				delete[] pass;
				cout <<"Error in the overWrite function.";
				switch(check)
				{
					case 1:
					{
						cout <<"\nError in the pointer fileOW";
						break;
					}
					case 2:
					{
						cout <<"\nError in the parameter fileSize";
						break;
					}
					case 3:
				 	{
				 		cout <<"\nError in the parameter fill";
						break;
					}
					case 4:
					{
						cout <<"\nIn the fseek function.";
						break;
					}
					case 5:
					{
						cout <<"\nIn the fprintf function.";
						break;
					}
				}	
				cout <<"\nEnter any key to finish program.";
				_getch();
				return 0;		
			}
			check = fclose(fileD);
			if(check == EOF)
			{
				delete[] dir;
				delete[] pass;
				cout <<"Error in the fclose function.";
				cout <<"\nEnter any key to finish program.";
				_getch();
				return 0;
			}  
		}
		delete[] pass;
	}
	check = remove(dir);
	if(check == 0)
		cout <<"File deleted successfully.";
	else
		cout <<"File deletion failed.";
	delete [] dir;
	cout <<"\nEnter any key to finish program.";
		_getch();
	return 0;
}

