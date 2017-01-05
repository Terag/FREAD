/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   paje_namespace.hpp
 * Author: terag
 *
 * Created on December 19, 2016, 6:55 PM
 */

#ifndef PAJE_NAMESPACE_HPP
#define PAJE_NAMESPACE_HPP

#include <string>

#include "Parser/PAJE/paje_typedefs.hpp"

namespace paje
{
    void awake(std::string const& path);
    void start();
    
    void PajeEventCall(std::string line, EventDef &event);
}


#endif /* PAJE_NAMESPACE_HPP */

