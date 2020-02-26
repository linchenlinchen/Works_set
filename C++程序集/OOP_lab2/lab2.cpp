#include <iostream>
#include <fstream>
#include <regex>
using namespace std;
class Stack {
public:
    vector<string> stack_vec;
    void push(string string){
        Stack::stack_vec.push_back(string);
    }

    string pop() {
        string& out = stack_vec[stack_vec.size()-1];
        Stack::stack_vec.erase(stack_vec.end());
        return out;
    }
};

static bool can_work = true;/*默认在出现的#define都能定义成功*/
/*被定义的宏数组*/
static vector<vector<string>> define;
/*函数声明*/
vector<string> split(string str, const string &pattern);
string& trim(string &str);
string get_unprocessed_code(int number);
string& replace_all(string& str,const string& old_value,const string& new_value);
void put_processed_code(int number, string code);
void run_test(int test_case_number);
void remove(vector<string>&,int i);
void define_func(string word,string value);

/*主函数*/
int main() {
    for (int test_case_number = 1; test_case_number <= 2; test_case_number++) {
        run_test(test_case_number);
    }
    return 0;
}
/*移除第i个*/
void remove(vector<string>& code,int i){
    replace_all(code[i], code[i]+"","");
}
/*判断某些字符串是不是被预定义为0*/
bool isZero(const string str,vector<vector<string>> define){
    for (auto &i : define) {
        if(i[0] == str && i[1] != "0"){
            return false;
        }
    }
    return true;
}
//字符串分割函数
vector<string> split(string str, const string &pattern) {
    string::size_type pos;
    vector<string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size();
    for(unsigned int i=0; i<size; i++) {
        pos=str.find(pattern,i);
        if(pos<size) {
            string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}
/*详见https://blog.csdn.net/yao_hou/article/details/78840723*/
string& trim(string &str) {
    if (str.empty()){
        return str;
    }
    str.erase(0,str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
    return str;
}
/*传入的const参数代表在函数内部不可修改，但是传入的可以是一个变量*/
string& replace_all(string& str,const string& old_value,const string& new_value) {
    if(old_value==new_value){
        return str;
    }
    while(true){
        string::size_type pos(0);
        if((pos=str.find(old_value))!=string::npos   )
            str.replace(pos,old_value.size(),new_value);
        else   break;
    }
    return str;
}
bool can_conclude(vector<string> word){
    if(word[0] == "#include" &&
       word[1] != "<iostream>" &&
       word[1] != "\"iostream\""){
        return true;
    }
    return false;
}
void include(vector<string> word,string& line){
    replace_all(word[1], "\"", "");
    string filename = "test/" + word[1];
    string file;
    ifstream is(filename);
    if (!is.is_open()) {
        cout << "Broken input file.";
    } else {
        string line;
        while (getline(is, line)) {
            file.append(line).push_back('\n');
        }
        is.close();
    }
    /*传入的两个对象要是不同的，就和java一样*/
    replace_all(line, line+"", file);
}
void define_func(const string word,const string value){
    /*一般存储与定义*/
    vector<string> key_value;
    string result_value = value;
    key_value.push_back(word);
    for (int i = 0; i < define.size(); ++i) {
        if(result_value.find(define[i][0])!=string::npos){
            replace_all(result_value,define[i][0],define[i][1]);
        }
    }
    key_value.push_back(result_value);
    define.push_back(key_value);
}
void deleteAllMark(string &s, const string &mark) {
    size_t nSize = mark.size();
    while(1) {
        size_t pos = s.find(mark);    //  尤其是这里
        if(pos == string::npos)
        {
            return;
        }
        s.erase(pos, nSize);
    }
}
void undef(const string word){
    vector<vector<string>>::iterator it;
    for (it = define.begin(); it != define.end(); it++) {
        if ((*it)[0] == word) {
            define.erase(it);
            break;
        }
    }
}
string& get_pare(const string word) {/*仅通过函数声明获取参数名*/
    return split(split(word,"(")[1],")")[0];
}
string get_pare(const string word, const string name){
    string::size_type pos = word.find('(');
    if(split(split(word,"(")[1],")")[0] == name) {
        return split(split(word,"(")[2],")")[0];
    }
}
/*对给定的函数define进行匹配，匹配成功进行操作，不超过则啥事没干*/
void deal_special_define(string& line, const string word, const string value){
    if(line.find(split(word,"(")[0])!=string::npos) {/*如果是一个函数*/
        string new_word = word;
        string new_value = value + "";
        if(value.find("##") == string::npos) {
            replace_all(new_word, get_pare(word), get_pare(line));
            replace_all(new_value, get_pare(word), get_pare(line));/*替代value得到result*/
        } else{
            replace_all(new_word, get_pare(word), get_pare(line,split(word,"(")[0]));
            replace_all(new_value, get_pare(word), get_pare(line,split(word,"(")[0]));/*替代value得到result*/
        }

        string::size_type pos = new_value.find("#"+get_pare(line));
        if(pos != string::npos){
            replace_all(new_value,"#"+get_pare(line),"\""+get_pare(line)+"\"");
        } else if(new_value.find("##")){
            replace_all(new_value," ## ","");
        }
        replace_all(line,new_word,new_value);
    }
}
void deal_line(string& line){
    int define_size = define.size();
    for (int i = 0; i < define_size; ++i) {
        if(define[i][0].find('(') && define[i][0].find(')') && line.find(split(define[i][0],"(")[0] + "(")!= string::npos){
            deal_special_define(line,define[i][0],define[i].size()>1?define[i][1]:"");
        }
    }
}
bool is_define(const string word){
    for (auto &j : define) {
        if (word == j[0]) {
            return true;
        }
    }
    return false;
}
void run_test(int test_case_number) {
    /*获取test1或者test2的代码字符串并分割*/
    string raw_code = get_unprocessed_code(test_case_number);
    vector<string> code = split(raw_code, "\n");
    /*主体*/
    int code_size = code.size();
    for (int i = 0; i < code_size; i++) {
        code[i] = trim(code[i]);
        /*如果本行是空行*/
        if (code[i].empty()) {
            remove(code, i);
            continue;
        }
        /*本行为宏定义*/
        if (code[i].at(0) == '#') {
            /*去除不必要的空格*/
            code[i].at(0) = ' ';
            code[i] = "#" + trim(code[i]);
        }
        cout << code[i] << endl;
        vector<string> word = split(code[i], " ");
        /*define*/
        if (word[0] == "#define" && can_work) {
            for (int j = 3; j < word.size(); ++j) {
                word[2].append(" "+word[j]);
            }
            define_func(word[1],word.size()>2?word[2]:"");
            /*删除define的预定义行*/
            remove(code, i);
        }
        else if (can_conclude(word) && can_work) {
            include(word, code[i]);
        }
        else if (word[0] == "#ifdef" && can_work) {
            remove(code, i);
            can_work = is_define(word[1]);
        }
        else if (word[0] == "#ifndef") {
            can_work = !is_define(word[1]);
        }
        else if (word[0] == "#undef" && can_work) {
            undef(word[1]);
            remove(code, i);
        }
        else if (word[0] == "#if") {
            bool is = is_define(word[1]);
            bool ze = isZero(word[1], define);
            for (int j = 0; j < define.size(); ++j) {
                cout<<define[j][0] << ":" << define[j][1]<<endl;
            }
            can_work = (is && !ze) ||
                       (!is && word[1] != "0");
        }
        else if(code[i] == "#else"){
            can_work = !can_work;
        }
        else if(code[i] == "#endif") {
            remove(code,i);
            can_work = true;
        }
        else if (!can_work) {
            remove(code, i);
        }
        else{
            deal_line(code[i]);
        }

        if(i == 25){
            cout << i<<endl;
        }
    }
    /*对raw_code重新拼接*/
    raw_code = "";
    int length = code.size();
    for (int k = 0; k < length; ++k) {
        if (code[k] == "#include <iostream>") {
            raw_code.append(code[k]).append("\n");
        } else {
            raw_code = code[k] != "" && code[k].at(0) != '#' ? raw_code.append(code[k]).append("\n") : raw_code;
        }
    }
    for (int l = 0; l < define.size(); ++l) {
        string DEF = define[l][0];
        string value = define[l][1];
        while(true){
            string::size_type pos(0);
            if((pos=raw_code.find(DEF))!=string::npos   && (raw_code[pos-1]<64 || raw_code[pos-1]>122 || (raw_code[pos-1]>90&&raw_code[pos-1]<97)))
                raw_code.replace(pos,DEF.size(),value);
            else   break;
        }
    }
    string processed_code = raw_code;
    put_processed_code(test_case_number, processed_code);
}
string get_unprocessed_code(int number) {
    string filename = "test/test" + to_string(number) + ".cpp";
    string file;
    ifstream is(filename);
    if (!is.is_open()) {
        cout << "Broken input file.";
    } else {
        string line;
        while (getline(is, line)) {
            file.append(line).push_back('\n');
        }
        is.close();
    }
    /*返回文件文本字符串*/
    return file;
}
void put_processed_code(int number, string code) {
    string filename = "test/test" + to_string(number) + ".out.cpp";
    ofstream os(filename);
    if (!os.is_open()) {
        cout << "Broken output file.";
    } else {
        /*将代码code输出到out.cpp*/
        os << code;
        os.close();
    }
}

