
#include <SFML/Graphics.hpp>

#include <SFML/System/Time.hpp>
#include <random>
#include <vector>
#include <iostream>

struct RNG
{
    static int next_int(int min, int max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> rand(min, max);
        return rand(gen);
    }
};

struct visualization_sortable_item_t
{
    sf::RectangleShape shape;
    int value;

    //void operator = (const visualization_sortable_item_t & other)
    //{
        //this->shape = other.shape;
        //this->value = other.value;
    //}
};

typedef visualization_sortable_item_t s_item_t;

bool operator < (const s_item_t & a, const s_item_t & b)
{
    return a.value < b.value;
}

bool operator > (const s_item_t & a, const s_item_t & b)
{
    return !(a < b);
}

typedef sf::RectangleShape RS;

std::vector<s_item_t> s_items;

const unsigned window_width = 500;
const unsigned window_height = 500;

int quantity = window_width / 10;
float width = window_width / (quantity);

bool finished = false;

void sort(std::vector<s_item_t> & items, sf::RenderWindow & window)
{
    if (items.size() < 0) return;

    int n = items.size();

    while(n >= 1)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        int n_size = 0;
        for(int i = 1; i <= n -1; ++i)
        {
            auto & first = items[i - 1];
            auto & second = items[i];

            // cambiar su color para identificarlos
            first.shape.setFillColor(sf::Color::Green);
            second.shape.setFillColor(sf::Color::Yellow);

            if(first > second)
            {
                // hacer el swap y actualizar su posicion

                first.shape.setPosition((i) * width + 1, first.shape.getPosition().y);
                second.shape.setPosition((i - 1) * width + 1, second.shape.getPosition().y);
                
                //std::swap(first, second);
                auto aux = first;
                first = second;
                second = aux;

                n_size = i;
            }
            

            // dibujar
            window.clear();        
            for(const auto & rect : s_items)
            {
                window.draw(rect.shape);
            }
            window.display();

            first.shape.setFillColor(sf::Color::White);
            second.shape.setFillColor(sf::Color::White);
            //sf::sleep(sf::milliseconds(25));
        }

        //sf::sleep(sf::seconds(0.3f));

        n = n_size;
    }
    finished = true;
}

void update()
{
    //static int index = 0;

    //if(index > 0)
        //s_items[index - 1].shape.setfillcolor(sf::color::white);

    //if(index > s_items.size() - 1)
        //index = 0;

    //s_items[index].shape.setfillcolor(sf::color::green);

    //++index;

    //sf::sleep(sf::seconds(0.2f));
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");
     
    // 20 cada uno de 10 de ancho 

    for(int i = 0; i < quantity; ++i)
    {

        int v = RNG::next_int(1, window_height);

        RS a({width - 2, (float)v});
        a.setFillColor(sf::Color::White); 
        a.setPosition(sf::Vector2f(i * width + 1, window_height - v));

        s_item_t t {a, v};

        s_items.push_back(t);
    }
    s_items.shrink_to_fit();

    //std::sort(s_items.begin(), s_items.end(), [](auto a, auto b) {
            //return a.value < b.value; });

    // actualiza todas las posiciones despues de ordenar
    //for(int i = 0; i < s_items.size(); ++i)
    //{
        //RS & s = s_items[i].shape;
        //s.setPosition(i * width + 1, s.getPosition().y);
    //}
    std::cerr << "hola\n";
    do
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        //update();
        if(!finished)
            sort(s_items, window); 
        //render(window);
    }
    while(window.isOpen());
}
