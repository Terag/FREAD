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

struct s_occurrences{
    int id;
    
    void operator=(s_occurrences other){
        id = other.id;
    }
    
    bool operator==(s_occurrences other){
        return (id == other.id);
    }
    
    bool operator!=(s_occurrences other){
        return ( id!=other.id );
    }
};

struct s_threads{
    int id;
    
    void operator=(s_threads other){
        id = other.id;
    }
    
    bool operator==(s_threads other){
        return (id == other.id);
    }
    
    bool operator!=(s_threads other){
        return ( id != other.id );
    }
};

struct s_display2occurrences{
    s_occurrences occ;
    
    void operator=(s_display2occurrences other){
        occ = other.occ;
    }
    
    bool operator==(s_display2occurrences other){
        return (occ == other.occ);
    }
    
    bool operator!=(s_display2occurrences other){
        return ( occ != other.occ );
    }
    
};

struct s_display2threads{
    s_threads thr;
    
    void operator=(s_display2threads other){
        thr = other.thr;
    }
    
    bool operator==(s_display2threads other){
        return (thr == other.thr);
    }
    
    bool operator!=(s_display2threads other){
        return ( thr != other.thr );
    }
};

struct s_parser2occurrences{
    s_occurrences occ;
    
    void operator=(s_parser2occurrences other){
        occ = other.occ;
    }
    
    bool operator==(s_parser2occurrences other){
        return (occ == other.occ);
    }
    
    bool operator!=(s_parser2occurrences other){
        return ( occ != other.occ );
    }
};

struct s_parser2threads{
    s_threads thr;
    
    void operator=(s_parser2threads other){
        thr = other.thr;
    }
    
    bool operator==(s_parser2threads other){
        return (thr == other.thr);
    }
    
    bool operator!=(s_parser2threads other){
        return ( thr != other.thr );
    }
};

struct s_core2display{
    s_occurrences occ;
    s_threads thr;
    
};

struct s_core2parser{
    s_occurrences occ;
    s_threads thr;
};

#endif /* STRUCTURES_H */

