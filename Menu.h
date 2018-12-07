#ifndef MENU_H
#define MENU_H
#include <vector>
#include <string>
#include <iostream>


template <typename T>
class Menu
{

public:
    typedef void (T::*menu_option_handler)(void);
    typedef std::string   T:: *menu_option_member;

    class Menu_option;

    Menu(std::vector<Menu<T>::Menu_option> o, char ec='q', const std::string menuName= std::string(), Menu<T>::menu_option_handler init_f=nullptr, T* if_o = nullptr);

    Menu(std::vector<T> &data, Menu<T>::menu_option_handler execf, char ec='q',  const std:: string menuName= std::string(), Menu<T>::menu_option_handler init_f = nullptr, T* if_o = nullptr);

    Menu(std::vector<T> &data,  Menu<T>::menu_option_handler execf, Menu<T>::menu_option_member, char ec='q',  const std:: string menuName= std::string(), Menu<T>::menu_option_handler init_f = nullptr, T* if_o = nullptr);

    Menu(std::vector<T> &data, Menu<T>::menu_option_handler execf,  const std:: string menuName, Menu<T>::menu_option_handler init_f = nullptr, T* if_o = nullptr);

    Menu(std::vector<T> &data, Menu<T>::menu_option_handler execf, Menu<T>::menu_option_member, const std:: string menuName, Menu<T>::menu_option_handler init_f = nullptr, T* if_o = nullptr);

    Menu(std::vector<T> &data, Menu<T>::menu_option_member option_name, char ec='q',  Menu<T>::menu_option_handler init_f = nullptr, T* if_o = nullptr);

    Menu(std::vector<T*> &data, Menu<T>::menu_option_handler execf, char ec='q',  const std:: string menuName= std::string(), Menu<T>::menu_option_handler init_f = nullptr, T* if_o = nullptr);

    Menu(std::vector<T*> &data,  Menu<T>::menu_option_handler execf, Menu<T>::menu_option_member, char ec='q',  const std:: string menuName= std::string(), Menu<T>::menu_option_handler init_f = nullptr, T* if_o = nullptr);

    Menu(std::vector<T*> &data, Menu<T>::menu_option_handler execf,  const std:: string menuName, Menu<T>::menu_option_handler init_f = nullptr, T* if_o = nullptr);

    Menu(std::vector<T*> &data, Menu<T>::menu_option_handler execf, Menu<T>::menu_option_member, const std:: string menuName, Menu<T>::menu_option_handler init_f = nullptr, T* if_o = nullptr);

    Menu(std::vector<T*> &data, Menu<T>::menu_option_member option_name, std::string selectorName= std::string (), char ec='q',  Menu<T>::menu_option_handler init_f = nullptr, T* if_o = nullptr);



    T* run_selector();
    void run();


private:
    void display(bool showErrorMsg);
    bool ask();

    T* evaluate_selection();
    bool evaluate_options();
    std::string name;
    Menu<T>::menu_option_handler initial_function;
    T* if_object;
    std::vector <Menu<T>::Menu_option> options;
    char exit_char;
    int selection;


};

template <typename T>
class Menu<T>::Menu_option{

public:
    friend class Menu<T>;

    Menu_option(unsigned opt, Menu<T>::menu_option_handler moh,  const std::string t=nullptr, T* obj=nullptr);
    Menu_option(unsigned opt, Menu<T>::menu_option_handler moh,  const std::string t=nullptr, T& obj = T());
    bool is_selected(unsigned opt);



private:
    unsigned option;
    std::string text;
    T *object;
    Menu<T>::menu_option_handler function;


};




#include  "Menu.tpp"


#endif // MENU_H
