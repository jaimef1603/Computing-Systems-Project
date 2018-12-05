
#include "Menu.h"

template <typename T>
Menu<T>::Menu(std::vector<Menu<T>::Menu_option> o, char ec, const std::string menuName, Menu<T>::menu_option_handler init_f, T* if_o)
{
    name=menuName;
    options=o;
    exit_char=ec;
    initial_function = init_f;
    if_object = if_o;
}


template <typename T>
Menu<T>::Menu(std::vector<T> &data, Menu<T>::menu_option_handler execf, char ec,  const std:: string menuName , Menu<T>::menu_option_handler init_f, T* if_o)
{
    int i=0;
    for(typename std::vector<T>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.push_back(Menu<T>::Menu_option('1'+char(i), execf, "option "+std::to_string(i+1), *it));
    }
    name=menuName;
    exit_char=ec;
    initial_function = init_f;
    if_object = if_o;
}



template <typename T>
Menu<T>::Menu(std::vector<T> &data,  Menu<T>::menu_option_handler execf, Menu<T>::menu_option_member option_name, char ec,  const std:: string menuName, Menu<T>::menu_option_handler init_f, T* if_o)

{

    int i=0;
    for(typename std::vector<T>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.push_back(Menu<T>::Menu_option('1'+char(i), execf, (*it).*option_name, *it));
    }
    name=menuName;
    exit_char=ec;
    initial_function = init_f;
    if_object = if_o;
}



template <typename T>
Menu<T>::Menu(std::vector<T> &data, Menu<T>::menu_option_handler execf,  const std:: string menuName, Menu<T>::menu_option_handler init_f, T* if_o)
{
    int i=0;
    for(typename std::vector<T>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.push_back(Menu<T>::Menu_option('1'+char(i), execf, "option "+std::to_string(i+1), *it));
    }
    name=menuName;
    exit_char='q';
    initial_function = init_f;
    if_object = if_o;
}



template <typename T>
Menu<T>::Menu(std::vector<T> &data, Menu<T>::menu_option_handler execf, Menu<T>::menu_option_member option_name, const std:: string menuName, Menu<T>::menu_option_handler init_f, T* if_o){
    int i=0;
    for(typename std::vector<T>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.push_back(Menu<T>::Menu_option('1'+char(i), execf, it->*option_name, *it));
    }
    name=menuName;
    exit_char='q';
    initial_function = init_f;
    if_object = if_o;
}



template <typename T>
Menu<T>:: Menu(std::vector<T> &data, Menu<T>::menu_option_member option_name, char ec,  Menu<T>::menu_option_handler init_f, T* if_o)
{

    for(unsigned i=0; i<data.size();  i++ ){
        options.push_back(Menu<T>::Menu_option('1'+char(i), nullptr, data[i].*option_name, data[i]));
    }
    name=std::string();
    exit_char=ec;
    initial_function = init_f;
    if_object = if_o;
}




template <typename T>
Menu<T>::Menu(std::vector<T*> &data, Menu<T>::menu_option_handler execf, char ec,  const std:: string menuName , Menu<T>::menu_option_handler init_f, T* if_o)
{
    int i=0;
    for(typename std::vector<T*>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.push_back(Menu<T>::Menu_option('1'+char(i), execf, "option "+std::to_string(i+1), *it));
    }
    name=menuName;
    exit_char=ec;
    initial_function = init_f;
    if_object = if_o;
}



template <typename T>
Menu<T>::Menu(std::vector<T*> &data,  Menu<T>::menu_option_handler execf, Menu<T>::menu_option_member option_name, char ec,  const std:: string menuName, Menu<T>::menu_option_handler init_f, T* if_o)

{

    int i=0;
    for(typename std::vector<T*>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.push_back(Menu<T>::Menu_option('1'+char(i), execf, (*it)->*option_name, *it));
    }
    name=menuName;
    exit_char=ec;
    initial_function = init_f;
    if_object = if_o;
}



template <typename T>
Menu<T>::Menu(std::vector<T*> &data, Menu<T>::menu_option_handler execf,  const std:: string menuName, Menu<T>::menu_option_handler init_f, T* if_o)
{
    int i=0;
    for(typename std::vector<T*>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.push_back(Menu<T>::Menu_option('1'+char(i), execf, "option "+std::to_string(i+1), *it));
    }
    name=menuName;
    exit_char='q';
    initial_function = init_f;
    if_object = if_o;
}



template <typename T>
Menu<T>::Menu(std::vector<T*> &data, Menu<T>::menu_option_handler execf, Menu<T>::menu_option_member option_name, const std:: string menuName, Menu<T>::menu_option_handler init_f, T* if_o){
    int i=0;
    for(typename std::vector<T*>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.push_back(Menu<T>::Menu_option('1'+char(i), execf, (*it).*option_name, *it));
    }
    name=menuName;
    exit_char='q';
    initial_function = init_f;
    if_object = if_o;
}



template <typename T>
Menu<T>:: Menu(std::vector<T*> &data, Menu<T>::menu_option_member option_name, char ec,  Menu<T>::menu_option_handler init_f, T* if_o)
{

    for(unsigned i=0; i<data.size();  i++ ){
        options.push_back(Menu<T>::Menu_option('1'+char(i), nullptr, data[i]->*option_name, data[i]));
    }
    name=std::string();
    exit_char=ec;
    initial_function = init_f;
    if_object = if_o;
}






template <typename T>
void Menu<T>::display(bool showErrorMsg)
{
    if (!name.empty())
        std::cout<<name<<std::endl;

    if(initial_function){
        (if_object->*initial_function)();
    }

    if(showErrorMsg)
        std::cout<<"Select a valid option"<<std::endl;

    for(unsigned i=0; i<options.size(); i++){
        std::cout<<"\t"<<options[i].option<<": "<<options[i].text<<std::endl;
    }
    std::cout<<"\t"<<exit_char<<" :"<<"Back"<<std::endl;
}



template <typename T>
bool Menu<T>::ask()
{
    std::cin>>std::ws>>selection;
    return selection==exit_char? false:true;
}



template <typename T>
bool Menu<T>::evaluate_options()
{
    for (unsigned i=0; i<options.size(); i++){
        if(options[i].is_selected(selection)){
            return true;
        }
    }
    return false;
}



template <typename T>
T* Menu<T>::evaluate_selection()
{
    for (unsigned i=0; i<options.size(); i++){
        if(options[i].is_selected(selection)){
           return options[i].object;
        }
    }
    return nullptr;
}


template <typename T>
void Menu<T>::run()
{
    system("clear");
    display(false);
    while (ask()) {
        system("clear");
        display(!evaluate_options());
    }
}



template<typename T>
T* Menu<T>::run_selector()
{
    T *temp=nullptr;
    system("clear");
    display(false);
    while(ask() && temp==nullptr){
        system("clear");
        if ((temp = evaluate_selection())){
            return temp;
        }
        display(temp==nullptr);
    }
    return temp;
}


template <typename T>
Menu<T>::Menu_option::Menu_option(char opt, Menu<T>::menu_option_handler moh, const std::string t, T* obj)
{
    object=obj;
    function=moh;
    option=opt;
    text=t;
}


template <typename T>
Menu<T>::Menu_option::Menu_option(char opt, Menu<T>::menu_option_handler moh, const std::string t, T& obj)
{
    object=&obj;
    function=moh;
    option=opt;
    text=t;
}



template <typename T>
bool Menu<T>::Menu_option::is_selected(int opt)
{
    if (option == opt){
        if( function){
            (object->*function)();
        }
        system("clear");
        return true;
    }
    return false;
}
