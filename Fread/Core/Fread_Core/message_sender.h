/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   message_sender.h
 * Author: guillem
 *
 * Created on 19 décembre 2016, 15:39
 */

#ifndef MESSAGE_SENDER_H
#define MESSAGE_SENDER_H

class message_sender {
public:
    message_sender();
    message_sender(const message_sender& orig);
    virtual ~message_sender();
    
    void data_sending();
private:

};

#endif /* MESSAGE_SENDER_H */

