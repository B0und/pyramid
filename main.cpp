#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;

template <typename T>
void show_vector(std::vector<T>& vec);
void lineIntoVector(std::string& line, std::vector<int>& vec);
int getNumberOfLines(std::ifstream& file);
void createSumVec(std::vector<int>& first, std::vector<int>& second, std::vector<int>& result);
void max_adjacent_sum(std::vector<int>& vec);

int main()
{

    std::string line, next_line;
    std::ifstream file("pyramid.txt");
    std::vector<int> firstV,secondV,resultV;
    int lines_num = getNumberOfLines(file);

    std::getline(file,line);
    std::getline(file,next_line);
    lineIntoVector(line,firstV);
    lineIntoVector(next_line,secondV);
    createSumVec(firstV,secondV,resultV);

    for (int i = 2; i < lines_num; ++i)
    {
        getline(file,line);
        firstV.clear();
        lineIntoVector(line,firstV);
        createSumVec(resultV,firstV,resultV);
    }
    auto it = max_element(std::begin(resultV), std::end(resultV));
    cout << *it;
    return 0;
}
int getNumberOfLines(std::ifstream& file)
{
    std::string line;
    int counter = 0;
    while(std::getline(file,line))
        ++counter;
    file.clear(); // clear to read again
    file.seekg(0,file.beg);
    return counter;
}

void lineIntoVector(std::string& line, std::vector<int>& vec)
{
    std::stringstream iss(line);
    int number;
    while (iss >> number)
        vec.push_back(number);
}

template <typename T>
void show_vector(std::vector<T>& vec)
{
    for (auto i : vec)
        cout << i << " ";
    cout << endl;
}

void createSumVec(std::vector<int>& first, std::vector<int>& second,std::vector<int>& result)
{
    std::vector<int> temp;
    for (std::vector<int>::size_type i = 0; i < first.size(); ++i )
    {
        int j = i+1;
        int sum = first[i] + second[i];
        temp.push_back(sum);
        sum = first[i] + second[j];
        temp.push_back(sum);
    }
    result = temp;
    max_adjacent_sum(result);
}
void max_adjacent_sum(std::vector<int>& vec)
{
    if (vec.size() > 3) {
    std::vector<int> temp_vect;
    temp_vect.push_back(vec[0]);

    for (std::vector<int>::size_type i = 1; i < vec.size()-1; i+=2)
            temp_vect.push_back(std::max(vec[i],vec[i+1]));

    temp_vect.push_back(vec[vec.size()-1]);
    vec = temp_vect;
    }
}
