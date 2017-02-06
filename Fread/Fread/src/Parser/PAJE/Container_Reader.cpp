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
    Container_Reader::Container_Reader(std::string const& c_alias, int c_id) :
        id(c_id), alias(c_alias), timestamps_begin_end(-1.f, -1.f), readyToRead(false)
    {
    }
    
    void Container_Reader::init(const std::string& path, int const& c_id) {
        container_Path = path;
        id = c_id;
        curseur_line = -1;
        //container_Stream.open(container_Path);
    }  
    
    void Container_Reader::checkIfReady() {
        if(id > -1 &&
           timestamps_begin_end.first > -1.f &&
           timestamps_begin_end.second > 1.f &&
           alias != "") 
        {
            readyToRead = true;
        }
    }
    
    vector<string> Container_Reader::getLinesBetweenTwoTimes(const float& t1, const float& t2) {
        vector<string> lines;
        string line;
        float time;
        int line_number;
        if(curseur_line < 0) {
            container_Stream.open(container_Path);
            curseur_line = 0;
            getline(container_Stream, line);
            line_number++;
            time = lineTime(line);
        } else {
            line_number = curseur_line;
            getline(container_Stream, line);
            line_number++;
            time = lineTime(line);
            if(time > t2) {
                container_Stream.close();
                container_Stream.open(container_Path);
                curseur_line = 0;
            }
        }
        do {
            if(time > t2) {
                break;
            }
            if(time >= t1 && time <= t2) {
                lines.push_back(line);
            }
            getline(container_Stream, line);
            line_number++;
            time = lineTime(line);
        } while(!container_Stream.eof());
       
        curseur_line = line_number;
        return lines;
    }
    
    float Container_Reader::lineTime(const string& line) {
            auto firstSpace = line.find(' ');
            auto secondSpace = line.find(' ', firstSpace+1);
            float time = stof(line.substr(firstSpace, secondSpace));
            return time;
    }

    
    Container_Reader::~Container_Reader() {
    }
}
