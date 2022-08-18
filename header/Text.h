#ifndef TEXT_H
#define TEXT_H

#define INCLUDE_SDL_TTF

#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
#include "Timer.h"

class Text : public Component {
    public:
        enum TextStyle {
            SOLID,
            SHADED,
            BLENDED
        };
        Text(GameObject& associated, const char* fontFile, int fontSize,
             TextStyle style, string text, SDL_Color color, float timeToBlink = -1);
        ~Text();
        void Update(float dt);
        void Render();
        bool Is(const char* type);
        string GetText();
        void SetText(string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(const char* fontFile);
        void SetFontSize(int fontSize);

    private:
        void RemakeTexture();
        TTF_Font* font;
        SDL_Texture* texture;
        string text;
        TextStyle style;
        const char* fontFile;
        int fontSize;
        SDL_Color color;
        Timer timer;
        float timeToBlink;
        bool showText;
};

#endif // TEXT_H