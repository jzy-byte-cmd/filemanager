#include "standard.h"


int classify(   string document_name,//文件名包含的内容
                string target_location,//目标文件夹
                string target_filename,//目标文件夹名
                string extra_name_option,//是否特定后缀名
                string extra_name,//后缀名
                string precise_option,//是否精确搜索
                string reserve,//是否保留原文件
                string son_file_as_document//是否将子文件夹作为文件分类
                );
                  //分类函数：分类子文件夹和文件


extern vector<string> file_name;//file_name待识别的文件名,file_name_valid已识别的文件名

int classify(   string document_name,
                string target_location,
                string target_filename,
                string extra_name_option,
                string extra_name,
                string precise_option,
                string reserve,
                string son_file_as_document
                )
{

    string alphabet_big ="QWERTYUIOPASDFGHJKLZXCVBNM";
    string alphabet_small ="qwertyuiopasdfghjklzxcvbnm";
    string numbers ="0123456789";
    string character =",.;'[]<>?{}~!@#$%^&*()`，。、；‘【】、《》？：“”~！@#￥%……&*（）·{}-=_+-=——+";
    size_t npos;
    string found;
    vector<string> found_valid;
    if (extra_name_option.compare("true") == 0) //如果区分后缀
    {
        for (int i = 0; i < file_name.size(); i++) //将含有目标后缀的文件名挑出来
        {
            npos=file_name[i].find(extra_name,file_name[i].size()-extra_name.size()-1);
            if(npos!=file_name[i].npos)
            {
                found_valid.push_back(file_name[i]);
            }
        }
        file_name.clear();
        file_name=found_valid;
        found_valid.clear();
    }
    if(precise_option.compare("true")==0)//如果是精确搜索
    {
        for(int k=0;k<document_name.size();k++)
        {
            switch(document_name[k])
            {
                case '*':
                break;
                case '<':
                for(int l=0;l<file_name.size();l++)
                {
                    npos=alphabet_big.find(file_name[l][k]);
                    if(npos!=alphabet_big.npos)
                    {
                        found_valid.push_back(file_name[l]);
                    }
                }
                file_name.clear();
                file_name=found_valid;
                found_valid.clear();
                break;
                case '>':
                for(int l=0;l<file_name.size();l++)
                {
                    npos=alphabet_small.find(file_name[l][k]);
                    if(npos!=alphabet_small.npos)
                    {
                        found_valid.push_back(file_name[l]);
                    }
                }
                file_name.clear();
                file_name=found_valid;
                found_valid.clear();
                break;
                case '|':
                for(int l=0;l<file_name.size();l++)
                {
                    npos=numbers.find(file_name[l][k]);
                    if(npos!=numbers.npos)
                    {
                        found_valid.push_back(file_name[l]);
                    }
                }
                file_name.clear();
                file_name=found_valid;
                found_valid.clear();
                break;
                case '?':
                for(int l=0;l<file_name.size();l++)
                {
                    npos=character.find(file_name[l][k]);
                    if(npos!=character.npos)
                    {
                        found_valid.push_back(file_name[l]);
                    }
                }
                file_name.clear();
                file_name=found_valid;
                found_valid.clear();
                break;
                default:
                for(int l=0;l<file_name.size();l++)
                {
                    if(file_name[l][k]==document_name[k])
                    {
                        found_valid.push_back(file_name[l]);
                    }
                }
                file_name.clear();
                file_name=found_valid;
                found_valid.clear();
                break;
            }
        }
    }
    else
    {
        for(int i=0;i<document_name.size();i++)
        {
            if (document_name[i]=='*' ||
                document_name[i] == '?' ||
                document_name[i] == '<' ||
                document_name[i] == '>' ||
                document_name[i] == '|')
            {
                document_name.erase(i,1);
                i=0;
            }
        }
        for(int k=0;k<file_name.size();k++)
        {
            npos=file_name[k].find(document_name);
            if(npos!=file_name[k].npos)
            {
                found_valid.push_back(file_name[k]);
            }
        }
        file_name.clear();
        file_name = found_valid;
        found_valid.clear();
    }

    return 0;

}