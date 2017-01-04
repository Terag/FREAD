/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   structures.h
 * Author: guillem
 *
 * Created on 18 décembre 2016, 02:35
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

enum message_type{
    OCCURRENCE,
    THREAD
};

struct s_display2core{
    message_type type;
};

struct s_parser2core{
    message_type type;
};

struct s_occurrences{
    
};

struct s_threads{
    
};

#endif /* STRUCTURES_H */

