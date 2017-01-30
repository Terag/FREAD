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

/* 
 * File:   FMap.tpp
 * Author: guillem
 *
 * Created on 28 janvier 2017, 14:56
 */

template<typename K, typename T>
FMap<K, T>::FMap(){
    
}

template<typename K, typename T>
FMap<K, T>::FMap(const FMap& orig){
    std::lock_guard<std::mutex> lock(m_mutex);
    m_unordered_map = orig.getMap();
}

template<typename K, typename T>
FMap<K, T>::~FMap(){
    
}
    
template<typename K, typename T>
std::shared_ptr<T> FMap<K, T>::at(const K& key){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_map.at(key);
}

template<typename K, typename T>
void FMap<K, T>::insert(K key, shared_ptr<T> element){
    std::lock_guard<std::mutex> lock(m_mutex);
    m_unordered_map.insert(key, element);
}

template<typename K, typename T>
bool FMap<K, T>::erase( std::unordered_map<K, T>::iterator it ){
    std::lock_guard<std::mutex> lock(m_mutex);
    if( m_unordered_map.at( it ).use_count() > 1 ){
        m_unordered_map.erase( it );
        return true;
    }
    return false;
}

template<typename K, typename T>
bool FMap<K, T>::contains(T element){
    std::lock_guard<std::mutex> lock(m_mutex);
    for( auto it = m_unordered_map.begin(); it != m_unordered_map.end(); ++it ){
        if( it->second.get() == element ){
            return true;
        }
    }
    return false;
}

template<typename K, typename T>
bool FMap<K, T>::contains(K key){
    std::lock_guard<std::mutex> lock(m_mutex);  
    if( m_unordered_map.at( key ) != NULL ){
        return true;
    }
    return false;
}

template<typename K, typename T>
std::shared_ptr<T> FMap<K, T>::operator[](const K key){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_map[key];
}
    
template<typename K, typename T>
typename std::unordered_map<K, T>::iterator FMap<K, T>::begin(){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_map.begin();
}
    
template<typename K, typename T>
unsigned int FMap<K, T>::size() const{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_map.size();
}

template<typename K, typename T>
bool FMap<K, T>::empty(){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_map.empty();
}

template<typename K, typename T>
std::unordered_map<K, std::shared_ptr<T> > FMap<K, T>::getMap() const{
    return m_unordered_map;
}

template<typename K, typename T>
std::mutex FMap<K, T>::getMutex() const{
    return m_mutex;
}
