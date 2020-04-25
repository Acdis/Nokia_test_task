// nolka.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
std::vector<std::string> read_strings(std::string path);
std::vector<std::string> separate_string(std::string s);
bool is_char_eq(char ch);
int calculate_formula(std::string s);
bool is_digit(char);
bool is_znak(char x);
std::string get_cell_value(std::string adress);

std::map<std::string, int>  columns;
std::map<std::string, int> lines;
std::vector<std::vector<int>> result;
std::vector<std::string> vector;

int main()
{




    //vector = read_strings(argv[1]);
    vector = read_strings("C://division_by_zero.csv");
    std::vector<std::string> temp_res = separate_string(vector[0]);



    for (int i = 0; i < temp_res.size(); i++)
    {
        columns.insert(std::pair<std::string, int>(temp_res[i], i));
    }
        for (int i = 0; i < vector.size(); i++)
    {
        lines.insert(std::pair<std::string, int>(separate_string(vector[i])[0], i));
    }





    for (int i = 1; i < vector.size(); i++)
    {
        std::vector<int> temp;
        std::vector<std::string> strings = separate_string(vector[i]);
        for (int j = 1; j < strings.size(); j++)
        {

           if (is_char_eq(strings[j][0]) )
               temp.push_back(-1);
           else 
               temp.push_back(std::stoi(strings[j]));
           
        }
        result.push_back(temp);
    }
    for (int i = 1; i < vector.size(); i++)
    {
        std::vector<std::string> strings = separate_string(vector[i]);
        for (int j = 1; j < strings.size(); j++)
        {

            if (is_char_eq(strings[j][0]))
                result[i-1][j-1] =calculate_formula(strings[j]);


        }
       
    }


    std::vector < std::string> columns_output;
    std::vector < std::string> lines_output;

    for (auto& item : columns)
    {
        columns_output.push_back(item.first);
    }
    for (auto& item : lines)
    {
        lines_output.push_back(item.first);
    }

    for (int i = 0; i < columns_output.size()-1; i++)
    {
        std::cout << columns_output[i] << ',';
    }

    std::cout << columns_output[columns_output.size()-1]<< std::endl;

    for (int i = 0; i < result.size(); i++)
    {
        std::cout << lines_output[i+1] << ',';
        int j;
        for (j = 0; j < result[0].size()-1; j++)
            std::cout << result[i][j]<<','  ;
        std::cout << result[i][j];
        std::cout << std::endl;
    }

  




 

}


std::vector<std::string> read_strings(std::string path)
{
    std::vector<std::string> rez;
    std::string line;

    std::ifstream in(path); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
            rez.push_back(line);
        }
    }
    return rez;
}
std::vector<std::string> separate_string(std::string str)
{
    std::vector<std::string> arr;

    std::string delim(",");
    size_t prev = 0;
    size_t next;
    size_t delta = delim.length();

    while ((next = str.find(delim, prev)) != std::string::npos) {
        //Отладка-start
        std::string tmp = str.substr(prev, next - prev);

        //Отладка-end
        arr.push_back(str.substr(prev, next - prev));
        prev = next + delta;
    }
    //Отладка-start
    std::string tmp = str.substr(prev);

    //Отладка-end
    arr.push_back(str.substr(prev));

    return arr;
}
bool is_char_eq(char ch)
{
    return (ch == '=');
}

int calculate_formula(std::string s)
{
    char action;
    std::string arg1;
    std::string arg2;
    
    int i = 0;
    while (!is_znak(s[i]))
        i++;
    arg1 = s.substr(1,i-1);
    arg2 = s.substr(i+1, s.npos);
    action = s[i];

    bool is_arg1_formula = is_char_eq(arg1[0]);
    if (is_arg1_formula)
    {
        arg1 = calculate_formula(arg1);
    }
    else
    {
        arg1 = get_cell_value(arg1);
    }
    bool is_arg2_formula = is_char_eq(arg2[0]);
    if (is_arg2_formula)
    {
        arg2 = calculate_formula(arg2);
    }
    else
    {
        arg2 = get_cell_value(arg2);
    }
    switch (action)
    {
    case '+':
        return (std::stoi(arg1) + std::stoi(arg2));
    case '-':
        return (std::stoi(arg1) - std::stoi(arg2));
    case '*':
        return (std::stoi(arg1) * std::stoi(arg2));
    case '/':
        return (std::stoi(arg1)/std::stoi(arg2));
    }

    
}


bool is_digit(char x)
{
    return !(x < '0' || x>'9');
}
bool is_znak(char x)
{
    return (x == '+') || (x == '-') || (x == '*') || (x == '/');
}


std::string get_cell_value(std::string adress)
{
    int i = 0;
    

    while (!is_digit(adress[i]))
        i++;
    std::string column = adress.substr(0,i);
    std::string line = adress.substr(i,adress.npos);
    
    int temp_column = columns.find(column)->second;
    int temp_line = lines.find(line)->second;
    if (result[temp_line-1][temp_column-1] == -1)
        {

        return separate_string(vector[temp_line])[temp_column];

        }
    else
    {
        return std::to_string (result[temp_line-1][temp_column-1]);
    }


}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
