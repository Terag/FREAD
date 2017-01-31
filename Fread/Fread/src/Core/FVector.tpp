    template<typedef T>
    FVector<T>::FVector(){

    }


    template<typedef T>
    FVector<T>::FVector(const FVector& orig){

    }


    template<typedef T>
    FVector<T>::~FVector(){

    }


    
    template<typedef T>
    std::shared_ptr<T> FVector<T>::at(const int& index){
        return m_vector.at(index);
    }


    template<typedef T>
    void FVector<T>::insert(int index, std::shared_ptr<T> element){

    }


    template<typedef T>
    void FVector<T>::push_back(std::shared_ptr<T> element){
        m_vector.push_back(element);
    }


    template<typedef T>
    bool FVector<T>::erase( typename std::vector<T>::iterator it){

    }


    
    template<typedef T>
    bool FVector<T>::contains(T element){

    }


    
    template<typedef T>
    std::shared_ptr<T> FVector<T>::operator[](const int index){

    }


    
    template<typedef T>
    typename std::vector<T>::iterator FVector<T>::begin(){

    }


    
    template<typedef T>
    unsigned int FVector<T>::size() const{

    }


    template<typedef T>
    bool FVector<T>::empty(){

    }


    
    template<typedef T>
    std::vector<std::shared_ptr<T> > FVector<T>::getVector() const{

    }


    template<typedef T>
    std::mutex FVector<T>::getMutex() const{

    }



    template<typedef T>
    void FVector<T>::operator()(const FVector<T>&) const{

    }

