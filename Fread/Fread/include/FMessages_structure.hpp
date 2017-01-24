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

#include <string>
#include <memory>

typedef enum {
     H_START,
     H_INITDONE,
     H_TIMESTAMP,
     H_CONTAINER,
     H_PATTERN,
     H_OCCURRENCE
} HEADER;

typedef struct {
    HEADER header;
    std::shared_ptr<std::string> content;
} msg_parserToCore;

typedef struct {
    HEADER header;
    std::shared_ptr<std::string> content;
} msg_rendererToCore;

typedef struct {
    HEADER header;
    std::shared_ptr<std::string> content;
} msg_coreToParser;

#endif /* FMESSAGES_STRUCTURE_HPP */

