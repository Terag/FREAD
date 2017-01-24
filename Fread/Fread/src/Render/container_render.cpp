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

#include <SFML/Graphics.hpp>
#include "Render/container_render.hpp"

using namespace std;
using namespace sf;

container_render::container_render() :
id(0), name(""), absoluteTime(1)
{
}

container_render::container_render(int id, std::string name, float absoluteTime) : 
id(id), name(name), absoluteTime(absoluteTime)
{}

container_render::container_render(int id, std::string name, float absoluteTime, int offsetX, int offsetY) : 
id(id), name(name), absoluteTime(absoluteTime), offsetX(offsetX), offsetY(offsetY)
{}

void container_render::calculateScale(float absoluteTime) 
{
    container_render.scale = container_render.sizeContainer/(absoluteTime);
}

void container_render::addOccurrence(occurrence_render occ) 
{
   container_render.occurrences.push_back(occ); 
}

float container_render::getScale() 
{
    return scale;
}

int container_render::getOffsetX()
{
    return offsetX;
}

int container_render::getOffsetY()
{
    return offsetY;
}

int container_render::getId()
{
    return id;
}

container_render::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const 
{
    target.draw(line, states );
    for (int i = 0; i < occurrences.size; i++) 
    {
        target.draw(occurrences[i], states);
    }        
}


    