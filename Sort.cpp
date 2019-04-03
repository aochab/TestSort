#include "stdafx.h"
#include "Sort.h"
#include <stdlib.h>
#include <memory.h>

void SelectionSort( int* pTab, int nSize )
{
	for( int i = 0; i < nSize - 1; i++ )
	{
		int min = pTab[i];
		int ix = i;
		for( int j = i + 1; j < nSize; j++ )
			if( pTab[j] < min )
			{
				min = pTab[j];
				ix = j;
			}
			pTab[ix] = pTab[i];
			pTab[i] = min;
	}
}

//------------------------------------------------------------------------------
void InsertionSort( int* pTab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{
		int x = pTab[i];
		int j = i - 1;
		while( ( j >= 0 ) && ( pTab[j] > x ) )
			pTab[j + 1] = pTab[j--];

		pTab[j + 1] = x;
	}
}

//------------------------------------------------------------------------------
void BubbleSort( int* pTab, int nSize )
{
	for( int j = 0; j < nSize - 1; j++ )
	{
		for( int i = nSize - 1; i > j; i-- )
		{
			if( pTab[i] < pTab[i - 1] )
			{
				int temp = pTab[i];
				pTab[i] = pTab[i - 1];
				pTab[i - 1] = temp;
			}
		}
	}
}

//------------------------------------------------------------------------------
void MixedSort( int* pTab, int nSize )
{
	int l = 1;
	int p = nSize - 1;
	int k = nSize - 1;
	while( l < p )
	{
		for( int i = p; i >= l; i-- )
			if( pTab[i - 1] > pTab[i] )
			{
				int temp = pTab[i - 1];
				pTab[i - 1] = pTab[i];
				pTab[i] = temp;
				k = i;
			}
		l = k + 1;

		for( int j = l; j <= p; j++ )
			if( pTab[j - 1] > pTab[j] )
			{
				int temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		p = k - 1;
	} 
}

//------------------------------------------------------------------------------
void HalfSort( int* pTab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{
		int x = pTab[i];
		int l = 0;
		int p = i - 1;
		while( l <= p )
		{
			int m = ( l + p ) / 2;
			if( x < pTab[m] )
				p = m - 1;
			else l = m + 1;
		}

		for( int j = i - 1; j >= l; j-- )
			pTab[j + 1] = pTab[j];
		pTab[l] = x;
	}
}

//------------------------------------------------------------------------------
//HeapSort

void Update( int *pTab, int l, int p )
{
	if( l == p ) return;
	int i = l;
	int j = 2 * i + 1;
	int x = pTab[i];
	while( j <= p )
	{
		if( j < p )
			if( pTab[j] < pTab[j + 1] ) 
				j++;

		if( x >= pTab[j] ) break;

		pTab[i] = pTab[j];
		i = j;
		j = 2 * i + 1;
	}
	pTab[i] = x;
}

void HeapSort( int* pTab, int nSize )
{
	int p = nSize - 1;
	int l = ( ( nSize - 1 ) / 2 );

	for( l; l >= 0; l-- )
		Update( pTab, l , p );

	for( p; p > 0; p-- )
	{
		int x = pTab[0];
		pTab[0] = pTab[p];
		pTab[p] = x;
		Update( pTab, 0, p - 1 );
	}
}

//------------------------------------------------------------------------------
void QuickSort( int* pTab, int l, int p ) 
{
	int i = l;
	int j = p;
	int x = pTab[ ( l + p ) / 2 ];
	do
	{
		while( pTab[i] < x ) i++;
		while( pTab[j] > x ) j--;
		if( i <= j )
		{
			int tmp = pTab[i];
			pTab[i] = pTab[j];
			pTab[j] = tmp;
			i++;
			j--;
		}
	} while( i < j );

	if( l < j ) QuickSort( pTab, l, j );
	if( p > i ) QuickSort( pTab, i, p );
}

//------------------------------------------------------------------------------
void Merge( int *pTab, int *tmpTab, int nSize, int l, int m, int p )
{
	memcpy( tmpTab, pTab, sizeof( int )*nSize );
	int i = l;			
	int j = m + 1;		
	int q = l;			

	while( ( i <= m ) && ( j <= p ) )
	{
		if( tmpTab[i] < tmpTab[j] )
			pTab[q++] = tmpTab[i++];
		else
			pTab[q++] = tmpTab[j++];
	}
	while( i <= m ) 
		pTab[q++] = tmpTab[i++];
}

void MergeSort( int *pTab, int *tmpTab, int nSize, int l, int p )
{
	if( l < p )
	{
		int m = ( l + p ) / 2;
		MergeSort( pTab, tmpTab, nSize, l, m );
		MergeSort( pTab, tmpTab, nSize, m + 1, p );
		Merge( pTab, tmpTab, nSize, l, m, p );	
	}
}

//------------------------------------------------------------------------------
//NaturalMergeSort

bool copy( int* t, int* i, int* tmp, int* ix, int nLast )
{
	t[(*i)++] = tmp[(*ix)++];			//przenosimy element z tmp do t
	if( *ix == nLast )				//sprawdzamy czy osiągnięto koniec serii
		return 1;
	return ( tmp[(*ix)-1] > tmp[*ix] ); //jeśli element skopiowany do t, jest większy niż następnik to return 1
}

void CopySerie( int* t, int* i, int* tmp, int* ix, int nLast )
{
	int bEnd = 0;
	do
	{
		bEnd = copy( t, i, tmp, ix, nLast ); // kopiuj jeden element i badaj koniec serii lub koniec tablicy z seriami
	} while( !bEnd );
}

void NaturalMergeSort( int* pTab, int nSize ) //Sortowanie przez łaczenie naturalne
{
	// Tworze tablice do zapamiętywania serii
	int* pTmp1 = (int*)malloc( nSize*sizeof( int ) );
	if( !pTmp1 )
	{
		perror( "ERROR! pTmp1 NaturalMergeSort" );
		return;
	}
	memset( pTmp1, 0, nSize*sizeof( int ) );


	int* pTmp2 = (int*)malloc( nSize * sizeof( int ) );
	if( !pTmp2 )
	{
		perror( "ERROR! pTmp2 NaturalMergeSort" );
		return;
	}
	memset( pTmp2, 0, nSize * sizeof( int ) );

	int nSerie = 0;

	do
	{
		int i = 0;
		int j = 0;
		int k = 0;

		//rozdzielanie
		while( i < nSize )
		{

			while( pTab[i] <= pTab[i + 1] )
				pTmp1[j++] = pTab[i++]; //kopiujemy ity do tmp1

			pTmp1[j++] = pTab[i++]; //dokopiowanie ostatniego z serii do tmp1( j++ )

			if( i < nSize )
			{
				while( pTab[i] <= pTab[i + 1] )
					pTmp2[k++] = pTab[i++];//kopiujemy ity do tmp2

				pTmp2[k++] = pTab[i++]; //dokopiowanie ostatniego z seriii do tmp2( k++ )
			}
		}

		int nLast1 = j;
		int nLast2 = k;

		nSerie = 0;
		i = 0;
		j = 0;
		k = 0;

		//laczenie i zliczanie serii
		//Przenoszenie danych z sortowaniem ze zbiorów pomocniczych do tablicy głównej
		while( ( j < nLast1 ) && ( k < nLast2 ) ) // dopóki nie koniec tab1 i nie koniec tab2
		{
			int bEndSerie = 0; //koniec serii
			while( !bEndSerie ) // dopóki nie ma końca tablcy z seriami 1 lub 2
			{
				if( pTmp1[j] <= pTmp2[k] )
				{
					bEndSerie = copy( pTab, &i, pTmp1, &j, nLast1 );  //kopiuj z serii1 do t i sprawdz czy nie koniec serii
					if( bEndSerie )
						CopySerie( pTab, &i, pTmp2, &k, nLast2 ); //dokopiuj koniec serii 2
				}
				else
				{
					bEndSerie = copy( pTab, &i, pTmp2, &k, nLast2 );  //kopiuj z serii2 do t i sprawdz czy nie koniec serii
					if( bEndSerie )
						CopySerie( pTab, &i, pTmp1, &j, nLast1 ); //dokopiuj koniec serii 1
				}
			}
			nSerie++;
		} 

		while( j < nLast1 ) //dokopiowanie serii
		{
			CopySerie( pTab, &i, pTmp1, &j, nLast1 );
			nSerie++;
		}

	} while( nSerie > 1 );

	free( pTmp1 );
	free( pTmp2 );
}
