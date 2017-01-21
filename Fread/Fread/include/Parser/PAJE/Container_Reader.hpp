/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Container_Reader.hpp
 * Author: terag
 *
 * Created on December 19, 2016, 8:53 PM
 */

#ifndef CONTAINER_READER_HPP
#define CONTAINER_READER_HPP

#include <string>
#include <iostream>
#include <fstream>

namespace paje
{
    class Container_Reader {
    public:

        Container_Reader();
        void init(std::string const& path);
        
        Container_Reader(const Container_Reader& orig);

        virtual ~Container_Reader();

    private:
        
        std::string container_Path;
        std::ifstream container_Stream;

    };
}

#endif /* CONTAINER_READER_HPP */

