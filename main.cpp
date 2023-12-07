#include "core/AirCore.h"
#include "renderer/Renderer2d.h"
#include "renderer/Sprite.h"


struct scene : public air::Scene<air::SRenderer2d> {
    void start() {
        air::P_Camera2d camera;
        air::P_Sprite sprite;
    };
};


int main(){
    air::Game game(1280, 720, "App");
    game.run(new scene());
    
    return 0;
}