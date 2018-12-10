
#include "Menu.h"
#include <sstream>
#include <limits>


template <typename T>
Menu<T>::Menu(std::vector<Menu<T>::Menu_option>& o, const std::string menuName, Menu<T>::menu_option_handler init_f, T* if_o)
    :name(menuName), options (o)

{

    initial_function = init_f;
    if_object = if_o;
    settings = DEFAULT_CONFIG;
}


template <typename T>
Menu<T>::Menu(std::vector<T> &data, Menu<T>::menu_option_handler execf,  const std:: string menuName , Menu<T>::menu_option_handler init_f, T* if_o)
    :name(menuName)
{
    int i=1;
    options.reserve(data.size());
    for(typename std::vector<T>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.emplace_back(i, execf, "option "+std::to_string(i+1), *it);
    }
    initial_function = init_f;
    if_object = if_o;
    settings = DEFAULT_CONFIG;
}



template <typename T>
Menu<T>::Menu(std::vector<T> &data,  Menu<T>::menu_option_handler execf, Menu<T>::menu_option_member option_name,  const std:: string menuName, Menu<T>::menu_option_handler init_f, T* if_o)
    :name(menuName)
{

    int i=1;
    options.reserve(data.size());
    for(typename std::vector<T>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.emplace_back(i, execf, (*it).*option_name, *it);
    }
    initial_function = init_f;
    if_object = if_o;
    settings = DEFAULT_CONFIG;
}



template <typename T>
Menu<T>:: Menu(std::vector<T> &data, Menu<T>::menu_option_member option_name,  Menu<T>::menu_option_handler init_f, T* if_o)
    :name()
{
    options.reserve(data.size());
    for(unsigned i=0; i<data.size();  i++ ){
        options.emplace_back(1+i, nullptr, data[i].*option_name, data[i]);
    }
    initial_function = init_f;
    if_object = if_o;
    settings = DEFAULT_CONFIG;
}




template <typename T>
Menu<T>::Menu(std::vector<T*> &data, Menu<T>::menu_option_handler execf,  const std:: string menuName , Menu<T>::menu_option_handler init_f, T* if_o)
    :name(menuName)
{
    int i=1;
    options.reserve(data.size());
    for(typename std::vector<T*>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.emplace_back(i, execf, "option "+std::to_string(i+1), *it);
    }
    initial_function = init_f;
    if_object = if_o;
    settings = DEFAULT_CONFIG;
}



template <typename T>
Menu<T>::Menu(std::vector<T*> &data,  Menu<T>::menu_option_handler execf, Menu<T>::menu_option_member option_name,  const std:: string menuName, Menu<T>::menu_option_handler init_f, T* if_o)
    :name(menuName)
{

    int i=1;
    options.reserve(data.size());
    for(typename std::vector<T*>::iterator it = data.begin(); it!=data.end(); it++, i++ ){
        options.emplace_back(i, execf, (*it)->*option_name, *it);
    }
    initial_function = init_f;
    if_object = if_o;
    settings = DEFAULT_CONFIG;
}



template <typename T>
Menu<T>:: Menu(std::vector<T*> &data, Menu<T>::menu_option_member option_name, std::string selectorName,  Menu<T>::menu_option_handler init_f, T* if_o)
    :name(selectorName)
{

    options.reserve(data.size());
    for(unsigned i=0; i<data.size();  i++ ){
        options.emplace_back(1+i, nullptr, data[i]->*option_name, data[i]);
    }
    initial_function = init_f;
    if_object = if_o;
    settings = DEFAULT_CONFIG;
}



template <typename T>
void Menu<T>::display(bool showErrorMsg)
{
    if (!name.empty())
        std::cout<<name<<std::endl;
    if (initial_function)
        (if_object->*initial_function)();

    if(showErrorMsg)
        std::cout<<settings.error_msg<<std::endl;

    if (settings.orientation == menu_config::vertical){
        for(unsigned i=0; i<options.size(); i++){
            std::cout<<"\t"<<settings.left_decoration
                    <<options[i].option<<settings.right_decoration
                   <<" "<<options[i].text<<std::endl;
            for (unsigned j=0; j<settings.line_spaces; j++){
                  std::cout<<"\n";
            }
        }
        std::cout<<"\t\'"<<settings.exit_char<<"\' "<<"Back"<<std::endl;

    }else{
        for(unsigned i=0; i<options.size(); i++){
            std::cout<<settings.left_decoration
                    <<options[i].option<<settings.right_decoration
                   <<options[i].text;
            for (unsigned j=0; j<settings.line_spaces; j++){
                  std::cout<<" ";
            }
        }
        std::cout<<"\t\'"<<settings.exit_char<<"\'"<<"Back"<<std::endl;
    }



}



template <typename T>
bool Menu<T>::ask()     //Waits for the user to insert an option which should be an unsigned or the exit char.
{
    std::string buffer;
    if (!std::cin.good()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<char>::max(), '\n');
    }
    std::cin>>std::ws>>buffer;
    char exit_str [2] = {settings.exit_char, '\0'};
    if (buffer == exit_str){
        return false;
    }else{
        std::istringstream(buffer)>>selection;
        if (std::cin.good()){
            return true;
        }
        selection = -1; // if the user selection is not valid (in format) selection is transformed to -1
        return true;    //but we return true because the insertion was not the exit character.
    }

}



template <typename T>
bool Menu<T>::evaluate_options()                    //  If the selection introduced was valid (whenever it
{                                                   //  is invalid it is transformed to -1) this function
    if (selection != -1){                           //  iterates through the option vector and if none of
        for (unsigned i=0; i<options.size(); i++){  //  them returns true it returns nullptr.
            if(options[i].is_selected(selection)){  //  Otherwise it returns true.
                if (settings.hold){
                    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                    std::cin.get();
                }
                system("clear");
                return true;
            }
        }
    }
    return false;
}



template <typename T>
T* Menu<T>::evaluate_selection()
{                                                       //  If the selection introduced was valid (whenever it
    if (selection != -1){                               //  is invalid it is transformed to -1) this function
        for (unsigned i=0; i<options.size(); i++){      //  iterates through the option vector and if none of
            if(options[i].is_selected(selection)){      //  them returns something different from nullptr it
                return options[i].object;               //  returns nullptr. Otherwise it returns the object
            }                                           //  of the first option that returned non-null in
        }                                               //  evaluate selection
    }
    return nullptr;
}


template <typename T>
void Menu<T>::run()
{
    system("clear");                    //Runs display and keeps running it while ask does not return
    display(false);                     // false (the exit character was inserted)
    while (ask()) {
        system("clear");
        display(!evaluate_options());   //we pass true if no correct option was selected in order to display
    }                                   //the error message
}



template<typename T>
T* Menu<T>::run_selector()
{
    T *temp=nullptr;
    system("clear");
    display(false);                         // runs display while ask does not return false (exit char was
    while(ask() && temp==nullptr){          // inserted) or evaluate_selector returns nullptr (no valid
        system("clear");                    // selection was introduced)
        if ((temp = evaluate_selection())){
            return temp;                    // if evaluate selector returns anything different from nullptr
        }                                   // a valid chose was made so we return it
        display(temp==nullptr);             // We tell display to show the error message whenever the selection
    }                                       // was invalid
    return temp;
}


template <typename T>
void Menu<T>::set_settings(menu_config& newConfig)
{
    settings = newConfig;
}



template <typename T>
void Menu<T>::set_settings(menu_config &&newConfig)
{
    settings = newConfig;
}



template <typename T>
void Menu<T>::show_settings()
{
    std::cout<<"Exit char: "<<settings.exit_char<<std::endl
             <<"Orientation: "
             <<(settings.orientation == menu_config::horizontal ? "horizontal":"vertical")<<std::endl
             << "Spaces between options: "<<settings.line_spaces<<std::endl
             << "Error message: "<<settings.error_msg<<std::endl
             << "Left Decoration: "<<settings.left_decoration<<std::endl
             << "Right Decorations: "<<settings.right_decoration<<std::endl;
}

//---------TWO SIMILAR CONSTRUCTORS FOR MENU_OPTION-----------


// [1]
template <typename T>
Menu<T>::Menu_option::Menu_option(unsigned opt, Menu<T>::menu_option_handler moh, const std::string t, T* obj)
{
    object=obj;
    function=moh;
    option=opt;
    text=t;
}


// [2]

template <typename T>
Menu<T>::Menu_option::Menu_option(unsigned opt, Menu<T>::menu_option_handler moh, const std::string t, T& obj)
{
    object=&obj;
    function=moh;
    option=opt;
    text=t;
}



template <typename T>
bool Menu<T>::Menu_option::is_selected(unsigned opt)

{
    if (option == opt){                 //evaluates if the option of this Menu_option is the one selected
        if( function){                  //(passed as parameter) and if true returns true. Also calls this
            (object->*function)();      //option's function if any.
        }
        return true;
    }
    return false;
}
