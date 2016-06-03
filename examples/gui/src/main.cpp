#include <GLUL/Logger.h>
#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>
#include <GLUL/GUI/Button.h>
#include <GLUL/GUI/Checkbox.h>
#include <GLUL/GUI/Slider.h>
#include <GLUL/GUI/Panel.h>
#include <GLUL/GUI/ProgressBar.h>
#include <GLUL/GUI/RadioButton.h>
#include <GLUL/GUI/RadioButtonGroup.h>
#include <GLUL/GUI/TextField.h>
#include <GLUL/GUI/Window.h>
#include <GLUL/Resource/Font.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>


/**
 * Main loop
 */
void run() {
    using namespace GLUL::GUI;

    GLUL::GUI::Window window(800, 600, "Title"); // Be advised - GUI-supporting Window is GLUL::GUI::Window, not GLUL::Window !
    window.create();
    window.registerEvents();
    window.getContext().setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

    /*
    GLUL::G2D::Font& defaultFont = GLUL::Resource::Font::GetDefault(16);

    // Buttons
    auto& button1 = window.add<Button>();
    auto& button2 = window.add<Button>();
    auto& button3 = window.add<Button>();

    // TextField
    auto& textField1 = window.add<TextField>();
    auto& textField2 = window.add<TextField>();
    auto& textField3 = window.add<TextField>();

    // Checkboxes
    auto& checkbox1_on  = window.add<Checkbox>(true);
    auto& checkbox2_on  = window.add<Checkbox>(true);
    auto& checkbox3_on  = window.add<Checkbox>(true);
    auto& checkbox1_off = window.add<Checkbox>(false);
    auto& checkbox2_off = window.add<Checkbox>(false);
    auto& checkbox3_off = window.add<Checkbox>(false);

    // Radio buttons
    auto& rbGroup = window.add<RadioButtonGroup>();     // RadioButtonGroup creates (and manages lifetime) radio buttons
    auto& rbutton1 = rbGroup.add();                     // When it's destroyed, it removes all created (and not yet removed) radio buttons
    auto& rbutton2 = rbGroup.add(true);                 // Only one radio button can be selected at any time (and one is always set)
    auto& rbutton3 = rbGroup.add();                     // To remove (and destroy) radio button, use rbGroup.remove(rbuttonX)

    // Progress bar
    auto& progressBar = window.add<ProgressBar>();

    // Sliders
    auto& slider1 = window.add<ProgressBar>();
    auto& slider2 = window.add<ProgressBar>();
    auto& slider3 = window.add<ProgressBar>();
    auto& slider4 = window.add<ProgressBar>();

    // Panels
    auto& panel = window.add<Panel>();
    auto& panelButton = panel.add<Button>();


    //
    // Event handlers
    //

    // Add anonymouse custom handler
    button1.onMouseRelease += GLUL::GUI::Event::MouseRelease::Handler(
        "b1:release",
        [](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseRelease& mouseReleaseEvent) {
            (void) mouseReleaseEvent;
            GLUL::GUI::Button& button = static_cast<GLUL::GUI::Button&>(component);
            // TODO: std::cout << "Released mouse over: " << ? << std::endl;
        }
    );

    // Create custom MouseClick handler that can be added to multiple components
    GLUL::GUI::Event::MouseClick::Handler myButtonClickHandler(
        "b2_b3:click",
        [](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseClick& mouseClickEvent) {
            (void) mouseClickEvent;
            GLUL::GUI::Button& button = static_cast<GLUL::GUI::Button&>(component);
            // TODO: std::cout << "Clicked in: " << ? << std::endl;
        }
    );

    button2.onMouseClick += myButtonClickHandler;
    button3.onMouseClick += myButtonClickHandler;

    // Mouse enter/leaves
    button2.onMouseEnter += GLUL::GUI::Event::MouseEnter::Handler(
        "b2:enter",
        [](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseEnter& mouseEnterEvent) {
            (void) mouseEnterEvent;
            GLUL::GUI::Button& button = static_cast<GLUL::GUI::Button&>(component);
            // TODO:
        }
    );
    button2.onMouseLeave += GLUL::GUI::Event::MouseLeave::Handler(
        "b2:leave",
        [](GLUL::GUI::Component& component, const GLUL::GUI::Event::MouseLeave& mouseEnterLeave) {
            (void) mouseEnterLeave;
            GLUL::GUI::Button& button = static_cast<GLUL::GUI::Button&>(component);
            // TODO:
        }
    );

    progressBar.onValueChange += GLUL::GUI::Event::ValueChange<float>::Handler(
        "pb:valueChange",
        [&](GLUL::GUI::Component& component, const GLUL::GUI::Event::ValueChange<float>& valueChangeEvent) {
            (void) component;
            (void) valueChangeEvent;
            // TODO:
        }
    );


    //
    // State update functions
    //
    auto progressbar_update = [&] {
        static GLUL::Clock clock;
        float progressCycleTime = 5.0f; // reaches 100% in 5 seconds
        float frameTime = clock.getElapsedTime().asSeconds<float>(), progressInt;
        float progressValue = progressBar.getProgress();

        progressValue += frameTime / progressCycleTime;
        progressValue = std::modf(progressValue, &progressInt);

        progressBar.setProgress(progressValue);
    };
    */


    /////////////////////////////////////////////////////////////////
    ///                         MAIN LOOP                         ///
    /////////////////////////////////////////////////////////////////

    while(window.isCreated() && window.shouldClose() == false) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        // progressbar_update();

        window.render();
        window.update();
    }

    GLUL::Resource::Font::ReleaseDefault(16);
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
