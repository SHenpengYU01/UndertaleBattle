#include "mainwindow.h"



MainWindow::MainWindow() {}

MainWindow::MainWindow(sf::VideoMode mode, char const* title, unsigned int style): sf::RenderWindow(mode, title, style) {
    this->setFramerateLimit(60);
}


PropertyNotification MainWindow::GetNotification(int nf_id){
    switch(nf_id){
        case PROP_ID::SPRITE:
            return [this](const std::any& any_sp)->void{
                try {
                    const sf::Sprite& sp = std::any_cast<const sf::Sprite&>(any_sp);
                    this->draw(sp);
                } catch (...) {
                    std::cerr << "Bad cast sf::Sprite " << std::endl;
                }
            };
            break;
        case PROP_ID::TEXT:
           return [this](const std::any& any_tx)->void{
                try {
                    const sf::Text& tx = std::any_cast<const sf::Text&>(any_tx);
                    this->draw(tx);
                } catch (...) {
                    std::cerr << "Bad cast sf::Text " << std::endl;
                }
            };
            break;
        case PROP_ID::RECTANGLE_SHAPE:
            return [this](const std::any& any_rect)->void{
                try {
                    const sf::RectangleShape& rs = std::any_cast<const sf::RectangleShape&>(any_rect);
                    this->draw(rs);
                } catch(...){
                    std::cerr << "Bad cast sf::Text " << std::endl;
                }
            };
        // case CMD_ID::NONE:
        //     return [this](const std::any& any)->void{
        //         try {
        //             this->m_next_command(CMD_ID::NONE);
        //         } catch(...) {
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //         // Do nothing
        //     };
        // case CMD_ID::LEFT:
        //     return [this](const std::any& any_rect)->void{
        //         try {
        //             this->m_next_command(CMD_ID::LEFT);
        //         } catch(...){
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //     };
        // case CMD_ID::RIGHT:
        //     return [this](const std::any& any_rect)->void{
        //         try {
        //             this->m_next_command(CMD_ID::RIGHT);
        //         } catch(...){
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //     };
        // case CMD_ID::UP:
        //     return [this](const std::any& any_rect)->void{
        //         try {
        //             this->m_next_command(CMD_ID::UP);
        //         } catch(...){
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //     };
        // case CMD_ID::DOWN:
        //     return [this](const std::any& any_rect)->void{
        //         try {
        //             this->m_next_command(CMD_ID::DOWN);
        //         } catch(...){
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //     };
        // case CMD_ID::LEFTUP:
        //     return [this](const std::any& any_rect)->void{
        //         try {
        //             this->m_next_command(CMD_ID::LEFTUP);
        //         } catch(...){
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //     };
        // case CMD_ID::RIGHTUP:
        //     return [this](const std::any& any_rect)->void{
        //         try {
        //             this->m_next_command(CMD_ID::RIGHTUP);
        //         } catch(...){
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //     };                    
        // case CMD_ID::LEFTDOWN:
        //     return [this](const std::any& any_rect)->void{
        //         try {
        //             this->m_next_command(CMD_ID::LEFTDOWN);
        //         } catch(...){
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //     };
        // case CMD_ID::RIGHTDOWN:
        //     return [this](const std::any& any_rect)->void{
        //         try {
        //             this->m_next_command(CMD_ID::RIGHTDOWN);
        //         } catch(...){
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //     };
        // case CMD_ID::X:
        //     return [this](const std::any& any_rect)->void{
        //         try {
        //             this->m_next_command(CMD_ID::X);
        //         } catch(...){
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //     };
        // case CMD_ID::Z:
        //     return [this](const std::any& any_rect)->void{
        //         try {
        //             this->m_next_command(CMD_ID::Z);
        //         } catch(...){
        //             std::cerr << "Bad cast sf::Text " << std::endl;
        //         }
        //     };                
    }
}



