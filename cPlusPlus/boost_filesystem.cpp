//g++ main.cpp -lboost_system -lboost_filesystem
#include <iostream>
// 判断文件是否存在
#include <boost/filesystem.hpp>
// 写入文件
#include <boost/filesystem/fstream.hpp>
// 解析ini文件
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
 
using namespace std;
 
#define FILE_MAX_SIZE 1024*40
 
int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

//读ini文件 文件已经存在
    if(!boost::filesystem::exists("config_test.ini")) {
        cerr<<"config.ini not exists."<<endl;
        return -1;
    }
    boost::property_tree::ptree root_node, tag_system;
    boost::property_tree::ini_parser::read_ini("config_test.ini", root_node);
    tag_system = root_node.get_child("System");
    cout<<"tag_system.count('number') : "<<tag_system.count("number")<<endl;

    if(tag_system.count("number") != 1) {
        cerr<<"reboot_cnt node not exists."<<endl;
    }
    int cnt = tag_system.get<int>("number");
    cout<<"reboot_cnt : "<<cnt<<endl;

//修改配置文件参数
    root_node.put<int>("System.number", 10);
    boost::property_tree::ini_parser::write_ini("config_test.ini", root_node);

//    读取整个文件
    if(!boost::filesystem::exists("config_test.ini")) {
        cerr<<"config.ini not exists."<<endl;
        return -1;
    }
    char *data = (char*)malloc(sizeof(char) * FILE_MAX_SIZE);
    boost::filesystem::ifstream ifstream("config_test.ini",ios_base::in);
    ifstream.read(data, FILE_MAX_SIZE);
    cout<<"data : "<<endl;
    cout<<data<<endl;
    free(data);
    ifstream.close();

//写ini文件 文件不存在
    if(!boost::filesystem::exists("config_2.ini")) {
        boost::filesystem::ofstream ofstream("config_2.ini", ios_base::out);
        ofstream<<"[System]";
        ofstream<<"\n";
        ofstream<<"name=zhangsan";
        ofstream.close();
    }
 
    return 0;
}