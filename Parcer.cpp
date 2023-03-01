//
//  Parcer.cpp
//  ParcerINIFile
//
//  Created by Павел on 28.02.2023.
//
#include "IParcer.hpp"
#include "Parcer.hpp"
#include <unistd.h>
#include <cstdio>

Parcer::~Parcer() {
    Clear();
}
void Parcer::Clear() {
    map.clear();
}

static void TrimLine(std::string& str){//обрезка строки
    str.erase(0, str.find_first_not_of(' '));//удаляет пробелы вначале строки
    str.erase(str.find_last_not_of(' ') + 1);//удаляет пробелы в конце строки
}


bool Parcer::getLineFile(const std::string& file){//читаем из файла построчно
    std::ifstream fs;
    fs.open(file);
    if (!fs.is_open()){
       std::cout<<"Файл не удалось открыть!"<<std::endl;
    }else{
    std::cout<<"Файл "<<file<<" открыт\n\n";
    }
    std::string line = "";
    std::map<std::string, std::string>* internalMap = nullptr; // создали внутреннюю карту
    size_t left;
    size_t right;
    size_t equal;
    while (std::getline(fs, line)){
    if (line.size() == 0) continue;    //пустая ли строка
        if ((std::string::npos != (left = line.find("["))) &&
            (line.npos != (right = line.find("]")))){//Проверка на признак заголовка - наличие [ ]
            
            std::size_t pos = line.find(']');//проверяем , есть ли текст за правой скобкой
            if (line[line.size() - 1] != ']'){
            if(pos!=std::string::npos)
            line = line.substr(0,pos+1);
            }
            std::string root = line.substr(left + 1, right - left - 1);
            TrimLine(root);//удаление пробелов
            if (!root.empty()){
                map[root] = std::map<std::string, std::string>{};//Запись в карту заголовка
                internalMap = &(map[root]);
            }
        }else if (std::string::npos != (equal = line.find("=")))
        {
            std::string key = line.substr(0, equal);
            size_t notePos = line.find(";");
            std::string value;
            if (std::string::npos != notePos){
                value = line.substr(equal + 1, notePos - equal - 1);
            }else{
                value = line.substr(equal + 1, line.size() - 1);
            }
            TrimLine(key);
            TrimLine(value);
            if (internalMap != nullptr && !key.empty()){
                (*internalMap)[key] = value;
            }}}
    fs.close();
    return true;
}


void Parcer::PrintFile(){//функция вывода на экран ини из мап
    std::cout <<"=================="<< std::endl;
    for (auto it = map.begin(); it != map.end(); ++it){
        std::cout << it->first.c_str() << std::endl;
        for (auto vit = it->second.begin(); vit != it->second.end(); ++vit){
            std::cout << vit->first.c_str()<<"  =  " << vit->second.c_str()<<std::endl;
        }
        std::cout <<"=================="<< std::endl;
    }}

bool Parcer::WriteFile( const std::string& file2){//записать Мап  в  файл
    std::ofstream fs;
    fs.open(file2, std::ios::out );
    if (!fs.is_open()){
       std::cout<<"Файл не удалось открыть!"<<std::endl;
    }else{
        std::cout<<"Файл "<<file2<<" открыт"<<std::endl;

    for (auto itr = map.begin(); itr != map.end(); ++itr){
        fs << "[" << itr->first << "]" << std::endl;
        for (std::map<std::string, std::string>::iterator sub_itr = itr->second.begin();
            sub_itr != itr->second.end(); ++sub_itr)
        {
            fs << sub_itr->first << "=" << sub_itr->second << std::endl;
        }}
        std::cout<<"Исходный INI файл обработан!\n";
        std::cout<<"Полученные данные записаны в файл "<<file2<<" \n";
    fs.close();
    }
    return true;
}

void Parcer::SaveMapToFILE() {//функция сохранения мап в файл
    std::string pathfile;
    std::ofstream fs;
    std::cout << "Введите имя файла ->" << std::endl;
    std::cin >> pathfile;
    fs.open(pathfile, std::ios::binary | std::ios::in | std::ios::out);
    if (!fs.is_open()) {
        std::cout << "Не удалось открыть файл!" << std::endl;
    }else{
        std::cout << "Файл "<<pathfile<<" открыт,изменения сохранены!" << std::endl;
        for (auto itr = map.begin(); itr != map.end(); ++itr) {

            fs << "[" << itr->first << "]" << std::endl;
            for (std::map<std::string, std::string>::iterator sub_itr = itr->second.begin();
                sub_itr != itr->second.end(); ++sub_itr)
            {
                fs << sub_itr->first << "=" << sub_itr->second << std::endl;
            }}}
    fs.close();
}

bool Parcer:: FindKeyinSection(){
    std::string  key;
    std::cout << "Введите требуемый ключ -> \n";
    std::cin >> key;
    for (auto itr = map.begin(); itr != map.end(); itr++) {
        for (std::map<std::string, std::string>::iterator sub_itr = itr->second.begin(); sub_itr != itr->second.end(); sub_itr++) {
            if (sub_itr->first == key) {
                std::cout << "Ключ "<<key<<" находится в заголовке " << itr->first << std::endl;
                return 0;
            }}}
    std::cout << "Ключ "<<key<<" отсутствует " <<  std::endl;
    return 0;
}



bool Parcer::FindSection() {//существует ли секция
    std::string  sec;
    std::cout << "Введите название заголовка, чтобы узнать существует ли он в файле \n";
    std::cin >> sec;
    if (map.count(sec)){
        std::cout << "Заголовок "<<sec<<" существует!" << std::endl;
        return 0;
    }else{
        std::cout << "Заголовок "<<sec<<" не существует!" << std::endl;
        return 0;
    }}
bool Parcer::FindfKey() {//  существует ли ключ
    std::string  key;
    std::cout << "Введите название ключа, чтобы узнать существует ли он в файле \n";
    std::cin >> key;
    for (auto itr = map.begin(); itr != map.end(); itr++) {
        for (std::map<std::string, std::string>::iterator sub_itr = itr->second.begin(); sub_itr != itr->second.end(); sub_itr++) {
            if (sub_itr->first == key) {
                std::cout << "Kлюч "<<key<<" существует!" << std::endl;
                return 0;
                }}}
    std::cout << "Kлюч "<<key<<" не существует!" << std::endl;
    return 0;
}

bool Parcer::FindValue() {//существует ли значение
    std::string  value="";
    std::cout << "Введите название значения, чтобы узнать существует ли оно в файле -> \n";
    std::getline(std::cin >> std::ws, value);//в том числе ввод строки с пробелами
    for (auto itr = map.begin(); itr != map.end(); itr++) {
        for (std::map<std::string, std::string>::iterator sub_itr = itr->second.begin(); sub_itr != itr->second.end(); sub_itr++) {
            if (value==sub_itr->second) {
               std::cout << "\nЗначение : "<<value<<" существует!" << std::endl;
               return 0;
            }}}
  std::cout << "\nЗначение : "<<value<<" не  существует!" << std::endl;
    return 0;
}

bool Parcer::FindValueKeySection() {//найти значение ключа в секции
    std::string root, key, value;
    std::cout << "Введите ключ: \n";
    std::cin >> key;
    std::cout << "Введите секцию: \n";
    std::cin >> root;
    for (auto itr = map.begin(); itr != map.end(); itr++) {
             for (std::map<std::string, std::string>::iterator sub_itr = itr->second.begin(); sub_itr != itr->second.end(); sub_itr++) {
                 if (sub_itr->first == key && itr->first==root) {
                     std::cout << "Значение у ключа "<<key<<" в  секции "<<root<< "  ->  " << sub_itr->second<<std::endl;
                     return 0;
                }}}
std::cout << "Ключ "<<key<<" не существует " << std::endl;
return 0;
}
void Parcer::ChangeKeyValue() {//заменить значение ключа на новое или создать
    std::string root, key, value;
    std::cout << "Введите секцию: \n";
    std::cin >> root;
    std::cout << "Введите ключ: \n";
    std::cin >> key;
    std::cout << "Введите значение, которое  необходимо модифицировать: \n";
    std::getline(std::cin >> std::ws, value);//в том числе ввод строки с пробелами
    auto itr = map.find(root);
    if (map.end() != itr){
        std::map<std::string, std::string>::iterator it = itr->second.find(key);
        if (it != itr->second.end()){
            it->second = value;
        }else{
            itr->second[key] = value;
        }
    }else{
        std::map<std::string, std::string> m;
        m[key] = value;
        map[root] = std::move(m);
    }
    std::cout <<  std::endl;
    PrintFile();
    std::cout << "Изменения внесены !" << std::endl;
}

void Parcer::Processing(){
    int num,  Y=0;
    do {
        std::cout << "\nPARCER \n";
        std::cout << "Выберите действие\n";
        std::cout << "1)В каком заголовке находится ключ.\n";
        std::cout << "2)Поиск заголовка.\n";
        std::cout << "3)Существует ли  ключ в файле.\n";
        std::cout << "4)Существует ли значение  в файле.\n";
        std::cout << "5)Поиск значения  ключа в секции.\n";
        std::cout << "6)Присвоить ключу значение.\n";
        std::cout << "7)Запись данных в файл.\n";
        std::cout << "8)Вывод данных.\n";
        std::cout << "9)Завершение работы.\n";
        std::cout << "\nВвод -> ";
        std::cin >> num;
    switch (num) {
        case 0:{}
    break;
        case 1:{ FindKeyinSection();
        }
    break;
        case 2:{ FindSection();
        }
    break;
        case 3:{ FindfKey();
        }
    break;
        case 4: {FindValue();
        }
    break;
        case 5:{ FindValueKeySection();
        }
    break;
        case 6: {ChangeKeyValue();
        }
    break;
        case 7: {SaveMapToFILE();
        }
    break;
        case 8:{PrintFile();
        }
    break;
    case 9:{
        std::cout<<"Работа завершена "<<std::endl;
        exit(0);
    }
        break;
    default:
    std::cout<<"Ошибка ввода, задайте корректные параметры "<<std::endl;
    break;
    }

} while (Y!=5);
}

  
