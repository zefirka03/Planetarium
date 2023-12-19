#include "core/AirCore.h"
#include "renderer/Renderer2d.h"
#include "renderer/Sprite.h"
#include "renderer/Texture.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


class S_Imgui : public air::System {
public:
    void start() override {
        const char* glsl_version = "#version 130";
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(air::Game::get_current_game()->get_glfw_window(), true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void update() override {
        auto renderer = air::Game::get_current_game()->get_current_scene()->get_system<air::S_Renderer2d>();
        auto& stats = renderer->get_stats();
            
        ++frame_count;
        avg_fps += ImGui::GetIO().Framerate;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
            
        {
            ImGui::Begin("Stats");
            ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
            ImGui::Text("FPS AVRG: %f", avg_fps / frame_count);

            ImGui::NewLine();

            ImGui::Text("Batch count: %d", stats.batch_count);
            ImGui::Text("Video memory allocated: %.2f MB", stats.video_memory_allocated / (1024.0 * 1024.0));
            ImGui::Text("Video memory use: %.2f MB", stats.video_memory_use / (1024.0 * 1024.0));
            ImGui::Text("Sprites rendered: %d", stats.sprites_rendered);

            ImGui::End();
        }
    }

    void last_update() override {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    float avg_fps = 0;
    float frame_count = 0;
};


struct scene : public air::Scene<air::S_Renderer2d, S_Imgui> {
    void start() override {
        auto& TM = get_system<air::S_Renderer2d>()->get_texture_manager();
        TM.load_texture("images/tex.png", "tex");
        TM.load_texture("images/ff.png", "ff");
        printf("%d", (GLuint)*TM.get_texture("tex"));

        air::P_Camera2d camera;
        camera.get_component<air::C_Camera2d>().resize(1920, 1080);
        

        for (int i = 0; i < 240; i++) {
            for (int j = 0; j < 54; j++) {
                air::P_Sprite sprite;
                sprite.get_component<air::C_Sprite>().set_texture(TM.get_texture("tex"));
                sprite.get_component<air::C_Sprite>().set_size({ 7, 7 });
                sprite.get_component<air::C_Transform>().set_position({ 8 * i, 8 * j });
            }
        }

        for (int i = 0; i < 240; i++) {
            for (int j = 0; j < 54; j++) {
                air::P_Sprite sprite;
                sprite.get_component<air::C_Sprite>().set_texture(TM.get_texture("ff"));
                sprite.get_component<air::C_Sprite>().set_size({ 7, 7 });
                sprite.get_component<air::C_Transform>().set_position({ 8 * i, 8 * 54 + 8 * j });
            }
        }
    };
};


int main(){
    air::Game game(1920, 1080, "App");
    game.run(new scene());
    
    return 0;
}