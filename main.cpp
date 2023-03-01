//
//  main.cpp
//  ParcerINIFile
//
//  Created by Павел on 28.02.2023.
//
#include <unistd.h>
#include <sstream>
 #include <fstream>
 #include <string>
 #include <vector>
 #include <stdio.h>
 #include <memory>
 #include <mutex>
 #include <cstdlib>
 #include <map>
 #include <algorithm>
#include "IParcer.hpp"
#include "Parcer.hpp"

int main(int argc, char** argv){
     std::string file = "parcer.txt";// исходный файл
     std::string file2 = "text.txt";//  обработанный файл
                                    //  ini.txt файл для записи модификаций
     Parcer config;
     config.getLineFile(file);
     config.PrintFile();
     config.WriteFile(file2);
     config.Processing();
     return 0;
}
