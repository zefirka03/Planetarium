#include "core/AirCore.h"
#include "renderer/Renderer2d.h"
#include "renderer/Sprite.h"
#include "renderer/Texture.h"


struct scene : public air::Scene<air::SRenderer2d> {
    void start() override {
        auto& TM = get_system<air::SRenderer2d>()->get_texture_manager();
        TM.load_texture("images/tex.png", "tex");
        printf("%d", (GLuint)*TM.get_texture("tex"));

        air::P_Camera2d camera;
        camera.get_component<air::C_Camera2d>().resize(1280, 720);

        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 14; j++) {
                air::P_Sprite sprite;
                sprite.get_component<air::C_Sprite>().set_texture(TM.get_texture("tex"));
                sprite.get_component<air::C_Sprite>().set_size({ 49, 49 });
                sprite.get_component<air::C_Transform>().set_position({ 50 * i, 50 * j });
            }
        }
    };
};


int main(){
    air::Game game(1280, 720, "App");
    game.run(new scene());
    
    return 0;
}