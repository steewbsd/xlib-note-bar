//
// Created by kn1ght on 9/8/20.
//

#ifndef NOTEBAR_MARGIN_H
#define NOTEBAR_MARGIN_H


class Margin {
private:
    float marginTop;
    float marginLeft;
    float marginBottom;
    float marginRight;
public:
    explicit Margin();
    explicit Margin(float* margins...);
    float getMarginTop() const {
        return marginTop;
    }

    void setMarginTop(float marginTop) {
        Margin::marginTop = marginTop;
    }

    float getMarginLeft() const {
        return marginLeft;
    }

    void setMarginLeft(float marginLeft) {
        Margin::marginLeft = marginLeft;
    }

    float getMarginBottom() const {
        return marginBottom;
    }

    void setMarginBottom(float marginBottom) {
        Margin::marginBottom = marginBottom;
    }

    float getMarginRight() const {
        return marginRight;
    }

    void setMarginRight(float marginRight) {
        Margin::marginRight = marginRight;
    }
};

#endif //NOTEBAR_MARGIN_H
