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
#include "../FObjet.hpp"

class scale {
private : 
    float absoluteTime = 1.f;
    int containerSize = 1000;
    int spacing = 100;
    int containerOffsetX = 50;
    int containerOffsetY = 30;
    int eventOffsetY = 8;
    float constScale = 1.f;
    int windowContainerOffsetY;
    //variable related to the text of the timeline
    sf::Font font;
    std::vector<sf::Text> times;
    std::vector<sf::VertexArray> timeLines;
    
public : 
    scale();
    scale(float absoluteTime, int nbContainer, int containerSize, int windowContainerOffsetY);
    scale(float absoluteTime, int nbContainer, int containerSize,
          int spacing, int containerOffsetX, int containerOffsetY,
          int eventOffsetY, int windowContainerOffsetY);
    // getters
    float getScale();
    int getContainerSize();
    int getContainerOffsetX();
    int getContainerOffsetY();
    int getEventOffsetY();
    int getWindowContainerOffsetY();
    // setters
    void setContainerSize(int containerSize);
    void setSpacing(int spacing);
    void setContainerOffsetX(int containerOffsetX);
    void setContainerOffsetY(int containerOffsetY);
    void setEventOffsetY(int eventOffsetY);
    // draw
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

};

class event_render : public sf::Drawable {
private:
    sf::Color eventColor = sf::Color(60,60,60);
    eventType type;
    int  tStart, tEnd, containerOffsetY, containerID, windowContainerOffsetY = 0;
    int offsetY = 6;
    int offsetX = 50;
    
public:
    event_render();
    event_render(eventType type, float tSStart, float tSEnd,
                 float scale, int containerOffsetY, int containerID,
                 int offsetY, int containerOffsetX, int windowContainerOffsetY);
    ~event_render();
    void setColor();
    eventType getType();
    sf::Color getColor();
    std::string getTypeString();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};

class occurrence_render : public sf::Drawable {
 
private : 
int id;
std::vector<float> timeStamps;
std::vector<eventType> eventTypes;
std::vector<event_render> events; 
// int id_pattern;   
// bool isLoaded = false;

public : 
occurrence_render();
occurrence_render(int id, int containerID, int containerOffsetY, 
                  int containerOffsetX, int eventOffsetY, int windowContainerOffsetY, float scale, std::vector<float> timeStamps,
                  std::vector<eventType> event);
std::vector<event_render> getEvents();
int getId();
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
    int offsetX = 30;
    int offsetY = 20;
    std::vector<occurrence_render> occurrences;
    sf::Font font;
    sf::Text textId;
    sf::VertexArray line;
      
public : 
    container_render();
    container_render(int id, std::string name, int containerSize);
    container_render(int id, std::string name, int containerSize, int offsetX, int offsetY,  int windowContainerOffsetY);
    void setOffsetX(int x);
    void setOffsetY(int y);
    int getOffsetX();
    int getOffsetY();
    int getId();
    void getOccId();
    void addOccurrence(occurrence_render occ);
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;
    ~container_render();
            
};
