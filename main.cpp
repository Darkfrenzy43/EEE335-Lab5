#include <gtkmm.h>
#include "SimulationView.h"


int main(int argc, char *argv[])
{
	srand(0);

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.gtkmm.lab5");

	SimulationView window;

	return app->run(window);
}
