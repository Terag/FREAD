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

#include "Render/container_render.hpp"

scale::scale()
{
}

scale::scale(float absoluteTime, int nbContainer, int containerSize, int windowContainerOffsetY):
absoluteTime(absoluteTime), containerSize(containerSize), windowContainerOffsetY(windowContainerOffsetY)
{
    int subdTimeLine = containerSize/spacing;
    constScale = containerSize/absoluteTime;
    if (!font.loadFromFile("Arimo-Regular.ttf")) 
    {
        // error
    }
    for (int i = 0; i < subdTimeLine + 1; i++) 
    {
    sf::Text time;
    time.setFont(font);
    time.setFillColor(sf::Color(60,60,60));
    time.setCharacterSize(10);
    time.setString(std::to_string(spacing*i/constScale));
    time.setPosition(containerOffsetX + spacing*(i), containerOffsetY - eventOffsetY - 15);
    times.push_back(time);
    sf::VertexArray timeLine = sf::VertexArray(sf::Lines, 2);
    timeLine[0].position = sf::Vector2f(containerOffsetX + spacing*(i), containerOffsetY - eventOffsetY); 
    timeLine[1].position = sf::Vector2f(containerOffsetX + spacing*(i), containerOffsetY*nbContainer + eventOffsetY);
    timeLine[0].color = sf::Color(231,231,231);
    timeLine[1].color = sf::Color(231,231,231); 
    timeLines.push_back(timeLine);
    }
}

scale::scale(float absoluteTime, int nbContainer, int containerSize,
             int spacing, int containerOffsetX, int containerOffsetY,
             int eventOffsetY, int windowContainerOffsetY) : 
            absoluteTime(absoluteTime), containerSize(containerSize), spacing(spacing),
            containerOffsetX(containerOffsetX), containerOffsetY(containerOffsetY),
            eventOffsetY(eventOffsetY), windowContainerOffsetY(windowContainerOffsetY)
{   
    subdTimeLine = containerSize/spacing;
    constScale = containerSize/absoluteTime;
    if (!font.loadFromFile("Arimo-Regular.ttf")) 
    {
        // error
    }
    for (int i = 0; i < subdTimeLine + 1; i++) 
    {
    sf::Text time;
    time.setFont(font);
    time.setFillColor(sf::Color(60,60,60));
    time.setCharacterSize(10);
    time.setString(std::to_string(spacing*i/constScale));
    time.setPosition(containerOffsetX + spacing*(i),windowContainerOffsetY + containerOffsetY - eventOffsetY - 15);
    times.push_back(time);
    sf::VertexArray timeLine = sf::VertexArray(sf::Lines, 2);
    timeLine[0].position = sf::Vector2f(containerOffsetX + spacing*(i), windowContainerOffsetY + containerOffsetY - eventOffsetY); 
    timeLine[1].position = sf::Vector2f(containerOffsetX + spacing*(i), windowContainerOffsetY + containerOffsetY*nbContainer + eventOffsetY);
    timeLine[0].color = sf::Color(231,231,231);
    timeLine[1].color = sf::Color(231,231,231); 
    timeLines.push_back(timeLine);
    }
}

//getters
int scale::getContainerSize()
{
    return containerSize;
}

int scale::getContainerOffsetX() 
{
    return containerOffsetX;
}

int scale::getContainerOffsetY() 
{
    return containerOffsetY;
}

int scale::getEventOffsetY() 
{
    return eventOffsetY;
}

int scale::getWindowContainerOffsetY() 
{
    return windowContainerOffsetY;
}

int scale::getSpacing() 
{
    return spacing;
}

float scale::getScale() 
{
    return constScale;
}

//setters
void scale::setContainerOffsetX(int containerOffsetX) 
{
    containerOffsetX = containerOffsetX;
}

void scale::setContainerOffsetY(int containerOffsetY)
{
    containerOffsetY = containerOffsetY;
}

void scale::setContainerSize(int containerSize) 
{
    containerSize = containerSize;
    constScale = containerSize/absoluteTime;
    subdTimeLine = containerSize/spacing;
}

void scale::setEventOffsetY(int eventOffsetY) 
{
    eventOffsetY = eventOffsetY;
}

void scale::setSpacing(int spacing) 
{
    spacing = spacing;
    subdTimeLine = containerSize/spacing;
}

void scale::setWindowContainerOffsetY(int windowContainerOffsetY)
{
    windowContainerOffsetY = windowContainerOffsetY;
}

//update 

void scale::updateScale(int containerSize, int spacing, int containerOffsetX, int containerOffsetY, int eventOffsetY, int windowContainerOffsetY, int nbContainer)
{
    scale::setContainerSize(containerSize);
    scale::setSpacing(spacing);
    scale::setContainerOffsetX(containerOffsetX);
    scale::setContainerOffsetY(containerOffsetY);
    scale::setEventOffsetY(eventOffsetY);
    scale::setWindowContainerOffsetY(windowContainerOffsetY);
    scale::updatePosition(nbContainer);
}

void scale::updatePosition(int nbContainer)
{
    for (int i = 0; i < times.size(); i ++) 
    {
            times[i].setCharacterSize(10);

        times[i].setPosition(containerOffsetX + spacing*(i),windowContainerOffsetY + containerOffsetY - eventOffsetY - 15);
    }
    for (int j = 0; j < timeLines.size(); j ++)
    {
        timeLines[j][0].position = sf::Vector2f(containerOffsetX + spacing*(j), windowContainerOffsetY + containerOffsetY - eventOffsetY); 
        timeLines[j][1].position = sf::Vector2f(containerOffsetX + spacing*(j), windowContainerOffsetY + containerOffsetY*nbContainer + eventOffsetY);
    }
}

//draw
 void scale::draw(sf::RenderTarget& target, sf::RenderStates states) const 
 {
     for (unsigned int i = 0; i < timeLines.size(); i++) 
     {
        target.draw(times[i], states);    
        target.draw(timeLines[i], states);
     }
 }

