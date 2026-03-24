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

void SierpinskiSzonyeg(RenderWindow &window, Vector2f a, Vector2f b, Vector2f c, Vector2f d, int n)
{
    if(n <= 0)
    {
        Vertex line[] = {
            Vertex(a, Color::Yellow), Vertex(b, Color::White),
            Vertex(b, Color::White), Vertex(c, Color::Blue),
            Vertex(c, Color::Blue), Vertex(d, Color::Red),
            Vertex(d, Color::Red), Vertex(a, Color::Yellow)
        };
        window.draw(line, 8, Lines);
        return;
    }

    // osztas 3x3-ra
    Vector2f ab = (b - a) / 3.f;
    Vector2f ad = (d - a) / 3.f;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // kozepso kihagyasa
            if (i == 1 && j == 1)
                continue;

            Vector2f na = a + ab * (float)i + ad * (float)j;
            Vector2f nb = na + ab;
            Vector2f nd = na + ad;
            Vector2f nc = nb + ad;

            SierpinskiSzonyeg(window, na, nb, nc, nd, n - 1);
        }
    }
}

int main()
{
    int windowWidth = 800;
    int windowHeight = 600;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Hello World SFML");
    window.setFramerateLimit(60);

    Vector2f a(200.f, 500.f);
    Vector2f b(600.f, 500.f);
    Vector2f c = forgat(b, a, 90);
    Vector2f d = forgat(a, b, -90);

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

        SierpinskiSzonyeg(window, a, b, c, d, 6);

        window.display();
    }

    return 0;
}
