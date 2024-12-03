#include "converter.h"

float convert::PIXELS_PER_METER = 4.0f;

sf::Vector2f convert::metersToPixels(const b2Vec2& meters)
{
    return sf::Vector2f(meters.x * PIXELS_PER_METER, meters.y * PIXELS_PER_METER);
}


b2Vec2 convert::pixelsToMeters(const sf::Vector2i& pixelPos)
{
    return b2Vec2(pixelPos.x / PIXELS_PER_METER, pixelPos.y / PIXELS_PER_METER);
}