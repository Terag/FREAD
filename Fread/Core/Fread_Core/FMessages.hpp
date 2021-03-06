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
 * File:   FMessages.hpp
 * Author: guillem
 *
 * Created on 25 janvier 2017, 16:05
 */

#ifndef FMESSAGES_HPP
#define FMESSAGES_HPP

#include <memory>

enum HEADER{
     START,
     INITDONE,
     TIMESTAMP,
     CONTAINER,
     PATTERN,
     OCCURRENCE
};

template<typename T>
class FMessages{
public:
    
    //give a content to the constructor it will make a shared_ptr of it
    FMessages(HEADER header, T content);
    FMessages(const FMessages& orig);
    
    FMessages& operator=(const FMessages&);
    
    virtual ~FMessages();
    
    HEADER getHeader();
    void setHeader(HEADER var);
    
    std::shared_ptr<T> getContent();
    void setContent(T var);
    
private:
    HEADER m_header;
    std::shared_ptr<T> m_content;
};

#endif //FMESSAGES_HPP

