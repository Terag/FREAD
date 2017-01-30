/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Container_Reader.cpp
 * Author: terag
 * 
 * Created on December 19, 2016, 8:53 PM
 */

#include "Parser/PAJE/Container_Reader.hpp"
#include "FContainer.hpp"
#include "Parser/PAJE/paje_interface.hpp"

using namespace std;

namespace paje
{
    Container_Reader::Container_Reader(std::string const& c_alias) :
        id(-1), alias(c_alias), timestamps_begin_end(-1.f, -1.f), readyToRead(false)
    {
    }
    
    void Container_Reader::init(const std::string& path, int const& c_id) {
        container_Path = path;
        id = c_id;
    }
    
    FContainer Container_Reader::start() {
        
        readyToRead = true;
        //vector<int> listeId;
        //listeId.push_back(1);
        return FContainer(-1, "pouet");
    }    
    
    void Container_Reader::checkIfReady() {
        if(id > -1 ||
           alias != "") 
        {
            readyToRead = true;
        }
    }
    
    vector<string> Container_Reader::getLinesBetweenTwoTimes(const float& t1, const float& t2) {
        vector<string> null;
        return null;
    }

    Container_Reader::~Container_Reader() {
    }
}
