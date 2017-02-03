/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 #include "Render/FRender.hpp"

FRender::FRender(std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _pop_queue_core, 
                 std::shared_ptr<FQueue< std::shared_ptr<FMessages> > > _push_queue_core, 
                 float absoluteTime):
                _m_pop_queue_core(_pop_queue_core), 
                _m_push_queue_core(_push_queue_core), 
                absoluteTime(absoluteTime)
{
}
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
 
FPattern FRender::viewPatternById(int id) 
{
    //FPattern pattern = *(FCore::view_patterns(id));
    //return pattern;
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


/*
 *
 * METHODS USED TO ASK THE CORE FOR AN OCCURRENCE BY ITS patternId AND ITS OWN occId
 *
 */
void FRender::ask_for_occurrence(int patternId, int occId){
  std::pair<int, int> occurrence(patternId, occId);
  std::shared_ptr< std::pair<int, int> > occurrence_send = std::make_shared< std::pair<int, int> >(occurrence);
  auto content_send = std::static_pointer_cast<void>( occurrence_send );
  FMessages msg_send(OCCURRENCE, content_send);
  std::cout << "RENDER >>> SEND OCCURRENCE " << patternId << ":" << occId << " TO CORE" << std::endl;
  _m_push_queue_core->push(std::make_shared<FMessages>(msg_send) );
}

/*
 *
 * METHODS USED TO ASK THE CORE FOR ALL THE PATTERN IN THE CONTAINER contId BETWEEN begin_time AND end_time
 *
 */
void FRender::ask_for_timestamps(int contId, float begin_time, float end_time){
  patternStruct timestamp(-1, contId, begin_time, end_time);
  auto timestamps_send = std::make_shared< patternStruct >(timestamp);
  auto content_send = std::static_pointer_cast<void>( timestamps_send );
  FMessages msg_send(TIMESTAMP, content_send);
  std::cout << "PARSER >>> SEND TIMESTAMPS ON CONTAINER : " << contId << " FROM : " << begin_time << " UNTIL : " << end_time << " TO CORE" << std::endl;
  _m_push_queue_core->push(std::make_shared<FMessages>(msg_send) );
}

/*
 *
 * METHODS USED TO ASK THE CORE FOR A PATTERN BY ITS patternId
 *
 */
void FRender::ask_for_pattern(int patternId){
  std::shared_ptr<int> pattern_send = std::make_shared<int>( patternId );
  auto content_send = std::static_pointer_cast<void>( pattern_send );
  FMessages msg_send(PATTERN, content_send);
  std::cout << "RENDER >>> SEND PATTERN : " << patternId << " TO CORE" << std::endl;
  _m_push_queue_core->push(std::make_shared<FMessages>(msg_send) );
}

/*
 *
 * METHODS USED TO ASK THE CORE FOR A CONTAINER BY ITS contId
 *
 */
void FRender::ask_for_container(int contId){
  std::shared_ptr<int> container_send= std::make_shared<int>( contId );
  auto content_send = std::static_pointer_cast<void>( container_send );
  FMessages msg_send(CONTAINER, content_send);
  std::cout << "RENDER >>> SEND CONTAINER : " << contId << " TO CORE" << std::endl;
  _m_push_queue_core->push(std::make_shared<FMessages>(msg_send) );
}

/*
 *
 * METHODS USED TO GET A MESSAGE FROM THE CORE
 *
 */
void FRender::receive_message(){

  std::shared_ptr<FMessages> msg = *( _m_pop_queue_core->try_pop() );
  if( msg.use_count() != 0 && msg != NULL){
      switch(msg->getHeader()){
          case(START):
          {
              std::cout << "CORE >>> START MESSAGE RECEIVED FROM CORE" << std::endl;
              break;
          }
          case(INITDONE):
          {
              std::cout << "CORE >>> INITDONE MESSAGE RECEIVED FROM CORE" << std::endl;
              break;
          }
          case(CONTAINER):
          {
              std::cout << "CORE >>> CONTAINER MESSAGE RECEIVED FROM CORE" << std::endl;
              std::shared_ptr< FContainer > received = std::static_pointer_cast<FContainer>( msg->getContent() );
              break;
          }
          case(PATTERN):
          {
              std::cout << "CORE >>> PATTERN MESSAGE RECEIVED FROM CORE" << std::endl;
              std::shared_ptr< FPattern > received = std::static_pointer_cast<FPattern>( msg->getContent() );
              break;
          }
          case(TIMESTAMP):
          {
              std::cout << "CORE >>> TIMESTAMP MESSAGE RECEIVED FROM CORE" << std::endl;
              std::shared_ptr< std::vector< patternStruct > > received = std::static_pointer_cast< std::vector<patternStruct> >( msg->getContent() );
              break;
          }
          case(OCCURRENCE):
          {
              std::cout << "CORE >>> OCCURRENCE MESSAGE RECEIVED FROM CORE" << std::endl;
              std::shared_ptr< FOccurrence > received = std::static_pointer_cast<FOccurrence>( msg->getContent() );
              break;
          }
          default:

          break;
      } /* switch */
    } /* if */
} /* void */

//Je ne sais pas comment vous comptez récupérer les messages mais sinon la méthode c'est:
//  auto msg = *( _m_pop_queue_core->try_and_pop() ); on récupère le message sous la forme d'un std::shared_ptr<FMessages>
//  auto received = std::static_pointer_cast<DEFINIR_LE_TYPE_SELON_LE_HEADER>( msg->getContent() ); on récupère un shared_ptr sur l'objet récupéré (dont le type dépend du HEADER : FContainer pour CONTAINER, FPattern pour PATTERN, std::vector<patternStruct> pour TIMESTAMP ou FOccurrence pour OCCURRENCE)
//  auto content = *received; pour avoir le contenu du shared_ptr