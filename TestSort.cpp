#include "stdafx.h"
#include "Sort.h"
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#define _DEBUG_
using namespace std;

typedef void( *pFSort )( int*, int ); //Typ wskaźnikowy na funkcje sortujące

int CreatTab( int** pTab, int nSize ); 
void InsertNumbers( int* pTab, int nSize ); //Wypełnienie tablicy
void CopyTab( int* pTabKopia, int* pTab, int nSize ); //Kopiowanie tablicy
void Sort( int* pTabKopia, int* pTab, int nSize, pFSort tab ); //Funkcja sortująca i obliczająca czas sortowania
void PrintTab( int* pTab, int nSize );


//==============================================================================
int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		printf( "ERROR! On Command line use size of array to sort.\ne.g. TestSort.exe 1000\n" );
		return 1;
	}

	srand( (unsigned int)time( NULL ) );
	pFSort tab[] = { SelectionSort, InsertionSort, BubbleSort, MixedSort, HalfSort, HeapSort, NaturalMergeSort }; //Tablica funkcji sortujących
	const char* tabnames[] = { "SelectionSort", "InsertionSort", "BubbleSort", "MixedSort", "HalfSort", "HeapSort", "NaturalMergeSort" };
	int nSize = atoi( argv[1] ); //rozmiar tablicy podany jako parametr

	//Tworzę wskaźniki do tablic 
	int* pTab = NULL; 
	int* pTabKopia = NULL;

	if( !CreatTab( &pTab, nSize ) )//Tworzą oryginalną tablcę  //NIE WIEM CZT TERŻ TRZEBA TO ZABEZPIECZENIE
	{
		perror( "ERROR! CreatTab - pTab main!" );
		return 1;
	}
	InsertNumbers( pTab, nSize ); //Zapełniam tablicę randomowymi liczbami

	if( !CreatTab( &pTabKopia, nSize ) ) //Tworzę kopię tablicy
	{
		perror( "ERROR! CreatTab - pTabKopia main!" );
		return 1;
	}

#ifdef _DEBUG_ //Wydruk kontrolny tablicy
	printf( "\nControl printout: \n" );
	PrintTab( pTab, nSize );
#endif
	
	printf( "Start sorting %d items:\n\n", nSize );
	int size = sizeof( tab ) / sizeof( pFSort ); //zmienna rozmiaru tablicy sortowań
	for( int i = 0; i < size; i++ )  //Wypisanie czasu sortowań, pętla for do wiellości tablicy tab
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
	printf( "Sorted in %.4f \n\n", czas ); 

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
	printf( "Sorted in %.4f \n\n", czas ); 

//----------------------------------------------------------------------------------------

#ifdef _DEBUG_ //Wydruk kontrolony posortowanej tablicy
	printf( "Sorted array (to 100 first items): \n" );
	PrintTab( pTabKopia, nSize );
#endif

	free( pTab ); 
	free( pTabKopia );

	return 0;
}

//------------------------------------------------------------------------------
int CreatTab( int** pTab, int nSize )
{
	*pTab = (int*)malloc( nSize*sizeof( int ) ); //przydzielam pamięć
	if( !*pTab )
	{
		perror( "ERROR! CreatTab" );
		return 0;
	}
	memset( *pTab, 0, nSize*sizeof( int ) ); //Wyzerowujemy tablicę
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
	printf( "Sorted in %.4f \n\n", czas );
}

//------------------------------------------------------------------------------
void PrintTab( int* pTab, int nSize )
{
	int x = 100; //Domyslna ilosc elementow wydruku kontrolnego
	if( nSize < 100 ) x = nSize; //zabezpieczenie przed tablica mniejszą od 100 elementow
	for( int i = 0; i < x; i++ )
		printf( "%d ", pTab[i] );
	printf( "\n\n" );
}
