// nolka.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
std::vector<std::string> read_strings(std::string path);
std::vector<std::string> separate_string(std::string s);

int main()
{

    std::vector<std::vector<std::string>> result;
    std::map<std::string, int>  columns;
    std::map<std::string, int> lines;

    std::vector<std::string> vector = read_strings("C:\\test.csv");
    std::vector<std::string> temp_res = separate_string(vector[0]);



    for (int i = 0; i < temp_res.size(); i++)
    {
        columns.insert(std::pair<std::string, int>(temp_res[i], i));
    }

    for (int i = 0; i < vector.size(); i++)
    {
        lines.insert(std::pair<std::string, int>(separate_string(vector[i])[0], i));
    }
    std::cout << "Hello World!\n";
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
        std::cout << tmp << std::endl;
        //Отладка-end
        arr.push_back(str.substr(prev, next - prev));
        prev = next + delta;
    }
    //Отладка-start
    std::string tmp = str.substr(prev);
    std::cout << tmp << std::endl;
    //Отладка-end
    arr.push_back(str.substr(prev));

    return arr;
}
std::vector<std::string> search_function(std::string str)
{
    std::string line;
    char c;
    std::getline(std::cin, line);
    std::cin >> c;

    std::cout << std::count(line.begin(), line.end(), c);
    return 0;
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
