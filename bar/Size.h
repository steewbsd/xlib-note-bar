//
// Created by kn1ght on 9/8/20.
//

#ifndef NOTEBAR_SIZE_H
#define NOTEBAR_SIZE_H

class Size {
public:
    float getSizeX() const;

    void setSizeX(float newSizeC);

    float getSizeY() const;

    void setSizeY(float sizeY);

    void resizeTo(const Size *newSize);

    void expand(const Size *addSize);

    Size(float sizeX, float sizeY);

private:
    float sizeX = 0;
    float sizeY = 0;
};

#endif //NOTEBAR_SIZE_H
