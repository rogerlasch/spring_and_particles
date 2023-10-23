


#ifndef G_START_H
#define G_START_H

#include<chrono>
#include<thread>
#include<sstream>
#include<fstream>
#include<format>

#define _FILENAME "main.txt"

struct G_STARTER{
G_STARTER(){
setlocale(LC_ALL, "Portuguese");
std::cout<<std::fixed;
std::cout.precision(2);
}
~G_STARTER(){
}
};

int64_t gettimestamp()
{
std::chrono::system_clock::time_point tp=std::chrono::system_clock::now();
std::chrono::system_clock::duration dtn=tp.time_since_epoch();
return std::chrono::duration_cast<std::chrono::milliseconds>(dtn).count();
}

template<class T>
T inputVal(const std::string& s){
T val;
std::cout<<s<<"\t";
std::cin>>val;
std::cout<<std::endl;
return val;
}

inline void lg_write(const std::string& str){
static std::ofstream ofn(_FILENAME);
ofn<<str<<std::endl;
}

inline void lg_lp(const std::string& s){
lg_write(s);
std::cout<<s<<std::endl;
}

#define _LOG(str, ...) lg_write(std::vformat(str, std::make_format_args(__VA_ARGS__)))
#define _LOG_P(str, ...) lg_lp(std::vformat(str, std::make_format_args(__VA_ARGS__)))
#endif
