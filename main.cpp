#include <gtkmm.h>
#include <vector>
#include <iostream>

class MyArea : public Gtk::DrawingArea {
public:
    MyArea() {
        // Setup event handlers for drawing
        add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK);
        current_color.set_rgba(0.0, 0.0, 0.0); // Default color is black
    }

    void set_color(const Gdk::RGBA& color) {
        current_color = color;
    }

    void clear() {
        lines.clear();
        queue_draw(); // Request a redraw of the widget
    }

protected:
    std::vector<std::vector<std::pair<Gdk::Point, Gdk::RGBA>>> lines;
    std::vector<std::pair<Gdk::Point, Gdk::RGBA>> current_line;
    Gdk::RGBA current_color;

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
        for (const auto& line : lines) {
            if (line.size() > 1) {
                cr->set_line_width(2.0);
                cr->set_source_rgba(line[0].second.get_red(), line[0].second.get_green(), line[0].second.get_blue(), line[0].second.get_alpha());
                cr->move_to(line[0].first.get_x(), line[0].first.get_y());
                for (unsigned int i = 1; i < line.size(); ++i) {
                    cr->line_to(line[i].first.get_x(), line[i].first.get_y());
                }
                cr->stroke();
            }
        }
        return true;
    }

    bool on_button_press_event(GdkEventButton* event) override {
        if (event->button == 1) {
            current_line.clear();
            current_line.push_back({Gdk::Point(event->x, event->y), current_color});
            lines.push_back(current_line);
        }
        return true;
    }

    bool on_motion_notify_event(GdkEventMotion* event) override {
        if (event->state & GDK_BUTTON1_MASK) {
            lines.back().push_back({Gdk::Point(event->x, event->y), current_color});
            queue_draw(); // Request a redraw of the widget
        }
        return true;
    }
};


int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "com.rijalasepnugroho");

    Gtk::Window window;
    window.set_default_size(800, 600);

    Gtk::Box vbox(Gtk::ORIENTATION_VERTICAL);
    window.add(vbox);

    MyArea area;
    vbox.pack_start(area);

    Gtk::Button button("Clear");
    button.signal_clicked().connect([&]() {
        area.clear();
    });
    vbox.pack_start(button, Gtk::PACK_SHRINK);

    Gtk::ColorButton color_button;
    color_button.signal_color_set().connect([&]() {
        Gdk::RGBA color = color_button.get_rgba();
        area.set_color(color);
    });
    vbox.pack_start(color_button, Gtk::PACK_SHRINK);

    window.show_all_children();

    return app->run(window);
}
