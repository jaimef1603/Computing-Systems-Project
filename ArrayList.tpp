




//------------CONSTRUCTORS------------------------
template <typename A>
ArrayList<A>::ArrayList()
    :vector<A>()

{


}


template <typename A>
ArrayList<A>::ArrayList(const A &a)
    :vector<A>(a) {

}



template <typename A>
ArrayList<A>::ArrayList(const A&& a)
    :vector<A>(a)
{

}


template <typename A>
ArrayList<A>::ArrayList(size_t _n, const A& a)
    :vector<A>(_n, a)
{

}



template <typename A>
ArrayList<A>::ArrayList(const vector<A> &a)
    :vector<A> (a)
{

}



template <typename A>
ArrayList<A>::ArrayList(const vector<A> && a)
    :vector<A>(a)
{

}



//-------------------------------------------------

template <typename A>
void ArrayList<A>::pushFront(const A& a)
{

    this->push_back(a);

}



template <typename A>
void ArrayList<A>::pushFront(const A&& a)
{

    this->push_back(a);

}



template <typename A>
void ArrayList<A>::pushBack(const A& a)
{

    this->insert(this->begin(), a);

}



template <typename A>
void ArrayList<A>::pushBack(const A&& a)
{

    this->insert(this->begin(), a);

}



template <typename A>
bool ArrayList<A>::remove(const A& a)
{

    for ( typename vector<A>::iterator it= this->begin(); it!=this->end(); it++){
        if ((*it) == a){
            this->erase(it);
            return true;
        }
    }

        return false;

}



template <typename A>
bool ArrayList<A>::removeByIndex(unsigned index)
{

    if (index< this->size()){
        this->erase(this->begin()+index);
        return true;
    }  else{
        return false;
    }
}



//template <typename A>
//A& ArrayList<A>::operator[](unsigned index)
//{

// return this[index];

//}



template <typename A>
ArrayList<A>& ArrayList<A>::operator = ( const ArrayList<A>& a)
{
    this->vector<A>:: operator=(a);
    return *this;
}



template <typename A>
ArrayList<A>& ArrayList<A>::operator = ( const ArrayList<A>&& a)
{
    this->vector<A>:: operator=(a);
    return *this;
}



template <typename A>
ArrayList<A>& ArrayList<A>::operator = ( const vector<A>& a)
{
    this->vector<A>:: operator=(a);
    return *this;
}



template <typename A>
ArrayList<A>& ArrayList<A>::operator = ( const vector<A>&& a)
{
    this->vector<A>:: operator=(a);
    return *this;
}



template <typename A>
vector <A>& ArrayList<A>::to_vector()
{
    return *this;
}






