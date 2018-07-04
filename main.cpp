// ImGui - standalone example application for SDL2 + OpenGL
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include <imgui/imgui.h>
#include "imgui_impl_sdl_gles2.h"
#include <stdio.h>
#include <SDL.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#else
#include <SDL_opengles2.h>
#include <GLES2/gl2.h>
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

bool done = false;
SDL_Window *window;
/*
bool show_test_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImColor(114, 144, 154);
*/
bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void main_loop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSdlGLES2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            done = true;
    }
    ImGui_ImplSdlGLES2_NewFrame(window);

    // 1. Show a simple window
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
    {
        static float f = 0.0f;
        static int counter = 0;
        ImGui::Text("Hello, world!");
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        ImGui::ColorEdit3("clear color", (float*)&clear_color);
        //if (ImGui::Button("Test Window")) show_test_window ^= 1;
        //if (ImGui::Button("Another Window")) show_another_window ^= 1;
        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name your windows.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

    // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow(). Read its code to learn more about Dear ImGui!
    if (show_demo_window)
    {
        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
    //ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    ImGui_ImplSdlGLES2_RenderDrawLists(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
}

int main(int, char**)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    //window = SDL_CreateWindow("ImGui SDL2+OpenGL ES2 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    window = SDL_CreateWindow("ImGui SDL2+OpenGL ES2 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    // Check if window was created
    if(window == 0)
    {
        printf("SDL window error\n");
        SDL_Quit();
    }

    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup ImGui binding
    //ImGui_ImplSDL2_InitForOpenGL(window, glcontext);
    (void)glcontext; // Viewport branch will need this.
    ImGui_ImplSdlGLES2_Init(window);

    // Setup style
    ImGui::StyleColorsDark();



    // Load Fonts
    // (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
    //ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyClean.ttf", 13.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (!done)
    {
        main_loop();
    }
#endif

    // Cleanup
    ImGui_ImplSdlGLES2_Shutdown();
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
