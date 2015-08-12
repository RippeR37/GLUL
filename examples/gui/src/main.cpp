#include <Utils/Logger.h>
#include <Utils/GL+/Program.h>
#include <Utils/GL+/VertexArray.h>
#include <Utils/GL+/VertexBuffer.h>
#include <Utils/GL+/GUI/Button.h>
#include <Utils/GL+/GUI/Font.h>
#include <Utils/GL+/GUI/Text.h>
#include <Utils/GL+/GUI/Window.h>

#include <vector>

/**
 * Font loading helper function
 */
void initFont(GL::GUI::Font& font, const std::string& fontName, int size) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    font.load("assets/fonts/" + fontName + ".ttf", size);
}

/**
 * Main loop
 */
void run() {
    GL::GUI::Window window(800, 600, "Title"); // Be advised - GUI-supporting Window is GL::GUI::Window, not Util::Window !
    
    window.create();
    window.registerEvents();
    window.getContext().setClearColor(glm::vec4(0.1f, 0.1, 0.1, 1.0f));

    // Fonts
    GL::GUI::Font fontArial;
    GL::GUI::Font fontVerdanaI;
    initFont(fontArial, "arial", 16);
    initFont(fontVerdanaI, "verdanai", 18);

    // Text
    GL::GUI::Text text;
    text.setFont(fontVerdanaI);
    text.setText("Hello world! Tab demo: '\t'\n{ std::cout << \"Hello world!\" << std::endl; }");
    text.setColor(glm::vec3(1.0f, 0.7f, 0.3f));
    text.setPosition(glm::vec2(50.0f, 50.0f));
    text.bindTo(window);


    // Buttons
    GL::GUI::Button button(window); // you can specify parent container in constructor
    button.setSize(glm::vec2(150.0f, 30.0f));
    button.setColor(glm::vec3(0.12f, 0.625f, 1.0f));
    button.setPosition(glm::vec2(50.0f, 140.0f));
    button.border = GL::GUI::Style::Border(1, -2, glm::vec3(1.0f, 0.0f, 0.0f)); // make sure you invalidate component after changing border!
        button.text.setFont(fontArial);
        button.text.setText("Press me #1");
        button.text.setColor(glm::vec3(1.0f));
        button.text.setAlignment(GL::GUI::Style::HorizontalAlignment::Left, GL::GUI::Style::VerticalAlignment::Top);

    GL::GUI::Button button2(window);
    button2.setSize(glm::vec2(150.0f, 30.0f));
    button2.setColor(glm::vec3(0.12f, 0.625f, 1.0f));
    button2.setPosition(glm::vec2(50.0f, 180.0f));
    button2.border = GL::GUI::Style::Border(2, 0, glm::vec3(0.3f, 0.7f, 1.0f)); // make sure you invalidate component after changing border!
        button2.text.setFont(fontArial);
        button2.text.setText("Press me #2");
        button2.text.setColor(glm::vec3(1.0f));
        button2.text.setAlignment(GL::GUI::Style::HorizontalAlignment::Center, GL::GUI::Style::VerticalAlignment::Center);

    GL::GUI::Button button3(window);
    button3.setSize(glm::vec2(150.0f, 30.0f));
    button3.setColor(glm::vec3(0.12f, 0.625f, 1.0f));
    button3.setPosition(glm::vec2(50.0f, 220.0f));
    button3.border = GL::GUI::Style::Border(1, 2, glm::vec3(0.0f, 0.0f, 1.0f)); // make sure you invalidate component after changing border!
        button3.text.setFont(fontArial);
        button3.text.setText("Press me #3");
        button3.text.setColor(glm::vec3(1.0f));
        button3.text.setAlignment(GL::GUI::Style::HorizontalAlignment::Right, GL::GUI::Style::VerticalAlignment::Bottom);


    while(window.isCreated() && window.shouldClose() == false) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        window.render();
        window.update();
    }
}

/**
 * Start of application
 */
int main() {
    try {
        run();

    } catch(const Util::Exception::FatalError& exception) {
        Util::Log::Stream("Example", "logExample.log") << "Cought fatal error exception: " + std::string(exception.what());
        return 1;

    } catch(const std::exception& exception) {
        Util::Log::Stream("Example", "logExample.log") << "Cought std::exception: " + std::string(exception.what());
        return 1;

    } catch(...) {
        Util::Log::Stream("Example", "logExample.log") << "Cought unknown exception!";
        return 1;
    }

    return 0;
}
