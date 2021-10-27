#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>


struct Pincel {
    sf::Font font;
    sf::Text text;
    sf::RenderWindow& window;

    Pincel(sf::RenderWindow& window) : window(window) {
        if(!font.loadFromFile("Ubuntu.ttf"))
            std::cout << "Erro no carregamento da fonte\n";
        text.setFont(font);
    }

    void write(std::string str, int x, int y, int size, sf::Color color){
        text.setString(str);
        text.setCharacterSize(size);
        text.setPosition(x, y);
        text.setFillColor(color);
        window.draw(text);
    }
};

struct Bolha {
    
    int x;
    int y;
    char letter;
    int speed;
    
    bool alive { true };
    static const int radius { 10 };
    
    Bolha(int x, int y, char letter, int speed) {
        this->x = x;
        this->y = y;
        this->letter = letter;
        this->speed = speed;
    }

    void update() {
        this->y += this->speed;
    }

    void draw(sf::RenderWindow& window){
        sf::CircleShape bolha (Bolha::radius);
        bolha.setPosition(x, y);
        bolha.setFillColor(sf::Color::White);
        window.draw(bolha);

        static Pincel pencil(window);
        pencil.write(std::string(1, letter), x + 0.2 * Bolha::radius, y, Bolha::radius * 1.5, sf::Color::Blue);
    }

};

struct Board {
    sf::RenderWindow& window;
    std::vector<Bolha> bolha;
    Pincel pencil;


    int hits { 0 };
    int misses { 0 };

    Board(sf::RenderWindow& window) : window{window}, pencil{window} {
        bolha.push_back(Bolha(100, 100, 'A', 1));
        bolha.push_back(Bolha(200, 100, 'B', 2));
        bolha.push_back(Bolha(300, 100, 'C', 3));
    }

    void update() {
        if (this->check_new_bolha())
            this->add_new_bolha();

        for (Bolha& bolha : bolha) {
            bolha.update();
        }
        this->mark_outside_bolha();
        this->remove_dead_bolhas();
    }

    void remove_dead_bolhas() {
        std::vector<Bolha> vivas;
        for (Bolha& bolha : bolha) {
            if (bolha.alive) {
                vivas.push_back(bolha);
            }
        }
        this->bolha = vivas;
    }

    void mark_outside_bolha(){
        for (Bolha& bolha : bolha) {
            if (bolha.y + 2 * Bolha::radius > (int) this->window.getSize().y) {
                if (bolha.alive) {
                    bolha.alive = false;
                    this->misses++;
                }
            }
        }
    }

    void mark_by_hit(char letter) {
        for (Bolha& bolha : bolha) {
            if(bolha.letter == letter) {
                bolha.alive = false;
                this->hits++;
                break;
            }
        }
    }

    bool check_new_bolha() {
        static const int new_bolha_timeout { 30 };
        static int new_bolha_timer { 0 };

        new_bolha_timer--;
        if (new_bolha_timer <= 0) {
            new_bolha_timer = new_bolha_timeout;
            return true;
        }
        return false;
    }

    void add_new_bolha() {
        int x = rand() % ((int) this->window.getSize().x - 2 * Bolha::radius);
        int y = - 2 * Bolha::radius;
        int speed = rand() % 5 + 1;
        char letter = rand() % 26 + 'A';
        bolha.push_back(Bolha(x, y, letter, speed));
    }

    void draw() {
        pencil.write("Acertos: " + std::to_string(this->hits ) + " Erros: " + std::to_string(this->misses), 10, 10, 20, sf::Color::White);
        pencil.write("Bolhas: " + std::to_string(this->bolha.size()), 10, 30, 20, sf::Color::White);
        for (Bolha& bolha : bolha) {
            bolha.draw(window);
        }
    }

};

struct Jogo{
    sf::RenderWindow window;
    Board board;
    std::function<void()> on_update;

    Jogo() : window(sf::VideoMode(800, 600), "Bolhas"), board(window) {
        this->on_update = [&]() {
            this->gameplay();
        };
        window.setFramerateLimit(30);
    }

    void process_events() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                char code = static_cast<char>(event.text.unicode);
                code = toupper(code);
                board.mark_by_hit(code); 
           }
        }
    }

    void gameplay(){
        board.update();

        window.clear(sf::Color::Black);
        board.draw();
        window.display();
        if(board.misses > 9) {
            this->on_update = [&]() {
                this->gameover();
            };
        }
    }

    void gameover() {
        static Pincel pencil(window);
        window.clear(sf::Color::Red);
        pencil.write("GAME OVER", 450, 350, 25, sf::Color::White);
        window.display();
    }

    void main_loop() {
        while (window.isOpen()) {
            process_events();
            on_update();
        }
        
    }

};

int main() {
    Jogo jogo;
    jogo.main_loop();
    return 0;
}