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
 * File:   container_render.hpp
 * Author: emma
 *
 * Created on 24 janvier 2017, 10:25
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum eventType {
    WAIT, COMPUTE, SEND
};

class scale {
private : 
    float constScale = 1.f;
    float absoluteTime = 1.f;
    int containerSize = 500;
    
public : 
    scale();
    scale(float absoluteTime, int containerSize);
    float getScale();
    int getContainerSize();
};

class event_render : public sf::Drawable {
private:
    sf::Color eventColor = sf::Color(255,255,255);
    int  tStart, tEnd, height, containerID = 0;
    eventType type;
    
public:
    event_render();
    event_render(float tSStart, float tSEnd, float scale, eventType type, int containerID, int height);
    ~event_render();
    void setColor();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};

class occurrence_render : public sf::Drawable {
 
private : 
int id;
// std::vector<float> timeStamps;
std::vector<event_render> events; 
// int id_pattern;   
// bool isLoaded = false;

public : 
occurrence_render();
occurrence_render(int id, int containerID, int height, float scale, std::vector<float> timeStamps, std::vector<eventType> event);
void addEvent(event_render event);  
void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
~occurrence_render();
// int getIdPattern();  
// bool getIsLoaded();

};

class container_render : public sf::Drawable
{
private : 
    int id; 
    std::string name;
    int offsetX = 10;
    int offsetY = 20;
    std::vector<occurrence_render> occurrences;
    sf::VertexArray line;

        
public : 
    container_render();
    container_render(int id, std::string name, int containerSize);
    container_render(int id, std::string name, int containerSize, int offsetX, int offsetY);
    int getOffsetX();
    int getOffsetY();
    int getId();
    void addOccurrence(occurrence_render occ);
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;
    ~container_render();
            
};
