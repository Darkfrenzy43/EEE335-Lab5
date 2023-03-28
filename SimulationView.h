#pragma once

#include "config.h"
#include <gtkmm.h>
#include <iostream>
#include <thread>


// Forward declaration
class Simulation;


class SimulationView : public Gtk::Window
{

public:
	// Forward declaration of nested classes
	class UIState;
	class Running;
	class Paused;
	class Completed;

	// Attributes
	Simulation *simulation;
	int runFor = DEFAULT_RUN_FOR;

	// Constructor and destructor
	SimulationView();
	virtual ~SimulationView();

private:
	Gtk::Button *btnStartPause;
	Gtk::Button *btnStep;
	Gtk::Button *btnReset;

	Gtk::Label *labelTurnCount2;
	Gtk::Label *labelPageFault2;

	Gtk::ComboBoxText *comboPra;
	Gtk::ComboBoxText *comboSpeed;
	Gtk::ComboBoxText *comboRunFor;

	Gtk::Label *labelVmem1[NUM_VPAGES];
	Gtk::Label *labelVmem2[NUM_VPAGES];
	Gtk::Frame *frameVmem2[NUM_VPAGES];
	Gtk::Label *labelPmem1[NUM_VPAGES];
	Gtk::Label *labelPmem2[NUM_PFRAMES];
	Gtk::Frame *framePmem2[NUM_PFRAMES];

	Gdk::RGBA defaultFontColor;
	Gdk::RGBA defaultBackgroundColor;

	sigc::connection timerConnection;
	int timerDelayMilli;

public:
	UIState *state;
	Running *runningState;
	Paused *pausedState;
	Completed *completedState;

	void buildGui();
	void updateGUI();
	void resetGUIColor();

	void onBtnStartPauseClicked();
	void onBtnStepClicked();
	void onBtnResetClicked();
	void onComboPraChanged();
	void onSimSpeedChanged();
	void onRunForChanged();
	bool onRunTimerTimeout();

	void simulationComplete();
	void setState(UIState *new_state);


// Nested classes
public:
	class UIState
	{
	public:
		SimulationView *view;
		UIState(SimulationView *view): view(view) { }
		virtual ~UIState() { }
		virtual void enterState() = 0;
		virtual void startPause() { }
		virtual void step() { }
		virtual void reset();
		virtual void timerTimeout() { }
		virtual void complete();
	};

public:
	class Running : public UIState
	{
	public:
		Running(SimulationView *view) : UIState(view) { }
		void enterState();
		void startPause();
		void timerTimeout();
	};

public:
	class Paused : public UIState
	{
	public:
		Paused(SimulationView *view) : UIState(view) { }
		void enterState();
		void startPause();
		void step();
	};

public:
	class Completed : public UIState
	{
	public:
		Completed(SimulationView *view) : UIState(view) { }
		void enterState();
	};

};
