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
        case PROP_ID::CMD:
            return [this](const std::any& any_cmd)->void{
                try {
                    int cmd_id = std::any_cast<int>(any_cmd);
                    if (this->m_next_command) {
                        this->m_next_command(cmd_id);
                    } else {
                        std::cerr << "No command handler set." << std::endl;
                    }
                } catch (...) {
                    std::cerr << "Bad cast int for command ID" << std::endl;
                }
            };
        }       
}



