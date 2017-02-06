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
 * File:   occurrence_render.cpp
 * Author: Jerome
 *
 * Created on 24 janvier 2017, 15:35
 */

#include "Render/occurrence_render.hpp"

using namespace std;

occurrence_render::occurrence_render() :
id(0)
{
}

occurrence_render::occurrence_render(int id, int containerID, int containerOffsetY, 
                                     int containerOffsetX, int eventOffsetY, int windowContainerOffsetY, float scale, 
                                     vector<float> timeStamps, vector<eventType> eventTypes ):
id(id), timeStamps(timeStamps), eventTypes(eventTypes)
{
    for (unsigned int i = 0; i < eventTypes.size() ; i++)
        {
            float tStart = timeStamps[2*i];
            float tEnd = timeStamps[2*i+1];
            eventType type = eventTypes[i];
            event_render nouvelEvent = event_render(type, tStart, tEnd, scale, containerOffsetY, containerID, eventOffsetY, containerOffsetX, windowContainerOffsetY);
            events.push_back(nouvelEvent);
        } 
}

occurrence_render::~occurrence_render()
{    
}

int occurrence_render::getId() 
{
    return id;
}
std::vector<event_render> occurrence_render::getEvents() 
{
    return events;
}

void occurrence_render::updatePosition(int newScale, int containerOffsetY, int offsetX, int offsetY) 
{
    for (unsigned int i = 0; i < events.size(); i++) 
    {
       events[i].updatePosition(newScale, containerOffsetY, offsetX, offsetY);
    } 
}

void occurrence_render::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < events.size(); i++) 
    {
       target.draw(events[i], states);
    }           
}
