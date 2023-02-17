#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <bits/stdc++.h>
#define range(container) std::begin(container), std::end(container)
std::ostream& operator<<(std::ostream& os, std::vector<int> v)
{
    for (auto item : v)
    {
         os << item <<' ';
    }
    return os;

}
std::vector<int> operator-(const std::vector<int>& v_1, const std::vector<int>& v_2)
{
    if (v_1.size() != v_2.size())
    {
       throw("sequence_lhs.size() != sequence_rhs.size()");

    }

    std::vector<int> v_diff(v_1.size());
    for(auto i = 0; i < v_1.size(); ++i)
        v_diff[i] = v_1[i] - v_2[i];
    return v_diff;
}
void write_vector(std::vector<int>& v)
{
    std::cout<<"Enter number of elements you want to add: ";
    int n = 0;
    std::cin>> n;
    for(auto i = 0; i < n; i++ )
    {
        int el;
        int pos;
        auto iter = std::begin(v);
        std::cout<<"Enter " << i+1 << " element's position: ";
        std::cin >> pos;
        if (pos >= v.size())
            {
                std::cout << "Position is out of the range of the sequence " << std::endl;;
                break;
            }
        iter+= pos;
        std::cout<<"Enter " << i+1 << " element: ";
        std::cin >> el;
        v.insert(iter, el);
    }

}
void random_mix_vector(std::vector<int>& v)
{
    std::random_device d;
	std::mt19937_64 mt(d());
	std::uniform_int_distribution<int> distribution(0, v.size()- 1);
	for (auto i = 0; i < 3*v.size(); i++)
    {
        auto j = distribution(mt);
        auto p = distribution(mt);
        std::swap(v.at(j), v.at(p));
    }

}
void delete_duplicants(std::vector<int>& v)
{
    auto end = std::end(v);
    for (auto i = std::begin(v); i != end; i++)
    {
        end = std::remove(i + 1 , end, *i);
    }
    v.erase(end, std::end(v));
}
int count_uneven_nombers(std::vector<int>& v)
{
    auto nomber = 0;
    for (auto i = 0; i < v.size(); i++)
    {
        if (v.at(i) % 2 != 0)
        {
            nomber++;
        }
    }
      return nomber;
}
 bool isPrime(int n)
{
    if (n <= 1)return false;
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0) return false;
    }
return true;
}
int prime_numbers_searcher(std::vector<int>& v)
{
    for (auto i = 0; i < v.size(); i++)
    {
        if (isPrime(v.at(i))) return v.at(i);
    }
    std::cout<<" There are no prime numbers "<<std::endl;

}

void replace_vector_with_square_vector(std::vector<int>& v)
{
    std::vector<int>  squares(v.size());
    std::transform(std::begin(v), std::end(v), std::back_inserter(squares), [](auto item){return item * item;});
    for(auto i =0; i < v.size(); i++)
    {
            v.at(i) = squares.at(i+v.size());
    }
}
void print_top_3_largest(std::vector<int>& v)
{
    int first, second, third;

    if (v.size() < 3)
    {
        std::cout << " Invalid Input ";
        return;
    }

    first = second = third = INT_MIN;
    for(int i = 0; i < v.size(); i++)
    {
        if (v.at(i) > first)
        {
            third = second;
            second = first;
            first = v.at(i);
        }
        else if (v.at(i) > second && v.at(i) != first)
        {
            third = second;
            second = v.at(i);
        }

        else if (v.at(i) > third && v.at(i) != second)
            third = v.at(i);
    }

    std::cout << "Ex.16 Three largest elements are : "
        << first << " " << second << " "
        << third << std::endl;
}
int main()
{
    int n = 10;
    std::vector<int>  sequence_1(10);
    for (auto i = 0; i < 10; i++) sequence_1[i] = i;
    std::cout<<"Ex.1 sequence number 1: "<<sequence_1<<std::endl;
    write_vector(sequence_1);
    std::cout<<"Ex.2 changed by cin sequence number 1: "<<sequence_1<<std::endl;
    random_mix_vector(sequence_1);
    std::cout<<"Ex.3 mixed sequence number 1: "<<sequence_1<<std::endl;
    std::cout << "Ex.4 Number of uneven numbers in the sequence: " << count_uneven_nombers(sequence_1)<<std::endl;
    delete_duplicants(sequence_1);
    std::cout<<"Ex.5 Sequence number 1 without duplicants: "<<sequence_1<<std::endl;
    std::cout<<"Ex.6 Minimal element of the sequence: " << *(std::min_element(range(sequence_1)))<<
    " Maximal element of the sequence: "<< *(std::max_element(range(sequence_1)))<<std::endl;
    std::cout<<"Ex.7 First prime number in the sequence is: " << prime_numbers_searcher(sequence_1)<<std::endl;
    replace_vector_with_square_vector( sequence_1);
    std::cout<<"Ex.8 sequence number 1 replaced with squares: "<<sequence_1<<std::endl;
    std::vector<int>  sequence_2(sequence_1.size());
    std::random_device k;
	std::mt19937_64 mt(k());
	std::uniform_int_distribution<int> distribution(0, 1000);
	for (auto i = 0; i < sequence_2.size(); i++)
    {
        sequence_2.at(i) = distribution(mt);
    }
    std::cout<<"Ex.9 Sequence number 2: "<<sequence_2<<std::endl;
    std::cout<<"Ex.10 Accumulation of second sequence: " << std::accumulate(sequence_2.begin(),
                                                                       sequence_2.end(), 0ull)<<std::endl;
    std::cout<<"How many numbers in the sequence number 2 do you want to replace with 1?";
    int number_of_el_to_be_replaced;
    std::cin>> number_of_el_to_be_replaced;
    for (auto i =0; i < number_of_el_to_be_replaced; i++)
    {
        sequence_2.at(i) = 1;
    }
     std::cout<<"Ex.11 Sequence number 2 with 1: "<<sequence_2<<std::endl;
     auto sequence_3 = sequence_1 - sequence_2;
     std::cout<<"Ex.12 Difference between sequence number 1 and number 2 (Sequence 3): "<< sequence_3 << std::endl;
     std::replace_if(range(sequence_3), [](int &i){return i < 0;}, 0);
     std::cout<<"Ex.13 Sequence number 3: "<<sequence_3<<std::endl;
     auto remove_from = std::remove_if(range(sequence_3),[](int &i){return(i == 0);});
     sequence_3.erase(remove_from, std::end(sequence_3));
     std::cout<<"Ex.14 Sequence number 3 without 0: "<<sequence_3<<std::endl;
     std::reverse(range(sequence_3));
     std::cout<<"Ex.15 Sequence number 3 (reversed) : "<<sequence_3<<std::endl;
     print_top_3_largest(sequence_3);
     std::sort(range(sequence_1));
     std::sort(range(sequence_2));
     std::cout<<"Ex.17 Sorted sequence 1: "<< sequence_1<<std::endl<<"Sorted sequence 2: "<< sequence_2<<std::endl;
     std::vector<int> sequence_4;
     copy(range(sequence_1), back_inserter(sequence_4));
     copy(range(sequence_2), back_inserter(sequence_4));
     std::sort(range(sequence_4));
     std::cout<<"Ex.18 Sequence number 4: "<<sequence_4<<std::endl;
     auto el_counts = count(range(sequence_4), 1);
     std::cout<<"Ex.19 The range of sorted placement of 1 : "<< el_counts << std::endl;
     std::cout<<"Ex.20 Sequence number 1: "<<sequence_1<<std::endl<<"Sequence number 2: "<<sequence_2
     <<std::endl<<"Sequence number 3: "<<sequence_3<<std::endl<<"Sequence number 4: "<<sequence_4<<std::endl;
}
