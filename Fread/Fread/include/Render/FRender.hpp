/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FRender.hpp
 * Author: emma
 *
 * Created on 30 janvier 2017, 17:15
 */

#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <SFML/Graphics.hpp>
#include "Render/container_render.hpp"
#include "FQueue.hpp" //template
#include "FMessages.hpp" //template
#include "FMap.hpp" //template
#include "FThread_guard.hpp"
#include "FObjet.hpp"
#include "FOccurrence.hpp"
#include "FPattern.hpp"
#include "FContainer.hpp"

class FRender {
    
public: 
    FRender(std::shared_ptr< FQueue< FMessages< FObjet > > > _pop_queue_core,
           std::shared_ptr< FQueue< FMessages< std::pair<int,int> > > > _push_queue_core,
            float absoluteTime);
    ~FRender();
    std::vector<container_render> transformContainer(std::vector<std::shared_ptr<FContainer>> listContainer, scale scale);
    void thr_FRender();
    FOccurrence askOccurrenceById(int idPattern, int idOccurrence);
    FPattern viewPatternById(int id);
    FMessages receive();
    float getAbsoluteTime();
    
private: 
    bool awake;
    float absoluteTime;
    std::shared_ptr<FQueue< FMessages< FObjet > > > _m_pop_queue_core;
    std::shared_ptr<FQueue< FMessages< std::pair<int,int> > > > _m_push_queue_core;
};