#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

int minval(vector<int> vec)
{
    int min = vec[0];
    #pragma omp parallel for reduction(min:min)
    for(int i=0;i<vec.size();i++)
    {
        if(vec[i]<min)
        {
            min = vec[i];
        }
    }
    return min;
}

int maxval(vector<int> vec)
{
    int max = vec[0];
    #pragma omp parallel for reduction(max:max)
    for(int i=0;i<vec.size();i++)
    {
        if(vec[i]>max)
        {
            max = vec[i];
        }
    }
    return max;
}

int averageval(vector<int> vec)
{
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<vec.size();i++)
    {
        sum += vec[i];
    }
    return (sum/(vec.size()));
}

int main()
{
    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    cout<<"Minimum value: "<<minval(vec)<<endl;
    cout<<"Maximum value: "<<maxval(vec)<<endl;
    cout<<"Average of values: "<<averageval(vec)<<endl;
    return 0;
}