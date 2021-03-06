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
#include <iostream>
#include <string>

//using namespace std;
using namespace sf;

container_render::container_render() :
id(0), name("")
{}

container_render::container_render(int id, std::string name, int containerSize, int offsetX, int offsetY, int windowContainerOffsetY) : 
id(id), name(name)
{
    if (!font.loadFromFile("Arimo-Regular.ttf")) 
    {
       std::cout << "error while loading the font" << std::endl;
    }
    textId.setFont(font);
    textId.setFillColor(Color(40,40,40));
    textId.setCharacterSize(10);
    textId.setString(std::to_string(id));
    textId.setPosition(20, windowContainerOffsetY + offsetY*id - 5);
    line[0].position = sf::Vector2f(offsetX, windowContainerOffsetY + offsetY*id); 
    line[1].position = sf::Vector2f(containerSize + offsetX, windowContainerOffsetY + offsetY*id);
    line[0].color = sf::Color(60,60,60);
    line[1].color = sf::Color(60,60,60);
}

void container_render::addOccurrence(occurrence_render occ) 
{
   occurrences.push_back(occ); 
}

int container_render::getId()
{
    return id;
}

std::vector<occurrence_render> container_render::getOccurrences() 
{
    return occurrences;
}

void container_render::updatePosition(int containerSize, int offsetX, int offsetY, int windowContainerOffsetY) 
{
    line[0].position = sf::Vector2f(offsetX, windowContainerOffsetY + offsetY*id); 
    line[1].position = sf::Vector2f(containerSize + offsetX, windowContainerOffsetY + offsetY*id);
}

void container_render::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(line);
    for (unsigned int i = 0; i < occurrences.size(); i++) 
    {
        target.draw(occurrences[i], states);
    }        
}

container_render::~container_render() 
{
        
}



   



