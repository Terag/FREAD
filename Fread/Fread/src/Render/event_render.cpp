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
 * Author: Emma et Jerome 
 * 
 * Created on 24 janvier 2017, 15:47
 */
#include "Render/event_render.hpp"

using namespace std;
using namespace sf;

event_render::event_render() :
type(WAIT)
{}

event_render::event_render(eventType type, float tSStart, float tSEnd,
                           float scale, int containerOffsetY, int containerID, 
                           int offsetY, int containerOffsetX, int windowContainerOffsetY) :
type(type), ftStart(tSStart), ftEnd(tSEnd), containerOffsetY(containerOffsetY), containerID(containerID), offsetY(offsetY), offsetX(containerOffsetX), windowContainerOffsetY(windowContainerOffsetY)
{
    int tStart = (int)(scale*tSStart);
    int tEnd = (int)(scale*tSEnd);
    setColor();
    rectangles[0].position = sf::Vector2f(tStart + offsetX,windowContainerOffsetY + containerID*containerOffsetY +offsetY);
    rectangles[1].position = sf::Vector2f(tStart + offsetX,windowContainerOffsetY + containerID*containerOffsetY -offsetY);
    rectangles[2].position = sf::Vector2f(tEnd + offsetX,windowContainerOffsetY + containerID*containerOffsetY -offsetY);
    rectangles[3].position = sf::Vector2f(tEnd + offsetX,windowContainerOffsetY + containerID*containerOffsetY + offsetY);
    for (int i = 0; i < 4; i++) {
        rectangles[i].color = eventColor;
    }
}

event_render::~event_render() 
{
}

void event_render::updatePosition(int newScale, int containerOffsetY, int offsetX, int offsetY)
{
    int tStart = (int)(newScale*ftStart);
    int tEnd = (int)(newScale*ftEnd);
    setColor();
    rectangles[0].position = sf::Vector2f(tStart + offsetX,windowContainerOffsetY + containerID*containerOffsetY +offsetY);
    rectangles[1].position = sf::Vector2f(tStart + offsetX,windowContainerOffsetY + containerID*containerOffsetY -offsetY);
    rectangles[2].position = sf::Vector2f(tEnd + offsetX,windowContainerOffsetY + containerID*containerOffsetY -offsetY);
    rectangles[3].position = sf::Vector2f(tEnd + offsetX,windowContainerOffsetY + containerID*containerOffsetY + offsetY);
}
void event_render::setColor() 
{
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

eventType event_render::getType() 
{
    return type;
}
sf::Color event_render::getColor() 
{
    return eventColor;
}

void event_render::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(rectangles, states);
}
