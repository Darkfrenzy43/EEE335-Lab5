#include "SimulationView.h"
#include "config.h"
#include "Simulation.h"
#include <iostream>
#include <string>


SimulationView::SimulationView()
{
	buildGui();
	simulation = new Simulation(this, comboPra->get_active_text());
	runningState = new Running(this);
	pausedState = new Paused(this);
	completedState = new Completed(this);
	setState(pausedState);
}


SimulationView::~SimulationView()
{
	delete runningState;
	delete pausedState;
	delete completedState;
}


void SimulationView::buildGui()
{
	this->set_default_size(400, 200);
	this->set_title("Page Replacement");

	Gtk::Grid *grid = Gtk::manage(new Gtk::Grid());
	grid->set_border_width(10);
	grid->set_column_spacing(50);
	grid->set_row_spacing(5);
	this->add(*grid);

	Gtk::Box *box1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	Gtk::Box *box2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	Gtk::Box *box3 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	Gtk::Box *box4 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	Gtk::Box *box5 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	Gtk::Box *box6 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	Gtk::Box *box7 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
	Gtk::Box *box8 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));

	box1->set_halign(Gtk::ALIGN_START);
	box2->set_halign(Gtk::ALIGN_START);
	box3->set_halign(Gtk::ALIGN_START);
	box4->set_halign(Gtk::ALIGN_START);
	box5->set_halign(Gtk::ALIGN_START);
	box6->set_halign(Gtk::ALIGN_START);
	box7->set_halign(Gtk::ALIGN_CENTER);
	box8->set_halign(Gtk::ALIGN_CENTER);

	grid->attach(*box1, 0, 0, 1, 1);
	grid->attach(*box2, 1, 0, 1, 1);
	grid->attach(*box3, 0, 1, 1, 1);
	grid->attach(*box4, 1, 1, 1, 1);
	grid->attach(*box5, 0, 2, 1, 1);
	grid->attach(*box6, 1, 2, 1, 1);
	grid->attach(*box7, 0, 3, 1, 1);
	grid->attach(*box8, 1, 3, 1, 1);


	// Box 1
	btnStartPause = Gtk::manage(new Gtk::Button("Start"));
	btnStep = Gtk::manage(new Gtk::Button("Step"));
	btnReset = Gtk::manage(new Gtk::Button("Reset"));
	btnStartPause->set_size_request(80,-1);
	btnStep->set_size_request(80,-1);
	btnReset->set_size_request(80,-1);
	box1->pack_start(*btnStartPause, Gtk::PACK_EXPAND_PADDING, 0);
	box1->pack_start(*btnStep, Gtk::PACK_EXPAND_PADDING, 0);
	box1->pack_start(*btnReset, Gtk::PACK_EXPAND_PADDING, 0);

	btnStartPause->signal_clicked().connect(sigc::mem_fun(*this, &SimulationView::onBtnStartPauseClicked));
	btnStep->signal_clicked().connect(sigc::mem_fun(*this, &SimulationView::onBtnStepClicked));
	btnReset->signal_clicked().connect(sigc::mem_fun(*this, &SimulationView::onBtnResetClicked));


	// Box 2
	Gtk::Label *labelPra = Gtk::manage(new Gtk::Label("PRA"));
	labelPra->set_size_request(60, -1);
	labelPra->set_alignment(0,0.5);
	comboPra = Gtk::manage(new Gtk::ComboBoxText());
	comboPra->append("Random");
	comboPra->append("FIFO");
	comboPra->append("Second Chance");
	comboPra->append("Clock");
	comboPra->append("NRU");
	comboPra->append("Working Set");
	comboPra->set_active(0);
	comboPra->signal_changed().connect(sigc::mem_fun(*this, &SimulationView::onComboPraChanged));
	box2->pack_start(*labelPra, Gtk::PACK_EXPAND_PADDING, 0);
	box2->pack_start(*comboPra, Gtk::PACK_EXPAND_PADDING, 0);


	// Box 3
	Gtk::Label *labelTurnCount = Gtk::manage(new Gtk::Label("Sim turn:", Gtk::ALIGN_START));
	labelTurnCount->set_size_request(100, -1);
	labelTurnCount->set_alignment(0,0.5);
	labelTurnCount2 = Gtk::manage(new Gtk::Label("0"));
	box3->pack_start(*labelTurnCount, Gtk::PACK_EXPAND_PADDING, 0);
	box3->pack_start(*labelTurnCount2, Gtk::PACK_EXPAND_PADDING, 0);


	// Box 4
	Gtk::Label *labelSpeed = Gtk::manage(new Gtk::Label("Speed"));
	labelSpeed->set_size_request(60, -1);
	labelSpeed->set_alignment(0,0.5);
	comboSpeed = Gtk::manage(new Gtk::ComboBoxText());
	comboSpeed->append("Normal");
	comboSpeed->append("Fast");
	comboSpeed->append("Turbo");
	comboSpeed->set_active_text(DEFAULT_SPEED);
	comboSpeed->signal_changed().connect(sigc::mem_fun(*this, &SimulationView::onSimSpeedChanged));
	onSimSpeedChanged();
	box4->pack_start(*labelSpeed, Gtk::PACK_EXPAND_PADDING, 0);
	box4->pack_start(*comboSpeed, Gtk::PACK_EXPAND_PADDING, 0);


	// Box 5
	Gtk::Label *labelPageFault = Gtk::manage(new Gtk::Label("Page fault:"));
	labelPageFault->set_size_request(100, -1);
	labelPageFault->set_alignment(0,0.5);
	labelPageFault2 = Gtk::manage(new Gtk::Label("0"));
	box5->pack_start(*labelPageFault, Gtk::PACK_EXPAND_PADDING, 0);
	box5->pack_start(*labelPageFault2, Gtk::PACK_EXPAND_PADDING, 0);


	// Box 6
	Gtk::Label *labelRunFor = Gtk::manage(new Gtk::Label("Stop at"));
	labelRunFor->set_size_request(60, -1);
	labelRunFor->set_alignment(0,0.5);
	comboRunFor = Gtk::manage(new Gtk::ComboBoxText());
	comboRunFor->append(std::to_string(RUN_FOR_CHOICE_1));
	comboRunFor->append(std::to_string(RUN_FOR_CHOICE_2));
	comboRunFor->append(std::to_string(RUN_FOR_CHOICE_3));
	comboRunFor->set_active_text(std::to_string(DEFAULT_RUN_FOR));
	comboRunFor->signal_changed().connect(sigc::mem_fun(*this, &SimulationView::onRunForChanged));
	box6->pack_start(*labelRunFor, Gtk::PACK_EXPAND_PADDING, 0);
	box6->pack_start(*comboRunFor, Gtk::PACK_EXPAND_PADDING, 0);


	// Box 7
	Gtk::Label *labelTitleVmem = Gtk::manage(new Gtk::Label("Virtual Memory"));
	labelTitleVmem->set_margin_top(10);
	Gtk::Grid *gridVmem = Gtk::manage(new Gtk::Grid());
	box7->pack_start(*gridVmem);
	gridVmem->attach(*labelTitleVmem, 0, 0, 2, 1);
	for (int i = 0; i < NUM_VPAGES; i++)
	{
		labelVmem1[i] = Gtk::manage(new Gtk::Label(std::to_string(i)));
		labelVmem2[i] = Gtk::manage(new Gtk::Label("X"));
		frameVmem2[i] = Gtk::manage(new Gtk::Frame());		// having a frame is necessary to place a border around the label
		labelVmem1[i]->set_size_request(25, 25);
		labelVmem2[i]->set_size_request(65, 25);
		frameVmem2[i]->set_border_width(3);
		frameVmem2[i]->add(*labelVmem2[i]);

		gridVmem->attach(*labelVmem1[i], 0, i+1, 1, 1);
		gridVmem->attach(*frameVmem2[i], 1, i+1, 1, 1);
	}


	// Box 8
	Gtk::Label *label_title_pmem = Gtk::manage(new Gtk::Label("Physical Memory"));
	label_title_pmem->set_margin_top(10);
	Gtk::Grid *grid_pmem = Gtk::manage(new Gtk::Grid());
	box8->pack_start(*grid_pmem);
	grid_pmem->attach(*label_title_pmem, 0, 0, 2, 1);
	for (int i = 0; i < NUM_PFRAMES; i++)
	{
		labelPmem1[i] = Gtk::manage(new Gtk::Label(std::to_string(i)));
		labelPmem2[i] = Gtk::manage(new Gtk::Label("X"));
		framePmem2[i] = Gtk::manage(new Gtk::Frame());		// having a frame is necessary to place a border around the label
		labelPmem1[i]->set_size_request(25, 25);
		labelPmem2[i]->set_size_request(65, 25);
		framePmem2[i]->set_border_width(3);
		framePmem2[i]->add(*labelPmem2[i]);

		grid_pmem->attach(*labelPmem1[i], 0, i+1, 1, 1);
		grid_pmem->attach(*framePmem2[i], 1, i+1, 1, 1);
	}

	defaultFontColor = labelTurnCount2->get_style_context()->get_color(Gtk::STATE_FLAG_NORMAL);
	defaultBackgroundColor = labelTurnCount2->get_style_context()->get_background_color(Gtk::STATE_FLAG_NORMAL);
	resetGUIColor();

	this->show_all();
}


void SimulationView::updateGUI()
{
	Gdk::RGBA colorFont(HIGHLIGHT_COLOR_FONT);
	Gdk::RGBA colorBg(HIGHLIGHT_COLOR_BG);

	// Update the turn count and page fault count
	labelTurnCount2->set_label(std::to_string(simulation->turnCount));
	labelPageFault2->set_label(std::to_string(simulation->faultCount));


	// Update the page table
	for (int i = 0; i < NUM_VPAGES; i++)
	{
		std::string temp;

		// Find the string to be written in the label
		if (simulation->pageTable[i].present)
			temp = std::to_string(simulation->pageTable[i].physicalPage);
		else
			temp = "X";

		// If the string has changed, write it and highlight it using a different color
		if (labelVmem2[i]->get_label().compare(temp) == 0)
		{
			labelVmem2[i]->override_color(defaultFontColor, Gtk::STATE_FLAG_NORMAL);
			labelVmem2[i]->override_background_color(defaultBackgroundColor, Gtk::STATE_FLAG_NORMAL);
		}
		else
		{
			labelVmem2[i]->override_color(colorFont, Gtk::STATE_FLAG_NORMAL);
			labelVmem2[i]->override_background_color(colorBg, Gtk::STATE_FLAG_NORMAL);
			labelVmem2[i]->set_label(temp);
		}
	}


	// Update the reversed page table
	for (int i = 0; i < NUM_PFRAMES; i++)
	{
		std::string temp;

		// Find the string to be written in the label
		if (simulation->reversePageTable[i].used)
			temp = std::to_string(simulation->reversePageTable[i].virtualPage);
		else
			temp = "X";

		// If the string has changed, write it and highlight it using a different color
		if (labelPmem2[i]->get_label().compare(temp) == 0)
		{
			labelPmem2[i]->override_color(defaultFontColor, Gtk::STATE_FLAG_NORMAL);
			labelPmem2[i]->override_background_color(defaultBackgroundColor, Gtk::STATE_FLAG_NORMAL);
		}
		else
		{
			labelPmem2[i]->override_color(colorFont, Gtk::STATE_FLAG_NORMAL);
			labelPmem2[i]->override_background_color(colorBg, Gtk::STATE_FLAG_NORMAL);
			labelPmem2[i]->set_label(temp);
		}
	}

	this->show_all();
}


void SimulationView::resetGUIColor()
{
	labelTurnCount2->override_color(defaultFontColor, Gtk::STATE_FLAG_NORMAL);
	labelPageFault2->override_color(defaultFontColor, Gtk::STATE_FLAG_NORMAL);

	for (int i = 0; i < NUM_VPAGES; i++)
	{
		labelVmem2[i]->override_color(defaultFontColor, Gtk::STATE_FLAG_NORMAL);
		labelVmem2[i]->override_background_color(defaultBackgroundColor, Gtk::STATE_FLAG_NORMAL);
	}

	for (int i = 0; i < NUM_PFRAMES; i++)
	{
		labelPmem2[i]->override_color(defaultFontColor, Gtk::STATE_FLAG_NORMAL);
		labelPmem2[i]->override_background_color(defaultBackgroundColor, Gtk::STATE_FLAG_NORMAL);
	}

	this->show_all();
}


void SimulationView::onBtnStartPauseClicked()
{
	state->startPause();
}


void SimulationView::onBtnStepClicked()
{
	state->step();
}


void SimulationView::onBtnResetClicked()
{
	state->reset();
}


void SimulationView::onComboPraChanged()
{
	simulation->setPra(comboPra->get_active_text());
}


void SimulationView::onSimSpeedChanged()
{
	if (comboSpeed->get_active_text().compare("Normal") == 0)
		timerDelayMilli = NORMAL_DELAY;
	else if (comboSpeed->get_active_text().compare("Fast") == 0)
		timerDelayMilli = FAST_DELAY;
	else
		timerDelayMilli = TURBO_DELAY;
	if (timerConnection.connected())
	{
		timerConnection.disconnect();
		sigc::slot<bool> my_slot = sigc::mem_fun(*this, &SimulationView::onRunTimerTimeout);
		timerConnection = Glib::signal_timeout().connect(my_slot, timerDelayMilli);
	}
}


void SimulationView::onRunForChanged()
{
	runFor = std::stoi(comboRunFor->get_active_text());
}


bool SimulationView::onRunTimerTimeout()
{
	state->timerTimeout();
	return true;		// true so the timer resets and continues
}


void SimulationView::simulationComplete()
{
	state->complete();
}


void SimulationView::setState(UIState *new_state)
{
	state = new_state;
	state->enterState();
}


// Class UIState member functions
void SimulationView::UIState::reset()
{
	if (view->timerConnection.connected())
		view->timerConnection.disconnect();
	delete view->simulation;
	view->simulation = new Simulation(view, view->comboPra->get_active_text());
	view->comboPra->set_sensitive(true);
	view->updateGUI();
	view->resetGUIColor();

	view->setState(view->pausedState);
}


void SimulationView::UIState::complete()
{
	view->setState(view->completedState);
}



// Nested class Running
void SimulationView::Running::enterState()
{
	view->btnStartPause->set_label("Pause");
	view->btnStep->set_sensitive(false);
	view->btnReset->set_sensitive(false);
	view->comboPra->set_sensitive(false);
	sigc::slot<bool> my_slot = sigc::mem_fun(*view, &SimulationView::onRunTimerTimeout);
	view->timerConnection = Glib::signal_timeout().connect(my_slot, view->timerDelayMilli);
}


void SimulationView::Running::startPause()
{
	view->setState(view->pausedState);
}


void SimulationView::Running::timerTimeout()
{
	view->simulation->doTurn();
}



// Nested class Paused
void SimulationView::Paused::enterState()
{
	view->btnStartPause->set_label("Start");
	view->btnStartPause->set_sensitive(true);
	view->btnStep->set_sensitive(true);
	view->btnReset->set_sensitive(true);
	if (view->timerConnection.connected())
		view->timerConnection.disconnect();
}


void SimulationView::Paused::startPause()
{
	view->setState(view->runningState);
}


void SimulationView::Paused::step()
{
	view->comboPra->set_sensitive(false);
	view->simulation->doTurn();
}



// Nested class Completed
void SimulationView::Completed::enterState()
{
	view->btnStartPause->set_sensitive(false);
	view->btnStep->set_sensitive(false);
	view->btnReset->set_sensitive(true);
	if (view->timerConnection.connected())
		view->timerConnection.disconnect();
}


