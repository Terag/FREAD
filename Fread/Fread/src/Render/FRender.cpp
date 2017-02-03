/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 #include "Render/FRender.hpp"

FRender::FRender(std::shared_ptr<FQueue<FMessages > > _pop_queue_core, 
                 std::shared_ptr<FQueue<FMessages>  > _push_queue_core, 
                 float absoluteTime):
_m_pop_queue_core(_pop_queue_core), _m_push_queue_core(_push_queue_core), absoluteTime(absoluteTime)
{}

std::vector<container_render> FRender::transformContainer(std::vector<std::shared_ptr<FContainer>> listContainer, scale scale) 
{
    std::vector<container_render> renderContainers;
    for(unsigned int i = 0; i < listContainer.size(); i++) 
    {
        container_render container(listContainer[i]->getId(), listContainer[i]->getAlias(), 1000, scale.getContainerOffsetX(),scale.getContainerOffsetY(),scale.getWindowContainerOffsetY());
        std::vector <patternStruct> listPattern = listContainer[i]->getPatternList();
        for (unsigned int j = 0; j < listPattern.size(); j ++) {
            FPattern fPat = viewPatternById(listPattern[j].id);
            occurrence_render occ(
                                  fPat.getId(),listPattern[j].contId,
                                  scale.getContainerOffsetY(), scale.getContainerOffsetX(),
                                  scale.getEventOffsetY(), scale.getWindowContainerOffsetY(),scale.getScale(), fPat.getMeanTimeStamps(),
                                  fPat.getEventTypes()
                                  );
            container.addOccurrence(occ);
        }
        renderContainers.push_back(container);
    }
    return renderContainers;
}  

FOccurrence FRender::askOccurrenceById(int idPattern, int idOccurrence)
{
    std::pair<int,int> pair= std::make_pair(idPattern, idOccurrence); 
    std::shared_ptr<std::pair<int,int>> shrd= std::make_shared<std::pair<int,int>>(pair);  
    std::shared_ptr<void> askedId = std::static_pointer_cast<void>(shrd); 
    FMessages msg(OCCURRENCE, askedId); 
    _m_push_queue_core->push(msg);
    FOccurrence occurrence = FOccurrence();
    return occurrence;
     
}

FContainer FRender::viewContainerById(int id)
{
   FContainer container; // = *(FCore::view_Containers(id));
   return container;    
}
 
FPattern FRender::viewPatternById(int id) 
{
    FPattern pattern = *(FCore::view_patterns(id));
    return pattern;
}

FMessages FRender::receive() 
{
   /*
    std::shared_ptr<FMessages> msg = _m_pop_queue_core->try_pop();
    if(msg != NULL) 
    {   
        FOccurrence occ = *(msg->getContent());
        std::vector<FOccurrence> waitingOcc;
    }
    */
}
 
 
float FRender::getAbsoluteTime() 
{
    return absoluteTime;
}
 
void FRender::thr_FRender() {
    //transform a list of FContainers in a list of container_renders + define the scaling 
    std::vector<std::shared_ptr<FContainer>> listContainer;
    int nbContainer = listContainer.size();
    // Valeur 1000 et 10 a changer
    scale scale(absoluteTime, nbContainer, 1000, 10);
    std::vector<container_render> renderContainers = transformContainer(listContainer, scale);
    
    //sfml antialiasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //define the window
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Container and occurrences test",sf::Style::Default, settings);
    
    // window loop
        while (window.isOpen())
    {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    for (unsigned int i = 0; i < renderContainers.size(); i++) {
                       window.draw(renderContainers[i]);
                    }
                    window.close();
            }
            window.clear(sf::Color(255,255,255));
            window.display();
    }
}

