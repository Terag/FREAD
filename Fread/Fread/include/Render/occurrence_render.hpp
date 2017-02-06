/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   occurrence_render.hpp
 * Author: Emma et Jerome 
 *
 * Created on 6 février 2017, 18:35
 */

/*
 * An occurrence_render referes to a bloc of events_render that are drawn on a container_render
 */

#pragma once 
#include <vector>
#include <SFML/Graphics.hpp>
#include "../FObjet.hpp" // the enum eventType is defined here
#include "event_render.hpp"

class occurrence_render : public sf::Drawable {
 
private : 
// the id of the occurrence
int id;
// the vector of all the timestamps of the events of an occurrence_render
std::vector<float> timeStamps;
// the vector of all the type of events which goes with the vector of timestamps
std::vector<eventType> eventTypes;
// the vector of each events drawable of an occurrence
std::vector<event_render> events; 

public : 
//constructors & destructors
occurrence_render();
occurrence_render(int id, int containerID, int containerOffsetY, 
                  int containerOffsetX, int eventOffsetY, int windowContainerOffsetY, float scale, std::vector<float> timeStamps,
                  std::vector<eventType> event);
~occurrence_render();
//getters
std::vector<event_render> getEvents();
int getId();
//update
void updatePosition(int newScale, int containerOffsetY, int offsetX, int offsetY);
//draw
void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
};