#ifndef SORT_H
#define SORT_H

void SelectionSort( int* pTab, int nSize );
void InsertionSort( int* pTab, int nSize );
void BubbleSort( int* pTab, int nSize );
void MixedSort( int* pTab, int nSize );
void HalfSort( int* pTab, int nSize );
void QuickSort( int* pTab, int l, int p );
void HeapSort( int* pTab, int nSize );
void NaturalMergeSort( int* pTab, int nSize );

void MergeSort( int* pTab, int* tmpTab, int nSize, int l, int p );
void Merge( int* pTab, int* tmpTab, int nSize, int l, int m, int p );

#endif

