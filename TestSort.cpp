#include "stdafx.h"
#include "Sort.h"
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#define _DEBUG_
using namespace std;

typedef void( *pFSort )( int*, int ); //Typ wskaŸnikowy na funkcje sortuj¹ce

int CreatTab( int** pTab, int nSize ); 
void InsertNumbers( int* pTab, int nSize ); //Wype³nienie tablicy
void CopyTab( int* pTabKopia, int* pTab, int nSize ); //Kopiowanie tablicy
void Sort( int* pTabKopia, int* pTab, int nSize, pFSort tab ); //Funkcja sortuj¹ca i obliczaj¹ca czas sortowania
void PrintTab( int* pTab, int nSize );


//==============================================================================
int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		printf( "ERROR! Jako parametr wywolania, prosze uzyc wielkosci tablicy do sortowania.\nnp. TestSort.exe 1000\n" );
		return 1;
	}

	srand( (unsigned int)time( NULL ) );
	pFSort tab[] = { SelectionSort, InsertionSort, BubbleSort, MixedSort, HalfSort, HeapSort, NaturalMergeSort }; //Tablica funkcji sortuj¹cych
	const char* tabnames[] = { "SelectionSort", "InsertionSort", "BubbleSort", "MixedSort", "HalfSort", "HeapSort", "NaturalMergeSort" };
	int nSize = atoi( argv[1] ); //rozmiar tablicy podany jako parametr

	//Tworzê wskaŸniki do tablic 
	int* pTab = NULL; 
	int* pTabKopia = NULL;

	if( !CreatTab( &pTab, nSize ) )//Tworz¹ oryginaln¹ tablcê  //NIE WIEM CZT TER¯ TRZEBA TO ZABEZPIECZENIE
	{
		perror( "ERROR! CreatTab - pTab main!" );
		return 1;
	}
	InsertNumbers( pTab, nSize ); //Zape³niam tablicê randomowymi liczbami

	if( !CreatTab( &pTabKopia, nSize ) ) //Tworzê kopiê tablicy
	{
		perror( "ERROR! CreatTab - pTabKopia main!" );
		return 1;
	}

#ifdef _DEBUG_ //Wydruk kontrolny tablicy
	printf( "\nWydruk kontrolny poczatku tablicy (do 100 pierwszych liczb): \n" );
	PrintTab( pTab, nSize );
#endif
	
	printf( "Rozpoczynam sortowania dla %d elementow:\n\n", nSize );
	int size = sizeof( tab ) / sizeof( pFSort ); //zmienna rozmiaru tablicy sortowañ
	for( int i = 0; i < size; i++ )  //Wypisanie czasu sortowañ, pêtla for do wielloœci tablicy tab
	{
		printf( "%s\n", tabnames[i] );
		Sort( pTabKopia, pTab, nSize, tab[i] );
	}
	
//----------------------------------------------------------------------------------------
	printf( "QuickSort \n" );
	CopyTab( pTabKopia, pTab, nSize ); //Przekopiowanie oryginalnej tablicy
	clock_t start = clock();
	QuickSort( pTabKopia, 0, nSize - 1 ); //Sortowanie
	double czas = (double)( clock() - start ) / CLOCKS_PER_SEC; //Oblicznie czasu sortowania
	printf( "Posortowano w czasie %.4f \n\n", czas ); 

//----------------------------------------------------------------------------------------
	printf( "MergeSort \n" );

	int* pTabtmp = NULL;
	if( !CreatTab( &pTabtmp, nSize ) )
	{
		perror( "ERROR! CreatTab - MergeSort pTabtmp main!" );
		return 1;
	}
	CopyTab( pTabKopia, pTab, nSize ); //Przekopiowanie oryginalnej tablicy
	start = clock();
	MergeSort( pTabKopia, pTabtmp, nSize, 0, nSize - 1 );
	czas = (double)( clock() - start ) / CLOCKS_PER_SEC; //Oblicznie czasu sortowania
	printf( "Posortowano w czasie %.4f \n\n", czas ); 

//----------------------------------------------------------------------------------------

#ifdef _DEBUG_ //Wydruk kontrolony posortowanej tablicy
	printf( "Wydruk posortowanej tablicy (do 100 pierwszych liczb): \n" );
	PrintTab( pTabKopia, nSize );
#endif

	free( pTab ); //Zwalniam pamiêæ
	free( pTabKopia );
	//free( pTabtmp );

	return 0;
}

//------------------------------------------------------------------------------
int CreatTab( int** pTab, int nSize )
{
	*pTab = (int*)malloc( nSize*sizeof( int ) ); //przydzielam pamiêæ
	if( !*pTab )
	{
		perror( "ERROR! CreatTab" );
		return 0;
	}
	memset( *pTab, 0, nSize*sizeof( int ) ); //Wyzerowujemy tablicê
	return 1;
}

//------------------------------------------------------------------------------
void InsertNumbers( int* pTab, int nSize)
{
	for( int i = 0; i < nSize; i++ )
		pTab[i] = rand() % 1000;
}

//------------------------------------------------------------------------------
void CopyTab( int* pTabKopia, int* pTab, int nSize )
{
	memcpy( pTabKopia, pTab, sizeof( int )*nSize );
}

//------------------------------------------------------------------------------
void Sort( int* pTabKopia, int* pTab, int nSize, pFSort tab )
{
	CopyTab( pTabKopia, pTab, nSize ); //Przekopiowanie oryginalnej tablicy
	clock_t start = clock();
	tab( pTabKopia, nSize ); //Sortowanie 
	double czas = (double)( clock() - start ) / CLOCKS_PER_SEC; //Oblicznie czasu sortowania
	printf( "Posortowano w czasie %.4f \n\n", czas );
}

//------------------------------------------------------------------------------
void PrintTab( int* pTab, int nSize )
{
	int x = 100; //Domyslna ilosc elementow wydruku kontrolnego
	if( nSize < 100 ) x = nSize; //zabezpieczenie przed tablica mniejsz¹ od 100 elementow
	for( int i = 0; i < x; i++ )
		printf( "%d ", pTab[i] );
	printf( "\n\n" );
}
