//
//  Parcer.hpp
//  ParcerINIFile
//
//  Created by Павел on 28.02.2023.
//

#ifndef Parcer_hpp
#define Parcer_hpp

 #include <stdio.h>
 #include <iostream>
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

class Parcer: public IParcer{
public:
    ~Parcer();
    
 void Clear();
 bool getLineFile( const std::string& file);
 bool WriteFile(const  std::string& file2);
 void PrintFile();
 void SaveMapToFILE();
 void Processing();
 bool FindKeyinSection();
 bool FindSection();
 bool FindfKey();
 bool FindValue();
 bool FindValueKeySection();
 void ChangeKeyValue();

 private:
      std::map<std::string, std::map<std::string, std::string>> map;
  };

#endif /* Parcer_hpp */
