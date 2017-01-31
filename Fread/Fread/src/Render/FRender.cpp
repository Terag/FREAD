/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* #include "Render/FRender.hpp"

FRender::FRender(std::shared_ptr<FQueue<FMessages<FObjet> > > _pop_queue_core, 
                 std::shared_ptr<FQueue<FMessages<std::pair<int,int> > > > _push_queue_core, 
                 float absoluteTime):
_m_pop_queue_core(_pop_queue_core), _m_push_queue_core(_push_queue_core), absoluteTime(absoluteTime)
{}
 std::vector<container_render> FRender::transformContainer(std::vector<std::shared_ptr<FContainer>> listContainer, scale) 
{
    std::vector<container_render> renderContainers;
    for(int i = 0; i < listContainer.size(); i++) 
    {
        container_render container = container_render(listContainer[i]->getId(), listContainer[i]->getAlias(), 1000);
        std::vector <int> listIdOccurrences = listContainer[i]->getListeIdOccurrences();
        for (int j = 0; j < listIdOccurrences.size(); j ++) {
            FOccurrence fOcc = askOccurrenceById(listIdOccurrences[j]);
            occurrence_render occ = occurrence_render(fOcc.getId(),fOcc.getContainerId(),
                                                      scale.getContainerOffsetY(), scale.getContainerOffsetX(),
                                                      scale.getEventOffsetY(), scale.getScale(), fOcc.getTimeStamps(),
                                                      viewPatternById(fOcc.getPatternId()).getEventTypes()
                                                      );
            container.addOccurrence(occ);
        }
        renderContainers.push_back(container);
    }
    return renderContainers;
}  

 FOccurrence FRender::askOccurrenceById(int idPattern, int idOccurrence)
 {
     std::pair<int, int> askedId = std::make_pair(idPattern, idOccurrence);
     FMessages msg(OCCURRENCE, askedId);
     _m_push_queue_core->push(msg);
     FOccurrence occurrence = FOccurrence();
     return occurrence;
     
 }
 
 FPattern FRender::viewPatternById(int id) 
 {
    std::pair<int, int> askedId = std::make_pair(id, id);
    FMessages msg(OCCURRENCE, askedId);
    _m_push_queue_core->push(msg); 
     FPattern pattern = FPattern();
     return pattern;
 }
 
 FMessages FRender::receive() 
 {
    std::shared_ptr<FMessages> msg = _m_pop_queue_core->try_pop();
    if(msg != NULL) 
    {
        
    }
 }
 
 float FRender::getAbsoluteTime() 
 {
     return absoluteTime;
 }
 
void FRender::thr_FRender() {
    //transform a list of FContainers in a list of container_renders + define the scaling 
    std::vector<std::shared_ptr<FContainer>> listContainer;
    int nbContainer = listContainer.size();
    scale scale = scale(absoluteTime, nbContainer);
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
                    for (int i = 0; i < renderContainers.size(); i++) {
                       window.draw(renderContainers[i]);
                    }
                    window.close();
            }
            window.clear(sf::Color(255,255,255));
            window.display();
    }
}
*/
