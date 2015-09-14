#include <GLUL/Logger.h>
#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Button.h>
#include <GLUL/GUI/Checkbox.h>
#include <GLUL/GUI/Font.h>
#include <GLUL/GUI/Text.h>
#include <GLUL/GUI/TextField.h>
#include <GLUL/GUI/Window.h>
#include <GLUL/GUI/Events/MouseClick.h>

#include <vector>
#include <iostream>

/**
 * Font loading helper function
 */
void initFont(GLUL::GUI::Font& font, const std::string& fontName, int size) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    font.load("assets/fonts/" + fontName + ".ttf", size);
}

/**
 * Main loop
 */
void run() {
    GLUL::GUI::Window window(800, 600, "Title"); // Be advised - GUI-supporting Window is GLUL::GUI::Window, not GLUL::Window !
    
    window.create();
    window.registerEvents();
    window.getContext().setClearColor(glm::vec4(0.1f, 0.1, 0.1, 1.0f));

    // Fonts
    GLUL::GUI::Font fontArial;
    GLUL::GUI::Font fontVerdanaI;
    initFont(fontArial, "arial", 16);
    initFont(fontVerdanaI, "verdanai", 18);

    // Text
    GLUL::GUI::Text text;
    text.setFont(fontVerdanaI);
    text.setText("Hello world! Tab demo: '\t'\n{ std::cout << \"Hello world!\" << std::endl; }");
    text.setColor(glm::vec3(1.0f, 0.7f, 0.3f));
    text.setPosition(glm::vec2(50.0f, 50.0f));
    text.bindTo(window);

    GLUL::GUI::Text text2(window);
    text2.setFont(fontArial);
    text2.setText("Buttons\t\t\t\t\t\t\t\t\t Text fields\t\t\t\t\t\t\t\tCheckboxes");
    text2.setColor(glm::vec3(0.3f, 0.7f, 0.7f));
    text2.setPosition(glm::vec2(50.0f, 110.0f));


    // Buttons
    GLUL::GUI::Button button(window); // you can specify parent container in constructor
    button.setSize(glm::vec2(150.0f, 30.0f));
    button.setColor(glm::vec3(0.12f, 0.625f, 1.0f));
    button.setPosition(glm::vec2(50.0f, 140.0f));
    button.border.set(1, -2, glm::vec3(1.0f, 0.0f, 0.0f));
        button.text.setFont(fontArial);
        button.text.setText("Press me #1");
        button.text.setColor(glm::vec3(1.0f));
        button.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Left, GLUL::GUI::Style::VerticalAlignment::Top);

    GLUL::GUI::Button button2(window);
    button2.setSize(glm::vec2(150.0f, 30.0f));
    button2.setColor(glm::vec3(0.12f, 0.625f, 1.0f));
    button2.setPosition(glm::vec2(50.0f, 180.0f));
    button2.border.set(1, 0, glm::vec3(0.3f, 0.7f, 1.0f));
        button2.text.setFont(fontArial);
        button2.text.setText("Press me #2");
        button2.text.setColor(glm::vec3(1.0f));
        button2.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Center, GLUL::GUI::Style::VerticalAlignment::Center);

    GLUL::GUI::Button button3(window);
    button3.setSize(glm::vec2(150.0f, 30.0f));
    button3.setColor(glm::vec3(0.12f, 0.625f, 1.0f));
    button3.setPosition(glm::vec2(50.0f, 220.0f));
    button3.border.set(2, 4, glm::vec3(0.0f, 0.0f, 1.0f));
        button3.text.setFont(fontArial);
        button3.text.setText("Press me #3");
        button3.text.setColor(glm::vec3(1.0f));
        button3.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Right, GLUL::GUI::Style::VerticalAlignment::Bottom);


    // TextField
    GLUL::GUI::TextField textField1(window);
    textField1.setSize(glm::vec2(150.0f, 30.0f));
    textField1.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    textField1.setPosition(glm::vec2(250.0f, 140.0f));
    textField1.border.set(1, 0, glm::vec3(0.0f));
        textField1.text.setFont(fontArial);
        textField1.text.setText("Default text");
        textField1.text.setColor(glm::vec3(0.0f));
        textField1.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Left, GLUL::GUI::Style::VerticalAlignment::Center);


    GLUL::GUI::TextField textField2(window);
    textField2.setSize(glm::vec2(150.0f, 30.0f));
    textField2.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
    textField2.setPosition(glm::vec2(250.0f, 180.0f));
    textField2.border.set(1, 0, glm::vec3(0.0f));
        textField2.text.setFont(fontArial);
        textField2.text.setText("Right alignment");
        textField2.text.setColor(glm::vec3(0.0f));
        textField2.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Right, GLUL::GUI::Style::VerticalAlignment::Center);
    
    // Checkboxes
    GLUL::GUI::Checkbox checkbox1_off(window);
    checkbox1_off.setSize(glm::vec2(20.0f));
    checkbox1_off.setPosition(glm::vec2(450.0f, 140.0f));

    GLUL::GUI::Checkbox checkbox2_off(window);
    checkbox2_off.setSize(glm::vec2(20.0f));
    checkbox2_off.setColor(glm::vec3(0.12f, 0.625f, 1.0f));
    checkbox2_off.setPosition(glm::vec2(480.0f, 140.0f));
    checkbox2_off.border.set(2, 0, glm::vec3(0.0f, 0.0f, 0.0f));

    GLUL::GUI::Checkbox checkbox3_off(window);
    checkbox3_off.setSize(glm::vec2(20.0f));
    checkbox3_off.setColor(glm::vec3(0.2f, 0.2f, 0.2f));
    checkbox3_off.setMarkColor(glm::vec3(0.8f, 0.8f, 0.8f));
    checkbox3_off.setMarkScale(0.7f);
    checkbox3_off.setPosition(glm::vec2(510.0f, 140.0f));
    checkbox3_off.border.set(1, 0, glm::vec3(0.0f, 0.0f, 0.0f));

    GLUL::GUI::Checkbox checkbox1_on(window);
    checkbox1_on.setSize(glm::vec2(20.0f));
    checkbox1_on.setPosition(glm::vec2(450.0f, 170.0f));
    checkbox1_on.setState(true);

    GLUL::GUI::Checkbox checkbox2_on(window, true); // default state can be passed as constructor parameter
    checkbox2_on.setSize(glm::vec2(20.0f));
    checkbox2_on.setColor(glm::vec3(0.12f, 0.625f, 1.0f));
    checkbox2_on.setPosition(glm::vec2(480.0f, 170.0f));
    checkbox2_on.border.set(2, 0, glm::vec3(0.0f, 0.0f, 0.0f));

    GLUL::GUI::Checkbox checkbox3_on(window, true);
    checkbox3_on.setSize(glm::vec2(20.0f));
    checkbox3_on.setColor(glm::vec3(0.2f, 0.2f, 0.2f));
    checkbox3_on.setMarkColor(glm::vec3(0.8f, 0.8f, 0.8f));
    checkbox3_on.setMarkScale(0.7f);
    checkbox3_on.setPosition(glm::vec2(510.0f, 170.0f));
    checkbox3_on.border.set(1, 0, glm::vec3(0.0f, 0.0f, 0.0f));


    /*
     * Possible events:
     * 
     * onMouseClick     click (mouse button down) happens over element
     * onMouseRelease   click (mouse button up) happens over element
     * onMouseEnter     mouse cursor enters element's space on screen (it wasn't last time over it)
     * onMouseLeave     mouse cursor leaves element's space on screen (it was last time but it's not anymore)
     * onMouseMove      mouse cursor moves over element's space on screen (it was and still is over it)
     */
    
    // Add anonymouse custom handler
    button.onMouseRelease += GLUL::GUI::Event::MouseRelease::Handler(
        "b:release", 
        [](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseRelease& mouseReleaseEvent) {
            (void) mouseReleaseEvent;
            GLUL::GUI::Button& button = static_cast<GLUL::GUI::Button&>(component);
            std::cout << "Released mouse over: " << button.text.getText() << std::endl;
        }
    );

    // Create custom onMouseClick handler that can be added to multiple components
    GLUL::GUI::Event::MouseClick::Handler myButtonClickHandler(
        "b:click", 
        [](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseClick& mouseClickEvent) {
            (void) mouseClickEvent;
            GLUL::GUI::Button& button = static_cast<GLUL::GUI::Button&>(component);
            std::cout << "Clicked in: " << button.text.getText() << std::endl;
        }
    );

    button2.onMouseClick += myButtonClickHandler;
    button3.onMouseClick += myButtonClickHandler;

    // Mouse enter/leaves
    button2.onMouseEnter += GLUL::GUI::Event::MouseEnter::Handler(
        "b:enter", 
        [](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseEnter& mouseEnterEvent) {
            (void) mouseEnterEvent;
            GLUL::GUI::Button& button = static_cast<GLUL::GUI::Button&>(component);
            button.setColor(glm::vec3(0.07f, 0.4f, 1.0f));
        }
    );
    button2.onMouseLeave += GLUL::GUI::Event::MouseLeave::Handler(
        "b:leave", 
        [](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseLeave& mouseEnterLeave) {
            (void) mouseEnterLeave;
            GLUL::GUI::Button& button = static_cast<GLUL::GUI::Button&>(component);
            button.setColor(glm::vec3(0.12f, 0.625f, 1.0f));
        }
    );
    

    /////////////////////////////////////////////////////////////////

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

    } catch(const GLUL::Exception::FatalError& exception) {
        GLUL::Log::Stream("Example", "logExample.log") << "Cought fatal error exception: " + std::string(exception.what());
        return 1;

    } catch(const std::exception& exception) {
        GLUL::Log::Stream("Example", "logExample.log") << "Cought std::exception: " + std::string(exception.what());
        return 1;

    } catch(...) {
        GLUL::Log::Stream("Example", "logExample.log") << "Cought unknown exception!";
        return 1;
    }

    return 0;
}
