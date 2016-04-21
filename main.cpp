#include <cstdlib>
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

string GetString(int n); //Zwraca liczbę jako napis
void GetThirds(int n, int* Thirds); //Zmienia liczbę na tablicę 4 elementową, gdzie każdy element to trójki liczbowe (poza miejscem 0, to jest milion)
void Unitize(int n, int* Array); //Zmienia daną trójkę z Thirds na poszczególne liczby
bool CheckBinary(int Number);
int GetK(int n, int k);

template<typename T>
string ToString(const T& a)
{
	stringstream SStream;
	SStream << a;
	return SStream.str();
}

int main(int argc, char *argv[])
{
	unsigned int n; //Definiujemy liczbę, na której będziemy pracować

	if(argc > 0) //Upewnijmy się, że mamy jakiś numer
		n = atoi(argv[1]);
	else
		return -1;

	if(n > 1000000) //Liczba ma być mniejsza lub równa 1000000
		return -2;

	unsigned int k = GetK(n, k);
	cout << "Liczba to: " << GetString(n) << endl;
	cout << "k = " << GetString(k) << endl;	
}

void GetThirds(int n, int* Thirds)
{
	Thirds[0] = n/1000000;
	Thirds[1] = (n/1000) % 1000;
	Thirds[2] = n % 1000;

	if(Thirds[0] > 1) //Liczba ma mieć maksymalnie 1 milion - więc jeśli jest więcej, to zmniejszamy tę liczbę do 1 miliona
		Thirds[0] = 1;
}
void Unitize(int n, int* Array)
{
	Array[0] = n/100;
	Array[1] = (n/10) % 10;
	Array[2] = n % 10;
}

string GetString(int n)
{
	/*Deklarujemy potrzebne nam zmienne*/
	string Result = ""; //Definiujemy zmienną, którą będziemy edytować i na koniec zwrócimy jako wynik
	int* Thirds = new int[3]; //Deklarujemy tablicę, która będzie przechowywała naszą liczbę podzieloną na trójki
	int* Milions = new int[3]; //Deklarujemy tablice, które będzie przechowywała miliony podzielone na pojedyncze miliony
	int* Thousands = new int[3]; //Deklarujemy talicę, która będzie przeychowywałą tysiące z Thirds podzielone na pojedyncze liczby
	int* Units = new int[3]; //Deklarujemy tablicę, która będzie przechowywała trójki z Thirds podzielone na pojedyncze liczby
	/*------------------------------------------------------------*/

	/*Deklarujemy wszystkie ciągi znaków, które będziemy używać*/
	string Unit[] = {"","jeden","dwa","trzy","cztery","piec","szesc","siedem","osiem","dziewiec"};
	string Dozen[] = {"dziesiec","jedenascie","dwanascie","trzynascie","czternscie","pietnascie","szescnascie","siedemnasice","osiemnascie","dziewietnascie"};
	string Ten[] = {"","dziesiec","dwadziescia","trzydziesci","czterdziesci","piecdziesiat","szescdziesiat","siedemdziesiat","osiemdziesiat","dziewiecdziesiat"};
	string Hundred[] = {"","sto","dwiescie","trzysta","czterysta","piecset","szescset","siedemset","osiemset","dziewiecset"};
	string Thousand[] = {"","tysiac","tysiace","tysiace","tysiace","tysiecy","tysiecy","tysiecy","tysiecy","tysiecy"};
	string Milion[] = {"", "milion", "miliony", "miliony", "miliony", "milionow", "milionow", "milionow", "milionow", "milionow"};
	/*------------------------------------------------------------*/

	/*Wywołujemy funkcje i zapisujemy tablice liczbami*/
	GetThirds(n, Thirds);
	Unitize(Thirds[0], Milions);
	Unitize(Thirds[1], Thousands);
	Unitize(Thirds[2], Units);
	/*------------------------------------------------------------*/

	/*Wypełniamy Result konkretnymi ciągami znaków*/
	if(Thirds[0] > 0) //Jeśli liczba ma coś na znaku milionu
	{
			Result += Hundred[Milions[0]];
			Result += " ";

		if(Milions[1] == 1) //Jeśli mamy sytuację, w której następna liczba mieści się w zasiegu 10-19 tysięcy
		{
			Result += Dozen[Milions[2]];
			Result += " ";
		}
		else
		{
			Result += Ten[Milions[1]];
			Result += " ";
			Result += Unit[Milions[2]];
			Result += " ";	
		}
		if(Milions[0] != Milions[2] && Milions[2] != 0) //101 tysiąc, ale 301 tysięcy
			Result += Milion[Milions[2]];
		else if(Milions[0] == Milions[2])
			Result += Milion[Milions[0]];
		else
			Result += Milion[6];
	}

	Result += " ";

	if(Thirds[1] > 0) //Jeśli liczba ma do wypisania tysiące
	{
			Result += Hundred[Thousands[0]];
			Result += " ";

		if(Thousands[1] == 1) //Jeśli mamy sytuację, w której następna liczba mieści się w zasiegu 10-19 tysięcy
		{
			Result += Dozen[Thousands[2]];
			Result += " ";
		}
		else
		{
			Result += Ten[Thousands[1]];
			Result += " ";
			Result += Unit[Thousands[2]];
			Result += " ";	
		}
		if(Thousands[0] != Thousands[2] && Thousands[2] != 0) //101 tysiąc, ale 301 tysięcy
			Result += Thousand[Thousands[2]];
		else if(Thousands[0] == Thousands[2])
			Result += Thousand[Thousands[0]];
		else
			Result += Thousand[6];
	}

	Result += " ";

	if(Thirds[2] > 0) //Jeśli liczba ma do wpisania setki
	{
			Result += Hundred[Units[0]];
			Result += " ";	

		if(Units[1] == 1) //Jeśli mamy sytuację, w której następna liczba mieści się w zasiegu 10-19
		{
			Result += Dozen[Units[2]];
			Result += " ";
		}
		else
		{
			Result += Ten[Units[1]];
			Result += " ";
			Result += Unit[Units[2]];
			Result += " ";	
		}

		
	}
	/*------------------------------------------------------------*/

	return Result;
} 

bool CheckBinary(int Number)
{
	string NumText = ToString(Number); //Na tej liczbie będziemy sprawdzać czy mamy 0 czy 1
	int i = 0; //Deklarujemy licznik, który będzie sprawdzał ile mamy liczb 0 lub 1 w liczbie


	for(int j = 0; j<NumText.length(); j++)
	{
		if(NumText[j] == '0' || NumText[j] == '1')
			i++;
	}

	if(i == NumText.length()) //Jeśli jest tyle 0 i 1 w liczbie ile jest znaków w niej
		return true;

	return false; //Jeśli powyższe return true się nie spełni, to znaczy, że to nie jest prawda

}

int GetK(int n, int k)
{
	unsigned int CheckNumber;
	k = 1; //Zaczynamy próby od k = 1
	bool bIsBinary; 

	bIsBinary = CheckBinary(n); //Może już jest binarna?

	if(!bIsBinary)
	{
		do
		{
			k++;
			CheckNumber = n*k;

			if(CheckBinary(CheckNumber)) //Wypisz liczbę, która spełnia warunek
				cout << "Szukana liczba to " << GetString(CheckNumber) << endl;

		} while(!CheckBinary(CheckNumber));
	}

	return k;
}