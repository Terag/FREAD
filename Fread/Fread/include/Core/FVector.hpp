/*
Boost Software License - Version 1.0 - August 17th, 2003
 * Modified by Victor Rouquette - January 2017

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
 */


#ifndef FVECTOR_HPP
#define FVECTOR_HPP

#include <vector>
#include <memory>

template<typename T> class FVector;

template<typename T>
class FVector {
public:
    FVector();
    FVector(const FVector& orig);
    ~FVector();
    
    std::shared_ptr<T> at(const int& index);
    void insert(int index, std::shared_ptr<T> element);
    bool erase( typename std::vector<T>::iterator it);
    
    bool contains(T element);
    
    std::shared_ptr<T> operator[](const int index);
    
    typename std::vector<T>::iterator begin();
    
    unsigned int size() const;
    bool empty();
    
    std::vector<std::shared_ptr<T> > getVector() const;
    std::mutex getMutex() const;

    void operator()(const FVector<T>&) const;
    
private:
    std::vector< std::shared_ptr<T> > m_vector;
    std::mutex m_mutex; 
};

#include "../../src/Core/FVector.tpp"

#endif /* FVECTOR_HPP */
