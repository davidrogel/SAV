
#include <SFML/Graphics.hpp>

#include <SFML/Graphics/Color.hpp>
#include <random>
#include <vector>
#include <utility>

namespace 
{
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

    // -.-
    struct visualization_sortable_item_t
    {
        sf::RectangleShape shape;
        int value;
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
}

std::vector<s_item_t> s_items;

const unsigned window_width = 1000;
const unsigned window_height = 500;

constexpr int quantity = window_width / 2;
constexpr float width = window_width / (quantity);

const sf::Color default_color = sf::Color::White;
const sf::Color first_hl_color = sf::Color::Green;
const sf::Color second_hl_color = sf::Color::Yellow;

template <typename T>
void sort(std::vector<T> & items) // BUBBLE SORT
{
    if (items.size() < 0) return;

    int n = items.size();

    while(n >= 1)
    {
        int n_size = 0;
        for(int i = 1; i <= n -1; ++i)
        {
            auto & first = items[i - 1];
            auto & second = items[i];

            // change colors
            {
                first.shape.setFillColor(first_hl_color);
                second.shape.setFillColor(second_hl_color);
            }

            sf::sleep(sf::microseconds(2));

            if(first > second)
            {
                // update position and swap

                first.shape.setPosition ((i) * width + 1,     first.shape.getPosition().y);
                second.shape.setPosition((i - 1) * width + 1, second.shape.getPosition().y);
                
                std::swap(first, second);

                n_size = i;
            }

            sf::sleep(sf::microseconds(2));
            
            // restore colors
            {
                first.shape.setFillColor(default_color);
                second.shape.setFillColor(default_color);
            }
        }

        n = n_size;
    }
}

void run()
{
    sort(s_items);

    // floritura
    {
        for(int i = 0; i < s_items.size(); ++i)
        {
            if(i > 0) s_items[i - 1].shape.setFillColor(default_color);
            
            s_items[i].shape.setFillColor(first_hl_color);
            sf::sleep(sf::milliseconds(10));
        }

        s_items.back().shape.setFillColor(default_color);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");

    for(int i = 0; i < quantity; ++i)
    {
        int random_number = RNG::next_int(1, window_height);

        sf::Vector2f size       (width - 1,     (float)random_number);
        sf::Vector2f position   (i * width + 1, window_height - random_number);

        sf::RectangleShape a(size);
        a.setFillColor(default_color); 
        a.setPosition(position);

        s_item_t t {a, random_number};

        s_items.push_back(t);
    }

    sf::Thread t(run);
    bool launched = false;

    do
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(!launched && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            launched = true;
            t.launch();
        }

        window.clear();        
        for(const auto & rect : s_items)
        {
            window.draw(rect.shape);
        }
        window.display();
    }
    while(window.isOpen());
    
    // close thread
    t.terminate();
}
