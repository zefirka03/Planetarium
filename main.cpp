#include "core/AirCore.h"
#include "renderer/Renderer2d.h"
#include "renderer/Sprite.h"
#include "renderer/Texture.h"


struct scene : public air::Scene<air::SRenderer2d> {
    void start() {
        air::P_Camera2d camera;
        for (int i = 0; i < 100; i++) {
            air::P_Sprite sprite;
            sprite.get_component<air::C_Transform>().set_position({ 10*i,10*i });
        }

        camera.get_component<air::C_Camera2d>().resize(1280, 720);
    };

};


int main(){
    air::Game game(1280, 720, "App");
    game.run(new scene());
    
    return 0;
}