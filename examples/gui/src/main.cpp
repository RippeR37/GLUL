#include <GLUL/Logger.h>
#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Button.h>
#include <GLUL/GUI/Checkbox.h>
#include <GLUL/GUI/Font.h>
#include <GLUL/GUI/Slider.h>
#include <GLUL/GUI/Panel.h>
#include <GLUL/GUI/ProgressBar.h>
#include <GLUL/GUI/RadioButton.h>
#include <GLUL/GUI/RadioButtonGroup.h>
#include <GLUL/GUI/Text.h>
#include <GLUL/GUI/TextField.h>
#include <GLUL/GUI/Window.h>

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
    GLUL::GUI::Window window(800, 600, "Title"); // Be advised - GUI-supporting Window is GLUL::GUI::Window, not GLUL::Window !
    window.create();
    window.registerEvents();
    window.getContext().setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });


    // Fonts
    GLUL::GUI::Font fontArial;
    GLUL::GUI::Font fontVerdanaI;
    initFont(fontArial, "arial", 16);
    initFont(fontVerdanaI, "verdanai", 18);


    // Text
    GLUL::GUI::Text text;
    text.setFont(fontVerdanaI).setColor({ 1.0f, 0.7f, 0.3f }).setPosition({ 50.0f, 50.0f });
    text.setText("Hello world! Tab demo: '\t'\n{ std::cout << \"Hello world!\" << std::endl; }");
    text.bindTo(window);

    GLUL::GUI::Text text2(window);
    text2.setFont(fontArial).setColor({ 0.3f, 0.7f, 0.7f }).setPosition({ 50.0f, 110.0f });
    text2.setText("Buttons\t\t\t\t\t\t\t\t\t Text fields\t\t\t\t\t\t\t\tCheckboxes\t\t\tRadio buttons");


    // Buttons
    GLUL::GUI::Button button(window); // you can specify parent container in constructor
    button.setSize({ 150.0f, 30.0f }).setColor({ 0.12f, 0.625f, 1.0f }).setPosition({ 50.0f, 140.0f });
    button.border.set(1, -2, { 1.0f, 0.0f, 0.0f });
    button.text.setFont(fontArial).setText("Press me #1").setColor({ 1.0f, 1.0f, 1.0f });
    button.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Left, GLUL::GUI::Style::VerticalAlignment::Top);

    GLUL::GUI::Button button2(window);
    button2.setSize({ 150.0f, 30.0f }).setColor({ 0.12f, 0.625f, 1.0f }).setPosition({ 50.0f, 180.0f });
    button2.border.set(1, 0, { 0.3f, 0.7f, 1.0f });
    button2.text.setFont(fontArial).setText("Press me #2").setColor({ 1.0f, 1.0f, 1.0f });
    button2.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Center, GLUL::GUI::Style::VerticalAlignment::Center);

    GLUL::GUI::Button button3(window);
    button3.setSize({ 150.0f, 30.0f }).setColor({ 0.12f, 0.625f, 1.0f }).setPosition({ 50.0f, 220.0f });
    button3.border.set(2, 4, { 0.0f, 0.0f, 1.0f });
    button3.text.setFont(fontArial).setText("Press me #3").setColor({ 1.0f, 1.0f, 1.0f });
    button3.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Right, GLUL::GUI::Style::VerticalAlignment::Bottom);


    // TextField
    GLUL::GUI::TextField textField1(window);
    textField1.setSize({ 150.0f, 30.0f }).setColor({ 1.0f, 1.0f, 1.0f }).setPosition({ 250.0f, 140.0f });
    textField1.border.set(1, 0, { 0.0f, 0.0f, 0.0f });
    textField1.text.setFont(fontArial).setText("Default text").setColor({ 0.0f, 0.0f, 0.0f });
    textField1.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Left, GLUL::GUI::Style::VerticalAlignment::Center);

    GLUL::GUI::TextField textField2(window);
    textField2.setSize({ 150.0f, 30.0f }).setColor({ 1.0f, 1.0f, 1.0f }).setPosition({ 250.0f, 180.0f });
    textField2.border.set(1, 0, { 0.0f, 0.0f, 0.0f });
    textField2.text.setFont(fontArial).setText("Right alignment").setColor({ 0.0f, 0.0f, 0.0f });
    textField2.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Right, GLUL::GUI::Style::VerticalAlignment::Center);


    // Checkboxes
    GLUL::GUI::Checkbox checkbox1_off(window);
    checkbox1_off.setSize({ 20.0f, 20.0f }).setPosition({ 450.0f, 140.0f });

    GLUL::GUI::Checkbox checkbox2_off(window);
    checkbox2_off.setSize({ 20.0f, 20.0f }).setColor({ 0.12f, 0.625f, 1.0f }).setPosition({ 480.0f, 140.0f });
    checkbox2_off.border.set(2, 0, { 0.0f, 0.0f, 0.0f });

    GLUL::GUI::Checkbox checkbox3_off(window);
    checkbox3_off.setSize({ 20.0f, 20.0f }).setColor({ 0.2f, 0.2f, 0.2f }).setPosition({ 510.0f, 140.0f });
    checkbox3_off.setMarkColor({ 0.8f, 0.8f, 0.8f }).setMarkScale(0.7f);
    checkbox3_off.border.set(1, 0, { 0.0f, 0.0f, 0.0f });

    GLUL::GUI::Checkbox checkbox1_on(window);
    checkbox1_on.setSize({ 20.0f, 20.0f }).setPosition({ 450.0f, 170.0f }).setState(true);

    GLUL::GUI::Checkbox checkbox2_on(window, true); // default state can be passed as constructor parameter
    checkbox2_on.setSize({ 20.0f, 20.0f }).setColor({ 0.12f, 0.625f, 1.0f }).setPosition({ 480.0f, 170.0f });
    checkbox2_on.border.set(2, 0, { 0.0f, 0.0f, 0.0f });

    GLUL::GUI::Checkbox checkbox3_on(window, true);
    checkbox3_on.setSize({ 20.0f, 20.0f }).setColor({ 0.2f, 0.2f, 0.2f }).setPosition({ 510.0f, 170.0f });
    checkbox3_on.setMarkColor({ 0.8f, 0.8f, 0.8f }).setMarkScale(0.7f);
    checkbox3_on.border.set(1, 0, { 0.0f, 0.0f, 0.0f });


    // Radio buttons
    GLUL::GUI::Text rbLabels(window);
    GLUL::GUI::RadioButtonGroup rbGroup(window);                // RadioButtonGroup creates (and manages lifetime) radio buttons
    GLUL::GUI::RadioButton& rbutton1 = rbGroup.create();        // When it's destroyed, it removes all created (and not yet removed) radio buttons
    GLUL::GUI::RadioButton& rbutton2 = rbGroup.create().set();  // Only one radio button can be selected at any time
    GLUL::GUI::RadioButton& rbutton3 = rbGroup.create();        // And if there is at least one, then one is always selected

    rbutton1.setSize({ 20.0f, 20.0f }).setPosition({ 585.0f, 140.0f }).setColor({ 0.12f, 0.625f, 1.0f });
    rbutton2.setSize({ 20.0f, 20.0f }).setPosition({ 585.0f, 177.0f }).setColor({ 0.12f, 0.625f, 1.0f });
    rbutton3.setSize({ 20.0f, 20.0f }).setPosition({ 585.0f, 212.0f }).setColor({ 0.12f, 0.625f, 1.0f });

    // To remove (and destroy) radio button, use
    // rbGroup.remove(rbuttonX); if it's currently selected, another one ('oldest') will be set instead

    rbLabels
        .setFont(fontArial).setColor({ 0.7f, 0.7f, 0.7f }).setPosition({ 615.0f, 142.0f })
        .setText("only \n\none \n\nchecked");


    // Progress bar
    GLUL::GUI::Text progressbar_header(window), progressbar1_text(window);
    progressbar_header.setFont(fontArial).setColor({ 0.3f, 0.7f, 0.7f });
    progressbar_header.setPosition({ 50.0f, 280.0f }).setText("Progress bar");
    progressbar1_text.setFont(fontArial).setPosition({ 210.0f, 310.0f }).setText("0 %");

    GLUL::GUI::ProgressBar progressbar1(window, 0.0f);
    progressbar1.setSize({ 150.0f, 20.0f }).setPosition({ 50.0f, 310.0f });
    progressbar1.setColor({ 0.12f, 0.625f, 1.0f }).setBackgroundColor({ 0.2f, 0.2f, 0.2f });
    progressbar1.border.set(1, 0, { 0.0f, 0.0f, 0.0f });


    // Sliders
    GLUL::GUI::Text slider_header(window);
    slider_header.setFont(fontArial).setColor({ 0.3f, 0.7f, 0.7f });
    slider_header.setPosition({ 50.0f, 350.0f }).setText("Sliders");

    GLUL::GUI::Slider slider1(window, GLUL::GUI::Style::Orientation::Horizontal, 0.0f, 1.0f, 0.5f);
    slider1.setSize({ 150.0f, 20.0f }).setPosition({ 50.0f, 380.0f });
    slider1.setHandleColor({ 0.12f, 0.625f, 1.0f }).setBackgroundColor({ 0.2f, 0.2f, 0.2f });
    slider1.border.set(1, 0, { 0.0f, 0.0f, 0.0f });
    slider1.handleBorder.set(1, 0, { 0.0f, 0.0f, 0.0f });

    GLUL::GUI::Slider slider2(window, GLUL::GUI::Style::Orientation::Horizontal, -1.5f, 6.5f, 0.0f);
    slider2.setSize({ 150.0f, 20.0f }).setPosition({ 215.0f, 380.0f });
    slider2.setHandleSize({ slider2.getHandleSize().x, slider2.getSize().y });
    slider2.setHandleColor({ 0.12f, 0.625f, 1.0f }).setBackgroundColor({ 0.0f, 0.0f, 0.0f, 0.0f });
    slider2.setLineColor({ 0.2f, 0.2f, 0.2f, 1.0f }).handleBorder.set(1, 0, { 0.0f, 0.0f, 0.0f });

    GLUL::GUI::Slider slider3(window, GLUL::GUI::Style::Orientation::Horizontal, 0.0f, 5.0f, 0.0f);
    slider3.setSize({ 150.0f, 20.0f }).setPosition({ 380.0f, 380.0f });
    slider3.setHandleColor({ 0.12f, 0.625f, 1.0f }).setBackgroundColor({ 0.2f, 0.2f, 0.2f });
    slider3.restrictValuesToIntegers(true).border.set(1, 0, { 0.0f, 0.0f, 0.0f });
    slider3.handleBorder.set(1, 0, { 0.0f, 0.0f, 0.0f });

    GLUL::GUI::Slider slider4(window, GLUL::GUI::Style::Orientation::Vertical);
    slider4.setSize({ 20.0f, 150.0f }).setPosition({ 545.0f, 250.0f }).border.set(1, 0, { 0.0f, 0.0f, 0.0f });
    slider4.setHandleColor({ 0.12f, 0.625f, 1.0f }).setBackgroundColor({ 0.2f, 0.2f, 0.2f });
    slider4.handleBorder.set(1, 0, { 0.0f, 0.0f, 0.0f });



    // Panels
    GLUL::GUI::Panel panel(window, { 100.0f, 450.0f }, { 600.0f, 100.0f }, { 900.0f, 400.0f });
    GLUL::GUI::Button panelButton(panel);
    panelButton.setSize({ 150.0f, 30.0f }).setPosition({ 250.0f, 30.0f }).setColor({ 0.3f, 0.3f, 0.3f });
    panelButton.text.setFont(fontArial).setText("Press me").setColor({ 1.0f, 1.0f, 1.0f });
    panelButton.text.setAlignment(GLUL::GUI::Style::HorizontalAlignment::Center, GLUL::GUI::Style::VerticalAlignment::Center);


    //
    // Event handlers
    //

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
            button.setColor({ 0.07f, 0.4f, 1.0f });
        }
    );
    button2.onMouseLeave += GLUL::GUI::Event::MouseLeave::Handler(
        "b:leave",
        [](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseLeave& mouseEnterLeave) {
            (void) mouseEnterLeave;
            GLUL::GUI::Button& button = static_cast<GLUL::GUI::Button&>(component);
            button.setColor({ 0.12f, 0.625f, 1.0f });
        }
    );

    progressbar1.onValueChange += GLUL::GUI::Event::ValueChange<float>::Handler(
        "p1:valueChange",
        [&progressbar1_text](GLUL::GUI::Component& component, const GLUL::GUI::Event::ValueChange<float>& valueChangeEvent) {
            (void) component; // unused

            int progressValue = static_cast<int>(std::ceil(valueChangeEvent.newValue * 100.0f));
            std::string valueText = std::to_string(progressValue) + "%";

            progressbar1_text.setText(valueText);
        }
    );


    //
    // State update functions
    //
    auto progressbar_update = [&] {
        static GLUL::Clock clock;
        float progressCycleTime = 5.0f; // reaches 100% in 5 seconds
        float frameTime = clock.getElapsedTime().asSeconds<float>(), progressInt;
        float progressValue = progressbar1.getProgress();

        progressValue += frameTime / progressCycleTime;
        progressValue = std::modf(progressValue, &progressInt);

        progressbar1.setProgress(progressValue);
    };

    /////////////////////////////////////////////////////////////////
    ///                         MAIN LOOP                         ///
    /////////////////////////////////////////////////////////////////

    while(window.isCreated() && window.shouldClose() == false) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        progressbar_update();

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
