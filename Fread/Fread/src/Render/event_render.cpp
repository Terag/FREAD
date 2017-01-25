/*
 * Copyright (c) 2017, FREAD - Jérôme Berthelin, Emma Goldblum, Maxime Guillem, Victor Rouquette
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of the copyright holders nor the names of its contributors 
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* 
 * File:   event_render.cpp
 * Author: gg
 * 
 * Created on 24 janvier 2017, 15:47
 */
#include "Render/event_render.hpp"
#include <cmath>
#include <stdio.h>

using namespace std;
using namespace sf;

event_render::event_render() :
type(NULL)
{}

event_render::event_render(float tSStart, float tSEnd, eventType type) :
type(type)
{
    tStart = (int)(container_render.getScale()*tSStart);
    tEnd = (int)(container_render.getScale()*tSEnd);
    setColor();
}

event_render::setColor() {
        switch(type) {
            
            case(WAIT): 
            {
                eventColor = sf::Color(246,56,58);
                break;
            }
            case(COMPUTE): 
            {
                eventColor = sf::Color(0,200,225);
                break;
            }
            case(SEND):
            {
                eventColor = sf::Color(132,0,166);
                break;
            }
        }
    }   

event_render::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const 
{
    int size = (tEnd - tStart);
    RectangleShape rectangle(Vector2f(size, 10));
    rectangle.setFillColor(eventColor);
    rectangle.setPosition(tStart,container_render.getId()*container_render.getOffsetY());
    target.draw(rectangle, states);
}

event_render::~event_render() 
{
}
    
