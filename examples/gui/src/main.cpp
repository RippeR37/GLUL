#include <GLUL/Logger.h>
#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Button.h>
#include <GLUL/GUI/Checkbox.h>
#include <GLUL/GUI/Font.h>
#include <GLUL/GUI/Slider.h>
#include <GLUL/GUI/ProgressBar.h>
#include <GLUL/GUI/Text.h>
#include <GLUL/GUI/TextField.h>
#include <GLUL/GUI/Window.h>
#include <GLUL/GUI/Events/MouseClick.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>


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
    using namespace glm;

    GLUL::GUI::Window window(800, 600, "Title"); // Be advised - GUI-supporting Window is GLUL::GUI::Window, not GLUL::Window !
    
    window.create();
    window.registerEvents();
    window.getContext().setClearColor(vec4(0.1f, 0.1f, 0.1f, 1.0f));

    // Fonts
    GLUL::GUI::Font fontArial;
    GLUL::GUI::Font fontVerdanaI;
    initFont(fontArial, "arial", 16);
    initFont(fontVerdanaI, "verdanai", 18);

    // Text
    GLUL::GUI::Text text;
    text.setFont(fontVerdanaI).setColor(vec3(1.0f, 0.7f, 0.3f)).setPosition(vec2(50.0f, 50.0f));
    text.setText("Hello world! Tab demo: '\t'\n{ std::cout << \"Hello world!\" << std::endl; }");
    text.bindTo(window);

    GLUL::GUI::Text text2(window);
    text2.setFont(fontArial).setColor(vec3(0.3f, 0.7f, 0.7f)).setPosition(vec2(50.0f, 110.0f));
    text2.setText("Buttons\t\t\t\t\t\t\t\t\t Text fields\t\t\t\t\t\t\t\tCheckboxes");


    // Buttons
    GLUL::GUI::Button button(window); // you can specify parent container in constructor
    button.setSize(vec2(150.0f, 30.0f)).setColor(vec3(0.12f, 0.625f, 1.0f)).setPosition(vec2(50.0f, 140.0f));
    button.border.set(1, -2, vec3(1.0f, 0.0f, 0.0f));
    button.text.setFont(fontArial).setText("Press me #1").setColor(vec3(1.0f));
    button.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Left, GLUL::GUI::Style::VerticalAlignment::Top);

    GLUL::GUI::Button button2(window);
    button2.setSize(vec2(150.0f, 30.0f)).setColor(vec3(0.12f, 0.625f, 1.0f)).setPosition(vec2(50.0f, 180.0f));
    button2.border.set(1, 0, vec3(0.3f, 0.7f, 1.0f));
    button2.text.setFont(fontArial).setText("Press me #2").setColor(vec3(1.0f));
    button2.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Center, GLUL::GUI::Style::VerticalAlignment::Center);

    GLUL::GUI::Button button3(window);
    button3.setSize(vec2(150.0f, 30.0f)).setColor(vec3(0.12f, 0.625f, 1.0f)).setPosition(vec2(50.0f, 220.0f));
    button3.border.set(2, 4, vec3(0.0f, 0.0f, 1.0f));
    button3.text.setFont(fontArial).setText("Press me #3").setColor(vec3(1.0f));
    button3.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Right, GLUL::GUI::Style::VerticalAlignment::Bottom);


    // TextField
    GLUL::GUI::TextField textField1(window);
    textField1.setSize(vec2(150.0f, 30.0f)).setColor(vec3(1.0f)).setPosition(vec2(250.0f, 140.0f));
    textField1.border.set(1, 0, vec3(0.0f));
    textField1.text.setFont(fontArial).setText("Default text").setColor(vec3(0.0f));
    textField1.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Left, GLUL::GUI::Style::VerticalAlignment::Center);

    GLUL::GUI::TextField textField2(window);
    textField2.setSize(vec2(150.0f, 30.0f)).setColor(vec3(1.0f)).setPosition(vec2(250.0f, 180.0f));
    textField2.border.set(1, 0, vec3(0.0f));
    textField2.text.setFont(fontArial).setText("Right alignment").setColor(vec3(0.0f));
    textField2.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Right, GLUL::GUI::Style::VerticalAlignment::Center);
    

    // Checkboxes
    GLUL::GUI::Checkbox checkbox1_off(window);
    checkbox1_off.setSize(vec2(20.0f)).setPosition(vec2(450.0f, 140.0f));

    GLUL::GUI::Checkbox checkbox2_off(window);
    checkbox2_off.setSize(vec2(20.0f)).setColor(vec3(0.12f, 0.625f, 1.0f)).setPosition(vec2(480.0f, 140.0f));
    checkbox2_off.border.set(2, 0, vec3(0.0f));

    GLUL::GUI::Checkbox checkbox3_off(window);
    checkbox3_off.setSize(vec2(20.0f)).setColor(vec3(0.2f, 0.2f, 0.2f)).setPosition(vec2(510.0f, 140.0f));
    checkbox3_off.setMarkColor(vec3(0.8f, 0.8f, 0.8f)).setMarkScale(0.7f);
    checkbox3_off.border.set(1, 0, vec3(0.0f));


    GLUL::GUI::Checkbox checkbox1_on(window);
    checkbox1_on.setSize(vec2(20.0f)).setPosition(vec2(450.0f, 170.0f)).setState(true);

    GLUL::GUI::Checkbox checkbox2_on(window, true); // default state can be passed as constructor parameter
    checkbox2_on.setSize(vec2(20.0f)).setColor(vec3(0.12f, 0.625f, 1.0f)).setPosition(vec2(480.0f, 170.0f));
    checkbox2_on.border.set(2, 0, vec3(0.0f));

    GLUL::GUI::Checkbox checkbox3_on(window, true);
    checkbox3_on.setSize(vec2(20.0f)).setColor(vec3(0.2f, 0.2f, 0.2f)).setPosition(vec2(510.0f, 170.0f));
    checkbox3_on.setMarkColor(vec3(0.8f, 0.8f, 0.8f)).setMarkScale(0.7f);
    checkbox3_on.border.set(1, 0, vec3(0.0f));

    
    // Progress bar
    GLUL::GUI::Text progressbar_header(window), progressbar1_text(window);
    progressbar_header.setFont(fontArial).setColor(vec3(0.3f, 0.7f, 0.7f));
    progressbar_header.setPosition(vec2(50.0f, 280.0f)).setText("Progress bar");
    progressbar1_text.setFont(fontArial).setPosition(vec2(210.0f, 310.0f)).setText("0 %");

    GLUL::GUI::ProgressBar progressbar1(window, 0.0f);
    progressbar1.setSize(vec2(150.0f, 20.0f)).setPosition(vec2(50.0f, 310.0f));
    progressbar1.setColor(vec3(0.12f, 0.625f, 1.0f)).setBackgroundColor(vec3(0.2f));
    progressbar1.border.set(1, 0, vec3(0.0f));


    // Sliders
    GLUL::GUI::Text slider_header(window);
    slider_header.setFont(fontArial).setColor(vec3(0.3f, 0.7f, 0.7f));
    slider_header.setPosition(vec2(50.0f, 350.0f)).setText("Sliders");

    GLUL::GUI::Slider slider1(window, 0.0f, 1.0f, 0.5f);
    slider1.setSize(vec2(150.0f, 20.0f)).setPosition(vec2(50.0f, 380.0f));
    slider1.setColor(vec3(0.12f, 0.625f, 1.0f)).setBackgroundColor(vec3(0.2f));
    slider1.border.set(1, 0, vec3(0.0f));

    GLUL::GUI::Slider slider2(window, -1.5f, 6.5f, 0.0f);
    slider2.setSize(vec2(150.0f, 20.0f)).setPosition(vec2(250.0f, 380.0f));
    slider2.setColor(vec3(0.12f, 0.625f, 1.0f)).setBackgroundColor(vec3(0.2f));
    slider2.border.set(1, 0, vec3(0.0f));

    GLUL::GUI::Slider slider3(window, 0.0f, 5.0f, 0.0f);
    slider3.setSize(vec2(150.0f, 20.0f)).setPosition(vec2(450.0f, 380.0f));
    slider3.setColor(vec3(0.12f, 0.625f, 1.0f)).setBackgroundColor(vec3(0.2f));
    slider3.restrictValuesToIntegers(true).border.set(1, 0, vec3(0.0f));


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
            button.setColor(vec3(0.07f, 0.4f, 1.0f));
        }
    );
    button2.onMouseLeave += GLUL::GUI::Event::MouseLeave::Handler(
        "b:leave", 
        [](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseLeave& mouseEnterLeave) {
            (void) mouseEnterLeave;
            GLUL::GUI::Button& button = static_cast<GLUL::GUI::Button&>(component);
            button.setColor(vec3(0.12f, 0.625f, 1.0f));
        }
    );
    

    /////////////////////////////////////////////////////////////////

    GLUL::Clock clock;

    while(window.isCreated() && window.shouldClose() == false) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        window.render();
        window.update();

        {
            const float progressCycleTime = 5.0f; // reaches 100% in 5 seconds
            float frameTime = clock.getElapsedTime().asSeconds<float>(), progressInt;
            float progressValue = progressbar1.getProgress();

            progressValue += frameTime / progressCycleTime;
            progressValue = std::modf(progressValue, &progressInt);
            
            progressbar1.setProgress(progressValue);
            progressbar1_text.setText(std::to_string(static_cast<int>(std::ceil(progressValue * 100.0f))) + " %");
        }
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
