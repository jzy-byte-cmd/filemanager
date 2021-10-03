#include "standard.h"

using std::streampos;
using std::ios_base;

string g_sort_standard_s[9]={""};//[0]后缀名,[1]目标路径,[2]目标文件夹名,[3]文件格式名(包含什么字符) 
                                 //[4]要分类的文件夹,[5]是否区分后缀,
                                 //[6]是否将子文件夹作为文件分类
                                 //[7]是否精确搜索,[8]是否保留原目录/文件
long int g_tell_l;//读取data.txt的数据指针,记录上一次读取的位置,下次直接从这里开始读取
vector<string> file_name;//读取的所有文件名(包括子文件夹名)


int input_data();
int input_cur_file(string enter);
void error_out(string err_code);
int file_operate();
int replace_r_n();
extern int classify(
                string document_name,
                string target_location,
                string target_filename,
                string extra_name_option,
                string extra_name,
                string precise_option,
                string reserve,
                string son_file_as_document
                );//分类函数

int input_data()//读取文件分类标准
{
    int num=0;//文件路径中空格的个数
    ifstream in;
    ofstream out;
    in.open("data.txt",ios::in|ios::binary);//读取分类标准
    if(in.fail())//如果读取数据失败
    {
        in.open("data.txt",ios::in|ios::binary);//再试一次
        if(in.fail())//如果还是失败,输出错误代码至错误txt文件,退出程序
        {
            cout<<"文件操作失败,请确认文件是否全部出于关闭状态..."<<endl;
            cout<<"error code: C001"<<endl;
            error_out("C001");//写入错误码
            return -1;//向主函数传递错误代码,命令其终止执行
        }
        in.seekg(g_tell_l, ios::beg); //定位到上一次读取完毕的位置
        getline(in, g_sort_standard_s[0]);
        getline(in, g_sort_standard_s[1]);
        getline(in, g_sort_standard_s[2]);
        getline(in, g_sort_standard_s[3]);
        getline(in, g_sort_standard_s[4]);
        getline(in, g_sort_standard_s[5]);
        getline(in, g_sort_standard_s[6]);
        getline(in, g_sort_standard_s[7]);
        getline(in, g_sort_standard_s[8]);
        g_tell_l = in.tellg(); //保存当前文件读取位置
        in.close();
        int test=replace_r_n();
    }
    else
    {
        in.seekg(g_tell_l, ios::beg); //定位到上一次读取完毕的位置
        getline(in, g_sort_standard_s[0]);
        getline(in, g_sort_standard_s[1]);
        getline(in, g_sort_standard_s[2]);
        getline(in, g_sort_standard_s[3]);
        getline(in, g_sort_standard_s[4]);
        getline(in, g_sort_standard_s[5]);
        getline(in, g_sort_standard_s[6]);
        getline(in, g_sort_standard_s[7]);
        getline(in, g_sort_standard_s[8]);
        g_tell_l = in.tellg(); //保存当前文件读取位置
        in.close();
        int test=replace_r_n();
    }
    //读取完成
    return 0;
}


void error_out(string err_code)//错误码写入
{
    ofstream err_out;
    err_out.open("error.txt", ios::out | ios::app); //写入错误码到error.txt文件内
    if (err_out.fail())                             //如果连error.txt都打开失败,启用error2.txt
    {                                                //并追加error.txt打开失败的错误码
        err_out.open("error2.txt", ios::out | ios::app);
        err_out <<err_code << endl
                << "C002" << endl; //写入错误码
        err_out.close();
    }
    err_out << err_code << endl; //写出错误码
    err_out.close();

}



int file_operate()
{
    ofstream out;
    int classify_result=0;
    string movement="move /y",target_path="";
    string location = "cd " + g_sort_standard_s[4];
    const char *path,*move,*copy;
    out.open("enter_and_target.cmd",ios::out|ios::app);
    out<<location<<endl;
    if(g_sort_standard_s[6].compare("true")==0)
    {
        out<<"dir /b >target.txt"<<endl;
        out.close();
        system("enter_and_target.cmd");
        system("erase enter_and_target.cmd");
        int standby=input_cur_file(g_sort_standard_s[4]);
       // cout<<"standby"<<endl;
        if(standby==-1)
        {
            //cout<<"exit"<<endl;
            exit(-1);
        }
        //cout<<"before classify"<<endl;
        classify_result = classify(g_sort_standard_s[3],
                                   g_sort_standard_s[1],
                                   g_sort_standard_s[2],
                                   g_sort_standard_s[5],
                                   g_sort_standard_s[0],
                                   g_sort_standard_s[7],
                                   g_sort_standard_s[8],
                                   g_sort_standard_s[6]);
       // cout<<"prepare"<<endl;
        if ((g_sort_standard_s[8].compare("false")) == 0)//如果不保留源文件
        {
            cout<<"false"<<endl;
            target_path="mkdir";
            target_path+=" \""+g_sort_standard_s[1];
            target_path+=g_sort_standard_s[2]+"\"";
            path=target_path.c_str();
            system(path);
            target_path.clear();
            target_path+=" \""+g_sort_standard_s[1]+g_sort_standard_s[2]+"\"";
            for (int k = 0; k < file_name.size(); k++)
            {
                movement+=" \""+file_name[k]+"\""+target_path;
                move=movement.c_str();
                system(move);
                target_path.clear();
                movement="move /y";
            }
        }
        else
        {
            cout<<"true"<<endl;
            target_path="mkdir";
            target_path+=" \""+g_sort_standard_s[1];
            target_path+=g_sort_standard_s[2]+"\"";
            path=target_path.c_str();
            system(path);
            target_path.clear();
            target_path+=" \""+g_sort_standard_s[1]+g_sort_standard_s[2]+"\"";
            string copyment="copy /y";
            for (int k = 0; k < file_name.size(); k++)
            {
                copyment+=" \""+file_name[k]+"\"";
                cout<<copyment<<endl;
                copyment+=target_path;
                copy=copyment.c_str();
                system(copy);
                copyment="copy /y";
            }
        }
    }
    else
    {
        out<<"dir /a:-d /b >target.txt"<<endl;
        out.close();
        system("enter_and_target.cmd");
        system("erase enter_and_target.cmd");
        int standby=input_cur_file(g_sort_standard_s[4]);
        if(standby==-1)
        {
            exit(-1);
        }
        classify_result = classify(g_sort_standard_s[3],
                                   g_sort_standard_s[1],
                                   g_sort_standard_s[2],
                                   g_sort_standard_s[5],
                                   g_sort_standard_s[0],
                                   g_sort_standard_s[7],
                                   g_sort_standard_s[8],
                                   g_sort_standard_s[6]);
        if ((g_sort_standard_s[8].compare("false")) == 0)//如果不保留原文件
        {
            target_path="mkdir";
            target_path+=" \""+g_sort_standard_s[1];
            target_path+=g_sort_standard_s[2]+"\"";
            path=target_path.c_str();
            system(path);
            target_path.clear();
            target_path+=" \""+g_sort_standard_s[1]+g_sort_standard_s[2]+"\"";
            for (int k = 0; k < file_name.size(); k++)
            {
                movement+=" \""+file_name[k]+"\""+target_path;
                move=movement.c_str();
                system(move);
                target_path.clear();
                movement="move /y";
            }
        }
        else
        {
            target_path="mkdir";
            target_path+=" \""+g_sort_standard_s[1];
            target_path+=g_sort_standard_s[2]+"\"";
            path=target_path.c_str();
            system(path);
            target_path.clear();
            target_path+=" \""+g_sort_standard_s[1]+g_sort_standard_s[2]+"\"";
            string copyment="copy /y";
            for (int k = 0; k < file_name.size(); k++)
            {
                copyment+=" \""+file_name[k]+"\"";
                cout<<copyment<<endl;
                copyment+=target_path;
                copy=copyment.c_str();
                system(copy);
                copyment="copy /y";
            }
        }
    }

    return 0;
}

int input_cur_file(string enter)//当前目录下所有文件名的读取
{
    enter+="target.txt";
    string file_name_T;//文件名传递
    ifstream in;
    int check=1;
    cout<<enter<<endl;
    in.open(enter,ios::in|ios::binary);
    if(in.fail())
    {
        in.open(enter,ios::in|ios::binary);
        if(in.fail())
        {
            error_out("C003");
            return -1;
        }
        while (check)//从target.txt内读取目标文件夹的所有文件名
        {
            getline(in, file_name_T);
            file_name.push_back(file_name_T);
            if(in.peek()==EOF)
            {
                check=0;
            }
        }
        in.close();
        enter = "erase " + enter;
        const char *target_erase = enter.c_str();
        system(target_erase);
    }
    else
    {
        while (check) //从target.txt内读取目标文件夹的所有文件名
        {
            getline(in, file_name_T);
            file_name.push_back(file_name_T);
            if (in.peek() == EOF)
            {
                check = 0;
            }
        }
    }
    in.close();
    enter="erase "+enter;
    const char *target_erase=enter.c_str();
    system(target_erase);
    return 0;
}


int replace_r_n()
{
    for(int k=0;k<9;k++)
    {
        for(int i=0;i<g_sort_standard_s[k].size();i++)
        {
            if(g_sort_standard_s[k][i]=='\r'||g_sort_standard_s[k][i]=='\n')
            {
                g_sort_standard_s[k].erase(i,1);
            }
        }
    }
    return 0;
}
