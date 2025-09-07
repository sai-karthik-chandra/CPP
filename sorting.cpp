#include<iostream>
#include<vector>
using namespace std;

void swap(int& x,int& y)
{
	x = x+y;
	y = x-y;
	x = x-y;
}

void printArray(int arr[],int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

void selectionSort(int arr[],int n)
{
	for(int i=0;i<n-1;i++)
	{
		int min_idx = i;
		for(int j=i+1;j<n;j++)
		{
			if(arr[j]<arr[min_idx])
				min_idx = j;
		}
		if(min_idx != i)
		{
			swap(arr[i],arr[min_idx]);
		}
	}

}

void bubbleSort(int arr[],int n)
{
	for(int i=0;i<n-1;i++)
	{
		bool isSorted = true;
		for(int j=0;j<n-1-i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				swap(arr[j],arr[j+1]);
				isSorted = false;
			}
		}
		if(isSorted)
			return;
	}

}

void insertionSort(int arr[],int n)
{
	for(int i=1;i<n;i++)
	{
		int key = arr[i];
		int j = i-1;
		while(j>=0 && arr[j]>key)
		{
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = key;
	}
}

//first sorted array arr[l...mid]
//second sorted array arr[mid+1...h]
void merge(int arr[],int l,int mid,int h)
{
	vector<int> temp;
	int i=l;
	int j=mid+1;

	while(i<=mid && j<=h)
	{
		if(arr[i]<=arr[j])
		{
			temp.push_back(arr[i]);
			i++;
		}
		else
		{
			temp.push_back(arr[j]);
			j++;
		}
	}
	while(i<=mid)
	{
		temp.push_back(arr[i]);
		i++;
	}
	while(j<=h)
	{
		temp.push_back(arr[j]);
		j++;
	}

	//copy elements from temp to arr[l...h]
	for(int k=l;k<=h;k++)
	{
		arr[k] = temp[k-l];
	}
}

void mergeSort(int arr[],int l,int h)
{
	if(l<h)
	{
		int mid = l + (h-l)/2;
		mergeSort(arr,l,mid);
		mergeSort(arr,mid+1,h);
		merge(arr,l,mid,h);
	}
	return;
}

int partition(int arr[],int l,int h)
{
	int pivot = arr[l];
	int i = l-1;
	int j = h+1;

	while(true)
	{
		do
		{
			i++;
		}while(arr[i]<pivot);
		do
		{
			j--;
		}while(arr[j]>pivot);

		if(i<j)
		{
			swap(arr[i],arr[j]);
		}
		else
		{
			return j;
		}
	}
}

void quickSort(int arr[],int l,int h)
{
	if(l<h)
	{
		int p = partition(arr,l,h);
		quickSort(arr,l,p);
		quickSort(arr,p+1,h);
	}
	return;
}

int main()
{
	int n;
	cin>>n;
	int* arr = new int[n];
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}
	printArray(arr,n);
	
	selectionSort(arr,n);
	//bubbleSort(arr,n);
	//insertionSort(arr,n);
	//mergeSort(arr,0,n-1);
	//quickSort(arr,0,n-1);
	
	printArray(arr,n);
	delete[] arr;
	return 0;
}
