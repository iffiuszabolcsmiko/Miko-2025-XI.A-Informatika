#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

const float pi = 3.141592;

//elforgatja b-t a korul
Vector2f forgat(Vector2f a, Vector2f b, float szog)
{
    float rad = szog * pi / 180;
    Vector2f c;
    c.x = a.x + (b.x - a.x) * cos(rad) - (b.y - a.y) * sin(rad);
    c.y = a.y + (b.x - a.x) * sin(rad) + (b.y - a.y) * cos(rad);
    return c;
}

void SierpinskiHaromszog(RenderWindow &window, Vector2f a, Vector2f b, Vector2f c, int n, int i = 0)
{
    if(i >= n)
    {
        Vertex line[] = {
            Vertex(a, Color::Red), Vertex(b, Color::White),
            Vertex(b, Color::White), Vertex(c, Color::Blue),
            Vertex(c, Color::Blue), Vertex(a, Color::Red)
        };
        window.draw(line, 6, Lines);
        return;
    }

    Vector2f d = (a + b) / 2.f;
    Vector2f e = (c + b) / 2.f;
    Vector2f f = (a + c) / 2.f;

    SierpinskiHaromszog(window, a, d, f, n, i + 1);
    SierpinskiHaromszog(window, d, b, e, n, i + 1);
    SierpinskiHaromszog(window, f, e, c, n, i + 1);
}

int main()
{
    int windowWidth = 800;
    int windowHeight = 600;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Hello World SFML");
    window.setFramerateLimit(60);

    Vector2f a(200.f, 400.f);
    Vector2f b(600.f, 400.f);
    Vector2f c = forgat(a, b, -60);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
                //if (event.key.code == Keyboard::Escape)
                window.close();
        }

        window.clear(Color::Black);

        SierpinskiHaromszog(window, a, b, c, 9);

        window.display();
    }

    return 0;
}
