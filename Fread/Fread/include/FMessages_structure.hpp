/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FMessages_structure.hpp
 * Author: guillem
 *
 * Created on 24 janvier 2017, 17:02
 */

#ifndef FMESSAGES_STRUCTURE_HPP
#define FMESSAGES_STRUCTURE_HPP

enum HEADER{
     START,
     INITDONE,
     TIMESTAMP,
     INITDONE,
     CONTAINER,
     PATTERN,
     OCCURRENCE
};

struct msg_parser{
    HEADER header;
    std::shared_ptr<> content;
};

struct msg_renderer{
    HEADER header;
    std::shared_ptr<> content;
};

#endif /* FMESSAGES_STRUCTURE_HPP */

